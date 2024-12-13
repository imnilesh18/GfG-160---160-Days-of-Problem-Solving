/*
 * Sorted and Rotated Minimum
 *
 * A sorted array of distinct elements arr[] is rotated at some unknown point, the task is to find the minimum element in it.
 *
 * Examples:
 *
 * Input: arr[] = [5, 6, 1, 2, 3, 4]
 * Output: 1
 * Explanation: 1 is the minimum element in the array.
 *
 * Input: arr[] = [3, 1, 2]
 * Output: 1
 * Explanation: Here 1 is the minimum element.
 *
 * Input: arr[] = [4, 2, 3]
 * Output: 2
 * Explanation: Here 2 is the minimum element.
 *
 * Constraints:
 * 1 ≤ arr.size() ≤ 10^6
 * 1 ≤ arr[i] ≤ 10^9
 */

/************************************************************ C++ ************************************************/

// Approach : Modified Binary Search
// Time Complexity: O(log n) (Binary search reduces the search space logarithmically).
// Space Complexity: O(1) (No extra space used; only variables l, r, and mid are used).
class Solution {
public:
   int findMin(vector<int>& arr){
      int l = 0, r = arr.size() - 1; // Initialize left and right pointers

      while (l < r) {                // Continue until the search space is reduced to one element
         int mid = l + (r - l) / 2;  // Calculate the middle index (avoiding overflow)
         // If the middle element is greater than the rightmost element,
         // the minimum must be in the right part of the array
         if (arr[mid] > arr[r]) {
            l = mid + 1;     // Narrow the search to the right half
         } else {
            // If the middle element is less than or equal to the rightmost element,
            // the minimum could still be in the left part
            r = mid;     // Narrow the search to the left half (including mid)
         }
      }
      // At the end of the loop, 'l' points to the minimum element
      return arr[l];
   }
};

/************************************************************ JAVA ************************************************/

// Approach : Modified Binary Search
// Time Complexity: O(log n) (Binary search reduces the search space logarithmically).
// Space Complexity: O(1) (No extra space used; only variables l, r, and mid are used).
