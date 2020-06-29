#
# Copyright (c) 2020 Nordic Semiconductor
#
# SPDX-License-Identifier: LicenseRef-BSD-5-Clause-Nordic
#

if(CONFIG_AWTK)

FILE(GLOB awtk_base_src src/base/*.c)
FILE(GLOB awtk_tkc_src src/tkc/*.c)
FILE(GLOB awtk_widgets_src src/widgets/*.c)
FILE(GLOB awtk_layouters_src src/layouters/*.c)
FILE(GLOB awtk_ui_loader_src src/ui_loader/*.c)
FILE(GLOB awtk_xml_src src/xml/*.c)
FILE(GLOB awtk_svg_src src/svg/*.c)
FILE(GLOB awtk_clip_board_src src/clip_board/*.c)
FILE(GLOB awtk_font_loader_src src/font_loader/*.c)
FILE(GLOB awtk_blend_src src/blend/*.c)
FILE(GLOB awtk_image_loader_src src/image_loader/*.c)
FILE(GLOB awtk_designer_support_src src/designer_support/*.c)
FILE(GLOB awtk_window_animators_src src/window_animators/*.c)
FILE(GLOB awtk_dialog_highlighters_src src/dialog_highlighters/*.c)
FILE(GLOB awtk_input_method_src src/input_methods/*.c)
FILE(GLOB awtk_global_src src/awtk_global.c)
FILE(GLOB awtk_native_window_src src/native_window/native_window_raw.c)
FILE(GLOB awtk_window_manager_src src/window_manager/window_manager_default.c)
FILE(GLOB awtk_main_loop_src src/main_loop/main_loop_simple.c)
FILE(GLOB awtk_grapic_buffer_src src/graphic_buffer/graphic_buffer_default.c)
FILE(GLOB awtk_widget_animators_src src/widget_animators/*.c)
FILE(GLOB awtk_ext_widgets_src src/ext_widgets/*.c src/ext_widgets/*/*.c)

zephyr_library()
zephyr_library_sources(
  ${awtk_base_src}
  ${awtk_tkc_src}
  ${awtk_widgets_src}
  ${awtk_layouters_src}
  ${awtk_ui_loader_src}
  ${awtk_xml_src}
  ${awtk_svg_src}
  ${awtk_clip_board_src}
  ${awtk_font_loader_src}
  ${awtk_blend_src}
  ${awtk_image_loader_src}
  ${awtk_designer_support_src}
  ${awtk_window_animators_src}
  ${awtk_dialog_highlighters_src}
  ${awtk_input_method_src}
  ${awtk_global_src}
  ${awtk_native_window_src}
  ${awtk_window_manager_src}
  ${awtk_main_loop_src}
  ${awtk_grapic_buffer_src}
  ${awtk_widget_animators_src}
  ${awtk_ext_widgets_src}
)

zephyr_include_directories(src)
zephyr_include_directories(src/ext_widgets)
zephyr_include_directories(3rd)

endif()
