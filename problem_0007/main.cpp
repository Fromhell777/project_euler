#include "timer.hpp"

#include <cstddef>
#include <cstdint>
#include <iostream>
#include <bitset>

template <size_t bitsetsize>
long find_primes(long max, std::bitset<bitsetsize> primes) {
  long index = 0;
  primes[0] = 0;
  primes[1] = 0;
  size_t i = 1;
  while (index < max && i < bitsetsize) {
    ++i;
    if (primes[i] == 1) {
      ++index;
      for (size_t j = 2 * i; j < bitsetsize; j = j + i) {
        primes[j] = 0;
      }
    }
  }

  if (index != max) {
    std::cout << "Warning: bitset was to small\n";
  }
  return i;
}

int main () {

  const long max = 10'001;
  std::bitset<max * 100> primes; // change if to small
  primes.flip();
  long result;

  {
    timer Timer;

    result = find_primes(max, primes);
  }

  std::cout << "Result: " << result << "\n";
}
