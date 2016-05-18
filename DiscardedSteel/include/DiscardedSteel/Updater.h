#pragma once

#ifdef SWIG
    %feature("director") discarded_steel::Updater;
#else
    #include <string>
#endif

namespace discarded_steel {

class Updater {
public:
    Updater();
    virtual ~Updater();

    virtual void update(int width, int height, const std::string& data) = 0;
};

}
