/*
 * Anagram
 *
 * Given two strings s1 and s2 consisting of lowercase characters. The task is to check whether two given strings are an anagram of each other or not. An anagram of a string is another string that contains the same characters, only the order of characters can be different. For example, act and tac are an anagram of each other. Strings s1 and s2 can only contain lowercase alphabets.
 *
 * Note: You can assume both the strings s1 & s2 are non-empty.
 *
 * Examples :
 * Input: s1 = "geeks", s2 = "kseeg"
 * Output: true
 * Explanation: Both the string have same characters with same frequency. So, they are anagrams.
 *
 * Input: s1 = "allergy", s2 = "allergic"
 * Output: false
 * Explanation: Characters in both the strings are not same, so they are not anagrams.
 *
 * Input: s1 = "g", s2 = "g"
 * Output: true
 * Explanation: Character in both the strings are same, so they are anagrams.
 *
 * Constraints:
 * 1 ≤ s1.size(), s2.size() ≤ 10^5
 */

/************************************************************ C++ ************************************************/

// Approach 1 : Sorting
// T.C: O(nlogn)
// S.C: O(1)
class Solution {
public:
   // Function is to check whether two strings are anagram of each other or not.
   bool areAnagrams(string& s1, string& s2){
      int n1 = s1.length();
      int n2 = s2.length();

      if (n1 != n2) {
         return false;
      }

      sort(s1.begin(), s1.end());
      sort(s2.begin(), s2.end());

      return s1 == s2;
   }
};

// Approach 2: Frequency Count
// T.C: O(n)
// S.C: O(26) ~ O(1)
class Solution {
public:
   // Function is to check whether two strings are anagram of each other or not.
   bool areAnagrams(string& s1, string& s2){
      // If lengths are different, they cannot be anagrams
      if (s1.length() != s2.length()) {
         return false;
      }

      // Frequency array for 26 lowercase English alphabets
      vector<int> frequency(26, 0);

      // Count the frequency of characters in s1 and s2
      for (size_t i = 0; i < s1.length(); i++) {
         frequency[s1[i] - 'a']++; // Increment for s1
         frequency[s2[i] - 'a']--; // Decrement for s2
      }

      // Check if all frequencies are zero
      for (int count : frequency) {
         if (count != 0) {
            return false; // If any frequency is non-zero, not an anagram
         }
      }

      return true; // All frequencies matched, it's an anagram
   }
};


/************************************************************ JAVA ************************************************/

// Approach 1 : Sorting
// T.C: O(nlogn)
// S.C: O(n) Due to extra Char Array
class Solution {
   // Function is to check whether two strings are anagram of each other or not.
   public static boolean areAnagrams(String s1, String s2){
      // Check if lengths are different
      if (s1.length() != s2.length()) {
         return false;
      }

      // Convert strings to character arrays
      char[] arr1 = s1.toCharArray();
      char[] arr2 = s2.toCharArray();

      // Sort both character arrays
      Arrays.sort(arr1);
      Arrays.sort(arr2);

      // Compare sorted arrays
      return Arrays.equals(arr1, arr2);
   }
}

// Approach 2: Frequency Count
// T.C: O(n)
// S.C: O(26) ~ O(1)
class Solution {
   // Function is to check whether two strings are anagram of each other or not.
   public static boolean areAnagrams(String s1, String s2){
      // If lengths are different, they cannot be anagrams
      if (s1.length() != s2.length()) {
         return false;
      }

      // Frequency array for 26 lowercase English alphabets
      int[] frequency = new int[26];

      // Count the frequency of characters in s1 and s2
      for (int i = 0; i < s1.length(); i++) {
         frequency[s1.charAt(i) - 'a']++;    // Increment for s1
         frequency[s2.charAt(i) - 'a']--;    // Decrement for s2
      }

      // Check if all frequencies are zero
      for (int count : frequency) {
         if (count != 0) {
            return false;     // If any frequency is non-zero, not an anagram
         }
      }

      return true;   // All frequencies matched, it's an anagram
   }
}
