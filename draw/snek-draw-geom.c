/*
 * SnekDraw - A Tiny Window System
 * Copyright © 2004 Keith Packard <keithp@keithp.com>
 * All rights reserved.
 *
 * This Library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Library General Public License as
 * published by the Free Software Foundation; either version 2 of the
 * License, or (at your option) any later version.
 *
 * This Library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Library General Public License for more details.
 *
 * You should have received a copy of the GNU Library General Public
 * License along with the SnekDraw Library; see the file COPYING.  If not,
 * write to the Free Software Foundation, Inc., 59 Temple Place - Suite 330,
 * Boston, MA 02111-1307, USA.
 */

#include "snek-draw-int.h"

snek_draw_dfixed_t
_snek_draw_distance_to_point_squared (snek_draw_spoint_t *a, snek_draw_spoint_t *b)
{
    snek_draw_dfixed_t dx = (b->x - a->x);
    snek_draw_dfixed_t dy = (b->y - a->y);

    return dx*dx + dy*dy;
}

snek_draw_dfixed_t
_snek_draw_distance_to_line_squared (snek_draw_spoint_t *p, snek_draw_spoint_t *p1, snek_draw_spoint_t *p2)
{
    /*
     * Convert to normal form (AX + BY + C = 0)
     *
     * (X - x1) * (y2 - y1) = (Y - y1) * (x2 - x1)
     *
     * X * (y2 - y1) - Y * (x2 - x1) - x1 * (y2 - y1) + y1 * (x2 - x1) = 0
     *
     * A = (y2 - y1)
     * B = (x1 - x2)
     * C = (y1x2 - x1y2)
     *
     * distance² = (AX + BC + C)² / (A² + B²)
     */
    snek_draw_dfixed_t   A = p2->y - p1->y;
    snek_draw_dfixed_t   B = p1->x - p2->x;
    snek_draw_dfixed_t   C = ((snek_draw_dfixed_t) p1->y * p2->x - 
			 (snek_draw_dfixed_t) p1->x * p2->y);
    snek_draw_dfixed_t   den, num;

    num = A * p->x + B * p->y + C;
    if (num < 0)
	num = -num;
    den = A * A + B * B;
    if (den == 0 || num >= 0x8000)
	return _snek_draw_distance_to_point_squared (p, p1);
    else
	return (num * num) / den;
}

