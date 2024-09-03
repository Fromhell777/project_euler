#include "timer.hpp"

#include <cstddef>
#include <cstdint>
#include <iostream>
#include <vector>
#include <algorithm>

typedef std::pair<std::vector<int>, std::vector<int> > cubes_t;

// Sizes must be 4, 5 or 6
std::vector<std::vector<int> > extractPossibilities(std::vector<int>& cube_combination)
{
  std::vector<int> digits;

  for (std::size_t i = 0; i < 10; ++i)
    {
      auto it = std::find(std::begin(cube_combination),
                          std::end(cube_combination), i);
      if (it == std::end(cube_combination))
        digits.push_back(i);
    }

  auto six_it = std::find(std::begin(cube_combination),
                          std::end(cube_combination), 6);

  std::vector<std::vector<int> > result;

  if (six_it != std::end(cube_combination))
    {
      std::size_t six_index = std::distance(std::begin(cube_combination), six_it);

      if (cube_combination.size() == 4)
        {
          for (auto const & digit1 : digits)
            {
              for (auto const & digit2 : digits)
                {
                  if (digit1 != digit2)
                    {
                      result.push_back(cube_combination);
                      result.back().push_back(digit1);
                      result.back().push_back(digit2);
                    }
                }
            }

          digits.pop_back();
          cube_combination[six_index] = 9;

          for (auto const & digit1 : digits)
            {
              for (auto const & digit2 : digits)
                {
                  if (digit1 != digit2)
                    {
                      result.push_back(cube_combination);
                      result.back().push_back(digit1);
                      result.back().push_back(digit2);
                    }
                }
            }
        }
      else if (cube_combination.size() == 5)
        {
          for (auto const & digit1 : digits)
            {
              result.push_back(cube_combination);
              result.back().push_back(digit1);
            }

          digits.pop_back();
          cube_combination[six_index] = 9;

          for (auto const & digit1 : digits)
            {
              result.push_back(cube_combination);
              result.back().push_back(digit1);
            }
        }
      else
        {
          result.push_back(cube_combination);
          cube_combination[six_index] = 9;
          result.push_back(cube_combination);
        }
    }
  else
    {
      if (cube_combination.size() == 4)
        {
          for (auto const & digit1 : digits)
            {
              for (auto const & digit2 : digits)
                {
                  if (digit1 != digit2)
                    {
                      result.push_back(cube_combination);
                      result.back().push_back(digit1);
                      result.back().push_back(digit2);
                    }
                }
            }
        }
      else if (cube_combination.size() == 5)
        {
          for (auto const & digit1 : digits)
            {
              result.push_back(cube_combination);
              result.back().push_back(digit1);
            }
        }
      else
        {
          result.push_back(cube_combination);
        }
    }

  return result;
}

unsigned long findCubeDigitPairs()
{
  static std::vector<std::pair<int, int> > const dependencies =
    {
      {0, 1},
      {0, 4},
      {0, 6},
      {1, 6},
      {1, 8},
      {2, 5},
      {3, 6},
      {4, 6}
    };

  std::vector<cubes_t> cube_combinations =
    std::initializer_list<cubes_t>({std::make_pair(std::vector<int>(),
                                                  std::vector<int>())});

  for (auto const & dependency : dependencies)
    {
      std::size_t limit = cube_combinations.size();
      for (std::size_t i = 0; i < limit; ++i)
        {
          auto cube_combination = cube_combinations[i];
          cube_combination.second.emplace_back(dependency.first);
          cube_combination.first.emplace_back(dependency.second);
          cube_combinations.push_back(cube_combination);
          cube_combinations[i].first.emplace_back(dependency.first);
          cube_combinations[i].second.emplace_back(dependency.second);
        }
    }

  // Remove the duplicates
  auto mid = std::begin(cube_combinations) + cube_combinations.size() / 2;
  cube_combinations.erase(mid, std::end(cube_combinations));

  for (auto& cube_combination : cube_combinations)
    {
      std::sort(std::begin(cube_combination.first),
                std::end(cube_combination.first));
      std::sort(std::begin(cube_combination.second),
                std::end(cube_combination.second));
      auto last = std::unique(std::begin(cube_combination.first),
                              std::end(cube_combination.first));
      cube_combination.first.erase(last, std::end(cube_combination.first));
      last = std::unique(std::begin(cube_combination.second),
                         std::end(cube_combination.second));
      cube_combination.second.erase(last, std::end(cube_combination.second));
    }

  // Remove impossible (too large) solutions
  cube_combinations.erase(std::remove_if(std::begin(cube_combinations),
                                         std::end(cube_combinations),
                                         [](cubes_t cubes){return cubes.first.size() > 6 ||
                                                                  cubes.second.size() > 6;}),
                          std::end(cube_combinations));

  // Remove subsets of solutions
  for (std::vector<cubes_t>::reverse_iterator i = std::rbegin(cube_combinations);
       i != std::rend(cube_combinations); ++i)
    {
      bool redundant = false;
      for (std::vector<cubes_t>::iterator j = std::begin(cube_combinations);
           !redundant && j != std::end(cube_combinations); ++j)
        {
          if (std::distance(std::begin(cube_combinations), j) +
              std::distance(std::rbegin(cube_combinations), i) !=
              static_cast<long>(cube_combinations.size() - 1))
            {
              if ((std::includes(std::begin((*i).first), std::end((*i).first),
                                std::begin((*j).first), std::end((*j).first)) &&
                  std::includes(std::begin((*i).second), std::end((*i).second),
                                std::begin((*j).second), std::end((*j).second))) ||
                  (std::includes(std::begin((*i).first), std::end((*i).first),
                                std::begin((*j).second), std::end((*j).second)) &&
                  std::includes(std::begin((*i).second), std::end((*i).second),
                                std::begin((*j).first), std::end((*j).first))))
                {
                  cube_combinations.erase(std::next(i).base());
                  redundant = true;
                }
            }
        }
    }

  std::vector<cubes_t> result;
  for (auto & cube_combination : cube_combinations)
    {
      std::vector<std::vector<int> > left_cube_possibilities = extractPossibilities(cube_combination.first);
      std::vector<std::vector<int> > right_cube_possibilities = extractPossibilities(cube_combination.second);

      for (auto const & left_cube_possibility : left_cube_possibilities)
        {
          for (auto const & right_cube_possibility : right_cube_possibilities)
            {
              result.emplace_back(left_cube_possibility,
                                  right_cube_possibility);
            }
        }
    }

  for (auto& cube_combination : result)
    {
      std::sort(std::begin(cube_combination.first),
                std::end(cube_combination.first));
      std::sort(std::begin(cube_combination.second),
                std::end(cube_combination.second));
    }

  for (std::size_t i = 0; i < result.size(); ++i)
    {
      std::size_t j = i + 1;
      while (j < result.size())
        {
          if (result[i] == result[j] ||
              (result[i].first == result[j].second &&
               result[i].second == result[j].first))
            result.erase(std::begin(result) + j);
          else
            ++j;
        }
    }

  return result.size();
}

int main ()
{
  long result;

  {
    timer Timer;

    result = findCubeDigitPairs();
  }

  std::cout << "Result: " << result << "\n";
}
