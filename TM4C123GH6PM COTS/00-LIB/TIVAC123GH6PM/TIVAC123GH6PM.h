/*
 * TIVAC123GH6PM.h
 *
 *  Created on: Aug 15, 2021
 *      Author: ibrahim
 */

#ifndef LIB_TIVAC123GH6PM_TIVAC123GH6PM_H_
#define LIB_TIVAC123GH6PM_TIVAC123GH6PM_H_

/**********************************************************************/
/*************      UART REGISTERS  *************/
/**********************************************************************/
#define UART0_BASE_ADDRESS          0x4000C000
#define UART1_BASE_ADDRESS          0x4000D000
#define UART2_BASE_ADDRESS          0x4000E000
#define UART3_BASE_ADDRESS          0x4000F000
#define UART4_BASE_ADDRESS          0x40010000
#define UART5_BASE_ADDRESS          0x40011000
#define UART6_BASE_ADDRESS          0x40012000
#define UART7_BASE_ADDRESS          0x40013000


typedef struct {

    volatile u32    DR              ;
    volatile u32    RSR_ECR         ;
    volatile u32    FR              ;
    volatile u32    ILPR            ;
    volatile u32    IBRD            ;
    volatile u32    FBRD            ;
    volatile u32    LCRH            ;
    volatile u32    CTL             ;
    volatile u32    IFLS            ;
    volatile u32    IM              ;
    volatile u32    RIS             ;
    volatile u32    MIS             ;
    volatile u32    ICR             ;
    volatile u32    DMACTL          ;
    volatile u32    BIT_9_ADDR      ;
    volatile u32    BIT_9_AMASK     ;
    volatile u32    PP              ;
    volatile u32    CC              ;
    volatile u32    PeriphID_4_7[4] ;
    volatile u32    PeriphID_0_3[4] ;
    volatile u32    PCellID_0_3[4]  ;

}UART_REGISTER_t;

#define UART0                  ( ( UART_REGISTER_t *  ) UART0_BASE_ADDRESS)
#define UART1                  ( ( UART_REGISTER_t *  ) UART1_BASE_ADDRESS)
#define UART2                  ( ( UART_REGISTER_t *  ) UART2_BASE_ADDRESS)
#define UART3                  ( ( UART_REGISTER_t *  ) UART3_BASE_ADDRESS)
#define UART4                  ( ( UART_REGISTER_t *  ) UART4_BASE_ADDRESS)
#define UART5                  ( ( UART_REGISTER_t *  ) UART5_BASE_ADDRESS)
#define UART6                  ( ( UART_REGISTER_t *  ) UART6_BASE_ADDRESS)
#define UART7                  ( ( UART_REGISTER_t *  ) UART7_BASE_ADDRESS)

/**********************************************************************/

#endif /* LIB_TIVAC123GH6PM_TIVAC123GH6PM_H_ */
