#include "timer.hpp"

#include <cstddef>
#include <cstdint>
#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <algorithm>
#include <cmath>

void extract_passcodes(std::string filename,
                       std::vector<std::vector<unsigned long> > & passcodes) {
  std::ifstream input_file_stream(filename);
  for (std::string line; std::getline(input_file_stream, line); ) {
    passcodes.emplace_back(std::initializer_list<unsigned long>{
                           static_cast<unsigned long>(line[0] - '0'),
                           static_cast<unsigned long>(line[1] - '0'),
                           static_cast<unsigned long>(line[2] - '0')});
  }
}

long derivate_passcode(std::vector<std::vector<unsigned long> > & passcodes) {
  std::vector<unsigned long> solution = {0, 1, 2, 3, 6, 7, 8, 9};
  do {
    bool done = true;
    for (auto & passcode : passcodes) {
      auto result1 = std::find(std::begin(solution), std::end(solution),
                               passcode[0]);
      auto result2 = std::find(result1, std::end(solution),
                               passcode[1]);
      if (result2 == std::end(solution)) {
        done = false;
        break;
      }
      auto result3 = std::find(result2, std::end(solution),
                               passcode[2]);
      if (result3 == std::end(solution)) {
        done = false;
        break;
      }
    }

    if (done == true) {
      long result = 0;
      for (std::size_t i = 0; i < solution.size(); ++i) {
        result += std::pow(10, solution.size() - i - 1) * solution[i];
      }
      return result;
    }
  } while (std::next_permutation(std::begin(solution), std::end(solution)));

  return -1;
}

int main () {

  const std::string filename = "keylog.txt";
  std::vector<std::vector<unsigned long> > passcodes;
  long result;

  {
    timer Timer;

    extract_passcodes(filename, passcodes);
    result = derivate_passcode(passcodes);
  }

  std::cout << "Result: " << result << "\n";
}
