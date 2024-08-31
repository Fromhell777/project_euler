#include "timer.hpp"

#include <cstddef>
#include <cstdint>
#include <iostream>
#include <cmath>
#include <bitset>

template <size_t bitsetsize>
void find_primes(std::bitset<bitsetsize> &primes) {
  primes[0] = 0;
  primes[1] = 0;
  size_t i = 1;
  for (size_t i = 4; i < bitsetsize; i += 2) {
    primes[i] = 0;
  }

  for (i = 3; i < sqrt(bitsetsize); i += 2) {
    if (primes[i] == 1) {
      for (size_t j = i * i; j < bitsetsize; j = j + 2 * i) {
        primes[j] = 0;
      }
    }
  }
}

template <size_t bitsetsize>
long find_max_quadratic_prime(long max_coefficient,
                              std::bitset<bitsetsize> &primes) {
  int max_primes = 0;
  long product = 0;
  for (long b = 2; b <= max_coefficient; ++b) {
    if (primes[b] == 1) {
      // a should be negative for double primes encounter
      for (long a = - std::sqrt(4 * b); a < 0; ++a) {
        int current_max_primes = 0;
        while (primes[std::pow(current_max_primes, 2) + a * current_max_primes + b] == 1) {
          ++current_max_primes;
        }

        if (current_max_primes >= max_primes) {
          max_primes = current_max_primes;
          product = a * b;
        }
      }
    }
  }

  return product;
}


int main () {

  const long max_coefficient = 1000;
  // 80 was the maximum consecutive primes length above 1000
  const long max_prime = std::pow(80, 2) + max_coefficient * 80 + max_coefficient;
  std::bitset<max_prime> primes;
  primes.flip();
  long result;

  {
    timer Timer;

    find_primes(primes);

    result = find_max_quadratic_prime(max_coefficient, primes);

  }

  std::cout << "Result: " << result << "\n";
}
