#include "timer.hpp"

#include <cstddef>
#include <cstdint>
#include <iostream>

std::uint32_t gauss(std::uint32_t const number) {
  return number * (number + 1) / 2;
}

int main () {

  std::uint32_t const max = 999;
  std::uint32_t result;

  {
    timer Timer;

    result = gauss(max / 5) * 5;
    result += gauss(max / 3) * 3;
    result -= gauss(max / 15) * 15;
  }

  std::cout << "Result: " << result << "\n";
}
