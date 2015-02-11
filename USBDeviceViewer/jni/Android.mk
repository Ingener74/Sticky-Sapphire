
LOCAL_PATH := $(call my-dir)

include $(LOCAL_PATH)/libusb/Android.mk
include $(LOCAL_PATH)/libuvc/Android.mk

include $(CLEAR_VARS)

LOCAL_MODULE    := UsbCameraViewer

# LOCAL_CPPFLAGS := -D<cxx_flag>

LOCAL_C_INCLUDES :=                    \
	$(LOCAL_PATH)/libusb               \
	$(LOCAL_PATH)/libuvc/include       \

LOCAL_SRC_FILES :=                     \
    UsbCameraViewer.cpp                \
    RgbImageViewer.cpp                 \

LOCAL_LDLIBS    := -llog -landroid -ljnigraphics

LOCAL_STATIC_LIBRARIES := uvc

include $(BUILD_SHARED_LIBRARY)

# $(call import-module,android/native_app_glue) 
