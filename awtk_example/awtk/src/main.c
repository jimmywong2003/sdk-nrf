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

static ret_t on_btn_close(void* ctx, event_t* e);

static ret_t on_btn_slide_h(void* ctx, event_t* e)
{
	widget_t* win = (widget_t*)ctx;

	if (e->type == EVT_CLICK) {
		window_close(win);
		win = window_create(NULL, 0, 0, 0, 0);

		widget_t* btn_close;
		btn_close = button_create(win, 220, 20, 80, 30);
		widget_set_text(btn_close, L"close");
		widget_on(btn_close, EVT_CLICK, on_btn_close, win);

		widget_t* view;
		widget_t* image;
		widget_t* slide_view;

		slide_view = slide_view_create(win, 0, 80, win->w, win->h - 80);

		view = image_create(slide_view, 0, 0, slide_view->w, slide_view->h);
		image = image_create(view, 0, 0, slide_view->w, slide_view->h);
		image_set_draw_type(image, IMAGE_DRAW_CENTER);
		image_set_image(image, "1");

		view = image_create(slide_view, 0, 0, slide_view->w, slide_view->h);
		image = image_create(view, 0, 0, slide_view->w, slide_view->h);
		image_set_draw_type(image, IMAGE_DRAW_CENTER);
		image_set_image(image, "2");

		view = image_create(slide_view, 0, 0, slide_view->w, slide_view->h);
		image = image_create(view, 0, 0, slide_view->w, slide_view->h);
		image_set_draw_type(image, IMAGE_DRAW_CENTER);
		image_set_image(image, "3");
	}

	return RET_OK;
}

static ret_t on_btn_slide_v(void* ctx, event_t* e)
{
	widget_t* win = (widget_t*)ctx;

	if (e->type == EVT_CLICK) {
		window_close(win);

		win = window_create(NULL, 0, 0, 0, 0);

		widget_t* btn_close;
		btn_close = button_create(win, 220, 20, 80, 30);
		widget_set_text(btn_close, L"close");
		widget_on(btn_close, EVT_CLICK, on_btn_close, win);

		widget_t* view;
		widget_t* image;
		widget_t* slide_view;

		slide_view = slide_view_create(win, 0, 0, win->w - 120, win->h);
		slide_view_set_vertical(slide_view, true);

		view = image_create(slide_view, 0, 0, slide_view->w, slide_view->h);
		image = image_create(view, 0, 0, slide_view->w, slide_view->h);
		image_set_draw_type(image, IMAGE_DRAW_CENTER);
		image_set_image(image, "1");

		view = image_create(slide_view, 0, 0, slide_view->w, slide_view->h);
		image = image_create(view, 0, 0, slide_view->w, slide_view->h);
		image_set_draw_type(image, IMAGE_DRAW_CENTER);
		image_set_image(image, "2");

		view = image_create(slide_view, 0, 0, slide_view->w, slide_view->h);
		image = image_create(view, 0, 0, slide_view->w, slide_view->h);
		image_set_draw_type(image, IMAGE_DRAW_CENTER);
		image_set_image(image, "3");
	}

	return RET_OK;
}

static void add_button(widget_t* slide_menu, const char* text)
{
	widget_t* b = button_create(slide_menu, 0, 0, 0, 0);
	widget_set_name(b, text);
	widget_set_text_utf8(b, text);
}

static ret_t on_btn_slide_m(void* ctx, event_t* e)
{
	widget_t* win = (widget_t*)ctx;

	if (e->type == EVT_CLICK) {
		window_close(win);

		win = window_create(NULL, 0, 0, 0, 0);

		widget_t* slide_menu;
		slide_menu = slide_menu_create(win, 10, 90, 300, 60);
		add_button(slide_menu, "1");
		add_button(slide_menu, "2");
		add_button(slide_menu, "3");
		add_button(slide_menu, "4");
		add_button(slide_menu, "5");
		add_button(slide_menu, "6");

		widget_t* btn_close;
		btn_close = button_create(win, 220, 20, 80, 30);
		widget_set_text(btn_close, L"close");
		widget_on(btn_close, EVT_CLICK, on_btn_close, win);
	}

	return RET_OK;
}

static ret_t on_btn_hello(void* ctx, event_t* e)
{
	widget_t* win = (widget_t*)ctx;

	if (e->type == EVT_CLICK) {
		window_close(win);

		win = window_create(NULL, 0, 0, 0, 0);

		widget_t* image;
		image = image_create(win, 10, 10, 24, 24);
		image_set_image(image, "earth");
		image_set_draw_type(image, IMAGE_DRAW_DEFAULT);

		widget_t* image_2;
		image_2 = image_create(win, 60, 140, 100, 73);
		image_set_image(image_2, "2");
		image_set_draw_type(image_2, IMAGE_DRAW_DEFAULT);

		widget_t* image_3;
		image_3 = image_create(win, 190, 140, 100, 73);
		image_set_image(image_3, "3");
		image_set_draw_type(image_3, IMAGE_DRAW_DEFAULT);

		widget_t *label = label_create(win, 100, 80, 100, 20);
		widget_set_text(label, L"Hello World!");

		widget_t* btn_close;
		btn_close = button_create(win, 220, 20, 80, 30);
		widget_set_text(btn_close, L"close");
		widget_on(btn_close, EVT_CLICK, on_btn_close, win);
	}

	return RET_OK;
}

static void main_window_create(void)
{
	widget_t* win = window_create(NULL, 0, 0, 0, 0);

	widget_t* btn_hello;
	btn_hello = button_create(win, 25, 25, 120, 80);
	widget_set_text(btn_hello, L"hello");
	widget_on(btn_hello, EVT_CLICK, on_btn_hello, win);

	widget_t* btn_slide_m;
	btn_slide_m = button_create(win, 175, 25, 120, 80);
	widget_set_text(btn_slide_m, L"slide_menu");
	widget_on(btn_slide_m, EVT_CLICK, on_btn_slide_m, win);
	
	widget_t* btn_slide_h;
	btn_slide_h = button_create(win, 25, 135, 120, 80);
	widget_set_text(btn_slide_h, L"slide_view h");
	widget_on(btn_slide_h, EVT_CLICK, on_btn_slide_h, win);

	widget_t* btn_slide_v;
	btn_slide_v = button_create(win, 175, 135, 120, 80);
	widget_set_text(btn_slide_v, L"slide_view v");
	widget_on(btn_slide_v, EVT_CLICK, on_btn_slide_v, win);
}

static ret_t on_btn_close(void* ctx, event_t* e)
{
	widget_t* win = (widget_t*)ctx;

	if (e->type == EVT_CLICK) {
		window_close(win);

		main_window_create();
	}

	return RET_OK;
}

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

	main_window_create();

	tk_run();
}
