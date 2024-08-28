#include "timer.hpp"

#include <cstddef>
#include <cstdint>
#include <iostream>

int main () {

  long max = 4'000'000;
  long fib_temp = 0;
  long fib1 = 0;
  long fib2 = 1;
  long result = 0;

  {
    timer Timer;

    while (fib2 <= max) {
      fib_temp = fib1 + fib2;
      fib1 = fib2;
      fib2 = fib_temp;
      if (fib2 % 2 == 0) {
        result += fib2;
      }
    }
  }

  std::cout << "Result: " << result << "\n";
}
