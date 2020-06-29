/*
 * Copyright (c) 2020 Nordic Semiconductor ASA
 *
 * SPDX-License-Identifier: LicenseRef-BSD-5-Clause-Nordic
 */

#include <zephyr.h>

u64_t m_uptime_cnt;
s64_t m_uptime_last;

uint64_t get_time_ms64(void)
{
	s64_t uptime_delta;

	uptime_delta = k_uptime_delta(&m_uptime_last);
	m_uptime_cnt += uptime_delta;

	return m_uptime_cnt;
}

void sleep_ms(uint32_t ms)
{
	k_sleep(K_MSEC(ms));
}
