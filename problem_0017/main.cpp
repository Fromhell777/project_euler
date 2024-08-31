#include "timer.hpp"

#include <cstddef>
#include <cstdint>
#include <iostream>
#include <map>

// till 1000
long number_letter_count(int max) {
  std::map<int, int> letters_of_number;
  letters_of_number.insert(std::make_pair(1, 3));
  letters_of_number.insert(std::make_pair(2, 3));
  letters_of_number.insert(std::make_pair(3, 5));
  letters_of_number.insert(std::make_pair(4, 4));
  letters_of_number.insert(std::make_pair(5, 4));
  letters_of_number.insert(std::make_pair(6, 3));
  letters_of_number.insert(std::make_pair(7, 5));
  letters_of_number.insert(std::make_pair(8, 5));
  letters_of_number.insert(std::make_pair(9, 4));
  letters_of_number.insert(std::make_pair(10, 3));
  letters_of_number.insert(std::make_pair(11, 6));
  letters_of_number.insert(std::make_pair(12, 6));
  letters_of_number.insert(std::make_pair(13, 8));
  letters_of_number.insert(std::make_pair(14, 8));
  letters_of_number.insert(std::make_pair(15, 7));
  letters_of_number.insert(std::make_pair(16, 7));
  letters_of_number.insert(std::make_pair(17, 9));
  letters_of_number.insert(std::make_pair(18, 8));
  letters_of_number.insert(std::make_pair(19, 8));
  letters_of_number.insert(std::make_pair(20, 6));
  letters_of_number.insert(std::make_pair(30, 6));
  letters_of_number.insert(std::make_pair(40, 5));
  letters_of_number.insert(std::make_pair(50, 5));
  letters_of_number.insert(std::make_pair(60, 5));
  letters_of_number.insert(std::make_pair(70, 7));
  letters_of_number.insert(std::make_pair(80, 6));
  letters_of_number.insert(std::make_pair(90, 6));
  long sum = 0;
  auto search = letters_of_number.find(0);

  for (int i = 1; i <= max; ++i) {
    search = letters_of_number.find(i % 100);
    if(search != letters_of_number.end()) {
      sum += search->second;
    } else {
      search = letters_of_number.find(i % 10);
      if(search != letters_of_number.end()) {
        sum += search->second;
      }
      search = letters_of_number.find((i % 100) - (i % 10));
      if(search != letters_of_number.end()) {
        sum += search->second;
      }
    }

    if (i % 1000 >= 100 ) {
      sum += 7; // for "hunderd"
      if (i % 100 > 0) {
        sum += 3; // for "and"
      }
      search = letters_of_number.find((i / 100) % 10);
      if(search != letters_of_number.end()) {
        sum += search->second;
      }
    }

    if (i % 1000'000 >= 1000) {
      sum += 8; // for "thousand"
      search = letters_of_number.find((i / 1000) % 100);
      if(search != letters_of_number.end()) {
        sum += search->second;
      } else {
        search = letters_of_number.find(i % 10);
        if(search != letters_of_number.end()) {
          sum += search->second;
        }
        search = letters_of_number.find((i % 100) - (i % 10));
        if(search != letters_of_number.end()) {
          sum += search->second;
        }
      }
    }
  }

  return sum;
}

int main () {

  long result;

  {
    timer Timer;

    result = number_letter_count(1000);
  }

  std::cout << "Result: " << result << "\n";
}
