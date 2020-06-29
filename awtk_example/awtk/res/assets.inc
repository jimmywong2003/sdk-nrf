/*
 * Copyright (c) 2020 Nordic Semiconductor ASA
 *
 * SPDX-License-Identifier: LicenseRef-BSD-5-Clause-Nordic
 */

#include "awtk.h"
#include "base/assets_manager.h"
#ifndef WITH_FS_RES
#include "assets/default/inc/fonts/default.data"
#include "assets/default/inc/images/1.data"
#include "assets/default/inc/images/2.data"
#include "assets/default/inc/images/3.data"
#include "assets/default/inc/images/earth.data"
#include "assets/default/inc/styles/default.data"
#ifdef WITH_STB_IMAGE
#else
#endif /* WITH_STB_IMAGE */
#ifdef WITH_VGCANVAS
#endif /* WITH_VGCANVAS */
#endif /* WITH_FS_RES */

ret_t assets_init(void)
{
	assets_manager_t* am = assets_manager();

#ifdef WITH_FS_RES
	assets_manager_preload(rm, ASSET_TYPE_FONT, "default");
	assets_manager_preload(rm, ASSET_TYPE_STYLE, "default");
#else
	assets_manager_add(am, font_default);
	assets_manager_add(am, image_1);
	assets_manager_add(am, image_2);
	assets_manager_add(am, image_3);
	assets_manager_add(am, image_earth);
	assets_manager_add(am, style_default);
#ifdef WITH_STB_IMAGE
#endif /* WITH_STB_IMAGE */
#ifdef WITH_VGCANVAS
#endif /* WITH_VGCANVAS */
#endif

	tk_init_assets();

	return RET_OK;
}
