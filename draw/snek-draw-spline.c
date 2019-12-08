/*
 * SnekDraw - A Tiny Window System
 * Copyright © 2004 Carl Worth <cworth@cworth.org>
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

typedef struct _snek_draw_spline {
    snek_draw_spoint_t    a, b, c, d;
} snek_draw_spline_t;

static void
_lerp_half (snek_draw_spoint_t *a, snek_draw_spoint_t *b, snek_draw_spoint_t *result)
{
    result->x = a->x + ((b->x - a->x) >> 1);
    result->y = a->y + ((b->y - a->y) >> 1);
}

static void
_de_casteljau (snek_draw_spline_t *spline, snek_draw_spline_t *s1, snek_draw_spline_t *s2)
{
    snek_draw_spoint_t ab, bc, cd;
    snek_draw_spoint_t abbc, bccd;
    snek_draw_spoint_t final;

    _lerp_half (&spline->a, &spline->b, &ab);
    _lerp_half (&spline->b, &spline->c, &bc);
    _lerp_half (&spline->c, &spline->d, &cd);
    _lerp_half (&ab, &bc, &abbc);
    _lerp_half (&bc, &cd, &bccd);
    _lerp_half (&abbc, &bccd, &final);

    s1->a = spline->a;
    s1->b = ab;
    s1->c = abbc;
    s1->d = final;

    s2->a = final;
    s2->b = bccd;
    s2->c = cd;
    s2->d = spline->d;
}

/*
 * Return an upper bound on the error (squared) that could
 * result from approximating a spline as a line segment 
 * connecting the two endpoints 
 */

static snek_draw_dfixed_t
_snek_draw_spline_error_squared (snek_draw_spline_t *spline)
{
    snek_draw_dfixed_t berr, cerr;

    berr = _snek_draw_distance_to_line_squared (&spline->b, &spline->a, &spline->d);
    cerr = _snek_draw_distance_to_line_squared (&spline->c, &spline->a, &spline->d);

    if (berr > cerr)
	return berr;
    else
	return cerr;
}

/*
 * Pure recursive spline decomposition.
 */

static void
_snek_draw_spline_decompose (snek_draw_path_t	*path,
			snek_draw_spline_t	*spline, 
			snek_draw_dfixed_t	tolerance_squared)
{
    if (_snek_draw_spline_error_squared (spline) <= tolerance_squared)
    {
	_snek_draw_path_sdraw (path, spline->a.x, spline->a.y);
    }
    else
    {
	snek_draw_spline_t s1, s2;
	_de_casteljau (spline, &s1, &s2);
	_snek_draw_spline_decompose (path, &s1, tolerance_squared);
	_snek_draw_spline_decompose (path, &s2, tolerance_squared);
    }
}

void
_snek_draw_path_scurve (snek_draw_path_t	    *path,
		   snek_draw_sfixed_t    x1, snek_draw_sfixed_t y1,
		   snek_draw_sfixed_t    x2, snek_draw_sfixed_t y2,
		   snek_draw_sfixed_t    x3, snek_draw_sfixed_t y3)
{
    snek_draw_spline_t   spline;

    if (path->npoints == 0)
	_snek_draw_path_smove (path, 0, 0);
    spline.a = path->points[path->npoints - 1];
    spline.b.x = x1;
    spline.b.y = y1;
    spline.c.x = x2;
    spline.c.y = y2;
    spline.d.x = x3;
    spline.d.y = y3;
    _snek_draw_spline_decompose (path, &spline, SNEK_DRAW_SFIXED_TOLERANCE * SNEK_DRAW_SFIXED_TOLERANCE);
    _snek_draw_path_sdraw (path, x3, y3);
}

void
snek_draw_path_curve (snek_draw_path_t	*path,
		 float   x1, float y1,
		 float   x2, float y2,
		 float   x3, float y3)
{
    return _snek_draw_path_scurve (path,
			      _snek_draw_matrix_x (&path->state.matrix, x1, y1),
			      _snek_draw_matrix_y (&path->state.matrix, x1, y1),
			      _snek_draw_matrix_x (&path->state.matrix, x2, y2),
			      _snek_draw_matrix_y (&path->state.matrix, x2, y2),
			      _snek_draw_matrix_x (&path->state.matrix, x3, y3),
			      _snek_draw_matrix_y (&path->state.matrix, x3, y3));
}
