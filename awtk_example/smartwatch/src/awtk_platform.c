/*
 * Copyright (c) 2020 Nordic Semiconductor ASA
 *
 * SPDX-License-Identifier: LicenseRef-BSD-5-Clause-Nordic
 */

#include <stdlib.h>
#include <zephyr.h>
#include <device.h>
#include <drivers/display.h>

#include "awtk.h"
#include "awtk_platform.h"
#include "awtk_tp_poll.h"
#include "awtk_date_time.h"
#include "main_loop/main_loop_simple.h"
#include "lcd/lcd_mem_fragment.h"

#ifndef HAS_STD_MALLOC
/* Memory heap dedicated to AWTK. */
static u32_t m_heap_mem[32 * 1024];
#endif

static struct device *m_display_dev;

static void fill_screen(struct device *display_dev, u8_t *p_rgb)
{
	struct display_capabilities cap;
	u8_t *p_buff;

	display_get_capabilities(display_dev, &cap);

#ifndef HAS_STD_MALLOC
	if (sizeof(m_heap_mem) < 2 * cap.x_resolution) {
		return;
	}

	p_buff = (u8_t *)m_heap_mem;
#else
	p_buff = malloc(2 * cap.x_resolution);
#endif
	if (p_buff == NULL) {
		return;
	}

	struct display_buffer_descriptor buf_desc;
	u16_t i;
	u16_t rgb = (*(p_rgb + 2) >> 3) | ((*(p_rgb + 1) >> 2) << 5) | ((*(p_rgb + 0) >> 3) << 11);

	for (i = 0; i < cap.x_resolution; i++) {
		*(p_buff + i * 2 + 0) = (rgb >> 8) & 0xFF;
		*(p_buff + i * 2 + 1) = (rgb     ) & 0xFF;
	}

	buf_desc.pitch = cap.x_resolution;
	buf_desc.width = cap.x_resolution;
	buf_desc.height = 1;
	buf_desc.buf_size = sizeof(2 * cap.x_resolution);

	for (i = 0; i < cap.y_resolution; i++) {
		display_write(display_dev, 0, i, &buf_desc, p_buff);
	}

#ifdef HAS_STD_MALLOC
	free(p_buff);
#endif
}

struct device *get_display_dev(void)
{
	return m_display_dev;
}

int platform_init(void)
{
	m_display_dev = device_get_binding(DT_LABEL(DT_INST(0, ilitek_ili9340)));

	return (m_display_dev != NULL) ? 0 : -ENODEV;
}

ret_t platform_prepare(void)
{
	u8_t rgb[3] = {0x0, 0x0, 0x0};

	display_blanking_on(m_display_dev);

	fill_screen(m_display_dev, rgb);

	display_blanking_off(m_display_dev);

	tp_poll_init();

#ifndef HAS_STD_MALLOC
	tk_mem_init(m_heap_mem, sizeof(m_heap_mem));
#endif

	platform_date_init();

	return RET_OK;
}

static lcd_t *platform_create_lcd(wh_t w, wh_t h)
{
	return lcd_mem_fragment_create(w, h);
}

static ret_t platform_disaptch_input(main_loop_t *l)
{
	static tp_poll_pos_t touch_pos_0;
	tp_poll_pos_t touch_pos;

	while (!tp_poll_get_pos(&touch_pos)) {
		if (touch_pos.z) {
			if (touch_pos.z != touch_pos_0.z ||
			    touch_pos.x != touch_pos_0.x ||
			    touch_pos.y != touch_pos_0.y) {
				main_loop_post_pointer_event(l, TRUE, touch_pos.x, touch_pos.y);
			}
		}
		else if (!touch_pos.z && touch_pos_0.z) {
			main_loop_post_pointer_event(l, FALSE, touch_pos_0.x, touch_pos_0.y);
		}

		touch_pos_0 = touch_pos;
	}

	return RET_OK;
}

#include "main_loop/main_loop_raw.inc"

#include "tkc/fs.h"

fs_t *os_fs(void)
{
	return NULL;
}
