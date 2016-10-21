#include "ledDriver.h"

void LEDSet(bool Off) {

	Chip_GPIO_SetPinState(LPC_GPIO_PORT, LED_GPIO_PORT, LED_GPIO_PIN,
			(bool) !Off);
}

void LEDInit() {

	/* Set pin direction and init to off */
	Chip_GPIO_SetPinDIROutput(LPC_GPIO_PORT, LED_GPIO_PORT, LED_GPIO_PIN);
	LEDSet((bool) true);
}

bool LEDTest(void) {

	return (bool) !Chip_GPIO_GetPinState(LPC_GPIO_PORT, LPC_GPIO_PORT, LED_GPIO_PIN);
}

void LEDToggle(void) {

	LEDSet(!LEDTest());
}
