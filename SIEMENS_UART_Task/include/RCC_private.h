/*************************************************************************************/
/** author 		: Ibrahim Saber 													 */
/** Date   		: 6/5/2021															 */
/** Version 	: V00																 */
/*************************************************************************************/


#ifndef RCC_PRIVATE_H_
#define RCC_PRIVATE_H_

#define HSE_CLK        		 0b01
#define HSE_BYPASS_CLK       0b011
#define HSI_CLK              0b00
#define PLL_CLK		         0b10

#define PLL_HSI_DEV_2       (0 << 17)|(1<<16)
#define PLL_HSE_DEV_2       (1 << 17)|(1<<16)
#define PLL_HSE             (0 << 16)


#endif
