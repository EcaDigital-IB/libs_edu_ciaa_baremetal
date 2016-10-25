#include "stdio.h"
#include "chip.h"
#include "buttons.h"
#include "leds.h"
#include "board.h"

#define TICK_RATE 1000

#define PRINT_RATE 1

uint32_t _tCnt = 0;

void SysTick_Handler(void) {

	_tCnt++;
}

int main(void) {

	uint32_t oldT;

	char printBuff [128];

	SystemCoreClockUpdate();

	SysTick_Config(SystemCoreClock / TICK_RATE);

	Board_Debug_Init();

	LEDS_Init();

	Buttons_Init();

	oldT = _tCnt;



	while (1) {

		if (Buttons_Poll(BUTTONS_SW1))
			LEDS_Set(LEDS_1, false);

		else
			LEDS_Set(LEDS_1, true);

		if (Buttons_Poll(BUTTONS_SW2))
					LEDS_SetAll(0x2A);

				else
					LEDS_SetAll(0x00);

		if (Buttons_Poll(BUTTONS_SW3))
					LEDS_SetAll(0x15);

				else
					LEDS_SetAll(0x00);

		if (Buttons_Poll(BUTTONS_SW4))
					LEDS_SetAll(0x07);

				else
					LEDS_SetAll(0x00);

		if (_tCnt - oldT >= PRINT_RATE * TICK_RATE) {

			oldT = _tCnt;

			sprintf(printBuff, "LEDs  %d \r\n", 0x10);

			sprintf(printBuff, "LEDs state: %d \r\n", LEDS_TestAll());

			Board_UARTPutSTR(printBuff);

			sprintf(printBuff, "Buttons state: %d \r\n", Buttons_PollAll());

			Board_UARTPutSTR(printBuff);

		}
	}
}
