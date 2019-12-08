/*
 * Twin - A Tiny Window System
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

#include <snek-draw.h>
#include <snek-lcd.h>
#include <stdio.h>
#include <sys/time.h>
#include <time.h>

#define D(x) (x)

#define SNEK_CLOCK_BACKGROUND	0xff3b80ae
#define SNEK_CLOCK_HOUR		0x80808080
#define SNEK_CLOCK_HOUR_OUT	0x30000000
#define SNEK_CLOCK_MINUTE	0x80808080
#define SNEK_CLOCK_MINUTE_OUT	0x30000000
#define SNEK_CLOCK_SECOND	0x80808080
#define SNEK_CLOCK_SECOND_OUT	0x30000000
#define SNEK_CLOCK_TIC		0xffbababa
#define SNEK_CLOCK_NUMBERS	0xffdedede
#define SNEK_CLOCK_WATER	0x60200000
#define SNEK_CLOCK_WATER_OUT	0x40404040
#define SNEK_CLOCK_WATER_UNDER	0x60400000
#define SNEK_CLOCK_BORDER	0xffbababa
#define SNEK_CLOCK_BORDER_WIDTH	D(0.01)

typedef struct _snek_clock {
	snek_draw_pixmap_t *pixmap;
} snek_clock_t;

#define _snek_clock_pixmap(clock)   	((clock)->pixmap)
#define _snek_clock_width(clock)	(240)
#define _snek_clock_height(clock)	(240)

static void
snek_clock_set_transform (snek_clock_t	*clock,
			  snek_draw_path_t	*path)
{
    float    scale;

    scale = (1 - SNEK_CLOCK_BORDER_WIDTH * 3) / 2;
    snek_draw_path_translate(path, 40, 0);
    snek_draw_path_scale (path, _snek_clock_width (clock) * scale,
			  _snek_clock_height (clock) * scale);

    snek_draw_path_translate (path,
			      1 + SNEK_CLOCK_BORDER_WIDTH * 3,
			      1 + SNEK_CLOCK_BORDER_WIDTH * 3);

    snek_draw_path_rotate (path, -SNEK_DRAW_ANGLE_90);
}

static void
snek_clock_hand (snek_clock_t	*clock,
		 snek_draw_angle_t	angle,
		 float	len,
		 float	fill_width,
		 float	out_width,
		 snek_draw_argb32_t	fill_pixel,
		 snek_draw_argb32_t	out_pixel)
{
    snek_draw_path_t	    *stroke = snek_draw_path_create ();
    if (!stroke)
	    return;
    snek_draw_path_t	    *pen = snek_draw_path_create ();
    if (!pen)
	    return;
    snek_draw_path_t	    *path = snek_draw_path_create ();
    if (!path)
	    return;
    snek_draw_matrix_t   m;

    snek_clock_set_transform (clock, stroke);

    snek_draw_path_rotate (stroke, angle);
    snek_draw_path_move (stroke, D(0), D(0));
    snek_draw_path_draw (stroke, len, D(0));

    m = snek_draw_path_current_matrix (stroke);
    m.m[2][0] = 0;
    m.m[2][1] = 0;
    snek_draw_path_set_matrix (pen, m);
    snek_draw_path_set_matrix (path, m);
    snek_draw_path_circle (pen, 0, 0, fill_width);
    snek_draw_path_convolve (path, stroke, pen);

    snek_draw_path_destroy (pen);
    snek_draw_path_destroy (stroke);

    snek_draw_paint_path (_snek_clock_pixmap(clock), fill_pixel, path);

    snek_draw_paint_stroke (_snek_clock_pixmap(clock), out_pixel, path, out_width);

    snek_draw_path_destroy (path);
}

static void
snek_clock_day (snek_clock_t *clock,
		int mday)
{
	char	text[3];
	snek_draw_text_metrics_t metrics;
	float	    height, width;

	sprintf(text, "%2d", mday);

	snek_draw_path_t	*path = snek_draw_path_create ();
	if (!path)
		return;
	snek_clock_set_transform(clock, path);
	snek_draw_path_rotate(path, SNEK_DRAW_ANGLE_90);
	snek_draw_path_translate(path, 0.8, 0);
	snek_draw_path_set_font_size(path, 0.25f);
	snek_draw_path_set_font_style(path, SNEK_DRAW_TEXT_UNHINTED);
	snek_draw_text_metrics_utf8(path, text, &metrics);
	height = metrics.ascent + metrics.descent;
	width = metrics.right_side_bearing - metrics.left_side_bearing;
	snek_draw_path_move (path, -width, metrics.ascent - height/2);
	snek_draw_path_utf8 (path, text);
	snek_draw_paint_path (_snek_clock_pixmap(clock), SNEK_CLOCK_WATER, path);
	snek_draw_path_destroy(path);
}

static snek_draw_angle_t
snek_clock_minute_angle (int min)
{
    return min * SNEK_DRAW_ANGLE_360 / 60;
}

static void
snek_clock_face (snek_clock_t *clock)
{
    snek_draw_path_t	    *path = snek_draw_path_create ();
    int		    m;

    if (!path)
	    return;

    snek_clock_set_transform (clock, path);

    snek_draw_path_circle (path, 0, 0, 1);

    snek_draw_paint_path (_snek_clock_pixmap(clock), SNEK_CLOCK_BACKGROUND, path);

    snek_draw_paint_stroke (_snek_clock_pixmap(clock), SNEK_CLOCK_BORDER, path, SNEK_CLOCK_BORDER_WIDTH);

    {
	snek_draw_state_t	    state = snek_draw_path_save (path);
	snek_draw_text_metrics_t metrics;
	float	    height, width;
	static char	    *label = "snek";

	snek_draw_path_empty (path);
	snek_draw_path_translate(path, -.25, 0);
	snek_draw_path_rotate (path, snek_draw_degrees_to_angle (-11) + SNEK_DRAW_ANGLE_90);
	snek_draw_path_set_font_size (path, D(0.25));
	snek_draw_path_set_font_style (path, SNEK_DRAW_TEXT_UNHINTED|SNEK_DRAW_TEXT_OBLIQUE);
	snek_draw_text_metrics_utf8 (path, label, &metrics);
	height = metrics.ascent + metrics.descent;
	width = metrics.right_side_bearing - metrics.left_side_bearing;

	snek_draw_path_move (path, -width / 2, metrics.ascent - height/2 + D(0.01));
	snek_draw_path_draw (path, width / 2, metrics.ascent - height/2 + D(0.01));
	snek_draw_paint_stroke (_snek_clock_pixmap(clock), SNEK_CLOCK_WATER_UNDER, path, D(0.02));
	snek_draw_path_empty (path);

	snek_draw_path_move (path, -width / 2 - metrics.left_side_bearing, metrics.ascent - height/2);
	snek_draw_path_utf8 (path, label);
	snek_draw_paint_path (_snek_clock_pixmap(clock), SNEK_CLOCK_WATER, path);
	snek_draw_path_restore (path, &state);
    }

    snek_draw_path_set_font_size (path, D(0.2));
    snek_draw_path_set_font_style (path, SNEK_DRAW_TEXT_UNHINTED);

    for (m = 1; m <= 60; m++)
    {
	snek_draw_state_t	state = snek_draw_path_save (path);
	snek_draw_path_rotate (path, snek_clock_minute_angle (m) + SNEK_DRAW_ANGLE_90);
        snek_draw_path_empty (path);
	if (m % 5 != 0)
	{
	    snek_draw_path_move (path, 0, -1);
	    snek_draw_path_draw (path, 0, -D(0.9));
	    snek_draw_paint_stroke (_snek_clock_pixmap(clock), SNEK_CLOCK_TIC, path, D(0.01));
	}
	else
	{
	    char		hour[3];
	    snek_draw_text_metrics_t	metrics;
	    float	width;
	    float	left;

	    sprintf (hour, "%d", m / 5);
	    snek_draw_text_metrics_utf8 (path, hour, &metrics);
	    width = metrics.right_side_bearing - metrics.left_side_bearing;
	    left = -width / 2 - metrics.left_side_bearing;
	    snek_draw_path_move (path, left, -D(0.98) + metrics.ascent);
	    snek_draw_path_utf8 (path, hour);
	    snek_draw_paint_path (_snek_clock_pixmap(clock), SNEK_CLOCK_NUMBERS, path);
	}
        snek_draw_path_restore (path, &state);
    }

    snek_draw_path_destroy (path);
}

static snek_clock_t snek_clock;

void
snek_clock_paint (struct timeval *tv)
{
    snek_draw_angle_t    second_angle, minute_angle, hour_angle;
    struct tm	    t;

    snek_clock.pixmap = &snek_lcd_pixmap;

    snek_clock_t *clock = &snek_clock;

    localtime_r(&tv->tv_sec, &t);

    snek_clock_face (clock);

    snek_clock_day(clock, t.tm_mday);

    second_angle = ((t.tm_sec * 100 + tv->tv_usec / 10000) *
		    SNEK_DRAW_ANGLE_360) / 6000;
    minute_angle = snek_clock_minute_angle (t.tm_min) + second_angle / 60;
    hour_angle = (t.tm_hour * SNEK_DRAW_ANGLE_360 + minute_angle) / 12;
    snek_clock_hand (clock, hour_angle, D(0.4), D(0.07), D(0.01),
		     SNEK_CLOCK_HOUR, SNEK_CLOCK_HOUR_OUT);
    snek_clock_hand (clock, minute_angle, D(0.8), D(0.05), D(0.01),
		     SNEK_CLOCK_MINUTE, SNEK_CLOCK_MINUTE_OUT);
    snek_clock_hand (clock, second_angle, D(0.9), D(0.01), D(0.01),
		     SNEK_CLOCK_SECOND, SNEK_CLOCK_SECOND_OUT);
}
