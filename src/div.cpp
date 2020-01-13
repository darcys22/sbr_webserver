#include "div.h"
double division(int dividend, int divisor){
  if (divisor == 0){
    return -1;
  }

  return (double)dividend / divisor;
}
