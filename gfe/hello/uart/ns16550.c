/* CJC: Adapted from Dover's uart stuff to remove C++ */
#include "ns16550.h"
#include "softmath.h"

void init_ns16550(ns16550_pio_t* uart) {
  int baudrate = NS16550_DEFAULT_BAUD_RATE;
  int clock_rate = NS16550_CLOCK_RATE;

  uint32_t divisor;
  uart->ier = (enum ier_t)0;

  divisor = softdiv(clock_rate, (16 * baudrate));
  uart->lcr = (enum lcr_t)(uart->lcr | LCR_DLAB);
  uart->dll = divisor & 0xff;
  uart->dlm = (divisor >> 8) & 0xff;
  uart->lcr = (enum lcr_t)(uart->lcr & ~LCR_DLAB);

  uart->lcr = LCR_WLS8;
  uart->fcr = FCR_FE;
  uart->mcr = MCR_RTS;
}

bool rx_ready(ns16550_pio_t* uart) {
  return (uart->lsr & LSR_DR) != 0;
}

void tx(ns16550_pio_t* uart, uint8_t byte) {
  while ((uart->lsr & LSR_THRE) == 0)
    ;  // nothing

  uart->thr = byte;
}

uint8_t rx(ns16550_pio_t* uart) {
  while ((uart->lsr & LSR_DR) == 0)
    ;  // nothing

  return uart->rbr;
}

