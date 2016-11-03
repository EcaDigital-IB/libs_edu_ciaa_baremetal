#include "uartDriver.h"

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
