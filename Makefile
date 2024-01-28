ifneq ($(NO_CROSS),)
	CROSS_COMPILE=
else
	CROSS_COMPILE=arm-webos-linux-gnueabi-
endif

CC=$(CROSS_COMPILE)gcc
CC+=-x c -pipe
CFLAGS+=-std=c17 -Wall -Wextra -O2 -ggdb -feliminate-unused-debug-types -fdebug-prefix-map='$(dir $(PWD))='
LDFLAGS+=-ldl

BINS:=aa

.PHONY: all
all: $(BINS)

aa: aa.c

.PHONY: clean
clean:
	rm -f -- $(BINS)
