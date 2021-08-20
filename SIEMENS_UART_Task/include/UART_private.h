/*
 * UART_private.h
 *
 *  Created on: Jul 2, 2021
 *      Author: ibrahim
 */

#ifndef UART_PRIVATE_H_
#define UART_PRIVATE_H_

/* Status register bits USART_SR */
#define CTC			9			// bit detect clear to send flag
#define LBD			8    		// Detect lin break
#define TXE			7			// Transmit data register empty
#define TC			6			// Transmission complete
#define RXNE		5			// Read data register is not empty
#define IDLE		4 			// IDLE line detect
#define ORE			3			// Data Over Run
#define NE			2     		// Noise Error Flag
#define FE			1			// Frame Error flag
#define PE			0			// Parity error flag

/*control register USART_CR1 */

#define  UE			13      	// USART Enable
#define  M			12 			// Word length
#define  WAKE		11			// Wakeup method
#define  PCE		10			// Parity control Enable
#define  PS			9			// parity selection (0 Even , 1 Odd)
#define  PEIE		8			// parity interrupt enable
#define  TXEIE		7			// Transmit data register empty interrupt Enable
#define  TCIE		6			// Transmission complete interrupt enable
#define  RXNEIE		5			// Read data register is not empty interrupt enable
#define  IDLEIE 	4			// IDLE line detect interrupt enable
#define  TE			3			// Transmitter enable
#define  RE			2			// receiver enable

/* Receiver wakeup This bit determines if the USART is in mute mode or not. It is set and cleared by software and
   can be cleared by hardware when a wakeup sequence is recognized.*/
#define  RWU    	1	   	    //Receiver wakeup
#define  SBK		0			// Send break

#define CPOL		10			// clock polarity
#define CPHA		9			// clock phase



#endif /* UART_PRIVATE_H_ */
