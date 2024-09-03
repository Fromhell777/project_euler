#include "timer.hpp"
#include "prettyprint.hpp"

#include <cstddef>
#include <cstdint>
#include <iostream>
#include <vector>
#include <unordered_set>
#include <algorithm>
#include <cmath>

std::size_t find_chain_length(std::vector<std::size_t> & numberSet) {
  std::unordered_set<double> totalExpressions;

  do {
    // First check the linear expressions
    std::unordered_set<double> expressions = {static_cast<double>(numberSet[0])};

    for (std::size_t i = 1; i < numberSet.size(); ++i) {
      std::unordered_set<double> newExpressions;

      for (auto const expression : expressions) {
        // Addition
        newExpressions.emplace(expression + numberSet[i]);

        // Subtraction
        newExpressions.emplace(expression - numberSet[i]);
        newExpressions.emplace(static_cast<double>(numberSet[i]) - expression);

        // Multiplication
        newExpressions.emplace(expression * numberSet[i]);

        // Division
        newExpressions.emplace(expression / numberSet[i]);
        if (expression != 0) {
          newExpressions.emplace(static_cast<double>(numberSet[i]) / expression);
        }
      }

      expressions = newExpressions;
    }

    totalExpressions.insert(expressions.begin(), expressions.end());

    // Check the tree expressions

    // Calculate leaf results
    std::unordered_set<double> firstExpressions;
    std::unordered_set<double> secondExpressions;
    // Addition
    firstExpressions.emplace(static_cast<double>(numberSet[0]) + numberSet[1]);
    secondExpressions.emplace(static_cast<double>(numberSet[2]) + numberSet[3]);

    // Subtraction
    firstExpressions.emplace(static_cast<double>(numberSet[0]) - numberSet[1]);
    firstExpressions.emplace(static_cast<double>(numberSet[1]) - numberSet[0]);
    secondExpressions.emplace(static_cast<double>(numberSet[2]) - numberSet[3]);
    secondExpressions.emplace(static_cast<double>(numberSet[3]) - numberSet[2]);

    // Multiplication
    firstExpressions.emplace(static_cast<double>(numberSet[0]) * numberSet[1]);
    secondExpressions.emplace(static_cast<double>(numberSet[2]) * numberSet[3]);

    // Division
    firstExpressions.emplace(static_cast<double>(numberSet[0]) / numberSet[1]);
    firstExpressions.emplace(static_cast<double>(numberSet[1]) / numberSet[0]);
    secondExpressions.emplace(static_cast<double>(numberSet[2]) / numberSet[3]);
    secondExpressions.emplace(static_cast<double>(numberSet[3]) / numberSet[2]);

    // Calculate root results
    std::unordered_set<double> newExpressions;

    for (auto const firstExpression : firstExpressions) {
      for (auto const secondExpression : secondExpressions) {
        // Addition
        newExpressions.emplace(firstExpression + secondExpression);

        // Subtraction
        newExpressions.emplace(firstExpression - secondExpression);
        newExpressions.emplace(secondExpression - firstExpression);

        // Multiplication
        newExpressions.emplace(firstExpression * secondExpression);

        // Division
        newExpressions.emplace(firstExpression / secondExpression);
        newExpressions.emplace(secondExpression / firstExpression);
      }
    }

    totalExpressions.insert(newExpressions.begin(), newExpressions.end());

  } while (std::next_permutation(numberSet.begin(), numberSet.end()));

  // Remove the floating point and negative numbers
  std::vector<std::size_t> uintExpressions;
  for (auto const expression : totalExpressions) {
    if (expression > 0.6) {
      if (std::abs(std::round(expression) - expression) <= 0.00001f) {
        uintExpressions.emplace_back(static_cast<std::size_t>(std::round(expression)));
      }
    }
  }

  std::sort(uintExpressions.begin(), uintExpressions.end());

  uintExpressions.erase(std::unique(uintExpressions.begin(),
                                    uintExpressions.end()),
                        uintExpressions.end());

  std::size_t chainLength = 0;

  for (std::size_t i = 0; i < uintExpressions.size(); ++i) {
    if (uintExpressions[i] == i + 1) {
      ++chainLength;
    } else {break;}
  }

  return chainLength;
}

int main()
{
  std::vector<std::size_t> result;

  {
    timer Timer;

    std::size_t maxChainLength = 0;

    for (std::size_t i = 1; i < 7; ++i) {
      for (std::size_t j = i + 1; j < 8; ++j) {
        for (std::size_t k = j + 1; k < 9; ++k) {
          for (std::size_t l = k + 1; l < 10; ++l) {

            std::vector<std::size_t> numberSet = {i, j, k, l};
            std::size_t chainLength = find_chain_length(numberSet);

            if (chainLength > maxChainLength) {
              maxChainLength = chainLength;
              result = std::move(numberSet);
            }
          }
        }
      }
    }

  }

  std::cout << "Result: ";

  for (auto const digit : result) {
    std::cout << digit;
  }

  std::cout << '\n';
}
