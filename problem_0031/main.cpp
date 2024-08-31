#include "timer.hpp"

#include <cstddef>
#include <cstdint>
#include <iostream>
#include <vector>

long long find_combinations(std::vector<long> numbers, long max) {
  while (numbers.empty() == false && max < numbers.back()) {
    numbers.pop_back();
  }

  if (numbers.empty()) {
    return 1;
  }

  std::vector<long> new_numbers = numbers;
  new_numbers.pop_back();
  return find_combinations(numbers, max - numbers.back()) +
         find_combinations(new_numbers, max);
}

int main () {

  const long max = 200;
  std::vector<long> numbers = {1, 2, 5, 10, 20, 50, 100, 200};
  long long result;

  {
    timer Timer;

    numbers.erase(std::begin(numbers)); // the 1 must be omitted
    result = find_combinations(numbers, max);
  }

  std::cout << "Result: " << result << "\n";
}
