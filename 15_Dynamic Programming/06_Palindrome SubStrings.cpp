/*
 * Palindrome SubStrings
 *
 * Given a string s, count all palindromic sub-strings present in the string. The length of the palindromic sub-string must be greater than or equal to 2.
 *
 * Examples
 *
 * Input: s = "abaab"
 * Output: 3
 * Explanation: All palindromic substrings are : "aba" , "aa" , "baab".
 *
 * Input: s = "aaa"
 * Output: 3
 * Explanation: All palindromic substrings are : "aa", "aa", "aaa".
 *
 * Input: s = "abbaeae"
 * Output: 4
 * Explanation: All palindromic substrings are : "bb" , "abba" , "aea", "eae".
 *
 * Constraints:
 * 2 ≤ s.size() ≤ 10^3
 * string contains only lowercase english characters
 */

/************************************************************ C++ ************************************************/

// Approach: Expand around center for each index (for odd and even length palindromes)
// Time Complexity: O(n^2) - In worst case, each center expands across the string
// Space Complexity: O(1) - Only a few extra variables are used
class Solution {
public:
    int countPS(string& s) {
        int n     = s.size();
        int count = 0;

        // Count odd length palindromic substrings (using each character as center)
        for (int i = 0; i < n; i++) {
            int left  = i - 1;
            int right = i + 1;
            while (left >= 0 && right < n && s[left] == s[right]) {
                count++;         // Found a palindrome (length >= 3)
                left--;          // Expand to the left
                right++;         // Expand to the right
            }
        }

        // Count even length palindromic substrings (using adjacent characters as center)
        for (int i = 0; i < n; i++) {
            int left  = i;
            int right = i + 1;
            while (left >= 0 && right < n && s[left] == s[right]) {
                count++;         // Found a palindrome (length 2 or more)
                left--;          // Expand to the left
                right++;         // Expand to the right
            }
        }
        return count;
    }
};

/*
 * Dry Run:
 * Input: s = "abbaeae"
 * Odd Length Check:
 * i = 0: center 'a' -> left = -1, right = 1 => no expansion.
 * i = 1: center 'b' -> left = 0 ('a'), right = 2 ('b') => not equal.
 * i = 2: center 'b' -> left = 1 ('b'), right = 3 ('a') => not equal.
 * i = 3: center 'a' -> left = 2 ('b'), right = 4 ('e') => not equal.
 * i = 4: center 'e' -> left = 3 ('a'), right = 5 ('a') => equal, count becomes 1.
 *       Expand: left = 2 ('b'), right = 6 ('e') => not equal.
 * i = 5: center 'a' -> left = 4 ('e'), right = 6 ('e') => equal, count becomes 2.
 *       Expand: left = 3 ('a'), right = 7 (out-of-bound) => stop.
 * i = 6: center 'e' -> left = 5 ('a'), right = 7 => stop.
 * Even Length Check:
 * i = 0: compare s[0] ('a') with s[1] ('b') => not equal.
 * i = 1: compare s[1] ('b') with s[2] ('b') => equal, count becomes 3.
 *       Expand: left = 0 ('a'), right = 3 ('a') => equal, count becomes 4.
 *       Expand: left = -1, right = 4 => stop.
 * i = 2: compare s[2] ('b') with s[3] ('a') => not equal.
 * i = 3: compare s[3] ('a') with s[4] ('e') => not equal.
 * i = 4: compare s[4] ('e') with s[5] ('a') => not equal.
 * i = 5: compare s[5] ('a') with s[6] ('e') => not equal.
 * Total palindromic substrings (length >= 2): 4.
 */

/************************************************************ JAVA ************************************************/

// Approach: Expand around center for each index (for odd and even length palindromes)
// Time Complexity: O(n^2) - In worst case, each center expands across the string
// Space Complexity: O(1) - Only a few extra variables are used
class Solution {
    public int countPS(String s) {
        int n     = s.length();
        int count = 0;

        // Count odd length palindromic substrings (using each character as center)
        for (int i = 0; i < n; i++) {
            int left  = i - 1;
            int right = i + 1;
            while (left >= 0 && right < n && s.charAt(left) == s.charAt(right)) {
                count++;       // Found a palindrome (length >= 3)
                left--;        // Expand to the left
                right++;       // Expand to the right
            }
        }

        // Count even length palindromic substrings (using adjacent characters as center)
        for (int i = 0; i < n; i++) {
            int left  = i;
            int right = i + 1;
            while (left >= 0 && right < n && s.charAt(left) == s.charAt(right)) {
                count++;       // Found a palindrome (length 2 or more)
                left--;        // Expand to the left
                right++;       // Expand to the right
            }
        }
        return count;
    }
}

/*
 * Dry Run:
 * Input: s = "abbaeae"
 * Odd Length Check:
 * i = 0: center 'a' -> left = -1, right = 1 => no expansion.
 * i = 1: center 'b' -> left = 0 ('a'), right = 2 ('b') => not equal.
 * i = 2: center 'b' -> left = 1 ('b'), right = 3 ('a') => not equal.
 * i = 3: center 'a' -> left = 2 ('b'), right = 4 ('e') => not equal.
 * i = 4: center 'e' -> left = 3 ('a'), right = 5 ('a') => equal, count becomes 1.
 *       Expand: left = 2 ('b'), right = 6 ('e') => not equal.
 * i = 5: center 'a' -> left = 4 ('e'), right = 6 ('e') => equal, count becomes 2.
 *       Expand: left = 3 ('a'), right = 7 (out-of-bound) => stop.
 * i = 6: center 'e' -> left = 5 ('a'), right = 7 => stop.
 * Even Length Check:
 * i = 0: compare s.charAt(0) ('a') with s.charAt(1) ('b') => not equal.
 * i = 1: compare s.charAt(1) ('b') with s.charAt(2) ('b') => equal, count becomes 3.
 *       Expand: left = 0 ('a'), right = 3 ('a') => equal, count becomes 4.
 *       Expand: left = -1, right = 4 => stop.
 * i = 2: compare s.charAt(2) ('b') with s.charAt(3) ('a') => not equal.
 * i = 3: compare s.charAt(3) ('a') with s.charAt(4) ('e') => not equal.
 * i = 4: compare s.charAt(4) ('e') with s.charAt(5) ('a') => not equal.
 * i = 5: compare s.charAt(5) ('a') with s.charAt(6) ('e') => not equal.
 * Total palindromic substrings (length >= 2): 4.
 */
