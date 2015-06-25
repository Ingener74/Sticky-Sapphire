
#include <future>
#include <iostream>
#include <stdexcept>
#include <sstream>

#include <android/log.h>

#include <libusb/libusb.h>
#include <libuvc/include/libuvc/libuvc.h>

#include "UsbCameraViewer.h"
#include "RgbImageViewer.h"

using namespace std;
using namespace std::placeholders;

/*
 * Definitions
 */

template<typename Res, typename Arg>
Res to_(Arg a)
{
    stringstream _;
    _ << a;
    Res res;
    _ >> res;

    return res;
}

class AndroidLogBuffer: public streambuf
{
public:
    AndroidLogBuffer(ostream& stream, android_LogPriority priority = ANDROID_LOG_DEBUG) :
            streambuf(), _buffer(1024), _stream(stream), _orig(stream.rdbuf()), _priority(priority)
    {
        setp(&_buffer.front(), &_buffer.back() + 1);
        _stream.rdbuf(this);
    }
    virtual ~AndroidLogBuffer()
    {
        _stream.rdbuf(_orig);
    }

    virtual int sync()
    {
        __android_log_print(_priority, "UsbCameraViewer", "%s", pbase());
        pbump(-(pptr() - pbase()));
        for (auto &b : _buffer)
        {
            b = 0;
        }
        return 0;
    }

private:
    vector<char> _buffer;
    ostream& _stream;
    streambuf* _orig = nullptr;
    android_LogPriority _priority = ANDROID_LOG_DEBUG;
};

/*
 * Data
 */
shared_ptr<streambuf> error_buf, debug_buf;
shared_ptr<RgbImageViewer> rgbImageViewer;

thread firstThread, secondThread;

atomic<bool> stopThread;
JavaVM *jvm = nullptr;

/*
 * Code
 */
jint JNI_OnLoad(JavaVM* vm, void* reserved)
{
    stopThread = false;

    error_buf = make_shared<AndroidLogBuffer>(cerr, ANDROID_LOG_ERROR);
    debug_buf = make_shared<AndroidLogBuffer>(cout);

    cout << "JNI_OnLoad( vm = " << vm << ", reserved = " << reserved << " )" << endl;
    cout << "test cout" << endl;
    cerr << "test cerr" << endl;

    jvm = vm;

    JNIEnv* jniEnv = nullptr;
    return jvm->GetEnv(reinterpret_cast<void**>(&jniEnv),
    JNI_VERSION_1_6) != JNI_OK ? -1 : JNI_VERSION_1_6;
}

void JNI_OnUnload(JavaVM* vm, void* reserved)
{
    cout << "JNI_OnUnload( vm = " << vm << ", reserved = " << reserved << " )" << endl;
    error_buf.reset();
    debug_buf.reset();
}

class Uvc
{
public:
    Uvc(int vid, int pid, int fd)
    {
        if (uvc_init(&ctx, NULL) < 0)
            throw runtime_error("can't init uvc");

        if (uvc_find_device(ctx, &dev, vid, pid, NULL) < 0)
            throw runtime_error("can't find device");

        if (uvc_open_android(dev, &devh, fd) < 0)
            throw runtime_error("can't open device " + to_<string>(fd));

        if (uvc_get_stream_ctrl_format_size(devh, &ctrl, UVC_FRAME_FORMAT_YUYV, 640, 480, 30) < 0)
            throw runtime_error("can't get stream control");

        if (uvc_stream_open_ctrl(devh, &strmh, &ctrl) < 0)
            throw runtime_error("can't open stream control");

        if (uvc_stream_start_iso(strmh, nullptr, nullptr) < 0)
            throw runtime_error("can't start isochronous stream");
    }
    virtual ~Uvc()
    {
        cout << __PRETTY_FUNCTION__ << endl;
        if (devh)
            uvc_stop_streaming(devh);
        if (devh)
            uvc_close(devh);
        if (dev)
            uvc_unref_device(dev);
        if (ctx)
            uvc_exit(ctx);
    }

