#include "timer.hpp"

#include <cstddef>
#include <cstdint>
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

long find_pandigital_substring_divisibility() {
  long sum = 0;
  std::vector<int> primes = {2, 3, 5, 7, 11, 13, 17};
  std::string number = "0123456789";
  do {
    bool prime = true;
    for (std::size_t i = 7; prime && i > 0 ; --i) {
      std::string subnumber = number.substr(i, 3);
      if (std::stoul(subnumber) % primes[i - 1] != 0) {
        prime = false;
      }
    }

    if (prime) {
      sum += std::stoul(number);
    }
  } while (std::next_permutation(std::begin(number), std::end(number)));

  return sum;
}

int main () {

  long result;

  {
    timer Timer;

    result = find_pandigital_substring_divisibility();
  }

  std::cout << "Result: " << result << "\n";
}
