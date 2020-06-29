/*
 * Copyright (c) 2020 Nordic Semiconductor ASA
 *
 * SPDX-License-Identifier: LicenseRef-BSD-5-Clause-Nordic
 */

#include <zephyr.h>
#include <device.h>

#include "awtk.h"
#include "awtk_tp_poll.h"

#define POLL_INTERVAL	K_MSEC(20)

#define POLL_FIFO_CNT	2

typedef struct {
	void *fifo_internal;
	tp_poll_pos_t tp_pos;
} pos_fifo_t;

static pos_fifo_t m_pos_poll[POLL_FIFO_CNT];
static K_FIFO_DEFINE(m_fifo_free);
static K_FIFO_DEFINE(m_fifo_used);

static struct k_delayed_work m_tp_poll;

static void tp_poll_work_fn(struct k_work *work);

void tp_poll_init(void)
{
	u32_t i;

	for (i = 0; i < POLL_FIFO_CNT; i++) {
		k_fifo_put(&m_fifo_free, m_pos_poll + i);
	}

	touch_ft6206_init();

	k_delayed_work_init(&m_tp_poll, tp_poll_work_fn);
	k_delayed_work_submit(&m_tp_poll, POLL_INTERVAL);
}

int tp_poll_get_pos(tp_poll_pos_t *p_pos)
{
	pos_fifo_t *p_fifo;

	p_fifo = k_fifo_get(&m_fifo_used, K_NO_WAIT);

	if (p_fifo != NULL) {
		*p_pos = p_fifo->tp_pos;
		k_fifo_put(&m_fifo_free, p_fifo);
	}
	
	return (p_fifo != NULL) ? 0 : -1;
}

static void tp_poll_work_fn(struct k_work *work)
{
	static tp_poll_pos_t tp_poll_pos_0;
	pos_fifo_t *p_fifo;

	p_fifo = k_fifo_get(&m_fifo_free, K_NO_WAIT);
	if (p_fifo != NULL) {
		touch_pos_t touch_pos = touch_ft6206_get();

		/* Map touch panel position to screen position. */
		p_fifo->tp_pos.x = 320 - touch_pos.y;
		p_fifo->tp_pos.y = touch_pos.x;
		p_fifo->tp_pos.z = touch_pos.z;

		if (!p_fifo->tp_pos.z && !tp_poll_pos_0.z) {
			/* Touch panel is idle. Do not report. */
			k_fifo_put(&m_fifo_free, p_fifo);
		} else {
			tp_poll_pos_0 = p_fifo->tp_pos;
			k_fifo_put(&m_fifo_used, p_fifo);
		}
	}

	k_delayed_work_submit(&m_tp_poll, POLL_INTERVAL);
}
