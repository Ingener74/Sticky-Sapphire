#include "DiscardedSteel/Updater.h"
#include "DiscardedSteel/Capture.h"

namespace discarded_steel {

using namespace Poco;

Capture::Capture(int vid, int pid, int fd, Updater* updater) :
        _thread(this, &Capture::run), _updater(updater) {
    _thread.start();
}

Capture::~Capture() {
    _cond.broadcast();
    _thread.stop();
    _thread.wait();
}

void Capture::run() {
    while (_thread.isRunning()) {
        // do hard work ...

        _cond.wait(_mutex, 2000);

        if (_updater)
            _updater->update(100, 100, "hard work result");
    }
}

}
