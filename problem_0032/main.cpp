#include "timer.hpp"

#include <cstddef>
#include <cstdint>
#include <iostream>
#include <string>
#include <algorithm>

long find_pandigial_products(std::string identity) {
  long sum = 0;
  while (std::next_permutation(std::begin(identity), std::end(identity))) {
    long product = std::stol(identity.substr(0,4));
    long count = 119; // 5! - 1
    bool pandigital = false;
    while (count != 0) {
      if (pandigital == false && identity[identity.size() - 1] != '1') {
        for (size_t i = 1; i < 5; ++i) {
          if (identity[4 + i] != '1') {
            long multiplicand = std::stol(identity.substr(4, i));
            long multiplier = std::stol(identity.substr(4 + i, 5 - i));
            if (multiplicand * multiplier == product) {
              pandigital = true;
            }
          }
        }
      }

      --count;
      std::next_permutation(std::begin(identity), std::end(identity));
    }

    if (pandigital) {
      sum += product;
    }
  }

  return sum;
}

int main () {

  std::string identity = "298765431"; // starting number must be larger than 3000
  long result;

  {
    timer Timer;

    result = find_pandigial_products(identity);
  }

  std::cout << "Result: " << result << "\n";
}
