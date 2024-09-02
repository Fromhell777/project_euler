#include "timer.hpp"

#include <cstddef>
#include <cstdint>
#include <iostream>
#include <cmath>

long find_pentagonal_diff() {
  for (long n = 1; ; ++n) {
    for (long k = 1; k < n; ++k) {
      double temp_value = 12 * k * (6 * n - 3 * k - 1);
      double temp_value_sqrt = std::sqrt(1 + temp_value);
      if (std::floor(temp_value_sqrt) == temp_value_sqrt &&
          static_cast<int>(temp_value_sqrt) % 6 == 5) {
        temp_value_sqrt = std::sqrt(1 + 24 * n * (3 * n - 1) - temp_value);
        if (std::floor(temp_value_sqrt) == temp_value_sqrt &&
            static_cast<int>(temp_value_sqrt) % 6 == 5) {
          return temp_value / 24;
        }
      }
    }
  }

  return -1;
}

int main () {

  long result;

  {
    timer Timer;

    result = find_pentagonal_diff();
  }

  std::cout << "Result: " << result << "\n";
}
