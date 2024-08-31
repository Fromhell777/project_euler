#include "timer.hpp"

#include <cstddef>
#include <cstdint>
#include <iostream>
#include <string>
#include <algorithm>
#include <bitset>

bool check_palindrome(const std::string number_str) {
  bool is_palindrome = true;
  for (std::size_t i = 0; i < number_str.size() / 2; ++i) {
    if (number_str[i] != number_str[number_str.size() - 1 - i]) {
      is_palindrome = false;
    }
  }

  return is_palindrome;
}

long find_double_base_palindromes(const unsigned long max) {
  long sum = 0;
  for (unsigned long i = 1; i < max; i += 2){
    std::bitset<20> number_bin(i);
    std::string number_bin_str = number_bin.to_string();
    int start_position = std::distance(std::begin(number_bin_str),
                                       std::find(std::begin(number_bin_str),
                                                 std::end(number_bin_str), '1'));
    number_bin_str = number_bin_str.substr(start_position,
                                           number_bin_str.size()); // overflow is catched
    if (check_palindrome(std::to_string(i)) && check_palindrome(number_bin_str)) {
      sum += i;
    }
  }

  return sum;
}

int main () {

  const unsigned long max = 1'000'000;
  long result;

  {
    timer Timer;

    result = find_double_base_palindromes(max);
  }

  std::cout << "Result: " << result << "\n";
}
