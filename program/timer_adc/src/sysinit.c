#include "chip.h"

#define CORE_CLK 10000000

void SystemInit(void) {

	Chip_SCU_PinMuxSet(7, 1, (SCU_MODE_INBUFF_EN | SCU_MODE_INACT | SCU_MODE_FUNC6));						// UART2 TX
	Chip_SCU_PinMuxSet(7, 2, (SCU_MODE_INBUFF_EN | SCU_MODE_ZIF_DIS | SCU_MODE_INACT | SCU_MODE_FUNC6));	// UART2 RX

	// Configure Main PLL and set core clock to 10 MHz
	Chip_SetupCoreClock(CLKIN_CRYSTAL, CORE_CLK, false);

	fpuInit();
}
