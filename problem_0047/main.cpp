#include "timer.hpp"

#include <cstddef>
#include <cstdint>
#include <iostream>
#include <cmath>

long total_distinct_prime_factors(long value) {
  long distinct_factors = 0;
  long divisor = 5;

  if(value % 2 == 0) {
    ++distinct_factors;
    while(value % 2 == 0) {
      value = value / 2;
    }
  }
  if(value % 3 == 0) {
    ++distinct_factors;
    while(value % 3 == 0) {
      value = value / 3;
    }
  }

  double max_value = sqrt(value);
  while(divisor < max_value ) {
    if(value % divisor == 0) {
      ++distinct_factors;
      while(value % divisor == 0) {
        value = value / divisor;
        max_value = sqrt(value);
        }
    }

    divisor += 2;

    if(value % divisor == 0) {
      ++distinct_factors;
      while(value % divisor == 0) {
        value = value / divisor;
        max_value = sqrt(value);
      }
    }

    divisor += 4;
  }

  if (value != 1) {
    ++distinct_factors;
  }

  return distinct_factors;
}

long find_consecutive_distinct_primes_factors(const int serie_length) {
  int occurrences = 0;
  long i;
  for (i = 2; occurrences != serie_length; ++i) {
    if (total_distinct_prime_factors(i) == serie_length) {
      ++occurrences;
    } else {
      occurrences = 0;
    }
  }

  return i - serie_length;
}

int main () {

  const int serie_length = 4;
  long result;

  {
    timer Timer;

    result = find_consecutive_distinct_primes_factors(serie_length);
  }

  std::cout << "Result: " << result << "\n";
}
