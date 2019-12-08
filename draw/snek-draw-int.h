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

#ifndef _SNEK_DRAWINT_H_
#define _SNEK_DRAWINT_H_

#include "snek-draw.h"
#include <string.h>
#include <float.h>

/*
 * Post-transformed points are stored in 12.4 fixed point
 * values
 */

typedef int16_t	    snek_draw_sfixed_t;  /* 12.4 format */
typedef int32_t	    snek_draw_dfixed_t;  /* 24.8 format (12.4 * 12.4) */

#define snek_draw_sfixed_floor(f)	    ((f) & ~0xf)
#define snek_draw_sfixed_trunc(f)	    ((f) >> 4)
#define snek_draw_sfixed_ceil(f)	    (((f) + 0xf) & ~0xf)

#define snek_draw_int_to_sfixed(i)	    ((snek_draw_sfixed_t) ((i) * 16))

#define snek_draw_sfixed_to_float(s)	    ((float) (s) / 16)
#define snek_draw_float_to_sfixed(f)	    ((snek_draw_sfixed_t) ((f) * 16 + 1/2))

#define snek_draw_sfixed_to_dfixed(s)    (((snek_draw_dfixed_t) (s)) << 4)

#define SNEK_DRAW_SFIXED_ONE		(0x10)
#define SNEK_DRAW_SFIXED_HALF	(0x08)
#define SNEK_DRAW_SFIXED_TOLERANCE	(SNEK_DRAW_SFIXED_ONE)
#define SNEK_DRAW_SFIXED_MIN		(-0x7fff)
#define SNEK_DRAW_SFIXED_MAX		(0x7fff)

/*
 * Glyph coordinates are stored in 2.6 fixed point
 */

typedef signed char	snek_draw_gfixed_t;

#define SNEK_DRAW_GFIXED_ONE		(0x40)

/*
 * Compositing stuff
 */
#define snek_draw_int_mult(a,b,t)	((t) = (a) * (b) + 0x80, \
				 ((((t)>>8 ) + (t))>>8 ))
#define snek_draw_int_div(a,b)	(((uint16_t) (a) * 255) / (b))
#define snek_draw_get_8(v,i)		((uint16_t) (uint8_t) ((v) >> (i)))
#define snek_draw_sat(t)		((uint8_t) ((t) | (0 - ((t) >> 8))))

#define snek_draw_in(s,i,m,t)	\
    ((snek_draw_argb32_t) snek_draw_int_mult (snek_draw_get_8(s,i),(m),(t)) << (i))

#define snek_draw_over(s,d,i,m,t)	\
    (((t) = snek_draw_int_mult(snek_draw_get_8(d,i),(m),(t)) + snek_draw_get_8(s,i)),\
     (snek_draw_argb32_t) snek_draw_sat (t) << (i))

#define snek_draw_add(s,d,i,t) \
    (((t) = snek_draw_get_8(d,i) + snek_draw_get_8(s,i)),\
     (snek_draw_argb32_t) snek_draw_sat (t) << (i))

#define _snek_draw_argb32_to_rgb16(s)    ((((s) >> 3) & 0x001f) |	\
					 (((s) >> 5) & 0x07e0) |	\
					 (((s) >> 8) & 0xf800))
#define _snek_draw_rgb16_to_argb32(s)				\
	(((((s) << 3) & 0xf8) | (((s) >> 2) & 0x7)) |		\
	 ((((s) << 5) & 0xfc00) | (((s) >> 1) & 0x300)) |	\
	 ((((s) << 8) & 0xf80000) | (((s) << 3) & 0x70000)) |	\
	 0xff000000)
#if 0
#define snek_draw_argb32_to_rgb16(s) _snek_draw_argb32_to_rgb16(s)
#define snek_draw_rgb16_to_argb32(s) _snek_draw_rgb16_to_argb32(s)
#else

/* byte swap */
static inline snek_draw_rgb16_t
snek_draw_argb32_to_rgb16(snek_draw_argb32_t s)
{
	union {
		struct  {
			uint8_t l;
			uint8_t h;
		} s;
		snek_draw_rgb16_t rgb16;
	} d;
	d.rgb16 = _snek_draw_argb32_to_rgb16(s);
	uint8_t t = d.s.l;
	d.s.l = d.s.h;
	d.s.h = t;
	return d.rgb16;
}

