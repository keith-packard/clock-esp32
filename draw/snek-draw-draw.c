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

/* op, src, dst */
static snek_draw_src_op  comp2[2][4][3] = {
    {	/* OVER */
	{   /* A8 */
	    _snek_draw_a8_over_a8,
	    _snek_draw_a8_over_rgb16,
	    _snek_draw_a8_over_argb32,
	},
	{   /* RGB16 */
	    _snek_draw_rgb16_over_a8,
	    _snek_draw_rgb16_over_rgb16,
	    _snek_draw_rgb16_over_argb32,
	},
	{   /* ARGB32 */
	    _snek_draw_argb32_over_a8,
	    _snek_draw_argb32_over_rgb16,
	    _snek_draw_argb32_over_argb32,
	},
	{   /* C */
	    _snek_draw_c_over_a8,
	    _snek_draw_c_over_rgb16,
	    _snek_draw_c_over_argb32,
	}
    },
    {	/* SOURCE */
	{   /* A8 */
	    _snek_draw_a8_source_a8,
	    _snek_draw_a8_source_rgb16,
	    _snek_draw_a8_source_argb32,
	},
	{   /* RGB16 */
	    _snek_draw_rgb16_source_a8,
	    _snek_draw_rgb16_source_rgb16,
	    _snek_draw_rgb16_source_argb32,
	},
	{   /* ARGB32 */
	    _snek_draw_argb32_source_a8,
	    _snek_draw_argb32_source_rgb16,
	    _snek_draw_argb32_source_argb32,
	},
	{   /* C */
	    _snek_draw_c_source_a8,
	    _snek_draw_c_source_rgb16,
	    _snek_draw_c_source_argb32,
	}
    }
};

