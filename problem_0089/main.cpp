#include "timer.hpp"

#include <cstddef>
#include <cstdint>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <unordered_map>

void read_file(std::string const & filename, std::vector<std::string>& roman_numerals)
{
  std::ifstream input_file_stream(filename);
  for (std::string line; std::getline(input_file_stream, line); )
    {
      roman_numerals.push_back(line);
    }
}

unsigned long minimalise_roman_numerals(std::vector<std::string> const & roman_numerals)
{
  static std::unordered_map<char, unsigned long> numerals =
    {
        { 'I', 1},
        { 'V', 5},
        { 'X', 10},
        { 'L', 50},
        { 'C', 100},
        { 'D', 500},
        { 'M', 1000},
    };

  static std::unordered_map<unsigned long, unsigned long> numeral_sizes =
    {
        { 0, 0},
        { 1, 1},
        { 2, 2},
        { 3, 3},
        { 4, 2},
        { 5, 1},
        { 6, 2},
        { 7, 3},
        { 8, 4},
        { 9, 2},
    };

  unsigned long result = 0;
  for (auto& roman_numeral : roman_numerals)
    {
      unsigned long roman_numeral_value = numerals[roman_numeral[0]];
      for (std::size_t i = 1; i < roman_numeral.size(); ++i)
        {
          roman_numeral_value += numerals[roman_numeral[i]];
          if (numerals[roman_numeral[i]] > numerals[roman_numeral[i - 1]])
            {
              roman_numeral_value -= 2 * numerals[roman_numeral[i - 1]];
            }
        }

      result += roman_numeral.size();

      result -= roman_numeral_value / 1000;
      roman_numeral_value %= 1000;

      while (roman_numeral_value)
        {
          result -= numeral_sizes[roman_numeral_value % 10];
          roman_numeral_value /= 10;
        }
    }

  return result;
}

int main ()
{
  std::string const filename = "roman.txt";
  std::vector<std::string> roman_numerals;
  long result;

  {
    timer Timer;

    read_file(filename, roman_numerals);
    result = minimalise_roman_numerals(roman_numerals);
  }

  std::cout << "Result: " << result << "\n";
}
