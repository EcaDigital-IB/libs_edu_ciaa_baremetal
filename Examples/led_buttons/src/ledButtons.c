#include "chip.h"
#include "buttons.h"

#define TICKRATE_HZ (1000)

#define CORE_CLK 10000000

// Led PinMuxing and GPIO ports
#define LED_PINMUX_PORT	2
#define LED_PINMUX_PIN	10

#define LED_GPIO_PORT	0
#define LED_GPIO_PIN	14

void SystemInit(void) {

	// LED_1 pin muxing
	Chip_SCU_PinMuxSet(LED_PINMUX_PORT, LED_PINMUX_PIN,
			(SCU_MODE_INBUFF_EN | SCU_MODE_PULLUP | SCU_MODE_FUNC0));

	// Configure Main PLL and set core clock to 10 MHz
	Chip_SetupCoreClock(CLKIN_CRYSTAL, CORE_CLK, false);
	SystemCoreClockUpdate();
}

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

int main(void) {

	LEDInit();

	Buttons_Init();

	while (1) {

		if (Buttons_Poll(1))
			LEDSet(false);
		//Board_LED_Toggle(LED_1);
		else
			LEDSet(true);
	}
}
