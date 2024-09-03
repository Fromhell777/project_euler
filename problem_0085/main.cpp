#include "timer.hpp"

#include <cstddef>
#include <cstdint>
#include <iostream>
#include <cmath>

long count_rectangles(const unsigned long target) {
  unsigned long width = (-1 + std::sqrt(1 + 4 * std::sqrt(4 * target))) / 2.0;
  unsigned long height = width;
  unsigned long rectangles = width * (width + 1) * height * (height + 1) / 4;
  unsigned long smallest_error = target - rectangles;
  unsigned long area = width * height;
  rectangles = (width + 1) * (width + 2) * (height + 1) * (height + 2) / 4;

  if (rectangles - target < smallest_error) {
    smallest_error = rectangles - target;
    area = (width + 1) * (height + 1);
  }

  while (width > 0) {
    rectangles = width * (width + 1) * (height + 1) * (height + 2) / 4;
    while (rectangles < target) {
      ++height;
      if (target - rectangles < smallest_error) {
        smallest_error = target - rectangles;
        area = width * height;
      }
      rectangles += width * (width + 1) * (height + 1) / 2;
    }

    if (rectangles - target < smallest_error) {
      smallest_error = rectangles - target;
      area = width * (height + 1);
    }

    --width;
  }

  return area;
}

int main () {

  constexpr unsigned long target = 2'000'000;
  long result;

  {
    timer Timer;

    result = count_rectangles(target);
  }

  std::cout << "Result: " << result << "\n";
}
