/*
 * Copyright (c) 2018 - 2020 Nordic Semiconductor ASA
 *
 * SPDX-License-Identifier: LicenseRef-BSD-5-Clause-Nordic
 */

#include <zephyr.h>
#include <device.h>
#include <drivers/i2c.h>
#include "Adafruit_FT6206.h"
#include "touch_ft6206.h"

#if CONFIG_BOARD_NRF5340PDK_NRF5340_CPUAPP || CONFIG_BOARD_NRF5340PDK_NRF5340_CPUAPPNS
#define I2C_DEV_NAME	DT_LABEL(DT_ALIAS(i2c_1))
#else
#define I2C_DEV_NAME	DT_LABEL(DT_ALIAS(i2c_0))
#endif

static struct device *i2c_dev = NULL;

void touch_ft6206_init(void)
{
	int err;

	i2c_dev = device_get_binding(I2C_DEV_NAME);

	if (i2c_dev == NULL) {
		printk("i2c_dev = NULL\n");
	}

	u32_t i2c_cfg = I2C_SPEED_SET(I2C_SPEED_FAST) | I2C_MODE_MASTER;

	err = i2c_configure(i2c_dev, i2c_cfg);
	if (err) {
		printk("i2c_configure() = %d\n", err);
	}

#if 0
	u8_t datum;

	err = i2c_reg_read_byte(i2c_dev, FT62XX_ADDR, FT62XX_REG_VENDID, &datum);
	if (err) {
		printk("i2c_reg_read_byte() = %d\n", err);
	} else {
		printk("VENDID = %02X\n", datum);
	}

	err = i2c_reg_read_byte(i2c_dev, FT62XX_ADDR, FT62XX_REG_CHIPID, &datum);
	if (err) {
		printk("i2c_reg_read_byte() = %d\n", err);
	} else {
		printk("CHIPID = %02X\n", datum);
	}

	err = i2c_reg_read_byte(i2c_dev, FT62XX_ADDR, FT62XX_REG_MODE, &datum);
	if (err) {
		printk("i2c_reg_read_byte() = %d\n", err);
	} else {
		printk("MODE = %02X\n", datum);
	}

	err = i2c_reg_read_byte(i2c_dev, FT62XX_ADDR, FT62XX_REG_POINTRATE, &datum);
	if (err) {
		printk("i2c_reg_read_byte() = %d\n", err);
	} else {
		printk("POINTRATE = %02X\n", datum);
	}
#endif

	err = i2c_reg_write_byte(i2c_dev, FT62XX_ADDR, FT62XX_REG_MODE, FT62XX_REG_WORKMODE);
	if (err) {
		printk("i2c_reg_write_byte() = %d\n", err);
	} else {
		printk("MODE = %02X\n", FT62XX_REG_WORKMODE);
	}

	err = i2c_reg_write_byte(i2c_dev, FT62XX_ADDR, FT62XX_REG_THRESHHOLD, FT62XX_DEFAULT_THRESHOLD);
	if (err) {
		printk("i2c_reg_write_byte() = %d\n", err);
	} else {
		printk("THRESHHOLD = %02X\n", FT62XX_DEFAULT_THRESHOLD);
	}
}

touch_pos_t touch_ft6206_get(void)
{
	touch_pos_t touch_pos;
	int err;

	u8_t data[7];

	err = i2c_burst_read(i2c_dev, FT62XX_ADDR, FT62XX_REG_NUMTOUCHES, data, 7);
	if (err) {
		printk("i2c_burst_read() = %d\n", err);

		// I2C error...
		touch_pos.x = touch_pos.y = touch_pos.z = 0;
	} else {
		u8_t num_touch = data[0] & 0xF;
		if (!num_touch || num_touch > 2) {
			// panel not pressed
			touch_pos.x = touch_pos.y = touch_pos.z = 0;
		} else {
			// get touch position
			touch_pos.z = 1;
			touch_pos.x = (((u16_t)data[1] & 0xF) << 8) + data[2];
			touch_pos.y = (((u16_t)data[3] & 0xF) << 8) + data[4];
		}
	}

	return touch_pos;
}
