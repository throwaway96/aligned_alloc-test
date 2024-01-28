ifneq ($(NO_CROSS),)
	CROSS_COMPILE=
else
	CROSS_COMPILE=arm-webos-linux-gnueabi-
endif

CC=$(CROSS_COMPILE)gcc
CC+=-x c -pipe
CFLAGS+=-std=c17 -Wall -Wextra -O2 -ggdb -feliminate-unused-debug-types -ffile-prefix-map='$(dir $(PWD))='
LDFLAGS+=-ldl

BINS:=aa aa-c17

.PHONY: all
all: $(BINS)

aa: aa.c

aa-c17: aa-c17.c

.PHONY: clean
clean:
	rm -f -- $(BINS)
