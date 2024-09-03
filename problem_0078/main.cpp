#include "timer.hpp"

#include <cstddef>
#include <cstdint>
#include <iostream>
#include <vector>

long count_summations(const long multiple_of) {
  std::vector<long> partitions = {1, 1};
  long i = 2;
  while (partitions.back() != 0) {
    long partition = 0;
    long pentagonal_number = 1;
    long k = 1;
    do {
      ++k;
      if ((k / 2) % 2 == 0) {
        partition -= partitions[i - pentagonal_number];
      } else {
        partition += partitions[i - pentagonal_number];
      }
      pentagonal_number += (k % 2) ? k : k / 2;
    } while (i >= pentagonal_number);

    partitions.emplace_back(partition % multiple_of);
    ++i;
  }

  return i - 1;
}

int main () {

  const unsigned long multiple_of = 1'000'000;
  long result;

  {
    timer Timer;

    result = count_summations(multiple_of);
  }

  std::cout << "Result: " << result << "\n";
}
