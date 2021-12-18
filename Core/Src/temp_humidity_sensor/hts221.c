/*
 * hts221.c
 *
 *  Created on: Dec 18, 2021
 *      Author: Filip Gerhat
 */

#include "temp_humidity_sensor/hts221.h"

static uint8_t address = HTS221_I2C_ADDRESS;

void hts221_write_byte(uint8_t reg_address, uint8_t data)
{
	i2c_master_write(data, reg_address, address, 0);

}
uint8_t hts221_read_byte(uint8_t reg_address)
{
	uint8_t data = 0;
	i2c_master_read(&data, 1, reg_address, address, 0);
	return data;
}

uint8_t hts221_init()
{
	uint8_t id = hts221_read_byte(HTS221_REG_WHO_AM_I);
	if(id != HTS221_WHO_AM_I_VALUE)
	{
		return 0;
	}

	// set up sensor registers

	uint8_t ctrl_reg1 = 0b10000011;
	hts221_write_byte(HTS221_REG_CTRL_REG1, ctrl_reg1);

	return 1;
}

float hts221_get_temperature()
{
	// TODO calibration data
	uint8_t temp_l = hts221_read_byte(HTS221_REG_TEMP_OUT_L);
	uint8_t temp_h = hts221_read_byte(HTS221_REG_TEMP_OUT_H);

	int16_t temp = temp_l | (temp_h << 8);

	float temperature = (float)temp/8.0;

	if(temperature > 120)
	{
		return 120.0;
	}
	if(temperature < -40)
	{
		return -40.0;
	}

	return temperature;
}

float hts221_get_humidity()
{
	// TODO calibration data
	uint8_t hum_l = hts221_read_byte(HTS221_REG_HUMIDITY_OUT_L);
	uint8_t hum_h = hts221_read_byte(HTS221_REG_HUMIDITY_OUT_H);

	int16_t hum = hum_l | (hum_h << 8);

	float humidity = (float)hum/2.0;

	if(humidity > 100)
	{
		return 100.0;
	}
	if(humidity < 0)
	{
		return 0.0;
	}

	return humidity;
}
