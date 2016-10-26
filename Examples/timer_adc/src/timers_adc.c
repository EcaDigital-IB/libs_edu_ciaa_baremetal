/*
 * @brief Blinky example using a timer and interrupt
 *
 * @note
 * Copyright(C) NXP Semiconductors, 2013
 * All rights reserved.
 *
 * @par
 * Software that is described herein is for illustrative purposes only
 * which provides customers with programming information regarding the
 * LPC products.  This software is supplied "AS IS" without any warranties of
 * any kind, and NXP Semiconductors and its licensor disclaim any and
 * all warranties, express or implied, including all implied warranties of
 * merchantability, fitness for a particular purpose and non-infringement of
 * intellectual property rights.  NXP Semiconductors assumes no responsibility
 * or liability for the use of the software, conveys no license or rights under any
 * patent, copyright, mask work right, or any other intellectual property rights in
 * or to any products. NXP Semiconductors reserves the right to make changes
 * in the software without notification. NXP Semiconductors also makes no
 * representation or warranty that such application will be suitable for the
 * specified use without further testing or modification.
 *
 * @par
 * Permission to use, copy, modify, and distribute this software and its
 * documentation is hereby granted, under NXP Semiconductors' and its
 * licensor's relevant copyrights in the software, without fee, provided that it
 * is used in conjunction with NXP Semiconductors microcontrollers.  This
 * copyright, permission, and disclaimer notice must appear in all copies of
 * this code.
 */

#include "chip.h"
#include "leds.h"
#include "timerDriver.h"

#define TICKRATE_HZ 20000
#define ADC_RATE_HZ (TICKRATE_HZ * 20)

volatile uint16_t _ADCSample = 0x00;

volatile bool _fADCDone = false;

#define _ADC_CHANNLE ADC_CH3
#define _LPC_ADC_ID LPC_ADC0
#define _LPC_ADC_IRQ ADC0_IRQn

/**
 * @brief	Handle interrupt from 32-bit timer
 * @return	Nothing
 */
void TIMER1_IRQHandler(void) {
	static bool On = false;

	if (Chip_TIMER_MatchPending(LPC_TIMER1, 1)) {

		Chip_TIMER_ClearMatch(LPC_TIMER1, 1);

		Chip_ADC_SetStartMode(_LPC_ADC_ID, ADC_START_NOW,
				ADC_TRIGGERMODE_RISING);
	}
}

/**
 * @brief	ADC0 interrupt handler sub-routine
 * @return	Nothing
 */
void ADC0_IRQHandler(void) {
	uint16_t dataADC;
	/* Interrupt mode: Call the stream interrupt handler */
	NVIC_DisableIRQ(_LPC_ADC_IRQ);
	Chip_ADC_Int_SetChannelCmd(_LPC_ADC_ID, _ADC_CHANNLE, DISABLE);
	Chip_ADC_ReadValue(_LPC_ADC_ID, _ADC_CHANNLE, &dataADC);
	_ADCSample = dataADC;
	_fADCDone = true;

	NVIC_EnableIRQ(_LPC_ADC_IRQ);
	Chip_ADC_Int_SetChannelCmd(_LPC_ADC_ID, _ADC_CHANNLE, ENABLE);
}

void UART_Init(void) {

	Chip_SCU_PinMuxSet(7, 1,
			(SCU_MODE_INBUFF_EN | SCU_MODE_INACT | SCU_MODE_FUNC6)); // UART2 TX
	Chip_SCU_PinMuxSet(7, 2,
			(SCU_MODE_INBUFF_EN | SCU_MODE_ZIF_DIS | SCU_MODE_INACT
					| SCU_MODE_FUNC6));	// UART2 RX

	Chip_UART_Init(LPC_USART2);
	Chip_UART_SetBaudFDR(LPC_USART2, 230400);
	Chip_UART_ConfigData(LPC_USART2,
	UART_LCR_WLEN8 | UART_LCR_SBS_1BIT | UART_LCR_PARITY_DIS);

	/* Enable UART Transmit */
	Chip_UART_TXEnable(LPC_USART2);

}

void UART_PutChar(char ch) {

	while ((Chip_UART_ReadLineStatus(LPC_USART2) & UART_LSR_THRE) == 0) {
	}

	Chip_UART_SendByte(LPC_USART2, (uint8_t) ch);

}
/**
 * @brief	main routine for blinky example
 * @return	Function should not exit.
 */
int main(void) {

	ADC_CLOCK_SETUP_T ADCSetup;

	uint16_t ADCSampleBuff = 0;

	SystemCoreClockUpdate();

	LEDS_Init();

	UART_Init();

	Timer_MatchConfig(TICKRATE_HZ);
	Timer_matchIntEnable();

	Chip_ADC_Init(_LPC_ADC_ID, &ADCSetup);
	Chip_ADC_EnableChannel(_LPC_ADC_ID, _ADC_CHANNLE, ENABLE);

	ADCSetup.burstMode = true;

	Chip_ADC_SetSampleRate(_LPC_ADC_ID, &ADCSetup, ADC_RATE_HZ);

	Chip_ADC_SetResolution(_LPC_ADC_ID, &ADCSetup, ADC_10BITS);

	NVIC_EnableIRQ(_LPC_ADC_IRQ);
	Chip_ADC_Int_SetChannelCmd(_LPC_ADC_ID, _ADC_CHANNLE, ENABLE);

	while (true) {

		if (_fADCDone) {

			ADCSampleBuff = _ADCSample;

			_fADCDone = 0;

			UART_PutChar((char) ((ADCSampleBuff & 0x03FF) >> 2));
		}
	}
}
