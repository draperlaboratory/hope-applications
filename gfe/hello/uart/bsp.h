/*****************************************************************************/
/**
*
* @file bsp.h
* @addtogroup bsp
* @{
*
* Test
* ## This is markdown example
*
* **More** markdown
*
* @note
*
* Lorem impsum
*
*
******************************************************************************/
#ifndef RISCV_P1_BSP_H
#define RISCV_P1_BSP_H

/**
 * UART defines
 */
#define XPAR_UART_USE_POLLING_MODE 1
#define XPAR_XUARTNS550_NUM_INSTANCES 2
#define XPAR_DEFAULT_BAUD_RATE 115200

#define BSP_USE_UART0 1
#define XPAR_UARTNS550_0_DEVICE_ID 0
#define XPAR_UARTNS550_0_BAUD_RATE XPAR_DEFAULT_BAUD_RATE
#define XPAR_UARTNS550_0_BASEADDR 0x62300000ULL
#define XPAR_UARTNS550_0_CLOCK_HZ 50000000

// UART1 is in use by the PEX, so avoid re-initializing it on the AP
#define BSP_USE_UART1 0
#define XPAR_UARTNS550_1_DEVICE_ID 1
#define XPAR_UARTNS550_1_BAUD_RATE XPAR_DEFAULT_BAUD_RATE
#define XPAR_UARTNS550_1_BASEADDR (0x62340000ULL)
#define XPAR_UARTNS550_1_CLOCK_HZ 50000000

#endif /* RISCV_P1_BSP_H */
