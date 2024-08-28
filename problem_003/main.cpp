#include "timer.hpp"

#include <cstddef>
#include <cstdint>
#include <iostream>
#include <math.h>

long check_prime(long value) {
  long divisor = 5;
  long largestPrimeFactor;

  if(value % 2 == 0) {
    largestPrimeFactor = 2;
    while(value % 2 == 0) {
      value = value / 2;
    }
  }
  if(value % 3 == 0) {
    largestPrimeFactor = 3;
    while(value % 3 == 0) {
      value = value / 3;
    }
  }

  double max_value = sqrt(value);
  while(divisor < max_value )
  {
      if(value % divisor == 0)
      {
          largestPrimeFactor = divisor;
          while(value % largestPrimeFactor == 0) {
            value = value / largestPrimeFactor;
            max_value = sqrt(value);
          }
      }

      divisor += 2;

      if(value % divisor == 0)
      {
          largestPrimeFactor = divisor;
          while(value % largestPrimeFactor == 0) {
            value = value / largestPrimeFactor;
            max_value = sqrt(value);
          }
      }
      divisor += 4;
  }
  return value;
}

int main () {

  long max = 600'851'475'143;
  long result;

  {
    timer Timer;

    result = check_prime(max);
  }

  std::cout << "Result: " << result << "\n";
}
