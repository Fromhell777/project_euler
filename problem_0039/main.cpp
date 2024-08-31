#include "timer.hpp"

#include <cstddef>
#include <cstdint>
#include <iostream>
#include <vector>
#include <utility>

long find_maximum_perimeters(const long max_perimeter) {
  std::vector<std::pair<long, long> > triples = {std::make_pair(2, 1)};
  std::vector<long> perimeters(max_perimeter + 1);
  while (not triples.empty()) {
    std::pair<long, long> triple = triples[triples.size() - 1];
    triples.pop_back();
    long m = triple.first;
    long n = triple.second;
    long perimeter = 2 * m * (m + n);
    if (perimeter <= max_perimeter) {
      triples.emplace_back(2 * m - n, m);
      triples.emplace_back(2 * m + n, m);
      triples.emplace_back(m + 2 * n, n);
    }

    long k_times_perimeter = perimeter;
    while (k_times_perimeter <= max_perimeter) {
      ++perimeters[k_times_perimeter];
      k_times_perimeter += perimeter;
    }
  }

  long result = 0;
  long max_perimeter_occurrence = 0;
  for (std::size_t i = 0; i < perimeters.size(); ++i) {
    if (perimeters[i] >= max_perimeter_occurrence) {
      max_perimeter_occurrence = perimeters[i];
      result = i;
    }
  }

  return result;
}

int main () {

  const long max_perimeter = 1'000;
  long result;

  {
    timer Timer;

    result = find_maximum_perimeters(max_perimeter);
  }

  std::cout << "Result: " << result << "\n";
}
