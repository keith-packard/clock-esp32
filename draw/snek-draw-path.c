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

static int
_snek_draw_current_subpath_len (snek_draw_path_t *path)
{
    int	start;

    if (path->nsublen)
	start = path->sublen[path->nsublen-1];
    else
	start = 0;
    return path->npoints - start;
}

snek_draw_spoint_t
_snek_draw_path_current_spoint (snek_draw_path_t *path)
{
    if (!path->npoints)
	snek_draw_path_move (path, 0, 0);
    return path->points[path->npoints - 1];
}

snek_draw_spoint_t
_snek_draw_path_subpath_first_spoint (snek_draw_path_t *path)
{
    int	start;

    if (!path->npoints)
	snek_draw_path_move (path, 0, 0);

    if (path->nsublen)
	start = path->sublen[path->nsublen-1];
    else
	start = 0;

    return path->points[start];
}

void
_snek_draw_path_sfinish (snek_draw_path_t *path)
{
    switch (_snek_draw_current_subpath_len(path)) {
    case 1:
	path->npoints--;
    case 0:
	return;
    }

    if (path->nsublen == path->size_sublen)
    {
	int	size_sublen;
	int	*sublen;

	if (path->size_sublen > 0)
	    size_sublen = path->size_sublen * 2;
	else
	    size_sublen = 1;
	if (path->sublen)
	    sublen = realloc (path->sublen, size_sublen * sizeof (int));
	else
	    sublen = malloc (size_sublen * sizeof (int));
	if (!sublen)
	    return;
	path->sublen = sublen;
	path->size_sublen = size_sublen;
    }
    path->sublen[path->nsublen] = path->npoints;
    path->nsublen++;
}

void
_snek_draw_path_smove (snek_draw_path_t *path, snek_draw_sfixed_t x, snek_draw_sfixed_t y)
{
    switch (_snek_draw_current_subpath_len (path)) {
    default:
	_snek_draw_path_sfinish (path);
	/* fall through */
    case 0:
	_snek_draw_path_sdraw (path, x, y);
	break;
    case 1:
	path->points[path->npoints-1].x = x;
	path->points[path->npoints-1].y = y;
	break;
    }
}

void
_snek_draw_path_sdraw (snek_draw_path_t *path, snek_draw_sfixed_t x, snek_draw_sfixed_t y)
{
    if (_snek_draw_current_subpath_len(path) > 0 &&
	path->points[path->npoints-1].x == x &&
	path->points[path->npoints-1].y == y)
	return;
    if (path->npoints == path->size_points)
    {
	int		size_points;
	snek_draw_spoint_t	*points;

	if (path->size_points > 0)
	    size_points = path->size_points * 2;
	else
	    size_points = 16;
	if (path->points)
	    points = realloc (path->points, size_points * sizeof (snek_draw_spoint_t));
	else
	    points = malloc (size_points * sizeof (snek_draw_spoint_t));
	if (!points)
	    return;
	path->points = points;
	path->size_points = size_points;
    }
    path->points[path->npoints].x = x;
    path->points[path->npoints].y = y;
    path->npoints++;
}

void
snek_draw_path_move (snek_draw_path_t *path, float x, float y)
{
    _snek_draw_path_smove (path,
		      _snek_draw_matrix_x (&path->state.matrix, x, y),
		      _snek_draw_matrix_y (&path->state.matrix, x, y));
}

void
snek_draw_path_rmove (snek_draw_path_t *path, float dx, float dy)
{
    snek_draw_spoint_t   here = _snek_draw_path_current_spoint (path);
    _snek_draw_path_smove (path,
		      here.x +
		      _snek_draw_matrix_dx (&path->state.matrix, dx, dy),
		      here.y +
		      _snek_draw_matrix_dy (&path->state.matrix, dx, dy));
}

void
snek_draw_path_draw (snek_draw_path_t *path, float x, float y)
{
    _snek_draw_path_sdraw (path,
		      _snek_draw_matrix_x (&path->state.matrix, x, y),
		      _snek_draw_matrix_y (&path->state.matrix, x, y));
}

void
snek_draw_path_rdraw (snek_draw_path_t *path, float dx, float dy)
{
    snek_draw_spoint_t   here = _snek_draw_path_current_spoint (path);
    _snek_draw_path_sdraw (path,
		      here.x +
		      _snek_draw_matrix_dx (&path->state.matrix, dx, dy),
		      here.y +
		      _snek_draw_matrix_dy (&path->state.matrix, dx, dy));
}

void
snek_draw_path_close (snek_draw_path_t *path)
{
    snek_draw_spoint_t   f;

    switch (_snek_draw_current_subpath_len(path)) {
    case 0:
    case 1:
	break;
    default:
	f = _snek_draw_path_subpath_first_spoint (path);
	_snek_draw_path_sdraw (path, f.x, f.y);
	break;
    }
}

