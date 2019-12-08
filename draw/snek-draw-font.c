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

#if 0
#include <stdio.h>
#define F(x) floato_double(x)
#define S(x) snek_draw_sfixed_to_float(x)
#define G(x) ((double) (x))
#define DBGMSG(x)	printf x
#else
#define DBGMSG(x)
#endif

#define SNAPI(p)	ceilf(p)
#define SNAPH(p)	(ceilf((p)*2) / 2)
#define FX(g,i)		((g) * (i)->scale.x / 64)
#define FY(g,i)		((g) * (i)->scale.y / 64)

typedef struct _snek_draw_text_info {
    snek_draw_point_t    scale;
    snek_draw_point_t    pen;
    snek_draw_point_t    margin;
    snek_draw_point_t    reverse_scale;
    bool	    snap;
    snek_draw_matrix_t   matrix;
    snek_draw_matrix_t   pen_matrix;
    int		    n_snap_x;
    float    	    snap_x[SNEK_DRAW_GLYPH_MAX_SNAP_X];
    int		    n_snap_y;
    float    	    snap_y[SNEK_DRAW_GLYPH_MAX_SNAP_Y];
} snek_draw_text_info_t;

static void
_snek_draw_text_compute_info (snek_draw_path_t *path, snek_draw_text_info_t *info)
{
    snek_draw_spoint_t   origin = _snek_draw_path_current_spoint (path);

    /*
     * Only hint axis aligned text
     */
    if ((path->state.font_style & SNEK_DRAW_TEXT_UNHINTED) == 0 &&
	((path->state.matrix.m[0][1] == 0 &&
	  path->state.matrix.m[1][0] == 0) ||
	 (path->state.matrix.m[0][0] == 0 &&
	  path->state.matrix.m[1][1] == 0)))
    {
	int	xi, yi;

	if (path->state.matrix.m[0][0] != 0)
	    xi = 0;
	else
	    xi = 1;
	yi = 1-xi;
	info->snap = true;
	info->matrix.m[xi][0] = SNEK_DRAW_FLOAT_ONE;
	info->matrix.m[xi][1] = 0;
	info->matrix.m[yi][0] = 0;
	info->matrix.m[yi][1] = SNEK_DRAW_FLOAT_ONE;
	info->matrix.m[2][0] = SNAPI(snek_draw_sfixed_to_float (origin.x));
	info->matrix.m[2][1] = SNAPI(snek_draw_sfixed_to_float (origin.y));
	info->scale.x = path->state.font_size * path->state.matrix.m[0][xi];
	info->reverse_scale.x = 1.0f / path->state.matrix.m[0][xi];
	if (info->scale.x < 0)
	{
	    info->scale.x = -info->scale.x;
	    info->reverse_scale.x = -info->reverse_scale.x;
	    info->matrix.m[0][xi] = -info->matrix.m[0][xi];
	    info->matrix.m[1][xi] = -info->matrix.m[1][xi];
	}
	info->scale.y = path->state.font_size * path->state.matrix.m[1][yi];
	info->reverse_scale.y = 1.0f / path->state.matrix.m[1][yi];
	if (info->scale.y < 0)
	{
	    info->scale.y = -info->scale.y;
	    info->reverse_scale.y = -info->reverse_scale.y;
	    info->matrix.m[0][yi] = -info->matrix.m[0][yi];
	    info->matrix.m[1][yi] = -info->matrix.m[1][yi];
	}

	info->pen.x = SNAPH(info->scale.x / 24);
	info->pen.y = SNAPH(info->scale.y / 24);
	if (info->pen.x < SNEK_DRAW_FLOAT_HALF)
	    info->pen.x = SNEK_DRAW_FLOAT_HALF;
	if (info->pen.y < SNEK_DRAW_FLOAT_HALF)
	    info->pen.y = SNEK_DRAW_FLOAT_HALF;
	info->margin.x = info->pen.x;
	info->margin.y = info->pen.y;
	if (path->state.font_style & SNEK_DRAW_TEXT_BOLD)
	{
	    float    pen_x_add = SNAPH(info->pen.x / 2);
	    float    pen_y_add = SNAPH(info->pen.y / 2);

	    if (pen_x_add < SNEK_DRAW_FLOAT_HALF)
		pen_x_add = SNEK_DRAW_FLOAT_HALF;
	    if (pen_y_add < SNEK_DRAW_FLOAT_HALF)
		pen_y_add = SNEK_DRAW_FLOAT_HALF;
	    info->pen.x += pen_x_add;
	    info->pen.y += pen_y_add;
	}
	DBGMSG (("pen: %9.4f %9.4f\n", F(info->pen.x), F(info->pen.y)));

	snek_draw_matrix_translate (&info->matrix,
			       SNAPI(info->margin.x) + info->pen.x,
			       -info->pen.y);
	info->pen_matrix = info->matrix;
    }
    else
    {
	info->snap = false;
	info->matrix = path->state.matrix;
	info->matrix.m[2][0] = snek_draw_sfixed_to_float (origin.x);
	info->matrix.m[2][1] = snek_draw_sfixed_to_float (origin.y);
	info->scale.x = path->state.font_size;
	info->scale.y = path->state.font_size;

	if (path->state.font_style & SNEK_DRAW_TEXT_BOLD)
	    info->pen.x = path->state.font_size / 16;
	else
	    info->pen.x = path->state.font_size / 24;
	info->pen.y = info->pen.x;

	info->margin.x = path->state.font_size / 24;
	info->margin.y = info->margin.x;

	info->pen_matrix = path->state.matrix;
	snek_draw_matrix_translate (&info->matrix,
			       info->margin.x + info->pen.x, -info->pen.y);
    }
    info->pen_matrix.m[2][0] = 0; info->pen_matrix.m[2][1] = 0;
    snek_draw_matrix_scale (&info->pen_matrix, info->pen.x, info->pen.y);

    if (path->state.font_style & SNEK_DRAW_TEXT_OBLIQUE)
    {
	snek_draw_matrix_t	m;

	m.m[0][0] = SNEK_DRAW_FLOAT_ONE;	    m.m[0][1] = 0;
	m.m[1][0] = -SNEK_DRAW_FLOAT_ONE / 4;    m.m[1][1] = SNEK_DRAW_FLOAT_ONE;
	m.m[2][0] = 0;			    m.m[2][1] = 0;
	snek_draw_matrix_multiply (&info->matrix, &m, &info->matrix);
    }
    DBGMSG (("%9.4f %9.4f\n", F(info->matrix.m[0][0]), F(info->matrix.m[0][1])));
    DBGMSG (("%9.4f %9.4f\n", F(info->matrix.m[1][0]), F(info->matrix.m[1][1])));
    DBGMSG (("%9.4f %9.4f\n", F(info->matrix.m[2][0]), F(info->matrix.m[2][1])));
}

