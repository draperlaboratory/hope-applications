#include <stdio.h>
#include "uart.h"

int main() {
  uart0_init();
  for(;;) {
    puts("Hello GFE!\n");
  }
  return 0;
}
