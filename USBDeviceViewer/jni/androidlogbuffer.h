/*
 * androidlogbuffer.h
 *
 *  Created on: Jul 16, 2014
 *      Author: ingener
 */

#ifndef ANDROIDLOGBUFFER_H_
#define ANDROIDLOGBUFFER_H_

#include <Common.h>

namespace usbcv
{

class android_log_buffer: public std::streambuf
{
public:
    android_log_buffer( std::ostream& stream, android_LogPriority priority = ANDROID_LOG_DEBUG );
    virtual ~android_log_buffer();

    virtual int sync();

private:
    std::vector<char> _buffer;
    std::ostream& _stream;
    std::streambuf* _orig = nullptr;
    android_LogPriority _priority;
};

} /* namespace usbcv */

#endif /* ANDROIDLOGBUFFER_H_ */
