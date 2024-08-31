#include "timer.hpp"

#include <cstddef>
#include <cstdint>
#include <iostream>
#include <string>

long factorial(int n) {
  return (n == 1 || n == 0) ? 1 : factorial(n - 1) * n;
}

void find_lexicographic_permutations(std::string &result,
                                     std::string digits, long number) {
  int index = number / factorial(digits.size() - 1);
  result.push_back(digits[index]);
  digits.erase(index, 1);

  if (digits.size() != 0) {
    find_lexicographic_permutations(result, digits,
                                    number % factorial(digits.size()));
  }
}

int main () {

  const long number = 999'999; // is the 1'000'000th permutation
  std::string digits("0123456789");
  std::string result;

  {
    timer Timer;

    find_lexicographic_permutations(result, digits, number);
  }

  std::cout << "Result: " << result << "\n";
}
