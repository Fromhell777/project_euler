#include "timer.hpp"

#include <cstddef>
#include <cstdint>
#include <iostream>

int main () {

  const long square_width = 1001;
  long result;

  {
    timer Timer;

    result = (4 * square_width * square_width * square_width + 3 * square_width
              * square_width + 8 * square_width - 9) / 6;
  }

  std::cout << "Result: " << result << "\n";
}
// in every layer the sum is 6 * n + 4 * l
// where n is the step increase from corner to corner at that layer
// while l is the lower rightmost number in that layer
// then perform Gaussses formula