static inline snek_draw_argb32_t
snek_draw_rgb16_to_argb32(snek_draw_rgb16_t rgb16) {
	union {
		struct  {
			uint8_t l;
			uint8_t h;
		} s;
		snek_draw_rgb16_t rgb16;
	} s;
	s.rgb16 = rgb16;
	uint8_t t = s.s.l;
	s.s.l = s.s.h;
	s.s.h = t;
	return _snek_draw_rgb16_to_argb32(s.rgb16);
}
#endif


typedef union {
    snek_draw_pointer_t  p;
    snek_draw_argb32_t   c;
} snek_draw_source_u;

typedef void (*snek_draw_src_msk_op) (snek_draw_pointer_t dst,
				 snek_draw_source_u	src,
				 snek_draw_source_u	msk,
				 int		width);

typedef void (*snek_draw_src_op) (snek_draw_pointer_t dst,
			     snek_draw_source_u  src,
			     int	    width);

/* snek_draw_primitive.c */

typedef void snek_draw_in_op_func (snek_draw_pointer_t	dst,
			      snek_draw_source_u	src,
			      snek_draw_source_u	msk,
			      int		width);

typedef void snek_draw_op_func (snek_draw_pointer_t	dst,
			   snek_draw_source_u	src,
			   int			width);

/* Geometrical objects */

typedef struct _snek_draw_spoint {
    snek_draw_sfixed_t    x, y;
} snek_draw_spoint_t;

struct _snek_draw_path {
    snek_draw_spoint_t   *points;
    int		    size_points;
    int		    npoints;
    int		    *sublen;
    int		    size_sublen;
    int		    nsublen;
    snek_draw_state_t    state;
};

typedef struct _snek_draw_gpoint { snek_draw_gfixed_t x, y; } snek_draw_gpoint_t;

/*
 * This needs to be refactored to reduce the number of functions...
 */
