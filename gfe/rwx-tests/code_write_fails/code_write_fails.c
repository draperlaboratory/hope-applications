#include <stdio.h>

int main() {
  volatile int foo = 42;
  volatile int *foo_ptr;

  foo_ptr = (int *)main;
  printf("foo = %d\n", foo);
  printf("foo_ptr = %p\n", foo_ptr);

  *foo_ptr = foo;
  
  printf("RWX Test - should not execute this\n");

  return 0;
}
