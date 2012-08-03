/*
 * This code is based on information from
 * http://www.nondot.org/sabre/os/files/Communication/ser_port.txt
 */

#include <driver/uart.h>

void UartSend(char c)
{
	if (c == '\n')
		UartSend_int('\r');
	UartSend_int(c);
}

void UartSendString(const char *str)
{
	do {
		UartSend(*str);
	}	while (*str++);
}

static void UartSend_int(char c)
{
	/* wait until UART is ready to send */
	while ((HalInPort(UART_BASE_REGISTER + LineStatus) & THRE) == 0);

	HalOutPort(UART_BASE_REGISTER, (uint8_t)c);
}

void UartInit()
{
	HalOutPort(UART_BASE_REGISTER + LineControl, DLAB);
	HalOutPort(UART_BASE_REGISTER, UART_BAUDRATE_DIVISOR);
	HalOutPort(UART_BASE_REGISTER + LineControl, UART_LCR);
	HalOutPort(UART_BASE_REGISTER + ModemControl, 0);

	UartSendString("UART successfully enabled.\n");
}

struct DisplayDevice UartDisplayDevice = {
	.Init		= (void*)UartInit,
	.DisplayChar	= (void*)UartSend,
	.DisplayClear	= NULL,	/* I don't think this is possible. */
};
