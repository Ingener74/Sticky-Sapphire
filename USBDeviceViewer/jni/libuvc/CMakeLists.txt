cmake_minimum_required(VERSION 3.0)

set(uvc_SOURCES
    src/ctrl.c
    src/ctrl-gen.c
    src/device.c
    src/diag.c
    src/frame.c
    src/init.c
    src/misc.c
    src/stream.c
)

add_library(uvc ${uvc_SOURCES})
target_link_libraries(uvc usb)