#include <unistd.h>
#include <stdint.h>
#include <sys/types.h>
#include "weak_under_alias.h"
#include "uart.h"

ssize_t __wrap_write(int fd, const void* ptr, size_t len)
{
    const uint8_t* current = (const uint8_t*)ptr;

    if (isatty(fd)) {
        for (size_t jj = 0; jj < len; jj++) {
            tx(uart0, current[jj]);
            if (current[jj] == '\n') {
                tx(uart0, '\r');
            }
        }
        return len;
    }

    return -1;
}
weak_under_alias(write);
