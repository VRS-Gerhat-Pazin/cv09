/*
 * lps25hb.c
 *
 *  Created on: Dec 16, 2021
 *      Author: Filip Gerhat
 */

#include "pressure_sensor/lps25hb.h"
#include "math.h"

static uint8_t address = LPS25HB_I2C_ADDRESS_1;

void lps25hb_write_byte(uint8_t reg_address, uint8_t data)
{
	i2c_master_write(data, reg_address, address, 0);
}

uint8_t lps25hb_read_byte(uint8_t reg_address)
{
	uint8_t data;
	i2c_master_read(&data, 1, reg_address, address, 0);
	return data;
}

uint8_t lps25hb_init()
{
	// verify WHO_AM_I
	uint8_t id = lps25hb_read_byte(LPS25HB_REG_WHO_AM_I_ADDR);
	if(id != LPS25HB_WHO_AM_I_VALUE)
	{
		// try another address
		address = LPS25HB_I2C_ADDRESS_0;
		id = lps25hb_read_byte(LPS25HB_REG_WHO_AM_I_ADDR);
		if(id != LPS25HB_WHO_AM_I_VALUE)
		{
			return 0;
		}
	}

	// set up sensor registers

	uint8_t ctrl_reg1 = 0b11000000; // power enable, ODR 25Hz, interrupts off, BDU off, Autozero off
	lps25hb_write_byte(LPS25HB_REG_CTRL_REG1, ctrl_reg1);

	return 1;
}

float lps25hb_get_pressure()
{
	uint8_t press_xl = lps25hb_read_byte(LPS25HB_REG_PRESS_OUT_XL);
	uint8_t press_l = lps25hb_read_byte(LPS25HB_REG_PRESS_OUT_L);
	uint8_t press_h = lps25hb_read_byte(LPS25HB_REG_PRESS_OUT_H);

	uint32_t pressure = 0;
	pressure = press_xl | (press_l << 8) | (press_h << 16);

	return ((float)pressure)/4096.0;
}

float lps25hb_calculate_altitude(float pressure)
{
	// https://community.bosch-sensortec.com/t5/Question-and-answers/How-to-calculate-the-altitude-from-the-pressure-sensor-data/qaq-p/5702
	return 44330 * (1 - pow(pressure/1013.25, 1/5.255));
}
