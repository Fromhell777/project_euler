#include "timer.hpp"

#include <cstddef>
#include <cstdint>
#include <iostream>
#include <cmath>
#include <set>

long find_distinct_powers(const int max_base, const int max_exponent) {
  std::set<double> results;
  for (int i = 2; i <= max_base; ++i) {
    for (int j = 2; j <= max_exponent; ++j) {
      results.insert(std::pow(i, j));
    }
  }

  return results.size();
}

int main () {

  const int max_base = 100;
  const int max_exponent = 100;
  long result;

  {
    timer Timer;

    result = find_distinct_powers(max_base, max_exponent);
  }

  std::cout << "Result: " << result << "\n";
}

// idea:
// count all the numbers and the "promotions" of that number. Don't count the
// number when you can "demote" it.
// "promotion" = when the exponent can be split up in prime factors
//               example: 2 ^ 8 = 2 ^ (2 ^ (2 ^ 2)) = 4 ^ 4 = ...
// "demotion" =  reverse of "promotion"
