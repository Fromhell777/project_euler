#include "timer.hpp"

#include <cstddef>
#include <cstdint>
#include <iostream>
#include <vector>
#include <map>
#include <array>
#include <algorithm>

long find_cubic_permutation(const unsigned long limit) {
  // sorted number is the key, values are the number of permutations and n
  std::map<unsigned long, std::array<unsigned long, 2> > cubes;
  unsigned long times = 100'000'000; // starting value for when limit > 4
  for (unsigned long n = 345; ; ++n) {
    unsigned long number = n * n * n;
    if (number >= times) {
      times *= 10;
      cubes = {};
    }

    std::string number_str = std::to_string(number);
    std::sort(std::begin(number_str), std::end(number_str));
    unsigned long cube = std::stoul(number_str);
    auto permutation = cubes.find(cube);
    if (permutation != std::end(cubes)) {
      if (++permutation->second[0] == limit) {
        return permutation->second[1] * permutation->second[1] * permutation->second[1];
      }
    } else {
      cubes.emplace(cube, std::array<unsigned long, 2>{1, n});
    }
  }

  return -1;
}

int main () {

  const unsigned long limit = 5;
  long result;

  {
    timer Timer;

    result = find_cubic_permutation(limit);
  }

  std::cout << "Result: " << result << "\n";
}
