/*************************************************************************************/
/** author 		: Ibrahim Saber 													 */
/** Date   		: 12/5/2021															 */
/** Version 	: V00																 */
/** SWC			: GPIO											 					 */
/*************************************************************************************/

#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "STM32F103C8.h"

#include "GPIO_interface.h"
#include "GPIO_private.h"
#include "GPIO_config.h"

/* array of pointers to structure */
static GPIO_REGISTERS * GPIOx[4] = { GPIOA, GPIOB, GPIOC , GPIOD};
u8 GPIO_u8SetPinDirection(GPIO_PIN_CONFIGS * Copy_structPinConfigurations)
{
	u8 LOC_u8State = STATE_OK;
	u8 LOC_u8mode  = Copy_structPinConfigurations->mode;
	if( LOC_u8mode == INPUT_PULL_UP )
	{
		/* GPIOx is an array holds pointers to structures */
		/* the port id represents the index of the corresponding pointer in the GPIOx */
		GPIOx[Copy_structPinConfigurations->port]->ODR  |= ( 1 << Copy_structPinConfigurations->pin );
	}
	else if ( LOC_u8mode == INPUT_PULL_DOWN )
	{
		GPIOx[Copy_structPinConfigurations->port]->ODR  &= ~( 1 << Copy_structPinConfigurations->pin );
		LOC_u8mode >>= 1 ;
	}
	else
	{

	}
	if ( Copy_structPinConfigurations->pin <PIN8 )
	{
		GPIOx[Copy_structPinConfigurations->port]->CRL &= ~ ( ( 0b1111 ) << (Copy_structPinConfigurations->pin * 4 ) )  ;
		GPIOx[Copy_structPinConfigurations->port]->CRL |=  ( LOC_u8mode  << ( Copy_structPinConfigurations->pin* 4 ) ) ;
	}
	else if(Copy_structPinConfigurations->pin <=PIN15 )
	{
		GPIOx[Copy_structPinConfigurations->port]->CRH &= ~ ( ( 0b1111 ) << ( ( Copy_structPinConfigurations->pin - 8 ) * 4 ) );
		GPIOx[Copy_structPinConfigurations->port]->CRH |=  ( LOC_u8mode  << ( Copy_structPinConfigurations->pin - 8 ) * 4 ) ;
	}
	else {
		LOC_u8State = STATE_NOK;
	}

	return LOC_u8State;
}
u8 GPIO_u8SetPinValue(GPIO_PIN_CONFIGS * Copy_structPinConfigurations, PIN_Value Copy_enumPinValue)
{
	u8 LOC_u8State = STATE_OK;
	if ( Copy_enumPinValue == HIGH ) 
	{
		if ( Copy_structPinConfigurations->pin <=PIN15 )
		{
			GPIOx[Copy_structPinConfigurations->port]->BSRR = ( 1 <<  Copy_structPinConfigurations->pin ) ;
		}
		else
		{
			LOC_u8State = STATE_NOK;
		}
	}

	else if ( Copy_enumPinValue == LOW )
	{
		if ( Copy_structPinConfigurations->pin <=PIN15 )
		{
			GPIOx[Copy_structPinConfigurations->port]->BRR = ( 1 <<  Copy_structPinConfigurations->pin ) ;
		}
		else
		{
			LOC_u8State = STATE_NOK;
		}
	}
	else
	{
		LOC_u8State = STATE_NOK;
	}
	return LOC_u8State;
}
u8 GPIO_u8ReadPinValue(GPIO_PIN_CONFIGS * Copy_structPinConfigurations, u8 * Copy_ptrPinValue)
{
	u8 LOC_u8State = STATE_OK;
	if( Copy_structPinConfigurations->pin <= PIN15 )
	{
		*Copy_ptrPinValue  = GET_BIT(GPIOx[Copy_structPinConfigurations->port]->IDR, Copy_structPinConfigurations->pin );
	}
	else
	{
		LOC_u8State = STATE_NOK ;
	}
	return LOC_u8State;
}

u8 GPIO_uTogglePinValue  (GPIO_PIN_CONFIGS * Copy_structPinConfigurations )
{
	u8 LOC_u8State = STATE_OK ;
	if( Copy_structPinConfigurations->pin <= PIN15 )
	{
		TOGG_BIT(GPIOx[Copy_structPinConfigurations->port]->ODR, Copy_structPinConfigurations->pin );
	}
	else
	{
		LOC_u8State = STATE_NOK ;
	}
	return LOC_u8State;
}

u8 GPIO_u8SetPortDirection(GPIO_PIN_CONFIGS * Copy_structPinConfigurations);
u8 GPIO_u8SetPortValue(GPIO_PIN_CONFIGS * Copy_structPinConfigurations, u16 Copy_u16PinValue);
u8 GPIO_u8ReaPortnValue(GPIO_PIN_CONFIGS * Copy_structPinConfigurations, u16 *Copy_u16PinValue);

