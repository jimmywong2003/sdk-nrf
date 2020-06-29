/*
 * Copyright (c) 2020 Nordic Semiconductor ASA
 *
 * SPDX-License-Identifier: LicenseRef-BSD-5-Clause-Nordic
 */

#ifndef __AWTK_TP_POLL_H__
#define __AWTK_TP_POLL_H__

#include "touch_ft6206.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef touch_pos_t tp_poll_pos_t;

void tp_poll_init(void);

int tp_poll_get_pos(tp_poll_pos_t *p_pos);

#ifdef __cplusplus
}
#endif

#endif
