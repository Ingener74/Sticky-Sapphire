
#include <Common.h>
#include <Error.h>
#include <UsbCameraViewer.h>
#include <RgbImageViewer.h>

using namespace std;
using namespace std::placeholders;

/*
 * Definitions
 */
template <typename Res, typename Arg>
Res to_( Arg a )
{
    stringstream _;
    _ << a;
    Res res;
    _ >> res;

    return res;
}

class AndroidLogBuffer: public std::streambuf
{
public:
	AndroidLogBuffer(std::ostream& stream, android_LogPriority priority = ANDROID_LOG_DEBUG) :
			std::streambuf(), _buffer(1024), _stream(stream), _orig(stream.rdbuf()), _priority(priority)
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
	std::vector<char> _buffer;
	std::ostream& _stream;
	std::streambuf* _orig = nullptr;
	android_LogPriority _priority;
};

/*
 * Data
 */
shared_ptr<streambuf> error_buf, debug_buf;
shared_ptr<RgbImageViewer> rgbImageViewer;
thread th;
JavaVM *jvm = nullptr;

/*
 * Code
 */
jint JNI_OnLoad( JavaVM* vm, void* reserved )
{
    error_buf = make_shared<AndroidLogBuffer>(cerr, ANDROID_LOG_ERROR);
    debug_buf = make_shared<AndroidLogBuffer>(cout);

    cout << "JNI_OnLoad( vm = " << vm << ", reserved = " << reserved << " )" << endl;
    cout << "test cout" << endl;
    cerr << "test cerr" << endl;

    jvm = vm;

    JNIEnv* jniEnv = nullptr;
    if ( jvm->GetEnv(reinterpret_cast<void**>(&jniEnv), JNI_VERSION_1_6) != JNI_OK )
    {
        return -1;
    }

    return JNI_VERSION_1_6;
}

void JNI_OnUnload( JavaVM* vm, void* reserved )
{
    cout << "JNI_OnUnload( vm = " << vm << ", reserved = " << reserved << " )" << endl;
    error_buf.reset();
    debug_buf.reset();
}

void thread_func( int vid, int pid, int fd, promise<exception_ptr>& start,
        function<void( RgbImage)> onNewImage )
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
        if ( res < 0 ) throw Error("can't init uvc");

        res = uvc_find_device(ctx, &dev, vid, pid, NULL);
        if ( res < 0 ) throw Error("can't find device");

        res = uvc_open_android(dev, &devh, fd);
        if ( res < 0 ) throw Error("can't open device " + to_<string>(fd));

        res = uvc_get_stream_ctrl_format_size(devh, &ctrl, UVC_FRAME_FORMAT_YUYV, 640, 480, 30);
        if ( res < 0 ) throw Error("can't get stream control");

        res = uvc_stream_open_ctrl(devh, &strmh, &ctrl);
        if ( res < 0 ) throw Error("can't open stream control");

        res = uvc_stream_start_iso(strmh, nullptr, nullptr);
        if ( res < 0 ) throw Error("can't start isochronous stream");

        start.set_value(exception_ptr());

        for ( ;; )
        {
            uvc_frame* frame = nullptr;
            res = uvc_stream_get_frame(strmh, &frame, 100000);
            if ( res < 0 ) throw Error("can't get frame");
            if ( !frame || !frame->width || !frame->height || !frame->data )
            {
                cerr << "warning: can't get frame" << endl;
                continue;
            }

            shared_ptr<uvc_frame_t> bgr(uvc_allocate_frame(frame->width * frame->height * 3), bind(uvc_free_frame, _1));
            if ( !bgr ) throw Error("can't allocate frame");

            res = uvc_any2rgb(frame, bgr.get());
            if ( res < 0 ) throw Error("can't convert any to bgr");

            RgbImage newImage;
            newImage.rows = bgr->height;
            newImage.cols = bgr->width;
            newImage.buffer = vector<uint8_t>(static_cast<uint8_t*>(bgr->data),
                    static_cast<uint8_t*>(bgr->data) + (bgr->width * bgr->height * 3));

            onNewImage(newImage);
        }

        uvc_stop_streaming(devh);
        uvc_close(devh);
        uvc_unref_device(dev);
        uvc_exit(ctx);
    }
    catch ( exception const & e )
    {
        cerr << "uvc thread error " << e.what() << endl;
        auto curError = current_exception();
        start.set_exception(curError);
    }
}

jboolean Java_com_shnaider_usbcameraviewer_USBCameraViewer_startUsbCameraViewer( JNIEnv * jniEnv, jobject self,
        jint vid, jint pid, jint fd )
{
    try
    {
        rgbImageViewer = make_shared<RgbImageViewer>(jniEnv, self);

        promise<exception_ptr> start_promise;
        auto start = start_promise.get_future();

        th = thread(thread_func, vid, pid, fd, ref(start_promise), bind(&RgbImageViewer::drawRgbImage, rgbImageViewer.get(), _1));
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

void Java_com_shnaider_usbcameraviewer_USBCameraViewer_stopUsbCameraViewer( JNIEnv *, jobject )
{
    cout << "stop capture thread" << endl;
    th = thread();
}
