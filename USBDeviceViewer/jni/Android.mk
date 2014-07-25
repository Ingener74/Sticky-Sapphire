
LOCAL_PATH := $(call my-dir)

include $(LOCAL_PATH)/libusb/Android.mk
include $(LOCAL_PATH)/libuvc/Android.mk

include $(CLEAR_VARS)

LOCAL_MODULE    := UsbCameraViewer

# LOCAL_CPPFLAGS := -Dcxx_flags

LOCAL_C_INCLUDES :=                    \
	$(LOCAL_PATH)/libusb               \
	$(LOCAL_PATH)/libuvc/include       \

LOCAL_SRC_FILES :=                     \
    USBCameraViewer.cpp                \
    androidlogbuffer.cpp               \

LOCAL_LDLIBS    := -llog -landroid

LOCAL_STATIC_LIBRARIES := uvc

include $(BUILD_SHARED_LIBRARY)

# import modules from <path-to-android-ndk>/sources/android/native_app_glue
# $(call import-module,android/native_app_glue) 