static void
_snek_draw_text_compute_snap (snek_draw_text_info_t   *info,
			 const signed char  *b)
{
    int			s, n;
    const signed char	*snap;

    snap = snek_draw_glyph_snap_x (b);
    n = snek_draw_glyph_n_snap_x (b);
    info->n_snap_x = n;
    for (s = 0; s < n; s++)
	info->snap_x[s] = FX(snap[s], info);

    snap = snek_draw_glyph_snap_y (b);
    n = snek_draw_glyph_n_snap_y (b);
    info->n_snap_y = n;
    for (s = 0; s < n; s++)
	info->snap_y[s] = FY(snap[s], info);
}

static snek_draw_path_t *
_snek_draw_text_compute_pen (snek_draw_text_info_t *info)
{
    snek_draw_path_t	*pen = snek_draw_path_create ();

    snek_draw_path_set_matrix (pen, info->pen_matrix);
    snek_draw_path_circle (pen, 0, 0, SNEK_DRAW_FLOAT_ONE);
    return pen;
}

static float
_snek_draw_snap (float    v,
	    float    *snap,
	    int		    n)
{
    int	s;

    for (s = 0; s < n - 1; s++)
    {
	if (snap[s] <= v && v <= snap[s+1])
	{
	    float    before = snap[s];
	    float    after = snap[s+1];
	    float    dist = after - before;
	    float    snap_before = SNAPI(before);
	    float    snap_after = SNAPI(after);
	    float    move_before = snap_before - before;
	    float    move_after = snap_after - after;
	    float    dist_before = v - before;
	    float    dist_after = after - v;
	    float    move = ((int64_t) dist_before * move_after +
				    (int64_t) dist_after * move_before) / dist;
	    DBGMSG (("%9.4f <= %9.4f <= %9.4f\n", F(before), F(v), F(after)));
	    DBGMSG (("before: %9.4f -> %9.4f\n", F(before), F(snap_before)));
	    DBGMSG (("after: %9.4f -> %9.4f\n", F(after), F(snap_after)));
	    DBGMSG (("v: %9.4f -> %9.4f\n", F(v), F(v+move)));
	    v += move;
	    break;
	}
    }
    return v;
}

