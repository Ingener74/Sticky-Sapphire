cmake_minimum_required(VERSION 3.0)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/Gloomy-Dog")

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

add_subdirectory(WrenchRough)