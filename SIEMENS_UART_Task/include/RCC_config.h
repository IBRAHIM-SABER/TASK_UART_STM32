/*************************************************************************************/
/** author 		: Ibrahim Saber 													 */
/** Date   		: 6/5/2021															 */
/** Version 	: V00																 */
/*************************************************************************************/

#ifndef RCC_CONFIG_H_
#define RCC_CONFIG_H_

	/*
	 * 1- HSE_CLK
	 * 2- HSE_BYPASS_CLK
	 * 3- HSI_CLK
	 * 4- PLL_CLK			  */
#define SYS_CLOCK		HSI_CLK
#if SYS_CLOCK == PLL_CLK
		/*
		 * 1- PLL_HSI_DEV_2
		 * 2- PLL_HSE_DEV_2
		 * 3- PLL_HSE
		 * */
	#define PLL_CLK_SOURC	PLL_HSI_DEV_2
		/*
		 * Write a number from 2 -> 16 */
	#define PLL_MULTIPLY_FACTOR 	2
#endif
#endif
