/*
 * Capture.cpp
 *
 *  Created on: Dec 11, 2015
 *      Author: pavel
 */

#include "DiscardedSteel/Updater.h"
#include "DiscardedSteel/Capture.h"

namespace discarded_steel {

using namespace Poco;

Capture::Capture(int vid, int pid, int fd, Updater* updater) :
        _thread(this, &Capture::run), _updater(updater) {
    _thread.start();
}

Capture::~Capture() {
}

void Capture::run() {
    while (_thread.isRunning()) {
        // do hard work ...

        Thread::sleep(2000);

        if (_updater)
            _updater->update(100, 100, "hard work result");
    }
}

} /* namespace discarded_steel */
