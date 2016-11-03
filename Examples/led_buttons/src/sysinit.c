#include "chip.h"

#define TICKRATE_HZ (1000)

#define CORE_CLK 10000000

void SystemInit(void) {

	// Configure Main PLL and set core clock to 10 MHz
	Chip_SetupCoreClock(CLKIN_CRYSTAL, CORE_CLK, false);
	SystemCoreClockUpdate();
}
