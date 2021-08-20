/************************************************************************************/
/*** Author 	: Ibrahim Saber Mohamed Ahmed 									*****/
/*** Version  	: V01 															*****/		
/*** SOC		: NVIC															*****/
/************************************************************************************/

#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "STM32F103C8.h"

#include "NVIC_interface.h"
#include "NVIC_private.h"
#include "NVIC_config.h"

u8 NVIC_u8EnableInterrupt ( INTERRUPT_NUMBER Copy_enumIRQN )
{
	u8 State = STATE_OK;
	u8 LOC_u8REG_Index = Copy_enumIRQN / 32 ;
	u8 LOC_u8BIT_Value = Copy_enumIRQN % 32 ;
	if ( Copy_enumIRQN >59 )
	{
		State = STATE_NOK;
	}
	else
	{
		/* Enable the Interrupt from the NVIC Side  */
		/* Writing 0 has No effect */
		/* Writing One To the corresponding Bit in the ISER-Register */

		NVIC->ISER[LOC_u8REG_Index] = ( 1 << LOC_u8BIT_Value );
	}
	return State;
}
u8 NVIC_u8DisableInterrupt( INTERRUPT_NUMBER Copy_enumIRQN )
{
	u8 State = STATE_OK;
	u8 LOC_u8REG_Index = Copy_enumIRQN / 32 ;
	u8 LOC_u8BIT_Value = Copy_enumIRQN % 32 ;
	if ( Copy_enumIRQN >59 )
	{
		State = STATE_NOK;
	}
	else
	{
		/* Disable the Interrupt from the NVIC Side  */
		/*Writing 0 has No effect */
		/* Writing One To the corresponding Bit in the ICER-Register */

		NVIC->ICER[LOC_u8REG_Index] = ( 1 << LOC_u8BIT_Value );
	}
	return State;
}
u8 NVIC_u8SetPendingFlag  ( INTERRUPT_NUMBER Copy_enumIRQN )
{
	u8 State = STATE_OK;
	u8 LOC_u8REG_Index = Copy_enumIRQN / 32 ;
	u8 LOC_u8BIT_Value = Copy_enumIRQN % 32 ;
	if ( Copy_enumIRQN >59 )
	{
		State = STATE_NOK;
	}
	else
	{
		/* Enable the Pending Flag */
		/* if the flag is pending writing 1 has No effect */ 
		/* Writing One To the corresponding Bit in the ISPR-Register */

		NVIC->ISPR[LOC_u8REG_Index] = ( 1 << LOC_u8BIT_Value );
	}
	return State;

}
u8 NVIC_u8ClearPendingFlag( INTERRUPT_NUMBER Copy_enumIRQN )
{
	u8 State = STATE_OK;
	u8 LOC_u8REG_Index = Copy_enumIRQN / 32 ;
	u8 LOC_u8BIT_Value = Copy_enumIRQN % 32 ;
	if ( Copy_enumIRQN >59 )
	{
		State = STATE_NOK;
	}
	else
	{
		/* Disable the Pending Flag */
		/* Removes the pending state of an interrupt */ 
		/* Writing One To the corresponding Bit in the ISPR-Register */
		/* Writing One To the corresponding Bit in the ISPR-Register does not affect the Active State of that Interrupt*/

		NVIC->ICPR[LOC_u8REG_Index] = ( 1 << LOC_u8BIT_Value );
	}
	return State;
}
u8 NVIC_u8GetActiveFlag   ( INTERRUPT_NUMBER Copy_enumIRQN , u8*Copy_ptrReturnValue )
{
	u8 State = STATE_OK;
	u8 LOC_u8REG_Index = Copy_enumIRQN / 32 ;
	u8 LOC_u8BIT_Value = Copy_enumIRQN % 32 ;
	if ( ( Copy_enumIRQN < 60 ) && ( Copy_ptrReturnValue != NULL ) )
	{
		/* Reading the Active Flag State from IABRx- Register */
		/* Reading " 1 " -> Active & Reading " 0 " -> Not Active  */

		*Copy_ptrReturnValue = ( ( NVIC->IABR[ LOC_u8REG_Index ] >>  LOC_u8BIT_Value ) & 1 );
	}
	else
	{
		State = STATE_NOK;
	}
	return State;
}

u8 NVIC_u8SetPriorty(INTERRUPT_NUMBER Copy_enumIRQN, u8 Copy_u8GroupPriorty, u8 Copy_u8SubPriorty)
{
	u8 State = STATE_OK;
	if (  Copy_enumIRQN < 60  )
	{
		NVIC->IPR[Copy_enumIRQN] = ( ( ( Copy_u8GroupPriorty << 2 ) | Copy_u8SubPriorty ) << 4 ) ;
	}
	else
	{
		State = STATE_NOK;
	}
	return State;
}


u8 NVIC_u8ConfigurePriority(void)
{
	u8 Local_u8ErrorState = STATE_OK;
	/* 2 Bits for Group Priority, 2 Bits for Sub Priority */
	SCB_u32_AIRCR_REG = 0x05FA0500;
	return Local_u8ErrorState;
}
