LOCAL_PATH:= $(call my-dir)
include $(CLEAR_VARS)

# ARM instruction can be little bit faster in some cases
# For speed up compile code as ARM instruction instead of THUMB.
LOCAL_ARM_MODE := arm

snappy_files := \
	snappy.cc \
	snappy-c.cc \
	snappy-sinksource.cc \
	snappy-stubs-internal.cc

snappy_c_includes += $(LOCAL_PATH)/

LOCAL_MODULE := libsnappy
LOCAL_CPP_EXTENSION := .cc

LOCAL_C_INCLUDES := $(snappy_c_includes)
LOCAL_CFLAGS := -Wno-unused-parameter \
                -Wno-unused-variable \
                -Wno-unused-label \
                -Wno-sign-compare
LOCAL_MODULE_TAGS := optional
LOCAL_SRC_FILES := $(snappy_files)

ANDROID_M_OR_LATER := $(shell if [ "$(PLATFORM_SDK_VERSION)" -ge "23" ] ; then echo "true"; fi)
ifeq ($(ANDROID_M_OR_LATER),true)
    LOCAL_CXX_STL := default
else
    LOCAL_SHARED_LIBRARIES := libstlport
    include external/stlport/libstlport.mk
endif

include $(BUILD_SHARED_LIBRARY)
