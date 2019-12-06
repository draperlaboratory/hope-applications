#include <stdio.h>

int main() {
  int foo = 0x8067;
  void (*foo_fn_ptr)() = NULL;

  foo_fn_ptr = (void (*)()) &foo;
  foo_fn_ptr();

  return 0;
}
