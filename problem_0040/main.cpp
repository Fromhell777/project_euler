#include "timer.hpp"

#include <cstddef>
#include <cstdint>
#include <iostream>
#include <vector>
#include <cmath>

long find_champernowne_product(const std::vector<long> indexes) {
  long product = 1;
  for (auto index : indexes) {
    if (index < 10) {
      product *= index;
    } else {
      long result = 0;
      long row_number = index;
      long j = 0;
      long number_count = 10;
      while (number_count <= row_number) {
        row_number -= number_count;
        result += number_count / (j + 1);
        ++j;
        number_count = (j + 1) * 9 * std::pow(10, j);
      }

      result = result + row_number / (j + 1);
      result /= std::pow(10, j - (row_number % (j + 1)));
      product *= result % 10;
    }
  }

  return product;
}

int main () {

  const std::vector<long> indexes = {1, 10, 100, 1'000, 10'000, 100'000,
                                     1'000'000};
  long result;

  {
    timer Timer;

    result = find_champernowne_product(indexes);
  }

  std::cout << "Result: " << result << "\n";
}
