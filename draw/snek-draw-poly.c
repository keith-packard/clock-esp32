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

typedef struct _snek_draw_edge {
	struct _snek_draw_edge	*next;
	snek_draw_sfixed_t	top, bot;
	snek_draw_sfixed_t	x;
	snek_draw_sfixed_t	e;
	snek_draw_sfixed_t	dx, dy;
	snek_draw_sfixed_t	inc_x;
	snek_draw_sfixed_t	step_x;
	int			winding;
} snek_draw_edge_t;

#define SNEK_DRAW_POLY_SHIFT	    2
#define SNEK_DRAW_POLY_FIXED_SHIFT	(4 - SNEK_DRAW_POLY_SHIFT)
#define SNEK_DRAW_POLY_SAMPLE    (1 << SNEK_DRAW_POLY_SHIFT)
#define SNEK_DRAW_POLY_MASK	    (SNEK_DRAW_POLY_SAMPLE - 1)
#define SNEK_DRAW_POLY_STEP	    (SNEK_DRAW_SFIXED_ONE >> SNEK_DRAW_POLY_SHIFT)
#define SNEK_DRAW_POLY_START	    (SNEK_DRAW_POLY_STEP >> 1)
#define SNEK_DRAW_POLY_CEIL(c)   (((c) + (SNEK_DRAW_POLY_STEP-1)) & ~(SNEK_DRAW_POLY_STEP-1))
#define SNEK_DRAW_POLY_COL(x)    (((x) >> SNEK_DRAW_POLY_FIXED_SHIFT) & SNEK_DRAW_POLY_MASK)

static int
_edge_compare_y (const void *a, const void *b)
{
	const snek_draw_edge_t	*ae = a;
	const snek_draw_edge_t	*be = b;

	return (int) (ae->top - be->top);
}

static void
_edge_step_by (snek_draw_edge_t  *edge, snek_draw_sfixed_t dy)
{
	snek_draw_dfixed_t   e;

	e = edge->e + (snek_draw_dfixed_t) dy * edge->dx;
	edge->x += edge->step_x * dy + edge->inc_x * (e / edge->dy);
	edge->e = e % edge->dy;
}

/*
 * Returns the nearest grid coordinate no less than f
 *
 * Grid coordinates are at SNEK_DRAW_POLY_STEP/2 + n*SNEK_DRAW_POLY_STEP
 */

static snek_draw_sfixed_t
_snek_draw_sfixed_grid_ceil (snek_draw_sfixed_t f)
{
	return ((f + (SNEK_DRAW_POLY_START - 1)) & ~(SNEK_DRAW_POLY_STEP - 1)) + SNEK_DRAW_POLY_START;
}

#if 0
#include <stdio.h>
#define F(x)	snek_draw_sfixed_to_float(x)
#define DBGOUT(x...)	printf(x)
#else
#define DBGOUT(x...)
#endif

static int
_snek_draw_edge_build (snek_draw_spoint_t *vertices, int nvertices, snek_draw_edge_t *edges,
		       snek_draw_sfixed_t dx, snek_draw_sfixed_t dy, snek_draw_sfixed_t top_y)
{
	int		    v, nv;
	int		    tv, bv;
	int		    e;
	snek_draw_sfixed_t   y;

	e = 0;
	for (v = 0; v < nvertices; v++)
	{
		nv = v + 1;
		if (nv == nvertices) nv = 0;

		/* skip horizontal edges */
		if (vertices[v].y == vertices[nv].y)
			continue;

		DBGOUT ("Vertex: %9.4f, %9.4f\n", F(vertices[v].x), F(vertices[v].y));

		/* figure winding */
		if (vertices[v].y < vertices[nv].y)
		{
			edges[e].winding = 1;
			tv = v;
			bv = nv;
		}
		else
		{
			edges[e].winding = -1;
			tv = nv;
			bv = v;
		}

		/* snap top to first grid point in pixmap */
		y = _snek_draw_sfixed_grid_ceil (vertices[tv].y + dy);
		if (y < SNEK_DRAW_POLY_START + top_y)
			y = SNEK_DRAW_POLY_START + top_y;

		/* skip vertices which don't span a sample row */
		if (y >= vertices[bv].y + dy)
			continue;

		/* Compute bresenham terms */
		edges[e].dx = vertices[bv].x - vertices[tv].x;
		edges[e].dy = vertices[bv].y - vertices[tv].y;
		if (edges[e].dx >= 0)
			edges[e].inc_x = 1;
		else
		{
			edges[e].inc_x = -1;
			edges[e].dx = -edges[e].dx;
		}
		edges[e].step_x = edges[e].inc_x * (edges[e].dx / edges[e].dy);
		edges[e].dx = edges[e].dx % edges[e].dy;

		edges[e].top = vertices[tv].y + dy;
		edges[e].bot = vertices[bv].y + dy;

		edges[e].x = vertices[tv].x + dx;
		edges[e].e = 0;

		/* step to first grid point */
		_edge_step_by (&edges[e], y - edges[e].top);

		edges[e].top = y;
		e++;
	}
	return e;
}

