/*
 * Peak element
 *
 * Given an array arr[] where no two adjacent elements are same, find the index of a peak element. An element is considered to be a peak if it is greater than its adjacent elements (if they exist). If there are multiple peak elements, return index of any one of them. The output will be "true" if the index returned by your function is correct; otherwise, it will be "false".
 *
 * Note: Consider the element before the first element and the element after the last element to be negative infinity.
 *
 * Examples :
 * Input: arr = [1, 2, 4, 5, 7, 8, 3]
 * Output: true
 * Explanation: arr[5] = 8 is a peak element because arr[4] < arr[5] > arr[6].
 *
 * Input: arr = [10, 20, 15, 2, 23, 90, 80]
 * Output: true
 * Explanation: arr[1] = 20 and arr[5] = 90 are peak elements because arr[0] < arr[1] > arr[2] and arr[4] < arr[5] > arr[6].
 *
 * Input: arr = [1, 2, 3]
 * Output: true
 * Explanation: arr[2] is a peak element because arr[1] < arr[2] and arr[2] is the last element, so it has negative infinity to its right.
 *
 * Constraints:
 * 1 ≤ arr.size() ≤ 10^6
 * -2^31 ≤ arr[i] ≤ 2^31 - 1
 */

/************************************************************ C++ ************************************************/

// Approach: Binary Search on Peaks
// Time Complexity: O(log n) (Binary search reduces the search space logarithmically).
// Space Complexity: O(1) (Uses constant extra space for variables).
class Solution {
public:
   int peakElement(vector<int>&arr){
      int n = arr.size();
      int left = 0, right = n - 1;   // Initialize binary search boundaries

      // Binary search loop
      while (left < right) {
         int mid = left + (right - left) / 2;    // Calculate mid to avoid overflow

         // Compare middle element with its right neighbor
         if (arr[mid] < arr[mid + 1]) {
            left = mid + 1;  // Move to the right half
         } else {
            right = mid;     // Move to the left half
         }
      }

      // Verify if the found index is a peak element
      if ((left == 0 || arr[left] >= arr[left - 1]) && (left == n - 1 || arr[left] >= arr[left + 1])) {
         return left;    // Return the peak element's index
      }

      return -1;   // Return -1 if no peak is found (edge case, unlikely due to constraints)
   }
};

/************************************************************ JAVA ************************************************/

// Approach: Binary Search on Peaks
// Time Complexity: O(log n) (Binary search reduces the search space logarithmically).
// Space Complexity: O(1) (Uses constant extra space for variables).
class Solution {
   public int peakElement(int[] arr){
      int n = arr.length;
      int left = 0, right = n - 1;   // Initialize binary search boundaries

      // Binary search loop
      while (left < right) {
         int mid = left + (right - left) / 2;    // Calculate mid to avoid overflow

         // Compare the middle element with its right neighbor
         if (arr[mid] < arr[mid + 1]) {
            left = mid + 1;  // Move to the right half
         } else {
            right = mid;     // Move to the left half
         }
      }

      // Verify if the found index is a peak element
      if ((left == 0 || arr[left] >= arr[left - 1]) && (left == n - 1 || arr[left] >= arr[left + 1])) {
         return left;    // Return the peak element's index
      }

      return -1;   // Return -1 if no peak is found (edge case, unlikely due to constraints)
   }
}
