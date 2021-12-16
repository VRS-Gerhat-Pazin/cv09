/*
 * display.h
 *
 *  Created on: Dec 13, 2021
 *      Author: Filip Gerhat
 */

#ifndef INC_DISPLAY_H_
#define INC_DISPLAY_H_

#include "stdint.h"
#include "main.h"

void disableAllSegments();
void disableAllDigits();
uint8_t ascii_to_7segments(uint8_t character);
void displayAsciiCharacter(uint8_t character);
extern const uint8_t seven_seg_digits_decode_abcdefg[];
extern const uint32_t segment_pin[];
extern const GPIO_TypeDef* segment_port[];
extern const uint32_t digit_pin[];
extern const GPIO_TypeDef* digit_port[];

#endif /* INC_DISPLAY_H_ */
