/*
 * Longest substring with distinct characters
 *
 * Given a string s, find the length of the longest substring with all distinct characters.
 *
 * Examples:
 *
 * Input: s = "geeksforgeeks"
 * Output: 7
 * Explanation: "eksforg" is the longest substring with all distinct characters.
 *
 * Input: s = "aaa"
 * Output: 1
 * Explanation: "a" is the longest substring with all distinct characters.
 *
 * Input: s = "abcdefabcbb"
 * Output: 6
 * Explanation: The longest substring with all distinct characters is "abcdef", which has a length of 6.
 *
 * Constraints:
 * 1<= s.size()<=3*10^4
 * All the characters are in lowercase.
 */

/************************************************************ C++ ************************************************/

// Approach: Use sliding window technique with a vector to track last occurrence of each character, moving start pointer when duplicates are found.
// Time Complexity: O(n) where n is length of string as we traverse the string once.
// Space Complexity: O(1) as we use fixed size vector of 26 for lowercase letters.
class Solution {
public:
   int longestUniqueSubstr(string&s){
      // Create a vector to store the last index of each character (initialized with -1)
      vector<int> count(26, -1);
      int         n = s.size();

      // i: start of current window, j: end of current window
      int i = 0;
      int j = 0;

      // Store the length of longest substring with unique characters
      int result = 1;

      while (j < n) {
         // If current character was seen before, move start pointer to
         // position after the last occurrence of current character
         if (count[s[j] - 'a'] != -1) {
            i = max(i, count[s[j] - 'a'] + 1);
         }

         // Update result with max length of current window
         result = max(result, j - i + 1);

         // Update last seen index of current character
         count[s[j] - 'a'] = j;

         j++;
      }

      return result;
   }
};

/************************************************************ JAVA ************************************************/

// Approach: Use sliding window technique with a vector to track last occurrence of each character, moving start pointer when duplicates are found.
// Time Complexity: O(n) where n is length of string as we traverse the string once.
// Space Complexity: O(1) as we use fixed size vector of 26 for lowercase letters.
class Solution {
   public int longestUniqueSubstr(String s){
      // Create an array to store the last index of each character (initialized with -1)
      int[] count = new int[26];

      for (int k = 0; k < 26; k++) {
         count[k] = -1;
      }

      int n = s.length();

      // i: start of current window, j: end of current window
      int i = 0;
      int j = 0;

      // Store the length of longest substring with unique characters
      int result = 1;

      while (j < n) {
         // If current character was seen before, move start pointer to
         // position after the last occurrence of current character
         if (count[s.charAt(j) - 'a'] != -1) {
            i = Math.max(i, count[s.charAt(j) - 'a'] + 1);
         }

         // Update result with max length of current window
         result = Math.max(result, j - i + 1);

         // Update last seen index of current character
         count[s.charAt(j) - 'a'] = j;

         j++;
      }

      return result;
   }
}
