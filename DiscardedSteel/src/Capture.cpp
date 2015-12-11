/*
 * Capture.cpp
 *
 *  Created on: Dec 11, 2015
 *      Author: pavel
 */

#include "DiscardedSteel/Capture.h"

namespace discarded_steel {

Capture::Capture(int vid, int pid, int fd, Updater* updater) :
    updater(updater) {
}

Capture::~Capture() {
}

} /* namespace discarded_steel */
