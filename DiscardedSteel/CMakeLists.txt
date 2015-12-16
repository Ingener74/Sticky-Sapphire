cmake_minimum_required(VERSION 3.0)

set(DiscardedSteel_SOURCES
    src/RgbImageViewer.cpp
    src/UsbCameraViewer.cpp
    src/Capture.cpp
    src/Updater.cpp
)

add_library(DiscardedSteel ${DiscardedSteel_SOURCES})
target_link_libraries(DiscardedSteel usb uvc log android jnigraphics)

if(NOT EXISTS ${SYSROOT})
    add_dependencies(DiscardedSteel ext_POCO)
endif()
