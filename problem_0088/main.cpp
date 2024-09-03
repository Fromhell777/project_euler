#include "timer.hpp"

#include <cstddef>
#include <cstdint>
#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>

struct Set
{
  unsigned long set_size;
  unsigned long product;
  std::vector<unsigned long> factors;
};

void exploreSets(const unsigned long limit, const unsigned long index,
                 std::vector<Set>& sets, Set& set)
{
  if (sets[set.set_size].product > set.product)
    {
      sets[set.set_size] = set;
    }

  if (index != set.factors.size() - 1 &&
      set.factors[index] > set.factors[index + 1])
    {
      Set new_set = set;
      new_set.set_size += set.product / set.factors[index + 1] - 1;
      if (new_set.set_size <= limit)
        {
          new_set.product += set.product / set.factors[index + 1];
          new_set.factors[index + 1]++;

          exploreSets(limit, index + 1, sets, new_set);
        }
    }

  if (index == 0 || set.factors[index - 1] > set.factors[index])
    {
      set.set_size += set.product / set.factors[index] - 1;
      if (set.set_size <= limit)
        {
          set.product += set.product / set.factors[index];
          set.factors[index]++;

          exploreSets(limit, index, sets, set);
        }
    }
}

long findProductSumNumbers(const unsigned long limit)
{
  std::vector<Set> sets(limit + 1);

  // Add all the worst case sets
  for (std::size_t k = 2; k <= limit; ++k)
    {
      sets[k].set_size = k;
      sets[k].product = 2 * k;
      sets[k].factors = {k, 2};
    }

  // explore the sets of set size 2
  Set tmp_set;
  tmp_set.set_size = 5;
  tmp_set.product = 9;
  tmp_set.factors = {3, 3};
  exploreSets(limit, 0, sets, tmp_set);

  // explore the sets of set size bigger than 2
  unsigned long set_size = 5;
  unsigned long product = 8;
  for (std::size_t i = 3; set_size <= limit; ++i)
    {
      Set new_set;
      new_set.set_size = set_size;
      new_set.product = product;
      new_set.factors = std::vector<unsigned long>(i, 2);
      exploreSets(limit, 0, sets, new_set);
      set_size += product - 1;
      product *= 2;
    }

  std::sort(std::begin(sets), std::end(sets),
            [](const Set& lhs, const Set& rhs) {return lhs.product > rhs.product;});
  auto end = std::unique(std::begin(sets), std::end(sets),
                         [](const Set& lhs, const Set& rhs)
                           {
                             return lhs.product == rhs.product;
                           });

  unsigned long result = std::accumulate(std::begin(sets), end, 0ull,
                                         [](const unsigned long sum, const Set& rhs)
                                           {
                                             return sum + rhs.product;
                                           });
  return result;
}

int main ()
{
  const unsigned long limit = 12000;

  long result;

  {
    timer Timer;

    result = findProductSumNumbers(limit);
  }

  std::cout << "Result: " << result << "\n";
}
