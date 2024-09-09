#include "timer.hpp"

#include <cstddef>
#include <cstdint>
#include <iostream>
#include <utility>

/*
Analysis:

We will try to solve the problem with Pythagorean triples:
https://en.wikipedia.org/wiki/Pythagorean_triple

First we will calculate the formula for the area of a almost equilateral
triangle

   x /\ x
    /  \
   /    \
   ------
    x + 1

  area = 1/4 * (x + 1) * sqrt(4 * x^2 - (x + 1)^2)

   x /\ x
    /  \
   /    \
   ------
    x - 1

  area = 1/4 * (x - 1) * sqrt(4 * x^2 - (x - 1)^2)

From this we can conclude a couple of things:
- x must always be odd. Otherwise the division by 4 will result in a
  non-integer area
- The bottom edge will always be even
- The height must be an integer
- The triangle consists of two right angled triangles that are the same
  Pythagorean triple

We know that if we check all the Pythagorean triples we will also have checked
all the almost equilateral triangles. Let's say that we have a primitive triple
x, y, z with:

  x != 2 * z +- 1

Multiplying both sides by a scaler k we can find a non-primitive solution:

  k * x = 2 * k * z +- 1
  k * x - 2 * k * z = +- 1
  k * (x - 2 * z) = +- 1
  k = +- 1 / (x - 2z)

Which will be fractional. So there is no non-primitive solution.


We can use the tree generation method of Pythagorean triples and just check if
they are adhering to the conditions of an almost equilateral triangle:
https://en.wikipedia.org/wiki/Tree_of_primitive_Pythagorean_triples

Triple: x, y, z

Transform matrices

  a =     x - 2 * y + 2 * z
  b = 2 * x -     y + 2 * z
  c = 2 * x - 2 * y + 3 * z

  a = -     x + 2 * y + 2 * z
  b = - 2 * x +     y + 2 * z
  c = - 2 * x + 2 * y + 3 * z

  a =     x + 2 * y + 2 * z
  b = 2 * x +     y + 2 * z
  c = 2 * x + 2 * y + 3 * z


First we will prove that the 3rd transformation can never produce a valid almost
equilateral triangle

Starting out with any right triangle of the form:

  x, y, sqrt(x^2 + y^2)
  a =     x + 2 * y + 2 * sqrt(x^2 + y^2)
  b = 2 * x +     y + 2 * sqrt(x^2 + y^2)
  c = 2 * x + 2 * y + 3 * sqrt(x^2 + y^2)

It can be shown that 2 * a +- 1 is always greater than c:

  2 * (x + 2 * y + 2 * sqrt(x^2 + y^2)) +- 1 >= 2 * x + 2 * y + 3 * sqrt(x^2 + y^2)
  2 * x + 4 * y + 4 * sqrt(x^2 + y^2) +- 1 >= 2 * x + 2 * y + 3 * sqrt(x^2 + y^2)
  2 * y + sqrt(x^2 + y^2) +- 1 >= 0

The equation on the left is always larger than 0. Proving the statement

The same be done for proving that 2 * b +- 1 is always greater than c:

  2 * (2 * x + y + 2 * sqrt(x^2 + y^2)) +- 1 >= 2 * x + 2 * y + 3 * sqrt(x^2 + y^2)
  4 * x + 2 * y + 4 * sqrt(x^2 + y^2) +- 1 >=  2 * x + 2 * y + 3 * sqrt(x^2 + y^2)
  2 * x + sqrt(x^2 + y^2) +- 1 >= 0

The equation on the left is always larger than 0. Proving the statement


Now let's see what happens when we used the first transform starting out with
any right triangle of the form:

  x, y, sqrt(x^2 + y^2)
  a =     x - 2 * y + 2 * sqrt(x^2 + y^2)
  b = 2 * x -     y + 2 * sqrt(x^2 + y^2)
  c = 2 * x - 2 * y + 3 * sqrt(x^2 + y^2)

If the new triple is part of an almost equilateral triangle than z differs from
2 * a or 2 * b by no more than one unit. Let's first check if 2 * b +- 1 = c is
possible:

  2 * (2 * x - y + 2 * sqrt(x^2 + y^2)) +- 1 = 2 * x - 2 * y + 3 * sqrt(x^2 + y^2)
  4 * x - 2 * y + 4 * sqrt(x^2 + y^2) +- 1 = 2 * x - 2 * y + 3 * sqrt(x^2 + y^2)
  2 * x + sqrt(x^2 + y^2) +- 1 = 0

The equation on the left is always larger than 0. Meaning that after using the
first transform the, that b can't be the smaller side of an almost equilateral
triangle

Let's continue to check 2 * a +- 1 = c

  2 * (x - 2 * y + 2 * sqrt(x^2 + y^2)) +- 1 = 2 * x - 2 * y + 3 * sqrt(x^2 + y^2)
  2 * x - 4 * y + 4 * sqrt(x^2 + y^2) +- 1 = 2 * x - 2 * y + 3 * sqrt(x^2 + y^2)
  sqrt(x^2 + y^2) +- 1 = 2 * y
  sqrt(x^2 + y^2) = 2 * y +- 1
  x^2 + y^2 = (2 * y +- 1)^2
  x^2 + y^2 = 4 * y^2 +- 4 * y + 1
  x^2 = 3 * y^2 +- 4 * y + 1
  x = sqrt(3 * y^2 +- 4 * y + 1)

Using this extra restriction on the starting triple, we can see that the
starting triangle should also be an almost equilateral triangle

  x, y, sqrt(x^2 + y^2)
  sqrt(3 * y^2 +- 4 * y + 1), y, sqrt(4 * y^2 +- 4 * y + 1 + y^2)
  sqrt(3 * y^2 +- 4 * y + 1), y, sqrt(4 * y^2 +- 4 * y + 1)
  sqrt(3 * y^2 +- 4 * y + 1), y, sqrt((2 * y +- 1)^2)
  sqrt(3 * y^2 +- 4 * y + 1), y, 2 * y +- 1

So the starting triangle should also be an almost equilateral triangle with y as
the smaller side


The same reasoning can be applied to the second transform starting out with
any right triangle of the form:

  x, y, sqrt(x^2 + y^2)
  a = -     x + 2 * y + 2 * sqrt(x^2 + y^2)
  b = - 2 * x +     y + 2 * sqrt(x^2 + y^2)
  c = - 2 * x + 2 * y + 3 * sqrt(x^2 + y^2)

If the new triple is part of an almost equilateral triangle than z differs from
2 * a or 2 * b by no more than one unit. Let's first check if 2 * a +- 1 = c is
possible:

  2 * (- x + 2 * y + 2 * sqrt(x^2 + y^2)) +- 1 = - 2 * x + 2 * y + 3 * sqrt(x^2 + y^2)
  - 2 * x + 4 * y + 4 * sqrt(x^2 + y^2) +- 1 = - 2 * x + 2 * y + 3 * sqrt(x^2 + y^2)
  2 * y + sqrt(x^2 + y^2) +- 1 = 0

The equation on the left is always larger than 0. Meaning that after using the
first transform the, that a can't be the smaller side of an almost equilateral
triangle

Let's continue to check 2 * b +- 1 = c

  2 * (- 2 * x + y + 2 * sqrt(x^2 + y^2)) +- 1 = - 2 * x + 2 * y + 3 * sqrt(x^2 + y^2)
  - 4 * x + 2 * y + 4 * sqrt(x^2 + y^2) +- 1 = - 2 * x + 2 * y + 3 * sqrt(x^2 + y^2)
  sqrt(x^2 + y^2) +- 1 = 2 * x
  sqrt(x^2 + y^2) = 2 * x +- 1
  x^2 + y^2 = (2 * x +- 1)^2
  x^2 + y^2 = 4 * x^2 +- 4 * x + 1
  y^2 = 3 * x^2 +- 4 * x + 1
  y = sqrt(3 * x^2 +- 4 * x + 1)

Using this extra restriction on the starting triple, we can see that the
starting triangle should also be an almost equilateral triangle

  x, y, sqrt(x^2 + y^2)
  x, sqrt(3 * x^2 +- 4 * x + 1), sqrt(x^2 + 3 * x^2 +- 4 * x + 1)
  x, sqrt(3 * x^2 +- 4 * x + 1), sqrt(4 * x^2 +- 4 * x + 1)
  x, sqrt(3 * x^2 +- 4 * x + 1), sqrt((2 * x +- 1)^2)
  x, sqrt(3 * x^2 +- 4 * x + 1), 2 * x +- 1

So the starting triangle should also be an almost equilateral triangle with y as
the smaller side


In conclusion we can say that we should always start from an almost equilateral
triangle in order to find the next. Since we start from the triangle 3, 4, 5 we
can iteratively perform the second and then the first transform to generate all
the almost equilateral triangles
*/

