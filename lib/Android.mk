LOCAL_PATH := $(call my-dir)
include $(CLEAR_VARS)

LOCAL_MODULE := app
LOCAL_CFLAGS := -Wall -Os
LOCAL_SRC_FILES := main.c libui.c json.c
LOCAL_C_INCLUDES += $(LOCAL_PATH)
LOCAL_LDLIBS += -llog

include $(BUILD_SHARED_LIBRARY)
