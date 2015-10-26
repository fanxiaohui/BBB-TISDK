-include Rules.make

MAKE_JOBS ?= 1

all: linux matrix-gui arm-benchmarks am-sysinfo matrix-gui-browser refresh-screen oprofile-example u-boot-spl ti-crypto-examples linux-dtbs wireless cryptodev sgx-modules 
clean: linux_clean matrix-gui_clean arm-benchmarks_clean am-sysinfo_clean matrix-gui-browser_clean refresh-screen_clean oprofile-example_clean u-boot-spl_clean ti-crypto-examples_clean linux-dtbs_clean wireless_clean cryptodev_clean sgx-modules_clean 
install: linux_install matrix-gui_install arm-benchmarks_install am-sysinfo_install matrix-gui-browser_install refresh-screen_install oprofile-example_install u-boot-spl_install ti-crypto-examples_install linux-dtbs_install wireless_install cryptodev_install sgx-modules_install 
# Kernel build targets
linux: linux-dtbs
	@echo =================================
	@echo     Building the Linux Kernel
	@echo =================================
	$(MAKE) -C $(LINUXKERNEL_INSTALL_DIR) ARCH=arm CROSS_COMPILE=$(CROSS_COMPILE) $(DEFCONFIG)
	$(MAKE) -j $(MAKE_JOBS) -C $(LINUXKERNEL_INSTALL_DIR) ARCH=arm CROSS_COMPILE=$(CROSS_COMPILE) zImage
	$(MAKE) -j $(MAKE_JOBS) -C $(LINUXKERNEL_INSTALL_DIR) ARCH=arm CROSS_COMPILE=$(CROSS_COMPILE) modules

linux_install: linux-dtbs_install
	@echo ===================================
	@echo     Installing the Linux Kernel
	@echo ===================================
	@if [ ! -d $(DESTDIR) ] ; then \
		echo "The extracted target filesystem directory doesn't exist."; \
		echo "Please run setup.sh in the SDK's root directory and then try again."; \
		exit 1; \
	fi
	install -d $(DESTDIR)/boot
	install $(LINUXKERNEL_INSTALL_DIR)/arch/arm/boot/zImage $(DESTDIR)/boot
	install $(LINUXKERNEL_INSTALL_DIR)/vmlinux $(DESTDIR)/boot
	install $(LINUXKERNEL_INSTALL_DIR)/System.map $(DESTDIR)/boot
	$(MAKE) -C $(LINUXKERNEL_INSTALL_DIR) ARCH=arm CROSS_COMPILE=$(CROSS_COMPILE) INSTALL_MOD_PATH=$(DESTDIR) modules_install

linux_clean:
	@echo =================================
	@echo     Cleaning the Linux Kernel
	@echo =================================
	$(MAKE) -C $(LINUXKERNEL_INSTALL_DIR) ARCH=arm CROSS_COMPILE=$(CROSS_COMPILE) mrproper
# Make Rules for matrix-gui project
matrix-gui:
	@echo =============================
	@echo      Building Matrix GUI
	@echo =============================
	@echo    NOTHING TO DO.  COMPILATION NOT REQUIRED

matrix-gui_clean:
	@echo =============================
	@echo      Cleaning Matrix GUI
	@echo =============================
	@echo    NOTHING TO DO.

matrix-gui_install:
	@echo =============================
	@echo     Installing Matrix GUI
	@echo =============================
	@cd example-applications; cd `find . -name "*matrix-gui-2.0*"`; make install
# arm-benchmarks build targets
arm-benchmarks:
	@echo =============================
	@echo    Building ARM Benchmarks
	@echo =============================
	@cd example-applications; cd `find . -name "*arm-benchmarks*"`; make

arm-benchmarks_clean:
	@echo =============================
	@echo    Cleaning ARM Benchmarks
	@echo =============================
	@cd example-applications; cd `find . -name "*arm-benchmarks*"`; make clean

arm-benchmarks_install:
	@echo ==============================================
	@echo   Installing ARM Benchmarks - Release version
	@echo ==============================================
	@cd example-applications; cd `find . -name "*arm-benchmarks*"`; make install

arm-benchmarks_install_debug:
	@echo ============================================
	@echo   Installing ARM Benchmarks - Debug Version
	@echo ============================================
	@cd example-applications; cd `find . -name "*arm-benchmarks*"`; make install_debug
# am-sysinfo build targets
am-sysinfo:
	@echo =============================
	@echo    Building AM Sysinfo
	@echo =============================
	@cd example-applications; cd `find . -name "*am-sysinfo*"`; make

am-sysinfo_clean:
	@echo =============================
	@echo    Cleaning AM Sysinfo
	@echo =============================
	@cd example-applications; cd `find . -name "*am-sysinfo*"`; make clean

am-sysinfo_install:
	@echo ===============================================
	@echo     Installing AM Sysinfo - Release version
	@echo ===============================================
	@cd example-applications; cd `find . -name "*am-sysinfo*"`; make install

am-sysinfo_install_debug:
	@echo =============================================
	@echo     Installing AM Sysinfo - Debug version
	@echo =============================================
	@cd example-applications; cd `find . -name "*am-sysinfo*"`; make install_debug
