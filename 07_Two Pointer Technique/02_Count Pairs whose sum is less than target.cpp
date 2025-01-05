/*
 * Count Pairs whose sum is less than target
 *
 * Given an array arr[] and an integer target. You have to find the number of pairs in the array whose sum is strictly less than the target.
 *
 * Examples:
 *
 * Input: arr[] = [7, 2, 5, 3], target = 8
 * Output: 2
 * Explanation: There are 2 pairs with sum less than 8: (2, 5) and (2, 3).
 *
 * Input: arr[] = [5, 2, 3, 2, 4, 1], target = 5
 * Output: 4
 * Explanation: There are 4 pairs whose sum is less than 5: (2, 2), (2, 1), (3, 1) and (2, 1).
 *
 * Input: arr[] = [2, 1, 8, 3, 4, 7, 6, 5], target = 7
 * Output: 6
 * Explanation: There are 6 pairs whose sum is less than 7: (2, 1), (2, 3), (2, 4), (1, 3), (1, 4) and (1, 5).
 *
 * Constraints:
 * 1 <= arr.size() <= 10^5
 * 0 <= arr[i] <= 10^4
 * 1 <= target <= 10^4
 */

/************************************************************ C++ ************************************************/

// Approach: Sort array and use two pointer technique to find valid pairs
// Time Complexity: O(nlogn) for sorting + O(n) for two pointer = O(nlogn)
// Space Complexity: O(1) as we are using constant extra space
class Solution {
public:
   int countPairs(vector<int>&arr, int target){
      // Sort the array to use two pointer technique
      sort(arr.begin(), arr.end());

      // Initialize two pointers at start and end
      int left  = 0;
      int right = arr.size() - 1;

      // Variable to store count of valid pairs
      int cnt = 0;

      // Use two pointer technique to find pairs
      while (left < right) {
         int sum = arr[left] + arr[right];

         // If sum is less than target, then arr[left] will form
         // valid pairs with all elements from (left+1) to right
         if (sum < target) {
            cnt += right - left;     // Add count of all valid pairs
            left++;                  // Move left pointer to find more pairs
         }
         // If sum is >= target, decrease right pointer to reduce sum
         else {
            right--;
         }
      }
      return cnt;
   }
};

/************************************************************ JAVA ************************************************/

// Approach: Sort array then use two pointers to find pairs - if sum < target add all pairs between pointers, increment left if sum < target else decrement right.
// TC: O(nlogn + n) where nlogn for sorting and n for two pointer traversal.
// SC: O(1) as we only use constant extra space for pointers and counter variables.
class Solution {
   int countPairs(int arr[], int target){
      // Step 1: Sort array to use two pointer approach effectively
      Arrays.sort(arr);

      // Step 2: Initialize two pointers at start and end of array
      int left  = 0;
      int right = arr.length - 1;

      // Counter to keep track of valid pairs found
      int cnt = 0;

      // Step 3: Use two pointer technique to find valid pairs
      while (left < right) {
         // Calculate current sum of elements at left and right pointers
         int sum = arr[left] + arr[right];

         // If sum < target, we found valid pairs
         // arr[left] will form valid pairs with all elements from (left+1) to right
         // Because array is sorted, all these pairs will have sum < target
         if (sum < target) {
            cnt += right - left;     // Add count of all valid pairs with arr[left]
            left++;                  // Move left pointer to find more pairs
         }
         // If sum >= target, we need to decrease sum
         // Move right pointer left to get smaller sum in next iteration
         else {
            right--;
         }
      }
      return cnt;
   }
}
