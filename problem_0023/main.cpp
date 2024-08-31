#include "timer.hpp"

#include <cstddef>
#include <cstdint>
#include <iostream>
#include <vector>
#include <map>
#include <bitset>
#include <cmath>

void find_prime_factors(int value, std::vector<std::pair<int, int>> &prime_factors) {
  int divisor = 5;
  int largestPrimeFactor;
  int exponent = 0;
  int max_value = std::sqrt(value);

  auto const find_factors = [&](int const divisor) {
    if(value % divisor == 0) {
      largestPrimeFactor = divisor;
      exponent = 0;
      while(value % divisor == 0) {
        ++exponent;
        value /= divisor;
      }
      prime_factors.emplace_back(largestPrimeFactor, exponent);
      max_value = std::sqrt(value);
    }
  };

  find_factors(2);
  find_factors(3);

  while (divisor <= max_value ) {
    find_factors(divisor);
    divisor += 2;
    find_factors(divisor);
    divisor += 4;
  }

  if (value > 1) {
    prime_factors.emplace_back(value, 1);
  }
}

void find_divisors(int n, int i, unsigned long &sum, std::vector<std::pair<int, int>> &factors) {
  for (size_t j = i; j < factors.size(); ++j) {
    int x = factors[j].first * n;
    for (int k = 0; k < factors[j].second; ++k) {
      sum += x;
      find_divisors(x, j + 1, sum, factors);
      x *= factors[j].first;
    }
  }
}

template <size_t bitsetsize>
void find_abundant_numbers(std::bitset<bitsetsize> &abundant_numbers) {
  for (size_t i = 1; i < bitsetsize; ++i) {
    std::vector<std::pair<int, int>> prime_factors;
    find_prime_factors(i, prime_factors);

    unsigned long sum_divisors = 1; // for the division by 1
    find_divisors(1, 0, sum_divisors, prime_factors);

    if (sum_divisors - i > i) {
      abundant_numbers[i] = 1;
    }
  }
}

template <size_t bitsetsize>
bool is_non_abundant(size_t number, std::bitset<bitsetsize> &abundant_numbers) {
  for (size_t j = 1; j <= number/2; ++j) {
    if (abundant_numbers[j] == 1 && abundant_numbers[number - j] == 1) {
      return false;
    }
  }
  return true;
}

template <size_t bitsetsize>
long find_non_abundant_sum(std::bitset<bitsetsize> &abundant_numbers) {
  long sum = 0;
  for (size_t i = 1; i < bitsetsize; ++i) {
    if (is_non_abundant(i, abundant_numbers)) {
      sum += i;
    }
  }
  return sum;
}

int main () {

  const long max = 28123;
  std::bitset<max + 1> abundant_numbers;
  long result;

  {
    timer Timer;

    find_abundant_numbers(abundant_numbers);
    result = find_non_abundant_sum(abundant_numbers);
  }

  std::cout << "Result: " << result << "\n";
}
