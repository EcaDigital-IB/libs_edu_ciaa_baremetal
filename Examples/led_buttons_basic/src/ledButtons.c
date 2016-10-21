#include "chip.h"

void SystemInit(void) {

	// LED_1 pin muxing
	Chip_SCU_PinMuxSet(2, 10, (SCU_MODE_INBUFF_EN | SCU_MODE_PULLUP | SCU_MODE_FUNC0));

	Chip_SCU_PinMuxSet(1, 0, (SCU_MODE_FUNC0 | SCU_MODE_PULLUP | SCU_MODE_INBUFF_EN | SCU_MODE_ZIF_DIS));

	// Configure Main PLL and set core clock to 10 MHz
	Chip_SetupCoreClock(CLKIN_CRYSTAL, 10000000, false);
}

int main(void) {

	//Led Init: Set pin as output and init to off
	Chip_GPIO_SetPinDIROutput(LPC_GPIO_PORT, 0, 14);
	Chip_GPIO_SetPinState(LPC_GPIO_PORT, 0, 14, false);

	//Button Init: Set pin as input
	Chip_GPIO_SetPinDIRInput(LPC_GPIO_PORT, 0, 4);

	while (1) {

		if (Chip_GPIO_GetPinState(LPC_GPIO_PORT, 0, 4) == 0)

			Chip_GPIO_SetPinState(LPC_GPIO_PORT, 0, 14, true);

		else

			Chip_GPIO_SetPinState(LPC_GPIO_PORT, 0, 14, false);
	}
}
