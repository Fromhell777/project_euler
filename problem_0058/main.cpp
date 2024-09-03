#include "timer.hpp"

#include <cstddef>
#include <cstdint>
#include <iostream>
#include <vector>
#include <map>

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

bool check_prime(const unsigned long value) {
  static const std::vector<unsigned long> first_primes = { 2,  3,  5,  7, 11,
                                                          13, 17, 19, 23, 29,
                                                          31, 37, 41, 43, 47,
                                                          53, 59, 61, 67, 71,
                                                          73, 79};
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

long find_spiral_primes(long prime_ratio) {
  long number = 1;
  long total_primes = 0;
  long total_numbers = 1;
  for (long side_length = 2; ; side_length += 2) {
    for (long i = 0; i < 4; ++i) {
      number += side_length;
      if (check_prime(number)) {
        ++total_primes;
      }
    }

    total_numbers += 4;

    if (total_primes * prime_ratio < total_numbers) {
      return side_length + 1;
    }
  }
  return -1;
}

int main () {

  const long prime_ratio = 10;
  long result;

  {
    timer Timer;

    result = find_spiral_primes(prime_ratio);
  }

  std::cout << "Result: " << result << "\n";
}
