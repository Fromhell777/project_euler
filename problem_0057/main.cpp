#include "timer.hpp"

#include <cstddef>
#include <cstdint>
#include <iostream>
#include <gmpxx.h>
#include <string>

long find_square_root_convergents(long max_iterations) {
  mpz_class numerator = 1;
  mpz_class denominator = 1;
  long larger_denominators = 0;
  for (long i = 0; i < max_iterations; ++i) {
    numerator += 2 * denominator;
    denominator = numerator - denominator;
    if (numerator.get_str().size() > denominator.get_str().size()) {
      ++larger_denominators;
    }
  }

  return larger_denominators;
}

int main () {

  long max_iterations = 1000;
  long result;

  {
    timer Timer;

    result = find_square_root_convergents(max_iterations);
  }

  std::cout << "Result: " << result << "\n";
}
