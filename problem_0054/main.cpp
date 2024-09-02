#include "timer.hpp"
#include "evaluator.h"

#include <cstddef>
#include <cstdint>
#include <iostream>
#include <string>
#include <fstream>
#include <map>

long poker_hand_evaluator(std::string filename) {
  std::map<char, int> card_values;
  // values
  card_values.insert(std::make_pair('2', 0));
  card_values.insert(std::make_pair('3', 1));
  card_values.insert(std::make_pair('4', 2));
  card_values.insert(std::make_pair('5', 3));
  card_values.insert(std::make_pair('6', 4));
  card_values.insert(std::make_pair('7', 5));
  card_values.insert(std::make_pair('8', 6));
  card_values.insert(std::make_pair('9', 7));
  card_values.insert(std::make_pair('T', 8));
  card_values.insert(std::make_pair('J', 9));
  card_values.insert(std::make_pair('Q', 10));
  card_values.insert(std::make_pair('K', 11));
  card_values.insert(std::make_pair('A', 12));
  // suits
  card_values.insert(std::make_pair('C', 0));
  card_values.insert(std::make_pair('D', 1));
  card_values.insert(std::make_pair('H', 2));
  card_values.insert(std::make_pair('S', 3));

  std::ifstream input_stream(filename);
  long victories = 0;
  for (std::string line; std::getline(input_stream, line); ) {
    long player1_card1 = card_values[line[0]] * 4 + card_values[line[1]];
    long player1_card2 = card_values[line[3]] * 4 + card_values[line[4]];
    long player1_card3 = card_values[line[6]] * 4 + card_values[line[7]];
    long player1_card4 = card_values[line[9]] * 4 + card_values[line[10]];
    long player1_card5 = card_values[line[12]] * 4 + card_values[line[13]];
    long player2_card1 = card_values[line[15]] * 4 + card_values[line[16]];
    long player2_card2 = card_values[line[18]] * 4 + card_values[line[19]];
    long player2_card3 = card_values[line[21]] * 4 + card_values[line[22]];
    long player2_card4 = card_values[line[24]] * 4 + card_values[line[25]];
    long player2_card5 = card_values[line[27]] * 4 + card_values[line[28]];

    if (evaluate_5cards(player1_card1, player1_card2, player1_card3,
                        player1_card4, player1_card5) <
        evaluate_5cards(player2_card1, player2_card2, player2_card3,
                        player2_card4, player2_card5)) {
      ++victories;
    }
  }

  return victories;
}

int main () {

  std::string filename = "poker.txt";
  long result;

  {
    timer Timer;

    result = poker_hand_evaluator(filename);
  }

  std::cout << "Result: " << result << "\n";
}
