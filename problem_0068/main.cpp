#include "timer.hpp"

#include <cstddef>
#include <cstdint>
#include <iostream>
#include <vector>
#include <array>
#include <string>
#include <algorithm>

std::string find_magic_5_gon_ring() {
  std::vector<int> numbers1 = {10, 9, 8, 7, 6, 5, 4, 3, 2, 1};
  for (unsigned int i = 4; i < numbers1.size(); ++i) {
    auto & number1 = numbers1[i];
    auto numbers2 = numbers1;
    numbers2.erase(std::begin(numbers2) + i);
    for (unsigned int j = 0; j < numbers2.size(); ++j) {
      auto & number2 = numbers2[j];
      if (number2 != 10) {
        auto numbers3 = numbers2;
        numbers3.erase(std::begin(numbers3) + j);
        for (unsigned int k = 0; k < numbers3.size(); ++k) {
          auto & number3 = numbers3[k];
          if (number3 != 10) {
            int sum = number1 + number2 + number3;
            auto numbers4 = numbers3;
            numbers4.erase(std::begin(numbers4) + k);
            for (unsigned int l = 0; l < numbers4.size(); ++l) {
              auto & number4 = numbers4[l];
              if (number4 > number1) {
                auto numbers5 = numbers4;
                numbers5.erase(std::begin(numbers5) + l);
                int number5 = sum - number4 - number3;
                auto it_number5 = std::find(std::begin(numbers5),
                                            std::end(numbers5), number5);
                if (number5 != 10 && it_number5 != std::end(numbers5)) {
                  numbers5.erase(it_number5);
                  for (unsigned int m = 0; m < numbers5.size(); ++m) {
                    auto & number6 = numbers5[m];
                    if (number6 > number1) {
                      auto numbers7 = numbers5;
                      numbers7.erase(std::begin(numbers7) + m);
                      int number7 = sum - number6 - number5;
                      auto it_number7 = std::find(std::begin(numbers7),
                                                  std::end(numbers7), number7);
                      if (number7 != 10 && it_number7 != std::end(numbers7)) {
                        numbers7.erase(it_number7);
                        for (unsigned int n = 0; n < numbers7.size(); ++n) {
                          auto & number8 = numbers7[n];
                          if (number8 > number1) {
                            auto numbers9 = numbers7;
                            numbers9.erase(std::begin(numbers9) + n);
                            int number9 = sum - number8 - number7;
                            auto it_number9 = std::find(std::begin(numbers9),
                                                        std::end(numbers9),
                                                        number9);
                            if (number9 != 10 &&
                                it_number9 != std::end(numbers9)) {
                              numbers9.erase(it_number9);
                              int number10 = sum - number9 - number2;
                              if (number10 > number1 &&
                                  numbers9[0] == number10) {
                                return std::to_string(number1) +
                                       std::to_string(number2) +
                                       std::to_string(number3) +
                                       std::to_string(number4) +
                                       std::to_string(number3) +
                                       std::to_string(number5) +
                                       std::to_string(number6) +
                                       std::to_string(number5) +
                                       std::to_string(number7) +
                                       std::to_string(number8) +
                                       std::to_string(number7) +
                                       std::to_string(number9) +
                                       std::to_string(number10) +
                                       std::to_string(number9) +
                                       std::to_string(number2);
                              }
                            }
                          }
                        }
                      }
                    }
                  }
                }
              }
            }
          }
        }
      }
    }
  }

  return "";
}

std::string find_magic_5_gon_ring2() {
  std::array<bool, 11> numbers = {false, true, true, true, true,
                                  true, true, true, true, true, true};
  for (unsigned int number1 = 6; number1 > 0; --number1) {
    numbers[number1] = false;
    for (unsigned int number2 = 9; number2 > 0; --number2) {
      if (numbers[number2] == true) {
        numbers[number2] = false;
        for (unsigned int number3 = 9; number3 > 0; --number3) {
          if (numbers[number3] == true) {
            numbers[number3] = false;
            int sum = number1 + number2 + number3;
            for (unsigned int number4 = 10; number4 > number1; --number4) {
              if (numbers[number4] == true) {
                numbers[number4] = false;
                unsigned int number5 = sum - number4 - number3;
                if (number5 < 10 && number5 > 0 && numbers[number5] == true) {
                  numbers[number5] = false;
                  for (unsigned int number6 = 10; number6 > number1; --number6) {
                    if (numbers[number6] == true) {
                      numbers[number6] = false;
                      unsigned int number7 = sum - number6 - number5;
                      if (number7 < 10 && number7 > 0 && numbers[number7] == true) {
                        numbers[number7] = false;
                        for (unsigned int number8 = 10; number8 > number1; --number8) {
                          if (numbers[number8] == true) {
                            numbers[number8] = false;
                            unsigned int number9 = sum - number8 - number7;
                            if (number9 < 10 && number9 > 0 && numbers[number9] == true) {
                              numbers[number9] = false;
                              unsigned int number10 = sum - number9 - number2;
                              if (number10 > number1 && number10 > 0 &&
                                  numbers[number10] == true) {
                                return std::to_string(number1) +
                                       std::to_string(number2) +
                                       std::to_string(number3) +
                                       std::to_string(number4) +
                                       std::to_string(number3) +
                                       std::to_string(number5) +
                                       std::to_string(number6) +
                                       std::to_string(number5) +
                                       std::to_string(number7) +
                                       std::to_string(number8) +
                                       std::to_string(number7) +
                                       std::to_string(number9) +
                                       std::to_string(number10) +
                                       std::to_string(number9) +
                                       std::to_string(number2);
                              }
                              numbers[number9] = true;
                            }
                            numbers[number8] = true;
                          }
                        }
                        numbers[number7] = true;
                      }
                      numbers[number6] = true;
                    }
                  }
                  numbers[number5] = true;
                }
                numbers[number4] = true;
              }
            }
            numbers[number3] = true;
          }
        }
        numbers[number2] = true;
      }
    }
    numbers[number1] = true;
  }

  return "";
}

int main () {

  std::string result;

  {
    timer Timer;

    result = find_magic_5_gon_ring2();
  }

  std::cout << "Result: " << result << "\n";
}
