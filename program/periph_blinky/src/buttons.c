/*
 * buttons.c
 *
 *  Created on: Oct 14, 2016
 *      Author: l_vis
 */

#include "buttons.h"

bool _fDebInit = false, _fButInit = false;

uint32_t _debT = BUTTONS_DEF_DEB_T;

uint32_t _oldT = 0;

int8_t _butState = 0x80;

uint32_t _butClks[] = { 0, 0, 0, 0 };

/* initialize board's buttons driver */
void Buttons_Init(void) {

	int i;

	for (i = 0; i < sizeof(_gpioSWBits) / sizeof(_gpioSWBits[0]); ++i) {

		Chip_SCU_PinMuxSet(_gpioSWBits[i].mux.pingrp, _gpioSWBits[i].mux.pinnum,
				(_gpioSWBits[i].mux.modefunc | SCU_MODE_PULLUP
						| SCU_MODE_INBUFF_EN | SCU_MODE_ZIF_DIS));

		Chip_GPIO_SetPinDIRInput(LPC_GPIO_PORT, _gpioSWBits[i].io.port,
				_gpioSWBits[i].io.pin);

	}

	_fButInit = true;
}

/** initialize board's buttons driver with debounce
 *
 * @param debT: stabilization period in ms
 * @param currentT: current time in ms
 */
void Buttons_InitDeb(uint32_t debT, uint32_t currentT) {

	Buttons_Init();

	_fDebInit = true;

	_oldT = currentT;

	Buttons_SetDebT(debT);

}

/** Debounce stabilization period setter
 *
 * @param debT: stabilization period in ms
 */
void Buttons_SetDebT(uint32_t debT) {

	_debT = debT;

}

/** Polls all buttons without deboucing
 *
 * @return raw button states masked byte (masks: BUTTONS_SW[n])
 */
int8_t Buttons_PollAll(void) {

	int i;
	uint8_t ret = 0x80;

	if (!_fButInit)
		return -1;

	for (i = 0; i < sizeof(_gpioSWBits) / sizeof(_gpioSWBits[0]); ++i) {

		if (Chip_GPIO_GetPinState(LPC_GPIO_PORT, _gpioSWBits[i].io.port,
				_gpioSWBits[i].io.pin) == 0)

			ret |= 0x1 << i;
	}

	return ~ret;
}

/** Polls button without deboucing
 *
 * @param buttonNum: button's number (1 ... n)
 * @return button's raw state (true if pressed false otherwise)
 */
bool Buttons_Poll(int8_t buttonNum) {

	if (!_fButInit)
		return false;

	if(buttonNum > sizeof(_gpioSWBits) / sizeof(_gpioSWBits[0]))
			return false;

	buttonNum--;

	if (Chip_GPIO_GetPinState(LPC_GPIO_PORT, _gpioSWBits[buttonNum].io.port,
			_gpioSWBits[buttonNum].io.pin) == 0)
		return true;

	return false;
}

/** Polls all buttons with deboucing
 *
 * @param currentT: current time in ms
 * @return debounced button states masked byte (masks: BUTTONS_SW[n])
 */
int8_t Buttons_PollDebAll(uint32_t currentT) {

	int i;

	bool butRaw;

	//return if debouncing not init
	if (!_fDebInit)
		return -1;

	//return if buttonNum greater than num of defined buttons
	for (i = 0; i < sizeof(_gpioSWBits) / sizeof(_gpioSWBits[0]); ++i) {

		if (_butClks[i] > _debT)
			_butClks[i] = _debT;

		// get button's raw value
		butRaw = Chip_GPIO_GetPinState(LPC_GPIO_PORT, _gpioSWBits[i].io.port,
				_gpioSWBits[i].io.pin);

		// check if state and raw value are different update clock
		if (butRaw != ((_butState >> i) & 0x01) && _butClks[i] < _debT) {

				_butClks[i] += currentT - _oldT;

		// otherwise, reset clock and update state
		} else {

			_butClks[i] = 0;
			_butState &= ~(0x1 << i); // clear bits
			_butState |= butRaw << i;  // set bits

		}
	}

	_oldT = currentT;

	return ~_butState;

}

/** Polls button with deboucing
 *
 * @param buttonNum: button's number (1 ... n)
 * @param currentT: current time in ms
 * @return button's debounced state (true if pressed false otherwise)
 */
bool Buttons_PollDeb(int8_t buttonNum, uint32_t currentT) {

	//return if debouncing not init
	if (!_fDebInit)
		return false;

	//return if buttonNum greater than num of defined buttons
	if(buttonNum > sizeof(_gpioSWBits) / sizeof(_gpioSWBits[0]))
		return false;

	//
	return (bool) ((Buttons_PollDebAll(currentT) & (0x1 << (buttonNum - 1))) > 0);
}

