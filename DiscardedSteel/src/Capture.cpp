#include "DiscardedSteel/Uvc.h"
#include "DiscardedSteel/RgbImage.h"
#include "DiscardedSteel/Updater.h"
#include "DiscardedSteel/AndroidLogStreambuf.h"
#include "DiscardedSteel/Capture.h"

namespace discarded_steel {

using namespace std;
using namespace Poco;

Capture::Capture(int vid, int pid, int fd, Updater* updater) :
    m_thread(this, &Capture::run), m_updater(updater),
    m_cout(new AndroidLogStreambuf(cout)),
    m_cerr(new AndroidLogStreambuf(cerr, ANDROID_LOG_ERROR)) {
    if(m_updater)
        m_thread.start();
}

Capture::~Capture() {
    m_thread.stop();
    m_thread.wait();
}

void Capture::run() {

    m_uvc.reset(new Uvc(m_vid, m_pid, m_fd));

    while (m_thread.isRunning()) {

        // do hard work ...

        int rows, cols;
        vector<char> data;
        if(!m_uvc->getImage(rows, cols, data))
            continue;

        for (auto& c : data)
            if (c == 0)
                c = 1;

        if (m_updater)
            m_updater->update(cols, rows, std::string(data.data()));
    }
}

}
