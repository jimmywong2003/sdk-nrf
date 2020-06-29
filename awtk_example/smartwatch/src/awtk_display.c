/*
 * Copyright (c) 2020 Nordic Semiconductor ASA
 *
 * SPDX-License-Identifier: LicenseRef-BSD-5-Clause-Nordic
 */

#include <zephyr.h>
#include <device.h>
#include <drivers/display.h>

#include "awtk.h"
#include "awtk_platform.h"
#include "base/pixel.h"
#include "lcd/lcd_mem_fragment.h"

typedef pixel_bgr565_t  pixel_t;
#define LCD_FORMAT      pixel_bgr565_format
#define pixel_bpp	pixel_bgr565_BPP
#define pixel_from_rgb  pixel_bgr565_from_rgb
#define pixel_from_rgba pixel_bgr565_from_rgba
#define pixel_to_rgba   pixel_bgr565_to_rgba

#define lcd_draw_bitmap_impl lcd_draw_bitmap

static void lcd_draw_bitmap(u16_t x, u16_t y, u16_t w, u16_t h, pixel_t *p)
{
	struct device *display_dev;
	struct display_buffer_descriptor buf_desc;

	buf_desc.pitch = w;
	buf_desc.width = w;
	buf_desc.height = h;
	buf_desc.buf_size = w * h * pixel_bpp;

#if LCD_FORMAT == BITMAP_FMT_BGR565
	/* ILI9341 takes a byte swap */
	u32_t i;
	u8_t *ptr = (u8_t*)p;

	for (i = 0; i < w * h; i++)
	{
		u8_t t = *(ptr + i * 2 + 1);

		*(ptr + i * 2 + 1) = *(ptr + i * 2 + 0);
		*(ptr + i * 2 + 0) = t;
	}
#endif

	display_dev = get_display_dev();
	display_write(display_dev, x, y, &buf_desc, (u8_t*)p);
}

#include "blend/pixel_ops.inc"
#include "lcd/lcd_mem_fragment.inc"
