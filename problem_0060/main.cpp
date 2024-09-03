#include "timer.hpp"

#include <cstddef>
#include <cstdint>
#include <iostream>
#include <cmath>
#include <bitset>
#include <vector>
#include <memory>
#include <numeric>
#include <map>

template <size_t bitsetsize>
void find_primes(const size_t max, std::bitset<bitsetsize> &primes) {
  primes[2] = 1;
  primes[3] = 1;
  for (size_t i = 5; i < bitsetsize; i += 4) {
    primes[i] = 1;
    i += 2;
    primes[i] = 1;
  }

  for (size_t i = 5; i < std::sqrt(max); i += 4) {
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

unsigned long int_power_modular(unsigned long base,
                                unsigned long exponent,
                                const unsigned long modulo) {
  base %= modulo;
  unsigned long result = 1;
  if (modulo < 10e9) {
    while (exponent > 1) {
      if (exponent % 2) {
        result *= base;
        if (result >= modulo) result %= modulo;
      }

      base *= base;
      if (base >= modulo) base %= modulo;

      exponent = exponent >> 1;
    }

    result *= base;
    if (result >= modulo) result %= modulo;

    return result;
  } else {
    while (exponent > 1) {
      if (exponent % 2) {
        for (unsigned long j = 0; j < base; ++j) {
          result += base;
          if (result >= modulo) result %= modulo;
        }
      }

      for (unsigned long j = 0; j < base; ++j) {
        base += base;
        if (base >= modulo) base %= modulo;
      }

      exponent = exponent >> 1;
    }

    for (unsigned long j = 0; j < base; ++j) {
      result += base;
      if (result >= modulo) result %= modulo;
    }

    return result;
  }
}

bool check_large_prime(const unsigned long value) {
  static const std::vector<unsigned long> first_primes = { 2,  3,  5,  7, 11,
                                                          13, 17, 19, 23, 29};
  if (value == 1) return false;

  for (const auto& prime : first_primes) {
    if (value % prime == 0) return value == prime;
  }

  unsigned long d = value - 1;
  unsigned long r = 0;

  while (d % 2 == 0) {
    d /= 2;
    ++r;
  }

  // works up to 2 ^ 64
  static const std::map<unsigned long long, std::vector<unsigned long> > witnesses_map = {
      {2'047ull, {2}},
      {1'373'653ull, {2, 3}},
      {9'080'191ull, {31, 73}},
      {25'326'001ull, {2, 3, 5}},
      {4'759'123'141ull, {2, 7, 61}},
      {1'122'004'669'633ull, {2, 13, 23, 1662803ull}},
      {2'152'302'898'747ull, {2, 3, 5, 7, 11}},
      {3'474'749'660'383ull, {2, 3, 5, 7, 11, 13}},
      {341'550'071'728'321ull, {2, 3, 5, 7, 11, 13, 17}},
      {3'825'123'056'546'413'051ull, {2, 3, 5, 7, 11, 13, 17, 19, 23}},
      {18'446'744'073'709'551'615ull, {2,  3,  5, 7, 11, 13, 17, 19, 23, 29, 31, 37}}};


  std::vector<unsigned long> witnesses = witnesses_map.upper_bound(value)->second;

  for (const auto& witness : witnesses) {
    unsigned long x = int_power_modular(witness, d, value);
    if (x != 1 && x != value - 1) {
      for (unsigned long i = 1; i < r && x != value - 1; ++i) {
        x = int_power_modular(x, 2, value);
        if (x == 1) {
          return false;
        }
      }

      if (x != value - 1) {
        return false;
      }
    }
  }

  return true;
}

template <size_t bitsetsize>
bool check_property(std::bitset<bitsetsize> &primes,
                    std::vector<unsigned long> &combination,
                    unsigned long number, unsigned long times_number) {
  for (auto element: combination) {
    unsigned long times_element = 1;
    while (times_element <= element) {
      times_element *= 10;
    }

    unsigned long result = element * times_number + number;
    if (result < bitsetsize) {
      if (primes[result] == 0) return false;
    } else {
      if (check_large_prime(element * times_number + number) == 0) return false;
    }

    result = number * times_element + element;
    if (result < bitsetsize) {
      if (primes[result] == 0) return false;
    } else {
      if (check_large_prime(number * times_element + element) == 0) return false;
    }
  }

  return true;
}

template <size_t bitsetsize>
long find_prime_pair_sets(std::bitset<bitsetsize> &primes,
                          unsigned long number_of_primes) {
  std::vector<std::vector<unsigned long> > combinations;
  unsigned long min_sum = 1'000'000; // chosen large enough
  unsigned long times_number = 1; // count the digit size
  for (std::size_t i = 3; i < min_sum; i += 2) {
    if (primes[i] == 1) {
      if (i >= times_number) times_number *= 10;
      unsigned long original_size = combinations.size();
      for (std::size_t j = 0; j < original_size; ++j) {
        std::vector<unsigned long> combination = combinations[j];
        if (std::accumulate(std::begin(combination), std::end(combination),
                            0ull) +
            (number_of_primes - combination.size()) * i > min_sum ) {
          combinations.erase(std::begin(combinations) + j); // erase impossible candidates
          --original_size;
          --j;
        } else if (check_property(primes, combination, i, times_number)) {
          combinations[j].emplace_back(i);
          combinations.push_back(combination);
          if (combinations[j].size() == number_of_primes) {
            unsigned long sum = 0;
            for (auto &element : combinations[j]) {
              sum += element;
            }

            if (sum < min_sum) min_sum = sum;
          }
        }
      }

      if (min_sum == 1'000'000) {
        combinations.push_back({i});
      }
    }
  }

  return min_sum;
}

int main () {

  const unsigned long max = 100'000'000;
  auto primes = std::make_unique<std::bitset<max> >();
  const unsigned long number_of_primes = 5;
  long result;

  {
    timer Timer;

    find_primes(max, *primes);
    result = find_prime_pair_sets(*primes, number_of_primes);
  }

  std::cout << "Result: " << result << "\n";
}
