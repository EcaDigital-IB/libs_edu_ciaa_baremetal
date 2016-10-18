/*
 * buttons.h
 *
 *  Created on: Oct 14, 2016
 *      Author: l_vis
 */

#ifndef INC_BUTTONS_H_
#define INC_BUTTONS_H_

#include <stdint.h>
#include <stdbool.h>

#include "chip.h"

#define BUTTONS_DEF_DEB_T 200 // [ms]

#define BUTTONS_SW1  0x01
#define BUTTONS_SW2  0x02
#define BUTTONS_SW3  0x04
#define BUTTONS_SW4  0x08

/* GPIO Port structure*/

typedef struct {
	uint8_t port;
	uint8_t pin;
} io_port_t;

typedef struct {
	PINMUX_GRP_T mux;
	io_port_t io;
} gpio_port_t;

/* Buttons' GPIO Port structure array*/
static const gpio_port_t _gpioSWBits[] = { {.mux = {1, 0, SCU_MODE_FUNC0}, .io = {0, 4}},
	{	.mux = {1, 1, SCU_MODE_FUNC0}, .io = {0, 8}},
	{	.mux = {1, 2, SCU_MODE_FUNC0}, .io = {0, 9}},
	{	.mux = {1, 6, SCU_MODE_FUNC0}, .io = {1, 9}}};



/* initialize board's buttons driver */
void Buttons_Init(void);

/** initialize board's buttons driver with debounce
 *
 * @param debT: stabilization period in ms
 * @param currentT: current time in ms
 */
void Buttons_InitDeb(uint32_t debT, uint32_t currentT);

/** Debounce stabilization period setter
 *
 * @param debT: stabilization period in ms
 */
void Buttons_SetDebT(uint32_t debT);

/** Polls all buttons without deboucing
 *
 * @param currentT: current time in ms
 * @return raw button states masked byte (masks: BUTTONS_SW[n])
 */
int8_t Buttons_PollAll(void);

/** Polls button without deboucing
 *
 * @param buttonNum: button's number (1 ... n)
 * @return button's raw state (true if pressed false otherwise)
 */
bool Buttons_Poll(int8_t buttonNum);

/** Polls all buttons with deboucing
 *
 * @param currentT: current time in ms
 * @return debounced button states masked byte (masks: BUTTONS_SW[n])
 */
int8_t Buttons_PollDebAll(uint32_t currentT);

/** Polls button with deboucing
 *
 * @param buttonNum: button's number (1 ... n)
 * @param currentT: current time in ms
 * @return button's debounced state (true if pressed false otherwise)
 */
bool Buttons_PollDeb(int8_t buttonNum, uint32_t currentT);

#endif /* PROGRAM_PERIPH_BLINKY_INC_BUTTONS_H_ */
