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

#ifndef _SNEK_DRAW_H_
#define _SNEK_DRAW_H_

#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <math.h>

#ifdef SNEK_DRAW_MALLOC_TRACE
#define malloc Malloc
#define free Free

void *Malloc(size_t size);
void Free(void *p);
#endif

typedef uint8_t	    snek_draw_a8_t;
typedef uint16_t    snek_draw_a16_t;
typedef uint16_t    snek_draw_rgb16_t;
typedef uint32_t    snek_draw_argb32_t;
typedef uint32_t    snek_draw_ucs4_t;
typedef int16_t	    snek_draw_coord_t;
typedef int16_t	    snek_draw_style_t;
typedef int16_t	    snek_draw_count_t;
typedef int16_t	    snek_draw_keysym_t;
typedef int32_t	    snek_draw_area_t;
typedef int32_t	    snek_draw_time_t;
typedef int16_t	    snek_draw_stretch_t;

typedef enum { SNEK_DRAW_A8, SNEK_DRAW_RGB16, SNEK_DRAW_ARGB32 } snek_draw_format_t;

#define snek_draw_bytes_per_pixel(format)    (1 << (snek_draw_coord_t) (format))

/*
 * Angles
 */
typedef int16_t	    snek_draw_angle_t;   /* -2048 .. 2048 for -180 .. 180 */

#define SNEK_DRAW_ANGLE_360	    4096
#define SNEK_DRAW_ANGLE_180	    (SNEK_DRAW_ANGLE_360 >> 1)
#define SNEK_DRAW_ANGLE_90	    (SNEK_DRAW_ANGLE_360 >> 2)
#define SNEK_DRAW_ANGLE_45	    (SNEK_DRAW_ANGLE_360 >> 3)
#define SNEK_DRAW_ANGLE_22_5	    (SNEK_DRAW_ANGLE_360 >> 4)
#define SNEK_DRAW_ANGLE_11_25       (SNEK_DRAW_ANGLE_360 >> 5)

#define SNEK_DRAW_ANGLE_270	    (SNEK_DRAW_ANGLE_180 + SNEK_DRAW_ANGLE_90)
#define SNEK_DRAW_ANGLE_0	    (0)

#define snek_draw_degrees_to_angle(d)    ((snek_draw_angle_t) ((((int32_t) (d)) * SNEK_DRAW_ANGLE_360 / 360)))

/*
 * A rectangle
 */
typedef struct _snek_draw_rect {
    snek_draw_coord_t    left, right, top, bottom;
} snek_draw_rect_t;

typedef union _snek_draw_pointer {
    void	    	*v;
    uint8_t	    	*b;
    snek_draw_a8_t	*a8;
    snek_draw_rgb16_t   *rgb16;
    snek_draw_argb32_t  *argb32;
} snek_draw_pointer_t;

typedef struct _snek_draw_window snek_draw_window_t;

typedef struct _snek_draw_slice {
	snek_draw_coord_t	top;
	snek_draw_pointer_t	p;
} snek_draw_slice_t;

/*
 * A rectangular array of pixels
 */
typedef struct _snek_draw_pixmap {
	/*
	 * Pixmap layout
	 */
	snek_draw_format_t		format;
	snek_draw_coord_t		width;	    /* pixels */
	snek_draw_coord_t		height;	    /* pixels */
	snek_draw_coord_t		stride;	    /* bytes */
	/*
	 * Pixels
	 */
	snek_draw_count_t		nslice;
	snek_draw_slice_t		*slices;
} snek_draw_pixmap_t;

/*
 * A source operand
 */

typedef enum { SNEK_DRAW_SOLID, SNEK_DRAW_PIXMAP } snek_draw_source_t;

typedef struct _snek_draw_operand {
    snek_draw_source_t	source_kind;
    union {
	snek_draw_pixmap_t	*pixmap;
	snek_draw_argb32_t	argb;
    }			u;
} snek_draw_operand_t;

typedef enum { SNEK_DRAW_OVER, SNEK_DRAW_SOURCE } snek_draw_operator_t;

#define SNEK_DRAW_FLOAT_ONE	(1.0f)
#define SNEK_DRAW_FLOAT_HALF	(0.5f)
#define SNEK_DRAW_FLOAT_MAX	(FLT_MAX)
#define SNEK_DRAW_FLOAT_MIN	(FLT_MIN)

typedef struct _snek_draw_point {
    float    x, y;
} snek_draw_point_t;

/*
 * Place matrices in structures so they can be easily copied
 */
typedef struct _snek_draw_matrix {
    float	m[3][2];
} snek_draw_matrix_t;

typedef struct _snek_draw_path snek_draw_path_t;

typedef enum _snek_draw_cap {
    SnekDrawCapRound,
    SnekDrawCapButt,
    SnekDrawCapProjecting,
} snek_draw_cap_t;

typedef struct _snek_draw_state {
    snek_draw_matrix_t   matrix;
    float    	    font_size;
    snek_draw_style_t    font_style;
    snek_draw_cap_t	    cap_style;
} snek_draw_state_t;

