#include "timer.hpp"

#include <cstddef>
#include <cstdint>
#include <iostream>
#include <string>
#include <gmpxx.h>
#include <algorithm>

bool check_possible_lychrel(long max_iterations, long number) {
  mpz_class lychrel = number;
  mpz_class reverse_lychrel = lychrel;
  std::string lychrel_str = lychrel.get_str();
  std::string reverse_lychrel_str = lychrel_str;
  std::reverse(std::begin(reverse_lychrel_str), std::end(reverse_lychrel_str));
  reverse_lychrel_str.erase(0, std::min(reverse_lychrel_str.find_first_not_of('0'),
                                        reverse_lychrel_str.size()-1));
  reverse_lychrel = reverse_lychrel_str;
  lychrel += reverse_lychrel;

  for (long i = 1; i < max_iterations; ++i) {
    lychrel_str = lychrel.get_str();
    reverse_lychrel_str = lychrel_str;
    std::reverse(std::begin(reverse_lychrel_str), std::end(reverse_lychrel_str));
    reverse_lychrel_str.erase(0, std::min(reverse_lychrel_str.find_first_not_of('0'),
                                          reverse_lychrel_str.size()-1));
    if (lychrel_str == reverse_lychrel_str) {
      return false;
    }

    reverse_lychrel = reverse_lychrel_str;
    lychrel += reverse_lychrel;
  }

  return true;
}

long find_lychrel_numbers(long max, long max_iterations) {
  long result = 0;
  for (long i = 0; i < max; ++i) {
    if (check_possible_lychrel(max_iterations, i)) {
      ++result;
    }
  }

  return result;
}

int main () {

  const long max = 10000;
  const long max_iterations = 50;
  long result;

  {
    timer Timer;

    result = find_lychrel_numbers(max, max_iterations);
  }

  std::cout << "Result: " << result << "\n";
}
