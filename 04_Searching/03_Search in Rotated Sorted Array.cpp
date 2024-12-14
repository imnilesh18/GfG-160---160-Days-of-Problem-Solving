/*
 * Search in Rotated Sorted Array
 *
 * Given a sorted and rotated array arr[] of distinct elements, the task is to find the index of a target key. Return -1 if the key is not found.
 *
 * Examples:
 * Input: arr[] = [5, 6, 7, 8, 9, 10, 1, 2, 3], key = 3
 * Output: 8
 * Explanation: 3 is found at index 8.
 *
 * Input: arr[] = [3, 5, 1, 2], key = 6
 * Output: -1
 * Explanation: There is no element that has value 6.
 *
 * Input: arr[] = [33, 42, 72, 99], key = 42
 * Output: 1
 * Explanation: 42 is found at index 1.
 *
 * Constraints:
 * 1 ≤ arr.size() ≤ 10^6
 * 0 ≤ arr[i] ≤ 10^6
 * 1 ≤ key ≤ 10^6
 */

/************************************************************ C++ ************************************************/

// Approach : Modified Binary Search
// Time Complexity: O(log n) (Binary search reduces the search space logarithmically).
// Space Complexity: O(1) (No extra space used; only pointers and variables are utilized).
class Solution {
public:
   int search(vector<int>& arr, int key){
      int start = 0, end = arr.size() - 1;   // Initialize pointers for the search range

      // Perform binary search
      while (start <= end) {                  // Repeat until the search range is exhausted
         int mid = start + (end - start) / 2; // Calculate mid to avoid overflow

         // Check if the middle element is the target key
         if (key == arr[mid]) {
            return mid;     // Return the index if found
         }

         // Check if the left half is sorted
         if (arr[start] <= arr[mid]) {
            // If the key lies in the sorted left half
            if (key >= arr[start] && key < arr[mid]) {
               end = mid - 1;      // Adjust the end pointer to search the left half
            } else {
               start = mid + 1;    // Otherwise, search the right half
            }
         }
         // Else, the right half is sorted
         else {
            // If the key lies in the sorted right half
            if (key > arr[mid] && key <= arr[end]) {
               start = mid + 1;    // Adjust the start pointer to search the right half
            } else {
               end = mid - 1;      // Otherwise, search the left half
            }
         }
      }

      // If the loop ends without finding the key, return -1
      return -1;
   }
};

/************************************************************ JAVA ************************************************/

// Approach : Modified Binary Search
// Time Complexity: O(log n) (Binary search reduces the search space logarithmically).
// Space Complexity: O(1) (No extra space used; only pointers and variables are utilized).
class Solution {
   public int search(int[] arr, int key){
      int start = 0, end = arr.length - 1;   // Initialize pointers for the search range

      // Perform binary search
      while (start <= end) {                  // Repeat until the search range is exhausted
         int mid = start + (end - start) / 2; // Calculate mid to avoid overflow

         // Check if the middle element is the target key
         if (key == arr[mid]) {
            return mid;     // Return the index if found
         }

         // Check if the left half is sorted
         if (arr[start] <= arr[mid]) {
            // If the key lies in the sorted left half
            if (key >= arr[start] && key < arr[mid]) {
               end = mid - 1;      // Adjust the end pointer to search the left half
            } else {
               start = mid + 1;    // Otherwise, search the right half
            }
         }
         // Else, the right half is sorted
         else {
            // If the key lies in the sorted right half
            if (key > arr[mid] && key <= arr[end]) {
               start = mid + 1;    // Adjust the start pointer to search the right half
            } else {
               end = mid - 1;      // Otherwise, search the left half
            }
         }
      }

      // If the loop ends without finding the key, return -1
      return -1;
   }
}
