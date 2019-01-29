
FILES = nbtest load50 mapcmp polltest mapper setconsole inp outp \
	datasize dataalign netifdebug asynctest scullsingleTest sculluidTest polltest-pipe

KERNELDIR ?= /lib/modules/$(shell uname -r)/build
INCLUDEDIR = $(KERNELDIR)/include
CFLAGS = -O2 -fomit-frame-pointer -Wall -I$(INCLUDEDIR)

all: $(FILES)

clean:
	rm -f $(FILES) *~ core

