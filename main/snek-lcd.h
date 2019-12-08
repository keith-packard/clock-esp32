/*
 * Copyright © 2019 Keith Packard <keithp@keithp.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program; if not, write to the Free Software Foundation, Inc.,
 * 51 Franklin St, Fifth Floor, Boston, MA 02110-1301, USA.
 */

#pragma once
#include <string.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include "snek-draw.h"

void
snek_draw_lcd_init(void);

void
snek_draw_lcd(void);

extern snek_draw_pixmap_t snek_lcd_pixmap;

void
snek_lcd_set_backlight(uint16_t backlight);
