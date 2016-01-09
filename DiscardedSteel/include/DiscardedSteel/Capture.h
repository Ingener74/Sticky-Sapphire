/*
 * Capture.h
 *
 *  Created on: Dec 11, 2015
 *      Author: pavel
 */

#ifndef DISCARDEDSTEEL_INCLUDE_DISCARDEDSTEEL_CAPTURE_H_
#define DISCARDEDSTEEL_INCLUDE_DISCARDEDSTEEL_CAPTURE_H_

#ifdef SWIG
    %feature("director") discarded_steel::Updater;
#else
    #include <Poco/Activity.h>
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
};

} /* namespace discarded_steel */

#endif /* DISCARDEDSTEEL_INCLUDE_DISCARDEDSTEEL_CAPTURE_H_ */
