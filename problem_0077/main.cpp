#include "timer.hpp"

#include <cstddef>
#include <cstdint>
#include <iostream>
#include <cmath>
#include <bitset>
#include <vector>
#include <memory>

template <size_t bitsetsize>
void find_primes(const std::size_t max, std::bitset<bitsetsize> &primes,
                 std::vector<long> & prime_divisors) {
  primes[2] = 1;
  prime_divisors[2] = 2;
  for (std::size_t i = 4; i < bitsetsize; i += 2) {
    prime_divisors[i] += 2;
  }


  primes[3] = 1;
  prime_divisors[3] = 3;
  for (std::size_t i = 6; i < bitsetsize; i += 3) {
    prime_divisors[i] += 3;
  }

  for (std::size_t i = 5; i < bitsetsize; i += 4) {
    primes[i] = 1;
    i += 2;
    primes[i] = 1;
  }

  std::size_t i;
  for (i = 5; i < std::sqrt(max); i += 4) {
    if (primes[i] == 1) {
      prime_divisors[i] = i;
      for (std::size_t j = 2 * i; j < bitsetsize; j += i) {
        prime_divisors[j] += i;
      }

      for (std::size_t j = i * i; j < bitsetsize; j += 4 * i) {
        primes[j] = 0;

        j += 2 * i;

        if (j < bitsetsize) {
          primes[j] = 0;
        }
      }
    }

    i += 2;

    if (primes[i] == 1) {
      prime_divisors[i] = i;
      for (std::size_t j = 2 * i; j < bitsetsize; j += i) {
        prime_divisors[j] += i;
      }

      for (std::size_t j = i * i; j < bitsetsize; j += 2 * i) {
        primes[j] = 0;

        j += 4 * i;

        if (j < bitsetsize) {
          primes[j] = 0;
        }
      }
    }
  }

  for (; i < bitsetsize; i += 2) {
    if (primes[i] == 1) {
      prime_divisors[i] = i;
      for (std::size_t j = 2 * i; j < bitsetsize; j += i) {
        prime_divisors[j] += i;
      }
    }
  }
}

long count_prime_summations(const long limit,
                            std::vector<long> & prime_divisors) {
  std::vector<long> partitions = {0, 0};
  unsigned long number = 2;
  while (partitions.back() < limit) {
    long partition = prime_divisors[number];
    for (std::size_t i = 2; i < number; ++i) {
      partition += prime_divisors[i] * partitions[number - i];
    }
    partition /= number;
    partitions.emplace_back(partition);
    ++number;
  }

  return partitions.size() - 1;
}

int main () {

  const unsigned long limit = 5000;
  const unsigned long max = 100; // chosen large enough
  auto primes = std::make_unique<std::bitset<max> >();
  std::vector<long> prime_divisors(max, 0);
  long result;

  {
    timer Timer;

    find_primes(max, *primes, prime_divisors);
    result = count_prime_summations(limit, prime_divisors);
  }

  std::cout << "Result: " << result << "\n";
}
