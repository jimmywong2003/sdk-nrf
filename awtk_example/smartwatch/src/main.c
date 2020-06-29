/*
 * Copyright (c) 2020 Nordic Semiconductor ASA
 *
 * SPDX-License-Identifier: LicenseRef-BSD-5-Clause-Nordic
 */

#include <zephyr.h>
#include <drivers/display.h>
#include "awtk.h"
#include "assets.h"
#include "awtk_platform.h"

extern ret_t application_init(void);
extern ret_t application_exit(void);

void main(void)
{
	if (platform_init()) {
		return;
	}

	struct device *display_dev = get_display_dev();
	struct display_capabilities cap;

	display_get_capabilities(display_dev, &cap);

	tk_init(cap.x_resolution, cap.y_resolution, APP_MOBILE, NULL, NULL);

	assets_init();

	tk_ext_widgets_init();

	application_init();

	tk_run();

	application_exit();
}
