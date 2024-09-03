#include "timer.hpp"

#include <cstddef>
#include <cstdint>
#include <iostream>
#include <cmath>
#include <vector>

long find_totients(size_t max) {
  std::vector<unsigned long> totients(max + 1);
  totients[1] = 1;
  totients[2] = 1;
  long result = totients[2];

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

    result += totients[i];
  }

  for (std::size_t i = 4; i <= max; i += 2) {
    long index = i / 2;
    totients[i] = totients[index];
    if (index % 2 == 0) {
      totients[i] = 2 * totients[i];
    }

    result += totients[i];
  }

  return result;
}

int main () {

  const long max = 1'000'000;
  long result;

  {
    timer Timer;

    result = find_totients(max);
  }

  std::cout << "Result: " << result << "\n";
}
