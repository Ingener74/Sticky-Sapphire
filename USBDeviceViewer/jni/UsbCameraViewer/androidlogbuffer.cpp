/*
 * androidlogbuffer.cpp
 *
 *  Created on: Jul 16, 2014
 *      Author: ingener
 */

#include <UsbCameraViewer/androidlogbuffer.h>

namespace usbcv
{

android_log_buffer::android_log_buffer( std::ostream& stream, android_LogPriority priority ) :
        std::streambuf(), _buffer(1024), _stream(stream), _orig(stream.rdbuf()), _priority(priority)
{
    setp(&_buffer.front(), &_buffer.back() + 1);
    _stream.rdbuf(this);
}

android_log_buffer::~android_log_buffer()
{
    _stream.rdbuf(_orig);
}

int android_log_buffer::sync()
{
    __android_log_print(_priority, "UsbCameraViewer", "%s", pbase());
    pbump(-(pptr() - pbase()));
    for ( auto &b : _buffer )
    {
        b = 0;
    }
    return 0;
}

} /* namespace usbcv */
