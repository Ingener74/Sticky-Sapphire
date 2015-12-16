/*
 * Capture.cpp
 *
 *  Created on: Dec 11, 2015
 *      Author: pavel
 */

#include "DiscardedSteel/Updater.h"
#include "DiscardedSteel/Capture.h"

namespace discarded_steel {

Capture::Capture(int vid, int pid, int fd, Updater* updater) :
        updater(updater) {

    if (updater)
        updater->update(100, 100, "Test");

}

Capture::~Capture() {
}

} /* namespace discarded_steel */
