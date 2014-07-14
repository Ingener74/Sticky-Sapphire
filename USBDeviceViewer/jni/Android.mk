
LOCAL_PATH := $(call my-dir)

#include $(LOCAL_PATH)/png/Android.mk
#include $(LOCAL_PATH)/lua/Android.mk

include $(LOCAL_PATH)/libusb/Android.mk
include $(LOCAL_PATH)/libuvc/Android.mk

include $(CLEAR_VARS)

LOCAL_MODULE    := UsbCameraViewer

# LOCAL_CPPFLAGS := -Dcxx_flags
    
LOCAL_SRC_FILES :=                 \
    USBCameraViewer.cpp

LOCAL_LDLIBS    := -llog -landroid#  -lEGL -lGLESv2 -lz -lOpenSLES
#LOCAL_STATIC_LIBRARIES := #android_native_app_glue png lua

LOCAL_STATIC_LIBRARIES := usb1.0 uvc

include $(BUILD_SHARED_LIBRARY)

# import modules from <path-to-android-ndk>/sources/android/native_app_glue
# $(call import-module,android/native_app_glue) 
