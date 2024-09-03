#include "timer.hpp"

#include <cstddef>
#include <cstdint>
#include <iostream>
#include <gmpxx.h>

long find_fundamental_diophantine_equation_solution(const unsigned long limit) {
  long result = 0;
  unsigned long power = 4;
  long start_coefficient = 1;
  mpz_class max_numerator = 0;
  for (unsigned long i = 2; i <= limit; ++i) {
    if (i == power) {
      ++start_coefficient;
      power += (start_coefficient << 1) + 1;
    } else {
      long m = 0;
      long d = 1;
      long a = start_coefficient;
      mpz_class numerator_1 = start_coefficient;
      mpz_class numerator_2 = 1;
      mpz_class numerator_temp = numerator_1;
      mpz_class denominator_1 = 1;
      mpz_class denominator_2 = 0;
      mpz_class denominator_temp = denominator_1;
      while (numerator_1 * numerator_1 - i * denominator_1 * denominator_1 != 1) {
        m = d * a - m;
        d = (i - m * m) / d;
        a = (start_coefficient + m) / d;
        numerator_1 = a * numerator_1 + numerator_2;
        numerator_2 = numerator_temp;
        numerator_temp = numerator_1;
        denominator_1 = a * denominator_1 + denominator_2;
        denominator_2 = denominator_temp;
        denominator_temp = denominator_1;
      }

      if (numerator_1 > max_numerator) {
        result = i;
        max_numerator = numerator_1;
      }
    }
  }

  return result;
}

int main () {

  const long limit = 1000;
  long result;

  {
    timer Timer;

    result = find_fundamental_diophantine_equation_solution(limit);
  }

  std::cout << "Result: " << result << "\n";
}

// idea:
// Use the Chakravala method which was developed by Bhaskara II (1114 - 1185)
// based on the work done by Brahmagupta (598 - 668)
//
// Let k = a ^ 2 − d * b ^ 2 for given d
// Start with b = 1, a = floor(sqrt(d + 1) + 1)
//
// Find m such that (a + b * m) / k becomes integer
// and abs(m ^ 2 − d) is minimal
//
// a, b, k ⟶> (a * m + b * d) / abs(k), (a + b * m) / abs(k), (m ^ 2 − d) / k
// Stop when k = 1
//
// For (a + b * m) / k to be an integer
// m should be of form abs(k) * t + x
// where 0 < x < abs(k) and (a + b * x) / k is an integer
// To find t, substitute m = abs(k) * t + x in m ^ 2 − d = 0
// which gives t = (sqrt(d) - x) / abs(k)
// Choose between floor(t) and floor(t) + 1 to minimize abs(m ^ 2 − d)
// Every step tries to minimize k, and m can be found in less than k iterations
//
// It was later proven by Lagrange that this method always terminates
//
// Python example:
//
//
// from math import sqrt
// from fractions import Fraction
//
// def chakravala(d):
//
//     if sqrt(d) == int(sqrt(d)): return 1, 0
//
//     a, b, x =  int(sqrt(d+1)+1), 1, 0
//     k = int(a**2 - d)
//
//
//     while True:
//
//         # FINDING m
//         M = lambda T: abs(k) * T + x
//         for i in range(0,int(abs(k))):
//             if (a + i*b)%k == 0:
//                 x = i
//                 break
//         t = int((sqrt(d)-x)/abs(k))
//         if abs(d - M(t)**2) > abs(d - M(t+1)**2): t += 1
//         m = M(t)
//
//         # COMPOSITION
//         a, b = int(Fraction(a*m+d*b,abs(k))), int(Fraction(a+b*m,abs(k)))
//         k = int(a)**2 - d*(int(b)**2)
//
//         if k == 1: return int(a),int(b)
//
//         # BRAHMAGUPTA'S FORMULAE
//         if k == -1: return int(a**2+d*(b**2)), int(2*a*b)
//         if abs(k) == 2: return int(Fraction((a**2 + d*(b**2)), 2)), int(a*b)
//
//
// ans, xmin = 0, 0
// for d in range(8,1001):
//     s = chakravala(d)
//     if s[0]> xmin: xmin, ans = s[0], d
// print(ans)
