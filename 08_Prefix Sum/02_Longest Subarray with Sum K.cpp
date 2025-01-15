/*
 * Longest Subarray with Sum K
 *
 * Given an array arr[] containing integers and an integer k, your task is to find the length of the longest subarray where the sum of its elements is equal to the given value k. If there is no subarray with sum equal to k, return 0.
 *
 * Examples:
 *
 * Input: arr[] = [10, 5, 2, 7, 1, -10], k = 15
 * Output: 6
 * Explanation: Subarrays with sum = 15 are [5, 2, 7, 1], [10, 5] and [10, 5, 2, 7, 1, -10]. The length of the longest subarray with a sum of 15 is 6.
 *
 * Input: arr[] = [-5, 8, -14, 2, 4, 12], k = -5
 * Output: 5
 * Explanation: Only subarray with sum = 15 is [-5, 8, -14, 2, 4] of length 5.
 *
 * Input: arr[] = [10, -10, 20, 30], k = 5
 * Output: 0
 * Explanation: No subarray with sum = 5 is present in arr[].
 *
 * Constraints:
 * 1 ≤ arr.size() ≤ 10^5
 * -10^4 ≤ arr[i] ≤ 10^4
 * -10^9 ≤ k ≤ 10^9
 */

/************************************************************ C++ ************************************************/

// Approach: Use prefix sum with hashmap to store first occurrence of each sum and find longest subarray with sum k
// Time Complexity: O(n) where n is the length of input array - single pass through array with O(1) hashmap operations
// Space Complexity: O(n) to store prefix sums in hashmap in worst case where all prefix sums are unique
class Solution {
public:
   int longestSubarray(vector<int>& arr, int k){
      // HashMap to store first occurrence index of each prefix sum
      // Key: prefix sum value, Value: first index where this sum occurs
      unordered_map<int, int> prefixSumIndex;

      int sum       = 0;    // Running prefix sum
      int maxLength = 0;    // Track length of longest valid subarray found

      for (int i = 0; i < arr.size(); i++) {
         sum += arr[i];     // Add current element to running sum

         // Case 1: If current prefix sum equals k, entire subarray from start to i has sum k
         if (sum == k) {
            maxLength = max(maxLength, i + 1);
         }

         // Case 2: Look for any previous prefix sum that would make current subarray have sum k
         // If we find (sum - k) in map, then subarray from that index+1 to i has sum k
         if (prefixSumIndex.find(sum - k) != prefixSumIndex.end()) {
            maxLength = max(maxLength, i - prefixSumIndex[sum - k]);
         }

         // Case 3: Only store first occurrence of each prefix sum
         // We want earliest index to get longest possible subarray
         if (prefixSumIndex.find(sum) == prefixSumIndex.end()) {
            prefixSumIndex[sum] = i;
         }
      }

      return maxLength;
   }
};

/************************************************************ JAVA ************************************************/

// Approach: Use prefix sum with hashmap to store first occurrence of each sum and find longest subarray with sum k
// Time Complexity: O(n) where n is the length of input array - single pass through array with O(1) hashmap operations
// Space Complexity: O(n) to store prefix sums in hashmap in worst case where all prefix sums are unique
class Solution {
   public int longestSubarray(int[] arr, int k){
      // HashMap to store first occurrence index of each prefix sum
      // Key: prefix sum value, Value: first index where this sum occurs
      HashMap<Long, Integer> prefixSumIndex = new HashMap<>();

      long sum       = 0; // Running prefix sum (using long to handle integer overflow)
      int  maxLength = 0; // Track length of longest valid subarray found

      for (int i = 0; i < arr.length; i++) {
         sum += arr[i];   // Add current element to running sum

         // Case 1: If current prefix sum equals k, entire subarray from start to i has sum k
         if (sum == k) {
            maxLength = Math.max(maxLength, i + 1);
         }

         // Case 2: Look for any previous prefix sum that would make current subarray have sum k
         // If we find (sum - k) in map, then subarray from that index+1 to i has sum k
         if (prefixSumIndex.containsKey(sum - k)) {
            maxLength = Math.max(maxLength, i - prefixSumIndex.get(sum - k));
         }

         // Case 3: Only store first occurrence of each prefix sum
         // We want earliest index to get longest possible subarray
         if (!prefixSumIndex.containsKey(sum)) {
            prefixSumIndex.put(sum, i);
         }
      }

      return maxLength;
   }
}
