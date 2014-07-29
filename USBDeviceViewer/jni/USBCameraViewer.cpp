#include <Common.h>
#include <androidlogbuffer.h>
#include <UsbCameraViewer.h>

using namespace std;
using namespace std::placeholders;
using namespace usbcv;

shared_ptr<streambuf> error_buf, debug_buf;
thread th;

struct Image
{
    int32_t rows;
    int32_t cols;
    int32_t bpp;
    vector<uint8_t> buffer;
};

void drawImage( Image image )
{
    cout << "draw image " << image.rows << " x " << image.cols << " " << image.bpp << " " << image.buffer.size()
            << endl;
}

void thread_func( promise<exception_ptr>& start, function<void( Image )> onNewImage )
{
    uvc_context_t * ctx = nullptr;
    uvc_device_t * dev = nullptr;
    uvc_device_handle_t * devh = nullptr;
    uvc_stream_handle *strmh = nullptr;
    uvc_stream_ctrl_t ctrl;

    try
    {
        uvc_error_t res;

        res = uvc_init(&ctx, NULL);
        if ( res < 0 ) throw runtime_error("can't init uvc");

        res = uvc_find_device(ctx, &dev, 0, 0, NULL);
        if ( res < 0 ) throw runtime_error("can't find device");

        res = uvc_open(dev, &devh);
        if ( res < 0 ) throw runtime_error("can't open device");

        res = uvc_stream_open_ctrl(devh, &strmh, &ctrl);
        if ( res < 0 ) throw runtime_error("can't open stream control");

//        res = uvc_get_stream_ctrl_format_size(devh, &ctrl, UVC_FRAME_FORMAT_YUYV, 640, 480, 30);
//        if ( res < 0 ) runtime_error("can't get stream control");

//        res = uvc_start_streaming(devh, &ctrl, nullptr, nullptr, 0);
//        if ( res < 0 ) runtime_error("can't start streaming");

        res = uvc_stream_start_iso(strmh, nullptr, nullptr);
        if ( res < 0 ) throw runtime_error("can't start isochronous stream");

        start.set_value(exception_ptr());

        for ( ;; )
        {
//          this_thread::yield(); /* for exit */

            uvc_frame* frame = nullptr;
            res = uvc_stream_get_frame(strmh, &frame, 0);
            if ( res < 0 ) throw runtime_error("can't get frame");

            uvc_frame_t *bgr = uvc_allocate_frame(frame->width * frame->height * 3); // RAII destroy: uvc_free_frame(bgr);
            if ( !bgr ) throw runtime_error("can't allocate frame");

            res = uvc_any2bgr(frame, bgr);
            if ( res < 0 ) throw runtime_error("can't convert any to bgr");

            Image newImage;
            onNewImage(newImage);

            uvc_free_frame(bgr);
        }

        uvc_stop_streaming(devh);
        uvc_close(devh);
        uvc_unref_device(dev);
        uvc_exit(ctx);
    }
    catch ( exception const & e )
    {
        start.set_exception(current_exception());
    }
}

bool start()
{
    error_buf = make_shared<android_log_buffer>(cerr, ANDROID_LOG_ERROR);
    debug_buf = make_shared<android_log_buffer>(cout);

    try
    {
        promise<exception_ptr> start_promise;
        auto start = start_promise.get_future();

        th = thread(thread_func, ref(start_promise), bind(drawImage, _1));
        th.detach();

        start.wait();
        if ( start.get() ) rethrow_exception(start.get());

        return true;
    }
    catch ( std::exception const & e )
    {
        cerr << "Error: " << e.what() << endl;
        return false;
    }
}

void stop()
{
    error_buf.reset();
    debug_buf.reset();
}

jboolean Java_com_shnaider_usbcameraviewer_USBCameraViewer_startUsbCameraViewer( JNIEnv * jniEnv, jobject self )
{
    return start();
}

void Java_com_shnaider_usbcameraviewer_USBCameraViewer_stopUsbCameraViewer( JNIEnv *, jobject )
{
    stop();
}
