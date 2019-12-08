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

#if 0
#include <stdio.h>
#define F(f)	(f)
#define DBGMSG(x) printf x

static void
_snek_draw_dump_matrix (char *name, const snek_draw_matrix_t *m)
{
    int row, col;

    printf ("%-6.6s:", name);
    for (row = 0; row < 3; row++)
    {
	printf ("\t");
	for (col = 0; col < 2; col++)
	    printf ("%9.4f ", m->m[row][col]);
	printf ("\n");
    }
}

#else
#define DBGMSG(x)
#define _snek_draw_dump_matrix(n,m)
#endif

void
snek_draw_matrix_multiply (snek_draw_matrix_t	    *result,
		      const snek_draw_matrix_t   *a,
		      const snek_draw_matrix_t   *b)
{
    snek_draw_matrix_t   r;
    int		    row, col, n;
    float    t;

    for (row = 0; row < 3; row++)
	for (col = 0; col < 2; col++) {
	    if (row == 2)
		t = b->m[2][col];
	    else
		t = 0;
	    for (n = 0; n < 2; n++)
		t += a->m[row][n] * b->m[n][col];
	    r.m[row][col] = t;
	}
    _snek_draw_dump_matrix ("a", a);
    _snek_draw_dump_matrix ("b", b);
    _snek_draw_dump_matrix ("r", &r);

    *result = r;
}

void
snek_draw_matrix_identity (snek_draw_matrix_t *m)
{
    m->m[0][0] = SNEK_DRAW_FLOAT_ONE;    m->m[0][1] = 0;
    m->m[1][0] = 0;		    m->m[1][1] = SNEK_DRAW_FLOAT_ONE;
    m->m[2][0] = 0;		    m->m[2][1] = 0;
}

void
snek_draw_matrix_translate (snek_draw_matrix_t *m, float tx, float ty)
{
    snek_draw_matrix_t   t;

    t.m[0][0] = SNEK_DRAW_FLOAT_ONE;	    t.m[0][1] = 0;
    t.m[1][0] = 0;		    t.m[1][1] = SNEK_DRAW_FLOAT_ONE;
    t.m[2][0] = tx;		    t.m[2][1] = ty;
    snek_draw_matrix_multiply (m, &t, m);
}

void
snek_draw_matrix_scale (snek_draw_matrix_t *m, float sx, float sy)
{
    snek_draw_matrix_t   t;

    t.m[0][0] = sx;		    t.m[0][1] = 0;
    t.m[1][0] = 0;		    t.m[1][1] = sy;
    t.m[2][0] = 0;		    t.m[2][1] = 0;
    snek_draw_matrix_multiply (m, &t, m);
}

float
_snek_draw_matrix_determinant (snek_draw_matrix_t *matrix)
{
    float    a, b, c, d;
    float    det;

    a = matrix->m[0][0]; b = matrix->m[0][1];
    c = matrix->m[1][0]; d = matrix->m[1][1];

    det = a * d - b * c;

    return det;
}

snek_draw_point_t
_snek_draw_matrix_expand (snek_draw_matrix_t *matrix)
{
    float    a = matrix->m[0][0];
    float    d = matrix->m[1][1];
    float    aa = a * a;
    float    dd = d * d;
    snek_draw_point_t    expand;

    expand.x = sqrtf (aa + dd);
    expand.y = _snek_draw_matrix_determinant (matrix) / expand.x;
    return expand;
}

void
snek_draw_matrix_rotate (snek_draw_matrix_t *m, snek_draw_angle_t a)
{
    snek_draw_matrix_t   t;
    float    c = snek_draw_cos (a);
    float    s = snek_draw_sin (a);

    t.m[0][0] = c;		    t.m[0][1] = s;
    t.m[1][0] = -s;		    t.m[1][1] = c;
    t.m[2][0] = 0;		    t.m[2][1] = 0;
    snek_draw_matrix_multiply (m, &t, m);
}

snek_draw_sfixed_t
_snek_draw_matrix_x (snek_draw_matrix_t *m, float x, float y)
{
    snek_draw_sfixed_t   s;
    s = snek_draw_float_to_sfixed (m->m[0][0] * x +
			      m->m[1][0] * y +
			      m->m[2][0]);
    DBGMSG (("x: %9.4f,%9.4f -> %9.4f\n",
	     (x), (y),
	     snek_draw_sfixed_to_float (s)));
    return s;
}

snek_draw_sfixed_t
_snek_draw_matrix_y (snek_draw_matrix_t *m, float x, float y)
{
    snek_draw_sfixed_t   s;
    s = snek_draw_float_to_sfixed (m->m[0][1] * x +
			      m->m[1][1] * y +
			      m->m[2][1]);
    DBGMSG (("y: %9.4f,%9.4f -> %9.4f\n",
	     (x), (y),
	     snek_draw_sfixed_to_float (s)));
    return s;
}

snek_draw_sfixed_t
_snek_draw_matrix_dx (snek_draw_matrix_t *m, float x, float y)
{
    return snek_draw_float_to_sfixed (m->m[0][0] * x +
				 m->m[1][0] * y);

}

snek_draw_sfixed_t
_snek_draw_matrix_dy (snek_draw_matrix_t *m, float x, float y)
{
    return snek_draw_float_to_sfixed (m->m[0][1] * x +
				 m->m[1][1] * y);
}

snek_draw_sfixed_t
_snek_draw_matrix_len (snek_draw_matrix_t *m, float dx, float dy)
{
    float    xs = (m->m[0][0] * dx + m->m[1][0] * dy);
    float    ys = (m->m[0][1] * dx + m->m[1][1] * dy);
    float    ds = (xs * xs + ys * ys);
    return (snek_draw_float_to_sfixed (sqrtf (ds)));
}
