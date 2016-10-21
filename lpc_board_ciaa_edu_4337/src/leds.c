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

		Chip_GPIO_SetPinDIRInput(LPC_GPIO_PORT, _gpioLEDBits[i].io.port,
				_gpioLEDBits[i].io.pin);

	}

	_fLedsInit = true;
}

void LEDS_Set(uint8_t LEDNumber, bool Off) {

	if(!_fLedsInit)
		return;

	if (LEDNumber < (sizeof(_gpioLEDBits) / sizeof(io_port_t)))

		Chip_GPIO_SetPinState(LPC_GPIO_PORT, _gpioLEDBits[LEDNumber].io.port,
				_gpioLEDBits[LEDNumber].io.pin, (bool) !Off);
}

bool LEDS_Test(uint8_t LEDNumber) {

	if(!_fLedsInit)
		return false;

	if (LEDNumber < (sizeof(_gpioLEDBits) / sizeof(io_port_t)))

		return (bool) !Chip_GPIO_GetPinState(LPC_GPIO_PORT,
				_gpioLEDBits[LEDNumber].io.port, _gpioLEDBits[LEDNumber].io.pin);

	return false;
}

void LEDS_Toggle(uint8_t LEDNumber) {

	if(!_fLedsInit)
		return;

	LEDS_Set(LEDNumber, !LEDS_Test(LEDNumber));
}

