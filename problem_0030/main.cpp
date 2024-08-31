#include "timer.hpp"

#include <cstddef>
#include <cstdint>
#include <iostream>
#include <cmath>
#include <numeric>
#include <vector>

long find_digit_fifth_powers(const int power, const int number_of_digits) {
  long limit = number_of_digits * std::pow(9, power);
  std::vector<int> digits;
  long sum = 0;
  for (long i = 2; i <= limit; ++i) {
    for (int j = 0; j <= number_of_digits; ++j) {
      digits.emplace_back((i / static_cast<int>(std::pow(10, j))) % 10);
    }

    // if condition only for the fifth power
    if (std::accumulate(std::begin(digits), std::end(digits), 0) % 10 == i % 10) {
      long current_sum = 0;
      for (auto element : digits) {
        current_sum += std::pow(element, power);
      }

      if (current_sum == i) {
        sum += i;
      }
    }

    digits.clear();
  }

  return sum;
}

int main () {

  const int power = 5;
  const int number_of_digits = 5;
  long result;

  {
    timer Timer;

    result = find_digit_fifth_powers(power, number_of_digits);
  }

  std::cout << "Result: " << result << "\n";
}
