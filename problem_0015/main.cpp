#include "timer.hpp"

#include <cstddef>
#include <cstdint>
#include <iostream>

long possible_latice_paths(long x, long y, long **cache) {
  if ((x == 0) || (y == 0)) {
    return 1;
  } else if (cache[x-1][y-1] != 0) {
    return cache[x-1][y-1];
  } else {
    cache[x-1][y-1] = possible_latice_paths(x, y - 1, cache) +
                  possible_latice_paths(x - 1, y, cache);
    return cache[x-1][y-1];
  }
  return 1;
}

int main () {

  int const grid_size = 20;
  long result;

  long **cache;
  cache = new long *[grid_size];
  for (int i = 0; i < grid_size; i++) {
    cache[i] = new long [grid_size];
    for (int j = 0; j < grid_size; j++) {
      cache[i][j] = 0;
    }
  }

  {
    timer Timer;

    // recursive
    // result = possible_latice_paths(grid_size, grid_size, cache);

    // iterative
    long nodes[grid_size + 1] = {};
    nodes[0] = 1;
    for (int i = 1; i <= grid_size; i++) {
      for (int j = 1; j < i; j++) {
        nodes[j] += nodes[j - 1];
      }
      nodes[i] = nodes[i - 1] * 2;
    }

    result = nodes[grid_size];
  }

  std::cout << "Result: " << result << "\n";
}
