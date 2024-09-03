#include "timer.hpp"

#include <cstddef>
#include <cstdint>
#include <iostream>
#include <algorithm>

unsigned long GCD(unsigned long a, unsigned long b) {
  while (true)
    {
      if (a == 0)
        return b;

      b %= a;
      if (b == 0)
        return a;

      a %= b;
    }
}

unsigned long findIntegerCoordinatesRightTriangles(unsigned long const limit)
{
  unsigned long result = 0;
  for (unsigned long j = 1; j <= limit; ++j)
    {
      for (unsigned long i = 1; i <= limit - 1; ++i)
        {
          unsigned long gcd = GCD(i, j);
          result += std::min((limit - i) / (j / gcd), j / (i / gcd));
        }
    }

  result *= 2; // count these double
  result += limit * limit * 2; // right angle at the edge
  result += limit * limit; // right angle at the origin
  return result;
}

int main ()
{
  unsigned long const limit = 50;
  long result;

  {
    timer Timer;

    result = findIntegerCoordinatesRightTriangles(limit);
  }

  std::cout << "Result: " << result << "\n";
}
