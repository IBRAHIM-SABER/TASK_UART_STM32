/*
 * main.c
 *
 *  Created on: Aug 20, 2021
 *      Author: ibrahim Saber Mohammed Ahmed
 */

#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "STM32F103C8.h"

#include "RCC_interface.h"
#include "GPIO_interface.h"
#include "UART_interface.h"
#include "NVIC_interface.h"

volatile u8 Flag  = 0;
volatile u8 ReceivedCharacter = 0;
void UART1_IRQ(u8 Copy_u8Character)
{
	Flag = 1;
	ReceivedCharacter = Copy_u8Character;
}
int main(void)
{

	RCC_CONFIGS ClockCofigurations;
	ClockCofigurations.SYS_CLK = RCC_HSI_SRC;
	ClockCofigurations.APB1_SCLR = APB1_HCLK_NO_PRE;
	ClockCofigurations.APB2_SCLR = APB2_HCLK_NO_PRE;
	ClockCofigurations.AHB_SCLR = SYS_CLK_NO_PRE;
	ClockCofigurations.OUT_CLK = NO_CLOCK;
	ClockCofigurations.PLL_SRC = RCC_HSI_DEV_2;
	ClockCofigurations.PLL_FACTOR = PLL_DEV_2;
	RCC_enumConfigSystemClock(&ClockCofigurations);

	RCC_voidEnable_PeripheralCLOCK(APB2_BUS, GPIOA_CLK);
	RCC_voidEnable_PeripheralCLOCK(APB2_BUS, USART1_CLK);

	GPIO_PIN_CONFIGS Uart_tx = {PORTA, PIN9 , ALTERANTE_PUSH_PULL_10_MHz};
	GPIO_PIN_CONFIGS Uart_rx = {PORTA, PIN10, INPUT_PULL_UP };
	GPIO_u8SetPinDirection(&Uart_tx);
	GPIO_u8SetPinDirection(&Uart_rx);

	USART_Configs_t Uart1 ;
	Uart1.UART_BaudRate = 9600;
	Uart1.UART_ChannelID = USART_1;
	Uart1.UART_Data = EIGHT_BITS;
	Uart1.UART_Parity = NO_PARITY;
	Uart1.UART_RX = UART_RXEnable;
	Uart1.UART_TX = UART_TXEnable;
	Uart1.UART_Stop = ONE_STOP;
	Uart1.UART_Interrupt = RX_ENABLE_INTERRUPT;
	UART_u8SetUartConfigurations(&Uart1);

	UART_u8SetRXCallBack(USART_1, UART1_IRQ);

	NVIC_u8EnableInterrupt(USART1_IRQ);


	while(1)
	{
		if(Flag == 1)
		{
			if(ReceivedCharacter >= 0x61 && ReceivedCharacter <= 0x7A)
			{
				ReceivedCharacter -=0x20;
				UART_u8TransmitChar_POL(USART_1,ReceivedCharacter);
			}
			else
			{
				ReceivedCharacter +=0x1;
				UART_u8TransmitChar_POL(USART_1,ReceivedCharacter);
			}
			Flag = 0;
			ReceivedCharacter = 0;
		}
	}
	return 0;
}

