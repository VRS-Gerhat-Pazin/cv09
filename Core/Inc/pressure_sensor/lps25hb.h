/*
 * lps25hb.h
 *
 *  Created on: Dec 16, 2021
 *      Author: Filip Gerhat
 */

#ifndef PRESSURE_SENSOR_LPS25HB_H_
#define PRESSURE_SENSOR_LPS25HB_H_

#include "stdint.h"
#include "i2c.h"

#define LPS25HB_I2C_ADDRESS_0 0xB8
#define LPS25HB_I2C_ADDRESS_1 0xBA

#define LPS25HB_REG_WHO_AM_I_ADDR 0x0F
#define LPS25HB_WHO_AM_I_VALUE 0b10111101

#define LPS25HB_REG_CTRL_REG1 0x20
#define LPS25HB_REG_PRESS_OUT_XL 0x28
#define LPS25HB_REG_PRESS_OUT_L 0x29
#define LPS25HB_REG_PRESS_OUT_H 0x2A



void lps25hb_write_byte(uint8_t reg_address, uint8_t data);
uint8_t lps25hb_read_byte(uint8_t reg_address);

uint8_t lps25hb_init();

float lps25hb_get_pressure();
float lps25hb_calculate_altitude(float pressure);



#endif /* PRESSURE_SENSOR_LPS25HB_H_ */
