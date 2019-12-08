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

#if 0
#include <stdio.h>
#include <math.h>
#define S(x)	snek_draw_sfixed_to_float(x)
#define DBGMSG(x)	printf x
#else
#define DBGMSG(x)
#endif

typedef struct snek_draw_slope {
    snek_draw_sfixed_t dx;
    snek_draw_sfixed_t dy;
} snek_draw_slope_t, snek_draw_distance_t;

typedef struct _snek_draw_hull {
    snek_draw_spoint_t point;
    snek_draw_slope_t slope;
    int discard;
} snek_draw_hull_t;

static void
_snek_draw_slope_init (snek_draw_slope_t *slope, snek_draw_spoint_t *a, snek_draw_spoint_t *b)
{
    slope->dx = b->x - a->x;
    slope->dy = b->y - a->y;
}

static snek_draw_hull_t *
_snek_draw_hull_create (snek_draw_path_t *path, int *nhull)
{
    int		    i, j;
    int		    n = path->npoints;
    snek_draw_spoint_t    *p = path->points;
    snek_draw_hull_t	    *hull;
    int		    e;
    
    e = 0;
    for (i = 1; i < n; i++)
	if (p[i].y < p[e].y || (p[i].y == p[e].y && p[i].x < p[e].x))
	    e = i;
    
    hull = malloc (n * sizeof (snek_draw_hull_t));
    if (hull == NULL)
	return NULL;
    *nhull = n;

    DBGMSG (("original polygon: \n"));
    for (i = 0; i < n; i++) 
    {
	DBGMSG (("\t%d: %9.4f, %9.4f\n", i, S(p[i].x), S(p[i].y)));
	/* place extremum first in array */
	if (i == 0) j = e;
	else if (i == e) j = 0;
	else j = i;
	
	hull[i].point = p[j];
	_snek_draw_slope_init (&hull[i].slope, &hull[0].point, &hull[i].point);

	/* Discard all points coincident with the extremal point */
	if (i != 0 && hull[i].slope.dx == 0 && hull[i].slope.dy == 0)
	    hull[i].discard = 1;
	else
	    hull[i].discard = 0;
    }

    return hull;
}

/* Compare two slopes. Slope angles begin at 0 in the direction of the
   positive X axis and increase in the direction of the positive Y
   axis.

   WARNING: This function only gives correct results if the angular
   difference between a and b is less than PI.

   <  0 => a less positive than b
   == 0 => a equal to be
   >  0 => a more positive than b
*/
static int
_snek_draw_slope_compare (snek_draw_slope_t *a, snek_draw_slope_t *b)
{
    snek_draw_dfixed_t diff;

    diff = ((snek_draw_dfixed_t) a->dy * (snek_draw_dfixed_t) b->dx -
	    (snek_draw_dfixed_t) b->dy * (snek_draw_dfixed_t) a->dx);

    if (diff > 0)
	return 1;
    if (diff < 0)
	return -1;

    if (a->dx == 0 && a->dy == 0)
	return 1;
    if (b->dx == 0 && b->dy ==0)
	return -1;

    return 0;
}

static int
_snek_draw_hull_vertex_compare (const void *av, const void *bv)
{
    snek_draw_hull_t *a = (snek_draw_hull_t *) av;
    snek_draw_hull_t *b = (snek_draw_hull_t *) bv;
    int ret;

    ret = _snek_draw_slope_compare (&a->slope, &b->slope);

    /* In the case of two vertices with identical slope from the
       extremal point discard the nearer point. */

    if (ret == 0) 
    {
	snek_draw_dfixed_t a_dist, b_dist;
	a_dist = ((snek_draw_dfixed_t) a->slope.dx * a->slope.dx +
		  (snek_draw_dfixed_t) a->slope.dy * a->slope.dy);
	b_dist = ((snek_draw_dfixed_t) b->slope.dx * b->slope.dx +
		  (snek_draw_dfixed_t) b->slope.dy * b->slope.dy);
	if (a_dist < b_dist)
	{
	    a->discard = 1;
	    ret = -1;
	}
	else
	{
	    b->discard = 1;
	    ret = 1;
	}
    }

    return ret;
}

static int
_snek_draw_hull_prev_valid (snek_draw_hull_t *hull, int num_hull, int index)
{
    (void) num_hull;
    do {
	/* hull[0] is always valid, so don't test and wraparound */
	index--;
    } while (hull[index].discard);

    return index;
}

static int
_snek_draw_hull_next_valid (snek_draw_hull_t *hull, int num_hull, int index)
{
    do {
	index = (index + 1) % num_hull;
    } while (hull[index].discard);

    return index;
}

/*
 * Graham scan to compute convex hull
 */

static void
_snek_draw_hull_eliminate_concave (snek_draw_hull_t *hull, int num_hull)
{
    int i, j, k;
    snek_draw_slope_t slope_ij, slope_jk;

    i = 0;
    j = _snek_draw_hull_next_valid (hull, num_hull, i);
    k = _snek_draw_hull_next_valid (hull, num_hull, j);

    do {
	DBGMSG (("i: %d j: %d k: %d\n", i, j, k));
	_snek_draw_slope_init (&slope_ij, &hull[i].point, &hull[j].point);
	_snek_draw_slope_init (&slope_jk, &hull[j].point, &hull[k].point);

	/* Is the angle formed by ij and jk concave? */
	if (_snek_draw_slope_compare (&slope_ij, &slope_jk) >= 0) {
	    if (i == k)
		break;
	    hull[j].discard = 1;
	    j = i;
	    i = _snek_draw_hull_prev_valid (hull, num_hull, j);
	} else {
	    i = j;
	    j = k;
	    k = _snek_draw_hull_next_valid (hull, num_hull, j);
	}
    } while (j != 0);
}

/*
 * Convert the hull structure back to a simple path
 */
static snek_draw_path_t *
_snek_draw_hull_to_path (snek_draw_hull_t *hull, int num_hull)
{
    snek_draw_path_t	*path = snek_draw_path_create ();
    int		i;

    DBGMSG (("convex hull\n"));
    for (i = 0; i < num_hull; i++) 
    {
	DBGMSG (("\t%d: %9.4f, %9.4f %c\n",
		 i, S(hull[i].point.x), S(hull[i].point.y), 
		 hull[i].discard ? '*' : ' '));
	if (hull[i].discard)
	    continue;
	_snek_draw_path_sdraw (path, hull[i].point.x, hull[i].point.y);
    }

    return path;
}

/*
 * Given a path, return the convex hull using the Graham scan algorithm. 
 */

snek_draw_path_t *
snek_draw_path_convex_hull (snek_draw_path_t *path)
{
    snek_draw_hull_t *hull;
    int		num_hull;
    snek_draw_path_t	*convex_path;

    hull = _snek_draw_hull_create (path, &num_hull);
    
    if (hull == NULL)
	return 0;

    qsort (hull + 1, num_hull - 1, sizeof (snek_draw_hull_t),
	   _snek_draw_hull_vertex_compare);

    _snek_draw_hull_eliminate_concave (hull, num_hull);

    convex_path = _snek_draw_hull_to_path (hull, num_hull);

    free (hull);

    return convex_path;
}
