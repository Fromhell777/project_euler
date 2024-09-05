#include "timer.hpp"
#include "prettyprint.hpp"

#include <cstddef>
#include <cstdint>
#include <iostream>
#include <vector>
#include <utility>

/*
Analysis:

We will try to solve the problem with Pythagorian triples:
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

We can use the tree generation method of Pythagorean triples and just check if
they are adhering to the conditions of an almost equilateral triangle:
https://en.wikipedia.org/wiki/Tree_of_primitive_Pythagorean_triples




 Also, as to why you need only two transformations:

You start out with a triangle with sides:

     x2 + y2 = (2x ± 1)2
     x2 + y2 = 4x2 ± 4x + 1
     y2 = 3x2 ± 4x + 1
     y = √3x2 ± 4x + 1

So all triangles fitting the conditions must be of the form:

     x, √3x2 ± 4x + 1, 2x ± 1

The thrid transformation is:

     x2 =  x + 2y + 2z
     y2 = 2x +  y + 2z
     z2 = 2x + 2y + 3z

Starting out with any right triangle of the form:

     x, y, √x2 + y2
     x2 =  x + 2y + 2√x2 + y2
     y2 = 2x +  y + 2√x2 + y2
     z2 = 2x + 2y + 3√x2 + y2

And, in any integral case, 2x2 - 1 and 2y2 - 1 are greater than z2:

     2(x + 2y + 2√x2 + y2)± 1 = 2x + 2y + 3√x2 + y2
     2x + 4y + 4√x2 + y2 ± 1 = 2x + 2y + 3√x2 + y2
     2y + √x2 + y2 ± 1 = 0

And that is impossible.  Also:

     2(2x + y + 2√x2 + y2) ± 1 = 2x + 2y + 3√x2 + y2
     4x + 2y + 4√x2 + y2 ± 1 = 2x + 2y + 3√x2 + y2
     2x + √x2 + y2 ± 1 = 0

Which is also impossible.  Therefore the third transformation is never needed.  The first and second transformations are needed only under certain conditions.  Starting with:

     x, y, √x2 + y2

And using the first transformation:

     x2 =  x - 2y + 2√x2 + y2
     y2 = 2x - y - 2√x2 + y2
     z2 = 2x - 2y + 3√x2 + y2

Assuming that z2 differs from 2x2 or 2y2 by no more than one unit:

     2(x - 2y + 2√x2) ± 1 = 2x - 2y + 3√x2 + y2
     2x - 4y + 4√x2 ± 1 = 2x - 2y + 3√x2 + y2
     -2y ± 1 = √x2 + y2
     (-2y ± 1)2 = x2 + y2
     4y2 ± 4y + 1 = x2 + y2
     x2 = 3y2 ± 4y + 1
     x = √3y2 ± 4y + 1

As stated in the beginning, any right triangle that fits the conditions must be a triangle of the form:

     x, √3x2 ± 4x + 1, 2x ± 1

If 2y2 was the one that differed by no more than one unit instead of 2x2, then:

     2(2x - y - 2√x2 + y2) ± 1 = 2x - 2y + 3√x2 + y2
     4x - 2y - 4√x2 + y2 ± 1 = 2x - 2y + 3√x2 + y2
     2x - 7√x2 + y2 = 0
     2x = 7√x2 + y2
     4x2 = 7x2 + 7y2
     7y2 + 3x2 = 0

And that is impossible.  So, before and after the transformation:

     x, √3x2 ± 4x + 1, 2x ± 1
     √3y2 ± 4y + 1, y, 2y ± 1

Now, applying the first transformation to the result:


     x2 = √3y2 ± 4y + 1 - 2y + 2(2y ± 1)
     y2 = 2√3y2 ± 4y + 1 - y -2(2y ± 1)
     z2 = 2√3y2 ± 4y + 1 - 2y + 3(2y ± 1)

Simplifying x2, y2 and z2:

     x2 = √3y2 ± 4y + 1 - 2y + 2(2y ± 1)  
     x2 = √3y2 ± 4y + 1 - 2y + 4y ± 2  
     x2 = √3y2 ± 4y + 1 + 2y ± 2  

     y2 = 2√3y2 ± 4y + 1 - y -2(2y ± 1)
     y2 = 2√3y2 ± 4y + 1 - y -4y ± 2     
     y2 = 2√3y2 ± 4y + 1 - 5y ± 2

     z2 = 2√3y2 ± 4y + 1 - 2y + 3(2y ± 1)
     z2 = 2√3y2 ± 4y + 1 - 2y + 6y ± 3
     z2 = 2√3y2 ± 4y + 1 - 4y ± 3

Checking to see if x2 ± 1 is equal to z2:

     2(√3y2 ± 4y + 1 + 2y ± 2) ± 1 =
     2√3y2 ± 4y + 1 + 4y ± 4 ± 1

This can be equal to:

     2√3y2 ± 4y + 1 + 4y ± 3 

Which is z.  If instead you check to see if y2 ± 1 is equal to z2:

     2(2√3y2 ± 4y + 1 - 5y ± 2) ± 1 =
     4√3y2 ± 4y + 1 - 10y ± 4 ± 1

Which will not be equal to z if y is an integer.  So now we have:

     x, √3x2 ± 4x + 1, 2x ± 1

Now checking to see if other right triangles yield a solution when transformed via the second solution.  Starting with sides:

     x, y, √x2 + y2
     x2 = -x + 2y + 2√x2 + y2
     y2 = -2x + y + 2√x2 + y2
     z2 = -2x + 2y + 3√x2 + y2

Checking to see possible solutions in which 2x ± 1 = z:

     2(2y - x + 2√x2 + y2) ± 1 = 2y - 2x + 3√x2 + y2
     -2x + 4y + 4√x2 + y2 ± 1 = -2x + 2y + 3√x2 + y2
     2y + √x2 + y2 = 0

So there is no solution possible.  Now checking to see possible solutions in which 2y ± 1 = z:

     2(y - 2x + 2√x2 + y2) ± 1 = 2y - 2x + 3√x2 + y2
     -4x + 2y + 4√x2 + y2 ± 1 = -2x + 2y + 3√x2 + y2
     -2x + √x2 + y2 ± 1 = 0
     2x ± 1 = √x2 + y2
     4x2 ± 4x + 1 = x2 + y2
     3x2 ± 4x + 1 = y2
     y = √3x2 ± 4x + 1

And that is what we started out with.  So these are indeed the only primitive solutions.  So all primitive Pythagorean triples which satisfy these conditions can be found using this method.  Non-primitive triples satisfying these conditions, however, cannot be found.  Luckily, there are no such triples.  Start with a primitive triple x, y, z.  So:

       x != 2z ± 1

Multiplying both sides by an a to find a non-primitive solution:

       xa = 2az ± 1
       xa - 2az = ± 1
       a(x - 2z) = ± 1
       a = ± 1 / (x - 2z)

Which will be fractional.  So there is no non-primitive solution.  So, starting with 3, 4, 5, you need to apply the second and first transformations in turn.
*/