void
snek_draw_path_circle (snek_draw_path_t	*path,
		  float		x,
		  float		y,
		  float		radius)
{
    snek_draw_path_ellipse (path, x, y, radius, radius);
}

void
snek_draw_path_ellipse (snek_draw_path_t *path,
		   float 	x,
		   float	y,
		   float 	x_radius,
		   float	y_radius)
{
    snek_draw_path_move (path, x + x_radius, y);
    snek_draw_path_arc (path, x, y, x_radius, y_radius, 0, SNEK_DRAW_ANGLE_360);
    snek_draw_path_close (path);
}

#define snek_draw_fixed_abs(f)   ((f) < 0 ? -(f) : (f))

static float
_snek_draw_matrix_max_radius (snek_draw_matrix_t *m)
{
    return (snek_draw_fixed_abs (m->m[0][0]) + snek_draw_fixed_abs (m->m[0][1]) +
	    snek_draw_fixed_abs (m->m[1][0]) + snek_draw_fixed_abs (m->m[1][1]));
}

void
snek_draw_path_arc (snek_draw_path_t  *path,
	       float 	    x,
	       float 	    y,
	       float 	    x_radius,
	       float 	    y_radius,
	       snek_draw_angle_t start,
	       snek_draw_angle_t extent)
{
    snek_draw_matrix_t   save = snek_draw_path_current_matrix (path);
    float    max_radius;
    int32_t    	    sides;
    int32_t    	    n;
    snek_draw_angle_t    a;
    snek_draw_angle_t    first, last, step, inc;
    snek_draw_angle_t    epsilon;

    snek_draw_path_translate (path, x, y);
    snek_draw_path_scale (path, x_radius, y_radius);

    max_radius = _snek_draw_matrix_max_radius (&path->state.matrix);
    sides = max_radius / snek_draw_sfixed_to_float (SNEK_DRAW_SFIXED_TOLERANCE);
    if (sides > 1024) sides = 1024;

    n = 2;
    while ((1 << n) < sides)
	n++;

    sides = (1 << n);

    step = SNEK_DRAW_ANGLE_360 >> n;
    inc = step;
    epsilon = 1;
    if (extent < 0)
    {
	inc = -inc;
	epsilon = -1;
    }

    first = (start + inc - epsilon) & ~(step - 1);
    last = (start + extent - inc + epsilon) & ~(step - 1);

    if (first != start)
	snek_draw_path_draw (path, snek_draw_cos(start), snek_draw_sin(start));

    for (a = first; a != last; a += inc)
	snek_draw_path_draw (path, snek_draw_cos (a), snek_draw_sin (a));

    if (last != start + extent)
	snek_draw_path_draw (path, snek_draw_cos (start+extent), snek_draw_sin(start+extent));

    snek_draw_path_set_matrix (path, save);
}

void
snek_draw_path_rectangle (snek_draw_path_t    *path,
		     float   	    x,
		     float   y,
		     float   w,
		     float   h)
{
    snek_draw_path_move (path, x, y);
    snek_draw_path_draw (path, x+w, y);
    snek_draw_path_draw (path, x+w, y+h);
    snek_draw_path_draw (path, x, y+h);
    snek_draw_path_close (path);
}

void
snek_draw_path_rounded_rectangle (snek_draw_path_t	*path,
			     float		x,
			     float		y,
			     float		w,
			     float		h,
			     float		x_radius,
			     float		y_radius)
{
    snek_draw_matrix_t   save = snek_draw_path_current_matrix (path);

    snek_draw_path_translate (path, x, y);
    snek_draw_path_move  (path,
		     0, y_radius);
    snek_draw_path_arc (path, x_radius, y_radius, x_radius, y_radius,
		   SNEK_DRAW_ANGLE_180, SNEK_DRAW_ANGLE_90);
    snek_draw_path_draw  (path,
		     w - x_radius, 0);
    snek_draw_path_arc (path, w - x_radius, y_radius, x_radius, y_radius,
		   SNEK_DRAW_ANGLE_270, SNEK_DRAW_ANGLE_90);
    snek_draw_path_draw  (path,
		     w, h - y_radius);
    snek_draw_path_arc (path, w - x_radius, h - y_radius, x_radius, y_radius,
		   SNEK_DRAW_ANGLE_0, SNEK_DRAW_ANGLE_90);
    snek_draw_path_draw  (path,
		     x_radius, h);
    snek_draw_path_arc (path, x_radius, h - y_radius, x_radius, y_radius,
		   SNEK_DRAW_ANGLE_90, SNEK_DRAW_ANGLE_90);
    snek_draw_path_close (path);
    snek_draw_path_set_matrix (path, save);
}

