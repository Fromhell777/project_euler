#include "timer.hpp"

#include <cstddef>
#include <cstdint>
#include <iostream>

long find_totient_maximum(const long limit) {
  static const std::array<int, 15> primes = {2, 3, 5, 7, 11, 13, 17, 19,
                                             23, 29, 31, 37, 41, 43, 47};
  long result = 1;
  for (const auto & prime : primes) {
    if (result * prime < limit) {
      result *= prime;
    } else {
      return result;
    }
  }

  return -1;
}

int main () {

  const long limit = 1'000'000;
  long result;

  {
    timer Timer;

    result = find_totient_maximum(limit);
  }

  std::cout << "Result: " << result << "\n";
}
