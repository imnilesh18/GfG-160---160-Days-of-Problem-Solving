/*
 * Search Pattern (KMP-Algorithm)
 *
 * Given two strings, one is a text string txt and the other is a pattern string pat. The task is to print the indexes of all the occurrences of the pattern string in the text string. Use 0-based indexing while returning the indices.
 * Note: Return an empty list in case of no occurrences of pattern.
 *
 * Examples :
 *
 * Input: txt = "abcab", pat = "ab"
 * Output: [0, 3]
 * Explanation: The string "ab" occurs twice in txt, one starts at index 0 and the other at index 3.
 * Input: txt = "abesdu", pat = "edu"
 * Output: []
 * Explanation: There's no substring "edu" present in txt.
 * Input: txt = "aabaacaadaabaaba", pat = "aaba"
 * Output: [0, 9, 12]
 * Explanation:
 *
 * Constraints:
 * 1 ≤ txt.size() ≤ 10^6
 * 1 ≤ pat.size() < txt.size()
 * Both the strings consist of lowercase English alphabets.
 */


/************************************************************ C++ ************************************************/

// Approach (KMP Algorithm)
// T.C : O(m+n)
// S.C : O(m) where m is the length of pattern
class Solution {
public:
   // Function to compute the Longest Prefix Suffix (LPS) array
   void computeLPS(const string& pat, vector<int>& LPS){
      int M   = pat.size();
      int len = 0;   // Length of previous longest prefix suffix

      LPS[0] = 0;    // LPS[0] is always 0

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

   // Function to search for pattern in text using the KMP algorithm
   vector<int> search(string& pat, string& txt){
      vector<int> result;
      int         N = txt.size();
      int         M = pat.size();

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
            // Pattern found, add the starting index (0-based index)
            result.push_back(i - j);
            j = LPS[j - 1];     // Get the next position from LPS array
         } else if (i < N && txt[i] != pat[j]) {
            // Mismatch after j matches
            if (j != 0) {
               j = LPS[j - 1]; // Fall back to the previous LPS index
            } else {
               i++;            // If no matches, just move to the next character in txt
            }
         }
      }

      return result;
   }
};

/************************************************************ JAVA ************************************************/

// Approach (KMP Algorithm)
// T.C : O(m+n)
// S.C : O(m) where m is the length of pattern
class Solution {
   // Method to compute the Longest Prefix Suffix (LPS) array
   void computeLPS(String pat, int[] LPS, int M){
      int len = 0;

      LPS[0] = 0;   // LPS[0] is always 0

      int i = 1;
      while (i < M) {
         if (pat.charAt(i) == pat.charAt(len)) {
            len++;
            LPS[i] = len;
            i++;
         } else {
            if (len != 0) {
               len = LPS[len - 1]; // Backtrack len to previous LPS position
            } else {
               LPS[i] = 0;         // If no match, set LPS[i] to 0
               i++;
            }
         }
      }
   }

   // Method to search for pattern in text using KMP algorithm
   ArrayList<Integer> search(String pat, String txt){
      ArrayList<Integer> result = new ArrayList<>();
      int N = txt.length();
      int M = pat.length();

      // Create LPS array and preprocess the pattern
      int[] LPS = new int[M];

      computeLPS(pat, LPS, M);

      int i = 0;   // Index for txt[]
      int j = 0;   // Index for pat[]

      while (i < N) {
         if (txt.charAt(i) == pat.charAt(j)) {
            i++;
            j++;
         }

         if (j == M) {
            // Pattern found, add the starting index (1-based index)
            result.add(i - j);
            j = LPS[j - 1];     // Get the next position from LPS array
         } else if (i < N && txt.charAt(i) != pat.charAt(j)) {
            // Mismatch after j matches
            if (j != 0) {
               j = LPS[j - 1]; // Fall back to the previous LPS index
            } else {
               i++;            // If no matches, just move to the next character in txt
            }
         }
      }
      return result;
   }
}