//bool is_perfect_square(std::uint64_t const n) {
//  // 0 is considered as a perfect
//  // square
//  //if (n == 0) return true;
//
//  //std::uint64_t odd = 1;
//  //while (n > 0) {
//  //    n -= odd;
//  //    odd += 2;
//  //}
//
//  //return n == 0;
//
//  std::uint64_t const squareRoot = std::floor(std::sqrt(n));
//  return squareRoot * squareRoot == n;
//}

std::uint64_t find_almost_equilateral_triangles(std::uint64_t const limit) {
  std::vector<std::pair<std::uint64_t, std::uint64_t> > triples = {std::make_pair(2, 1)};
  std::uint64_t perimiterSum = 0;

  //while (not triples.empty()) {
  //  std::pair<std::uint64_t, std::uint64_t> triple = triples.back();
  //  triples.pop_back();
  //  std::uint64_t const m = triple.first;
  //  std::uint64_t const n = triple.second;
  //  std::uint64_t const a = m * m - n * n;
  //  std::uint64_t const b = 2 * m * n;
  //  std::uint64_t const c = m * m + n * n;

  //  std::uint64_t const smallestSide = std::min(a, b);

  //  //std::cout << "triple: " << smallestSide << ", " << std::max(a,b) << ", " << c << '\n';

  //  // Upper limit that may not be exceeded for the worst case triangle
  //  if (smallestSide + c < limit) {
  //    triples.emplace_back(2 * m - n, m); // odd, even
  //    //triples.emplace_back(2 * m + n, m); // odd, even
  //    triples.emplace_back(m + 2 * n, n); // even, odd
  //  }

  //  // Check that the sides only differ by 1 for the standard triangle
  //  // C must be odd for the area to be an integer. So A will come from an even
  //  // side and will thus always be an integer number and never have a half part
  //  if (2 * smallestSide == c - 1 or 2 * smallestSide == c + 1) {
  //    if (2 * (smallestSide + c) <= limit) {
  //      std::cout << "triangle: " << 2 * smallestSide << ", " << c << ", " << c << '\n';
  //      perimiterSum += 2 * (smallestSide + c);
  //    }
  //  }

  //}

  std::pair<std::uint64_t, std::uint64_t> triple = std::make_pair(2, 1);

  std::uint64_t a = 3;
  std::uint64_t b = 4;
  std::uint64_t c = 5;

  std::uint64_t perimiter = 16;
  bool evenCycle = true;

  do {
    std::uint64_t const smallestSide = std::min(a, b);

    // Check that the sides only differ by 1 for the standard triangle
    // C must be odd for the area to be an integer. So A will come from an even
    // side and will thus always be an integer number and never have a half part
    if (2 * smallestSide == c - 1 or 2 * smallestSide == c + 1) {
      std::cout << "triangle: " << 2 * smallestSide << ", " << c << ", " << c << '\n';
      perimiterSum += 2 * (smallestSide + c);
    }

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

    perimiter = 2 * (smallestSide + c);

    evenCycle = not evenCycle;
  } while (perimiter <= limit);

  //std::cout << "\nBrute force: \n";


  //std::uint64_t i = 3;
  //bool limit_reached = false;

  //while (not limit_reached) {

  //  limit_reached = true;

  //  if (3 * i - 1 <= limit) {
  //    limit_reached = false;
  //    std::uint64_t const heigthSquared = 3 * i * i + 2 * i - 1;

  //    if (is_perfect_square(heigthSquared)) {
  //      std::cout << "triangle: " << i - 1 << ", " << i << ", " << i << '\n';
  //      perimiterSum += 3 * i - 1;
  //    }
  //  }

  //  if (3 * i + 1 <= limit) {
  //    limit_reached = false;
  //    std::uint64_t const heigthSquared = 3 * i * i - 2 * i - 1;

  //    if (is_perfect_square(heigthSquared)) {
  //      std::cout << "triangle: " << i + 1 << ", " << i << ", " << i << '\n';
  //      perimiterSum += 3 * i + 1;
  //    }
  //  }

  //  i += 2;
  //}

  return perimiterSum;
}

// 1/4*sqrt(4 * a^2 * b^2 - (a^2 + b^2 - c^2)^2)
// 1/4*sqrt(4 * x^2 * (x - 1)^2 - (x^2 + (x - 1)^2 - x^2)^2)
// 1/4*sqrt(4 * x^2 * (x - 1)^2 - (x - 1)^4)
// 1/4*sqrt((4 * x^2 - (x - 1)^2) * (x - 1)^2)
// 1/4 * (x - 1) * sqrt(4 * x^2 - (x - 1)^2)

int main()
{
  constexpr std::uint64_t limit = 1'000'000'000;
  std::uint64_t result;

  {
    timer Timer;

    result = find_almost_equilateral_triangles(limit);
  }

  std::cout << "Result: " << result << '\n';
}
