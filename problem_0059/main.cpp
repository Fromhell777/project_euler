#include "timer.hpp"

#include <cstddef>
#include <cstdint>
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>

long find_substring_occurences(std::vector<unsigned long> base_string,
                               std::vector<unsigned long> substring) {
  long occurrences = 0;
  auto start = std::begin(base_string);

  while ((start = std::search(start, std::end(base_string),
                              std::begin(substring), std::end(substring))) !=
         std::end(base_string)) {
      ++occurrences;
      start += substring.size();
  }

  return occurrences;
}

long find_decrypted_ascii_sum(std::string filename) {
  std::ifstream input_file_stream(filename);
  std::string text;
  std::getline(input_file_stream, text);
  std::istringstream line_stream(text);
  std::vector<unsigned long> text_characters;
  for (std::string line; std::getline(line_stream, line, ','); ) {
    text_characters.emplace_back(std::stoul(line));
  }

  long max_occurences = 0;
  long most_likely_sum = 0;
  for (long key1 = 97; key1 < 123; ++key1) {
    // starting letters if between some relevant characters
    if ((text_characters[0] xor key1) > 32 &&
        (text_characters[0] xor key1) < 123) {
      for (long key2 = 97; key2 < 123; ++key2) {
        for (long key3 = 97; key3 < 123; ++key3) {
          std::vector<unsigned long> decrypted_text;
          long decrypted_character = 0;
          long ascii_sum = 0;
          for (std::size_t i = 0; i < text_characters.size(); ++i) {
            if (i % 3 == 0) {
              decrypted_character = text_characters[i] xor key1;
              decrypted_text.emplace_back(decrypted_character);
              ascii_sum += decrypted_character;
            } else if (i % 3 == 1) {
              decrypted_character = text_characters[i] xor key2;
              decrypted_text.emplace_back(decrypted_character);
              ascii_sum += decrypted_character;
            } else {
              decrypted_character = text_characters[i] xor key3;
              decrypted_text.emplace_back(decrypted_character);
              ascii_sum += decrypted_character;
            }
          }

          // // search for trigram the
          // long trigram_occurences = 0;
          // std::vector<unsigned long> trigram = {116, 104, 101}; //the
          // trigram_occurences += find_substring_occurences(decrypted_text,
          //                                                 trigram);

          // search for whitespaces
          long whitespace_occurences = 0;
          for (auto element : decrypted_text) {
            if (element == 32) {
              ++whitespace_occurences;
            }
          }

          if (whitespace_occurences > max_occurences) {
            max_occurences = whitespace_occurences;
            most_likely_sum = ascii_sum;
          }
        }
      }
    }
  }

  return most_likely_sum;
}

int main () {

  std::string filename = "cipher.txt";
  long result;

  {
    timer Timer;

    result = find_decrypted_ascii_sum(filename);
  }

  std::cout << "Result: " << result << "\n";
}

// idea:
// split into 3 columns
// get the most frequent character per column which is probably a space or e
