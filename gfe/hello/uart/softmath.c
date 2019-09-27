#include "softmath.h"

uint32_t softmul(uint32_t multiplier, uint32_t multiplicand)
{
  uint32_t i;
  uint32_t result = 0;

  for(i = 0; i < 32; i++) {
    if(((multiplier << i) & 1) == 1) {
      result += multiplicand;
    }

    multiplicand = multiplicand << 1;
  }

  return result;
}

uint32_t softdiv(uint32_t dividend, uint32_t divisor)
{
  uint32_t result = 0;

  while (dividend > divisor) {
    dividend -= divisor;
    result++;
  }

  return result;
}
