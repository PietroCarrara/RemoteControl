release: all
	psp-build-exports -k input_util_exp.exp
	psp-build-exports -s -k -v input_util_exp.exp

TARGET = input_util
OBJS = input_util.o

# Define to build this as a prx (instead of a static elf)
BUILD_PRX = 1
# Define the name of our custom exports (minus the .exp extension)
PRX_EXPORTS = input_util_exp.exp

USE_PSPSDK_LIBC = 1
# USE_KERNEL_LIBS = 1

INCDIR = 
CFLAGS = -O2 -G0 -Wall
CXXFLAGS = $(CFLAGS) -fno-exceptions -fno-rtti
ASFLAGS = $(CFLAGS) 
LDFLAGS = -nostartfiles

LIBDIR =

PSPSDK=$(shell psp-config --pspsdk-path)
include $(PSPSDK)/lib/build.mak
