#
# Copyright (C) 2013 The CyanogenMod Project
# Copyright (C) 2017 The LineageOS Project
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#      http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.
#

LOCAL_PATH := device/samsung/k3gxx

# Inherit from common 5420
-include device/samsung/universal5420-common/BoardConfigCommon.mk

# Device-specific headers
TARGET_SPECIFIC_HEADER_PATH := $(LOCAL_PATH)/include

# Platform
TARGET_SOC := exynos5422
TARGET_LINUX_KERNEL_VERSION := 3.10

# Bootloader
TARGET_OTA_ASSERT_DEVICE := k3g,k3gxx
TARGET_BOOTLOADER_BOARD_NAME := universal5422

# Device Tree
BOARD_USES_DT := true

# Camera
BOARD_USE_SAMSUNG_CAMERAFORMAT_NV21 := true
BOARD_NEEDS_MEMORYHEAPION := true

# ValidityService
BOARD_USES_VALIDITY := true

# Battery / charging mode
BOARD_CHARGER_ENABLE_SUSPEND := true
BOARD_CHARGING_MODE_BOOTING_LPM := /sys/class/power_supply/battery/batt_lp_charging
BOARD_BATTERY_DEVICE_NAME := battery
RED_LED_PATH := "/sys/devices/virtual/sec/led/led_r"
GREEN_LED_PATH := "/sys/devices/virtual/sec/led/led_g"
BLUE_LED_PATH := "/sys/devices/virtual/sec/led/led_b"
BACKLIGHT_PATH := "/sys/devices/14400000.fimd_fb/backlight/panel/brightness"
CHARGING_ENABLED_PATH := "/sys/class/power_supply/battery/batt_lp_charging"

# Kernel
BOARD_MKBOOTIMG_ARGS := --ramdisk_offset 0x01000000 --tags_offset 0x00000100
BOARD_KERNEL_SEPARATED_DT := true
TARGET_CUSTOM_DTBTOOL := dtbhtoolExynos
TARGET_KERNEL_SOURCE := kernel/samsung/k3gxx
TARGET_KERNEL_CONFIG := lineage_k3gxx_defconfig
BOARD_KERNEL_PAGESIZE := 2048

# Partitions
BOARD_BOOTIMAGE_PARTITION_SIZE := 13631488
BOARD_RECOVERYIMAGE_PARTITION_SIZE := 157286400
BOARD_SYSTEMIMAGE_PARTITION_SIZE := 2621440000
BOARD_USERDATAIMAGE_PARTITION_SIZE := 12442369024
BOARD_CACHEIMAGE_PARTITION_SIZE := 209715200
BOARD_CACHEIMAGE_FILE_SYSTEM_TYPE := ext4
BOARD_FLASH_BLOCK_SIZE := 131072

# ConsumerIR from hardware/samsung
IR_HAL_SUFFIX := universal5422

# Radio
BOARD_PROVIDES_LIBRIL := true
BOARD_MODEM_TYPE := xmm6360
BOARD_RIL_CLASS := ../../../device/samsung/k3gxx/ril

# Recovery
TARGET_RECOVERY_FSTAB := device/samsung/k3gxx/ramdisk/fstab.universal5422

# SELinux
BOARD_SEPOLICY_DIRS += \
    device/samsung/k3gxx/sepolicy

# Graphics
USE_OPENGL_RENDERER := true
NUM_FRAMEBUFFER_SURFACE_BUFFERS := 3
BOARD_USE_BGRA_8888 := true
BOARD_USES_VIRTUAL_DISPLAY := true
BOARD_USES_HWC_SERVICES := true

# HeartRate
TARGET_NO_SENSOR_PERMISSION_CHECK := true

# frameworks/native/libs/binder/Parcel.cpp
TARGET_GLOBAL_CFLAGS += -DDISABLE_ASHMEM_TRACKING

# Samsung OpenMAX Video
BOARD_USE_ENCODER_RGBINPUT_SUPPORT := true
TARGET_OMX_LEGACY_RESCALING := true
BOARD_USE_HEVC_HWIP := true

# Samsung OpenMAX Audio
BOARD_USE_WMA_CODEC := true
BOARD_USE_ALP_AUDIO := true
BOARD_USE_SEIREN_AUDIO := true

# Samsung Gralloc
TARGET_SAMSUNG_GRALLOC_EXTERNAL_USECASES := true

# HDMI
BOARD_USES_NEW_HDMI := true

# WFD
BOARD_USES_WFD := true

# Bluetooth
BOARD_CUSTOM_BT_CONFIG := $(LOCAL_PATH)/bluetooth/libbt_vndcfg.txt
BOARD_BLUETOOTH_BDROID_BUILDCFG_INCLUDE_DIR := $(LOCAL_PATH)/bluetooth

# NFC
BOARD_NFC_CHIPSET := pn547
BOARD_NFC_HAL_SUFFIX := $(TARGET_BOOTLOADER_BOARD_NAME)

# Legacy BLOB support
TARGET_NEEDS_PLATFORM_TEXT_RELOCATIONS := true

# CMHW
BOARD_HARDWARE_CLASS += hardware/samsung/cmhw
BOARD_HARDWARE_CLASS += device/samsung/k3gxx/cmhw

# SECCOMP
BOARD_SECCOMP_POLICY += device/samsung/k3gxx/seccomp
