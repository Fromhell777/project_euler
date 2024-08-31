#include "timer.hpp"

#include <cstddef>
#include <cstdint>
#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <fstream>
#include <algorithm>

void read_names(const std::string filename, std::vector<std::string> &names) {
  std::string names_string;
  std::ifstream input_file_stream(filename);
  std::getline(input_file_stream, names_string);
  std::istringstream line_stream(names_string);
  for (std::string line; std::getline(line_stream, line, ','); ) {
    names.emplace_back(line.substr(1, line.size() - 2));
  }

  std::sort(names.begin(), names.end());
}

long find_names_score(std::vector<std::string> &names) {
  long sum = 0;
  for (size_t i = 0; i < names.size(); ++i) {
    long name_score = 0;
    for (size_t j = 0; j < names[i].size(); ++j) {
      name_score += names[i][j] - 'A' + 1;
    }
    sum += name_score * (i + 1);
  }
  return sum;
}

int main () {

  const std::string filename = "names.txt";
  std::vector<std::string> names = {};
  long result;

  {
    timer Timer;

    read_names(filename, names);
    result = find_names_score(names);
  }

  std::cout << "Result: " << result << "\n";
}
