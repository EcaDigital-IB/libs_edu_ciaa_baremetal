/*
 * timerDriver.h
 *
 *  Created on: Oct 26, 2016
 *      Author: l_vis
 */

#ifndef PROGRAM_TIMER_ADC_INC_TIMERDRIVER_H_
#define PROGRAM_TIMER_ADC_INC_TIMERDRIVER_H_

#include "chip.h"

/**
 * Set timer's match tick rate value
 * @param tickRateHZ
 */
void Timer_SetMatch(uint32_t tickRateHZ);

/**
 * Config timer1  set match value and enable interrupt
 * @param tickRateHZ
 */
void Timer_MatchConfig(uint32_t tickRateHZ);

/**
 * Timer's int enable
 */
void Timer_matchIntEnable(void);

/**
 * Timer's int disable
 */
void Timer_matchIntDisable(void);


#endif /* PROGRAM_TIMER_ADC_INC_TIMERDRIVER_H_ */