# matrix-gui-browser build targets
matrix-gui-browser:
	@echo =================================
	@echo    Building Matrix GUI Browser
	@echo =================================
	@cd example-applications; cd `find . -name "*matrix-gui-browser*"`; make -f Makefile.build release

matrix-gui-browser_clean:
	@echo =================================
	@echo    Cleaning Matrix GUI Browser
	@echo =================================
	@cd example-applications; cd `find . -name "*matrix-gui-browser*"`; make -f Makefile.build clean

matrix-gui-browser_install:
	@echo ===================================================
	@echo   Installing Matrix GUI Browser - Release version
	@echo ===================================================
	@cd example-applications; cd `find . -name "*matrix-gui-browser*"`; make -f Makefile.build install

matrix-gui-browser_install_debug:
	@echo =================================================
	@echo   Installing Matrix GUI Browser - Debug Version
	@echo =================================================
	@cd example-applications; cd `find . -name "*matrix-gui-browser*"`; make -f Makefile.build install_debug
# refresh-screen build targets
refresh-screen:
	@echo =============================
	@echo    Building Refresh Screen
	@echo =============================
	@cd example-applications; cd `find . -name "*refresh-screen*"`; make -f Makefile.build release

refresh-screen_clean:
	@echo =============================
	@echo    Cleaning Refresh Screen
	@echo =============================
	@cd example-applications; cd `find . -name "*refresh-screen*"`; make -f Makefile.build clean

refresh-screen_install:
	@echo ================================================
	@echo   Installing Refresh Screen - Release version
	@echo ================================================
	@cd example-applications; cd `find . -name "*refresh-screen*"`; make -f Makefile.build install

refresh-screen_install_debug:
	@echo ==============================================
	@echo   Installing Refresh Screen - Debug Version
	@echo ==============================================
	@cd example-applications; cd `find . -name "*refresh-screen*"`; make -f Makefile.build install_debug
# oprofile-example build targets
oprofile-example:
	@echo =============================
	@echo    Building OProfile Example
	@echo =============================
	@cd example-applications; cd `find . -name "*oprofile-example*"`; make

oprofile-example_clean:
	@echo =============================
	@echo    Cleaning OProfile Example
	@echo =============================
	@cd example-applications; cd `find . -name "*oprofile-example*"`; make clean

oprofile-example_install:
	@echo =============================================
	@echo     Installing OProfile Example - Debug version
	@echo =============================================
	@cd example-applications; cd `find . -name "*oprofile-example*"`; make install
# u-boot build targets
u-boot-spl: u-boot
u-boot-spl_clean: u-boot_clean
u-boot-spl_install: u-boot_install

u-boot:
	@echo ===================================
	@echo    Building U-boot
	@echo ===================================
	$(MAKE) -j $(MAKE_JOBS) -C $(TI_SDK_PATH)/board-support/u-boot-* CROSS_COMPILE=$(CROSS_COMPILE) $(UBOOT_MACHINE)
	$(MAKE) -j $(MAKE_JOBS) -C $(TI_SDK_PATH)/board-support/u-boot-* CROSS_COMPILE=$(CROSS_COMPILE)

u-boot_clean:
	@echo ===================================
	@echo    Cleaining U-boot
	@echo ===================================
	$(MAKE) -C $(TI_SDK_PATH)/board-support/u-boot-* CROSS_COMPILE=$(CROSS_COMPILE) distclean

u-boot_install:
	@echo ===================================
	@echo    Installing U-boot
	@echo ===================================
	@echo "Nothing to do"
# ti-crypto-examples build targets
ti-crypto-examples:
	@echo =================================
	@echo    Building TI Crypto Examples
	@echo =================================
	@cd example-applications; cd `find . -name "*ti-crypto-examples*"`; make release

ti-crypto-examples_clean:
	@echo =================================
	@echo    Cleaning TI Crypto Examples
	@echo =================================
	@cd example-applications; cd `find . -name "*ti-crypto-examples*"`; make clean

ti-crypto-examples_install:
	@echo ===================================================
	@echo   Installing TI Crypto Examples - Release version
	@echo ===================================================
	@cd example-applications; cd `find . -name "*ti-crypto-examples*"`; make install

ti-crypto-examples_install_debug:
	@echo =================================================
	@echo   Installing TI Crypto Examples - Debug Version
	@echo =================================================
	@cd example-applications; cd `find . -name "*ti-crypto-examples*"`; make install_debug
# Kernel DTB build targets
linux-dtbs:
	@echo =====================================
	@echo     Building the Linux Kernel DTBs
	@echo =====================================
	$(MAKE) -C $(LINUXKERNEL_INSTALL_DIR) ARCH=arm CROSS_COMPILE=$(CROSS_COMPILE) $(DEFCONFIG)
	$(MAKE) -j $(MAKE_JOBS) -C $(LINUXKERNEL_INSTALL_DIR) ARCH=arm CROSS_COMPILE=$(CROSS_COMPILE) am335x-evm.dtb am335x-evmsk.dtb am335x-bone.dtb am335x-boneblack.dtb