/* op, src, msk, dst */
static snek_draw_src_msk_op	comp3[2][4][4][3] = {
    {	/* OVER */
	{   /* A8 */
	    {	/* A8 */
		_snek_draw_a8_in_a8_over_a8,
		_snek_draw_a8_in_a8_over_rgb16,
		_snek_draw_a8_in_a8_over_argb32,
	    },
	    {	/* RGB16 */
		_snek_draw_a8_in_rgb16_over_a8,
		_snek_draw_a8_in_rgb16_over_rgb16,
		_snek_draw_a8_in_rgb16_over_argb32,
	    },
	    {	/* ARGB32 */
		_snek_draw_a8_in_argb32_over_a8,
		_snek_draw_a8_in_argb32_over_rgb16,
		_snek_draw_a8_in_argb32_over_argb32,
	    },
	    {	/* C */
		_snek_draw_a8_in_c_over_a8,
		_snek_draw_a8_in_c_over_rgb16,
		_snek_draw_a8_in_c_over_argb32,
	    },
	},
	{   /* RGB16 */
	    {	/* A8 */
		_snek_draw_rgb16_in_a8_over_a8,
		_snek_draw_rgb16_in_a8_over_rgb16,
		_snek_draw_rgb16_in_a8_over_argb32,
	    },
	    {	/* RGB16 */
		_snek_draw_rgb16_in_rgb16_over_a8,
		_snek_draw_rgb16_in_rgb16_over_rgb16,
		_snek_draw_rgb16_in_rgb16_over_argb32,
	    },
	    {	/* ARGB32 */
		_snek_draw_rgb16_in_argb32_over_a8,
		_snek_draw_rgb16_in_argb32_over_rgb16,
		_snek_draw_rgb16_in_argb32_over_argb32,
	    },
	    {	/* C */
		_snek_draw_rgb16_in_c_over_a8,
		_snek_draw_rgb16_in_c_over_rgb16,
		_snek_draw_rgb16_in_c_over_argb32,
	    },
	},
	{   /* ARGB32 */
	    {	/* A8 */
		_snek_draw_argb32_in_a8_over_a8,
		_snek_draw_argb32_in_a8_over_rgb16,
		_snek_draw_argb32_in_a8_over_argb32,
	    },
	    {	/* RGB16 */
		_snek_draw_argb32_in_rgb16_over_a8,
		_snek_draw_argb32_in_rgb16_over_rgb16,
		_snek_draw_argb32_in_rgb16_over_argb32,
	    },
	    {	/* ARGB32 */
		_snek_draw_argb32_in_argb32_over_a8,
		_snek_draw_argb32_in_argb32_over_rgb16,
		_snek_draw_argb32_in_argb32_over_argb32,
	    },
	    {	/* C */
		_snek_draw_argb32_in_c_over_a8,
		_snek_draw_argb32_in_c_over_rgb16,
		_snek_draw_argb32_in_c_over_argb32,
	    },
	},
	{   /* C */
	    {	/* A8 */
		_snek_draw_c_in_a8_over_a8,
		_snek_draw_c_in_a8_over_rgb16,
		_snek_draw_c_in_a8_over_argb32,
	    },
	    {	/* RGB16 */
		_snek_draw_c_in_rgb16_over_a8,
		_snek_draw_c_in_rgb16_over_rgb16,
		_snek_draw_c_in_rgb16_over_argb32,
	    },
	    {	/* ARGB32 */
		_snek_draw_c_in_argb32_over_a8,
		_snek_draw_c_in_argb32_over_rgb16,
		_snek_draw_c_in_argb32_over_argb32,
	    },
	    {	/* C */
		_snek_draw_c_in_c_over_a8,
		_snek_draw_c_in_c_over_rgb16,
		_snek_draw_c_in_c_over_argb32,
	    },
	},
    },
    {	/* SOURCE */
	{   /* A8 */
	    {	/* A8 */
		_snek_draw_a8_in_a8_source_a8,
		_snek_draw_a8_in_a8_source_rgb16,
		_snek_draw_a8_in_a8_source_argb32,
	    },
	    {	/* RGB16 */
		_snek_draw_a8_in_rgb16_source_a8,
		_snek_draw_a8_in_rgb16_source_rgb16,
		_snek_draw_a8_in_rgb16_source_argb32,
	    },
	    {	/* ARGB32 */
		_snek_draw_a8_in_argb32_source_a8,
		_snek_draw_a8_in_argb32_source_rgb16,
		_snek_draw_a8_in_argb32_source_argb32,
	    },
	    {	/* C */
		_snek_draw_a8_in_c_source_a8,
		_snek_draw_a8_in_c_source_rgb16,
		_snek_draw_a8_in_c_source_argb32,
	    },
	},
	{   /* RGB16 */
	    {	/* A8 */
		_snek_draw_rgb16_in_a8_source_a8,
		_snek_draw_rgb16_in_a8_source_rgb16,
		_snek_draw_rgb16_in_a8_source_argb32,
	    },
	    {	/* RGB16 */
		_snek_draw_rgb16_in_rgb16_source_a8,
		_snek_draw_rgb16_in_rgb16_source_rgb16,
		_snek_draw_rgb16_in_rgb16_source_argb32,
	    },
	    {	/* ARGB32 */
		_snek_draw_rgb16_in_argb32_source_a8,
		_snek_draw_rgb16_in_argb32_source_rgb16,
		_snek_draw_rgb16_in_argb32_source_argb32,
	    },
	    {	/* C */
		_snek_draw_rgb16_in_c_source_a8,
		_snek_draw_rgb16_in_c_source_rgb16,
		_snek_draw_rgb16_in_c_source_argb32,
	    },
	},
	{   /* ARGB32 */
	    {	/* A8 */
		_snek_draw_argb32_in_a8_source_a8,
		_snek_draw_argb32_in_a8_source_rgb16,
		_snek_draw_argb32_in_a8_source_argb32,
	    },
	    {	/* RGB16 */
		_snek_draw_argb32_in_rgb16_source_a8,
		_snek_draw_argb32_in_rgb16_source_rgb16,
		_snek_draw_argb32_in_rgb16_source_argb32,
	    },
	    {	/* ARGB32 */
		_snek_draw_argb32_in_argb32_source_a8,
		_snek_draw_argb32_in_argb32_source_rgb16,
		_snek_draw_argb32_in_argb32_source_argb32,
	    },
	    {	/* C */
		_snek_draw_argb32_in_c_source_a8,
		_snek_draw_argb32_in_c_source_rgb16,
		_snek_draw_argb32_in_c_source_argb32,
	    },
	},
	{   /* C */
	    {	/* A8 */
		_snek_draw_c_in_a8_source_a8,
		_snek_draw_c_in_a8_source_rgb16,
		_snek_draw_c_in_a8_source_argb32,
	    },
	    {	/* RGB16 */
		_snek_draw_c_in_rgb16_source_a8,
		_snek_draw_c_in_rgb16_source_rgb16,
		_snek_draw_c_in_rgb16_source_argb32,
	    },
	    {	/* ARGB32 */
		_snek_draw_c_in_argb32_source_a8,
		_snek_draw_c_in_argb32_source_rgb16,
		_snek_draw_c_in_argb32_source_argb32,
	    },
	    {	/* C */
		_snek_draw_c_in_c_source_a8,
		_snek_draw_c_in_c_source_rgb16,
		_snek_draw_c_in_c_source_argb32,
	    },
	},
    }
};


