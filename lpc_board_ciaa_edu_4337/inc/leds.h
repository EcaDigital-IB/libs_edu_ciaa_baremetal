/*
 * buttons.h
 *
 *  Created on: Oct 14, 2016
 *      Author: l_vis
 */

#ifndef INC_LEDS_H_
#define INC_LEDS_H_

#include "chip.h"

#define LEDS_1 		0x01
#define LEDS_2  	0x02
#define LEDS_3  	0x04
#define LEDS_RED  	0x08
#define LEDS_GREEN  0x10
#define LEDS_BLUE  	0x20

/* Buttons' GPIO Port structure array*/
static const gpio_port_t _gpioLEDBits[] = { {.mux = {2, 10, SCU_MODE_FUNC0}, .io = {0, 14}},
	{	.mux = {2, 11, SCU_MODE_FUNC0}, .io = {1, 11}},
	{	.mux = {2, 12, SCU_MODE_FUNC0}, .io = {1, 12}},
	{	.mux = {2, 0, SCU_MODE_FUNC4}, .io = {5, 0}},
	{	.mux = {2, 1, SCU_MODE_FUNC4}, .io = {5, 1}},
	{	.mux = {2, 2, SCU_MODE_FUNC4}, .io = {5, 2}}};

/**
 * initialize board's LEDs driver
 */
void LEDS_Init(void);

/**
 * Set LED state
 * @param LEDTag: LED Tag macro from driver (LEDS_[name])
 * @param Off: not(state) of LED
 */
void LEDS_Set(uint8_t LEDTag, bool Off);

/**
 * Set all LED states at once
 * @param ledsState: ORed LED mask state (masks: LEDS_[name]_MSK)
 */
void LEDS_SetAll(uint8_t ledsState);

/**
 * Test LED state
 * @param LEDTag: LED Tag macro from driver (LEDS_[name])
 * @return LED state
 */
bool LEDS_Test(uint8_t LEDTag);

/**
 * Test all LED states at once
 * @return ORed LED mask state (masks: LEDS_[name]_MSK)
 */
uint8_t LEDS_TestAll(void);

/**
 * Toggle LED
 * @param LEDTag: LED Tag macro from driver (LEDS_[name])
 */
void LEDS_Toggle(uint8_t LEDTag);


#endif
