#include "timer.hpp"

#include <cstddef>
#include <cstdint>
#include <iostream>
#include <vector>
#include <algorithm>

long find_unique_perimeters(const unsigned long max_perimeter) {
  std::vector<std::pair<long, long> > triples = {std::make_pair(2, 1)};
  std::vector<unsigned long> perimeters(max_perimeter + 1);
  while (not triples.empty()) {
    std::pair<long, long> triple = triples[triples.size() - 1];
    triples.pop_back();
    long m = triple.first;
    long n = triple.second;
    unsigned long perimeter = 2 * m * (m + n);
    if (perimeter <= max_perimeter) {
      triples.emplace_back(2 * m - n, m);
      triples.emplace_back(2 * m + n, m);
      triples.emplace_back(m + 2 * n, n);
    }

    unsigned long k_times_perimeter = perimeter;
    while (k_times_perimeter <= max_perimeter) {
      ++perimeters[k_times_perimeter];
      k_times_perimeter += perimeter;
    }
  }

  long result = std::count(std::begin(perimeters), std::end(perimeters), 1);

  return result;
}

int main () {

  const unsigned long max_perimeter = 1'500'000;
  long result;

  {
    timer Timer;

    result = find_unique_perimeters(max_perimeter);
  }

  std::cout << "Result: " << result << "\n";
}
