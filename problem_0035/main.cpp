#include "timer.hpp"

#include <cstddef>
#include <cstdint>
#include <iostream>
#include <string>
#include <bitset>
#include <algorithm>

template <size_t bitsetsize>
void find_primes(const size_t max, std::bitset<bitsetsize> &primes) {
  primes[2] = 1;
  primes[3] = 1;
  for (size_t i = 5; i < bitsetsize; i += 4) {
    primes[i] = 1;
    i += 2;
    primes[i] = 1;
  }

  for (size_t i = 5; i < sqrt(max); i += 4) {
    if (primes[i] == 1) {
      for (size_t j = i * i; j < bitsetsize; j += 4 * i) {
        primes[j] = 0;

        j += 2 * i;

        if (j < bitsetsize) {
          primes[j] = 0;
        }
      }
    }

    i += 2;

    if (primes[i] == 1) {
      for (size_t j = i * i; j < bitsetsize; j += 2 * i) {
        primes[j] = 0;

        j += 4 * i;

        if (j < bitsetsize) {
          primes[j] = 0;
        }
      }
    }
  }
}

template <size_t bitsetsize>
long find_circular_primes(const size_t max, std::bitset<bitsetsize> primes) {
  long total = 0;
  for (size_t i = 2; i < max; ++i) {
    if (primes[i] == 1) {
      bool is_prime = true;
      std::string number_str = std::to_string(i);
      for (size_t j = 0; j < number_str.size() && is_prime; ++j) {
        std::rotate(std::begin(number_str), std::begin(number_str) + 1,
                    std::end(number_str));
        if (primes[std::stoi(number_str)] == 0) {
          is_prime = false;
        }
      }

      if (is_prime) {
        ++total;
      }
    }
  }

  return total;
}

int main () {

  const long max = 1'000'000;
  std::bitset<max> primes;
  long result;

  {
    timer Timer;

    find_primes(max, primes);
    result = find_circular_primes(max, primes);
  }

  std::cout << "Result: " << result << "\n";
}
