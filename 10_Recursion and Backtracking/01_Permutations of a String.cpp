/*
 * Permutations of a String
 *
 * Given a string s, which may contain duplicate characters, your task is to generate and return an array of all unique permutations of the string. You can return your answer in any order.
 *
 * Examples:
 *
 * Input: s = "ABC"
 * Output: ["ABC", "ACB", "BAC", "BCA", "CAB", "CBA"]
 * Explanation: Given string ABC has 6 unique permutations.
 *
 * Input: s = "ABSG"
 * Output: ["ABGS", "ABSG", "AGBS", "AGSB", "ASBG", "ASGB", "BAGS", "BASG", "BGAS", "BGSA", "BSAG", "BSGA", "GABS", "GASB", "GBAS", "GBSA", "GSAB", "GSBA", "SABG", "SAGB", "SBAG", "SBGA", "SGAB", "SGBA"]
 * Explanation: Given string ABSG has 24 unique permutations.
 *
 * Input: s = "AAA"
 * Output: ["AAA"]
 * Explanation: No other unique permutations can be formed as all the characters are same.
 *
 * Constraints:
 * 1 <= s.size() <= 9
 * s contains only Uppercase english alphabets
 */

/************************************************************ C++ ************************************************/

// Approach: Backtracking with a frequency map to track character counts, ensuring no duplicates.
// Time Complexity (TC): O(n * n!) - Worst case for unique characters (n! permutations, each taking O(n) time to build).
// Space Complexity (SC): O(n) - Recursion stack depth and temporary string storage (excluding output).
class Solution {
public:
   int n;                           // Length of the input string
   vector<string> result;           // Stores all unique permutations

   // Backtracking function to generate permutations
   void backtrack(string&temp, unordered_map<char, int>&mp) {
      // Base case: permutation is complete
      if (temp.size() == n) {
         result.push_back(temp);
         return;
      }

      // Iterate through each character in the frequency map
      for (auto& pair : mp) {
         char ch    = pair.first;   // Current character
         int& count = pair.second;  // Remaining count of the character

         if (count <= 0) {
            continue;               // Skip if character is exhausted
         }
         temp.push_back(ch);        // Add character to current permutation
         count--;                   // Decrement remaining count

         backtrack(temp, mp);       // Recurse to build next position

         temp.pop_back();           // Remove character (backtrack)
         count++;                   // Restore count (backtrack)
      }
   }

   vector<string> findPermutation(string&s) {
      n = s.length();
      unordered_map<char, int> mp;   // Frequency map for characters

      // Populate frequency map
      for (char ch : s) {
         mp[ch]++;
      }

      string temp;                  // Temporary storage for current permutation
      backtrack(temp, mp);          // Start backtracking with empty temp

      return result;                // Return all unique permutations
   }
};

/************************************************************ JAVA ************************************************/

// Approach: Backtracking with frequency map to handle duplicates by tracking character usage.
// Time Complexity: O(n * n!) - n! permutations (worst case for unique chars), each taking O(n) time.
// Space Complexity: O(n) - Recursion depth and temporary storage, plus frequency map overhead.
class Solution {
   private void backtrack(StringBuilder temp, HashMap<Character, Integer> freqMap, ArrayList<String> result, int targetLength) {
      // Base case: permutation is complete
      if (temp.length() == targetLength) {
         result.add(temp.toString());
         return;
      }

      // Try each character in frequency map
      for (Map.Entry<Character, Integer> entry : freqMap.entrySet()) {
         char ch    = entry.getKey();
         int  count = entry.getValue();

         // Skip if character is exhausted
         if (count == 0) {
            continue;
         }

         // Decrease count and add character to permutation
         entry.setValue(count - 1);
         temp.append(ch);

         // Recurse to build next position
         backtrack(temp, freqMap, result, targetLength);

         // Backtrack: restore character and count
         temp.deleteCharAt(temp.length() - 1);
         entry.setValue(count);
      }
   }

   public ArrayList<String> findPermutation(String s) {
      ArrayList<String>           result  = new ArrayList<>();
      HashMap<Character, Integer> freqMap = new HashMap<>();
      int n = s.length();

      // Populate frequency map with character counts
      for (char ch : s.toCharArray()) {
         freqMap.put(ch, freqMap.getOrDefault(ch, 0) + 1);
      }

      // Start backtracking with empty temporary string
      backtrack(new StringBuilder(), freqMap, result, n);
      return result;
   }
}
