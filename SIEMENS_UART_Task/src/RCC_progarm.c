#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "STM32F103C8.h"

#include  "RCC_interface.h"
#include  "RCC_config.h"
#include  "RCC_private.h"

void RCC_voidInitSystemClock(void)
{
	u32 LOC_u32TimeOut = 0;
#if  SYS_CLOCK == HSI_CLK
	RCC->CFGR &=~( (0b11) << 0 );
	RCC->CFGR |= HSI_CLK;
	SET_BIT( RCC->CR, HSI_ON );
	while( GET_BIT(RCC->CR, HSI_READY) == 0 )
	{
		LOC_u32TimeOut++;
		if ( LOC_u32TimeOut == 1000000 )
		{
			/* Time Out  */
		}
	}

#elif  SYS_CLOCK == HSE_CLK
	RCC->CFGR &=~( (0b11) << 0 );
	RCC->CFGR |= HSE_CLK;
	SET_BIT( RCC->CR, HSE_ON );
	while( GET_BIT(RCC->CR, HSE_READY) == 0 )
	{
		LOC_u32TimeOut++;
		if ( LOC_u32TimeOut == 10000 )
		{
			/* Time Out  */
		}
	}

#elif SYS_CLOCK == PLL_CLK
	RCC->CFGR &=~( (0b11) << 0 );
	RCC->CFGR |= PLL_CLK | PLL_CLK_SOURC ;
# if PLL_MULTIPLY_FACTOR >=2 && PLL_MULTIPLY_FACTOR<=16
	RCC->CFGR &= ~( ( 0b1111 )     << 18 ) ;
	RCC-<CFGR |= ( (PLL_MULTIPLY_FACTOR - 2 ) << 18 );
# elif PLL_MULTIPLY_FACTOR >16 || PLL_MULTIPLY_FACTOR<2
# warning "Wrong Multiply factor"
#endif
	SET_BIT( RCC->CR, PLL_ON );
	while( ( GET_BIT( RCC->CR, PLL_READY ) ) == 0 )
	{
		LOC_u32TimeOut++;
		if ( LOC_u32TimeOut == 10000 )
		{
			/* Time Out  */
		}
	}
#elif SYS_CLOCK == HSE_BYPASS_CLK
	CLR_BIT( RCC->CR , HSE_ON );
	SET_BIT( RCC->CR , HSE_BYP );
	RCC->CFGR &=~( (0b11) << 0 );
	RCC->CFGR |= ( HSE_BYPASS_CLK >> 1 );
	SET_BIT( RCC->CR , HSE_ON);
	while( ( GET_BIT( RCC->CR, HSE_READY ) ) == 0 )
	{
		LOC_u32TimeOut++;
		if( LOC_u32TimeOut >= 100000 )
		{
			LOC_enumState = NOK;
			/*TimeOut*/
		}
	}
#else
#warning   " Wrong Clock Configurations "
#endif
}

