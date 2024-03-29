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
 * License along with the Gnome Library; see the file COPYING.LIB.  If not,
 * write to the Free Software Foundation, Inc., 59 Temple Place - Suite 330,
 * Boston, MA 02111-1307, USA.
 */

#include "snek-draw-int.h"
	    
/*
 * Find the point in path which is furthest left of the line
 */
static int
_snek_draw_path_leftpoint (snek_draw_path_t   *path,
		      snek_draw_spoint_t *p1,
		      snek_draw_spoint_t *p2)
{
    snek_draw_spoint_t   *points = path->points;
    int		    p;
    int		    best = 0;
    /*
     * Normal form of the line is Ax + By + C = 0,
     * these are the A and B factors.  As we're just comparing
     * across x and y, the value of C isn't relevant
     */
    snek_draw_dfixed_t   Ap = p2->y - p1->y;
    snek_draw_dfixed_t   Bp = p1->x - p2->x;
    
    snek_draw_dfixed_t   max = -0x7fffffff;
    
    for (p = 0; p < path->npoints; p++)
    {
	snek_draw_dfixed_t	vp = Ap * points[p].x + Bp * points[p].y;

	if (vp > max)
	{
	    max = vp;
	    best = p;
	}
    }
    return best;
}

static int
_around_order (snek_draw_spoint_t    *a1,
	       snek_draw_spoint_t    *a2,
	       snek_draw_spoint_t    *b1,
	       snek_draw_spoint_t    *b2)
{
    snek_draw_dfixed_t   adx = (a2->x - a1->x);
    snek_draw_dfixed_t   ady = (a2->y - a1->y);
    snek_draw_dfixed_t   bdx = (b2->x - b1->x);
    snek_draw_dfixed_t   bdy = (b2->y - b1->y);
    snek_draw_dfixed_t   diff = (ady * bdx - bdy * adx);

    if (diff < 0) return -1;
    if (diff > 0) return 1;
    return 0;
}

#define F(x)	snek_draw_sfixed_to_float(x)
#if 0
#include <stdio.h>
#include <math.h>
#define DBGOUT(x...)	printf(x)

static double
_angle (snek_draw_spoint_t *a, snek_draw_spoint_t *b)
{
    snek_draw_sfixed_t    dx = b->x - a->x;
    snek_draw_sfixed_t    dy = b->y - a->y;
    double	    rad;

    rad = atan2 ((double) dy, (double) dx);
    return rad * 180 / M_PI;
}
#else
#define DBGOUT(x...)
#endif

#define A(a)  ((a) < 0 ? -(a) : (a))

/*
 * Convolve one subpath with a convex pen.  The result is
 * a closed path.
 */
