#
# Copyright (c) 2020 Nordic Semiconductor
#
# SPDX-License-Identifier: LicenseRef-BSD-5-Clause-Nordic
#

cmake_minimum_required(VERSION 3.13.1)

find_package(Zephyr REQUIRED HINTS $ENV{ZEPHYR_BASE})
project(smartwatch)

zephyr_compile_definitions(HAS_AWTK_CONFIG)
zephyr_compile_definitions(WATCH_ANIMATOR)

zephyr_include_directories(src)
zephyr_include_directories(src/tp)
zephyr_include_directories(src/clock_point_data)
zephyr_include_directories(src/clock_point_data/clock_point_read)
zephyr_include_directories(src/custom_widgets)
zephyr_include_directories(src/custom_widgets/calendar_month)
zephyr_include_directories(src/custom_widgets/color_button)
zephyr_include_directories(src/custom_widgets/gesture)
zephyr_include_directories(src/custom_widgets/music_play_button)
zephyr_include_directories(src/custom_widgets/round_menu)
zephyr_include_directories(src/custom_widgets/watch_clock)
zephyr_include_directories(src/custom_widgets/window_anim_menu)
zephyr_include_directories(src/window_controller)
zephyr_include_directories(src/window_controller/calendar_main)
zephyr_include_directories(src/window_controller/music_main)
zephyr_include_directories(src/window_controller/round_menu_main)
zephyr_include_directories(src/window_controller/training_main)
zephyr_include_directories(src/window_controller/watch_main)
zephyr_include_directories(src/window_controller/weather_main)

FILE(GLOB app_sources
  src/*.c
  src/tp/*.c
  src/clock_point_data/clock_point_read/*.c
  src/custom_widgets/*.c
  src/custom_widgets/calendar_month/*.c
  src/custom_widgets/color_button/*.c
  src/custom_widgets/gesture/*.c
  src/custom_widgets/music_play_button/*.c
  src/custom_widgets/round_menu/*.c
  src/custom_widgets/watch_clock/*.c
  src/custom_widgets/window_anim_menu/*.c
  src/window_controller/*.c
  src/window_controller/calendar_main/*.c
  src/window_controller/music_main/*.c
  src/window_controller/round_menu_main/*.c
  src/window_controller/training_main/*.c
  src/window_controller/watch_main/*.c
  src/window_controller/weather_main/*.c
)

target_sources(app PRIVATE ${app_sources})
