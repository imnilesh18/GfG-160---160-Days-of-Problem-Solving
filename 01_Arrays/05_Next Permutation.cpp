/*
 * Next Permutation
 *
 * Given an array of integers arr[] representing a permutation, implement the next permutation that rearranges the numbers into the lexicographically next greater permutation. If no such permutation exists, rearrange the numbers into the lowest possible order (i.e., sorted in ascending order).
 * Note - A permutation of an array of integers refers to a specific arrangement of its elements in a sequence or linear order.
 *
 * Examples:
 * Input: arr = [2, 4, 1, 7, 5, 0]
 * Output: [2, 4, 5, 0, 1, 7]
 * Explanation: The next permutation of the given array is {2, 4, 5, 0, 1, 7}.
 *
 * Input: arr = [3, 2, 1]
 * Output: [1, 2, 3]
 * Explanation: As arr[] is the last permutation, the next permutation is the lowest one.
 *
 * Input: arr = [3, 4, 2, 5, 1]
 * Output: [3, 4, 5, 1, 2]
 * Explanation: The next permutation of the given array is {3, 4, 5, 1, 2}.
 *
 * Constraints:
 * 1 ≤ arr.size() ≤ 10^5
 * 1 ≤ arr[i] ≤ 10^5
 */

/************************************************************ C++ ************************************************/

// Time Complexity: O(3N), where N = size of the given array
// Finding the break-point, finding the next greater element, and reversal at the end takes O(N) for each, where N is the number of elements in the input array. This sums up to 3*O(N) which is approximately O(3N).
// Space Complexity: Since no extra storage is required. Thus, its space complexity is O(1).
class Solution {
public:
   void nextPermutation(vector<int>& arr){
      int n = arr.size();   // size of the array.

      // Step 1: Find the break point:
      int ind = -1;   // break point

      for (int i = n - 2; i >= 0; i--) {
         if (arr[i] < arr[i + 1]) {
            // index i is the break point
            ind = i;
            break;
         }
      }

      // If break point does not exist:
      if (ind == -1) {
         // reverse the whole array:
         reverse(arr.begin(), arr.end());
         return;
      }

      // Step 2: Find the next greater element
      //         and swap it with arr[ind]:

      for (int i = n - 1; i > ind; i--) {
         if (arr[i] > arr[ind]) {
            swap(arr[i], arr[ind]);
            break;
         }
      }

      // Step 3: reverse the right half:
      reverse(arr.begin() + ind + 1, arr.end());

      return;
   }
};

/************************************************************ JAVA ************************************************/

// Time Complexity: O(3N), where N = size of the given array
// Finding the break-point, finding the next greater element, and reversal at the end takes O(N) for each, where N is the number of elements in the input array. This sums up to 3*O(N) which is approximately O(3N).
// Space Complexity: Since no extra storage is required. Thus, its space complexity is O(1).
class Solution {
   // Helper method to reverse an array from start to end indices.
   private void reverse(int[] arr, int start, int end){
      while (start < end) {
         swap(arr, start, end);
         start++;
         end--;
      }
   }

   // Helper method to swap two elements in an array.
   private void swap(int[] arr, int i, int j){
      int temp = arr[i];

      arr[i] = arr[j];
      arr[j] = temp;
   }

   public void nextPermutation(int[] arr){
      int n = arr.length;   // Size of the array.

      // Step 1: Find the break point.
      int ind = -1;   // Break point.

      // Traverse the array from right to left to find the break point.
      for (int i = n - 2; i >= 0; i--) {
         if (arr[i] < arr[i + 1]) {
            // Index i is the break point.
            ind = i;
            break;
         }
      }

      // If break point does not exist:
      if (ind == -1) {
         // Reverse the whole array.
         reverse(arr, 0, n - 1);
         return;
      }

      // Step 2: Find the next greater element and swap it with arr[ind].
      for (int i = n - 1; i > ind; i--) {
         if (arr[i] > arr[ind]) {
            // Swap arr[i] and arr[ind].
            swap(arr, i, ind);
            break;
         }
      }

      // Step 3: Reverse the right half of the array.
      reverse(arr, ind + 1, n - 1);
   }
}
