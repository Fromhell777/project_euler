#include "timer.hpp"

#include <cstddef>
#include <cstdint>
#include <iostream>
#include <cmath>
#include <vector>

long maximum_path_sum(size_t depth, std::vector<std::vector<long>> & triangle) {
  for (size_t i = 1; i < depth; ++i) {
    for (size_t j = 0; j <= i; ++j) {
      triangle[i][j] += std::max(triangle[i - 1][std::max((size_t) 0, j - 1)],
                                 triangle[i - 1][std::min(j, i - 1)]);
    }
  }

  long max = 0;
  for (auto const element : triangle[depth - 1]) {
    max = std::max(max, element);
  }

  return max;
}

int main () {

  const int depth = 15;
  using matrix_t = std::vector<std::vector<long>>;
  matrix_t triangle = {
   {75},
   {95, 64},
   {17, 47, 82},
   {18, 35, 87, 10},
   {20,  4, 82, 47, 65},
   {19,  1, 23, 75,  3, 34},
   {88,  2, 77, 73,  7, 63, 67},
   {99, 65,  4, 28,  6, 16, 70, 92},
   {41, 41, 26, 56, 83, 40, 80, 70, 33},
   {41, 48, 72, 33, 47, 32, 37, 16, 94, 29},
   {53, 71, 44, 65, 25, 43, 91, 52, 97, 51, 14},
   {70, 11, 33, 28, 77, 73, 17, 78, 39, 68, 17, 57},
   {91, 71, 52, 38, 17, 14, 91, 43, 58, 50, 27, 29, 48},
   {63, 66,  4, 68, 89, 53, 67, 30, 73, 16, 69, 87, 40, 31},
   { 4, 62, 98, 27, 23,  9, 70, 98, 73, 93, 38, 53, 60,  4, 23}
  };

  long result;

  {
    timer Timer;

    result = maximum_path_sum(depth, triangle);
  }

  std::cout << "Result: " << result << "\n";
}
