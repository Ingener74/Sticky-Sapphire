#include <vector>
#include <string>
#include <cstring>
#include <memory>
#include <iostream>

#include <android/log.h>

#include <UsbCameraViewer/androidlogbuffer.h>
#include <UsbCameraViewer.h>

using namespace std;
using namespace std::placeholders;
using namespace usbcv;

shared_ptr<streambuf> error, debug;

thread th;
exception_ptr error_ptr;

void start()
{
    error = make_shared<android_log_buffer>(cerr, ANDROID_LOG_ERROR);
    debug = make_shared<android_log_buffer>(cout);

    try
    {
        th = thread([]()
        {
            uvc_context_t * ctx = nullptr;
            uvc_device_t * dev = nullptr;
            uvc_device_handle_t * devh = nullptr;
            uvc_stream_ctrl_t ctrl;

            try
            {
                uvc_error_t res;

                res = uvc_init(&ctx, NULL);
                if ( res < 0 ) runtime_error("can't init uvc");

                res = uvc_find_device( ctx, &dev, 0, 0, NULL);
                if( res < 0) runtime_error("can't find device");

                res = uvc_open(dev, &devh);
                if (res < 0) runtime_error("can't open device");

                res = uvc_get_stream_ctrl_format_size(devh, &ctrl, UVC_FRAME_FORMAT_YUYV, 640, 480, 30);
                if(res < 0) runtime_error("can't get stream control");

                res = uvc_start_streaming(devh, &ctrl, nullptr, nullptr, 0);
                if(res < 0) runtime_error("can't start streaming");

                for(;;)
                {
//                    uvc_stream_get_frame()
                }

                uvc_stop_streaming(devh);
                uvc_close(devh);
                uvc_unref_device(dev);
                uvc_exit(ctx);

            }
            catch (exception const & e)
            {
                error_ptr = current_exception();
                cerr << "UvcImageGenerator error: " << e.what() << endl;
            }
        });
    }
    catch ( std::exception const & e )
    {
        cerr << "Error: " << e.what() << endl;
    }
}

void stop()
{
    error.reset();
    debug.reset();
}

jboolean Java_com_shnaider_usbcameraviewer_USBCameraViewer_startUsbCameraViewer( JNIEnv * jniEnv, jobject self )
{
    start();
    return true;
}

void Java_com_shnaider_usbcameraviewer_USBCameraViewer_stopUsbCameraViewer( JNIEnv *, jobject )
{
    stop();
}
