#platform
PLATFORM=am335x-evm

#defconfig
DEFCONFIG=singlecore-omap2plus_defconfig

#Architecture
ARCH=armv7-a

#u-boot machine
UBOOT_MACHINE=am335x_evm_config

#Points to the root of the TI SDK
export TI_SDK_PATH=/home/lixin/develop/BBB/BBB-TISDK

#root of the target file system for installing applications
DESTDIR=__DESTDIR__

#Points to the root of the Linux libraries and headers matching the
#demo file system.
export LINUX_DEVKIT_PATH=$(TI_SDK_PATH)/linux-devkit

#Cross compiler prefix
export CROSS_COMPILE=$(LINUX_DEVKIT_PATH)/sysroots/i686-arago-linux/usr/bin/arm-linux-gnueabihf-

#Default CC value to be used when cross compiling.  This is so that the
#GNU Make default of "cc" is not used to point to the host compiler
export CC=$(CROSS_COMPILE)gcc

#Location of environment-setup file
export ENV_SETUP=$(LINUX_DEVKIT_PATH)/environment-setup

#The directory that points to the SDK kernel source tree
LINUXKERNEL_INSTALL_DIR=$(TI_SDK_PATH)/board-support/linux-3.14.26-g2489c02

CFLAGS= -march=armv7-a -marm -mthumb-interwork -mfloat-abi=hard -mfpu=neon -mtune=cortex-a8

SDK_PATH_TARGET=$(TI_SDK_PATH)/linux-devkit/sysroots/cortexa8t2hf-vfp-neon-linux-gnueabi/

MAKE_JOBS=4
