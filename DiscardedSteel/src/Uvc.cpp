
#include <memory>
#include <iostream>
#include "DiscardedSteel/Uvc.h"

namespace discarded_steel {

using namespace std;

Uvc::Uvc(int vid, int pid, int fd) {
    if (uvc_init(&m_context, NULL) < 0)
        throw runtime_error("can't init uvc");

    if (uvc_find_device(m_context, &dev, vid, pid, NULL) < 0)
        throw runtime_error("can't find device");

    if (uvc_open_android(dev, &devh, fd) < 0)
        throw runtime_error("can't open device " + to_<string>(fd));

    if (uvc_get_stream_ctrl_format_size(devh, &ctrl, UVC_FRAME_FORMAT_YUYV, 640, 480, 30) < 0)
        throw runtime_error("can't get stream control");

    if (uvc_stream_open_ctrl(devh, &strmh, &ctrl) < 0)
        throw runtime_error("can't open stream control");

    if (uvc_stream_start_iso(strmh, nullptr, nullptr) < 0)
        throw runtime_error("can't start isochronous stream");
}

Uvc::~Uvc() {
    cout << __PRETTY_FUNCTION__ << endl;
    if (devh)
        uvc_stop_streaming(devh);
    if (devh)
        uvc_close(devh);
    if (dev)
        uvc_unref_device(dev);
    if (m_context)
        uvc_exit(m_context);
}

bool Uvc::getImage(int& rows, int& cols, std::vector<char>& data)
{
    uvc_frame* frame = nullptr;

    if (uvc_stream_get_frame(strmh, &frame, 100000) < 0)
        throw runtime_error("can't get frame");

    if (!frame || !frame->width || !frame->height || !frame->data)
    {
        cerr << "warning: can't get frame" << endl;
        return false;
    }

    unique_ptr<uvc_frame_t, void(*)(uvc_frame*)> bgr(uvc_allocate_frame(frame->width * frame->height * 3), uvc_free_frame);

    if (!bgr)
        throw runtime_error("can't allocate frame");

    if (uvc_any2rgb(frame, bgr.get()) < 0)
        throw runtime_error("can't convert any to bgr");

    rows = bgr->height;
    cols = bgr->width;
    data = vector<char>(
            static_cast<char*>(bgr->data),
            static_cast<char*>(bgr->data) + (bgr->width * bgr->height * 3));

    return true;
}

}
