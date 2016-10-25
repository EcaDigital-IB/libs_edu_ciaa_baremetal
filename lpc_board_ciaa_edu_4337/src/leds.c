/*
 * buttons.c
 *
 *  Created on: Oct 14, 2016
 *      Author: l_vis
 */

#include "leds.h"

static bool _fLedsInit = false;

/* initialize board's buttons driver */
void LEDS_Init(void) {

	int i;

	for (i = 0; i < sizeof(_gpioLEDBits) / sizeof(_gpioLEDBits[0]); ++i) {

		Chip_SCU_PinMuxSet(_gpioLEDBits[i].mux.pingrp,
				_gpioLEDBits[i].mux.pinnum,
				(_gpioLEDBits[i].mux.modefunc | SCU_MODE_INBUFF_EN
						| SCU_MODE_PULLUP));

		Chip_GPIO_SetPinDIROutput(LPC_GPIO_PORT, _gpioLEDBits[i].io.port,
				_gpioLEDBits[i].io.pin);

		Chip_GPIO_SetPinState(LPC_GPIO_PORT, _gpioLEDBits[i].io.port,
									_gpioLEDBits[i].io.pin, (bool) false);

	}

	_fLedsInit = true;
}

void LEDS_Set(uint8_t LEDTag, bool Off) {

	int i;

	if (!_fLedsInit)
		return;

	for (i = 0; i < sizeof(_gpioLEDBits) / sizeof(io_port_t); ++i) {

		if((LEDTag >> i) & 0x01 == 1){

			Chip_GPIO_SetPinState(LPC_GPIO_PORT, _gpioLEDBits[i].io.port,
							_gpioLEDBits[i].io.pin, (bool) !Off);

			return;
		}
	}
}

void LEDS_SetAll(uint8_t ledsState) {

	int i;

	if (!_fLedsInit)
		return;

	for (i = 0; i < sizeof(_gpioLEDBits) / sizeof(gpio_port_t); ++i)

		Chip_GPIO_SetPinState(LPC_GPIO_PORT, _gpioLEDBits[i].io.port,
				_gpioLEDBits[i].io.pin, (bool) ((ledsState >> i) & 0x01));
}

bool LEDS_Test(uint8_t LEDTag) {

	int i;

	if (!_fLedsInit)
		return false;

	for (i = 0; i < sizeof(_gpioLEDBits) / sizeof(io_port_t); ++i) {

		if((LEDTag >> i) & 0x01 == 1){

			return (bool) !Chip_GPIO_GetPinState(LPC_GPIO_PORT,
							_gpioLEDBits[i].io.port, _gpioLEDBits[i].io.pin);

		}
	}

	return false;
}

uint8_t LEDS_TestAll(void) {

	int i;
	uint8_t ret = 0x00;

	if (!_fLedsInit)
		return -1;

	for (i = 0; i < sizeof(_gpioLEDBits) / sizeof(_gpioLEDBits[0]); ++i) {

		if (Chip_GPIO_GetPinState(LPC_GPIO_PORT, _gpioLEDBits[i].io.port,
				_gpioLEDBits[i].io.pin) == 1)

			ret |= 0x1 << i;
	}

	return ret;
}

void LEDS_Toggle(uint8_t LEDTag) {

	if (!_fLedsInit)
		return;

	LEDS_Set(LEDTag, !LEDS_Test(LEDTag));
}

