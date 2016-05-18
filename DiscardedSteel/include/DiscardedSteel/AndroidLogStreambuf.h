#pragma once

#include <vector>
#include <iostream>

#include <android/log.h>

namespace discarded_steel {

class AndroidLogStreambuf: public std::streambuf {
public:
    AndroidLogStreambuf(std::ostream& stream, android_LogPriority priority = ANDROID_LOG_DEBUG);
    virtual ~AndroidLogStreambuf();

    virtual int sync();

private:
    std::vector<char> m_buffer;
    std::ostream& m_stream;
    std::streambuf* m_orig = nullptr;
    android_LogPriority m_priority = ANDROID_LOG_DEBUG;
};

}
