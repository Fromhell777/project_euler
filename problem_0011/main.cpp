#include "timer.hpp"

#include <cstddef>
#include <cstdint>
#include <iostream>

long find_largest_product(size_t numbers, size_t width, size_t height, int **number) {
  long result = 1;
  long temp_result = result;
  size_t zero_present = 0;

  // horizontal
  for (size_t i = 0; i < height; ++i) {
    for (size_t j = 0; j < numbers; ++j) {
      if (number[i][j] != 0) {
        temp_result *= number[i][j];
      } else {
        zero_present = j;
        temp_result = 1;
      }
    }

    for (size_t j = numbers; j < width; ++j) {
      if (number[i][j - numbers] != 0) {
        temp_result /= number[i][j - numbers];
        if (zero_present != 0) {
          --zero_present;
        }
      }

      if (number[i][j] != 0) {
        temp_result *= number[i][j];
      } else {
        zero_present = numbers - 1;
      }

      if (temp_result > result && zero_present == 0) {
        result = temp_result;
      }
    }
    temp_result = 1;
    zero_present = 0;
  }

  // vertical
  for (size_t i = 0; i < width; ++i) {
    for (size_t j = 0; j < numbers; ++j) {
      if (number[j][i] != 0) {
        temp_result *= number[j][i];
      } else {
        zero_present = j;
        temp_result = 1;
      }
    }

    for (size_t j = numbers; j < height; ++j) {
      if (number[j - numbers][i] != 0) {
        temp_result /= number[j - numbers][i];
        if (zero_present != 0) {
          --zero_present;
        }
      }

      if (number[j][i] != 0) {
        temp_result *= number[j][i];
      } else {
        zero_present = numbers - 1;
      }

      if (temp_result > result && zero_present == 0) {
        result = temp_result;
      }
    }
    temp_result = 1;
    zero_present = 0;
  }

  // diagonal right upper
  for (size_t i = 0; i < width - numbers + 1; ++i) {
    for (size_t j = 0; j < numbers; ++j) {
      if (number[j][j + i] != 0) {
        temp_result *= number[j][j + i];
      } else {
        zero_present = j;
        temp_result = 1;
      }
    }

    for (size_t j = numbers; j < height - i; ++j) {
      if (number[j - numbers][j - numbers + i] != 0) {
        temp_result /= number[j - numbers][j - numbers + i];
        if (zero_present != 0) {
          --zero_present;
        }
      }

      if (number[j][j + i] != 0) {
        temp_result *= number[j][j + i];
      } else {
        zero_present = numbers - 1;
      }

      if (temp_result > result && zero_present == 0) {
        result = temp_result;
      }
    }
    temp_result = 1;
    zero_present = 0;
  }

  // diagonal right lower
  for (size_t i = 0; i < width - numbers + 1; ++i) {
    for (size_t j = 0; j < numbers; ++j) {
      if (number[j + i][j] != 0) {
        temp_result *= number[j + i][j];
      } else {
        zero_present = j;
        temp_result = 1;
      }
    }

    for (size_t j = numbers; j < height - i; ++j) {
      if (number[j - numbers + i][j - numbers] != 0) {
        temp_result /= number[j - numbers + i][j - numbers];
        if (zero_present != 0) {
          --zero_present;
        }
      }

      if (number[j + i][j] != 0) {
        temp_result *= number[j + i][j];
      } else {
        zero_present = numbers - 1;
      }

      if (temp_result > result && zero_present == 0) {
        result = temp_result;
      }
    }
    temp_result = 1;
    zero_present = 0;
  }

  // diagonal left upper
  for (size_t i = 0; i < width - numbers + 1; ++i) {
    for (size_t j = 0; j < numbers; ++j) {
      if (number[j][width - j - i] != 0) {
        temp_result *= number[j][width - j - i];
      } else {
        zero_present = j;
        temp_result = 1;
      }
    }

    for (size_t j = numbers; j < height - i; ++j) {
      if (number[j - numbers][width - j + numbers - i] != 0) {
        temp_result /= number[j - numbers][width - j + numbers - i];
        if (zero_present != 0) {
          --zero_present;
        }
      }

      if (number[j][width - j - i] != 0) {
        temp_result *= number[j][width - j - i];
      } else {
        zero_present = numbers - 1;
      }

      if (temp_result > result && zero_present == 0) {
        result = temp_result;
      }
    }
    temp_result = 1;
    zero_present = 0;
  }

  // diagonal left lower
  for (size_t i = 0; i < width - numbers + 1; ++i) {
    for (size_t j = 0; j < numbers; ++j) {
      if (number[j + i][width - j] != 0) {
        temp_result *= number[j + i][width - j];
      } else {
        zero_present = j;
        temp_result = 1;
      }
    }

    for (size_t j = numbers; j < height - i; ++j) {
      if (number[j - numbers + i][width - j + numbers] != 0) {
        temp_result /= number[j - numbers + i][width - j + numbers];
        if (zero_present != 0) {
          --zero_present;
        }
      }

      if (number[j + i][width - j] != 0) {
        temp_result *= number[j + i][width - j];
      } else {
        zero_present = numbers - 1;
      }

      if (temp_result > result && zero_present == 0) {
        result = temp_result;
      }
    }
    temp_result = 1;
    zero_present = 0;
  }

  return result;
}