/*
 * Text metrics
 */

typedef struct _snek_draw_text_metrics {
    float    left_side_bearing;
    float    right_side_bearing;
    float    ascent;
    float    descent;
    float    width;
    float    font_ascent;
    float    font_descent;
} snek_draw_text_metrics_t;

/*
 * snek-draw-convolve.c
 */
void
snek_draw_path_convolve (snek_draw_path_t	*dest,
			 snek_draw_path_t	*stroke,
			 snek_draw_path_t	*pen);

/*
 * snek-draw-draw.c
 */

void
snek_draw_composite (snek_draw_pixmap_t		*dst,
		     snek_draw_coord_t		dst_x,
		     snek_draw_coord_t		dst_y,
		     snek_draw_operand_t	*src,
		     snek_draw_coord_t		src_x,
		     snek_draw_coord_t		src_y,
		     snek_draw_operand_t	*msk,
		     snek_draw_coord_t		msk_x,
		     snek_draw_coord_t		msk_y,
		     snek_draw_operator_t	operator,
		     snek_draw_coord_t		width,
		     snek_draw_coord_t		height);

void
snek_draw_fill (snek_draw_pixmap_t	*dst,
		snek_draw_argb32_t	pixel,
		snek_draw_operator_t	operator,
		snek_draw_coord_t	left,
		snek_draw_coord_t	top,
		snek_draw_coord_t	right,
		snek_draw_coord_t	bottom);

/*
 * snek-draw-font.c
 */

bool
snek_draw_has_ucs4 (snek_draw_ucs4_t ucs4);

#define SNEK_DRAW_TEXT_ROMAN	    	0
#define SNEK_DRAW_TEXT_BOLD	    	1
#define SNEK_DRAW_TEXT_OBLIQUE   	2
#define SNEK_DRAW_TEXT_UNHINTED  	4

void
snek_draw_path_ucs4_stroke (snek_draw_path_t *path, snek_draw_ucs4_t ucs4);

void
snek_draw_path_ucs4 (snek_draw_path_t *path, snek_draw_ucs4_t ucs4);

void
snek_draw_path_utf8 (snek_draw_path_t *path, const char *string);

float
snek_draw_width_ucs4 (snek_draw_path_t *path, snek_draw_ucs4_t ucs4);

float
snek_draw_width_utf8 (snek_draw_path_t *path, const char *string);

void
snek_draw_text_metrics_ucs4 (snek_draw_path_t		*path,
			     snek_draw_ucs4_t		ucs4,
			     snek_draw_text_metrics_t	*m);

void
snek_draw_text_metrics_utf8 (snek_draw_path_t		*path,
			     const char	    		*string,
			     snek_draw_text_metrics_t	*m);
/*
 * snek-draw-hull.c
 */

snek_draw_path_t *
snek_draw_path_convex_hull (snek_draw_path_t *path);

/*
 * snek-draw-matrix.c
 */

void
snek_draw_matrix_identity (snek_draw_matrix_t *m);

void
snek_draw_matrix_translate (snek_draw_matrix_t *m, float tx, float ty);

void
snek_draw_matrix_scale (snek_draw_matrix_t *m, float sx, float sy);

void
snek_draw_matrix_rotate (snek_draw_matrix_t *m, snek_draw_angle_t a);

void
snek_draw_matrix_multiply (snek_draw_matrix_t		*result,
			   const snek_draw_matrix_t	*a,
			   const snek_draw_matrix_t	*b);

/*
 * snek-draw-path.c
 */

void
snek_draw_path_move (snek_draw_path_t *path, float x, float y);

void
snek_draw_path_rmove (snek_draw_path_t *path, float x, float y);

void
snek_draw_path_draw (snek_draw_path_t *path, float x, float y);

void
snek_draw_path_rdraw (snek_draw_path_t *path, float x, float y);

void
snek_draw_path_circle(snek_draw_path_t	*path,
		      float		x,
		      float		y,
		      float		radius);

void
snek_draw_path_ellipse (snek_draw_path_t	*path,
			float			x,
			float			y,
			float 			x_radius,
			float			y_radius);

void
snek_draw_path_arc (snek_draw_path_t 	*path,
		    float	    	x,
		    float	    	y,
		    float	    	x_radius,
		    float	    	y_radius,
		    snek_draw_angle_t	start,
		    snek_draw_angle_t	extent);

void
snek_draw_path_rectangle (snek_draw_path_t	*path,
			  float	    		x,
			  float	    		y,
			  float	    		w,
			  float	    		h);

void
snek_draw_path_rounded_rectangle (snek_draw_path_t	*path,
				  float	    		x,
				  float	   		y,
				  float			w,
				  float			h,
				  float			x_radius,
				  float			y_radius);

void
snek_draw_path_lozenge (snek_draw_path_t	*path,
			float			x,
			float			y,
			float			w,
			float			h);

