#include "timer.hpp"

#include <cstddef>
#include <cstdint>
#include <iostream>
#include <gmpxx.h>
#include <numeric>
#include <string>

long find_convergents_of_e(const unsigned long limit) {
  mpz_class numerator_1 = 3;
  mpz_class numerator_2 = 2;
  mpz_class numerator_temp = numerator_1;
  long cycle = 2;
  long fraction_term = 2;
  for (unsigned long i = 2; i < limit; ++i) {
    if (cycle == 0 || cycle == 1) {
      numerator_1 += numerator_2;
      numerator_2 = numerator_temp;
      numerator_temp = numerator_1;
      ++cycle;
    } else {
      numerator_1 = fraction_term * numerator_1 + numerator_2;
      numerator_2 = numerator_temp;
      numerator_temp = numerator_1;
      cycle = 0;
      fraction_term += 2;
    }
  }

  long result = 0;
  for (auto &digit : numerator_1.get_str()) {
    result += digit;
  }
  result -= '0' * numerator_1.get_str().size();
  return result;
}

int main () {

  const unsigned long limit = 100;
  long result;

  {
    timer Timer;

    result = find_convergents_of_e(limit);
  }

  std::cout << "Result: " << result << "\n";
}
