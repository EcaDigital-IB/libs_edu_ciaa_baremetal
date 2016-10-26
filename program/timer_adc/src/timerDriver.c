#include "timerDriver.h"

void Timer_SetMatch(uint32_t tickRateHZ) {

	Chip_TIMER_Disable(LPC_TIMER1);
	Chip_TIMER_SetMatch(LPC_TIMER1, 1,
			Chip_Clock_GetRate(CLK_MX_TIMER1) / tickRateHZ);
	Chip_TIMER_Enable(LPC_TIMER1);

}

void Timer_MatchConfig(uint32_t tickRateHZ) {

	/* Enable timer 1 clock and reset it */
	Chip_TIMER_Init(LPC_TIMER1);
	Chip_RGU_TriggerReset(RGU_TIMER1_RST);
	while (Chip_RGU_InReset(RGU_TIMER1_RST)) {
	}

	/* Timer setup for match and interrupt at TICKRATE_HZ */
	Chip_TIMER_Reset(LPC_TIMER1);
	Chip_TIMER_MatchEnableInt(LPC_TIMER1, 1);
	Chip_TIMER_ResetOnMatchEnable(LPC_TIMER1, 1);
	Timer_SetMatch(tickRateHZ);
}

void Timer_matchIntEnable(void) {

	/* Enable timer interrupt */
	NVIC_EnableIRQ(TIMER1_IRQn);
	NVIC_ClearPendingIRQ(TIMER1_IRQn);
}

void Timer_matchIntDisable(void) {

	/* Enable timer interrupt */
	NVIC_ClearPendingIRQ(TIMER1_IRQn);
	NVIC_DisableIRQ(TIMER1_IRQn);
}
