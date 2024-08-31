#include "timer.hpp"

#include <cstddef>
#include <cstdint>
#include <iostream>
#include <bitset>
#include <cmath>
#include <memory>

template <size_t bitsetsize>
long find_primes(size_t max, std::bitset<bitsetsize> &primes) {
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

  long sum = 0;
  for (size_t i = 2; i < max; ++i) {
    if (primes[i] == 1) {
      sum += i;
    }
  }
  return sum;
}

int main () {

  const long max = 2'000'000;
  auto primes = std::make_unique<std::bitset<max + 1>>();
  long result;

  {
    timer Timer;

    result = find_primes(max, *primes);
  }

  std::cout << "Result: " << result << "\n";
}
