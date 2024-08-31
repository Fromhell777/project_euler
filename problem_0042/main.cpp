#include "timer.hpp"

#include <cstddef>
#include <cstdint>
#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <fstream>
#include <numeric>

void read_words(const std::string filename, std::vector<std::string> &words) {
  std::string words_string;
  std::ifstream input_file_stream(filename);
  std::getline(input_file_stream, words_string);
  std::istringstream line_stream(words_string);
  for (std::string line; std::getline(line_stream, line, ','); ) {
    words.emplace_back(line.substr(1, line.size() - 2));
  }
}

long find_triangle_words(std::vector<std::string> &words) {
  long total = 0;
  for (auto const & word : words) {
    double sum = std::accumulate(std::begin(word), std::end(word), 0ull);
    sum -= word.size() * ('A' - 1);
    sum = std::sqrt(1 + 8 * sum);
    if (std::floor(sum) == sum && static_cast<int>(sum) % 2 == 1) {
      ++total;
    }
  }

  return total;
}

int main () {

  const std::string filename = "words.txt";
  std::vector<std::string> words = {};
  long result;

  {
    timer Timer;

    read_words(filename, words);
    result = find_triangle_words(words);
  }

  std::cout << "Result: " << result << "\n";
}
