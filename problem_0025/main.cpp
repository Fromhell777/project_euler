#include "timer.hpp"

#include <cstddef>
#include <cstdint>
#include <iostream>
#include <cmath>
// #include <gmpxx.h>

int main () {

  const long digit_count = 1000;
  // mpz_class fib1 = 1;
  // mpz_class fib2 = 1;
  // mpz_class fib_temp;
  long result = 2;

  {
    timer Timer;

    // while (fib2.get_str().size() != digit_count) {
    //   ++result;
    //   fib_temp = fib2;
    //   fib2 += fib1;
    //   fib1 = fib_temp;
    // }

    result = std::ceil((digit_count - 1) / (std::log10(1 + std::sqrt(5)) -
                                            std::log10(2)) + 1);
  }

  std::cout << "Result: " << result << "\n";
}

// Fibonacci terms converge to (n)*Phi=(n+1),
// where Phi is the Golden Ratio (1+sqrt5)/2.
//
// Saying that a number contains 1000 digits is the same as saying that
// it's greater than 10**999.
// The nth Fibonacci number is [phi**n / sqrt(5)],
// where the brackets denote "nearest integer".
// So we need phi**n/sqrt(5) > 10**999
// n * log(phi) - log(5)/2 > 999 * log(10)
// n * log(phi) > 999 * log(10) + log(5)/2
// n > (999 * log(10) + log(5) / 2) / log(phi)
