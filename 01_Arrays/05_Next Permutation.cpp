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
