#include "timer.hpp"

#include <cstddef>
#include <cstdint>
#include <iostream>
//#include <bitset>
#include <cmath>
//#include <memory>
#include <vector>
#include <array>
#include <algorithm>

//template <size_t bitsetsize>
//void find_primes_totients(size_t max, std::bitset<bitsetsize> &primes,
//                          std::vector<long> &totients) {
//  totients[1] = 1;
//  totients[2] = 1;
//  for (std::size_t i = 3; i < max; i += 2) {
//    totients[i] = i;
//  }
//
//  primes[2] = 1;
//  primes[3] = 1;
//  totients[3] = 2;
//  totients[6] = 2;
//  for (std::size_t i = 9; i < max; i += 6) {
//    totients[i] = (totients[i] * 2) / 3;
//  }
//
//  for (std::size_t i = 5; i < bitsetsize; i += 4) {
//    primes[i] = 1;
//    i += 2;
//    primes[i] = 1;
//  }
//
//  std::size_t i;
//  for (i = 5; i < std::sqrt(max); i += 4) {
//    if (primes[i] == 1) {
//      totients[i] = i - 1;
//      for (std::size_t j = 3 * i ; j < max; j += i << 1) {
//        totients[j] = (totients[j] * (i - 1)) / i;
//      }
//
//      for (std::size_t j = i * i; j < bitsetsize; j += 4 * i) {
//        primes[j] = 0;
//
//        j += 2 * i;
//
//        if (j < bitsetsize) {
//          primes[j] = 0;
//        }
//      }
//    }
//
//    i += 2;
//
//    if (primes[i] == 1) {
//      totients[i] = i - 1;
//      for (std::size_t j = 3 * i ; j < max; j += i << 1) {
//        totients[j] = (totients[j] * (i - 1)) / i;
//      }
//
//      for (std::size_t j = i * i; j < bitsetsize; j += 2 * i) {
//        primes[j] = 0;
//
//        j += 4 * i;
//
//        if (j < bitsetsize) {
//          primes[j] = 0;
//        }
//      }
//    }
//  }
//
//  for (; i < max; i += 2) {
//    if (primes[i] == 1) {
//      totients[i] = i - 1;
//      for (std::size_t j = 3 * i ; j < max; j += i << 1) {
//        totients[j] = (totients[j] * (i - 1)) / i;
//      }
//    }
//  }
//
//  for (std::size_t t = 4; t < max; t += 2) {
//    totients[t] = totients[t >> 1];
//    if ((t / 2) % 2 == 0) {
//      totients[t] = totients[t] << 1;
//    }
//  }
//}

void find_totients(size_t max, std::vector<unsigned long> & totients) {
  totients[1] = 1;
  totients[2] = 1;

  for (std::size_t i = 3; i <= max; i += 2) {
    if (totients[i] == 0) {
      totients[i] = i - 1;
      if (i <= std::sqrt(max)) {
        for (std::size_t j = i * i; j <= max; j += 2 * i){
          if (totients[j] == 0) {
            totients[j] = i;
          }
        }
      }
    } else {
      unsigned long prime = totients[i];
      unsigned long remainder = i / prime;
      if (remainder % prime == 0) {
        totients[i] = prime * totients[remainder];
      } else {
        totients[i] = (prime - 1) * totients[remainder];
      }
    }
  }

  for (std::size_t i = 4; i <= max; i += 2) {
    long index = i / 2;
    totients[i] = totients[index];
    if (index % 2 == 0) {
      totients[i] = 2 * totients[i];
    }
  }
}

bool is_permutation (long number1, long number2) {
  std::array<std::uint8_t, 10> digits{0};

  // number2 is always smaller than number1
  while (number2 != 0) {
    ++digits[number1 % 10];
    number1 /= 10;
    --digits[number2 % 10];
    number2 /= 10;
  }

  if (number1 != 0)
    return false;

  for (auto & digit : digits) {
    if (digit != 0)
      return false;
  }

  return true;
}

long find_totient_permutation(size_t max,
                              std::vector<unsigned long> &totients) {
  long result = 0;
  long double minimum_ratio = 2.0;
  for (std::size_t i = 2; i < max; ++i) {
    if (is_permutation(i, totients[i])) {
      long double ratio = static_cast<long double>(i) /
                          static_cast<long double>(totients[i]);
      if (ratio <= minimum_ratio) {
        minimum_ratio = ratio;
        result = i;
      }
    }

  }

  return result;
}

int main () {

  const long max = 10'000'000;
  //auto primes = std::make_unique<std::bitset<max + 1>>();
  std::vector<unsigned long> totients(max + 1);
  long result;

  {
    timer Timer;

    //find_primes_totients(max, *primes, totients);
    find_totients(max, totients);
    result = find_totient_permutation(max, totients);
  }

  std::cout << "Result: " << result << "\n";
}

// idea: check large prime pairs