bool
snek_draw_has_ucs4 (snek_draw_ucs4_t ucs4)
{
    return ucs4 <= SNEK_DRAW_FONT_MAX && _snek_draw_g_offsets[ucs4] != 0;
}

#define SNAPX(p)	_snap (path, p, snap_x, nsnap_x)
#define SNAPY(p)	_snap (path, p, snap_y, nsnap_y)

static const signed char *
_snek_draw_g_base (snek_draw_ucs4_t ucs4)
{
    if (ucs4 > SNEK_DRAW_FONT_MAX) ucs4 = 0;

    return _snek_draw_gtable + _snek_draw_g_offsets[ucs4];
}

static float
_snek_draw_glyph_width (snek_draw_text_info_t	*info,
		   const signed char	*b)
{
    float    right = FX(snek_draw_glyph_right(b), info) + info->pen.x * 2;
    float    right_side_bearing;
    float    width;

    if (info->snap)
	right = SNAPI(_snek_draw_snap (right, info->snap_x, info->n_snap_x));

    right_side_bearing = right + info->margin.x;
    width = right_side_bearing + info->margin.x;
    return width;
}

void
snek_draw_text_metrics_ucs4 (snek_draw_path_t	    *path,
			snek_draw_ucs4_t	    ucs4,
			snek_draw_text_metrics_t *m)
{
    const signed char	*b = _snek_draw_g_base (ucs4);
    snek_draw_text_info_t	info;
    float	left, right, ascent, descent;
    float	font_spacing;
    float	font_descent;
    float	font_ascent;
    float	margin_x, margin_y;

    _snek_draw_text_compute_info (path, &info);
    if (info.snap)
	_snek_draw_text_compute_snap (&info, b);

    left = FX(snek_draw_glyph_left(b), &info);
    right = FX(snek_draw_glyph_right(b), &info) + info.pen.x * 2;
    ascent = FY(snek_draw_glyph_ascent(b), &info) + info.pen.y * 2;
    descent = FY(snek_draw_glyph_descent(b), &info);
    margin_x = info.margin.x;
    margin_y = info.margin.y;

    font_spacing = FY(SNEK_DRAW_GFIXED_ONE, &info);
    font_descent = font_spacing / 3;
    font_ascent = font_spacing - font_descent;
    if (info.snap)
    {
	left = SNAPI(_snek_draw_snap (left, info.snap_x, info.n_snap_x));
	right = SNAPI(_snek_draw_snap (right, info.snap_x, info.n_snap_x));
	ascent = SNAPI(_snek_draw_snap (ascent, info.snap_y, info.n_snap_y));
	descent = SNAPI(_snek_draw_snap (descent, info.snap_y, info.n_snap_y));
	font_descent = SNAPI(font_descent);
	font_ascent = SNAPI(font_ascent);

	left = left * info.reverse_scale.x;
	right = right * info.reverse_scale.x;
	ascent = ascent * info.reverse_scale.y;
	descent = descent * info.reverse_scale.y;
	font_descent = font_descent * info.reverse_scale.y;
	font_ascent = font_ascent * info.reverse_scale.y;
	margin_x = margin_x * info.reverse_scale.x;
	margin_y = margin_y * info.reverse_scale.y;
    }
    m->left_side_bearing = left + margin_x;
    m->right_side_bearing = right + margin_x;
    m->ascent = ascent;
    m->descent = descent;
    m->width = m->right_side_bearing + margin_x;
    m->font_ascent = font_ascent + margin_y;
    m->font_descent = font_descent + margin_y;
}

