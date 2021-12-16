/*
 * display.c
 *
 *  Created on: Dec 13, 2021
 *      Author: Filip Gerhat
 */

#include "display.h"

void disableAllSegments()
{
	for(uint8_t i = 0; i < 8; ++i)
	{
		LL_GPIO_SetOutputPin(segment_port[i], segment_pin[i]);
	}
}

void disableAllDigits()
{
	for(uint8_t i = 0; i < 5; ++i)
	{
		LL_GPIO_ResetOutputPin(digit_port[i], digit_pin[i]);
	}

}

uint8_t ascii_to_7segments(uint8_t character)
{
	if((character < '0') || (character > 'z'))
	{
		return 0x00;
	}

	return seven_seg_digits_decode_abcdefg[character - '0'];
}

void displayAsciiCharacter(uint8_t character)
{
	uint8_t segments = ascii_to_7segments(character);

	disableAllSegments();

	uint8_t mask = 0x01;
	for(uint8_t i = 0; i < 8; ++i)
	{
		if(segments & mask)
		{
			LL_GPIO_ResetOutputPin(segment_port[i], segment_pin[i]);
		}
		mask <<= 1;
	}
}

// order of segments:
// MSB            LSB
// DP A B C D E F G
const uint8_t seven_seg_digits_decode_abcdefg[75]= {
/*  0     1     2     3     4     5     6     7     8     9     :     ;     */
    0x7E, 0x30, 0x6D, 0x79, 0x33, 0x5B, 0x5F, 0x70, 0x7F, 0x7B, 0x00, 0x00,
/*  <     =     >     ?     @     A     B     C     D     E     F     G     */
    0x00, 0x00, 0x00, 0x00, 0x00, 0x77, 0x1F, 0x4E, 0x3D, 0x4F, 0x47, 0x5E,
/*  H     I     J     K     L     M     N     O     P     Q     R     S     */
    0x37, 0x06, 0x3C, 0x57, 0x0E, 0x55, 0x15, 0x1D, 0x67, 0x73, 0x05, 0x5B,
/*  T     U     V     W     X     Y     Z     [     \     ]     ^     _     */
    0x0F, 0x3E, 0x1C, 0x5C, 0x13, 0x3B, 0x6D, 0x00, 0x00, 0x00, 0x00, 0x08,
/*  `     a     b     c     d     e     f     g     h     i     j     k     */
    0x00, 0x77, 0x1F, 0x4E, 0x3D, 0x4F, 0x47, 0x5E, 0x37, 0x06, 0x3C, 0x57,
/*  l     m     n     o     p     q     r     s     t     u     v     w     */
    0x0E, 0x55, 0x15, 0x1D, 0x67, 0x73, 0x05, 0x5B, 0x0F, 0x3E, 0x1C, 0x5C,
/*  x     y     z     */
    0x13, 0x3B, 0x6D
};

const uint32_t segment_pin[] = {
	segmentG_Pin,
	segmentF_Pin,
	segmentE_Pin,
	segmentD_Pin,
	segmentC_Pin,
	segmentB_Pin,
	segmentA_Pin,
	segmentDP_Pin
};

const GPIO_TypeDef* segment_port[] = {
	segmentG_GPIO_Port,
	segmentF_GPIO_Port,
	segmentE_GPIO_Port,
	segmentD_GPIO_Port,
	segmentC_GPIO_Port,
	segmentB_GPIO_Port,
	segmentA_GPIO_Port,
	segmentDP_GPIO_Port
};

const uint32_t digit_pin[] = {
	digit0_Pin,
	digit1_Pin,
	digit2_Pin,
	digit3_Pin,
	digitTime_Pin
};

const GPIO_TypeDef* digit_port[] = {
	digit0_GPIO_Port,
	digit1_GPIO_Port,
	digit2_GPIO_Port,
	digit3_GPIO_Port,
	digitTime_GPIO_Port
};
