#include "timer.hpp"

#include <cstddef>
#include <cstdint>
#include <iostream>

long find_combinatoric_selections(const long max, const long limit) {
  long result = 0;
  for (long n = 1; n <= max; ++n) {
    long tmp_n = n;
    long tmp_r = 1;
    long number = 1;
    while (number <= limit && tmp_r < (n >> 1) + 1) {
      number = (number * tmp_n) / tmp_r;
      --tmp_n;
      ++tmp_r;
    }

    if (number > limit) {
      result += n + 1 - 2 * (tmp_r - 1);
    }
  }

  return result;
}

int main () {

  const long max = 100;
  const long limit = 1'000'000;
  long result;

  {
    timer Timer;

    result = find_combinatoric_selections(max, limit);
  }

  std::cout << "Result: " << result << "\n";
}
