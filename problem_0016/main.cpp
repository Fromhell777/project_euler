#include "timer.hpp"

#include <cstddef>
#include <cstdint>
#include <iostream>
#include <gmpxx.h>

int main () {

  int exponent = 1000;
  int base = 2;
  mpz_class power;
  long sum = 0;
  long result;

  {
    timer Timer;

    mpz_ui_pow_ui(power.get_mpz_t(), base, exponent);

    for (size_t i = 0; i < power.get_str().length(); ++i) {
      sum += power.get_str()[i] - '0';
    }

    result = sum;
  }

  std::cout << "Result: " << result << "\n";
}
