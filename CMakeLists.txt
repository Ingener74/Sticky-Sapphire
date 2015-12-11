cmake_minimum_required(VERSION 3.0)

include_directories(
    USBDeviceViewer/jni
    USBDeviceViewer/jni/libusb
    
    USBDeviceViewer/jni/libuvc/include
    
    DiscardedSteel/include
)

add_subdirectory(USBDeviceViewer/jni/libusb)

add_subdirectory(USBDeviceViewer/jni/libuvc)

add_definitions(-std=c++14)

add_subdirectory(DiscardedSteel)
