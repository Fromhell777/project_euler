#include "timer.hpp"

#include <cstddef>
#include <cstdint>
#include <iostream>

// only tested for relativly prime numbers
long find_smaller_ordered_fraction(long denominator_limit,
                                   long numerator, long denominator) {
  long result = denominator_limit * numerator;
  while ((result % denominator) != 1) {
    result -= numerator;
  }

  result = (result - 1) / 7;

  return result;
}

int main () {

  const long numerator = 3;
  const long denominator = 7;
  const long denominator_limit = 1'000'000;
  long result;

  {
    timer Timer;

    result = find_smaller_ordered_fraction(denominator_limit,
                                           numerator, denominator);
  }

  std::cout << "Result: " << result << "\n";
}

// 'Diophantine Approximations' the theorem of Hurwitz
// If a / b is the neighbor to the left of 3 / 7 in the Farey sequence (and
// Stern-Brocot tree), then 3 / 7 − a / b = 1 / (7 * b), or 3 * b − 7 * a = 1.
// This diophantine equation has solutions (a, b) = (2, 5) + k * (3, 7) for
// k >= 0. The largest with b <= 10 ^ 6 is (428570, 999997), attained with
// k = 142856. (a and b are automatically relatively prime because they satisfy
// the diophantine equation.)
