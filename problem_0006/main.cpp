#include "timer.hpp"

#include <cstddef>
#include <cstdint>
#include <iostream>
#include <math.h>

long sum_square_difference(long value) {
  long result = 0;
  result += 3 * pow(value, 4);
  result += 2 * pow(value, 3);
  result -= 3 * pow(value, 2);
  result -= 2 * value;
  return result / 12;
}

int main () {

  long max = 100;
  long result;

  {
    timer Timer;

    result = sum_square_difference(max);
  }

  std::cout << "Result: " << result << "\n";
}
