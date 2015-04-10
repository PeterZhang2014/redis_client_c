
CROSS_COMPILE =
AS		= $(CROSS_COMPILE)as
LD		= $(CROSS_COMPILE)ld
CC		= $(CROSS_COMPILE)gcc
CPP		= $(CC) -E
AR		= $(CROSS_COMPILE)ar
NM		= $(CROSS_COMPILE)nm

STRIP		= $(CROSS_COMPILE)strip
OBJCOPY		= $(CROSS_COMPILE)objcopy
OBJDUMP		= $(CROSS_COMPILE)objdump

export AS LD CC CPP AR NM
export STRIP OBJCOPY OBJDUMP

CFLAGS := -Wall -O2 -g
CFLAGS += -I $(shell pwd)/lib_include/ \
		  -I $(shell pwd)/lib_include/hiredis/

LDFLAGS := -lpthread 

export CFLAGS LDFLAGS

TOPDIR := $(shell pwd)
export TOPDIR

TARGETDIR := $(TOPDIR)/target/

TARGET := $(TARGETDIR)redis_pubsub_test.out

#Library
DYLIBSUFFIX=so
STLIBSUFFIX=a
LIBNAME=libgenredisclient
DYLIBNAME=$(LIBNAME).$(DYLIBSUFFIX)
STLIBNAME=$(LIBNAME).$(STLIBSUFFIX)


 obj-y += main.o
 obj-y += lib_source/

all : 
	make -C ./ -f $(TOPDIR)/Makefile.build
	$(CC)  -o $(TARGET) built-in.o $(LDFLAGS)

clean:
	rm -f $(shell find -name "*.o")
	rm -f $(shell find -name "*.d")
	rm -f $(TARGET)
	rm -f $(TARGETDIR)* 

static: all
	$(AR) rcs  $(TARGETDIR)$(STLIBNAME) ./lib_source/built-in.o
.PHONY:all clean static
