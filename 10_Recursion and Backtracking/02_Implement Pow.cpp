/*
 * Implement Pow
 *
 * Implement the function power(b, e), which calculates b raised to the power of e (i.e. be).
 *
 * Examples:
 *
 * Input: b = 3.00000, e = 5
 * Output: 243.00000
 *
 * Input: b = 0.55000, e = 3
 * Output: 0.16638
 *
 * Input: b = -0.67000, e = -7
 * Output: -16.49971
 *
 * Constraints:
 * -100.0 < b < 100.0
 * -10^9 <= e <= 10^9
 * Either b is not zero or e > 0.
 * -10^4 <= be <= 10^4
 */

/************************************************************ C++ ************************************************/

// Approach: Binary exponentiation (divide and conquer) to achieve O(log n) time and space.
// Time Complexity: O(log n) due to halving the exponent in each step.
// Space Complexity: O(log n) for recursion stack depth.
// Notes:
// 1. Binary Exponentiation Theorem: Uses the property x^n = (x^2)^(n/2) to reduce multiplications.
// 2. 32-bit Integer Handling: Casting to long avoids overflow when negating -2^31 (which can't be stored as positive int).
// 3. Long vs Int: Long is used to handle the full range of int exponents, including -2^31, whose negation exceeds int's max value (2^31-1).

/*
 * Notes:
 * 1. Binary Exponentiation Theorem: Reduces multiplications by decomposing the exponent into
 * even/odd cases (e.g., x^n = (x²)^(n/2) or x*(x²)^((n-1)/2)).
 * 2. 32-bit Integer Handling: Casting to `long` prevents overflow when n = -2^31 (smallest int),
 * which cannot be directly negated in int (max int is 2^31-1).
 * 3. Long vs Int: Using `long` ensures sufficient capacity to store -n when n is -2^31, avoiding
 * undefined behavior from integer overflow.
 */
class Solution {
public:
   double solve(double x, long n) {
      // Base case: any number to the power of 0 is 1
      if (n == 0) {
         return 1.0;
      }

      // Handle negative exponent: use reciprocal of x and positive n
      if (n < 0) {
         return solve(1 / x, -n);    // Long avoids overflow for n = -2^31
      }

      // Binary Exponentiation: decompose x^n into (x^2)^(n/2) for even n
      if (n % 2 == 0) {
         return solve(x * x, n / 2);
      }
      // For odd n: x^n = x * (x^2)^((n-1)/2)
      else {
         return x * solve(x * x, (n - 1) / 2);
      }
   }

   double power(double x, int n) {
      // Cast to long to handle integer overflow when n = -2^31
      return solve(x, (long)n);
   }
};

/************************************************************ JAVA ************************************************/

// Approach: Binary exponentiation (divide and conquer) to achieve O(log n) time and space.
// Time Complexity: O(log n) due to halving the exponent in each step.
// Space Complexity: O(log n) for recursion stack depth.
// Notes:
// 1. Binary Exponentiation Theorem: Uses the property x^n = (x^2)^(n/2) to reduce multiplications.
// 2. 32-bit Integer Handling: Casting to long avoids overflow when negating -2^31 (which can't be stored as positive int).
// 3. Long vs Int: Long is used to handle the full range of int exponents, including -2^31, whose negation exceeds int's max value (2^31-1).

/*
 * Notes:
 * 1. Binary Exponentiation Theorem: Reduces multiplications by decomposing the exponent into
 * even/odd cases (e.g., x^n = (x²)^(n/2) or x*(x²)^((n-1)/2)).
 * 2. 32-bit Integer Handling: Casting to `long` prevents overflow when n = -2^31 (smallest int),
 * which cannot be directly negated in int (max int is 2^31-1).
 * 3. Long vs Int: Using `long` ensures sufficient capacity to store -n when n is -2^31, avoiding
 * undefined behavior from integer overflow.
 */
class Solution {
   public double power(double x, int e) {
      return solve(x, (long)e);
   }

   private double solve(double x, long n) {
      // Base case: x^0 = 1
      if (n == 0) {
         return 1.0;
      }
      // Handle negative exponents by using reciprocal of x and positive n
      if (n < 0) {
         return solve(1 / x, -n);    // Cast to long prevents overflow for n = -2^31
      }
      // Binary Exponentiation: decompose x^n into (x^2)^(n/2) for even n
      if (n % 2 == 0) {
         return solve(x * x, n / 2);
      }
      // For odd n: x^n = x * (x^2)^((n-1)/2)
      else {
         return x * solve(x * x, (n - 1) / 2);
      }
   }
}
