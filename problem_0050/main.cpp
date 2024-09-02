#include "timer.hpp"

#include <cstddef>
#include <cstdint>
#include <iostream>
#include <bitset>
#include <vector>

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
long find_consecutive_prime_sum(std::bitset<bitsetsize> &primes) {
  std::vector<unsigned long> prime_sums = {0, 2};
  long max_serie_length = 1;
  for (std::size_t i = 3; i < bitsetsize; i += 2) {
    if (primes[i] == 1) {
      prime_sums.emplace_back(prime_sums.back() + i);
      if (prime_sums.back() < bitsetsize) {
        ++max_serie_length;
      }
    }
  }

  for ( ; max_serie_length > 0; --max_serie_length) {
    unsigned long sum = 0;
    for (long offset = 0; sum < bitsetsize; ++offset) {
      if (primes[sum] == 1) {
        return sum;
      }
      sum = prime_sums[max_serie_length + offset] - prime_sums[offset];
    }

  }

  return -1;
}

int main () {

  const long max = 1'000'000;
  std::bitset<max> primes;
  long result;

  {
    timer Timer;

    find_primes(max, primes);
    result = find_consecutive_prime_sum(primes);
  }

  std::cout << "Result: " << result << "\n";
}