snek_draw_in_op_func _snek_draw_argb32_in_argb32_over_argb32;
snek_draw_in_op_func _snek_draw_argb32_in_rgb16_over_argb32;
snek_draw_in_op_func _snek_draw_argb32_in_a8_over_argb32;
snek_draw_in_op_func _snek_draw_argb32_in_c_over_argb32;
snek_draw_in_op_func _snek_draw_rgb16_in_argb32_over_argb32;
snek_draw_in_op_func _snek_draw_rgb16_in_rgb16_over_argb32;
snek_draw_in_op_func _snek_draw_rgb16_in_a8_over_argb32;
snek_draw_in_op_func _snek_draw_rgb16_in_c_over_argb32;
snek_draw_in_op_func _snek_draw_a8_in_argb32_over_argb32;
snek_draw_in_op_func _snek_draw_a8_in_rgb16_over_argb32;
snek_draw_in_op_func _snek_draw_a8_in_a8_over_argb32;
snek_draw_in_op_func _snek_draw_a8_in_c_over_argb32;
snek_draw_in_op_func _snek_draw_c_in_argb32_over_argb32;
snek_draw_in_op_func _snek_draw_c_in_rgb16_over_argb32;
snek_draw_in_op_func _snek_draw_c_in_a8_over_argb32;
snek_draw_in_op_func _snek_draw_c_in_c_over_argb32;
snek_draw_in_op_func _snek_draw_argb32_in_argb32_over_rgb16;
snek_draw_in_op_func _snek_draw_argb32_in_rgb16_over_rgb16;
snek_draw_in_op_func _snek_draw_argb32_in_a8_over_rgb16;
snek_draw_in_op_func _snek_draw_argb32_in_c_over_rgb16;
snek_draw_in_op_func _snek_draw_rgb16_in_argb32_over_rgb16;
snek_draw_in_op_func _snek_draw_rgb16_in_rgb16_over_rgb16;
snek_draw_in_op_func _snek_draw_rgb16_in_a8_over_rgb16;
snek_draw_in_op_func _snek_draw_rgb16_in_c_over_rgb16;
snek_draw_in_op_func _snek_draw_a8_in_argb32_over_rgb16;
snek_draw_in_op_func _snek_draw_a8_in_rgb16_over_rgb16;
snek_draw_in_op_func _snek_draw_a8_in_a8_over_rgb16;
snek_draw_in_op_func _snek_draw_a8_in_c_over_rgb16;
snek_draw_in_op_func _snek_draw_c_in_argb32_over_rgb16;
snek_draw_in_op_func _snek_draw_c_in_rgb16_over_rgb16;
snek_draw_in_op_func _snek_draw_c_in_a8_over_rgb16;
snek_draw_in_op_func _snek_draw_c_in_c_over_rgb16;
snek_draw_in_op_func _snek_draw_argb32_in_argb32_over_a8;
snek_draw_in_op_func _snek_draw_argb32_in_rgb16_over_a8;
snek_draw_in_op_func _snek_draw_argb32_in_a8_over_a8;
snek_draw_in_op_func _snek_draw_argb32_in_c_over_a8;
snek_draw_in_op_func _snek_draw_rgb16_in_argb32_over_a8;
snek_draw_in_op_func _snek_draw_rgb16_in_rgb16_over_a8;
snek_draw_in_op_func _snek_draw_rgb16_in_a8_over_a8;
snek_draw_in_op_func _snek_draw_rgb16_in_c_over_a8;
snek_draw_in_op_func _snek_draw_a8_in_argb32_over_a8;
snek_draw_in_op_func _snek_draw_a8_in_rgb16_over_a8;
snek_draw_in_op_func _snek_draw_a8_in_a8_over_a8;
snek_draw_in_op_func _snek_draw_a8_in_c_over_a8;
snek_draw_in_op_func _snek_draw_c_in_argb32_over_a8;
snek_draw_in_op_func _snek_draw_c_in_rgb16_over_a8;
snek_draw_in_op_func _snek_draw_c_in_a8_over_a8;
snek_draw_in_op_func _snek_draw_c_in_c_over_a8;
snek_draw_in_op_func _snek_draw_argb32_in_argb32_over_c;