static void
_span_fill (snek_draw_pixmap_t   *pixmap,
	    snek_draw_sfixed_t    y,
	    snek_draw_sfixed_t    left,
	    snek_draw_sfixed_t    right)
{
#if SNEK_DRAW_POLY_SHIFT == 0
	/* 1x1 */
	static const snek_draw_a8_t	coverage[1][1] = {
		{ 0xff },
	};
#endif
#if SNEK_DRAW_POLY_SHIFT == 1
	/* 2x2 */
	static const snek_draw_a8_t	coverage[2][2] = {
		{ 0x40, 0x40 },
		{ 0x3f, 0x40 },
	};
#endif
#if SNEK_DRAW_POLY_SHIFT == 2
	/* 4x4 */
	static const snek_draw_a8_t	coverage[4][4] = {
		{ 0x10, 0x10, 0x10, 0x10 },
		{ 0x10, 0x10, 0x10, 0x10 },
		{ 0x0f, 0x10, 0x10, 0x10 },
		{ 0x10, 0x10, 0x10, 0x10 },
	};
#endif
#if SNEK_DRAW_POLY_SHIFT == 3
	/* 8x8 */
	static const snek_draw_a8_t	coverage[8][8] = {
		{ 4, 4, 4, 4, 4, 4, 4, 4 },
		{ 4, 4, 4, 4, 4, 4, 4, 4 },
		{ 4, 4, 4, 4, 4, 4, 4, 4 },
		{ 4, 4, 4, 4, 4, 4, 4, 4 },
		{ 3, 4, 4, 4, 4, 4, 4, 4 },
		{ 4, 4, 4, 4, 4, 4, 4, 4 },
		{ 4, 4, 4, 4, 4, 4, 4, 4 },
		{ 4, 4, 4, 4, 4, 4, 4, 4 },
	};
#endif
	const snek_draw_a8_t *cover = coverage[(y >> SNEK_DRAW_POLY_FIXED_SHIFT) & SNEK_DRAW_POLY_MASK];
	int		    row = snek_draw_sfixed_trunc (y);
	snek_draw_a8_t	    *span = snek_draw_pixmap_pointer(pixmap, 0, row).a8;
	snek_draw_a8_t	    *s;
	snek_draw_sfixed_t    x;
	snek_draw_a16_t	    a;
	snek_draw_a16_t	    w;
	int		    col;

	/* clip to pixmap */
	if (left < 0)
		left = 0;

	if (right > snek_draw_int_to_sfixed (pixmap->width))
		right = snek_draw_int_to_sfixed (pixmap->width);

	/* convert to sample grid */
	left = _snek_draw_sfixed_grid_ceil (left) >> SNEK_DRAW_POLY_FIXED_SHIFT;
	right = _snek_draw_sfixed_grid_ceil (right) >> SNEK_DRAW_POLY_FIXED_SHIFT;

	/* check for empty */
	if (right <= left)
		return;

	x = left;

	/* starting address */
	s = span + (x >> SNEK_DRAW_POLY_SHIFT);

	/* first pixel */
	if (x & SNEK_DRAW_POLY_MASK)
	{
		w = 0;
		col = 0;
		while (x < right && (x & SNEK_DRAW_POLY_MASK))
		{
			w += cover[col++];
			x++;
		}
		a = *s + w;
		*s++ = snek_draw_sat (a);
	}

	w = 0;
	for (col = 0; col < SNEK_DRAW_POLY_SAMPLE; col++)
		w += cover[col];

	/* middle pixels */
	while (x + SNEK_DRAW_POLY_MASK < right)
	{
		a = *s + w;
		*s++ = snek_draw_sat (a);
		x += SNEK_DRAW_POLY_SAMPLE;
	}

	/* last pixel */
	if (right & SNEK_DRAW_POLY_MASK)
	{
		w = 0;
		col = 0;
		while (x < right)
		{
			w += cover[col++];
			x++;
		}
		a = *s + w;
		*s = snek_draw_sat (a);
	}
}

