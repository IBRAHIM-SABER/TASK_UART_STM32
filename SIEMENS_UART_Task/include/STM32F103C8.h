/*************************************************************************************/
/** author 		: Ibrahim Saber 													 */
/** Date   		: 6/5/2021															 */
/** Version 	: V00																 */
/** SWC			: STM32F130C8 Registers 											 */
/*************************************************************************************/


#ifndef STM32F130C8_REGISTERS_H_
#define STM32F130C8_REGISTERS_H_

/**************************************************************************************/
/************************ RCC Registers Definitions	***********************************/
typedef struct{
	volatile u32 CR		  ;
	volatile u32 CFGR	  ;
	volatile u32 CIR 	  ;
	volatile u32 APB2RSTR ;
	volatile u32 APB1RSTR ;
	volatile u32 AHBENR   ;
	volatile u32 APB2ENR  ;
	volatile u32 APB1ENR  ;
	volatile u32 BDCR	  ;
	volatile u32 CSR	  ;

}RCC_REG;

#define RCC		( (volatile RCC_REG *) 0x40021000 )

/***************************************************************************************/

/***************************************************************************************/
/******************** GPIO Registers Definitions	****************************************/
#define GPIOA_BASE_ADDRESS 			0x40010800
#define GPIOB_BASE_ADDRESS 			0x40010C00
#define GPIOC_BASE_ADDRESS 			0x40011000
#define GPIOD_BASE_ADDRESS			0x40011000

typedef struct {

	volatile u32 CRL;
	volatile u32 CRH;
	volatile u32 IDR;
	volatile u32 ODR;
	volatile u32 BSRR;
	volatile u32 BRR;
	volatile u32 LCKR;

}GPIO_REGISTERS;

#define GPIOA				( ( GPIO_REGISTERS * const ) GPIOA_BASE_ADDRESS)
#define GPIOB				( ( GPIO_REGISTERS * const ) GPIOB_BASE_ADDRESS)
#define GPIOC				( ( GPIO_REGISTERS * const ) GPIOC_BASE_ADDRESS)
#define GPIOD				( ( GPIO_REGISTERS * const ) GPIOD_BASE_ADDRESS)

/*******************************************************************************************/

/*******************************************************************************************/
/******************** NVIC Registers Definitions	****************************************/

#define NVIC_BASE_ADDRESS 			0xE000E100

typedef struct {

	volatile u32 ISER[8];
	volatile u32 RESERVED1[24];
	volatile u32 ICER[8];
	volatile u32 RESERVED2[24];
	volatile u32 ISPR[8];
	volatile u32 RESERVED3[24];
	volatile u32 ICPR[8];
	volatile u32 RESERVED4[24];
	volatile u32 IABR[8];
	volatile u32 RESERVED5[56];
	volatile u8 IPR[240];


}NVIC_REG;

#define NVIC			( ( NVIC_REG*const ) NVIC_BASE_ADDRESS )
/*************************************************************************************************/
/*************************************************************************************************/
/******************** EXTI Registers Definitions	**********************************************/

#define EXTI_BASE_ADDRESS 	0x40010400
typedef struct{

	volatile u32 EXTI_IMR;
	volatile u32 EXTI_EMR;
	volatile u32 EXTI_TSR[2];
	volatile u32 EXTI_SWIER;
	volatile u32 EXTI_PR;

}EXTI_REGISTERS;

#define EXTI				( (volatile EXTI_REGISTERS * const) EXTI_BASE_ADDRESS)

/*************************************************************************************************/
/*************************************************************************************************/
/******************** SYSTICK Registers Definitions	**********************************************/

#define SYSTICK_BASE_ADDRESS 		0xE000E010
typedef struct{

	volatile u32 CTRL	;
	volatile u32 LOAD	;
	volatile u32 VAL	;
	volatile u32 CALIB	;

}SYSTICK_REGISTERS_DEF;

#define STK					( ( SYSTICK_REGISTERS_DEF * const ) SYSTICK_BASE_ADDRESS )

/*************************************************************************************************/
/*************************************************************************************************/
/******************** UART Registers	**********************************************************/

#define USART1_BASE_ADDRESS		0x40013800
#define USART2_BASE_ADDRESS		0x40004400
#define USART3_BASE_ADDRESS		0x40004800

typedef struct
{
	volatile u32 SR;
	volatile u32 DR;
	volatile u32 BRR;
	volatile u32 CR1;
	volatile u32 CR2;
	volatile u32 CR3;
	volatile u32 GRPR;

}USART_REGISTERs_t;

#define USART1    (( USART_REGISTERs_t * )USART1_BASE_ADDRESS)
#define USART2    (( USART_REGISTERs_t * )USART2_BASE_ADDRESS)
#define USART3    (( USART_REGISTERs_t * )USART3_BASE_ADDRESS)




#endif
