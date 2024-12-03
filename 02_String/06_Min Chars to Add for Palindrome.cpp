/*
 * Min Chars to Add for Palindrome
 *
 * Given a string s, the task is to find the minimum characters to be added at the front to make the string palindrome.
 * Note: A palindrome string is a sequence of characters that reads the same forward and backward.
 *
 * Examples:
 * Input: s = "abc"
 * Output: 2
 * Explanation: Add 'b' and 'c' at front of above string to make it palindrome : "cbabc"
 *
 * Input: s = "aacecaaaa"
 * Output: 2
 * Explanation: Add 2 a's at front of above string to make it palindrome : "aaaacecaaaa"
 *
 * Constraints:
 * 1 <= s.size() <= 10^6
 */

/************************************************************ C++ ************************************************/

// T.C: O(n)
// S.C: O(n)
class Solution {
public:
   int minChar(string& s){
      string rev = s;

      reverse(rev.begin(), rev.end());
      string      pat = s + "|" + rev;
      int         M   = pat.size();
      int         len = 0; // Length of previous longest prefix suffix
      vector<int> LPS(M);

      LPS[0] = 0;   // LPS[0] is always 0

      int i = 1;
      while (i < M) {
         if (pat[i] == pat[len]) {
            len++;
            LPS[i] = len;
            i++;
         } else {
            if (len != 0) {
               len = LPS[len - 1]; // Backtrack len to the previous LPS position
            } else {
               LPS[i] = 0;         // If no match, set LPS[i] to 0
               i++;
            }
         }
      }

      return s.size() - LPS[M - 1];
   }
};

/************************************************************ JAVA ************************************************/

// T.C: O(n)
// S.C: O(n)
class Solution {
   public static int minChar(String s){
      // Reverse the string
      String rev = new StringBuilder(s).reverse().toString();

      // Concatenate the string and its reverse with a delimiter
      String pat = s + "|" + rev;
      int    M   = pat.length();

      // Initialize LPS (Longest Prefix Suffix) array
      int[] LPS = new int[M];
      int len = 0;   // Length of the previous longest prefix suffix

      // Build the LPS array
      int i = 1;

      while (i < M) {
         if (pat.charAt(i) == pat.charAt(len)) {
            len++;
            LPS[i] = len;
            i++;
         } else {
            if (len != 0) {
               len = LPS[len - 1]; // Backtrack len to the previous LPS position
            } else {
               LPS[i] = 0;         // If no match, set LPS[i] to 0
               i++;
            }
         }
      }

      // Minimum characters to be added at the front
      return s.length() - LPS[M - 1];
   }
}
