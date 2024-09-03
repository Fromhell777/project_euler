#include "timer.hpp"

#include <cstddef>
#include <cstdint>
#include <iostream>
#include <vector>

long count_summations(const long number) {
  long k = -1;
  std::vector<long> pentagonal_numbers = {};
  long pentagonal_number = 1;
  while (pentagonal_number <= number) {
    pentagonal_numbers.emplace_back(pentagonal_number);
    pentagonal_number = (k * (3 * k - 1)) / 2;
    k = -k;
    if (k > 0) ++k;
  }
  pentagonal_numbers.emplace_back(pentagonal_number);

  std::vector<long> partitions = {1, 1};
  for (long i = 2; i <= number; ++i) {
    long sign = 1;
    long partition = 0;
    for (std::size_t j = 0; i - pentagonal_numbers[j] >= 0; ++j) {
      partition += sign * partitions[i - pentagonal_numbers[j]];
      if ((j % 2) == 1) sign = -sign;
    }
    partitions.emplace_back(partition);
  }

  return partitions[number] - 1; // subtract 100 itself
}

int main () {

  const unsigned long number = 100;
  long result;

  {
    timer Timer;

    result = count_summations(number);
  }

  std::cout << "Result: " << result << "\n";
}
// idea: faster solution
//
// const unsigned N = 100;
// std::array<unsigned, N + 1> P = { 0 };
// P[0] = 1;
// unsigned g, k, n;
// for (n = 1; n <= N; ++n) {
//   g = 1;
//   k = 1;
//   do {
//     k++;
//     (k / 2) % 2 ? P[n] += P[n - g] : P[n] -= P[n - g];
//     g += (k % 2) ? k : k / 2;
//   } while (g <= n);
// }
