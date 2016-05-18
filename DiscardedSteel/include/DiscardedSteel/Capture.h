#pragma once

#ifdef SWIG
#else
    #include <memory>
    #include <Poco/Activity.h>
    #include <Poco/Condition.h>
#endif

namespace discarded_steel {

class Uvc;
class Updater;
class AndroidLogStreambuf;

class Capture {
public:
    Capture(int vid, int pid, int fd, Updater*);
    virtual ~Capture();

    void run();

private:
    Poco::Activity<Capture> m_thread;
    Updater* m_updater = nullptr;

    int m_vid = -1, m_pid = -1, m_fd = -1;
    std::unique_ptr<Uvc> m_uvc;

    std::unique_ptr<AndroidLogStreambuf> m_cout, m_cerr;
};

}
