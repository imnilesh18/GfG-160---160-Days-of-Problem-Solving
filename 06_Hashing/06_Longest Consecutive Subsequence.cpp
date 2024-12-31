/*
 * Longest Consecutive Subsequence
 *
 * Given an array arr[] of non - negative integers.Find the length of the longest sub - sequence such that elements in the subsequence are consecutive integers, the consecutive numbers can be in any order.
 *
 * Examples:
 *
 * Input: arr[] = [2, 6, 1, 9, 4, 5, 3]
 * Output : 6
 * Explanation: The consecutive numbers here are 1, 2, 3, 4, 5, 6. These 6 numbers form the longest consecutive subsquence.
 *
 * Input: arr[] = [1, 9, 3, 10, 4, 20, 2]
 * Output : 4
 * Explanation : 1, 2, 3, 4 is the longest consecutive subsequence.
 *
 * Input: arr[] = [15, 13, 12, 14, 11, 10, 9]
 * Output : 7
 * Explanation: The longest consecutive subsequence is 9, 10, 11, 12, 13, 14, 15, which has a length of 7.
 *
 * Constraints:
 * 1 <= arr.size() <= 10 ^ 5
 * 0 <= arr[i] <= 10 ^ 5
 */

/************************************************************ C++ ************************************************/

// Approach: Store numbers in HashSet, iterate through each number and if it's a sequence start (no n-1 exists), count consecutive numbers until sequence breaks.
// Time Complexity: O(n) since we iterate through array once for set creation and each number is at most visited twice (as current and as next of another).
// Space Complexity: O(n) to store n numbers in the unordered_set.
class Solution {
public:
   // Function to return length of longest subsequence of consecutive integers.
   int longestConsecutive(vector<int>& arr){
      int n = arr.size();

      // Store all numbers in a HashSet for O(1) lookup
      // This removes duplicates automatically
      unordered_set<int> st(begin(arr), end(arr));

      int result = 1;    // Initialize result to 1 as minimum length possible

      // Iterate through each number in the set
      for (auto it : st) {
         // Check if this number can be the start of a sequence
         // If there's no number (it-1) in set, then 'it' is the start of a sequence
         if (st.find(it - 1) == st.end()) {
            int cnt = 1;      // Initialize current sequence length to 1
            int x   = it;     // Store current number to check for consecutive elements

            // Keep checking for next consecutive numbers (x+1)
            // While we keep finding consecutive numbers, increment length
            while (st.find(x + 1) != st.end()) {
               x   = x + 1;         // Move to next number
               cnt = cnt + 1;       // Increment sequence length
            }

            // Update result with maximum length found so far
            result = max(result, cnt);
         }
      }
      return result;
   }
};

/************************************************************ JAVA ************************************************/

// Approach: Create HashSet of array elements, then for each number that can be sequence start (no num-1 exists), count consecutive numbers until sequence breaks.
// Time Complexity: O(n) since we iterate through array once for HashSet creation and each number is checked at most twice.
// Space Complexity: O(n) to store all array elements in the HashSet.
class Solution {
   // Function to return length of longest subsequence of consecutive integers.
   public int longestConsecutive(int[] arr){
      // Store numbers in HashSet for O(1) lookup
      HashSet<Integer> st = new HashSet<>();

      for (int num : arr) {
         st.add(num);
      }

      int result = 1;    // Initialize result to 1 as minimum length

      // Iterate through each number in set
      for (int it : st) {
         // If current number can be sequence start (no n-1 exists)
         if (!st.contains(it - 1)) {
            int cnt = 1;      // Current sequence length
            int x   = it;     // Current number

            // Count consecutive numbers until sequence breaks
            while (st.contains(x + 1)) {
               x   = x + 1;
               cnt = cnt + 1;
            }

            result = Math.max(result, cnt);
         }
      }
      return result;
   }
}