int main () {

  int numbers = 4;
  const int gridsize = 20;
  int **grid;
  grid = new int *[gridsize];
  for(int i = 0; i < gridsize; i++)
    grid[i] = new int[gridsize];
  int values_00[gridsize] = { 8,  2, 22, 97, 38, 15,  0, 40,  0, 75,  4,  5,  7, 78, 52, 12, 50, 77, 91,  8};
  int values_01[gridsize] = {49, 49, 99, 40, 17, 81, 18, 57, 60, 87, 17, 40, 98, 43, 69, 48,  4, 56, 62,  0};
  int values_02[gridsize] = {81, 49, 31, 73, 55, 79, 14, 29, 93, 71, 40, 67, 53, 88, 30,  3, 49, 13, 36, 65};
  int values_03[gridsize] = {52, 70, 95, 23,  4, 60, 11, 42, 69, 24, 68, 56,  1, 32, 56, 71, 37,  2, 36, 91};
  int values_04[gridsize] = {22, 31, 16, 71, 51, 67, 63, 89, 41, 92, 36, 54, 22, 40, 40, 28, 66, 33, 13, 80};
  int values_05[gridsize] = {24, 47, 32, 60, 99,  3, 45,  2, 44, 75, 33, 53, 78, 36, 84, 20, 35, 17, 12, 50};
  int values_06[gridsize] = {32, 98, 81, 28, 64, 23, 67, 10, 26, 38, 40, 67, 59, 54, 70, 66, 18, 38, 64, 70};
  int values_07[gridsize] = {67, 26, 20, 68,  2, 62, 12, 20, 95, 63, 94, 39, 63,  8, 40, 91, 66, 49, 94, 21};
  int values_08[gridsize] = {24, 55, 58,  5, 66, 73, 99, 26, 97, 17, 78, 78, 96, 83, 14, 88, 34, 89, 63, 72};
  int values_09[gridsize] = {21, 36, 23,  9, 75,  0, 76, 44, 20, 45, 35, 14,  0, 61, 33, 97, 34, 31, 33, 95};
  int values_10[gridsize] = {78, 17, 53, 28, 22, 75, 31, 67, 15, 94,  3, 80,  4, 62, 16, 14,  9, 53, 56, 92};
  int values_11[gridsize] = {16, 39,  5, 42, 96, 35, 31, 47, 55, 58, 88, 24,  0, 17, 54, 24, 36, 29, 85, 57};
  int values_12[gridsize] = {86, 56,  0, 48, 35, 71, 89,  7,  5, 44, 44, 37, 44, 60, 21, 58, 51, 54, 17, 58};
  int values_13[gridsize] = {19, 80, 81, 68,  5, 94, 47, 69, 28, 73, 92, 13, 86, 52, 17, 77,  4, 89, 55, 40};
  int values_14[gridsize] = { 4, 52,  8, 83, 97, 35, 99, 16,  7, 97, 57, 32, 16, 26, 26, 79, 33, 27, 98, 66};
  int values_15[gridsize] = {88, 36, 68, 87, 57, 62, 20, 72,  3, 46, 33, 67, 46, 55, 12, 32, 63, 93, 53, 69};
  int values_16[gridsize] = { 4, 42, 16, 73, 38, 25, 39, 11, 24, 94, 72, 18,  8, 46, 29, 32, 40, 62, 76, 36};
  int values_17[gridsize] = {20, 69, 36, 41, 72, 30, 23, 88, 34, 62, 99, 69, 82, 67, 59, 85, 74,  4, 36, 16};
  int values_18[gridsize] = {20, 73, 35, 29, 78, 31, 90,  1, 74, 31, 49, 71, 48, 86, 81, 16, 23, 57,  5, 54};
  int values_19[gridsize] = { 1, 70, 54, 71, 83, 51, 54, 69, 16, 92, 33, 48, 61, 43, 52,  1, 89, 19, 67, 48};
  grid[0] = values_00;
  grid[1] = values_01;
  grid[2] = values_02;
  grid[3] = values_03;
  grid[4] = values_04;
  grid[5] = values_05;
  grid[6] = values_06;
  grid[7] = values_07;
  grid[8] = values_08;
  grid[9] = values_09;
  grid[10] = values_10;
  grid[11] = values_11;
  grid[12] = values_12;
  grid[13] = values_13;
  grid[14] = values_14;
  grid[15] = values_15;
  grid[16] = values_16;
  grid[17] = values_17;
  grid[18] = values_18;
  grid[19] = values_19;
  long result;

  {
    timer Timer;

    result = find_largest_product(numbers, gridsize, gridsize, grid);
  }

  std::cout << "Result: " << result << "\n";
}
