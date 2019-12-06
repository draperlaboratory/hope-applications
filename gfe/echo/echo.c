#include <stdio.h>

int main() {
  char buffer[0x100];

  for(;;) {
    printf("Enter a message\n");
    read(0, buffer, sizeof(buffer));
    printf("You entered: %s\n", buffer);
  }

  return 0;
}
