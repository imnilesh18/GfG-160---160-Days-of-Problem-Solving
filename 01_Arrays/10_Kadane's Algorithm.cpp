/*
 * Kadane's Algorithm
 *
 * Given an integer array arr[]. You need to find and return the maximum sum possible from all the subarrays.
 *
 * Examples:
 * Input: arr[] = [2, 3, -8, 7, -1, 2, 3]
 * Output: 11
 * Explanation: The subarray {7, -1, 2, 3} has the largest sum 11.
 *
 * Input: arr[] = [-2, -4]
 * Output: -2
 * Explanation: The subarray {-2} has the largest sum -2.
 *
 * Input: arr[] = [5, 4, 1, 7, 8]
 * Output: 25
 * Explanation: The subarray {5, 4, 1, 7, 8} has the largest sum 25.
 *
 * Constraints:
 * 1 ≤ arr.size() ≤ 10^5
 * -10^9 ≤ arr[i] ≤ 10^4
 */

/************************************************************ C++ ************************************************/

// T.C : O(n)
// S.C: O(1)
class Solution {
public:
   // Function to find the sum of contiguous subarray with maximum sum.
   int maxSubarraySum(vector<int>&arr){
      int maxi = INT_MIN;
      int sum  = 0;

      for (int i = 0; i < arr.size(); i++) {
         sum += arr[i];

         maxi = max(maxi, sum);
         if (sum < 0) {
            sum = 0;
         }
      }
      return maxi;
   }
};

/************************************************************ JAVA ************************************************/

// T.C : O(n)
// S.C: O(1)
class Solution {
   // arr: input array
   // Function to find the sum of contiguous subarray with maximum sum.
   int maxSubarraySum(int[] arr){
      int n    = arr.length;
      int sum  = 0;
      int maxi = Integer.MIN_VALUE;

      for (int i = 0; i < n; i++) {
         sum += arr[i];

         maxi = Math.max(maxi, sum);
         if (sum < 0) {
            sum = 0;
         }
      }
      return maxi;
   }
}
