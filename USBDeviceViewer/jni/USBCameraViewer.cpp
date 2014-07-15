#include <vector>
#include <string>
#include <cstring>
#include <memory>
#include <iostream>

#include <android/log.h>

#include <UsbCameraViewer/androidlogbuffer.h>
#include <UsbCameraViewer.h>

using namespace std;
using namespace usbcv;

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
