/*
 * Max Circular Subarray Sum
 *
 * Given an array of integers arr[] in a circular fashion. Find the maximum subarray sum that we can get if we assume the array to be circular.
 *
 * Examples:
 *
 * Input: arr[] = [8, -8, 9, -9, 10, -11, 12]
 * Output: 22
 * Explanation: Starting from the last element of the array, i.e, 12, and moving in a circular fashion, we have max subarray as 12, 8, -8, 9, -9, 10, which gives maximum sum as 22.
 *
 * Input: arr[] = [10, -3, -4, 7, 6, 5, -4, -1]
 * Output: 23
 * Explanation: Maximum sum of the circular subarray is 23. The subarray is [7, 6, 5, -4, -1, 10].
 *
 * Input: arr[] = [-1, 40, -14, 7, 6, 5, -4, -1]
 * Output: 52
 * Explanation: Circular Subarray [7, 6, 5, -4, -1, -1, 40] has the maximum sum, which is 52.
 *
 * Constraints:
 * 1 <= arr.size() <= 10^5
 * -10^4 <= arr[i] <= 10^4
 */

/************************************************************ C++ ************************************************/

// T.C: O(n)
// S.C: O(1)
class Solution {
public:
   // arr: input array
   // Function to find maximum circular subarray sum.
   int circularSubarraySum(vector<int>&arr){
      // your code here
      int total = 0, maxSum = arr[0], curMax = 0, minSum = arr[0], curMin = 0;

      for (int& a : arr) {
         curMax = max(curMax + a, a);
         maxSum = max(maxSum, curMax);
         curMin = min(curMin + a, a);
         minSum = min(minSum, curMin);
         total += a;
      }
      return maxSum > 0 ? max(maxSum, total - minSum) : maxSum;
   }
};

/************************************************************ JAVA ************************************************/

// T.C: O(n)
// S.C: O(1)
class Solution {
   // a: input array
   // n: size of array
   // Function to find maximum circular subarray sum.
   public int circularSubarraySum(int arr[]){
      // Your code here
      int total = 0, maxSum = arr[0], curMax = 0, minSum = arr[0], curMin = 0;

      for (int a : arr) {
         curMax = Math.max(curMax + a, a);
         maxSum = Math.max(maxSum, curMax);
         curMin = Math.min(curMin + a, a);
         minSum = Math.min(minSum, curMin);
         total += a;
      }
      return maxSum > 0 ? Math.max(maxSum, total - minSum) : maxSum;
   }
}
