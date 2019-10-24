int main() {
  volatile int foo = 42;
  volatile int *foo_ptr;

  foo_ptr = (int *)main;
  *foo_ptr = foo;
  
  return 0;
}
