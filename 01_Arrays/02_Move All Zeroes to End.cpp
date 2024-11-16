/*
 * Move All Zeroes to End
 *
 * Given an array arr[]. Push all the zeros of the given array to the right end of the array while maintaining the order of non-zero elements. Do the mentioned change in the array in place.
 *
 * Examples:
 * Input: arr[] = [1, 2, 0, 4, 3, 0, 5, 0]
 * Output: [1, 2, 4, 3, 5, 0, 0, 0]
 * Explanation: There are three 0s that are moved to the end.
 *
 * Input: arr[] = [10, 20, 30]
 * Output: [10, 20, 30]
 * Explanation: No change in array as there are no 0s.
 *
 * Input: arr[] = [0, 0]
 * Output: [0, 0]
 * Explanation: No change in array as there are all 0s.
 *
 * Constraints:
 * 1 ≤ arr.size() ≤ 10^5
 * 0 ≤ arr[i] ≤ 10^5
 */

// Approch 1:
// Brute Force: Use of an extra array
// T.C : O(N)
// S.C : O(N)
class Solution {
public:
   void pushZerosToEnd(vector<int>& arr){
      int         n = arr.size(); // Get the size of the array
      vector<int> temp;           // Temporary vector to store non-zero elements

      // First loop: Traverse the array and collect all non-zero elements
      for (int i = 0; i < n; i++) {
         if (arr[i] != 0) {
            temp.push_back(arr[i]);      // Add non-zero element to temp
         }
      }

      int nz = temp.size();    // Number of non-zero elements

      // Second loop: Copy all non-zero elements back into the original array
      for (int i = 0; i < nz; i++) {
         arr[i] = temp[i];     // Copy each non-zero element from temp to arr
      }

      // Third loop: Fill the remaining positions with zeroes
      for (int i = nz; i < n; i++) {
         arr[i] = 0;     // Place zeroes at the remaining positions
      }
   }
};

// Approach 2:
// Optimal Approach: Using 2 pointers
// T.C : O(N)
// S.C : O(1)
class Solution {
public:
   void pushZerosToEnd(vector<int>& arr){
      int n = arr.size(); // Get the size of the array
      int j = -1;         // Pointer to track the position where the next zero should be placed

      // First loop: Find the first zero in the array (this is where we'll start moving non-zero elements)
      for (int i = 0; i < n; i++) {
         if (arr[i] == 0) {
            j = i;      // Set the pointer j to the index of the first zero
            break;      // Exit the loop once we find the first zero
         }
      }

      // If no zero was found (i.e., j is still -1), return immediately as the array is already without zeros
      if (j == -1) {
         return;
      }

      // Second loop: Traverse the array from the index after the first zero to move non-zero elements
      for (int i = j + 1; i < n; i++) {
         if (arr[i] != 0) {
            swap(arr[i], arr[j]); // Swap the non-zero element with the first zero found
            j++;                  // Move the pointer j to the next position for placing the next zero
         }
      }
   }
};
