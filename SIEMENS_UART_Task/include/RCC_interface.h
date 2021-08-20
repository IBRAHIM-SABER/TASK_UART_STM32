/*************************************************************************************/
/** author 		: Ibrahim Saber 													 */
/** Date   		: 6/5/2021															 */
/** Version 	: V00																 */
/*************************************************************************************/


#ifndef RCC_INTERFACE_H_
#define RCC_INTERFACE_H_

#define PLL_ON   			24
#define HSE_ON				16
#define HSI_ON				0
#define HSE_BYP				18
#define PLL_READY  		 	25
#define HSE_READY  			17
#define HSI_READY   		1

typedef enum
{
	NOK ,
	OK
}ERROR_STATUS;
typedef enum{
	AHB_BUS  ,
	APB1_BUS ,
	APB2_BUS
}RCC_BUS;

typedef enum{
	DMA2_CLK 	,
	DMA1_CLK	,
	SRAM_CLK	,
	FLITF_CLK = 4 	,
	CRCE_CLK  = 6 	,
	FSMC_CLK  = 8 	,
	SDIO_CLK  = 10	,
	AFIO_CLK  = 0	,
	GPIOA_CLK = 2	,
	GPIOB_CLK		,
	GPIOC_CLK		,
	GPIOD_CLK		,
	GPIOE_CLK		,
	GPIOF_CLK		,
	GPIOG_CLK		,
	ADC1_CLK		,
	ADC2_CLK		,
	TIM1_CLK		,
	SPI1_CLK		,
	TIM8_CLK		,
	USART1_CLK		,
	ADC3_CLK		,
	TIM9_CLK  = 19	,
	TIM10_CLK		,
	TIM11_CLK		,
	TIM2_CLK  = 0	,
	TIM3_CLK		,
	TIM4_CLK		,
	TIM5_CLK		,
	TIM6_CLK		,
	TIM7_CLK		,
	TIM12_CLK		,
	TIM13_CLK		,
	TIM14_CLK		,
	WWDG_CLK		,
	SPI2_CLK  = 14 	,
	SPI3_CLK		,
	USART2_CLK = 17 ,
	USART3_CLK		,
	USART4_CLK		,
	USART5_CLK		,
	I2C1_CLK		,
	I2C2_CLK		,
	USB_CLK			,
	CAN_CLK  = 25	,
	BKP_CLK  = 27	,
	PWR_CLK			,
	DAC_CLK			,

}PERIPHERALS;



typedef enum{
	RCC_HSE_SRC			= 0b01,
	RCC_HSE_BYBASS_SRC 	= 0b011,
	RCC_HSI_SRC			= 0b00,
	RCC_PLL_SRC			= 0b10
}CLOCK_SOURCE;

typedef enum{
	RCC_HSE			= (0 << 17)|(1<<16) ,
	RCC_HSE_DEV_2	= (1 << 17)|(1<<16)	,
	RCC_HSI_DEV_2 	= 0 << 16

}PLL_SOURCE;

typedef enum{
	NO_CLOCK 		= 0b000 << 24 ,
	SYSTEM_CLOCK 	= 0b100 << 24 ,
	HSI_CLOCK 		= 0b101 << 24 ,
	HSE_CLOCK	 	= 0b110 << 24 ,
	PLL_DEV_2 		= 0b111 << 24
	
}OUTPUT_CLOCK;

typedef enum {
	PLL_CLK_2	=	0b0000 << 18 ,
	PLL_CLK_3	=	0b0001 << 18 ,
	PLL_CLK_4	=	0b0010 << 18 ,
	PLL_CLK_5	=	0b0011 << 18 ,
	PLL_CLK_6	=	0b0100 << 18 ,
	PLL_CLK_7	=	0b0101 << 18 ,
	PLL_CLK_8	=	0b0110 << 18 ,
	PLL_CLK_9	=	0b0111 << 18 ,
	PLL_CLK_10	=	0b1000 << 18 ,
	PLL_CLK_11	=	0b1001 << 18 ,
	PLL_CLK_12	=	0b1010 << 18 ,
	PLL_CLK_13	=	0b1011 << 18 ,
	PLL_CLK_14	=	0b1100 << 18 ,
	PLL_CLK_15	=	0b1101 << 18 ,
	PLL_CLK_16	=	0b1110 << 18 
}PLL_MUL_FACTPR;

typedef enum {
	APB2_HCLK_NO_PRE = (0b000 << 11),
	APB2_HCLK_DEV_2  = (0b100 << 11),
	APB2_HCLK_DEV_4  = (0b101 << 11),
	APB2_HCLK_DEV_8  = (0b110 << 11),
	APB2_HCLK_DEV_16 = (0b111 << 11)
}APB2_PRESCALLER;

typedef enum {
	APB1_HCLK_NO_PRE = (0b000 << 8),
	APB1_HCLK_DEV_2  = (0b100 << 8),
	APB1_HCLK_DEV_4  = (0b101 << 8),
	APB1_HCLK_DEV_8  = (0b110 << 8),
	APB1_HCLK_DEV_16 = (0b111 << 8)
}APB1_PRESCALLER;

typedef enum {
	SYS_CLK_NO_PRE  = (0b0000 << 4),
	SYS_CLK_DEV_2   = (0b1000 << 4),
	SYS_CLK_DEV_4   = (0b1001 << 4),
	SYS_CLK_DEV_8   = (0b1010 << 4),
	SYS_CLK_DEV_16  = (0b1011 << 4),
	SYS_CLK_DEV_64  = (0b1100 << 4),
	SYS_CLK_DEV_128 = (0b1101 << 4),
	SYS_CLK_DEV_256 = (0b1110 << 4),
	SYS_CLK_DEV_512 = (0b1111 << 4)
}AHB_PRESCALLER;

typedef struct{
	
	CLOCK_SOURCE SYS_CLK ;
	OUTPUT_CLOCK OUT_CLK ;
	PLL_SOURCE PLL_SRC  ;
	PLL_MUL_FACTPR PLL_FACTOR;
	APB2_PRESCALLER APB2_SCLR;
	APB1_PRESCALLER APB1_SCLR;
	AHB_PRESCALLER  AHB_SCLR;
}RCC_CONFIGS;

void RCC_voidInitSystemClock(void);
ERROR_STATUS RCC_enumConfigSystemClock(RCC_CONFIGS * Copy_structConfigurations);
void RCC_voidEnable_PeripheralCLOCK( RCC_BUS Copy_enumBus, PERIPHERALS Copy_enumPeripheral );
void RCC_voidDisable_PeripheralCLOCK( RCC_BUS Copy_enumBus, PERIPHERALS Copy_enumPeripheral );

#endif
