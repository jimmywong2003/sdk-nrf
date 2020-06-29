/*
 * Copyright (c) 2020 Nordic Semiconductor ASA
 *
 * SPDX-License-Identifier: LicenseRef-BSD-5-Clause-Nordic
 */

#include <zephyr.h>

#include "awtk.h"
#include "awtk_date_time.h"

static ret_t date_time_get_now_impl(date_time_t *dt);
static ret_t date_time_set_now_impl(date_time_t *dt);
static ret_t date_time_from_time_impl(date_time_t *dt, uint64_t timeval);

static const date_time_vtable_t m_date_time_vtable = {
	date_time_get_now_impl,
	date_time_set_now_impl,
	date_time_from_time_impl
};

static const u8_t m_mon_day[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

static u64_t m_base_ms;

static date_time_t m_date_cache;
static u64_t m_date_sec_cache;
static u64_t m_sec_cache;

void platform_date_init(void)
{
	date_time_t some_date;

	/* Initiate date to 2020-06-24 12:00:00. */
	some_date.year   = 2020;
	some_date.month  =    6;
	some_date.day    =   24;
	some_date.wday   =    3;
	some_date.hour   =   12;
	some_date.minute =    0;
	some_date.second =    0;
	date_time_set_now_impl(&some_date);

	date_time_global_init_ex(&m_date_time_vtable);
}

static void get_hhmmss_from_sec(date_time_t *dt, uint64_t second)
{
	u64_t timesec;
	u64_t timemin;
	u64_t timehr;

	timesec = second;
	timemin = timesec / 60;
	timehr  = timemin / 60;
	timesec = timesec % 60;
	timemin = timemin % 60;
	timehr  = timehr  % 24;

	dt->second = timesec;
	dt->minute = timemin;
	dt->hour   = timehr;
}

static void get_date_time_from_sec(date_time_t *dt, uint64_t second)
{
	u64_t timeday;
	u64_t timemon;
	u64_t time1yr;
	u64_t time4yr;

	get_hhmmss_from_sec(dt, second);

	timeday = second / (24U * 3600U);
	dt->wday = (6 + timeday) % 7;

	time4yr = timeday / 1461;
	timeday = timeday % 1461;
	time1yr = time4yr * 4;
	if (timeday >= 366) {
		timeday -= 366;
		time1yr++;

		while (timeday >= 365) {
			timeday -= 365;
			time1yr++;
		}
	}
	for (timemon = 0; timemon < 12; timemon++) {
		u8_t mon_day = m_mon_day[timemon];

		if (timemon == 1 && !(time1yr % 4)) {
			/* Febrary of leap year */
			mon_day++;
		}

		if (timeday < mon_day) {
			break;
		} else {
			timeday -= mon_day;
		}
	}

	dt->day    = timeday + 1;
	dt->month  = timemon + 1;
	dt->year   = 2000 + time1yr;
}

static u64_t get_sec_since_yr2000(const date_time_t *dt)
{
	u64_t timesec;
	u64_t timeday;
	u64_t timemon;
	u64_t time1yr;
	u64_t time4yr;
	bool leap_yr;

	timesec  = (u64_t)dt->second;
	timesec += (u64_t)dt->minute * 60U;
	timesec += (u64_t)dt->hour * 3600U;

	/* Calculate the number of days elapsed. */
	time1yr = dt->year - 2000U;
	time4yr = time1yr / 4U;
	time1yr = (time1yr % 4U);
	timeday = time4yr * 1461U;
	if (time1yr > 0) {
		time1yr--;
		timeday += 366U;
		while (time1yr > 0) {
			time1yr--;
			timeday += 365U;
		}
	}
	leap_yr = (!(dt->year % 4));
	for (timemon = 0; timemon < dt->month - 1; timemon++) {
		timeday += m_mon_day[timemon];
		if (timemon == 1 && leap_yr) {
			timeday++;
		}
	}
	timeday += (dt->day - 1);

	timesec += timeday * 24U * 3600U;

	return timesec;
}

static void cache_date_hhmmss(const date_time_t *dt)
{
	m_date_cache.hour   = dt->hour;
	m_date_cache.minute = dt->minute;
	m_date_cache.second = dt->second;
}

static void cache_date_sec(const date_time_t *dt)
{
	m_date_cache.year   = dt->year;
	m_date_cache.month  = dt->month;
	m_date_cache.day    = dt->day;
	m_date_cache.wday   = dt->wday;
	m_date_cache.hour   = 0;
	m_date_cache.minute = 0;
	m_date_cache.second = 0;
	m_date_sec_cache = get_sec_since_yr2000(&m_date_cache);

	cache_date_hhmmss(dt);
}

static ret_t date_time_from_time_impl(date_time_t *dt, uint64_t timeval)
{
	u64_t time_sec = timeval / 1000;

	if (time_sec == m_sec_cache) {
		*dt = m_date_cache;
	} else if (time_sec >= m_date_sec_cache && time_sec < m_date_sec_cache + 24U * 3600U) {
		m_sec_cache = time_sec;
		dt->year  = m_date_cache.year;
		dt->month = m_date_cache.month;
		dt->day   = m_date_cache.day;
		dt->wday  = m_date_cache.wday;
		get_hhmmss_from_sec(dt, time_sec);
		cache_date_hhmmss(dt);
	} else {
		m_sec_cache = time_sec;
		get_date_time_from_sec(dt, time_sec);
		cache_date_sec(dt);
	}

	return RET_OK;
}

static ret_t date_time_get_now_impl(date_time_t *dt)
{
	u64_t now_ms = m_base_ms + get_time_ms64();

	return date_time_from_time_impl(dt, now_ms);
}

static ret_t date_time_set_now_impl(date_time_t *dt)
{
	ret_t err;
	u64_t time_ms;

	if (dt->year < 2000U || dt-> year > 2099U) {
		err = RET_BAD_PARAMS;
	} else {
		m_sec_cache = get_sec_since_yr2000(dt);

		time_ms = m_sec_cache * 1000U;

		m_base_ms = time_ms - get_time_ms64();

		/* a cache to lower runtime load */
		cache_date_sec(dt);

		err = RET_OK;
	}

	return err;
}
