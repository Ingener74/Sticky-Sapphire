#pragma once

#ifndef SWIG

#include <vector>
#include <sstream>
#include <stdexcept>

#include <libusb/libusb.h>
#include <libuvc/include/libuvc/libuvc.h>

namespace discarded_steel {

template<typename Res, typename Arg>
Res to_(Arg&& a)
{
    std::stringstream _;
    _ << a;
    Res res;
    _ >> res;

    return res;
}

class Uvc
{
public:
    Uvc(int vid, int pid, int fd);
    virtual ~Uvc();

    bool getImage(int& rows, int& cols, std::vector<char>& data);

    uvc_context_t* getContext();
    uvc_device_t* getDevice();
    uvc_device_handle_t* getDeviceHandle();
    uvc_stream_handle* getStreamHandle();
    uvc_stream_ctrl_t* getStreamControl();

private:
    uvc_context_t * m_context = nullptr;
    uvc_device_t * dev = nullptr;
    uvc_device_handle_t * devh = nullptr;
    uvc_stream_handle * strmh = nullptr;
    uvc_stream_ctrl_t ctrl;
};

inline uvc_context_t* Uvc::getContext() {
    return m_context;
}

inline uvc_device_t* Uvc::getDevice() {
    return dev;
}

inline uvc_device_handle_t* Uvc::getDeviceHandle() {
    return devh;
}

inline uvc_stream_handle* Uvc::getStreamHandle() {
    return strmh;
}

inline uvc_stream_ctrl_t* Uvc::getStreamControl() {
    return &ctrl;
}

}

#endif
