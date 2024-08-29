#include "timer.hpp"

#include <cstddef>
#include <cstdint>
#include <iostream>
#include <string>
#include <algorithm>

long find_palindrome(long max) {
  std::string s;
  std::string copy;
  unsigned long largest_palindrome = 0;

  for (std::size_t i = max; i > 0; --i) {
    for (std::size_t j = max; j >= i; --j) {
      s = std::to_string(i * j);
      copy = s;
      std::reverse(s.begin(), s.end());
      if (s == copy && i * j > largest_palindrome) {
         largest_palindrome = i * j;
      }
    }
  }
  return largest_palindrome;
}

int main () {

  long max = 999;
  long result;

  {
    timer Timer;

    result = find_palindrome(max);
  }

  std::cout << "Result: " << result << "\n";
}