snek_draw_in_op_func _snek_draw_argb32_in_argb32_source_argb32;
snek_draw_in_op_func _snek_draw_argb32_in_rgb16_source_argb32;
snek_draw_in_op_func _snek_draw_argb32_in_a8_source_argb32;
snek_draw_in_op_func _snek_draw_argb32_in_c_source_argb32;
snek_draw_in_op_func _snek_draw_rgb16_in_argb32_source_argb32;
snek_draw_in_op_func _snek_draw_rgb16_in_rgb16_source_argb32;
snek_draw_in_op_func _snek_draw_rgb16_in_a8_source_argb32;
snek_draw_in_op_func _snek_draw_rgb16_in_c_source_argb32;
snek_draw_in_op_func _snek_draw_a8_in_argb32_source_argb32;
snek_draw_in_op_func _snek_draw_a8_in_rgb16_source_argb32;
snek_draw_in_op_func _snek_draw_a8_in_a8_source_argb32;
snek_draw_in_op_func _snek_draw_a8_in_c_source_argb32;
snek_draw_in_op_func _snek_draw_c_in_argb32_source_argb32;
snek_draw_in_op_func _snek_draw_c_in_rgb16_source_argb32;
snek_draw_in_op_func _snek_draw_c_in_a8_source_argb32;
snek_draw_in_op_func _snek_draw_c_in_c_source_argb32;
snek_draw_in_op_func _snek_draw_argb32_in_argb32_source_rgb16;
snek_draw_in_op_func _snek_draw_argb32_in_rgb16_source_rgb16;
snek_draw_in_op_func _snek_draw_argb32_in_a8_source_rgb16;
snek_draw_in_op_func _snek_draw_argb32_in_c_source_rgb16;
snek_draw_in_op_func _snek_draw_rgb16_in_argb32_source_rgb16;
snek_draw_in_op_func _snek_draw_rgb16_in_rgb16_source_rgb16;
snek_draw_in_op_func _snek_draw_rgb16_in_a8_source_rgb16;
snek_draw_in_op_func _snek_draw_rgb16_in_c_source_rgb16;
snek_draw_in_op_func _snek_draw_a8_in_argb32_source_rgb16;
snek_draw_in_op_func _snek_draw_a8_in_rgb16_source_rgb16;
snek_draw_in_op_func _snek_draw_a8_in_a8_source_rgb16;
snek_draw_in_op_func _snek_draw_a8_in_c_source_rgb16;
snek_draw_in_op_func _snek_draw_c_in_argb32_source_rgb16;
snek_draw_in_op_func _snek_draw_c_in_rgb16_source_rgb16;
snek_draw_in_op_func _snek_draw_c_in_a8_source_rgb16;
snek_draw_in_op_func _snek_draw_c_in_c_source_rgb16;
snek_draw_in_op_func _snek_draw_argb32_in_argb32_source_a8;
snek_draw_in_op_func _snek_draw_argb32_in_rgb16_source_a8;
snek_draw_in_op_func _snek_draw_argb32_in_a8_source_a8;
snek_draw_in_op_func _snek_draw_argb32_in_c_source_a8;
snek_draw_in_op_func _snek_draw_rgb16_in_argb32_source_a8;
snek_draw_in_op_func _snek_draw_rgb16_in_rgb16_source_a8;
snek_draw_in_op_func _snek_draw_rgb16_in_a8_source_a8;
snek_draw_in_op_func _snek_draw_rgb16_in_c_source_a8;
snek_draw_in_op_func _snek_draw_a8_in_argb32_source_a8;
snek_draw_in_op_func _snek_draw_a8_in_rgb16_source_a8;
snek_draw_in_op_func _snek_draw_a8_in_a8_source_a8;
snek_draw_in_op_func _snek_draw_a8_in_c_source_a8;
snek_draw_in_op_func _snek_draw_c_in_argb32_source_a8;
snek_draw_in_op_func _snek_draw_c_in_rgb16_source_a8;
snek_draw_in_op_func _snek_draw_c_in_a8_source_a8;
snek_draw_in_op_func _snek_draw_c_in_c_source_a8;
snek_draw_in_op_func _snek_draw_argb32_in_argb32_source_c;

snek_draw_op_func _snek_draw_argb32_over_argb32;
snek_draw_op_func _snek_draw_rgb16_over_argb32;
snek_draw_op_func _snek_draw_a8_over_argb32;
snek_draw_op_func _snek_draw_c_over_argb32;
snek_draw_op_func _snek_draw_argb32_over_rgb16;
snek_draw_op_func _snek_draw_rgb16_over_rgb16;
snek_draw_op_func _snek_draw_a8_over_rgb16;
snek_draw_op_func _snek_draw_c_over_rgb16;
snek_draw_op_func _snek_draw_argb32_over_a8;
snek_draw_op_func _snek_draw_rgb16_over_a8;
snek_draw_op_func _snek_draw_a8_over_a8;
snek_draw_op_func _snek_draw_c_over_a8;
snek_draw_op_func _snek_draw_argb32_source_argb32;
snek_draw_op_func _snek_draw_rgb16_source_argb32;
snek_draw_op_func _snek_draw_a8_source_argb32;
snek_draw_op_func _snek_draw_c_source_argb32;
snek_draw_op_func _snek_draw_argb32_source_rgb16;
snek_draw_op_func _snek_draw_rgb16_source_rgb16;
snek_draw_op_func _snek_draw_a8_source_rgb16;
snek_draw_op_func _snek_draw_c_source_rgb16;
snek_draw_op_func _snek_draw_argb32_source_a8;
snek_draw_op_func _snek_draw_rgb16_source_a8;
snek_draw_op_func _snek_draw_a8_source_a8;
snek_draw_op_func _snek_draw_c_source_a8;

snek_draw_argb32_t *
_snek_draw_fetch_rgb16 (snek_draw_pixmap_t *pixmap, int x, int y, int w, snek_draw_argb32_t *span);

