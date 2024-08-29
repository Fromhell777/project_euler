#include "timer.hpp"

#include <cstddef>
#include <cstdint>
#include <iostream>
#include <math.h>
#include <cstring>

// return an array with amount of that values occurence
void find_prime_factors(int value, int* prime_factors) {
  int divisor = 5;
  int largestPrimeFactor;

  if(value % 2 == 0) {
    largestPrimeFactor = 2;
    while(value % 2 == 0) {
      ++prime_factors[largestPrimeFactor];
      value = value / 2;
    }
  }
  if(value % 3 == 0) {
    largestPrimeFactor = 3;
    while(value % 3 == 0) {
      ++prime_factors[largestPrimeFactor];
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
            ++prime_factors[largestPrimeFactor];
            value = value / largestPrimeFactor;
            max_value = sqrt(value);
          }
      }

      divisor += 2;

      if(value % divisor == 0)
      {
          largestPrimeFactor = divisor;
          while(value % largestPrimeFactor == 0) {
            ++prime_factors[largestPrimeFactor];
            value = value / largestPrimeFactor;
            max_value = sqrt(value);
          }
      }
      divisor += 4;
  }
  ++prime_factors[value];
}


long find_multiple(size_t size, int* divisor_prime_factors, int* prime_factors) {
  for (size_t i = 2; i < size; ++i) {
    find_prime_factors(i, divisor_prime_factors);
    for (size_t j = 2; j < size; ++j) {
      if (divisor_prime_factors[j] > prime_factors[j]) {
        prime_factors[j] = divisor_prime_factors[j];
      }
    }
    memset(divisor_prime_factors, 0, size * sizeof(int));
  }
  long mult_factors = 1;
  for (size_t i = 2; i < size; ++i) {
    mult_factors *= pow(i, prime_factors[i]);
  }
  return mult_factors;
}

int main () {

  const int max = 20;
  int prime_factors[max + 1] = {};
  int divisor_prime_factors[max + 1] = {};
  long result;

  {
    timer Timer;

    result = find_multiple(max + 1, divisor_prime_factors, prime_factors);
  }

  std::cout << "Result: " << result << "\n";
}
