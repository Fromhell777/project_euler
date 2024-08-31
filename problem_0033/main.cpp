#include "timer.hpp"

#include <cstddef>
#include <cstdint>
#include <iostream>
#include <numeric>

int gcd(int a, int b) {
  while (true) {
    if (a == 0) {
      return b;
    }
    b %= a;
    if (b == 0) {
      return a;
    }
    a %= b;
  }
}

long find_digit_cancelling_fractions() {
  long numerators = 1;
  long denominators = 1;
  for (int i = 11; i < 100; ++i) {
    if (i % 10 != 0) {
      for (float j = 1; j < std::min(i / 10, i % 10); ++j) {
        float simplified = j / (i % 10);
        if (simplified == (j * 10 + (i / 10)) / i) {
          numerators *= j * 10 + (i / 10);
          denominators *= i;
        }
      }

      if (i % 10 < i / 10) {
        for (float j = 1; j < std::min(i % 10, i / 10); ++j) {
          float simplified = j / (i / 10);
          if (simplified == (j + 10 * (i % 10)) / i) {
            numerators *= j + 10 * (i % 10);
            denominators *= i;
          }
        }
      }
    }
  }

  return denominators / gcd(numerators, denominators);
}

int main () {

  float result;

  {
    timer Timer;

    result = find_digit_cancelling_fractions();
  }

  std::cout << "Result: " << result << "\n";
}