    pair<bool, RgbImage> getImage()
    {
        uvc_frame* frame = nullptr;

        if (uvc_stream_get_frame(strmh, &frame, 100000) < 0)
            throw runtime_error("can't get frame");

        if (!frame || !frame->width || !frame->height || !frame->data)
        {
            cerr << "warning: can't get frame" << endl;
            return {false, {}};
        }

        shared_ptr<uvc_frame_t> bgr(uvc_allocate_frame(frame->width * frame->height * 3), [](uvc_frame* frame){
            uvc_free_frame(frame);
        });

        if (!bgr)
            throw runtime_error("can't allocate frame");

        if (uvc_any2rgb(frame, bgr.get()) < 0)
            throw runtime_error("can't convert any to bgr");

        RgbImage newImage;
        newImage.rows = bgr->height;
        newImage.cols = bgr->width;
        newImage.buffer = vector<uint8_t>(
                static_cast<uint8_t*>(bgr->data),
                static_cast<uint8_t*>(bgr->data) + (bgr->width * bgr->height * 3));

        return {true, newImage};
    }

    uvc_context_t* getContext()
    {
        return ctx;
    }
    uvc_device_t* getDevice()
    {
        return dev;
    }
    uvc_device_handle_t* getDeviceHandle()
    {
        return devh;
    }
    uvc_stream_handle* getStreamHandle()
    {
        return strmh;
    }
    uvc_stream_ctrl_t* getStreamControl()
    {
        return &ctrl;
    }

private:
    uvc_context_t * ctx = nullptr;
    uvc_device_t * dev = nullptr;
    uvc_device_handle_t * devh = nullptr;
    uvc_stream_handle * strmh = nullptr;
    uvc_stream_ctrl_t ctrl;
};

jboolean Java_com_shnaider_usbcameraviewer_USBCameraViewer_startUsbCameraViewer(JNIEnv * jniEnv, jobject self, jint vid,
        jint pid, jint fd)
{
    try
    {
        if(true == stopThread)
            return false;

        cout << "start usb camera with vid = " << vid << ", pid = " << pid << ", fd = " << fd << endl;

        cout << "create rgb image viewer" << endl;
        rgbImageViewer = make_shared<RgbImageViewer>(jniEnv, self);

        cout << "create control thread" << endl;
        firstThread = thread([=]()
        {
            while(!stopThread)
            {
                try
                {
                    promise<exception_ptr> error;
                    auto errorFuture = error.get_future();

                    cout << "create worker thread" << endl;
                    secondThread = thread([=, &error]()
                    {
                        try
                        {
                            Uvc uvc{vid, pid, fd};

                            while (!stopThread)
                            {
                                auto image = uvc.getImage();

                                if(!image.first)
                                    continue;

                                rgbImageViewer->drawRgbImage(image.second);
                            }
                        }
                        catch (exception const & e)
                        {
                            cerr << "working exception: " << e.what() << endl;

                            error.set_value(current_exception());
                        }
                    });

                    errorFuture.wait();

                    if(secondThread.joinable())
                        secondThread.join();

                    if(errorFuture.get())
                        rethrow_exception(errorFuture.get());

                }
                catch(exception const &e)
                {
                    cerr << "control exception: " << e.what() << endl;
                    this_thread::sleep_for(chrono::seconds(1));
                }
            }
        });

        return true;
    }
    catch (exception const & e)
    {
        cerr << "Error: " << e.what() << endl;
        return false;
    }
}

void Java_com_shnaider_usbcameraviewer_USBCameraViewer_stopUsbCameraViewer(JNIEnv *, jobject)
{
    cout << "stop capture thread" << endl;
    stopThread = true;

    cout << "wait control thread" << endl;
    if(firstThread.joinable())
        firstThread.join();

    cout << "capture thread stoped" << endl;
    stopThread = false;

    cout << "end" << endl;
}
