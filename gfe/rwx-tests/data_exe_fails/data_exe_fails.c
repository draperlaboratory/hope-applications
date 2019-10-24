#include <stdio.h>

int main() {
  int foo = 0x8067;
  void (*foo_fn_ptr)() = NULL;

  foo_fn_ptr = (void (*)()) &foo;
  printf("&foo = %p\n", &foo);
  printf("foo_fn_ptr = %p\n", foo_fn_ptr);

  foo_fn_ptr();

  printf("RWX Test - should not execute this\n");

  return 0;
}
