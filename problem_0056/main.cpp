#include "timer.hpp"

#include <cstddef>
#include <cstdint>
#include <iostream>
#include <gmpxx.h>
#include <string>

long sum_of_digits(std::string number) {
  long sum = 0;
  for (auto element : number) {
    sum += element;
  }

  sum -= number.size() * '0';
  return sum;
}

long find_powetfull_digit_sum(long max_base, long max_exponent) {
  unsigned long max_digit_sum = 0;
  for (long base = max_base; base > 0; --base) {
    mpz_class number = 0;
    bool viable_result = true;
    for (long exponent = max_exponent; exponent > 0 && viable_result; --exponent) {
      mpz_ui_pow_ui(number.get_mpz_t(), base, exponent);
      unsigned long digit_sum = sum_of_digits(number.get_str());
      if (digit_sum > max_digit_sum) {
        max_digit_sum = digit_sum;
      }

      if (number.get_str().size() * 9 < max_digit_sum) {
        viable_result = false;
      }
    }
  }

  return max_digit_sum;
}


int main () {

  long max_base = 99;
  long max_exponent = 100;
  long result;

  {
    timer Timer;

    result = find_powetfull_digit_sum(max_base, max_exponent);
  }

  std::cout << "Result: " << result << "\n";
}