void
snek_draw_path_tab (snek_draw_path_t	*path,
		    float		x,
		    float		y,
		    float		w,
		    float		h,
		    float		x_radius,
		    float		y_radius);


void
snek_draw_path_close (snek_draw_path_t *path);

void
snek_draw_path_empty (snek_draw_path_t *path);

void
snek_draw_path_bounds (snek_draw_path_t *path, snek_draw_rect_t *rect);

void
snek_draw_path_append (snek_draw_path_t *dst, snek_draw_path_t *src);

snek_draw_path_t *
snek_draw_path_create (void);

void
snek_draw_path_destroy (snek_draw_path_t *path);

void
snek_draw_path_identity (snek_draw_path_t *path);

void
snek_draw_path_translate (snek_draw_path_t *path, float tx, float ty);

void
snek_draw_path_scale (snek_draw_path_t *path, float sx, float sy);

void
snek_draw_path_rotate (snek_draw_path_t *path, snek_draw_angle_t a);

snek_draw_matrix_t
snek_draw_path_current_matrix (snek_draw_path_t *path);

void
snek_draw_path_set_matrix (snek_draw_path_t *path, snek_draw_matrix_t matrix);

float
snek_draw_path_current_font_size (snek_draw_path_t *path);

void
snek_draw_path_set_font_size (snek_draw_path_t *path, float font_size);

snek_draw_style_t
snek_draw_path_current_font_style (snek_draw_path_t *path);

void
snek_draw_path_set_font_style (snek_draw_path_t *path, snek_draw_style_t font_style);

void
snek_draw_path_set_cap_style (snek_draw_path_t *path, snek_draw_cap_t cap_style);

snek_draw_cap_t
snek_draw_path_current_cap_style (snek_draw_path_t *path);

snek_draw_state_t
snek_draw_path_save (snek_draw_path_t *path);

void
snek_draw_path_restore (snek_draw_path_t *path, snek_draw_state_t *state);

void
snek_draw_composite_path (snek_draw_pixmap_t	*dst,
			  snek_draw_operand_t	*src,
			  snek_draw_coord_t	src_x,
			  snek_draw_coord_t	src_y,
			  snek_draw_path_t	*path,
			  snek_draw_operator_t	operator);
void
snek_draw_paint_path (snek_draw_pixmap_t	*dst,
		      snek_draw_argb32_t	argb,
		      snek_draw_path_t		*path);

void
snek_draw_composite_stroke (snek_draw_pixmap_t		*dst,
			    snek_draw_operand_t		*src,
			    snek_draw_coord_t		src_x,
			    snek_draw_coord_t		src_y,
			    snek_draw_path_t		*stroke,
			    float			pen_width,
			    snek_draw_operator_t	operator);

void
snek_draw_paint_stroke (snek_draw_pixmap_t	*dst,
			snek_draw_argb32_t	argb,
			snek_draw_path_t	*stroke,
			float			pen_width);

/*
 * snek-draw-pattern.c
 */
snek_draw_pixmap_t *
snek_draw_make_pattern (void);

/*
 * snek-draw-pixmap.c
 */

snek_draw_pixmap_t *
snek_draw_pixmap_create (snek_draw_format_t   format,
			 snek_draw_coord_t    width,
			 snek_draw_coord_t    height);

snek_draw_pixmap_t *
snek_draw_pixmap_create_const (snek_draw_format_t	format,
			       snek_draw_coord_t	width,
			       snek_draw_coord_t	height,
			       snek_draw_coord_t	stride,
			       snek_draw_pointer_t	pixels);

void
snek_draw_pixmap_destroy (snek_draw_pixmap_t *pixmap);

void
snek_draw_pixmap_damage (snek_draw_pixmap_t   *pixmap,
			 snek_draw_coord_t    left,	snek_draw_coord_t top,
			 snek_draw_coord_t    right,	snek_draw_coord_t bottom);

snek_draw_pointer_t
snek_draw_pixmap_pointer (snek_draw_pixmap_t *pixmap, snek_draw_coord_t x, snek_draw_coord_t y);

void
snek_draw_pixmap_lock (snek_draw_pixmap_t *pixmap);

void
snek_draw_pixmap_unlock (snek_draw_pixmap_t *pixmap);

bool
snek_draw_pixmap_transparent (snek_draw_pixmap_t *pixmap, snek_draw_coord_t x, snek_draw_coord_t y);

/*
 * snek-draw-poly.c
 */
void
snek_draw_fill_path (snek_draw_pixmap_t *pixmap, snek_draw_path_t *path,
		     snek_draw_coord_t dx, snek_draw_coord_t dy);

/*
 * snek-draw-spline.c
 */

void
snek_draw_path_curve (snek_draw_path_t	*path,
		      float x1, float y1,
		      float x2, float y2,
		      float x3, float y3);

/*
 * snek-draw-trig.c
 */

float
snek_draw_sin (snek_draw_angle_t a);

float
snek_draw_cos (snek_draw_angle_t a);

float
snek_draw_tan (snek_draw_angle_t a);

#endif /* _SNEK_DRAW_H_ */
