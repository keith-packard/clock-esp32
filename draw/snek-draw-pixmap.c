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

#include "snek-draw-int.h"

snek_draw_pixmap_t *
snek_draw_pixmap_create (snek_draw_format_t   format,
			 snek_draw_coord_t    width,
			 snek_draw_coord_t    height)
{
	snek_draw_coord_t	stride = snek_draw_bytes_per_pixel (format) * width;
	snek_draw_area_t	space = (snek_draw_area_t) stride * height;
	snek_draw_area_t	size = sizeof (snek_draw_pixmap_t) + sizeof (snek_draw_slice_t) + space;

	snek_draw_pixmap_t	*pixmap = malloc (size);

	if (!pixmap)
		return 0;
	pixmap->format = format;
	pixmap->width = width;
	pixmap->height = height;
	pixmap->stride = stride;
	pixmap->nslice = 1;
	pixmap->slices = (void *) (pixmap + 1);
	pixmap->slices[0].top = 0;
	pixmap->slices[0].p.v = (void *) (pixmap->slices + 1);
	memset (pixmap->slices[0].p.v, '\0', space);
	return pixmap;
}

snek_draw_pixmap_t *
snek_draw_pixmap_create_const (snek_draw_format_t	format,
			       snek_draw_coord_t	width,
			       snek_draw_coord_t	height,
			       snek_draw_coord_t	stride,
			       snek_draw_pointer_t	pixels)
{
	snek_draw_pixmap_t   *pixmap = malloc (sizeof (snek_draw_pixmap_t) + sizeof (snek_draw_slice_t));

	if (!pixmap)
		return 0;
	pixmap->format = format;
	pixmap->width = width;
	pixmap->height = height;
	pixmap->stride = stride;
	pixmap->nslice = 1;
	pixmap->slices = (void *) (pixmap + 1);
	pixmap->slices[0].top = 0;
	pixmap->slices[0].p.v = pixels.v;
	return pixmap;
}

void
snek_draw_pixmap_destroy (snek_draw_pixmap_t *pixmap)
{
	free (pixmap);
}

void
snek_draw_pixmap_damage (snek_draw_pixmap_t   *pixmap,
			 snek_draw_coord_t    left,	snek_draw_coord_t top,
			 snek_draw_coord_t    right,	snek_draw_coord_t bottom)
{
	(void) pixmap;
	(void) left;
	(void) right;
	(void) top;
	(void) bottom;
}

snek_draw_pointer_t
snek_draw_pixmap_pointer (snek_draw_pixmap_t *pixmap, snek_draw_coord_t x, snek_draw_coord_t y)
{
	snek_draw_pointer_t  	p;
	snek_draw_count_t	s;
	snek_draw_slice_t	*slice = pixmap->slices;

	for (s = 0; s < pixmap->nslice - 1; s++) {
		if (y < slice[1].top)
			break;
		slice++;
	}
	p.b = (slice->p.b +
	       (y - slice->top) * pixmap->stride +
	       x * snek_draw_bytes_per_pixel(pixmap->format));
	return p;
}

static snek_draw_argb32_t
_snek_draw_pixmap_fetch (snek_draw_pixmap_t *pixmap, snek_draw_coord_t x, snek_draw_coord_t y)
{
	snek_draw_pointer_t  p = snek_draw_pixmap_pointer (pixmap, x, y);

	if (0 <= x && x < pixmap->width &&
	    0 <= y && y < pixmap->height)
	{
		switch (pixmap->format) {
		case SNEK_DRAW_A8:
			return *p.a8 << 24;
		case SNEK_DRAW_RGB16:
			return snek_draw_rgb16_to_argb32 (*p.rgb16);
		case SNEK_DRAW_ARGB32:
			return *p.argb32;
		}
	}
	return 0;
}

bool
snek_draw_pixmap_transparent (snek_draw_pixmap_t *pixmap, snek_draw_coord_t x, snek_draw_coord_t y)
{
	return (_snek_draw_pixmap_fetch (pixmap, x, y) >> 24) == 0;
}