void
snek_draw_path_lozenge (snek_draw_path_t	*path,
		   float	x,
		   float	y,
		   float	w,
		   float	h)
{
    float    radius;

    if (w > h)
	radius = h / 2;
    else
	radius = w / 2;
    snek_draw_path_rounded_rectangle (path, x, y, w, h, radius, radius);
}

void
snek_draw_path_tab (snek_draw_path_t	*path,
	       float		x,
	       float		y,
	       float		w,
	       float		h,
	       float		x_radius,
	       float		y_radius)
{
    snek_draw_matrix_t   save = snek_draw_path_current_matrix (path);

    snek_draw_path_translate (path, x, y);
    snek_draw_path_move  (path,
		     0, y_radius);
    snek_draw_path_arc (path, x_radius, y_radius, x_radius, y_radius,
		   SNEK_DRAW_ANGLE_180, SNEK_DRAW_ANGLE_90);
    snek_draw_path_draw  (path,
		     w - x_radius, 0);
    snek_draw_path_arc (path, w - x_radius, y_radius, x_radius, y_radius,
		   SNEK_DRAW_ANGLE_270, SNEK_DRAW_ANGLE_90);
    snek_draw_path_draw  (path,
		     w, h);
    snek_draw_path_draw  (path,
		     0, h);
    snek_draw_path_close (path);
    snek_draw_path_set_matrix (path, save);
}

void
snek_draw_path_set_matrix (snek_draw_path_t *path, snek_draw_matrix_t matrix)
{
    path->state.matrix = matrix;
}

snek_draw_matrix_t
snek_draw_path_current_matrix (snek_draw_path_t *path)
{
    return path->state.matrix;
}

void
snek_draw_path_identity (snek_draw_path_t *path)
{
    snek_draw_matrix_identity (&path->state.matrix);
}

void
snek_draw_path_translate (snek_draw_path_t *path, float tx, float ty)
{
    snek_draw_matrix_translate (&path->state.matrix, tx, ty);
}

void
snek_draw_path_scale (snek_draw_path_t *path, float sx, float sy)
{
    snek_draw_matrix_scale (&path->state.matrix, sx, sy);
}

void
snek_draw_path_rotate (snek_draw_path_t *path, snek_draw_angle_t a)
{
    snek_draw_matrix_rotate (&path->state.matrix, a);
}

void
snek_draw_path_set_font_size (snek_draw_path_t *path, float font_size)
{
    path->state.font_size = font_size;
}

float
snek_draw_path_current_font_size (snek_draw_path_t *path)
{
    return path->state.font_size;
}

void
snek_draw_path_set_font_style (snek_draw_path_t *path, snek_draw_style_t font_style)
{
    path->state.font_style = font_style;
}

snek_draw_style_t
snek_draw_path_current_font_style (snek_draw_path_t *path)
{
    return path->state.font_style;
}

void
snek_draw_path_set_cap_style (snek_draw_path_t *path, snek_draw_cap_t cap_style)
{
    path->state.cap_style = cap_style;
}

snek_draw_cap_t
snek_draw_path_current_cap_style (snek_draw_path_t *path)
{
    return path->state.cap_style;
}

void
snek_draw_path_empty (snek_draw_path_t *path)
{
    path->npoints = 0;
    path->nsublen = 0;
}

void
snek_draw_path_bounds (snek_draw_path_t *path, snek_draw_rect_t *rect)
{
    snek_draw_sfixed_t   left = SNEK_DRAW_SFIXED_MAX;
    snek_draw_sfixed_t   top = SNEK_DRAW_SFIXED_MAX;
    snek_draw_sfixed_t   right = SNEK_DRAW_SFIXED_MIN;
    snek_draw_sfixed_t   bottom = SNEK_DRAW_SFIXED_MIN;
    int		    i;

    for (i = 0; i < path->npoints; i++)
    {
	snek_draw_sfixed_t	x = path->points[i].x;
	snek_draw_sfixed_t	y = path->points[i].y;
	if (x < left) left = x;
	if (x > right) right = x;
	if (y < top) top = y;
	if (y > bottom) bottom = y;
    }
    if (left >= right || top >= bottom)
	left = right = top = bottom = 0;
    rect->left = snek_draw_sfixed_trunc (left);
    rect->top = snek_draw_sfixed_trunc (top);
    rect->right = snek_draw_sfixed_trunc (snek_draw_sfixed_ceil (right));
    rect->bottom = snek_draw_sfixed_trunc (snek_draw_sfixed_ceil (bottom));
}

