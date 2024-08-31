#include "timer.hpp"

#include <cstddef>
#include <cstdint>
#include <iostream>
#include <bitset>

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
long find_circular_primes(const size_t max, std::bitset<bitsetsize> &primes) {
  long sum = 0;
  for (size_t i = 11; i < max; ++i) {
    if (primes[i] == 1) {
      bool is_prime = true;
      long number = i / 10;
      long number_truncated = i % 10;
      int digits = 1;
      while (is_prime && number) {
        if (primes[number] == 0) {
          is_prime = false;
        }
        if (primes[number_truncated] == 0) {
          is_prime = false;
        }

        number_truncated += (number % 10) * std::pow(10, digits);
        number /= 10;
        ++digits;
      }

      if (is_prime) {
        sum += i;
      }
    }
  }

  return sum;
}

int main () {

  const size_t max = 1'000'000;
  std::bitset<max> primes;
  long result;

  {
    timer Timer;

    find_primes(max, primes);
    result = find_circular_primes(max, primes);
  }

  std::cout << "Result: " << result << "\n";
}
