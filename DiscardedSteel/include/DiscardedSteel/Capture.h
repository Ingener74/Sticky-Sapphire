#pragma once

#ifdef SWIG
#else
    #include <Poco/Activity.h>
    #include <Poco/Condition.h>
#endif

namespace discarded_steel {

class Updater;

class Capture {
public:
    Capture(int vid, int pid, int fd, Updater*);
    virtual ~Capture();

    void run();

private:
    Poco::Activity<Capture> _thread;
    Updater* _updater = nullptr;

    Poco::Mutex _mutex;
    Poco::Condition _cond;
};

}
