
LOCAL_MODULE := uvc
LOCAL_MODULE_FILENAME := libuvc

LOCAL_C_INCLUDES := $(LOCAL_PATH)/libusb
LOCAL_C_INCLUDES += $(LOCAL_PATH)/libuvc/include

LOCAL_SRC_FILES :=               \
    libuvc/src/ctrl.c            \
    libuvc/src/ctrl-gen.c        \
    libuvc/src/device.c          \
    libuvc/src/diag.c            \
    libuvc/src/frame.c           \
    libuvc/src/init.c            \
    libuvc/src/misc.c            \
    libuvc/src/stream.c          \
    
LOCAL_STATIC_LIBRARIES := usb1.0

include $(BUILD_STATIC_LIBRARY)