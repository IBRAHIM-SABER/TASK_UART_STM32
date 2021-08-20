/*
 * UART_program.c
 *
 *  Created on: Jul 2, 2021
 *      Author: ibrahim
 */

#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "STM32F103C8.h"

#include "UART_interface.h"
#include "UART_config.h"
#include "UART_private.h"


static USART_REGISTERs_t * USARTx[3] = {USART1, USART2, USART3};
static void (*TX_CALL_BACK[3])(void) = {NULL};
static void (*RX_CALL_BACK[3])(u8)   = {NULL};

u8 UART_u8SetUartConfigurations(const USART_Configs_t * Copy_structUartConfigs)
{
	u8 LOC_u8ErrorState = STATE_OK;
	if( Copy_structUartConfigs != NULL )
	{
		/* Disable the USART */
		CLR_BIT(USARTx[Copy_structUartConfigs->UART_ChannelID]->CR1 , UE);
		/* Set Baud Rate */
		u32 LOC_u32Mantissa = ( F_CPU ) / ( 16 * Copy_structUartConfigs->UART_BaudRate ) ;

		u32 LOC_u32Fraction = ( ( ( F_CPU * 100 ) / ( 16 * Copy_structUartConfigs->UART_BaudRate  )  ) % 100 ) * 16 ;

		if( LOC_u32Fraction > 1500 )
		{
			LOC_u32Mantissa += 1 ;
			LOC_u32Fraction  = 0 ;
		}
		USARTx[Copy_structUartConfigs->UART_ChannelID]->BRR = (LOC_u32Mantissa << 4) | (LOC_u32Fraction/100);
		USARTx[Copy_structUartConfigs->UART_ChannelID]->CR1 |= Copy_structUartConfigs->UART_Data | Copy_structUartConfigs->UART_Parity | Copy_structUartConfigs->UART_Interrupt ;
		USARTx[Copy_structUartConfigs->UART_ChannelID]->CR1 |=  Copy_structUartConfigs->UART_TX | Copy_structUartConfigs->UART_RX;
		USARTx[Copy_structUartConfigs->UART_ChannelID]->CR2 |= Copy_structUartConfigs->UART_Stop ;
		/* Enable the USART */
		SET_BIT(USARTx[Copy_structUartConfigs->UART_ChannelID]->CR1 , UE);
	}
	else
	{
		LOC_u8ErrorState = STATE_NOK;
	}

	return LOC_u8ErrorState;
}

u8 UART_u8TransmitChar_POL(USART_Channel_t Copy_enumUartChannelId, u8 Copy_u8Character)
{
	u8 LOC_ErrorState = STATE_OK;
	u32 Local_u32Counter = 0;
	if(Copy_enumUartChannelId <= USART_3)
	{
		USARTx[Copy_enumUartChannelId]->DR = Copy_u8Character;
		while(!GET_BIT(USARTx[Copy_enumUartChannelId]->SR , TC ))
		{
			Local_u32Counter++;
			if(Local_u32Counter == 100000)
			{
				LOC_ErrorState = STATE_NOK;
				break;
			}
		}
		/* Clear the flag */
		CLR_BIT(USARTx[Copy_enumUartChannelId]->SR, TC);
	}
	else
	{
		LOC_ErrorState = STATE_NOK;
	}
	return LOC_ErrorState;
}
u8 UART_u8TransmitString_POL(USART_Channel_t Copy_enumUartChannelId, u8 * Copy_u8DataBuffer, u8 Copy_BufferSize)
{

	u8 LOC_ErrorState = STATE_OK ;
	u8 LOC_LoopIterator =0;
	if( Copy_enumUartChannelId<= USART_3  )
	{
		/* Send the data character at time and repeat the sending with the data size    */
		for(LOC_LoopIterator = 0; LOC_LoopIterator < Copy_BufferSize; LOC_LoopIterator++ )
		{
			LOC_ErrorState = UART_u8TransmitChar_POL(Copy_enumUartChannelId, Copy_u8DataBuffer[LOC_LoopIterator]);
			if ( LOC_ErrorState == STATE_NOK )
			{
				/* It means that an error has been happened so return Not Ok */
				return STATE_NOK;
			}
		}
	}
	else
	{
		LOC_ErrorState = STATE_NOK;
	}
	return LOC_ErrorState;

}
u8 UART_u8ReceiveChar_POL (USART_Channel_t Copy_enumUartChannelId, u8 * Copy_u8CharacterBuffer)
{
	u8 Local_u8ErrorState = STATE_OK;
	u32 Local_u32Counter = 0;
	/* Clear the flag */
	CLR_BIT(USARTx[Copy_enumUartChannelId]->SR , RXNE);
	if(Copy_enumUartChannelId <= USART_3)
	{
		while( (GET_BIT((USARTx[Copy_enumUartChannelId] -> SR), RXNE)) == 0 )
		{
			Local_u32Counter++;
			if (Local_u32Counter == 100000)
			{
				Local_u8ErrorState = STATE_NOK;
				break;
			}
		}

		if((GET_BIT((USARTx[Copy_enumUartChannelId] -> SR), RXNE)) == 1)
		{
			*Copy_u8CharacterBuffer = USARTx[Copy_enumUartChannelId]->DR;
		}

	}
	else{
		Local_u8ErrorState = STATE_NOK;
	}

	return (Local_u8ErrorState);
}

