#include "timer.hpp"

#include <cstddef>
#include <cstdint>
#include <iostream>
#include <math.h>

// return an array with amount of that values occurence
long find_prime_factors(int value) {
  int divisor = 5;
  int largestPrimeFactor;
  long total_divisors = 1;
  long temp_total_divisors = total_divisors;

  if(value % 2 == 0) {
    largestPrimeFactor = 2;
    while(value % 2 == 0) {
      total_divisors += temp_total_divisors;
      value = value / 2;
    }
  }

  temp_total_divisors = total_divisors;

  if(value % 3 == 0) {
    largestPrimeFactor = 3;
    while(value % 3 == 0) {
      total_divisors += temp_total_divisors;
      value = value / 3;
    }
  }

  temp_total_divisors = total_divisors;

  while(divisor <= value )
  {
      if(value % divisor == 0)
      {
          largestPrimeFactor = divisor;
          while(value % largestPrimeFactor == 0) {
            total_divisors += temp_total_divisors;
            value = value / largestPrimeFactor;
          }
      }

      divisor += 2;
      temp_total_divisors = total_divisors;

      if(value % divisor == 0)
      {
          largestPrimeFactor = divisor;
          while(value % largestPrimeFactor == 0) {
            total_divisors += temp_total_divisors;
            value = value / largestPrimeFactor;
          }
      }
      divisor += 4;
      temp_total_divisors = total_divisors;
  }
  return total_divisors;
}

long find_divisible_triangular_number(int value) {
  long number = sqrt(2 * (pow(2, 4) * pow(3, 4) * pow(5, 4) * 7 * 13)) - 1;
  long result = 0;
  bool done = false;

  while (!done) {
    result = find_prime_factors((number * (number + 1)) / 2);
    if (result > value) {
      done = true;
    } else {
      ++number;
    }
  }

  return (number * (number + 1)) / 2;
}

int main () {

  long result;

  {
    timer Timer;

    result = find_divisible_triangular_number(500);
  }

  std::cout << "Result: " << result << "\n";
}
