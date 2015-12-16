cmake_minimum_required(VERSION 3.0)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/Gloomy-Dog")

unset(BUILD_PLATFORM)
if(ANDROID)
    set(BUILD_PLATFORM android)
else()
    message(FATAL_ERROR "Invalid build platform")
endif()

set(SYSROOT ${CMAKE_SOURCE_DIR}/3rdparty/sysroot-${BUILD_PLATFORM})

set(3RDPARTY_INSTALL ${SYSROOT})

if(NOT EXISTS ${SYSROOT})
    add_subdirectory(3rdparty)
endif()

include_directories(
    ${3RDPARTY_INSTALL}/include

    USBDeviceViewer/jni
    USBDeviceViewer/jni/libusb
    
    USBDeviceViewer/jni/libuvc/include
    
    DiscardedSteel/include
)
link_directories(${3RDPARTY_INSTALL}/lib)

add_subdirectory(USBDeviceViewer/jni/libusb)

add_subdirectory(USBDeviceViewer/jni/libuvc)

add_definitions(-std=c++14)

add_subdirectory(DiscardedSteel)

add_subdirectory(WrenchRough)