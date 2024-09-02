#include "timer.hpp"

#include <cstddef>
#include <cstdint>
#include <iostream>
#include <bitset>
#include <vector>
#include <cmath>

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
long find_goldbachs_contradictions(std::bitset<bitsetsize> &primes) {
  std::vector<long> prime_vector = {3, 5, 7};
  for (unsigned long i = 9; i < bitsetsize; i += 2) {
    if (primes[i] == 0) {
      bool correct = false;
      for (std::size_t j = 0; (not correct) && j < prime_vector.size(); ++j) {
        long current_prime = prime_vector[j];
        double current_prime_sqrt = std::sqrt((i - current_prime) >> 1);
        if (std::floor(current_prime_sqrt) == current_prime_sqrt) {
          correct = true;
        }
      }

      if (not correct) {
        return i;
      }
    } else {
      prime_vector.emplace_back(i);
    }
  }

  return -1;
}

int main () {

  const long max = 10'000; // large enough
  std::bitset<max> primes;
  long result;

  {
    timer Timer;

    find_primes(max, primes);
    result = find_goldbachs_contradictions(primes);
  }

  std::cout << "Result: " << result << "\n";
}
