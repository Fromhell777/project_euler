#include "timer.hpp"

#include <cstddef>
#include <cstdint>
#include <iostream>
#include <vector>
#include <algorithm>

std::vector<std::vector<unsigned int> > check_cycle(std::vector<std::vector<unsigned int> > &numbers,
                                                    std::vector<std::vector<unsigned int> > &combinations) {
  std::vector<std::vector<unsigned int> > result;
  for (auto element : numbers) {
    for (auto combination : combinations) {
      if (element[0] == combination.back()) {
        result.push_back({});
        result.back().reserve(combination.size() + element.size());
        result.back().insert(std::end(result.back()), std::begin(combination),
                             std::end(combination));
        result.back().insert(std::end(result.back()), std::begin(element),
                             std::end(element));
      }
      if (element[1] == combination[0]) {
        result.push_back({});
        result.back().reserve(combination.size() + element.size());
        result.back().insert(std::end(result.back()), std::begin(element),
                             std::end(element));
        result.back().insert(std::end(result.back()), std::begin(combination),
                             std::end(combination));
      }
    }
  }

  return result;
}

long find_cyclical_figurate_numbers() {
  // contains numbers triangle to octagonal
  std::array<std::vector<std::vector<unsigned int> >, 6> all_numbers;
  for (unsigned int n = 19; n < 141; ++n) {
    unsigned int triangle_number = (n * n + n) / 2;
    unsigned int square_number = n * n;
    unsigned int pentagonal_number = (3 * n * n - n) / 2;
    unsigned int hexagonal_number = 2 * n * n - n;
    unsigned int heptagonal_number = (5 * n * n - 3 * n) / 2;
    unsigned int octagonal_number = 3 * n * n - 2 * n;

    if (triangle_number < 10'000 && triangle_number > 1000) {
      // triangle numbers
      all_numbers[0].emplace_back(std::initializer_list<unsigned int>{
                                  triangle_number / 100, triangle_number % 100});
    }

    if (square_number < 10'000 && square_number > 1000) {
      // square numbers
      all_numbers[1].emplace_back(std::initializer_list<unsigned int>{
                                  square_number / 100, square_number % 100});
    }

    if (pentagonal_number < 10'000 && pentagonal_number > 1000) {
      // pentagonal numbers
      all_numbers[2].emplace_back(std::initializer_list<unsigned int>{
                                  pentagonal_number / 100, pentagonal_number % 100});
    }

    if (hexagonal_number < 10'000 && hexagonal_number > 1000) {
      // hexagonal numbers
      all_numbers[3].emplace_back(std::initializer_list<unsigned int>{
                                  hexagonal_number / 100, hexagonal_number % 100});
    }

    if (heptagonal_number < 10'000 && heptagonal_number > 1000) {
      // heptagonal numbers
      all_numbers[4].emplace_back(std::initializer_list<unsigned int>{
                                  heptagonal_number / 100, heptagonal_number % 100});
    }

    if (octagonal_number < 10'000 && octagonal_number > 1000) {
      // octagonal numbers
      all_numbers[5].emplace_back(std::initializer_list<unsigned int>{
                                  octagonal_number / 100, octagonal_number % 100});
    }
  }

  // start with triangle numbers, end with octagonal numbers
  std::vector<unsigned int> sequence = {1, 2, 3, 4};
  do {
    std::vector<std::vector<unsigned int> > combinations = all_numbers[0];
    for (auto sequence_number : sequence) {
      combinations = check_cycle(all_numbers[sequence_number], combinations);
    }

    combinations = check_cycle(all_numbers[5], combinations);

    for (auto combination : combinations) {
      bool is_unique = true;
      for (std::size_t i = 0; i < combination.size() - 3; i += 2) {
        for (std::size_t j = i + 2; j < combination.size() - 1; j += 2) {
          if (combination[i] == combination[j] &&
              combination[i + 1] == combination[j + 1]) {
            is_unique = false;
          }
        }
      }

      if (is_unique && combination[0] == combination.back()) {
        long sum = 0;
        for (std::size_t i = 0; i < combination.size() - 1; i += 2) {
          sum += combination[i] * 100;
          sum += combination[i + 1];
        }

        return sum;
      }
    }

  } while (std::next_permutation(std::begin(sequence), std::end(sequence)));

  return -1;
}

int main () {

  long result;

  {
    timer Timer;

    result = find_cyclical_figurate_numbers();
  }

  std::cout << "Result: " << result << "\n";
}
