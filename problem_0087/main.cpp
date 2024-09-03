#include "timer.hpp"

#include <cstddef>
#include <cstdint>
#include <iostream>
#include <bitset>
#include <cmath>
#include <memory>
#include <vector>

template <size_t bitsetsize>
void find_primes(const size_t limit, std::bitset<bitsetsize> &primes,
                 std::vector<unsigned long> &squares,
                 std::vector<unsigned long> &cubes,
                 std::vector<unsigned long> &fourth_powers) {
  primes[2] = 1;
  primes[3] = 1;
  for (size_t i = 5; i < bitsetsize; i += 4) {
    primes[i] = 1;
    i += 2;
    primes[i] = 1;
  }

  for (std::size_t i = 5; i < std::sqrt(primes.size()); i += 4) {
    if (primes[i] == 1) {
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
      for (std::size_t j = i * i; j < bitsetsize; j += 2 * i) {
        primes[j] = 0;

        j += 4 * i;

        if (j < bitsetsize) {
          primes[j] = 0;
        }
      }
    }
  }

  for (std::size_t i = 2; i < std::sqrt(limit); ++i) {
    if (primes[i] == 1) {
      squares.push_back(i * i);
      if (i < std::cbrt(limit)) {
        cubes.push_back(i * i * i);
        if (i < std::sqrt(std::sqrt(limit))) {
          fourth_powers.push_back(i * i * i * i);
        }
      }
    }
  }
}

template <size_t bitsetsize>
long find_prime_power_triples(const unsigned long limit,
                              std::vector<unsigned long> &squares,
                              std::vector<unsigned long> &cubes,
                              std::vector<unsigned long> &fourth_powers) {
  auto results = std::make_unique<std::bitset<bitsetsize> >();
  for (auto &square : squares) {
    for (std::size_t i = 0; i < cubes.size() &&
                            square + cubes[i] < limit; ++i) {
      for (std::size_t j = 0; j < fourth_powers.size() &&
                              square + cubes[i] + fourth_powers[j] < limit; ++j) {
        (*results)[square + cubes[i] + fourth_powers[j]] = 1;
      }
    }
  }

  return (*results).count();
}

int main () {

  constexpr unsigned long limit = 50'000'000;
  constexpr unsigned long square_limit = std::sqrt(limit);
  auto primes = std::make_unique<std::bitset<square_limit + 1> >();
  std::vector<unsigned long> squares = {};
  std::vector<unsigned long> cubes = {};
  std::vector<unsigned long> fourth_powers = {};
  long result;

  {
    timer Timer;

    find_primes(limit, *primes, squares, cubes, fourth_powers);
    result = find_prime_power_triples<limit>(limit, squares, cubes,
                                             fourth_powers);
  }

  std::cout << "Result: " << result << "\n";
}
