#include "timer.hpp"

#include <cstddef>
#include <cstdint>
#include <iostream>
#include <gmpxx.h>
#include <string>

long find_root_digital_expansion(const unsigned long limit) {
  long result = 0;
  unsigned long power = 4;
  long integer_part = 1;
  for (unsigned long i = 2; i <= limit; ++i) {
    if (i == power) {
      ++integer_part;
      power += (integer_part << 1) + 1;
    } else {
      mpf_class number(i, 340); // large enough
      mp_exp_t exp;
      mpf_class root = sqrt(number);
      std::string number_str = root.get_str(exp, 10, 102);
      for (std::size_t i = 0; i < limit; ++i) {
        result += number_str[i];
      }
      result -= limit * '0';
    }
  }

  return result;
}

int main () {

  const unsigned long limit = 100;

  long result;

  {
    timer Timer;

    result = find_root_digital_expansion(limit);
  }

  std::cout << "Result: " << result << "\n";
}
