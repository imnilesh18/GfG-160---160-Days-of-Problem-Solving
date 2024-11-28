/*
 * Implement Atoi
 *
 * Given a string s, the objective is to convert it into integer format without utilizing any built-in functions. Refer the below steps to know about atoi() function.
 *
 * Cases for atoi() conversion:
 * Skip any leading whitespaces.
 * Check for a sign (‘+’ or ‘-‘), default to positive if no sign is present.
 * Read the integer by ignoring leading zeros until a non-digit character is encountered or end of the string is reached. If no digits are present, return 0.
 * If the integer is greater than 231 – 1, then return 231 – 1 and if the integer is smaller than -231, then return -231.
 *
 * Examples:
 * Input: s = "-123"
 * Output: -123
 * Explanation: It is possible to convert -123 into an integer so we returned in the form of an integer
 *
 * Input: s = "  -"
 * Output: 0
 * Explanation: No digits are present, therefore the returned answer is 0.
 *
 * Input: s = " 1231231231311133"
 * Output: 2147483647
 * Explanation: The converted number will be greater than 231 – 1, therefore print 231 – 1 = 2147483647.
 *
 * Input: s = "-999999999999"
 * Output: -2147483648
 * Explanation: The converted number is smaller than -231, therefore print -231 = -2147483648.
 *
 * Input: s = "  -0012gfg4"
 * Output: -12
 * Explanation: Nothing is read after -12 as a non-digit character ‘g’ was encountered.
 *
 * Constraints:
 * 1 ≤ |s| ≤ 15
 */

/************************************************************ C++ ************************************************/

// T.C: O(n)
// S.C: O(1)
class Solution {
public:
   int myAtoi(char *s){
      if (s == nullptr || *s == '\0') {
         return 0;
      }

      int  i    = 0;
      int  sign = 1;
      long ans  = 0;

      // Skip leading whitespaces
      while (s[i] == ' ') {
         i++;
      }

      // Check for sign
      if (s[i] == '-' || s[i] == '+') {
         sign = (s[i] == '-') ? -1 : 1;
         i++;
      }

      // Process digits
      while (isdigit(s[i])) {
         ans = ans * 10 + (s[i] - '0');

         // Handle overflow
         if (sign == -1 && -ans < INT_MIN) {
            return INT_MIN;
         }
         if (sign == 1 && ans > INT_MAX) {
            return INT_MAX;
         }

         i++;
      }

      return (int)(sign * ans);
   }
};

/************************************************************ JAVA ************************************************/

// T.C: O(n)
// S.C: O(1)
class Solution {
   public int myAtoi(String s){
      if (s == null || s.length() == 0) {
         return 0;
      }

      // Trim leading and trailing spaces
      s = s.trim();
      if (s.length() == 0) {
         return 0;
      }

      int  sign = 1;   // To determine the sign of the number
      int  i    = 0;   // Index to iterate through the string
      long ans  = 0;   // To handle overflow during computation

      // Check for the sign
      if (s.charAt(0) == '-') {
         sign = -1;
         i++;
      } else if (s.charAt(0) == '+') {
         i++;
      }

      // Constants for max and min values
      int MAX = Integer.MAX_VALUE;
      int MIN = Integer.MIN_VALUE;

      // Iterate through the string
      while (i < s.length() && Character.isDigit(s.charAt(i))) {
         ans = ans * 10 + (s.charAt(i) - '0');

         // Check for overflow
         if (sign == -1 && -1 * ans < MIN) {
            return MIN;
         }
         if (sign == 1 && ans > MAX) {
            return MAX;
         }

         i++;
      }

      return (int)(sign * ans);
   }
}
