#include "timer.hpp"

#include <cstddef>
#include <cstdint>
#include <iostream>
#include <bitset>
#include <array>
#include <memory>

unsigned long calculateNextChainNumber(unsigned long number)
{
  static std::array<int, 10> powers = {0, 1, 4, 9, 16, 25, 36, 49, 64, 81};
  unsigned long result = 0;
  while (number)
    {
      result += powers[number % 10];
      number /= 10;
    }

  return result;
}

template <std::size_t limit>
unsigned long find_square_digit_chains()
{
  auto chains_loops = std::make_unique<std::bitset<limit> >();
  chains_loops->set(2); // Will end up at 89
  chains_loops->set(3); // Will end up at 89
  chains_loops->set(4); // Will end up at 89

  for (std::size_t i = 5; i < limit; ++i)
    {
      unsigned long next_chain_number = i;
      while (next_chain_number >= i)
        {
          next_chain_number = calculateNextChainNumber(next_chain_number);
        }
      (*chains_loops)[i] = (*chains_loops)[next_chain_number];
    }

  return chains_loops->count();
}

int main ()
{
  unsigned long const limit = 10'000'000;
  long result;

  {
    timer Timer;

    result = find_square_digit_chains<limit>();
  }

  std::cout << "Result: " << result << "\n";
}
