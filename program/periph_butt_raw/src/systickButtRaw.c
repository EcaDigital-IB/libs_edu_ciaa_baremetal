#include "board.h"
#include "buttons.h"

#define TICKRATE_HZ (1000)

const int LED_3 = 2;
const int LED_2 = 1;
const int LED_1 = 0;
const int LED_RED = 3;
const int LED_GREEN = 4;
const int LED_BLUE = 5;

static volatile uint32_t tick_ct = 0;

void SysTick_Handler(void) {
	tick_ct++;
}

void delay(uint32_t tk) {
	uint32_t end = tick_ct + tk;
	while (tick_ct < end)
		__WFI();
}

int main(void) {
	SystemCoreClockUpdate();
	Board_Init();
	SysTick_Config(SystemCoreClock / TICKRATE_HZ);

	Buttons_InitDeb(100, tick_ct);

	bool fPressed = false;
	int bounceCnt = 0;
	char printBuff[128];

	while (1) {

		//Board_LED_Toggle(LED_BLUE);
		//delay(100);

		if (Buttons_Poll(1)) {
			Board_LED_Set(LED_1, false);
			//Board_LED_Toggle(LED_1);

			if (!fPressed) {
				fPressed = true;

				bounceCnt++;

				sprintf(printBuff, "Bounce n: %d\r\n", bounceCnt);

				Board_UARTPutSTR(printBuff);
			}

		} else {

			fPressed = false;

			Board_LED_Set(LED_1, true);
		}

		if (Buttons_Poll(2)) {
			Board_LED_Set(LED_2, false);
			//Board_LED_Toggle(LED_1);

			bounceCnt = 0;

		} else {
			Board_LED_Set(LED_2, true);
		}

	}
}
