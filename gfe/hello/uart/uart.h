#ifndef UART_H
#define UART_H

#include "ns16550.h"
#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>

typedef ns16550_pio_t uart_t;

extern uart_t* uart0;

/* The pex uart must be initialized before any other function is called! */
void init_uart();

/**
   Reads a 32bit word from the uart.  This method will block if no input is pending.
 */
uint32_t read_uint32();

#endif