u8 UART_u8ReceiveString_POL(USART_Channel_t Copy_enumUartChannelId , u8 * Copy_u8DataBuffer, u8 Copy_BufferSize)
{
	u8 LOC_ErrorState = STATE_OK ;
	u8 LOC_LoopIterator = 0;
	if( Copy_enumUartChannelId <= USART_3)
	{
		if( Copy_u8DataBuffer != NULL )
		{
			/* Receive the data character at time and repeat the Receiving with the data size    */
			for (LOC_LoopIterator = 0; LOC_LoopIterator < Copy_BufferSize; LOC_LoopIterator++ )
			{
				LOC_ErrorState = UART_u8ReceiveChar_POL(Copy_enumUartChannelId, (Copy_u8DataBuffer + LOC_LoopIterator  ) );
				if( LOC_ErrorState ==STATE_NOK )
				{
					/* It means that an error has been happened so return Not Ok */
					return STATE_NOK;
				}
			}
		}
		else
		{
			LOC_ErrorState = STATE_NOK;
		}

	}
	else
	{
		LOC_ErrorState = STATE_NOK;
	}
	return LOC_ErrorState;

}

u8 UART_u8SetTXCallBack(USART_Channel_t Copy_enumUARTChannel, void(*PtrFunc)(void) )
{
	u8 LOC_ErrorState = STATE_OK ;
	if( Copy_enumUARTChannel <= USART_3)
	{
		if(PtrFunc != NULL)
		{
			TX_CALL_BACK[Copy_enumUARTChannel] = PtrFunc;
		}
		else
		{
			LOC_ErrorState = STATE_NOK;
		}
	}
	else
	{
		LOC_ErrorState = STATE_NOK;
	}
	return LOC_ErrorState;
}
u8 UART_u8SetRXCallBack(USART_Channel_t Copy_enumUARTChannel, void(*PtrFunc)(u8) )
{
	u8 LOC_ErrorState = STATE_OK ;
	if( Copy_enumUARTChannel <= USART_3)
	{
		if(PtrFunc != NULL)
		{
			RX_CALL_BACK[Copy_enumUARTChannel] = PtrFunc;
		}
		else
		{
			LOC_ErrorState = STATE_NOK;
		}
	}
	else
	{
		LOC_ErrorState = STATE_NOK;
	}
	return LOC_ErrorState;
}

u8 UART_u8EnableTXInterrupt (USART_Channel_t Copy_enumUartChannelId)
{
	u8 LOC_ErrorState = STATE_OK;
	if( Copy_enumUartChannelId <= USART_3)
	{
		SET_BIT(USARTx[Copy_enumUartChannelId]->CR1, TXEIE);
	}
	else
	{
		LOC_ErrorState = STATE_NOK;
	}
	return LOC_ErrorState;

}
u8 UART_u8DisableTXInterrupt(USART_Channel_t Copy_enumUartChannelId)
{
	u8 LOC_ErrorState = STATE_OK;
	if( Copy_enumUartChannelId <= USART_3)
	{
		CLR_BIT(USARTx[Copy_enumUartChannelId]->CR1, TXEIE);
	}
	else
	{
		LOC_ErrorState = STATE_NOK;
	}
	return LOC_ErrorState;
}

u8 UART_u8EnableRXInterrupt (USART_Channel_t Copy_enumUartChannelId)
{
	u8 LOC_ErrorState = STATE_OK;
	if( Copy_enumUartChannelId <= USART_3)
	{
		SET_BIT(USARTx[Copy_enumUartChannelId]->CR1, RXNEIE);
	}
	else
	{
		LOC_ErrorState = STATE_NOK;
	}
	return LOC_ErrorState;
}
u8 UART_u8DisableRXInterrupt(USART_Channel_t Copy_enumUartChannelId)
{
	u8 LOC_ErrorState = STATE_OK;
	if( Copy_enumUartChannelId <= USART_3)
	{
		SET_BIT(USARTx[Copy_enumUartChannelId]->CR1, RXNEIE);
	}
	else
	{
		LOC_ErrorState = STATE_NOK;
	}
	return LOC_ErrorState;
}

void USART1_IRQHandler(void)
{
	if( GET_BIT(USARTx[USART_1]->SR, TC) == 1 )
	{
		if(TX_CALL_BACK[USART_1] != NULL)
		{
			TX_CALL_BACK[USART_1]();
		}
		CLR_BIT(USARTx[USART_1]->SR, TC);
	}
	else if( GET_BIT(USARTx[USART_1]->SR, RXNE) == 1 )
	{
		if( RX_CALL_BACK[USART_1] != NULL )
		{
			RX_CALL_BACK[USART_1]( USARTx[USART_1]->DR );
		}
		CLR_BIT(USARTx[USART_1]->SR, RXNE);
	}
}
void USART2_IRQHandler(void)
{
	if( GET_BIT(USARTx[USART_2]->SR, TC) == 1 )
	{
		if(TX_CALL_BACK[USART_2] != NULL)
		{
			TX_CALL_BACK[USART_2]();
		}
		CLR_BIT(USARTx[USART_2]->SR, TC);
	}
	else if( GET_BIT(USARTx[USART_2]->SR, RXNE) == 1 )
	{
		if( RX_CALL_BACK[USART_2] != NULL )
		{
			RX_CALL_BACK[USART_2]( USARTx[USART_2]->DR );
		}
		CLR_BIT(USARTx[USART_2]->SR, RXNE);
	}
}
void USART3_IRQHandler(void)
{
	if( GET_BIT(USARTx[USART_3]->SR, TC) == 1 )
	{
		if(TX_CALL_BACK[USART_3] != NULL)
		{
			TX_CALL_BACK[USART_3]();
		}
		CLR_BIT(USARTx[USART_3]->SR, TC);
	}
	else if( GET_BIT(USARTx[USART_3]->SR, RXNE) == 1 )
	{
		if( RX_CALL_BACK[USART_3] != NULL )
		{
			RX_CALL_BACK[USART_3]( USARTx[USART_3]->DR );
		}
		CLR_BIT(USARTx[USART_3]->SR, RXNE);
	}
}
