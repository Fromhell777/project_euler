#include "timer.hpp"

#include <cstddef>
#include <cstdint>
#include <iostream>
#include <cmath>

std::uint64_t find_self_powers_sum(const std::uint64_t max,
                                   const std::uint64_t modular) {
  std::uint64_t result = 0;
  for (std::uint64_t i = 1; i <= max; ++i) {
    std::uint64_t current_result = i;
    for (std::uint64_t j = 1; j < i; ++j) {
      current_result = (current_result * i) % modular;
    }

    result = (result + current_result) % modular;
  }

  return result;
}

// can only be used if the internal variable can be larger than modulo ^ 2
std::uint64_t self_power(const std::uint64_t number,
                         const std::uint64_t exponent,
                         const std::uint64_t modulo) {
  if (exponent == 0) {
    return 1;
  }

  std::uint64_t result = self_power(number, exponent / 2, modulo);
  result = (result * result) % modulo;
  if (exponent % 2 == 0) {
    return result;
  }

  return (result * number) % modulo;
}

std::uint64_t find_self_powers_sum2(const std::uint64_t max,
                                    const std::uint64_t modular) {
  std::uint64_t result = 0;
  for (std::uint64_t i = 1; i <= max; ++i) {
    result = (result + self_power(i % modular, i, modular)) % modular;
  }

  return result;
}

int main () {

  const std::uint64_t max = 1000;
  const long digits = 10;
  std::uint64_t result;

  {
    timer Timer;

    result = find_self_powers_sum(max, std::pow(10, digits));
  }

  std::cout << "Result: " << result << "\n";
}
