#include "timer.hpp"

#include <cstddef>
#include <cstdint>
#include <iostream>
#include <cmath>
#include <vector>
#include <fstream>
#include <string>

using matrix_t = std::vector<std::vector<long> >;

void load_triangle(std::string filename, matrix_t &triangle) {
  std::ifstream input_file_stream(filename);
  std::string triangle_string;
  while (std::getline(input_file_stream, triangle_string)) {
    triangle.push_back({});
    for (std::size_t i = 0; i < triangle_string.size(); i += 3) {
      if (triangle_string[i] == '0') {
        triangle.back().emplace_back(triangle_string[i + 1] - '0');
      } else {
        triangle.back().emplace_back(std::stoul(triangle_string.substr(i, 2)));
      }
    }

    // std::stringstream ss(triangle_string);
    // triangle.push_back({});
    // long number;
    // while (ss >> number) {
    //     triangle.back().emplace_back(number);
    // }
  }
}

long maximum_path_sum(std::size_t depth, matrix_t &triangle) {
  for (std::size_t i = 1; i < depth; ++i) {
    for (std::size_t j = 0; j <= i; ++j) {
      triangle[i][j] += std::max(triangle[i - 1][std::max((std::size_t) 0, j - 1)],
                                 triangle[i - 1][std::min(j, i - 1)]);
    }
  }

  long max = 0;
  for (const auto &element : triangle[depth - 1]) {
    max = std::max(max, element);
  }

  return max;
}
int main () {

  const int depth = 100;
  matrix_t triangle = {};
  std::string filename = "triangle.txt";
  long result;

  {
    timer Timer;

    load_triangle(filename, triangle);
    result = maximum_path_sum(depth, triangle);
  }

  std::cout << "Result: " << result << "\n";
}
