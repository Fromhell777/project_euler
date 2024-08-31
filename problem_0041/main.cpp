#include "timer.hpp"

#include <cstddef>
#include <cstdint>
#include <iostream>
#include <cmath>
#include <string>
#include <algorithm>

bool check_prime(long value) {
  long divisor = 5;

  if(value % 2 == 0) {
    return false;
  }
  if(value % 3 == 0) {
    return false;
  }

  double max_value = sqrt(value);
  while(divisor < max_value ) {
      if(value % divisor == 0) {
        return false;
      }

      divisor += 2;

      if(value % divisor == 0) {
        return false;
      }

      divisor += 4;
  }

  return true;
}

long find_pandigital_prime() {
  std::string number = "7654321"; // 9 and 8 digits is is a multiple of 9 (sum of digits)
  while (not number.empty()) {
    do {
      if (check_prime(std::stoul(number))) {
        return std::stoul(number);
      }
    } while (std::prev_permutation(std::begin(number), std::end(number)));

    number.erase(std::begin(number));
  }

  return -1;
}

int main () {

  long result;

  {
    timer Timer;

    result = find_pandigital_prime();
  }

  std::cout << "Result: " << result << "\n";
}
