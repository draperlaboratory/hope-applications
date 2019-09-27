#include "uart.h"

uart_t* uart0 = (uart_t*)(SOC_ADDR_UART0);

void init_uart() {
  init_ns16550(uart0);
}

/**
   Reads a 32bit word from the uart.  This method will block if no input is pending.
 */
uint32_t read_uint32() {
  int i;
  uint32_t res = 0;
  for (i = 0; i < 4; i++) {
    while (!rx_ready(uart0));
    uint8_t b = (uint8_t)rx(uart0);
    res |= b << (i * 8);
  }
  return res;
}
