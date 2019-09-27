#include <unistd.h>
#include <stdint.h>
#include <sys/types.h>
#include "uart.h"
#include "weak_under_alias.h"

int __wrap_puts(const char *s)
{
  int len = 0;
  while (*s != '\0') {
    tx(uart0, *s);

    if (*s == '\n') {
      tx(uart0, '\r');
    }

    ++len;
    ++s;
  }

  return len;
}
weak_under_alias(puts);
