#include "timer.hpp"

#include <cstddef>
#include <cstdint>
#include <iostream>
#include <vector>
#include <array>
#include <algorithm>

long find_odd_period_square_roots1(const unsigned long limit) {
  long result = 0;
  unsigned long power = 4;
  long first_fraction_term = 1;
  for (unsigned long i = 2; i <= limit; ++i) {
    if (i == power) {
      ++first_fraction_term;
      power += (first_fraction_term << 1) + 1;
    } else {
      long denominator = 1;
      long numerator = first_fraction_term;
      bool odd = false;
      do {
        odd = not odd;
        denominator = (i - numerator * numerator) / denominator;
        numerator = first_fraction_term -
                    ((first_fraction_term + numerator) % denominator);
      } while (numerator != first_fraction_term || denominator != 1);

      // assume the cycle alwayse repeats after only 1 term
      if (odd) {
        ++result;
      }
    }
  }

  return result;
}

long find_odd_period_square_roots2(const unsigned long limit) {
  long result = 0;
  std::vector<std::array<long, 2> > combinations;
  unsigned long power = 4;
  long starting_numerator = 1;
  for (unsigned long i = 2; i <= limit; ++i) {
    if (i == power) {
      ++starting_numerator;
      power = (starting_numerator + 1) * (starting_numerator + 1);
    } else {
      combinations = {};
      long denominator = 1;
      long numerator = - starting_numerator;
      auto repeated_combination = std::end(combinations);
      std::array<long, 2> combination = {numerator, denominator};
      while (repeated_combination == std::end(combinations)) {
        combinations.push_back(combination);
        denominator = (i - (numerator * numerator)) / denominator;
        numerator = ((starting_numerator - numerator) % denominator) - starting_numerator;
        combination = {numerator, denominator};
        repeated_combination = std::find(std::begin(combinations),
                                         std::end(combinations),
                                         combination);
      }

      if (std::distance(repeated_combination, std::end(combinations)) % 2 == 1) {
        ++result;
      }
    }
  }

  return result;
}

int main () {

  const unsigned long limit = 10000;
  long result;

  {
    timer Timer;

    result = find_odd_period_square_roots1(limit);
  }

  std::cout << "Result: " << result << "\n";
}
