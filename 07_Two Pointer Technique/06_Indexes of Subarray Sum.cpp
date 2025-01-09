/*
 * Indexes of Subarray Sum
 *
 * Given an array arr[] containing only non-negative integers, your task is to find a continuous subarray (a contiguous sequence of elements) whose sum equals a specified value target. You need to return the 1-based indices of the leftmost and rightmost elements of this subarray. You need to find the first subarray whose sum is equal to the target.
 *
 * Note: If no such array is possible then, return [-1].
 *
 * Examples:
 *
 * Input: arr[] = [1, 2, 3, 7, 5], target = 12
 * Output: [2, 4]
 * Explanation: The sum of elements from 2nd to 4th position is 12.
 *
 * Input: arr[] = [1, 2, 3, 4, 5, 6, 7, 8, 9, 10], target = 15
 * Output: [1, 5]
 * Explanation: The sum of elements from 1st to 5th position is 15.
 *
 * Input: arr[] = [5, 3, 4], target = 2
 * Output: [-1]
 * Explanation: There is no subarray with sum 2.
 *
 * Constraints:
 * 1 <= arr.size()<= 10^6
 * 0 <= arr[i] <= 10^3
 * 0 <= target <= 10^9
 */

/************************************************************ C++ ************************************************/

// Approach: Use sliding window technique with two pointers to track potential subarrays.
// TC: O(n) - Each element is added and removed at most once.
// SC: O(1) - Only uses constant extra space.

class Solution {
public:
   vector<int> subarraySum(vector<int>&arr, int target){
      // Initialize start pointer and running sum
      int i   = 0;
      int sum = 0;

      // Iterate through array with end pointer j
      for (int j = 0; j < arr.size(); j++) {
         // Add current element to sum
         sum += arr[j];

         // If sum exceeds target, remove elements from start
         // until sum becomes <= target
         while (sum > target && i <= j) {
            sum -= arr[i];
            i++;
         }

         // If exact target sum found, return 1-based indices
         if (sum == target) {
            return { i + 1, j + 1 };
         }
      }
      // No subarray found with target sum
      return { -1 };
   }
};

/************************************************************ JAVA ************************************************/

// Approach: Use sliding window technique with two pointers to track potential subarrays.
// TC: O(n) - Each element is added and removed at most once.
// SC: O(1) - Only uses constant extra space.
class Solution {
   // Function to find subarray with sum equal to target
   static ArrayList<Integer> subarraySum(int[] arr, int target){
      // Initialize start pointer and running sum
      int i   = 0;
      int sum = 0;

      // Use sliding window - j is end pointer
      for (int j = 0; j < arr.length; j++) {
         // Add current element to window sum
         sum += arr[j];

         // Shrink window if sum exceeds target
         while (sum > target && i <= j) {
            sum -= arr[i];
            i++;
         }

         // Return 1-based indices if target found
         if (sum == target) {
            ArrayList<Integer> result = new ArrayList<>();
            result.add(i + 1);     // Convert to 1-based index
            result.add(j + 1);     // Convert to 1-based index
            return result;
         }
      }
      // Return [-1] if no subarray found
      ArrayList<Integer> noResult = new ArrayList<>();
      noResult.add(-1);
      return noResult;
   }
}
