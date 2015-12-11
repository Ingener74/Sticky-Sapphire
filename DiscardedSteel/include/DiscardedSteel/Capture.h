/*
 * Capture.h
 *
 *  Created on: Dec 11, 2015
 *      Author: pavel
 */

#ifndef DISCARDEDSTEEL_INCLUDE_DISCARDEDSTEEL_CAPTURE_H_
#define DISCARDEDSTEEL_INCLUDE_DISCARDEDSTEEL_CAPTURE_H_

namespace discarded_steel {

class Updater;

class Capture {
public:
    Capture(int vid, int pid, int fd, Updater*);
    virtual ~Capture();

private:
    Updater* updater = nullptr;
};

} /* namespace discarded_steel */

#endif /* DISCARDEDSTEEL_INCLUDE_DISCARDEDSTEEL_CAPTURE_H_ */
