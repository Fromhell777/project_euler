#include "timer.hpp"

#include <cstddef>
#include <cstdint>
#include <iostream>
#include <vector>
#include <map>

void find_prime_factors(int value, std::vector<std::pair<int, int>> &prime_factors) {
  int divisor = 5;
  int largestPrimeFactor;
  int exponent = 0;

  auto const find_factors = [&](int const divisor) {
    if(value % divisor == 0) {
      largestPrimeFactor = divisor;
      exponent = 0;
      while(value % divisor == 0) {
        ++exponent;
        value /= divisor;
      }
      prime_factors.emplace_back(largestPrimeFactor, exponent);
    }
  };

  find_factors(2);
  find_factors(3);

  while(divisor <= value )
  {
    find_factors(divisor);
    divisor += 2;
    find_factors(divisor);
    divisor += 4;
  }
}

void find_divisors(int n, int i, long &sum, std::vector<std::pair<int, int>> &factors) {
  for (size_t j = i; j < factors.size(); ++j) {
    int x = factors[j].first * n;
    for (int k = 0; k < factors[j].second; ++k) {
      sum += x;
      find_divisors(x, j + 1, sum, factors);
      x *= factors[j].first;
    }
  }
}

long find_amicable_numbers(int max) {
  long sum = 0;
  for (int i = 2; i <= max; ++i) {
    std::vector<std::pair<int, int>> prime_factors;
    find_prime_factors(i, prime_factors);

    long sum_divisors = 1; // for the division by 1
    find_divisors(1, 0, sum_divisors, prime_factors);

    prime_factors.clear();
    find_prime_factors(sum_divisors - i, prime_factors);

    long sum_divisors_amicable = 1;
    find_divisors(1, 0, sum_divisors_amicable, prime_factors);

    if (sum_divisors_amicable - sum_divisors == 0 && sum_divisors - i != i) {
      sum += i;
      // std::cout << "Amicable number: " << i << "\n";
    }
  }

  return sum;
}

int main () {

  int const max = 10000;
  long result;

  {
    timer Timer;

    result = find_amicable_numbers(max);
  }

  std::cout << "Result: " << result << "\n";
}
