#include "timer.hpp"

#include <cstddef>
#include <cstdint>
#include <iostream>

long find_longest_collatz_chain(size_t max, long *numbers) {
  numbers[1] = 1;
  long chain_length = 1;
  long max_chain_length = 0;
  size_t collatz_result = 0;
  long result = 0;
  for (size_t i = 1; i < max; ++i) {
    collatz_result = i;
    while (collatz_result != 1) {
      if (collatz_result < max && numbers[collatz_result] != 0) {
        chain_length += numbers[collatz_result] - 2;
        collatz_result = 2;
      }

      if (collatz_result % 2 == 0) {
        collatz_result /= 2;
      } else {
        collatz_result = collatz_result * 3 + 1;
      }

      ++chain_length;
    }


    if (chain_length > max_chain_length) {
      max_chain_length = chain_length;
      result = i;
    }

    numbers[i] = chain_length;
    chain_length = 1;
  }

  return result;
}

int main () {

  const long max = 1'000'000;
  long numbers[max] = {};
  long result;

  {
    timer Timer;

    result = find_longest_collatz_chain(max, numbers);
  }

  std::cout << "Result: " << result << "\n";
}
