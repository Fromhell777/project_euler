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
bool check_prime_occurences(const long number, const long stepsize,
                            const long permitted_faults,
                            std::bitset<bitsetsize> &primes) {
  long faults = 0;
  long current_number = number;
  long correct = 0;
  while (correct < 7) {
    current_number += stepsize;
    if (primes[current_number] == 1) {
      ++correct;
    } else {
      ++faults;
    }

    if (faults > permitted_faults) {
      return false;
    }
  }

  return true;
}

template <size_t bitsetsize>
long find_prime_digit_replacements(std::bitset<bitsetsize> &primes) {
  for (std::size_t i = 11; i < bitsetsize; i += 2) {
    if (primes[i] == 1) {
      long prime = i / 10;
      long stepsize = 10;
      long stepsize_zeros = 0;
      long stepsize_ones = 0;
      long stepsize_twos = 0;
      while (prime != 0) {
        long digit = prime % 10;
        if (digit == 0) {
          stepsize_zeros += stepsize;
          if (check_prime_occurences(i, stepsize_zeros, 2, primes)) {
            return i;
          }
        }

        if (digit == 1) {
          stepsize_ones += stepsize;
          if (check_prime_occurences(i, stepsize_ones, 1, primes)) {
            return i;
          }
        }

        if (digit == 2) {
          stepsize_twos += stepsize;
          if (check_prime_occurences(i, stepsize_twos, 0, primes)) {
            return i;
          }
        }

        prime /= 10;
        stepsize *= 10;
      }
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
    result = find_prime_digit_replacements(primes);
  }

  std::cout << "Result: " << result << "\n";
}
