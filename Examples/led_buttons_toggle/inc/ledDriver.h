/*
 * ledDriver.h
 *
 *  Created on: Oct 21, 2016
 *      Author: l_vis
 */

#ifndef EXAMPLES_LED_BUTTONS_INC_LEDDRIVER_H_
#define EXAMPLES_LED_BUTTONS_INC_LEDDRIVER_H_

#include "chip.h"

// LED 1 port and pin values
#define LED_PINMUX_PORT	2
#define LED_PINMUX_PIN	10

#define LED_GPIO_PORT	0
#define LED_GPIO_PIN	14


/**
 * Sets led state
 *
 * @param Off: false for turning on LED, true for turning off
 */
void LEDSet(bool Off);

/**
 * Initializes LED GPIO
 */
void LEDInit(void);

/**
 * Reads LED value
 *
 * @return true if on, false otherwise
 */
bool LEDTest(void);

/**
 * Toggles LED state
 */
void LEDToggle(void);


#endif /* EXAMPLES_LED_BUTTONS_INC_LEDDRIVER_H_ */
