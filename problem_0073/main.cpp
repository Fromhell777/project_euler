#include "timer.hpp"

#include <cstddef>
#include <cstdint>
#include <iostream>
#include <cmath>
#include <vector>

long find_fractions_in_range(const unsigned long limit,
                             const long left_denominator,
                             const long right_denominator) {
  unsigned long count = 0;
  std::size_t top = 0;
  std::vector<long> stack(limit / 2);
  unsigned long left = left_denominator;
  unsigned long right = right_denominator;
  bool done = false;
  while (! done) {
    unsigned long mediant = left + right;
    if (mediant > limit) {
      if (top > 0) {
        left = right;
        --top;
        right = stack[top];
      } else {
        done = true;
      }
    } else {
      ++count;
      stack[top] = right;
      ++top;
      right = mediant;
    }
  }

  return count;
}

int main () {

  const unsigned long max = 12'000;
  const long left_denominator = 3;
  const long right_denominator = 2;
  long result;

  {
    timer Timer;

    result = find_fractions_in_range(max, left_denominator,
                                     right_denominator);
  }

  std::cout << "Result: " << result << "\n";
}
