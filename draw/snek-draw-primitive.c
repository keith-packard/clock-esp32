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

#define __inline

static snek_draw_argb32_t __inline
in_over (snek_draw_argb32_t	dst,
	 snek_draw_argb32_t	src,
	 snek_draw_a8_t	msk)
{
    uint16_t	t1, t2, t3, t4;
    snek_draw_a8_t	a;

    switch (msk) {
    case 0:
	return dst;
    case 0xff:
	break;
    default:
	src = (snek_draw_in(src,0,msk,t1) |
	       snek_draw_in(src,8,msk,t2) |
	       snek_draw_in(src,16,msk,t3) |
	       snek_draw_in(src,24,msk,t4));
	break;
    }
    if (!src)
	return dst;
    a = ~(src >> 24);
    switch (a) {
    case 0:
	return src;
    case 0xff:
	dst = (snek_draw_add (src, dst, 0, t1) |
	       snek_draw_add (src, dst, 8, t2) |
	       snek_draw_add (src, dst, 16, t3) |
	       snek_draw_add (src, dst, 24, t4));
	break;
    default:
	dst = (snek_draw_over (src, dst, 0, a, t1) |
	       snek_draw_over (src, dst, 8, a, t2) |
	       snek_draw_over (src, dst, 16, a, t3) |
	       snek_draw_over (src, dst, 24, a, t4));
	break;
    }
    return dst;
}

static snek_draw_argb32_t __inline
in (snek_draw_argb32_t   src,
    snek_draw_a8_t	    msk)
{
    uint16_t	t1, t2, t3, t4;

    return (snek_draw_in(src,0,msk,t1) |
	    snek_draw_in(src,8,msk,t2) |
	    snek_draw_in(src,16,msk,t3) |
	    snek_draw_in(src,24,msk,t4));
}

static snek_draw_argb32_t __inline
over (snek_draw_argb32_t	dst,
      snek_draw_argb32_t	src)
{
    uint16_t	t1, t2, t3, t4;
    snek_draw_a8_t	a;

    if (!src)
	return dst;
    a = ~(src >> 24);
    switch (a) {
    case 0:
	return src;
    case 0xff:
	dst = (snek_draw_add (src, dst, 0, t1) |
	       snek_draw_add (src, dst, 8, t2) |
	       snek_draw_add (src, dst, 16, t3) |
	       snek_draw_add (src, dst, 24, t4));
	break;
    default:
	dst = (snek_draw_over (src, dst, 0, a, t1) |
	       snek_draw_over (src, dst, 8, a, t2) |
	       snek_draw_over (src, dst, 16, a, t3) |
	       snek_draw_over (src, dst, 24, a, t4));
	break;
    }
    return dst;
}

static snek_draw_argb32_t __inline
rgb16_to_argb32 (snek_draw_rgb16_t v)
{
    return snek_draw_rgb16_to_argb32(v);
}

static snek_draw_argb32_t __inline
a8_to_argb32 (snek_draw_a8_t v)
{
    return v << 24;
}

static snek_draw_rgb16_t __inline
argb32_to_rgb16 (snek_draw_argb32_t v)
{
    return snek_draw_argb32_to_rgb16 (v);
}

static snek_draw_a8_t __inline
argb32_to_a8 (snek_draw_argb32_t v)
{
    return v >> 24;
}

/*
 * Naming convention
 *
 *  _snek_draw_<src>_in_<msk>_op_<dst>
 *
 * Use 'c' for constant
 */

#define dst_argb32_get	    (*dst.argb32)
#define dst_argb32_set	    (*dst.argb32++) =
#define dst_rgb16_get	    (rgb16_to_argb32(*dst.rgb16))
#define dst_rgb16_set	    (*dst.rgb16++) = argb32_to_rgb16
#define dst_a8_get	    (a8_to_argb32(*dst.a8))
#define dst_a8_set	    (*dst.a8++) = argb32_to_a8

#define src_c		    (src.c)
#define src_argb32	    (*src.p.argb32++)
#define src_rgb16	    (rgb16_to_argb32(*src.p.rgb16++))
#define src_a8		    (a8_to_argb32(*src.p.a8++))

#define msk_c		    (argb32_to_a8 (msk.c))
#define msk_argb32	    (argb32_to_a8 (*msk.p.argb32++))
#define msk_rgb16	    (0xff)
#define msk_a8		    (*msk.p.a8++)

#define cat2(a,b) a##b
#define cat3(a,b,c) a##b##c
#define cat4(a,b,c,d) a##b##c##d
#define cat6(a,b,c,d,e,f) a##b##c##d##e##f