ERROR_STATUS RCC_enumConfigSystemClock(RCC_CONFIGS * Copy_structConfigurations)
{
	/* Time out variable to terminate the pooling While loop */
	u32 LOC_u32TimeOut = 0;
	ERROR_STATUS LOC_enumState = OK;
	if ( Copy_structConfigurations->SYS_CLK == RCC_PLL_SRC )
	{
		/* Selecting the PLL Source and the PLL Multiply Factor and the Selecting PLL as the Source of System */
		RCC->CFGR &= ~( ( 0b1111 )     << 18 ) ;
		RCC->CFGR |= Copy_structConfigurations->PLL_SRC | Copy_structConfigurations->PLL_FACTOR | Copy_structConfigurations->SYS_CLK;
		/* Enabling the PLL  */
		SET_BIT(RCC->CR, PLL_ON);
		/* Pooling the PLL_READY flag until the Clock is stable */
		/* Time out will return Error LOC_enumState and Break the While loop */
		while( ( GET_BIT( RCC->CR, PLL_READY ) ) == 0 )
		{
			LOC_u32TimeOut++;
			if( LOC_u32TimeOut >= 100000 )
			{
				LOC_enumState = NOK;
				/*TimeOut Handler*/
				break;
			}
		}
	}
	else if(Copy_structConfigurations->SYS_CLK == RCC_HSE_SRC)
	{
		/* Selecting the Source */
		RCC->CFGR &=~( (0b11) << 0 );
		RCC->CFGR |= Copy_structConfigurations->SYS_CLK;
		/* Enable the HSE */
		SET_BIT(RCC->CR , HSE_ON);
		/* Pooling the HSE_READY flag until the Clock is stable */
		/* Time out will return Error LOC_enumState and Break the While loop */
		while( ( GET_BIT( RCC->CR, HSE_READY ) ) == 0 )
		{
			LOC_u32TimeOut++;
			if( LOC_u32TimeOut >= 100000 )
			{
				LOC_enumState = NOK;
				/*TimeOut*/
				break;
			}
		}
	}
	else if(Copy_structConfigurations->SYS_CLK == RCC_HSI_SRC)
	{
		RCC->CFGR &=~( (0b11) << 0 );
		RCC->CFGR |= Copy_structConfigurations->SYS_CLK;
		/* Enable the HSI */
		SET_BIT(RCC->CR, HSI_ON);
		/* Pooling the HSI_READY flag until the Clock is stable */
		/* Time out will return Error LOC_enumState and Break the While loop */
		while( ( GET_BIT( RCC->CR, HSI_READY ) ) == 0 )
		{
			LOC_u32TimeOut++;
			if( LOC_u32TimeOut >= 100000 )
			{
				LOC_enumState = NOK;
				/*TimeOut*/
				break;
			}
		}
	}
	else if( Copy_structConfigurations->SYS_CLK == RCC_HSE_BYBASS_SRC )
	{
		/* The HSEBYP Can Be Written Only When the HSE Oscilator Is Disabled */
		/* HSE Clock Disabled */
		CLR_BIT(RCC->CR, HSE_ON);
		/* Enable the HSE BYP */
		SET_BIT(RCC->CR,HSE_BYP);
		/* Select the HSE as the Source of the clock */
		RCC->CFGR &=~( (0b11) << 0 );
		RCC->CFGR |= (Copy_structConfigurations->SYS_CLK >>1 );
		/* Enable the HSE */
		SET_BIT(RCC->CR, HSE_ON);
		/* Pooling the HSE_READY flag until the Clock is stable */
		/* Time out will return Error LOC_enumState and Break the While loop */
		while( ( GET_BIT( RCC->CR, HSE_READY ) ) == 0 )
		{
			LOC_u32TimeOut++;
			if( LOC_u32TimeOut >= 100000 )
			{
				LOC_enumState = NOK;
				/*TimeOut*/
				break;
			}
		}
	}
	else
	{
		LOC_enumState = NOK;
		/* Error */
	}
	RCC->CFGR |= Copy_structConfigurations->OUT_CLK  | Copy_structConfigurations->AHB_SCLR | Copy_structConfigurations->APB1_SCLR | Copy_structConfigurations->APB2_SCLR;
	return LOC_enumState;
}
void RCC_voidEnable_PeripheralCLOCK( RCC_BUS Copy_enumBus, PERIPHERALS Copy_enumPeripheral )
{
	switch( Copy_enumBus ){
	case AHB_BUS  : SET_BIT(RCC->AHBENR  , Copy_enumPeripheral); break;
	case APB1_BUS : SET_BIT(RCC->APB1ENR , Copy_enumPeripheral); break;
	case APB2_BUS : SET_BIT(RCC->APB2ENR , Copy_enumPeripheral); break;
	default : /* Return Error */ break;
	}
}

void RCC_voidDisable_PeripheralCLOCK( RCC_BUS Copy_enumBus, PERIPHERALS Copy_enumPeripheral )
{
	switch( Copy_enumBus ){
	case AHB_BUS  : CLR_BIT(RCC->AHBENR  , Copy_enumPeripheral); break;
	case APB1_BUS : CLR_BIT(RCC->APB1ENR , Copy_enumPeripheral); break;
	case APB2_BUS : CLR_BIT(RCC->APB2ENR , Copy_enumPeripheral); break;
	default : /* Return Error */ break;
	}
}
