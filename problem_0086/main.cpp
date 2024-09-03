#include "timer.hpp"

#include <cstddef>
#include <cstdint>
#include <iostream>
#include <vector>

long find_cuboid_routes(const unsigned long limit,
                        const unsigned long max_length) {
  std::vector<std::pair<long, long> > triples = {std::make_pair(2, 1)};
  std::vector<unsigned long> cuboids(max_length, 0);
  while (not triples.empty()) {
    std::pair<unsigned long, unsigned long> triple = triples.back();
    triples.pop_back();
    const unsigned long m = triple.first;
    const unsigned long n = triple.second;
    const unsigned long a = m * m - n * n;
    const unsigned long b = 2 * m * n;
    const unsigned long c = m * m + n * n;
    if (a < max_length || b < max_length) {
      triples.emplace_back(2 * m - n, m);
      triples.emplace_back(2 * m + n, m);
      triples.emplace_back(m + 2 * n, n);
    }

    auto const count_integer_lengths = [&](const unsigned long a,
                                           const unsigned long b) {
      if (a < max_length && a >= (b + 1) / 2) {
        unsigned long integer_lengths = b / 2;
        if (a <= b) integer_lengths = integer_lengths - (b - a) + 1;
        cuboids[a] += integer_lengths;
      }
    };

    unsigned long ak = a;
    unsigned long bk = b;
    unsigned long ck = c;
    while (ak < max_length || bk < max_length) {
      count_integer_lengths(ak, bk);
      count_integer_lengths(bk, ak);
      ak += a;
      bk += b;
      ck += c;
    }
  }

  unsigned long sum = 0;
  for (std::size_t i = 0; i < cuboids.size(); ++i) {
    sum += cuboids[i];
    if (sum > limit) return i;
  }

  return -1;
}

int main () {

  constexpr unsigned long limit = 1'000'000;
  constexpr unsigned long max_length = 2'000; // chosen large enough
  long result;

  {
    timer Timer;

    result = find_cuboid_routes(limit, max_length);
  }

  std::cout << "Result: " << result << "\n";
}
