/*
 * Decode the string
 *
 * Given an encoded string s, the task is to decode it. The encoding rule is :
 * k[encodedString], where the encodedString inside the square brackets is being repeated exactly k times. Note that k is guaranteed to be a positive integer.
 * Note: The test cases are generated so that the length of the output string will never exceed 105 .
 *
 * Examples:
 *
 * Input: s = "1[b]"
 * Output: "b"
 * Explanation: "b" is present only one time.
 *
 * Input: s = "3[b2[ca]]"
 * Output: "bcacabcacabcaca"
 * Explanation:
 * 1. Inner substring “2[ca]” breakdown into “caca”.
 * 2. Now, new string becomes “3[bcaca]”
 * 3. Similarly “3[bcaca]” becomes “bcacabcacabcaca ” which is final result.
 *
 * Constraints:
 * 1 ≤ |s| ≤ 10^5
 */

/************************************************************ C++ ************************************************/

// Approach: Use two stacks (one for numbers and one for strings) to iteratively build the decoded string without performing unnecessary reversals.
// TC: O(n) - Each character in the string is processed once.
// SC: O(n) - In the worst case, the stacks store a significant portion of the input.
class Solution {
public:
   string decodedString(string&s) {
      stack<int>    numStack;        // Stack to store multipliers.
      stack<string> strStack;        // Stack to store the strings built so far.
      string        current;         // Current string being built.
      int           k = 0;           // Current multiplier.

      for (char c : s) {
         if (isdigit(c)) {
            // Build the multiplier k (handles multiple digits).
            k = k * 10 + (c - '0');
         } else if (c == '[') {
            // Push the current multiplier and string onto their stacks.
            numStack.push(k);
            strStack.push(current);
            // Reset k and current for the new substring.
            k       = 0;
            current = "";
         } else if (c == ']') {
            // Pop the last multiplier and previous string.
            int repeatTimes = numStack.top();
            numStack.pop();
            string decoded = strStack.top();
            strStack.pop();
            // Append the current substring repeated repeatTimes times.
            while (repeatTimes--) {
               decoded += current;
            }
            current = decoded;
         } else {
            // Append the current character to the current substring.
            current.push_back(c);
         }
      }
      return current;
   }
};

/*
 * Dry Run:
 * Example: s = "3[b2[ca]]"
 *
 * Iteration 1: c = '3'
 *   - It's a digit, update k: k = 3.
 *
 * Iteration 2: c = '['
 *   - Push k (3) onto numStack, push current (empty) onto strStack.
 *   - Reset k to 0 and current to "".
 *
 * Iteration 3: c = 'b'
 *   - Append 'b' to current, current = "b".
 *
 * Iteration 4: c = '2'
 *   - It's a digit, update k: k = 2.
 *
 * Iteration 5: c = '['
 *   - Push k (2) onto numStack, push current ("b") onto strStack.
 *   - Reset k to 0 and current to "".
 *
 * Iteration 6: c = 'c'
 *   - Append 'c' to current, current = "c".
 *
 * Iteration 7: c = 'a'
 *   - Append 'a' to current, current = "ca".
 *
 * Iteration 8: c = ']'
 *   - Pop numStack (2) and strStack ("b").
 *   - Repeat current ("ca") 2 times: "caca".
 *   - Set current = "b" + "caca" = "bcaca".
 *
 * Iteration 9: c = ']'
 *   - Pop numStack (3) and strStack (empty string).
 *   - Repeat current ("bcaca") 3 times: "bcaca" + "bcaca" + "bcaca" = "bcacabcacabcaca".
 *   - Set current = "bcacabcacabcaca".
 *
 * Final output: "bcacabcacabcaca"
 */

/************************************************************ JAVA ************************************************/

// Approach: Use two stacks to store multipliers and previously built strings; iteratively build the decoded string without extra reversals.
// TC: O(n) - Each character in the string is processed once.
// SC: O(n) - In the worst case, the stacks store a significant portion of the input string.
class Solution {
   static String decodeString(String s) {
      Stack<Integer> numStack = new Stack<>();      // Stack to store multipliers.
      Stack<String>  strStack = new Stack<>();      // Stack to store the strings built so far.
      String         current  = "";                 // Current string being built.
      int            k        = 0;                  // Current multiplier.

      for (char c : s.toCharArray()) {
         if (Character.isDigit(c)) {
            // Build the multiplier k (handles multiple digits).
            k = k * 10 + (c - '0');
         } else if (c == '[') {
            // Push the current multiplier and string onto their stacks.
            numStack.push(k);
            strStack.push(current);
            // Reset k and current for the new substring.
            k       = 0;
            current = "";
         } else if (c == ']') {
            // Pop the last multiplier and previous string.
            int           repeatTimes = numStack.pop();
            StringBuilder decoded     = new StringBuilder(strStack.pop());
            // Append the current substring repeated repeatTimes times.
            for (int i = 0; i < repeatTimes; i++) {
               decoded.append(current);
            }
            current = decoded.toString();
         } else {
            // Append the current character to the current substring.
            current += c;
         }
      }
      return current;
   }
}

/*
 * Dry Run:
 * Example: s = "3[b2[ca]]"
 *
 * Iteration 1: c = '3'
 *   - It's a digit, update k: k = 3.
 *
 * Iteration 2: c = '['
 *   - Push k (3) onto numStack, push current (empty) onto strStack.
 *   - Reset k to 0 and current to "".
 *
 * Iteration 3: c = 'b'
 *   - Append 'b' to current, current becomes "b".
 *
 * Iteration 4: c = '2'
 *   - It's a digit, update k: k = 2.
 *
 * Iteration 5: c = '['
 *   - Push k (2) onto numStack, push current ("b") onto strStack.
 *   - Reset k to 0 and current to "".
 *
 * Iteration 6: c = 'c'
 *   - Append 'c' to current, current becomes "c".
 *
 * Iteration 7: c = 'a'
 *   - Append 'a' to current, current becomes "ca".
 *
 * Iteration 8: c = ']'
 *   - Pop numStack (2) and strStack ("b").
 *   - Repeat current ("ca") 2 times: "caca".
 *   - Set current = "b" + "caca" = "bcaca".
 *
 * Iteration 9: c = ']'
 *   - Pop numStack (3) and strStack (empty string).
 *   - Repeat current ("bcaca") 3 times: "bcacabcacabcaca".
 *   - Set current = "bcacabcacabcaca".
 *
 * Final output: "bcacabcacabcaca"
 */
