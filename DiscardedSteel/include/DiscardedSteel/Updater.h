/*
 * Updater.h
 *
 *  Created on: Dec 11, 2015
 *      Author: pavel
 */

#ifndef DISCARDEDSTEEL_INCLUDE_DISCARDEDSTEEL_UPDATER_H_
#define DISCARDEDSTEEL_INCLUDE_DISCARDEDSTEEL_UPDATER_H_

#ifdef SWIG
    %feature("director") discarded_steel::Updater;
#else
#endif

namespace discarded_steel {

class Updater {
public:
    Updater();
    virtual ~Updater();

    virtual void update(int width, int height, const char* data) = 0;
};

} /* namespace discarded_steel */

#endif /* DISCARDEDSTEEL_INCLUDE_DISCARDEDSTEEL_UPDATER_H_ */