void
snek_draw_path_ucs4 (snek_draw_path_t *path, snek_draw_ucs4_t ucs4)
{
    const signed char	*b = _snek_draw_g_base (ucs4);
    const signed char	*g = snek_draw_glyph_draw(b);
    snek_draw_spoint_t	origin;
    float	x1, y1, x2, y2, x3, y3;
    snek_draw_path_t		*stroke;
    snek_draw_path_t		*pen;
    float	width;
    snek_draw_text_info_t	info;

    _snek_draw_text_compute_info (path, &info);
    if (info.snap)
	_snek_draw_text_compute_snap (&info, b);

    origin = _snek_draw_path_current_spoint (path);

    stroke = snek_draw_path_create ();
    snek_draw_path_set_matrix (stroke, info.matrix);
    pen = _snek_draw_text_compute_pen (&info);

    for (;;) {
	switch (*g++) {
	case 'm':
	    x1 = FX(*g++, &info);
	    y1 = FY(*g++, &info);
	    if (info.snap)
	    {
		x1 = _snek_draw_snap (x1, info.snap_x, info.n_snap_x);
		y1 = _snek_draw_snap (y1, info.snap_y, info.n_snap_y);
	    }
	    DBGMSG (("m %9.4f %9.4f\n",
		    S(_snek_draw_matrix_x (&stroke->state.matrix, x1, y1)),
		    S(_snek_draw_matrix_y (&stroke->state.matrix, x1, y1))));
	    snek_draw_path_move (stroke, x1, y1);
	    continue;
	case 'l':
	    x1 = FX(*g++, &info);
	    y1 = FY(*g++, &info);
	    if (info.snap)
	    {
		x1 = _snek_draw_snap (x1, info.snap_x, info.n_snap_x);
		y1 = _snek_draw_snap (y1, info.snap_y, info.n_snap_y);
	    }
	    DBGMSG (("l %9.4f %9.4f\n",
		    S(_snek_draw_matrix_x (&stroke->state.matrix, x1, y1)),
		    S(_snek_draw_matrix_y (&stroke->state.matrix, x1, y1))));
	    snek_draw_path_draw (stroke, x1, y1);
	    continue;
	case 'c':
	    x1 = FX(*g++, &info);
	    y1 = FY(*g++, &info);
	    x2 = FX(*g++, &info);
	    y2 = FY(*g++, &info);
	    x3 = FX(*g++, &info);
	    y3 = FY(*g++, &info);
	    if (info.snap)
	    {
		x1 = _snek_draw_snap (x1, info.snap_x, info.n_snap_x);
		y1 = _snek_draw_snap (y1, info.snap_y, info.n_snap_y);
		x2 = _snek_draw_snap (x2, info.snap_x, info.n_snap_x);
		y2 = _snek_draw_snap (y2, info.snap_y, info.n_snap_y);
		x3 = _snek_draw_snap (x3, info.snap_x, info.n_snap_x);
		y3 = _snek_draw_snap (y3, info.snap_y, info.n_snap_y);
	    }
	    snek_draw_path_curve (stroke, x1, y1, x2, y2, x3, y3);
	    continue;
	case 'e':
	    break;
	}
	break;
    }

    snek_draw_path_convolve (path, stroke, pen);
    snek_draw_path_destroy (pen);
    snek_draw_path_destroy (stroke);

    width = _snek_draw_glyph_width (&info, b);

    _snek_draw_path_smove (path,
		      origin.x + _snek_draw_matrix_dx (&info.matrix, width, 0),
		      origin.y + _snek_draw_matrix_dy (&info.matrix, width, 0));
}

