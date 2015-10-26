GENCCODE_ASSEMBLY_TYPE=-a gcc
SO=so
SOBJ=so
A=a
LIBPREFIX=lib
LIB_EXT_ORDER=.51.2
COMPILE=arm-linux-gnueabihf-gcc  -march=armv7-a -marm -mthumb-interwork -mfloat-abi=hard -mfpu=neon -mtune=cortex-a8 --sysroot=/home/gtbldadm/ti/oe-layersetup/build-CORTEX_1/arago-tmp-external-linaro-toolchain/sysroots/am335x-evm -isystem/opt/linaro-2013.03/arm-linux-gnueabihf/include  -fstack-protector -D_REENTRANT   -DU_ATTRIBUTE_DEPRECATED= -isystem/opt/linaro-2013.03/arm-linux-gnueabihf/include  -fstack-protector -O2 -pipe -g -feliminate-unused-debug-types -Wall -std=c99 -pedantic -Wshadow -Wpointer-arith -Wmissing-prototypes -Wwrite-strings  -c
LIBFLAGS=-I/usr/include -DPIC -fPIC
GENLIB=arm-linux-gnueabihf-gcc  -march=armv7-a -marm -mthumb-interwork -mfloat-abi=hard -mfpu=neon -mtune=cortex-a8 --sysroot=/home/gtbldadm/ti/oe-layersetup/build-CORTEX_1/arago-tmp-external-linaro-toolchain/sysroots/am335x-evm -isystem/opt/linaro-2013.03/arm-linux-gnueabihf/include  -fstack-protector -O2 -pipe -g -feliminate-unused-debug-types -Wall -std=c99 -pedantic -Wshadow -Wpointer-arith -Wmissing-prototypes -Wwrite-strings  -L/opt/linaro-2013.03/arm-linux-gnueabihf/lib -Wl,-rpath-link,/opt/linaro-2013.03/arm-linux-gnueabihf/lib -Wl,-O1 -Wl,--hash-style=gnu  -shared -Wl,-Bsymbolic
LDICUDTFLAGS=
LD_SONAME=-Wl,-soname -Wl,
RPATH_FLAGS=
BIR_LDFLAGS=-Wl,-Bsymbolic
AR=arm-linux-gnueabihf-ar
ARFLAGS=r
RANLIB=arm-linux-gnueabihf-ranlib
INSTALL_CMD=/usr/bin/install -c
