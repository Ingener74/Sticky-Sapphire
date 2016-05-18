#include "DiscardedSteel/AndroidLogStreambuf.h"

namespace discarded_steel {

using namespace std;

AndroidLogStreambuf::AndroidLogStreambuf(std::ostream& stream, android_LogPriority priority) :
    streambuf(), m_buffer(1 << 12), m_stream(stream), m_orig(stream.rdbuf()), m_priority(priority) {
    setp(m_buffer.data(), m_buffer.data() + m_buffer.size());
    m_stream.rdbuf(this);
}

AndroidLogStreambuf::~AndroidLogStreambuf() {
    m_stream.rdbuf(m_orig);
}

int AndroidLogStreambuf::sync() {
    __android_log_print(m_priority, "UsbCameraViewer", "%s", m_buffer.data());
    setp(m_buffer.data(), m_buffer.data() + m_buffer.size());
    for (auto& b : m_buffer)
        b = 0;
    return 0;
}

}