float
snek_draw_width_ucs4 (snek_draw_path_t *path, snek_draw_ucs4_t ucs4)
{
    snek_draw_text_metrics_t	metrics;

    snek_draw_text_metrics_ucs4 (path, ucs4, &metrics);
    return metrics.width;
}

static int
_snek_draw_utf8_to_ucs4 (const char	    *src_orig,
		    snek_draw_ucs4_t	    *dst)
{
    const char	    *src = src_orig;
    char	    s;
    int		    extra;
    snek_draw_ucs4_t	    result;

    s = *src++;
    if (!s)
	return 0;

    if (!(s & 0x80))
    {
	result = s;
	extra = 0;
    }
    else if (!(s & 0x40))
    {
	return -1;
    }
    else if (!(s & 0x20))
    {
	result = s & 0x1f;
	extra = 1;
    }
    else if (!(s & 0x10))
    {
	result = s & 0xf;
	extra = 2;
    }
    else if (!(s & 0x08))
    {
	result = s & 0x07;
	extra = 3;
    }
    else if (!(s & 0x04))
    {
	result = s & 0x03;
	extra = 4;
    }
    else if ( ! (s & 0x02))
    {
	result = s & 0x01;
	extra = 5;
    }
    else
    {
	return -1;
    }

    while (extra--)
    {
	result <<= 6;
	s = *src++;
	if (!s)
	    return -1;

	if ((s & 0xc0) != 0x80)
	    return -1;

	result |= s & 0x3f;
    }
    *dst = result;
    return src - src_orig;
}

void
snek_draw_path_utf8 (snek_draw_path_t *path, const char *string)
{
    int		len;
    snek_draw_ucs4_t	ucs4;

    while ((len = _snek_draw_utf8_to_ucs4(string, &ucs4)) > 0)
    {
	snek_draw_path_ucs4 (path, ucs4);
	string += len;
    }
}

float
snek_draw_width_utf8 (snek_draw_path_t *path, const char *string)
{
    int		    len;
    snek_draw_ucs4_t	    ucs4;
    float    w = 0;

    while ((len = _snek_draw_utf8_to_ucs4(string, &ucs4)) > 0)
    {
	w += snek_draw_width_ucs4 (path, ucs4);
	string += len;
    }
    return w;
}

void
snek_draw_text_metrics_utf8 (snek_draw_path_t	    *path,
			const char	    *string,
			snek_draw_text_metrics_t *m)
{
    int			len;
    snek_draw_ucs4_t		ucs4;
    float	w = 0;
    snek_draw_text_metrics_t	c;
    bool		first = true;

    while ((len = _snek_draw_utf8_to_ucs4(string, &ucs4)) > 0)
    {
	snek_draw_text_metrics_ucs4 (path, ucs4, &c);
	if (first)
	{
	    *m = c;
	    first = false;
	}
	else
	{
	    c.left_side_bearing += w;
	    c.right_side_bearing += w;
	    c.width += w;

	    if (c.left_side_bearing < m->left_side_bearing)
		m->left_side_bearing = c.left_side_bearing;
	    if (c.right_side_bearing > m->right_side_bearing)
		m->right_side_bearing = c.right_side_bearing;
	    if (c.width > m->width)
		m->width = c.width;
	    if (c.ascent > m->ascent)
		m->ascent = c.ascent;
	    if (c.descent > m->descent)
		m->descent = c.descent;
	}
	w = c.width;
	string += len;
    }
}
