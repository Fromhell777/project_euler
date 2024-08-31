#include "timer.hpp"

#include <cstddef>
#include <cstdint>
#include <iostream>
#include <string>
#include <gmpxx.h>

int main () {

  mpz_class intermidiate_result;
  int factorial = 100;
  long result = 0;

  {
    timer Timer;

    mpz_fac_ui(intermidiate_result.get_mpz_t(), factorial);

    std::string const & result_str = intermidiate_result.get_str();

    for (size_t i = 0; i < result_str.length(); ++i) {
      result += result_str[i] - '0';
    }
  }

  std::cout << "Result: " << result << "\n";
}
