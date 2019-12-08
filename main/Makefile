#
# Copyright © 2019 Keith Packard <keithp@keithp.com>
#
# This program is free software; you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# This program is distributed in the hope that it will be useful, but
# WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
# General Public License for more details.
#

SNEK_ROOT=..

include $(SNEK_ROOT)/draw/snek-draw.defs

SNEK_LOCAL_VPATH = $(SNEK_DRAW_VPATH)

SNEK_LOCAL_SRC = \
	snek-main.c \
	snek-lcd.c \
	snek-clock.c \
	snek-daytime.c \
	snek-adc.c \
	$(SNEK_DRAW_SRC)

SNEK_LOCAL_BUILTINS = \
	snek-esp32.builtin \
	$(SNEK_ROOT)/snek-math.builtin \
	$(SNEK_ROOT)/snek-input.builtin \
	$(SNEK_DRAW_BUILTINS)

SNEK_LOCAL_CFLAGS = \
	$(SNEK_DRAW_CFLAGS)

SNEK_SRC=$(SNEK_LOCAL_SRC)

vpath %.c $(SNEK_LOCAL_VPATH):$(SNEK_ROOT)
vpath %.S $(SNEK_LOCAL_VPATH):$(SNEK_ROOT)
vpath %.h $(SNEK_LOCAL_VPATH):$(SNEK_ROOT)
vpath %.ll $(SNEK_LOCAL_VPATH):$(SNEK_ROOT)
vpath %.py $(SNEK_LOCAL_VPATH):$(SNEK_ROOT)
vpath %.builtin $(SNEK_LOCAL_VPATH):$(SNEK_ROOT)

CMakeLists.txt: $(SNEK_SRC)
	(echo "idf_component_register(SRCS"; \
	for i in $^; do echo '"'$$i'"'; done; \
	echo 'INCLUDE_DIRS ".." "." "../draw")') > $@

all: snek-gram.h snek-builtin.h CMakeLists.txt

clean::
	rm -f CMakeLists.txt
