/*************************************************************************************/
/** author 		: Ibrahim Saber 													 */
/** Date   		: 12/5/2021															 */
/** Version 	: V00																 */
/** SWC			: GPIO											 					 */
/*************************************************************************************/

#ifndef GPIO_INTERFACE_H_
#define GPIO_INTERFACE_H_

typedef enum 
{
	LOW ,
	HIGH
}PIN_Value;
typedef enum
{
	PORTA,
	PORTB,
	PORTC,
	PORTD
}PORT_NUMBER;

typedef enum 
{
	PIN0,
	PIN1,
	PIN2,
	PIN3,
	PIN4,
	PIN5, 
	PIN6,
	PIN7,
	PIN8,
	PIN9,
	PIN10,
	PIN11,
	PIN12,
	PIN13,
	PIN14,
	PIN15
	
}PIN_NUMBER;

typedef enum
{
	INPUT_PULL_UP 		= 0b1000	,
	INPUT_PULL_DOWN		= 0b10001	,
	INPUT_FLOATING		= 0b0100	,
	INPUT_ANALOG		= 0b0000	,                    
	OUTPUT_OPEN_DRAIN_10_MHz    = 0b0101 ,
	OUTPUT_OPEN_DRAIN_2_MHz	    = 0b0110 ,
	OUTPUT_OPEN_DRAIN_50_MHz    = 0b0111 ,
	OUTPUT_PUSH_PULL_10_MHz	    = 0b0001 ,
	OUTPUT_PUSH_PULL_2_MHz	    = 0b0010 ,
	OUTPUT_PUSH_PULL_50_MHz     = 0b0011 ,
	ALTERANTE_PUSH_PULL_10_MHz  = 0b1001 ,
	ALTERANTE_PUSH_PULL_2_MHz   = 0b1010 ,
	ALTERANTE_PUSH_PULL_50_MHz  = 0b1011 ,
	ALTERANTE_OPEN_DRAIN_10_MHZ = 0b1101 ,
	ALTERANTE_OPEN_DRAIN_2_MHZ  = 0b1110 ,	
	ALTERANTE_OPEN_DRAIN_50_MHZ = 0b1111
	
}PIN_MODE;
typedef struct
{
	PORT_NUMBER port;
	PIN_NUMBER pin	;
	PIN_MODE mode;
}GPIO_PIN_CONFIGS;
/************************************************************************************************************/
/** @name 		: GPIO_u8SetPinDirection																	*/
/** @param[in] 	: GPIO_PIN_CONFIGS Copy_structPinConfigurations "Buffer Contains the Pin Configurations"	*/
/** @param[out] : u8 " Error status" (STATE_OK  or STATE_NOK)												*/
/** @description : 	* Each pin needs 4 bits to choose the mode and each register 32 bit so 32/4 = 8 pins
					* Reset the four bit of the given pin to choose its mode
					* writing the mode of the pin															*/
/** @note available PINs are from PIN0 ..PIN15																*/
/***********************************************************************************************************/

u8 GPIO_u8SetPinDirection(GPIO_PIN_CONFIGS * Copy_structPinConfigurations);

/*****************************************************************************************************************************************************/
/** @name 		: GPIO_u8SetPinValue
/** @param[in] 	: GPIO_PIN_CONFIGS Copy_structPinConfigurations "Buffer Contains the Pin Configurations"
/** @param[in]  : PIN_Value Copy_enumPinValue
/** @param[out] : u8 " Error status" (STATE_OK  or STATE_NOK)
/** @description : 	*GPIO_BSRR =(1<<Copyu8pin) faster than SET_BIT(GPIOx_ODR,Copyu8pin) 
						to set any bit i can write 1 on the bit number in the register GPIOx_BSRR 
						the register is 32 bit the first 16 bit are used if i want to set the bit the other 16 bit are used to reset the bit(clear)
						in this register only writing one affects 0 has no effect 
						(the set has more precedence than resetting )	
						
					*GPIO_BRR =(1<<Copyu8pin) faster than CLR_BIT(GPIOx_ODR,Copyu8pin) 
						to reset any bit i can wGPIO_BRR =(1<<Copyu8pin)rite 1 on the bit number in the register GPIOx_BRR 
						the register is 32 bit the first 16 bit are used if i want to reset the bit the other 16 bit are reserved 
						in this register only writing one affects 0 has no effect 
/** @note available PINs are from PIN0 ..PIN15
/*****************************************************************************************************************************************************/

u8 GPIO_u8SetPinValue(GPIO_PIN_CONFIGS * Copy_structPinConfigurations, PIN_Value Copy_enumPinValue);

/*****************************************************************************************************************************************************/
/** @name 		: GPIO_u8ReadPinValue
/** @param[in] 	: GPIO_PIN_CONFIGS Copy_structPinConfigurations "Buffer Contains the Pin Configurations"
/** @param[in]  : u8 pointer Copy_enumPinValue " Carries the returned pin value "
/** @param[out] : u8 " Error status" (STATE_OK  or STATE_NOK)
/** @description : 	*the GPIOx_IDR is 32 bit first 16 bit each bit represents a pin of the port (each port 16 PIN 0 to 15)		
/** @note available PINs are from PIN0 ..PIN15
/*****************************************************************************************************************************************************/
u8 GPIO_u8ReadPinValue  (GPIO_PIN_CONFIGS * Copy_structPinConfigurations, u8 * Copy_ptrPinValue);

/*****************************************************************************************************************************************************/
/** @name 		: GPIO_uTogglePinValue
/** @param[in] 	: GPIO_PIN_CONFIGS Copy_structPinConfigurations "Buffer Contains the Pin Configurations"
/** @param[out] : u8 " Error status" (STATE_OK  or STATE_NOK)
/** @description : toggling a given pin from 0 to one and from 1 to zero according to its value on the ODR register		
/** @note available PINs are from PIN0 ..PIN15
/*****************************************************************************************************************************************************/
u8 GPIO_uTogglePinValue (GPIO_PIN_CONFIGS * Copy_structPinConfigurations );
u8 GPIO_u8SetPortDirection(GPIO_PIN_CONFIGS * Copy_structPinConfigurations);
u8 GPIO_u8SetPortValue(GPIO_PIN_CONFIGS * Copy_structPinConfigurations, u16 Copy_u16PinValue);
u8 GPIO_u8ReaPortnValue(GPIO_PIN_CONFIGS * Copy_structPinConfigurations, u16 *Copy_u16PinValue);




#endif
