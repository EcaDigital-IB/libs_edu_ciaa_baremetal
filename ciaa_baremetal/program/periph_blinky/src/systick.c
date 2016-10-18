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

	while (1) {

		//Board_LED_Toggle(LED_BLUE);
		//delay(100);

		if (Buttons_PollDeb(1, tick_ct))
			Board_LED_Set(LED_1, false);
		//Board_LED_Toggle(LED_1);
		else
			Board_LED_Set(LED_1, true);

		if (Buttons_PollDeb(2, tick_ct))
			Board_LED_Set(LED_2, false);
		//Board_LED_Toggle(LED_2);
		else
			Board_LED_Set(LED_2, true);

		if (Buttons_PollDeb(3, tick_ct))
			Board_LED_Set(LED_3, false);
		//Board_LED_Toggle(LED_3);
		else
			Board_LED_Set(LED_3, true);

		if (Buttons_PollDeb(4, tick_ct))
			Board_LED_Set(LED_RED, false);
		//Board_LED_Toggle(LED_RED);
		else
			Board_LED_Set(LED_RED, true);

		Board_UARTPutSTR("Hola mundo\r\n");
	}
}
