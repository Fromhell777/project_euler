#include "timer.hpp"

#include <cstddef>
#include <cstdint>
#include <iostream>
#include <bitset>

// number must be 10 digits long
bool is_pandigital(long number) {
  std::bitset<10> numbers;
  numbers[0] = 1;
  while (number != 0) {
    if (numbers[number % 10] == 1) {
      return false;
    }
    numbers[number % 10] = 1;
    number /= 10;
  }

  return true;
}

long find_pandigital_multiples() {
  for (long i = 9999; i > 5000; --i) {
    long result = i * 100'000 + i * 2;
    if (is_pandigital(result)) {
      return result;
    }
  }

  return -1; // failed to find pandigital
}

int main () {

  long result;

  {
    timer Timer;

    result = find_pandigital_multiples();
  }

  std::cout << "Result: " << result << "\n";
}
