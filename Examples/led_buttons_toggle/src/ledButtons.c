#include "chip.h"
#include "buttons.h"
#include "ledDriver.h"

#define TICK_RATE 1000 // [HZ]

volatile uint32_t gTick = 0;

/* CONSIGNA:
 * 	Lograr que un LED parpadee con período 0.5s
 * 	cuando se pulse SW1
 */

// SysTick Interrupt service routine
void SysTick_Handler(void) {
	gTick++;
}

int main(void) {

	// Systick config. to interrupt at TICK_RATE Hz
	SysTick_Config(SystemCoreClock/TICK_RATE);

	LEDInit();

	Buttons_Init();

	while (1) {

		if (Buttons_Poll(1))
			LEDSet(false);

		else
			LEDSet(true);
	}
}
