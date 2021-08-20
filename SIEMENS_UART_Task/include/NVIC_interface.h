/************************************************************************************/
/*** Author 	: Ibrahim Saber Mohamed Ahmed 									*****/
/*** Version  	: V01 															*****/
/*** SOC		: NVIC															*****/
/************************************************************************************/

#ifndef NVIC_INTERFACE_H_
#define NVIC_INTERFACE_H_

typedef enum{
	WWDG_IRQ	,
	PVD_IRQ		,
	TAMPER_IRQ	,
	RTC_IRQ		,
	FLASH_IRQ	,
	RCC_IRQ	,
	EXTI0_IRQ	,
	EXTI1_IRQ	,
	EXTI2_IRQ	,
	EXTI3_IRQ	,
	EXTI4_IRQ	,
	DMA1_Channel1_IRQ	,
	DMA1_Channel2_IRQ	,
	DMA1_Channel3_IRQ	,
	DMA1_Channel4_IRQ	,
	DMA1_Channel5_IRQ	,
	DMA1_Channel6_IRQ	,
	DMA1_Channel7_IRQ	,
	ADC1_2_IRQ			,
	USB_HP_CAN_TX_IRQ	,
	USB_LP_CAN_RX0_IRQ	,
	CAN_RX1_IRQ			,
	CAN_SCE_IRQ			,
	EXTI9_5_IRQ			,
	TIM1_BRK_IRQ		,
	TIM1_UP_IRQ			,
	TIM1_TRG_COM_IRQ	,
	TIM1_CC_IRQ			,
	TIM2_IRQ			,
	TIM3_IRQ			,
	TIM4_IRQ			,
	I2C1_EV_IRQ			,
	I2C1_ER_IRQ			,
	I2C2_EV_IRQ			,
	I2C2_ER_IRQ			,
	SPI1_IRQ			,
	SPI2_IRQ			,
	USART1_IRQ			,
	USART2_IRQ			,
	USART3_IRQ			,
	EXTI15_10_IRQ		,
	RTCAlarm_IRQ		,
	USBWakeup_IRQ		,
	TIM8_BRK_IRQ		,
	TIM8_UP_IRQ			,
	TIM8_TRG_COM_IRQ	,
	TIM8_CC_IRQ			,
	ADC3_IRQ			,
	FSMC_IRQ			,
	SDIO_IRQ			,
	TIM5_IRQ			,
	SPI3_IRQ			,
	UART4_IRQ			,
	UART5_IRQ			,
	TIM6_IRQ			,
	TIM7_IRQ			,
	DMA2_Channel1_IRQ	,
	DMA2_Channel2_IRQ	,
	DMA2_Channel3_IRQ	,
	DMA2_Channel4_5_IRQ	,
	
}INTERRUPT_NUMBER;

u8 NVIC_u8EnableInterrupt ( INTERRUPT_NUMBER Copy_enumIRQN );
u8 NVIC_u8DisableInterrupt( INTERRUPT_NUMBER Copy_enumIRQN );
u8 NVIC_u8SetPendingFlag  ( INTERRUPT_NUMBER Copy_enumIRQN );
u8 NVIC_u8ClearPendingFlag( INTERRUPT_NUMBER Copy_enumIRQN );
u8 NVIC_u8GetActiveFlag   ( INTERRUPT_NUMBER Copy_enumIRQN , u8*Copy_ptrReturnValue );
u8 NVIC_u8SetPriorty(INTERRUPT_NUMBER Copy_enumIRQN, u8 Copy_u8GroupPriorty, u8 Copy_u8SubPriorty);
u8 NVIC_u8ConfigurePriority(void);


#endif
