#include <vector>
#include <string>
#include <cstring>
#include <memory>
#include <iostream>

#include <android/log.h>

#include <UsbCameraViewer.h>

using namespace std;

class android_log_buffer: public streambuf
{
public:
    android_log_buffer( ostream& stream, android_LogPriority priority = ANDROID_LOG_DEBUG ) :
            streambuf(), _buffer(1024), _stream(stream), _orig(stream.rdbuf()), _priority(priority)
    {
        setp(&_buffer.front(), &_buffer.back() + 1);
        _stream.rdbuf(this);
    }
    virtual ~android_log_buffer()
    {
        _stream.rdbuf(_orig);
    }

    virtual int sync()
    {
        __android_log_print(_priority, "UsbCameraViewer", "%s", pbase());
        pbump(-(pptr() - pbase()));
        for ( auto &b : _buffer )
        {
            b = 0;
        }
        return 0;
    }
private:
    vector<char> _buffer;
    ostream& _stream;
    streambuf* _orig = nullptr;
    android_LogPriority _priority;
};

shared_ptr<streambuf> _error, _debug;

void start()
{
    _error = make_shared<android_log_buffer>(cerr, ANDROID_LOG_ERROR);
    _debug = make_shared<android_log_buffer>(cout);

    cout << "Test android log buffer " << 3.1415 << ", e = " << 2.72 << endl;

    try
    {
        throw runtime_error("Test error");
    }
    catch ( std::exception const & e )
    {
        cerr << "Error: " << e.what() << endl;
    }
}

void stop()
{
    _error.reset();
    _debug.reset();
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
