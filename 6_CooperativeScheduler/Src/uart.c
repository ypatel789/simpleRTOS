#include <stdint.h>
#include "uart.h"
#include "stm32f4xx.h"

#define GPIOAEN		      (1U<<0)
#define UART2EN           (1U<<17)

#define SYS_FREQ          16000000
#define APB1_CLK          SYS_FREQ
#define UART_BAUDRATE     115200
#define CR1_TE            (1U<<3)
#define CR1_UE            (1U<<13)

#define SR_TXE            (1U<<7)

static uint16_t compute_uart_bd(uint32_t periphclock, uint32_t baudrate);
static void uart_set_baudrate(uint32_t periphclock, uint32_t baudrate);
static void uart_write(int ch);

int __io_putchar(int ch)
{
	uart_write(ch);
	return ch;
}

void uart_tx_init(void)
{
	/* Enable Clock access to GPIOA */
	RCC->AHB1ENR |= GPIOAEN;

	/* Set PA2 mode to alternate function mode - reference manual, search 'moder' set pin to alternate function pin*/
	GPIOA->MODER &=~(1U<<4);
	GPIOA->MODER |=(1U<<5);

	/* Set alternate function type to AF7 (UART2_TX) - reference manual pg161, Pin2 is AFRL2 bits 8,9,10,11, want to set it to AF7:0111*/
	GPIOA->AFR[0] |= (1U<<8); // there are no AFRL in .h files it is an array and accessing AFRL is done by AFR[0]
	GPIOA->AFR[0] |= (1U<<9);
	GPIOA->AFR[0] |= (1U<<10);
	GPIOA->AFR[0] &= ~(1U<<11);

	/* Enable clock access to UART - Datasheet - pg15 shows USART2 is connect via APB1 bus.
	 * Go to RM, find apb1enr. on the page118 it shows that if we set bit17 to 1 we will enable USART2 clock access */
	RCC->APB1ENR |= UART2EN;

	/* Configure baudrate */
	uart_set_baudrate(APB1_CLK, UART_BAUDRATE);

	/* Configure transfer direction - RM - search USART_CR1 - bit 3 if set to 1 it will enable transfer */
	USART2->CR1 = CR1_TE; // no logical OR used here as we want to set every other bit to 0 besides bit 3

	/* Enable UART module same page as above search - bit 13 if set to 1 will enable to USART module*/
	USART2->CR1 |= CR1_UE;
}

static void uart_write(int ch)
{
	/* Make sure the transmit data register is empty - RM - USART_SR (status register) - Bit7 is what we are interested in for this one */
	while (!(USART2->SR & SR_TXE)){}

	/* Write to transmit data register */
	USART2->DR = (ch & 0XFF);
}

static void uart_set_baudrate(uint32_t periphclock, uint32_t baudrate)
{
	USART2->BRR = compute_uart_bd(periphclock, baudrate);

}

static uint16_t compute_uart_bd(uint32_t periphclock, uint32_t baudrate)
{
	return ((periphclock + (baudrate/2U))/baudrate);
}
