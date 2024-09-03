#include "timer.hpp"

#include <cstddef>
#include <cstdint>
#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <complex>

#include <Eigen/Eigen>

void make_probability_matrix(Eigen::MatrixXd &matrix,
                             const unsigned long c_MaxDoubleRoll,
                             const unsigned long c_NumSquares) {
  // std::vector<double> dice_probability = {     0,      0,      0, 2.0/36,
  //                                         2.0/36, 4.0/36, 4.0/36, 6.0/36,
  //                                         4.0/36, 4.0/36, 2.0/36, 2.0/36,
  //                                              0,      0,      0,      0,
  //                                              0,      0,      0,      0,
  //                                              0,      0,      0,      0,
  //                                              0,      0,      0,      0,
  //                                              0,      0,      0,      0,
  //                                              0,      0,      0,      0,
  //                                              0,      0,      0,      0};

  // std::vector<double> dice_probability_doubles = {     0,      0, 1.0/36,
  //                                                      0, 1.0/36,      0,
  //                                                 1.0/36,      0, 1.0/36,
  //                                                      0, 1.0/36,      0,
  //                                                 1.0/36,      0,      0,
  //                                                      0,      0,      0,
  //                                                      0,      0,      0,
  //                                                      0,      0,      0,
  //                                                      0,      0,      0,
  //                                                      0,      0,      0,
  //                                                      0,      0,      0,
  //                                                      0,      0,      0,
  //                                                      0,      0,      0,
  //                                                      0};

  std::vector<double> dice_probability = {     0,      0,      0, 2.0/16,
                                          2.0/16, 4.0/16, 2.0/16, 2.0/16,
                                               0,      0,      0,      0,
                                               0,      0,      0,      0,
                                               0,      0,      0,      0,
                                               0,      0,      0,      0,
                                               0,      0,      0,      0,
                                               0,      0,      0,      0,
                                               0,      0,      0,      0,
                                               0,      0,      0,      0};

  std::vector<double> dice_probability_doubles = {     0,      0, 1.0/16,
                                                       0, 1.0/16,      0,
                                                  1.0/16,      0, 1.0/16,
                                                       0,      0,      0,
                                                       0,      0,      0,
                                                       0,      0,      0,
                                                       0,      0,      0,
                                                       0,      0,      0,
                                                       0,      0,      0,
                                                       0,      0,      0,
                                                       0,      0,      0,
                                                       0,      0,      0,
                                                       0,      0,      0,
                                                       0};

  // initial matrix with one double throw
  for (std::size_t j = 0; j < c_NumSquares; ++j) {
    for (std::size_t i = 0; i < dice_probability.size(); ++i) {
      matrix(i, j) = dice_probability[i];
      matrix(i, j + c_NumSquares * (c_MaxDoubleRoll - 1)) = dice_probability[i];
      matrix(i + c_NumSquares, j) = dice_probability_doubles[i];
    }

    // JAIL
    matrix(10, j) += matrix(30, j) + matrix(30 + c_NumSquares, j);
    matrix(30, j) = 0;
    matrix(30 + c_NumSquares, j) = 0;

    // chance
    matrix(0, j) += (matrix(7, j) + matrix(22, j) + matrix(36, j)) * 1.0/16; // GO
    matrix(10, j) += (matrix(7, j) + matrix(22, j) + matrix(36, j)) * 1.0/16; // JAIL
    matrix(11, j) += (matrix(7, j) + matrix(22, j) + matrix(36, j)) * 1.0/16; // C1
    matrix(24, j) += (matrix(7, j) + matrix(22, j) + matrix(36, j)) * 1.0/16; // E3
    matrix(39, j) += (matrix(7, j) + matrix(22, j) + matrix(36, j)) * 1.0/16; // H2
    matrix(5, j) += (matrix(7, j) + matrix(22, j) + matrix(36, j)) * 1.0/16; // R1
    matrix(15, j) += matrix(7, j) * 2.0/16; // R2
    matrix(25, j) += matrix(22, j) * 2.0/16; // R3
    matrix(5, j) += matrix(36, j) * 2.0/16; // R1
    matrix(12, j) += (matrix(7, j) + matrix(36, j)) * 1.0/16; // U1
    matrix(28, j) += matrix(22, j) * 1.0/16; // U2
    matrix(4, j) += matrix(7, j) * 1.0/16; // back 3 squares
    matrix(19, j) += matrix(22, j) * 1.0/16; // back 3 squares
    matrix(33, j) += matrix(36, j) * 1.0/16; // back 3 squares
    matrix(7, j) *= 6.0/16;
    matrix(22, j) *= 6.0/16;
    matrix(36, j) *= 6.0/16;

    // chance after one double throw
    matrix(0 + c_NumSquares, j) += (matrix(7 + c_NumSquares, j) +
                                    matrix(22 + c_NumSquares, j) +
                                    matrix(36 + c_NumSquares, j)) * 1.0/16; // GO
    matrix(10, j) += (matrix(7 + c_NumSquares, j) +
                      matrix(22 + c_NumSquares, j) +
                      matrix(36 + c_NumSquares, j)) * 1.0/16; // JAIL
    matrix(11 + c_NumSquares, j) += (matrix(7 + c_NumSquares, j) +
                                     matrix(22 + c_NumSquares, j) +
                                     matrix(36 + c_NumSquares, j)) * 1.0/16; // C1
    matrix(24 + c_NumSquares, j) += (matrix(7 + c_NumSquares, j) +
                                     matrix(22 + c_NumSquares, j) +
                                     matrix(36 + c_NumSquares, j)) * 1.0/16; // E3
    matrix(39 + c_NumSquares, j) += (matrix(7 + c_NumSquares, j) +
                                     matrix(22 + c_NumSquares, j) +
                                     matrix(36 + c_NumSquares, j)) * 1.0/16; // H2
    matrix(5 + c_NumSquares, j) += (matrix(7 + c_NumSquares, j) +
                                    matrix(22 + c_NumSquares, j) +
                                    matrix(36 + c_NumSquares, j)) * 1.0/16; // R1
    matrix(15 + c_NumSquares, j) += matrix(7 + c_NumSquares, j) * 2.0/16; // R2
    matrix(25 + c_NumSquares, j) += matrix(22 + c_NumSquares, j) * 2.0/16; // R3
    matrix(5 + c_NumSquares, j) += matrix(36 + c_NumSquares, j) * 2.0/16; // R1
    matrix(12 + c_NumSquares, j) += (matrix(7 + c_NumSquares, j) +
                                     matrix(36 + c_NumSquares, j)) * 1.0/16; // U1
    matrix(28 + c_NumSquares, j) += matrix(22 + c_NumSquares, j) * 1.0/16; // U2
    matrix(4 + c_NumSquares, j) += matrix(7 + c_NumSquares, j) * 1.0/16; // back 3 squares
    matrix(19 + c_NumSquares, j) += matrix(22 + c_NumSquares, j) * 1.0/16; // back 3 squares
    matrix(33 + c_NumSquares, j) += matrix(36 + c_NumSquares, j) * 1.0/16; // back 3 squares
    matrix(7 + c_NumSquares, j) *= 6.0/16;
    matrix(22 + c_NumSquares, j) *= 6.0/16;
    matrix(36 + c_NumSquares, j) *= 6.0/16;

    // community chest
    matrix(0, j) += (matrix(2, j) + matrix(17, j) + matrix(33, j)) * 1.0/16; // GO
    matrix(10, j) += (matrix(2, j) + matrix(17, j) + matrix(33, j)) * 1.0/16; // JAIL
    matrix(2, j) *= 14.0/16;
    matrix(17, j) *= 14.0/16;
    matrix(33, j) *= 14.0/16;

    // community chest after one double throw
    matrix(0 + c_NumSquares, j) += (matrix(2 + c_NumSquares, j) +
                                    matrix(17 + c_NumSquares, j) +
                                    matrix(33 + c_NumSquares, j)) * 1.0/16; // GO
    matrix(10, j) += (matrix(2 + c_NumSquares, j) +
                      matrix(17 + c_NumSquares, j) +
                      matrix(33 + c_NumSquares, j)) * 1.0/16; // JAIL
    matrix(2 + c_NumSquares, j) *= 14.0/16;
    matrix(17 + c_NumSquares, j) *= 14.0/16;
    matrix(33 + c_NumSquares, j) *= 14.0/16;


    std::rotate(std::rbegin(dice_probability),
                std::rbegin(dice_probability) + 1, std::rend(dice_probability));

    std::rotate(std::rbegin(dice_probability_doubles),
                std::rbegin(dice_probability_doubles) + 1,
                std::rend(dice_probability_doubles));
  }

  // subsequent matrices with no double rol penalty
  for (unsigned long double_rolls = 1; double_rolls < c_MaxDoubleRoll - 1;
       ++double_rolls) {
    for (std::size_t j = 0; j < c_NumSquares; ++j) {
      for (std::size_t i = 0; i < c_NumSquares; ++i) {
        matrix(i, j + double_rolls * c_NumSquares) = matrix(i, j);
        matrix(i + (double_rolls + 1) * c_NumSquares,
               j + double_rolls * c_NumSquares) = matrix(i + c_NumSquares, j);
      }
    }
  }

  // last matrix with double penalty
  for (std::size_t j = 0; j < c_NumSquares; ++j) {
    // JAIL
    matrix(10, j) += matrix(30, j);
    matrix(30, j) = 0;

    std::size_t offset = (c_MaxDoubleRoll - 1) * c_NumSquares;
    // chance after penalty double throw
    matrix(0, j + offset) += (matrix(7, j + offset) +
                              matrix(22, j + offset) +
                              matrix(36, j + offset)) * 1.0/16; // GO
    matrix(10, j + offset) += (matrix(7, j + offset) +
                      matrix(22, j + offset) +
                      matrix(36, j + offset)) * 1.0/16; // JAIL
    matrix(11, j + offset) += (matrix(7, j + offset) +
                               matrix(22, j + offset) +
                               matrix(36, j + offset)) * 1.0/16; // C1
    matrix(24, j + offset) += (matrix(7, j + offset) +
                               matrix(22, j + offset) +
                               matrix(36, j + offset)) * 1.0/16; // E3
    matrix(39, j + offset) += (matrix(7, j + offset) +
                               matrix(22, j + offset) +
                               matrix(36, j + offset)) * 1.0/16; // H2
    matrix(5,  j + offset) += (matrix(7, j + offset) +
                               matrix(22, j + offset) +
                               matrix(36, j + offset)) * 1.0/16; // R1
    matrix(15, j + offset) += matrix(7, j + offset) * 2.0/16; // R2
    matrix(25, j + offset) += matrix(22, j + offset) * 2.0/16; // R3
    matrix(5, j + offset) += matrix(36, j + offset) * 2.0/16; // R1
    matrix(12, j + offset) += (matrix(7, j + offset) +
                               matrix(36, j + offset)) * 1.0/16; // U1
    matrix(28, j + offset) += matrix(22, j + offset) * 1.0/16; // U2
    matrix(4, j + offset) += matrix(7, j + offset) * 1.0/16; // back 3 squares
    matrix(19, j + offset) += matrix(22, j + offset) * 1.0/16; // back 3 squares
    matrix(33, j + offset) += matrix(36, j + offset) * 1.0/16; // back 3 squares
    matrix(7, j + offset) *= 6.0/16;
    matrix(22, j + offset) *= 6.0/16;
    matrix(36, j + offset) *= 6.0/16;

    // community chest after penalty double throw
    matrix(0, j + offset) += (matrix(2, j + offset) +
                              matrix(17, j + offset) +
                              matrix(33, j + offset)) * 1.0/16; // GO
    matrix(10, j + offset) += (matrix(2, j + offset) +
                               matrix(17, j + offset) +
                               matrix(33, j + offset)) * 1.0/16; // JAIL
    matrix(2, j + offset) *= 14.0/16;
    matrix(17, j + offset) *= 14.0/16;
    matrix(33, j + offset) *= 14.0/16;

    // penalty for double roll
    matrix(10, j + offset) +=
      std::accumulate(std::begin(dice_probability_doubles),
                      std::end(dice_probability_doubles), float(0));
  }
}

