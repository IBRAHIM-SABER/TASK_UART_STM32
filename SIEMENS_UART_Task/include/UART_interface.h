/*
 * UART_interface.h
 *
 *  Created on: Jul 2, 2021
 *      Author: ibrahim
 */

#ifndef UART_INTERFACE_H_
#define UART_INTERFACE_H_


typedef enum{
    USART_1  ,
    USART_2  ,
    USART_3  ,
}USART_Channel_t;


typedef enum{
   ONE_STOP = (0b00 << 12 ),
   TWO_STOP = (0b10 << 12 )
}UART_Stop_Bit_t;

typedef enum{
    NO_PARITY   = (0b0 << 10) ,
    EVEN_PARITY = (0b1 << 10) | (0b0 << 9),
    ODD_PARITY  = (0b0 << 10) | (0b1 << 9)
}UART_Parity_t;

typedef enum{
    EIGHT_BITS = (0b0 << 12) ,
	NINE_BITS  = (0b1 << 12)
}UART_Dtat_Length_t;

typedef enum
{
    UART_TXEnable   = (1 << 3),
    UART_TXDisable  = (0 << 3),
}UART_TXMode_t;

typedef enum
{
    UART_RXEnable   = (1 << 2),
    UART_RXDisable  = (0 << 2),
}UART_RXMode_t;


typedef enum{

    TX_ENABLE_INTERRUPT    = (0b1 << 7) ,
    TX_DISABEL_INTERRuPT   = (0b0 << 7),
    RX_ENABLE_INTERRUPT    = (0b1 << 5),
    RX_DISABEL_INTERRuPT   = (0b0 << 5),
}UART_Interrupt_t;


typedef struct {
	USART_Channel_t       UART_ChannelID    ;
    u32                   UART_BaudRate     ;
    UART_TXMode_t         UART_TX           ;
    UART_RXMode_t         UART_RX           ;
    UART_Dtat_Length_t    UART_Data         ;
    UART_Parity_t         UART_Parity       ;
    UART_Stop_Bit_t       UART_Stop         ;
    UART_Interrupt_t      UART_Interrupt    ;

}USART_Configs_t;


u8 UART_u8SetUartConfigurations(const USART_Configs_t * Copy_structUartConfigs);

u8 UART_u8SetTXCallBack(USART_Channel_t Copy_enumUARTChannel, void(*PtrFunc)(void) );
u8 UART_u8SetRXCallBack(USART_Channel_t Copy_enumUARTChannel, void(*PtrFunc)(u8) );

u8 UART_u8EnableTXInterrupt (USART_Channel_t Copy_enumUartChannelId);
u8 UART_u8DisableTXInterrupt(USART_Channel_t Copy_enumUartChannelId);

u8 UART_u8EnableRXInterrupt (USART_Channel_t Copy_enumUartChannelId);
u8 UART_u8DisableRXInterrupt(USART_Channel_t Copy_enumUartChannelId);

u8 UART_u8TransmitChar_POL(USART_Channel_t Copy_enumUartChannelId, u8 Copy_u8Character);
u8 UART_u8ReceiveChar_POL (USART_Channel_t Copy_enumUartChannelId, u8 * Copy_u8CharacterBuffer);

u8 UART_u8TransmitString_POL(USART_Channel_t Copy_enumUartChannelId, u8 * Copy_u8DataBuffer, u8 Copy_BufferSize);
u8 UART_u8ReceiveString_POL(USART_Channel_t Copy_enumUartChannelId , u8 * Copy_u8DataBuffer, u8 Copy_BufferSize);




#endif /* UART_INTERFACE_H_ */
