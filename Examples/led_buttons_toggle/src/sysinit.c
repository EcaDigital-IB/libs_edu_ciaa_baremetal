#include "chip.h"
#include "ledDriver.h"

#define TICKRATE_HZ (1000)

#define CORE_CLK 10000000

void SystemInit(void) {

	// LED_1 pin muxing
	Chip_SCU_PinMuxSet(LED_PINMUX_PORT, LED_PINMUX_PIN,
			(SCU_MODE_INBUFF_EN | SCU_MODE_PULLUP | SCU_MODE_FUNC0));

	// Configure Main PLL and set core clock to 10 MHz
	Chip_SetupCoreClock(CLKIN_CRYSTAL, CORE_CLK, false);
	SystemCoreClockUpdate();
}
