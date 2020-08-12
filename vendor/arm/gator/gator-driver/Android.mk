LOCAL_PATH := $(call my-dir)
DLKM_DIR := $(TOP)/device/qcom/common/dlkm
KBUILD_OPTIONS := GATOR_DIR=$(CURDIR)/$(LOCAL_PATH)
include $(CLEAR_VARS)
LOCAL_MODULE             := gator.ko
LOCAL_MODULE_TAGS        := debug
LOCAL_MODULE_PATH        := $(TARGET_OUT)/lib/modules
include $(DLKM_DIR)/AndroidKernelModule.mk

