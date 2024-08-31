#include "timer.hpp"

#include <cstddef>
#include <cstdint>
#include <iostream>

long find_pythagorean_triplet() {
  long a = 0;
  long b = 0;
  bool done = false;
  while (b < 667 && !done) {
    ++b;
    while (a <= b && a < 334 && !done) {
      ++a;
      if (1000 * a + 1000 * b - a * b == 500'000) {
        done = true;
      }
    }
    if (!done) {
      a = 0;
    }
  }

  // std::cout << "a: " << a << "\n";
  // std::cout << "b: " << b << "\n";
  // std::cout << "c: " << 1000 - a - b << "\n";
  return a * b * (1000 - a - b);

}

int main () {

  long result;

  {
    timer Timer;

    result = find_pythagorean_triplet();
  }

  std::cout << "Result: " << result << "\n";
}
