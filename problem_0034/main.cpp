#include "timer.hpp"

#include <cstddef>
#include <cstdint>
#include <iostream>
#include <vector>

long find_digit_factorials(const long max) {
  long sum = 0;
  const std::vector<long> factorials = {1, 1, 2, 6, 24, 120, 720, 5'040, 40'320, 362'880};
  for (long i = 10; i < max; ++i) {
    long number = i;
    long digit_sum = 0;
    while (number) {
      digit_sum += factorials[number % 10];
      number /= 10;
      if (digit_sum > i) {
        number = 0;
      }
    }

    if (digit_sum == i) {
      sum += i;
    }
  }

  return sum;
}

int main () {

  const long max = 2'000'000;
  long result;

  {
    timer Timer;

    result = find_digit_factorials(max);
  }

  std::cout << "Result: " << result << "\n";
}