linux-dtbs_install:
	@echo =======================================
	@echo     Installing the Linux Kernel DTBs
	@echo =======================================
	@if [ ! -d $(DESTDIR) ] ; then \
		echo "The extracted target filesystem directory doesn't exist."; \
		echo "Please run setup.sh in the SDK's root directory and then try again."; \
		exit 1; \
	fi
	install -d $(DESTDIR)/boot
	@cp -f $(LINUXKERNEL_INSTALL_DIR)/arch/arm/boot/dts/*.dtb $(DESTDIR)/boot/

linux-dtbs_clean:
	@echo =======================================
	@echo     Cleaning the Linux Kernel DTBs
	@echo =======================================
	@echo "Nothing to do"

wireless: compat-modules
wireless_install: compat-modules_install
wireless_clean: compat-modules_clean

compat-modules: linux
	@echo ================================
	@echo      Building compat-modules
	@echo ================================
	@cd board-support/extra-drivers; \
	cd `find . -maxdepth 1 -name "*compat-wireless*"`; \
	make KLIB_BUILD=${LINUXKERNEL_INSTALL_DIR} KLIB=${DESTDIR} CC="cc" defconfig-wl18xx; \
	make KLIB_BUILD=${LINUXKERNEL_INSTALL_DIR} KLIB=${DESTDIR} CROSS_COMPILE=${CROSS_COMPILE} ARCH=arm

compat-modules_install:
	@echo ================================
	@echo      Installing compat-modules
	@echo ================================
	@cd board-support/extra-drivers; \
	cd `find . -maxdepth 1 -name "*compat-wireless*"`; \
	make DEPMOD=echo DESTDIR=${DESTDIR} KLIB_BUILD=${LINUXKERNEL_INSTALL_DIR} KLIB=${DESTDIR} INSTALL_MOD_PATH=${DESTDIR} CROSS_COMPILE=${CROSS_COMPILE} ARCH=arm modules_install

compat-modules_clean:
	@echo ================================
	@echo      Cleaning compat-modules
	@echo ================================
	@cd board-support/extra-drivers; \
	cd `find . -maxdepth 1 -name "*compat-wireless*"`; \
	make KLIB_BUILD=${LINUXKERNEL_INSTALL_DIR} KLIB=${DESTDIR} CROSS_COMPILE=${CROSS_COMPILE} ARCH=arm mrproper

cryptodev: linux
	@echo ================================
	@echo      Building cryptodev-linux
	@echo ================================
	@cd board-support/extra-drivers; \
	cd `find . -maxdepth 1 -name "cryptodev*"`; \
	make ARCH=arm KERNEL_DIR=$(LINUXKERNEL_INSTALL_DIR)

cryptodev_clean:
	@echo ================================
	@echo      Cleaning cryptodev-linux
	@echo ================================
	@cd board-support/extra-drivers; \
	cd `find . -maxdepth 1 -name "cryptodev*"`; \
	make ARCH=arm KERNEL_DIR=$(LINUXKERNEL_INSTALL_DIR) clean

cryptodev_install:
	@echo ================================
	@echo      Installing cryptodev-linux
	@echo ================================
	@if [ ! -d $(DESTDIR) ] ; then \
		echo "The extracted target filesystem directory doesn't exist."; \
		echo "Please run setup.sh in the SDK's root directory and then try again."; \
		exit 1; \
	fi
	@cd board-support/extra-drivers; \
	cd `find . -maxdepth 1 -name "cryptodev*"`; \
	make ARCH=arm  KERNEL_DIR=$(LINUXKERNEL_INSTALL_DIR)  INSTALL_MOD_PATH=$(DESTDIR) PREFIX=$(SDK_PATH_TARGET)  install
sgx-modules: linux
	@echo =====================================
	@echo      Building sgx-modules
	@echo =====================================
	@cd board-support/extra-drivers; \
	cd `find . -maxdepth 1 -name "sgx-modules*"`; \
	make ARCH=arm KERNELDIR=$(LINUXKERNEL_INSTALL_DIR) BUILD=release TI_PLATFORM=ti335x SUPPORT_XORG=0

sgx-modules_clean:
	@echo =====================================
	@echo      Cleaning sgx-modules
	@echo =====================================
	@cd board-support/extra-drivers; \
	cd `find . -maxdepth 1 -name "sgx-modules*"`; \
	make ARCH=arm KERNELDIR=$(LINUXKERNEL_INSTALL_DIR) clean

sgx-modules_install:
	@echo =====================================
	@echo      Installing sgx-modules
	@echo =====================================
	@if [ ! -d $(DESTDIR) ] ; then \
		echo "The extracted target filesystem directory doesn't exist."; \
		echo "Please run setup.sh in the SDK's root directory and then try again."; \
		exit 1; \
	fi
	@cd board-support/extra-drivers; \
	cd `find . -maxdepth 1 -name "sgx-modules*"`; \
	make -C $(LINUXKERNEL_INSTALL_DIR) SUBDIRS=`pwd` INSTALL_MOD_PATH=$(DESTDIR) PREFIX=$(SDK_PATH_TARGET) modules_install

