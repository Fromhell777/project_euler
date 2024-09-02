#include "timer.hpp"

#include <cstddef>
#include <cstdint>
#include <iostream>

long find_t_p_h_number() {
  long number = 40755;
  for (long i = 166; ; ++i) {
    number += 3 * i - 2;
    double number_sqrt = std::sqrt(1 + (number << 3));
    if (std::floor(number_sqrt) == number_sqrt &&
        static_cast<long>(number_sqrt) % 6 == 5) {
      return number;
    }
  }
}

int main () {

  long result;

  {
    timer Timer;

    result = find_t_p_h_number();
  }

  std::cout << "Result: " << result << "\n";
}
