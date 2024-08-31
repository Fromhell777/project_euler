#include "timer.hpp"

#include <cstddef>
#include <cstdint>
#include <iostream>
#include <map>

long find_recurring_cycle(long value) {
  std::map<long, long> cycle_values;
  long decimal_place = 0;
  long dividend = 10;
  // std::cout << "division result: 0,";
  while (dividend < value) {
    // std::cout << "0";
    ++decimal_place;
    dividend *= 10;
  }

  while (cycle_values.find(dividend) == cycle_values.end()) {
    cycle_values.emplace(dividend, decimal_place);

    // std::cout << dividend / value;

    dividend = (dividend % value) * 10;
    ++decimal_place;

    while (dividend != 0 && dividend < value) {
      // std::cout << "0";
      ++decimal_place;
      dividend *= 10;
    }
  }

  // std::cout << "\n";
  return decimal_place - cycle_values.find(dividend)->second;
}

long find_max_recurring_cycle(long max) {
  long max_recurring_cycle_number = 0;
  long max_recurring_cycle = 0;
  long current_recurring_cycle = 0;
  for (long i = 2; i < max; ++i) {
    // std::cout << "number: " << i << "\n";
    current_recurring_cycle = find_recurring_cycle(i);
    if (current_recurring_cycle >= max_recurring_cycle) {
      max_recurring_cycle = current_recurring_cycle;
      max_recurring_cycle_number = i;
      // std::cout << "current max number: " << max_recurring_cycle_number << "\n";
      // std::cout << "current max: " << max_recurring_cycle << "\n";
    }
  }

  return max_recurring_cycle_number;
}

int main () {

  long result;

  {
    timer Timer;

    result = find_max_recurring_cycle(1000);
  }

  std::cout << "Result: " << result << "\n";
}

// advanced method:
// - first calculate all the prime numbers up to the maximum
// - second calculate the longest recurring cycle of those primes
// - third split all the numbers in there prime factors
// - finally from each number their prime factors, calculate the least
//   common multiple of the longest recurring cycle of the prime factors
