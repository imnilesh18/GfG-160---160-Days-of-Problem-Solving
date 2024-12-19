/*
 * Kth Missing Positive Number in a Sorted Array
 *
 * Given a sorted array of distinct positive integers arr[], we need to find the kth positive number that is missing from arr[].
 *
 * Examples :
 * Input: arr[] = [2, 3, 4, 7, 11], k = 5
 * Output: 9
 * Explanation: Missing are 1, 5, 6, 8, 9, 10… and 5th missing number is 9.
 *
 * Input: arr[] = [1, 2, 3], k = 2
 * Output: 5
 * Explanation: Missing are 4, 5, 6… and 2nd missing number is 5.
 *
 * Input: arr[] = [3, 5, 9, 10, 11, 12], k = 2
 * Output: 2
 * Explanation: Missing are 1, 2, 4, 6… and 2nd missing number is 2.
 *
 * Constraints:
 * 1 <= arr.size() <= 10^5
 * 1 <= k <= 10^5
 * 1 <= arr[i]<= 10^6
 */

/************************************************************ C++ ************************************************/

// Approach: Binary search to find the position where the k-th missing number lies.
// Time Complexity: O(log(n)) (binary search on the array).
// Space Complexity: O(1) (no additional space used).
class Solution {
public:
   int kthMissing(vector<int>&arr, int k){
      // Initialize binary search bounds
      int low = 0, high = arr.size() - 1;

      // Perform binary search to find the position where the k-th missing number would be
      while (low <= high) {
         int mid = low + (high - low) / 2;    // Calculate the mid index

         // Calculate how many numbers are missing up to arr[mid]
         int missing = arr[mid] - (mid + 1);

         // If the number of missing numbers so far is less than k, move to the right half
         if (missing < k) {
            low = mid + 1;
         }
         // Otherwise, move to the left half
         else {
            high = mid - 1;
         }
      }

      // The k-th missing number lies at position `low + k` outside the array
      return low + k;
   }
};

/************************************************************ JAVA ************************************************/

// Approach: Binary search to find the position where the k-th missing number lies.
// Time Complexity: O(log(n)) (binary search on the array).
// Space Complexity: O(1) (no additional space used).
class Solution {
   public int kthMissing(int[] arr, int k){
      int low = 0, high = arr.length - 1;

      // Binary search to find the position where the k-th missing number lies
      while (low <= high) {
         int mid     = low + (high - low) / 2;
         int missing = arr[mid] - (mid + 1);    // Calculate number of missing elements before arr[mid]

         if (missing < k) {
            low = mid + 1;     // Search in the right half
         } else {
            high = mid - 1;    // Search in the left half
         }
      }

      // Calculate the k-th missing number
      return low + k;
   }
}