long solve_markov_chain(Eigen::MatrixXd &matrix,
                        const unsigned long c_MaxDoubleRoll,
                        const unsigned long c_NumSquares) {
  Eigen::EigenSolver<Eigen::MatrixXd> eigenSolver(matrix);

  // Find index for eigenvalue == 1. Note that returned eigenvalues are complex.
  auto const is_match = [](double const value, double const target) {
    constexpr static double c_Tolerance = 1e-10;
    return (std::abs(value - target) < c_Tolerance);
  };

  auto const & eigenValues = eigenSolver.eigenvalues();
  auto const eigenEnd = eigenValues.data() + eigenValues.size();
  auto const eigenIter = std::find_if(eigenValues.data(), eigenEnd,
    [&](auto const value) {
      return is_match(value.real(), 1) and is_match(value.imag(), 0);
    });

  if (eigenIter == eigenEnd) {
    throw std::runtime_error("No eigenvalue == 1.");
  }

  std::size_t const eigenIndex = std::distance(eigenValues.data(), eigenIter);

  // Extract eigenvector and do L1 normalization (Eigen returns L2 normalized value).
  Eigen::Matrix<double, 1, Eigen::Dynamic> steadyState = eigenSolver.eigenvectors().real().col(eigenIndex);
  steadyState /= steadyState.sum();

  // Sum states to get probability per cell
  std::vector<double> summedSteadyState(c_NumSquares, 0);
  for (std::size_t i = 0; i < c_NumSquares; ++i) {
    for (std::size_t numDouble = 0; numDouble < c_MaxDoubleRoll; ++numDouble) {
      summedSteadyState[i] += steadyState(i + numDouble * c_NumSquares);
    }
  }

  std::vector<double> sortedState = summedSteadyState;
  std::sort(std::begin(sortedState), std::end(sortedState), std::greater<>());

  long result = 0;
  for (std::size_t index = 0; index < 3; ++index) {
    auto const it = std::find(std::begin(summedSteadyState),
      std::end(summedSteadyState), sortedState[index]);
    auto const pos = std::distance(std::begin(summedSteadyState), it);
    result *= 100;
    result += pos;
  }

  return result;
}

int main () {
  constexpr static unsigned long c_MaxDoubleRoll = 3;
  constexpr static unsigned long c_NumSquares = 40;

  Eigen::MatrixXd matrix(c_NumSquares * c_MaxDoubleRoll,
                         c_NumSquares * c_MaxDoubleRoll);
  long result;

  {
    timer Timer;

    make_probability_matrix(matrix, c_MaxDoubleRoll, c_NumSquares);
    result = solve_markov_chain(matrix, c_MaxDoubleRoll, c_NumSquares);
  }

  std::cout << "Result: " << result << "\n";
}