#define _snek_draw_in_op_name(src,op,msk,dst) cat6(_snek_draw_,src,_in_,msk,op,dst)

#define _snek_draw_op_name(src,op,dst) cat4(_snek_draw_,src,op,dst)

#define make_snek_draw_in_over(__dst,__src,__msk)			\
	void								\
	_snek_draw_in_op_name(__src,_over_,__msk,__dst)(snek_draw_pointer_t   dst, \
							snek_draw_source_u    src, \
							snek_draw_source_u    msk, \
							int		    width) \
	{								\
		snek_draw_argb32_t   dst32;				\
		snek_draw_argb32_t   src32;				\
		snek_draw_a8_t	    msk8;				\
		(void) msk;						\
		while (width--) {					\
			dst32 = cat3(dst_,__dst,_get);			\
			src32 = cat2(src_,__src);			\
			msk8 = cat2(msk_,__msk);			\
			dst32 = in_over (dst32, src32, msk8);		\
			cat3(dst_,__dst,_set) (dst32);			\
		}							\
	}

#define make_snek_draw_in_source(__dst,__src,__msk)			\
	void								\
	_snek_draw_in_op_name(__src,_source_,__msk,__dst)(snek_draw_pointer_t	dst, \
							  snek_draw_source_u	src, \
							  snek_draw_source_u	msk, \
							  int		width) \
	{								\
		snek_draw_argb32_t   dst32;				\
		snek_draw_argb32_t   src32;				\
		snek_draw_a8_t	    msk8;				\
		(void) msk;						\
		while (width--) {					\
			src32 = cat2(src_,__src);			\
			msk8 = cat2(msk_,__msk);			\
			dst32 = in (src32, msk8);			\
			cat3(dst_,__dst,_set) (dst32);			\
		}							\
	}

#define make_snek_draw_in_op_msks(op,dst,src) \
cat2(make_snek_draw_in_,op)(dst,src,argb32) \
cat2(make_snek_draw_in_,op)(dst,src,rgb16) \
cat2(make_snek_draw_in_,op)(dst,src,a8) \
cat2(make_snek_draw_in_,op)(dst,src,c)

#define make_snek_draw_in_op_srcs_msks(op,dst) \
make_snek_draw_in_op_msks(op,dst,argb32) \
make_snek_draw_in_op_msks(op,dst,rgb16) \
make_snek_draw_in_op_msks(op,dst,a8) \
make_snek_draw_in_op_msks(op,dst,c)

#define make_snek_draw_in_op_dsts_srcs_msks(op) \
make_snek_draw_in_op_srcs_msks(op,argb32) \
make_snek_draw_in_op_srcs_msks(op,rgb16) \
make_snek_draw_in_op_srcs_msks(op,a8)

make_snek_draw_in_op_dsts_srcs_msks(over)
make_snek_draw_in_op_dsts_srcs_msks(source)

#define make_snek_draw_over(__dst,__src) \
void \
_snek_draw_op_name(__src,_over_,__dst) (snek_draw_pointer_t   dst, \
				   snek_draw_source_u    src, \
				   int		    width) \
{ \
    snek_draw_argb32_t   dst32; \
    snek_draw_argb32_t   src32; \
    while (width--) { \
	dst32 = cat3(dst_,__dst,_get); \
	src32 = cat2(src_,__src); \
	dst32 = over (dst32, src32); \
	cat3(dst_,__dst,_set) (dst32); \
    } \
}

#define make_snek_draw_source(__dst,__src) \
void \
_snek_draw_op_name(__src,_source_,__dst) (snek_draw_pointer_t dst, \
				     snek_draw_source_u  src, \
				     int	    width) \
{ \
    snek_draw_argb32_t   dst32; \
    snek_draw_argb32_t   src32; \
    while (width--) { \
	src32 = cat2(src_,__src); \
	dst32 = src32; \
	cat3(dst_,__dst,_set) (dst32); \
    } \
}

#define make_snek_draw_op_srcs(op,dst) \
cat2(make_snek_draw_,op)(dst,argb32) \
cat2(make_snek_draw_,op)(dst,rgb16) \
cat2(make_snek_draw_,op)(dst,a8) \
cat2(make_snek_draw_,op)(dst,c)

#define make_snek_draw_op_dsts_srcs(op) \
make_snek_draw_op_srcs(op,argb32) \
make_snek_draw_op_srcs(op,rgb16) \
make_snek_draw_op_srcs(op,a8)

make_snek_draw_op_dsts_srcs(over)
make_snek_draw_op_dsts_srcs(source)
