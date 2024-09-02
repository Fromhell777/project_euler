#include "timer.hpp"

#include <cstddef>
#include <cstdint>
#include <iostream>
#include <string>
#include <algorithm>

long find_permuted_mutiples() {
  long start_number = 10;
  long stop_number = 16;
  while (true) {
    for (long i = start_number; i <= stop_number; ++i) {
      long number = i << 1;
      std::string number_str = std::to_string(number);
      std::string i_str = std::to_string(i);
      long total_permutations = 1;
      while (std::is_permutation(std::begin(i_str), std::end(i_str),
                                 std:: begin(number_str))) {
        ++total_permutations;
        number += i;
        number_str = std::to_string(number);
      }

      if (total_permutations > 5) {
        return i;
      }
    }

    start_number *= 10;
    stop_number = stop_number * 10 + 6;
  }
}

int main () {

  long result;

  {
    timer Timer;

    result = find_permuted_mutiples();
  }

  std::cout << "Result: " << result << "\n";
}
