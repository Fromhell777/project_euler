#include "timer.hpp"

#include <cstddef>
#include <cstdint>
#include <iostream>
#include <cmath>

unsigned long find_powerful_digit_counts() {
  unsigned long result = 0;
  for (long i = 1; i < 10; ++i) {
    result += std::floor(std::log10(10) / (std::log10(10) - std::log10(i)));
  }

  return result;
}

int main () {

  long result;

  {
    timer Timer;

    result = find_powerful_digit_counts();
  }

  std::cout << "Result: " << result << "\n";
}