static void
_snek_draw_subpath_convolve (snek_draw_path_t	*path,
			snek_draw_path_t	*stroke,
			snek_draw_path_t	*pen)
{
    snek_draw_spoint_t   *sp   = stroke->points;
    snek_draw_spoint_t   *pp   = pen->points;
    int		    ns    = stroke->npoints;
    int		    np    = pen->npoints;
    snek_draw_spoint_t   *sp0  = &sp[0];
    snek_draw_spoint_t   *sp1  = &sp[1];
    int		    start = _snek_draw_path_leftpoint (pen, sp0, sp1);
    snek_draw_spoint_t   *spn1 = &sp[ns-1];
    snek_draw_spoint_t   *spn2 = &sp[ns-2];
    int		    ret   = _snek_draw_path_leftpoint (pen, spn1, spn2);
    int		    p;
    int		    s;
    int		    starget;
    int		    ptarget;
    int		    inc;
    int		    first;

    DBGOUT ("convolve stroke:\n");
    for (s = 0; s < ns; s++)
	DBGOUT ("\ts%02d: %9.4f, %9.4f\n", s, F(sp[s].x), F(sp[s].y));
    DBGOUT ("convolve pen:\n");
    for (p = 0; p < np; p++)
	DBGOUT ("\tp%02d: %9.4f, %9.4f\n", p, F(pp[p].x), F(pp[p].y));
    
    s = 0;
    p = start;
    DBGOUT ("start:  ");
    DBGOUT ("s%02d (%9.4f, %9.4f), p%02d (%9.4f, %9.4f): %9.4f, %9.4f\n",
	    s, F(sp[s].x), F(sp[s].y),
	    p, F(pp[p].x), F(pp[p].y),
	    F(sp[s].x + pp[p].x), F(sp[s].y + pp[p].y));
    _snek_draw_path_smove (path, sp[s].x + pp[p].x, sp[s].y + pp[p].y);
    first = path->npoints - 1;
    
    /* step along the path first */
    inc = 1;
    starget = ns-1;
    ptarget = ret;
    for (;;)
    {
	/*
	 * Convolve the edges
	 */
	do
	{
	    int	sn = s + inc;
	    int	pn = (p == np - 1) ? 0 : p + 1;
	    int	pm = (p == 0) ? np - 1 : p - 1;
    
	    /*
	     * step along pen (forwards or backwards) or stroke as appropriate
	     */
	     
	    DBGOUT ("\tangles: stroke %9.4f +pen %9.4f -pen %9.4f\n",
		    _angle (&sp[s], &sp[sn]),
		    _angle (&pp[p], &pp[pn]),
		    _angle (&pp[pm], &pp[p]));
	    if (_around_order (&sp[s],&sp[sn],&pp[p],&pp[pn]) > 0)
	    {
		DBGOUT ("+pen:   ");
		p = pn;
	    }
	    else if (_around_order (&sp[s],&sp[sn],&pp[pm],&pp[p]) < 0)
	    {
		DBGOUT ("-pen:   ");
		p = pm;
	    }
	    else
	    {
		DBGOUT ("stroke: ");
		s = sn;
	    }
	    DBGOUT ("s%02d (%9.4f, %9.4f), p%02d (%9.4f, %9.4f): %9.4f, %9.4f\n",
		    s, F(sp[s].x), F(sp[s].y),
		    p, F(pp[p].x), F(pp[p].y),
		    F(sp[s].x + pp[p].x), F(sp[s].y + pp[p].y));
	    _snek_draw_path_sdraw (path, sp[s].x + pp[p].x, sp[s].y + pp[p].y);
	} while (s != starget);
	
	/*
	 * Finish this edge
	 */
	
	/* draw a cap */
	switch (path->state.cap_style) {
	    int		pm;
	case SnekDrawCapProjecting:
	    /*
	     * This draws a rough projecting cap using the
	     * pen.
	     *
	     * First, project the line forward one pen radius
	     * by finding the pen location halfway between the
	     * two normals.
	     *
	     * Then, just add that to the normals themselves to
	     * find the corners of the projecting cap.  
	     * 
	     * The result may have significant error, so overwrite
	     * the existing corners with the new coordinates to
	     * avoid a kink.
	     */
	    if (p <= ptarget)
		pm = (ptarget + p) >> 1;
	    else
	    {
		pm = (ptarget + np + p) >> 1;
		if (pm >= np) pm -= np;
	    }
	    
	    /* replace last point with corner of cap */
	    path->npoints--;
	    _snek_draw_path_sdraw (path,
			      sp[s].x + pp[pm].x + pp[p].x,
			      sp[s].y + pp[pm].y + pp[p].y);
	    p = ptarget;
	    if (inc == 1)
	    {
		/* start next line at cap corner */
		_snek_draw_path_sdraw (path,
				  sp[s].x + pp[pm].x + pp[p].x,
				  sp[s].y + pp[pm].y + pp[p].y);
	    }
	    else
	    {
		/* overwrite initial point */
		path->points[first].x = sp[s].x + pp[pm].x + pp[p].x;
		path->points[first].y = sp[s].y + pp[pm].y + pp[p].y;
	    }
	    break;
	case SnekDrawCapButt:
	    p = ptarget-1;
	    /* fall through … */
	case SnekDrawCapRound:
	    while (p != ptarget)
	    {
		if (++p == np) p = 0;
		DBGOUT("cap:    ");
		DBGOUT ("s%02d (%9.4f, %9.4f), p%02d (%9.4f, %9.4f): %9.4f, %9.4f\n",
			s, F(sp[s].x), F(sp[s].y),
			p, F(pp[p].x), F(pp[p].y),
			F(sp[s].x + pp[p].x), F(sp[s].y + pp[p].y));
		_snek_draw_path_sdraw (path, sp[s].x + pp[p].x, sp[s].y + pp[p].y);
	    }
	    break;
	}
	
	if (inc == -1)
	    break;
	
	/* reach the end of the path?  Go back the other way now */
	inc = -1;
	ptarget = start;
	starget = 0;
    }
    snek_draw_path_close (path);
}

void
snek_draw_path_convolve (snek_draw_path_t	*path,
		    snek_draw_path_t	*stroke,
		    snek_draw_path_t	*pen)
{
    int		p;
    int		s;
    snek_draw_path_t	*hull = snek_draw_path_convex_hull (pen);

    p = 0;
    for (s = 0; s <= stroke->nsublen; s++)
    {
	int sublen;
	int npoints;

	if (s == stroke->nsublen)
	    sublen = stroke->npoints;
	else
	    sublen = stroke->sublen[s];
	npoints = sublen - p;
	if (npoints > 1)
	{
	    snek_draw_path_t	subpath;

	    subpath.points = stroke->points + p;
	    subpath.npoints = npoints;
	    subpath.sublen = 0;
	    subpath.nsublen = 0;
	    _snek_draw_subpath_convolve (path, &subpath, hull);
	    p = sublen;
	}
    }
    snek_draw_path_destroy (hull);
}
