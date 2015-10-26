#configuration
CONFIG +=  cross_compile shared qpa no_mocdepend release qt_no_framework
host_build {
    QT_ARCH = arm
    QT_TARGET_ARCH = arm
} else {
    QT_ARCH = arm
    QMAKE_DEFAULT_LIBDIRS = /opt/linaro-2013.03/arm-linux-gnueabihf/lib /home/gtbldadm/ti/oe-layersetup/build-CORTEX_1/arago-tmp-external-linaro-toolchain/sysroots/am335x-evm/lib /home/gtbldadm/ti/oe-layersetup/build-CORTEX_1/arago-tmp-external-linaro-toolchain/sysroots/am335x-evm/usr/lib /opt/linaro-2013.03/lib/gcc/arm-linux-gnueabihf/4.7.3 /opt/linaro-2013.03/lib/gcc /opt/linaro-2013.03/lib/gcc/arm-linux-gnueabihf
    QMAKE_DEFAULT_INCDIRS = /opt/linaro-2013.03/arm-linux-gnueabihf/include /opt/linaro-2013.03/arm-linux-gnueabihf/include/c++/4.7.3 /opt/linaro-2013.03/arm-linux-gnueabihf/include/c++/4.7.3/arm-linux-gnueabihf /opt/linaro-2013.03/arm-linux-gnueabihf/include/c++/4.7.3/backward /opt/linaro-2013.03/lib/gcc/arm-linux-gnueabihf/4.7.3/include /opt/linaro-2013.03/lib/gcc/arm-linux-gnueabihf/4.7.3/include-fixed /home/gtbldadm/ti/oe-layersetup/build-CORTEX_1/arago-tmp-external-linaro-toolchain/sysroots/am335x-evm/usr/include
}
QT_CONFIG +=  minimal-config small-config medium-config large-config full-config libudev evdev linuxfb c++11 egl eglfs opengl opengles2 shared qpa reduce_exports clock-gettime clock-monotonic posix_fallocate mremap getaddrinfo ipv6ifname getifaddrs inotify eventfd system-jpeg system-png png freetype harfbuzz system-zlib dbus openssl-linked pulseaudio icu concurrent audio-backend release

#versioning
QT_VERSION = 5.4.1
QT_MAJOR_VERSION = 5
QT_MINOR_VERSION = 4
QT_PATCH_VERSION = 1

#namespaces
QT_LIBINFIX = 
QT_NAMESPACE = 

# pkgconfig
PKG_CONFIG_SYSROOT_DIR = /home/gtbldadm/ti/oe-layersetup/build-CORTEX_1/arago-tmp-external-linaro-toolchain/sysroots/am335x-evm
PKG_CONFIG_LIBDIR = /home/gtbldadm/ti/oe-layersetup/build-CORTEX_1/arago-tmp-external-linaro-toolchain/sysroots/am335x-evm/usr/lib/pkgconfig

QT_GCC_MAJOR_VERSION = 4
QT_GCC_MINOR_VERSION = 7
QT_GCC_PATCH_VERSION = 3