snek_draw_argb32_t *
_snek_draw_fetch_argb32 (snek_draw_pixmap_t *pixmap, int x, int y, int w, snek_draw_argb32_t *span);

/*
 * Geometry helper functions
 */

snek_draw_dfixed_t
_snek_draw_distance_to_point_squared (snek_draw_spoint_t *a, snek_draw_spoint_t *b);

snek_draw_dfixed_t
_snek_draw_distance_to_line_squared (snek_draw_spoint_t *p, snek_draw_spoint_t *p1, snek_draw_spoint_t *p2);


/*
 * Polygon stuff
 */

/*
 * Fixed point helper functions
 */
snek_draw_sfixed_t
_snek_draw_sfixed_sqrt (snek_draw_sfixed_t as);

/*
 * Matrix stuff
 */

snek_draw_sfixed_t
_snek_draw_matrix_x (snek_draw_matrix_t *m, float x, float y);

snek_draw_sfixed_t
_snek_draw_matrix_y (snek_draw_matrix_t *m, float x, float y);

snek_draw_sfixed_t
_snek_draw_matrix_dx (snek_draw_matrix_t *m, float dx, float dy);

snek_draw_sfixed_t
_snek_draw_matrix_dy (snek_draw_matrix_t *m, float dx, float dy);

float
_snek_draw_matrix_determinant (snek_draw_matrix_t *matrix);

snek_draw_sfixed_t
_snek_draw_matrix_len (snek_draw_matrix_t *m, float dx, float dy);

snek_draw_point_t
_snek_draw_matrix_expand (snek_draw_matrix_t *matrix);
/*
 * Path stuff
 */

/*
 * A path
 */

snek_draw_spoint_t
_snek_draw_path_current_spoint (snek_draw_path_t *path);

snek_draw_spoint_t
_snek_draw_path_subpath_first_spoint (snek_draw_path_t *path);

void
_snek_draw_path_smove (snek_draw_path_t *path, snek_draw_sfixed_t x, snek_draw_sfixed_t y);

void
_snek_draw_path_sdraw (snek_draw_path_t *path, snek_draw_sfixed_t x, snek_draw_sfixed_t y);

void
_snek_draw_path_scurve (snek_draw_path_t	    *path,
		   snek_draw_sfixed_t    x1, snek_draw_sfixed_t y1,
		   snek_draw_sfixed_t    x2, snek_draw_sfixed_t y2,
		   snek_draw_sfixed_t    x3, snek_draw_sfixed_t y3);

void
_snek_draw_path_sfinish (snek_draw_path_t *path);

/*
 * Glyph stuff.  Coordinates are stored in 2.6 fixed point format
 */

#define SNEK_DRAW_FONT_MAX	0x7f

extern const snek_draw_gpoint_t	_snek_draw_glyphs[];
extern const uint16_t		_snek_draw_glyph_offsets[];

#define SNEK_DRAW_GLYPH_MAX_POINTS	56

extern const signed char _snek_draw_gtable[];
extern const uint16_t _snek_draw_g_offsets[];

/*
 * Check these whenever glyphs are changed
 */
#define SNEK_DRAW_GLYPH_MAX_SNAP_X	4
#define SNEK_DRAW_GLYPH_MAX_SNAP_Y	7

#define snek_draw_glyph_left(g)	((g)[0])
#define snek_draw_glyph_right(g)	((g)[1])
#define snek_draw_glyph_ascent(g)	((g)[2])
#define snek_draw_glyph_descent(g)	((g)[3])
#define snek_draw_glyph_n_snap_x(g)	((g)[4])
#define snek_draw_glyph_n_snap_y(g)	((g)[5])
#define snek_draw_glyph_snap_x(g)	(&g[6])
#define snek_draw_glyph_snap_y(g)	(snek_draw_glyph_snap_x(g) + snek_draw_glyph_n_snap_x(g))
#define snek_draw_glyph_draw(g)	(snek_draw_glyph_snap_y(g) + snek_draw_glyph_n_snap_y(g))

#endif /* _SNEK_DRAWINT_H_ */