std::uint64_t find_almost_equilateral_triangles1(std::uint64_t const limit) {
  std::uint64_t perimiterSum = 0;
  std::pair<std::uint64_t, std::uint64_t> triple = std::make_pair(2, 1);

  std::uint64_t a = 3;
  std::uint64_t b = 4;
  std::uint64_t c = 5;

  std::uint64_t smallestSide = std::min(a, b);
  std::uint64_t perimiter = 16;
  bool evenCycle = true;

  do {
    // The sides should only differ by 1 for the standard triangle because we
    // will only hit almost equilateral triangles
    perimiterSum += perimiter;

    std::uint64_t m = triple.first;
    std::uint64_t n = triple.second;

    // Upper limit that may not be exceeded for the worst case triangle
    if (evenCycle) {
      triple = std::make_pair(m + 2 * n, n);
    } else {
      triple = std::make_pair(2 * m - n, m);
    }

    m = triple.first;
    n = triple.second;

    a = m * m - n * n;
    b = 2 * m * n;
    c = m * m + n * n;

    smallestSide = std::min(a, b);
    perimiter = 2 * (smallestSide + c);

    evenCycle = not evenCycle;
  } while (perimiter <= limit);

  return perimiterSum;
}

/*
Analysis:

We can also solve the problem using Pell's equation:
https://en.wikipedia.org/wiki/Pell%27s_equation

Applying the Pythagorean theorem on the following triangle gives:

   h |\ x
     | \
     |  \
     ----
  (x +- 1) / 2

  x^2 = h^2 + ((x +- 1) / 2)^2
  x^2 = h^2 + (x^2 +- 2 * x + 1) / 4
  3 * x^2 -+ 2 * x - h^2 = 1
  3 * x^2 -+ 2 * x - 4 * h^2 = 1
  9 * x^2 -+ 6 * x - 12 * h^2 = 3
  (3 * x -+ 1)^2 - 1 - 12 * h^2 = 3
  (3 * x -+ 1)^2 - 12 * h^2 = 4
  ((3 * x -+ 1) / 2)^2 - 3 * h^2 = 1

This looks like the Pell's equation:

  a^2 - n * b^2 = 1
  a = (3 * x -+ 1) / 2
  b = h
  n = 3


Now we have to prove that finding all integer solutions to this equation will
give us all the almost equilateral triangles

- We already proved earlier that the height must also be an integer in an almost
  equilateral triangle
- If a is an integer then x will also be an integer. This can be seen as
  follows. If a is a solution then it is not divisible by 3. Otherwise the left
  side of equation ((3 * x -+ 1) / 2)^2 - 3 * h^2 = 1 becomes divisible by 3 and
  can never be equal to 1

  Secondly looking at the following equation we can see that for every integer
  solution a (which is not divisible by 3) we can make it a multiple of 3 by
  adding or subtracting 1. So we can always find an integer solution for x

  a = (3 * x -+ 1) / 2
  2 * a +- 1 = 3 * x
  (2 * a +- 1) / 3 = x


From a fundamental solution to Pell's equation we can recursively generation all
the other integer solutions

The fundamental solution for n = 3 is a = 2 and b = 1. This corresponds to a
1, 1, 2 triangle

The next values can be created using the following recursive formula:

  a_next = 2 * a + 3 * b
  b_next = 2 * b + a


The formula for the perimeter can then be calculated as follows:

  p = 3 * x +- 1
  p = 3 * (2 * a +- 1) / 3 +- 1
  p = 2 * a +- 1 +- 1
  p = 2 * a +- 2


Looking at the values of a we can actually see the it always oscillate between
1 mod 3 and -1 mod 3. This lets us know that we can just oscillate between doing
the addition or subtraction every iteration

*/

std::uint64_t find_almost_equilateral_triangles2(std::uint64_t const limit) {
  std::uint64_t perimiterSum = 0;
  std::pair<std::uint64_t, std::uint64_t> pellSolution = std::make_pair(7, 4);

  std::uint64_t perimiter = 16;
  bool evenCycle = false;

  do {
    perimiterSum += perimiter;

    pellSolution = std::make_pair(2 * pellSolution.first + 3 * pellSolution.second,
                                  2 * pellSolution.second + pellSolution.first);

    if (evenCycle) {
      perimiter = 2 * pellSolution.first + 2;
    } else {
      perimiter = 2 * pellSolution.first - 2;
    }

    evenCycle = not evenCycle;
  } while (perimiter <= limit);

  return perimiterSum;
}

int main()
{
  constexpr std::uint64_t limit = 1'000'000'000;
  std::uint64_t result;

  {
    timer Timer;

    //result = find_almost_equilateral_triangles1(limit);
    result = find_almost_equilateral_triangles2(limit);
  }

  std::cout << "Result: " << result << '\n';
}
