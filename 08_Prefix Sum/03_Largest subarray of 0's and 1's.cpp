/*
 * Largest subarray of 0's and 1's
 *
 * Given an array arr of 0s and 1s. Find and return the length of the longest subarray with equal number of 0s and 1s.
 *
 * Examples:
 *
 * Input: arr[] = [1, 0, 1, 1, 1, 0, 0]
 * Output: 6
 * Explanation: arr[1...6] is the longest subarray with three 0s and three 1s.
 *
 * Input: arr[] = [0, 0, 1, 1, 0]
 * Output: 4
 * Explnation: arr[0...3] or arr[1...4] is the longest subarray with two 0s and two 1s.
 *
 * Input: arr[] = [0]
 * Output: 0
 * Explnation: There is no subarray with an equal number of 0s and 1s.
 *
 * Constraints:
 * 1 <= arr.size() <= 10^5
 * 0 <= arr[i] <= 1
 */

/************************************************************ C++ ************************************************/

// Approach 1 Brute Force (TLE): Use two nested loops to check all possible subarrays. For each subarray, count 0s and 1s and update result when counts are equal.
// Time Complexity: O(n²) since we use nested loops to check all possible subarrays
// Space Complexity: O(1) since we only use a constant amount of extra space for variables
class Solution {
public:
   int maxLen(vector<int>& arr){
      // Get length of input array
      int n = arr.size();

      // Variable to store the maximum length of valid subarray found so far
      int result = 0;

      // Outer loop - try each possible starting point
      for (int i = 0; i < n; i++) {
         // Initialize counters for each subarray
         int ones  = 0;    // Count of 1s in current subarray
         int zeros = 0;    // Count of 0s in current subarray

         // Inner loop - extend subarray from current starting point
         for (int j = i; j < n; j++) {
            // Count 1s and 0s in current subarray window
            if (arr[j] == 1) {
               ones++;
            } else {
               zeros++;
            }

            // If equal number of 0s and 1s found, update result if current length is larger
            if (ones == zeros) {
               result = max(result, j - i + 1);
            }
         }
      }
      return result;
   }
};

// Approach 2 : Convert 0s to -1s and use prefix sum with hashmap to find longest subarray with equal number of 0s and 1s.
// TC: O(n) where n is the size of input array as we traverse array once.
// SC: O(n) to store prefix sums in hashmap in worst case.
class Solution {
public:
   int maxLen(vector<int>&arr){
      // Map to store prefix sum and its earliest index
      unordered_map<int, int> prefixSumIndex;
      int sum    = 0;         // Running sum
      int maxLen = 0;         // Length of longest subarray
      int k      = 0;         // Target sum (looking for subarrays with equal 0s and 1s)

      for (int i = 0; i < arr.size(); i++) {
         // Convert 0 to -1 to make equal number of 0s and 1s problem
         // equivalent to finding subarray with sum = 0
         sum += arr[i] == 0 ? -1 : 1;

         // If current sum equals k, entire subarray from start has equal 0s and 1s
         if (sum == k) {
            maxLen = max(maxLen, i + 1);
         }

         // If (sum-k) exists in map, we found a subarray with equal 0s and 1s
         if (prefixSumIndex.find(sum - k) != prefixSumIndex.end()) {
            maxLen = max(maxLen, i - prefixSumIndex[sum - k]);
         }

         // Only store first occurrence of sum to get maximum length
         if (prefixSumIndex.find(sum) == prefixSumIndex.end()) {
            prefixSumIndex[sum] = i;
         }
      }
      return maxLen;
   }
};

/************************************************************ JAVA ************************************************/

// Approach 1 Brute Force (TLE): Use two nested loops to check all possible subarrays. For each subarray, count 0s and 1s and update result when counts are equal.
// Time Complexity: O(n²) since we use nested loops to check all possible subarrays
// Space Complexity: O(1) since we only use a constant amount of extra space for variables
class Solution {
   public int maxLen(int[] arr){
      // Get length of input array
      int n = arr.length;

      // Variable to store the maximum length of valid subarray found so far
      int result = 0;

      // Outer loop - try each possible starting point
      for (int i = 0; i < n; i++) {
         // Initialize counters for each subarray
         int ones  = 0;      // Count of 1s in current subarray
         int zeros = 0;      // Count of 0s in current subarray

         // Inner loop - extend subarray from current starting point
         for (int j = i; j < n; j++) {
            // Count 1s and 0s in current subarray window
            if (arr[j] == 1) {
               ones++;
            } else {
               zeros++;
            }

            // If equal number of 0s and 1s found, update result if current length is larger
            if (ones == zeros) {
               result = Math.max(result, j - i + 1);
            }
         }
      }
      return result;
   }
}

// Approach 2 : Convert 0s to -1s and use prefix sum with hashmap to find longest subarray with equal number of 0s and 1s.
// TC: O(n) where n is the size of input array as we traverse array once.
// SC: O(n) to store prefix sums in hashmap in worst case.
class Solution {
   public int maxLen(int[] arr){
      // Map to store prefix sum and its earliest index
      HashMap<Integer, Integer> prefixSumIndex = new HashMap<>();
      int sum    = 0;       // Running sum
      int maxLen = 0;       // Length of longest subarray
      int k      = 0;       // Target sum (looking for subarrays with equal 0s and 1s)

      for (int i = 0; i < arr.length; i++) {
         // Convert 0 to -1 to make equal number of 0s and 1s problem
         // equivalent to finding subarray with sum = 0
         sum += arr[i] == 0 ? -1 : 1;

         // If current sum equals k, entire subarray from start has equal 0s and 1s
         if (sum == k) {
            maxLen = Math.max(maxLen, i + 1);
         }

         // If (sum-k) exists in map, we found a subarray with equal 0s and 1s
         if (prefixSumIndex.containsKey(sum - k)) {
            maxLen = Math.max(maxLen, i - prefixSumIndex.get(sum - k));
         }

         // Only store first occurrence of sum to get maximum length
         if (!prefixSumIndex.containsKey(sum)) {
            prefixSumIndex.put(sum, i);
         }
      }
      return maxLen;
   }
}
