/*
 * hts221.h
 *
 *  Created on: Dec 18, 2021
 *      Author: Filip Gerhat
 */

#ifndef INC_TEMP_HUMIDITY_SENSOR_HTS221_H_
#define INC_TEMP_HUMIDITY_SENSOR_HTS221_H_

#include "stdint.h"
#include "i2c.h"

#define HTS221_I2C_ADDRESS 0xBE

#define HTS221_WHO_AM_I_VALUE 0b10111100
#define HTS221_REG_WHO_AM_I 0x0F
#define HTS221_REG_CTRL_REG1 0x20
#define HTS221_REG_HUMIDITY_OUT_L 0x28
#define HTS221_REG_HUMIDITY_OUT_H 0x29
#define HTS221_REG_TEMP_OUT_L 0x2A
#define HTS221_REG_TEMP_OUT_H 0x2B


void hts221_write_byte(uint8_t reg_address, uint8_t data);
uint8_t hts221_read_byte(uint8_t reg_address);

uint8_t hts221_init();

float hts221_get_temperature();
float hts221_get_humidity();

#endif /* INC_TEMP_HUMIDITY_SENSOR_HTS221_H_ */