void
snek_draw_path_append (snek_draw_path_t *dst, snek_draw_path_t *src)
{
    int	    p;
    int	    s = 0;

    for (p = 0; p < src->npoints; p++)
    {
	if (s < src->nsublen && p == src->sublen[s])
	{
	    _snek_draw_path_sfinish (dst);
	    s++;
	}
	_snek_draw_path_sdraw (dst, src->points[p].x, src->points[p].y);
    }
}

snek_draw_state_t
snek_draw_path_save (snek_draw_path_t *path)
{
    return path->state;
}

void
snek_draw_path_restore (snek_draw_path_t *path, snek_draw_state_t *state)
{
    path->state = *state;
}

snek_draw_path_t *
snek_draw_path_create (void)
{
    snek_draw_path_t	*path;

    path = malloc (sizeof (snek_draw_path_t));
    if (!path)
	    return NULL;
    path->npoints = path->size_points = 0;
    path->nsublen = path->size_sublen = 0;
    path->points = 0;
    path->sublen = 0;
    snek_draw_matrix_identity (&path->state.matrix);
    path->state.font_size = SNEK_DRAW_FLOAT_ONE * 15;
    path->state.font_style = SNEK_DRAW_TEXT_ROMAN;
    path->state.cap_style = SnekDrawCapRound;
    return path;
}

void
snek_draw_path_destroy (snek_draw_path_t *path)
{
    if (path->points)
	free (path->points);
    if (path->sublen)
	free (path->sublen);
    free (path);
}

void
snek_draw_composite_path (snek_draw_pixmap_t	*dst,
		     snek_draw_operand_t	*src,
		     snek_draw_coord_t	src_x,
		     snek_draw_coord_t	src_y,
		     snek_draw_path_t	*path,
		     snek_draw_operator_t	operator)
{
    snek_draw_rect_t	    bounds;
    snek_draw_pixmap_t   *mask;
    snek_draw_operand_t  msk;
    snek_draw_coord_t    width, height;

    snek_draw_path_bounds (path, &bounds);
    if (bounds.left >= bounds.right || bounds.top >= bounds.bottom)
	return;
    width = bounds.right - bounds.left;
    height = bounds.bottom - bounds.top;
    mask = snek_draw_pixmap_create (SNEK_DRAW_A8, width, height);

    if (!mask)
	return;
    snek_draw_fill_path (mask, path, -bounds.left, -bounds.top);
    msk.source_kind = SNEK_DRAW_PIXMAP;
    msk.u.pixmap = mask;
    snek_draw_composite (dst, bounds.left, bounds.top,
		    src, src_x + bounds.left, src_y + bounds.top,
		    &msk, 0, 0, operator, width, height);
    snek_draw_pixmap_destroy (mask);
}

void
snek_draw_paint_path (snek_draw_pixmap_t	*dst,
		 snek_draw_argb32_t	argb,
		 snek_draw_path_t	*path)
{
    snek_draw_operand_t  src;

    src.source_kind = SNEK_DRAW_SOLID;
    src.u.argb = argb;
    snek_draw_composite_path (dst, &src, 0, 0, path, SNEK_DRAW_OVER);
}

void
snek_draw_composite_stroke (snek_draw_pixmap_t	*dst,
		       snek_draw_operand_t	*src,
		       snek_draw_coord_t	src_x,
		       snek_draw_coord_t	src_y,
		       snek_draw_path_t	*stroke,
		       float		pen_width,
		       snek_draw_operator_t	operator)
{
    snek_draw_path_t	    *pen = snek_draw_path_create ();
    snek_draw_path_t	    *path = snek_draw_path_create ();
    snek_draw_matrix_t   m = snek_draw_path_current_matrix (stroke);

    m.m[2][0] = 0;
    m.m[2][1] = 0;
    snek_draw_path_set_matrix (pen, m);
    snek_draw_path_set_cap_style (path, snek_draw_path_current_cap_style (stroke));
    snek_draw_path_circle (pen, 0, 0, pen_width / 2);
    snek_draw_path_convolve (path, stroke, pen);
    snek_draw_composite_path (dst, src, src_x, src_y, path, operator);
    snek_draw_path_destroy (path);
    snek_draw_path_destroy (pen);
}

void
snek_draw_paint_stroke (snek_draw_pixmap_t    *dst,
		   snek_draw_argb32_t    argb,
		   snek_draw_path_t	    *stroke,
		   float	    pen_width)
{
    snek_draw_operand_t  src;

    src.source_kind = SNEK_DRAW_SOLID;
    src.u.argb = argb;
    snek_draw_composite_stroke (dst, &src, 0, 0, stroke, pen_width, SNEK_DRAW_OVER);
}
