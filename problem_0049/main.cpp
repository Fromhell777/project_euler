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
std::string find_prime_permutation(std::bitset<bitsetsize> &primes) {
  for (long i = 1489; i < 4440; i += 2) {
    if (primes[i] == 1 && primes[i + 3330] == 1 && primes[i + 6660] == 1) {
      std::string number_0 = std::to_string(i);
      std::string number_1 = std::to_string(i + 3330);
      std::string number_2 = std::to_string(i + 6660);
      if (std::is_permutation(std::begin(number_0), std::end(number_0),
                              std::begin(number_1)) &&
          std::is_permutation(std::begin(number_0), std::end(number_0),
                              std::begin(number_2))) {
        return number_0 + number_1 + number_2;
      }
    }
  }

  return "FAILED";
}

int main () {

  const long max = 10'000;
  std::bitset<max> primes;
  std::string result;

  {
    timer Timer;

    find_primes(max, primes);
    result = find_prime_permutation(primes);
  }

  std::cout << "Result: " << result << "\n";
}
