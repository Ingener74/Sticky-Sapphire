cmake_minimum_required(VERSION 3.0)

set(usb_SOURCES
    core.c
    descriptor.c
    hotplug.c
    io.c
    strerror.c
    sync.c
    os/linux_netlink.c
    os/linux_usbfs.c
    os/poll_posix.c
    os/threads_posix.c
)

add_library(usb ${usb_SOURCES})
# target_link_libraries(usb log)