#define operand_index(o)    ((o)->source_kind == SNEK_DRAW_SOLID ? 3 : o->u.pixmap->format)

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
		     snek_draw_coord_t		height)
{
    snek_draw_coord_t    iy;
    snek_draw_coord_t    left, top, right, bottom;
    snek_draw_coord_t    sdx, sdy;
    snek_draw_source_u   s;

    left = dst_x;
    top = dst_y;
    right = dst_x + width;
    bottom = dst_y + height;

    /* clip */
    if (left < 0)
	    left = 0;
    if  (top < 0)
	    top = 0;
    if (right > dst->width)
	    right = dst->width;
    if (bottom > dst->height)
	    bottom = dst->height;

    if (left >= right || top >= bottom)
	return;

    if (src->source_kind != SNEK_DRAW_PIXMAP)
        s.c = src->u.argb;

    sdx = src_x - dst_x;
    sdy = src_y - dst_y;

    if (msk)
    {
	snek_draw_src_msk_op	op;
	snek_draw_source_u   m;
	snek_draw_coord_t	mdx, mdy;

	if (msk->source_kind != SNEK_DRAW_PIXMAP)
	    s.c = msk->u.argb;

	mdx = msk_x - dst_x;
	mdy = msk_y - dst_y;

	op = comp3[operator][operand_index(src)][operand_index(msk)][dst->format];
	for (iy = top; iy < bottom; iy++)
	{
	    if (src->source_kind == SNEK_DRAW_PIXMAP)
		s.p = snek_draw_pixmap_pointer (src->u.pixmap, left+sdx, iy+sdy);
	    if (msk->source_kind == SNEK_DRAW_PIXMAP)
		m.p = snek_draw_pixmap_pointer (msk->u.pixmap, left+mdx, iy+mdy);
	    (*op) (snek_draw_pixmap_pointer (dst, left, iy),
		   s, m, right - left);
	}
    }
    else
    {
	snek_draw_src_op	op;

	op = comp2[operator][operand_index(src)][dst->format];

	for (iy = top; iy < bottom; iy++)
	{
	    if (src->source_kind == SNEK_DRAW_PIXMAP)
		s.p = snek_draw_pixmap_pointer (src->u.pixmap, left+sdx, iy+sdy);
	    (*op) (snek_draw_pixmap_pointer (dst, left, iy),
		   s, right - left);
	}
    }
    snek_draw_pixmap_damage (dst, left, top, right, bottom);
}

/*
 * array primary    index is OVER SOURCE
 * array secondary  index is ARGB32 RGB16 A8
 */
static snek_draw_src_op  fill[2][3] = {
    {	/* OVER */
	_snek_draw_c_over_a8,
	_snek_draw_c_over_rgb16,
	_snek_draw_c_over_argb32,
    },
    {	/* SOURCE */
	_snek_draw_c_source_a8,
	_snek_draw_c_source_rgb16,
	_snek_draw_c_source_argb32,
    }
};

void
snek_draw_fill (snek_draw_pixmap_t	*dst,
		snek_draw_argb32_t	pixel,
		snek_draw_operator_t	operator,
		snek_draw_coord_t	left,
		snek_draw_coord_t	top,
		snek_draw_coord_t	right,
		snek_draw_coord_t	bottom)
{
    snek_draw_src_op	    op;
    snek_draw_source_u   src;
    snek_draw_coord_t    iy;

    if (left < 0)
	    left = 0;
    if (right > dst->width)
	    right = dst->width;
    if (top < 0)
	    top = 0;
    if (bottom > dst->height)
	    bottom = dst->height;

    if (right <= left || bottom <= top)
	    return;

    src.c = pixel;
    op = fill[operator][dst->format];
    for (iy = top; iy < bottom; iy++)
	(*op) (snek_draw_pixmap_pointer (dst, left, iy), src, right - left);
    snek_draw_pixmap_damage (dst, left, top, right, bottom);
}
