cmake_minimum_required(VERSION 3.0)

set(DiscardedSteel_SOURCES
    src/RgbImageViewer.cpp
    src/UsbCameraViewer.cpp
    src/Capture.cpp
)

add_library(DiscardedSteel SHARED ${DiscardedSteel_SOURCES})
target_link_libraries(DiscardedSteel usb uvc log android jnigraphics)