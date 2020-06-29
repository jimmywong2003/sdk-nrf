/*
 * Copyright (c) 2020 Nordic Semiconductor ASA
 *
 * SPDX-License-Identifier: LicenseRef-BSD-5-Clause-Nordic
 */

#ifndef __AWTK_PLATFORM_H__
#define __AWTK_PLATFORM_H__

#include <zephyr.h>

#ifdef __cplusplus
extern "C" {
#endif

int platform_init(void);

struct device *get_display_dev(void);

#ifdef __cplusplus
}
#endif

#endif
