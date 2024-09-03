#include "timer.hpp"

#include <cstddef>
#include <cstdint>
#include <iostream>
#include <vector>

long calculate_chain_length(unsigned long number,
                            std::vector<unsigned long> & digit_factorial_chains) {
  static std::vector<unsigned long> factorials = {1, 1, 2, 6, 24, 120, 720,
                                                  5'040, 40'320, 362'880};
  unsigned long chain_length = 0;
  unsigned long chain_number = number;
  std::vector<unsigned long> encountered_numbers;
  while (true) {
    if (chain_number >= digit_factorial_chains.size() ||
        digit_factorial_chains[chain_number] == 0) {
      long new_number = 0;
      while (chain_number != 0) {
        new_number += factorials[chain_number % 10];
        chain_number /= 10;
      }

      chain_number = new_number;
      ++chain_length;
    } else {
      chain_length += digit_factorial_chains[chain_number];

      digit_factorial_chains[number] = chain_length;
      return chain_length;
    }
  }

  return -1;
}

long find_digit_factorial_chains(unsigned long limit) {
  std::vector<unsigned long> digit_factorial_chains(limit);

  // 1 chain
  digit_factorial_chains[1] = 1;

  // 2 chain
  digit_factorial_chains[2] = 1;

  // 145 chain
  digit_factorial_chains[145] = 1;

  // 40585 chain
  digit_factorial_chains[40585] = 1;

  // 169 chain
  digit_factorial_chains[169] = 3;
  digit_factorial_chains[363601] = 3;
  digit_factorial_chains[1454] = 3;

  // 871 chain
  digit_factorial_chains[871] = 2;
  digit_factorial_chains[45361] = 2;

  // 872 chain
  digit_factorial_chains[872] = 2;
  digit_factorial_chains[45362] = 2;

  long result = 0;
  for (unsigned long i = 3; i < limit; ++i) {
    if (calculate_chain_length(i, digit_factorial_chains) == 60) ++ result;
  }

  return result;
}

int main () {

  const unsigned long limit = 1'000'000;
  long result;

  {
    timer Timer;

    result = find_digit_factorial_chains(limit);
  }

  std::cout << "Result: " << result << "\n";
}
