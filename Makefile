SUBDIRS = input_util
release:
	@for i in $(SUBDIRS); do echo "make all in $$i...";  (cd $$i; $(MAKE); cp $$i.prx ..; cp $$i.S ..); done 
	make all

USE_PSPSDK_LIBC = 1

TARGET = remote

OBJS   = main.o wifi-util.o graphics.o $(INPUT_UTIL_OBJS)
CFLAGS = -O2 -G0 -Wall 
ASFLAGS = $(CFLAGS) 
LIBS = -lpsphttp -lpspssl -lpspgu

EXTRA_TARGETS = EBOOT.PBP 

PSP_EBOOT_TITLE = Remote Control

# Compile the input_util module functions
INPUT_UTIL_OBJS = input_util_0000.o input_util_0001.o input_util_0002.o input_util_0003.o input_util_0004.o input_util_0005.o
$(INPUT_UTIL_OBJS): input_util.S 
	psp-gcc $(CFLAGS) -DF_$* $< -c -o $@ 

PSPSDK=$(shell psp-config --pspsdk-path)
include $(PSPSDK)/lib/build.mak
