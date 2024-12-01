/*
 * Non Repeating Character
 *
 * Given a string s consisting of lowercase Latin Letters. Return the first non-repeating character in s. If there is no non-repeating character, return '$'.
 * Note: When you return '$' driver code will output -1.
 *
 * Examples:
 * Input: s = "geeksforgeeks"
 * Output: 'f'
 * Explanation: In the given string, 'f' is the first character in the string which does not repeat.
 *
 * Input: s = "racecar"
 * Output: 'e'
 * Explanation: In the given string, 'e' is the only character in the string which does not repeat.
 *
 * Input: s = "aabbccc"
 * Output: -1
 * Explanation: All the characters in the given string are repeating.
 *
 * Constraints:
 * 1 <= s.size() <= 10^5
 */

/************************************************************ C++ ************************************************/

// T.C: O(n) traverse the string twice: once to build the frequency map and once to find the non-repeating character.
// S.C: O(1) because there are at most 26 lowercase Latin letters
class Solution {
public:
   // Function to find the first non-repeating character in a string.
   char nonRepeatingChar(string&s){
      unordered_map<char, int> freqMap;

      // Step 1: Count frequency of each character.
      for (char ch : s) {
         freqMap[ch]++;
      }

      // Step 2: Find the first non-repeating character.
      for (char ch : s) {
         if (freqMap[ch] == 1) {
            return ch;
         }
      }

      // Step 3: If no non-repeating character is found, return '$'.
      return '$';
   }
};

/************************************************************ JAVA ************************************************/

// T.C: O(n) traverse the string twice: once to build the frequency map and once to find the non-repeating character.
// S.C: O(1) because there are at most 26 lowercase Latin letters
class Solution {
   // Function to find the first non-repeating character in a string.
   static char nonRepeatingChar(String s){
      // Step 1: Create a HashMap to store the frequency of each character.
      HashMap<Character, Integer> freqMap = new HashMap<>();

      // Step 2: Count frequency of each character.
      for (char ch : s.toCharArray()) {
         freqMap.put(ch, freqMap.getOrDefault(ch, 0) + 1);
      }

      // Step 3: Find the first non-repeating character.
      for (char ch : s.toCharArray()) {
         if (freqMap.get(ch) == 1) {
            return ch;
         }
      }

      // Step 4: If no non-repeating character is found, return '$'.
      return '$';
   }
}