static void
_snek_draw_edge_fill (snek_draw_pixmap_t *pixmap, snek_draw_edge_t *edges, int nedges)
{
	snek_draw_edge_t	    *active, *a, *n, **prev;
	int		    e;
	snek_draw_sfixed_t    y;
	snek_draw_sfixed_t    x0 = 0;
	int		    w;

	qsort (edges, nedges, sizeof (snek_draw_edge_t), _edge_compare_y);
	e = 0;
	y = edges[0].top;
	active = 0;
	for (;;)
	{
		/* add in new edges */
		for (;e < nedges && edges[e].top <= y; e++)
		{
			for (prev = &active; (a = *prev); prev = &(a->next))
				if (a->x > edges[e].x)
					break;
			edges[e].next = *prev;
			*prev = &edges[e];
		}

		DBGOUT ("Y %9.4f:", F(y));
		/* walk this y value marking coverage */
		w = 0;
		for (a = active; a; a = a->next)
		{
			DBGOUT (" %9.4f(%d)", F(a->x), a->winding);
			if (w == 0)
				x0 = a->x;
			w += a->winding;
			if (w == 0)
			{
				DBGOUT (" F ");
				_span_fill (pixmap, y, x0, a->x);
			}
		}
		DBGOUT ("\n");

		/* step down, clipping to pixmap */
		y += SNEK_DRAW_POLY_STEP;

		if (snek_draw_sfixed_trunc (y) >= pixmap->height)
			break;

		/* strip out dead edges */
		for (prev = &active; (a = *prev);)
		{
			if (a->bot <= y)
				*prev = a->next;
			else
				prev = &a->next;
		}

		/* check for all done */
		if (!active && e == nedges)
			break;

		/* step all edges */
		for (a = active; a; a = a->next)
			_edge_step_by (a, SNEK_DRAW_POLY_STEP);

		/* fix x sorting */
		for (prev = &active; (a = *prev) && (n = a->next);)
		{
			if (a->x > n->x)
			{
				a->next = n->next;
				n->next = a;
				*prev = n;
				prev = &active;
			}
			else
				prev = &a->next;
		}
	}
}

void
snek_draw_fill_path (snek_draw_pixmap_t *pixmap, snek_draw_path_t *path,
		     snek_draw_coord_t dx, snek_draw_coord_t dy)
{
	snek_draw_edge_t	    *edges;
	int		    nedges, n;
	int		    nalloc;
	int		    s;
	int		    p;
	snek_draw_sfixed_t   sdx = snek_draw_int_to_sfixed (dx);
	snek_draw_sfixed_t   sdy = snek_draw_int_to_sfixed (dy);

	nalloc = path->npoints + path->nsublen + 1;
	edges = malloc (sizeof (snek_draw_edge_t) * nalloc);
	if (!edges)
		return;
	p = 0;
	nedges = 0;
	for (s = 0; s <= path->nsublen; s++)
	{
		int sublen;
		int npoints;

		if (s == path->nsublen)
			sublen = path->npoints;
		else
			sublen = path->sublen[s];
		npoints = sublen - p;
		if (npoints > 1)
		{
			n = _snek_draw_edge_build (path->points + p, npoints, edges + nedges,
						   sdx, sdy, 0);
			p = sublen;
			nedges += n;
		}
	}
	_snek_draw_edge_fill (pixmap, edges, nedges);
	free (edges);
}
