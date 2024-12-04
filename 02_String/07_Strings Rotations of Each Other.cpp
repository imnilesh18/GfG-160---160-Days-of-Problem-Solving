/*
 * Strings Rotations of Each Other
 *
 * You are given two strings of equal lengths, s1 and s2. The task is to check if s2 is a rotated version of the string s1.
 * Note: The characters in the strings are in lowercase.
 *
 * Examples :
 * Input: s1 = "abcd", s2 = "cdab"
 * Output: true
 * Explanation: After 2 right rotations, s1 will become equal to s2.
 *
 * Input: s1 = "aab", s2 = "aba"
 * Output: true
 * Explanation: After 1 left rotation, s1 will become equal to s2.
 *
 * Input: s1 = "abcd", s2 = "acbd"
 * Output: false
 * Explanation: Strings are not rotations of each other.
 *
 * Constraints:
 * 1 <= s1.size(), s2.size() <= 10^5
 */

/************************************************************ C++ ************************************************/

// Approach 1: find
// TLE:
// T.C: O(n)
// S.C: O(n)
class Solution {
public:
   // Function to check if two strings are rotations of each other or not.
   bool areRotations(string&s1, string&s2){
      // Check lengths and find if s2 is a substring of s1 + s1
      return s1.size() == s2.size() && (s1 + s1).find(s2) != string::npos;
   }
};

/*
 * The goal is to check if s2 is a rotated version of s1. The key insight is that a rotated string of s1 will always appear as a substring of the concatenated string s1 + s1.
 *
 * For example:
 * If s1 = "abcd" and s2 = "cdab", then s1 + s1 = "abcdabcd". Here, s2 ("cdab") is indeed a substring of "abcdabcd".
 * However, if s2 = "acbd", it cannot be a substring of "abcdabcd" because the rotation doesn't match.
 * Steps:
 * Check Length: If s1 and s2 are not of the same length, they cannot be rotations of each other.
 * Concatenate s1 with Itself: Form a new string, s1 + s1. This ensures that all possible rotations of s1 are covered.
 * Find Substring: Check if s2 exists as a substring within s1 + s1.
 */

// Approach 2: KMP Algorithm
// T.C : O(m+n)
// S.C : O(m) where m is the length of pattern
class Solution {
public:
   // Function to compute the Longest Prefix Suffix (LPS) array
   void computeLPS(const string& pat, vector<int>& LPS){
      int M   = pat.size();
      int len = 0;  // Length of the previous longest prefix suffix

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
   }

   // Function to check if two strings are rotations of each other or not
   bool areRotations(string&s1, string&s2){
      if (s1.size() != s2.size()) {
         return false;
      }

      string txt = s1 + s1;
      string pat = s2;

      int N = txt.size();
      int M = pat.size();

      // Create LPS array and preprocess the pattern
      vector<int> LPS(M);
      computeLPS(pat, LPS);

      int i = 0;   // Index for txt[]
      int j = 0;   // Index for pat[]

      while (i < N) {
         if (txt[i] == pat[j]) {
            i++;
            j++;
         }

         if (j == M) {
            // Pattern found
            return true;
         } else if (i < N && txt[i] != pat[j]) {
            // Mismatch after j matches
            if (j != 0) {
               j = LPS[j - 1]; // Fall back to the previous LPS index
            } else {
               i++;            // If no matches, move to the next character in txt
            }
         }
      }

      return false;
   }
};

/************************************************************ JAVA ************************************************/

// Approach 1: contains
// TLE:
// T.C: O(n)
// S.C: O(n)
class Solution {
   // Function to check if two strings are rotations of each other or not.
   public static boolean areRotations(String s1, String s2){
      // Check if lengths are equal and s2 is a substring of s1 + s1
      return s1.length() == s2.length() && (s1 + s1).contains(s2);
   }
}

/*
 * The goal is to check if s2 is a rotated version of s1. The key insight is that a rotated string of s1 will always appear as a substring of the concatenated string s1 + s1.
 *
 * For example:
 * If s1 = "abcd" and s2 = "cdab", then s1 + s1 = "abcdabcd". Here, s2 ("cdab") is indeed a substring of "abcdabcd".
 * However, if s2 = "acbd", it cannot be a substring of "abcdabcd" because the rotation doesn't match.
 * Steps:
 * Check Length: If s1 and s2 are not of the same length, they cannot be rotations of each other.
 * Concatenate s1 with Itself: Form a new string, s1 + s1. This ensures that all possible rotations of s1 are covered.
 * Find Substring: Check if s2 exists as a substring within s1 + s1.
 */

// Approach 2: KMP Algorithm
// T.C : O(m+n)
// S.C : O(m) where m is the length of pattern
class Solution {
   // Function to compute the Longest Prefix Suffix (LPS) array
   public void computeLPS(String pat, int[] LPS){
      int M   = pat.length();
      int len = 0;  // Length of the previous longest prefix suffix

      LPS[0] = 0;   // LPS[0] is always 0
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
   }

   // Function to check if two strings are rotations of each other or not
   public boolean areRotations(String s1, String s2){
      if (s1.length() != s2.length()) {
         return false;
      }

      String txt = s1 + s1;   // Concatenate s1 with itself
      String pat = s2;

      int N = txt.length();
      int M = pat.length();

      // Create LPS array and preprocess the pattern
      int[] LPS = new int[M];
      computeLPS(pat, LPS);

      int i = 0;   // Index for txt[]
      int j = 0;   // Index for pat[]

      while (i < N) {
         if (txt.charAt(i) == pat.charAt(j)) {
            i++;
            j++;
         }

         if (j == M) {
            // Pattern found
            return true;
         } else if (i < N && txt.charAt(i) != pat.charAt(j)) {
            // Mismatch after j matches
            if (j != 0) {
               j = LPS[j - 1]; // Fall back to the previous LPS index
            } else {
               i++;            // If no matches, move to the next character in txt
            }
         }
      }

      return false;   // Pattern not found
   }
}
