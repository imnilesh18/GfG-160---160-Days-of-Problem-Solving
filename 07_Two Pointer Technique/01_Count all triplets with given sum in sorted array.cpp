/*
 * Count all triplets with given sum in sorted array
 *
 * Given a sorted array arr[] and a target value, the task is to count triplets (i, j, k) of valid indices, such that arr[i] + arr[j] + arr[k] = target and i < j < k.
 *
 * Examples:
 *
 * Input: arr[] = [-3, -1, -1, 0, 1, 2], target = -2
 * Output: 4
 * Explanation: Two triplets that add up to -2 are:
 * arr[0] + arr[3] + arr[4] = (-3) + 0 + (1) = -2
 * arr[0] + arr[1] + arr[5] = (-3) + (-1) + (2) = -2
 * arr[0] + arr[2] + arr[5] = (-3) + (-1) + (2) = -2
 * arr[1] + arr[2] + arr[3] = (-1) + (-1) + (0) = -2
 *
 * Input: arr[] = [-2, 0, 1, 1, 5], target = 1
 * Output: 0
 * Explanation: There is no triplet whose sum is equal to 1.
 *
 * Constraints:
 * 3 ≤ arr.size() ≤ 10^3
 * -10^5 ≤ arr[i], target ≤ 10^5
 */

/************************************************************ C++ ************************************************/

// Approach: Two pointers technique with fixed first element to find triplets in sorted array while handling duplicates using counting combinations.
// TC: O(n²) where n is size of array, as we have one outer loop and two pointers traversing array.
// SC: O(1) as we only use constant extra space regardless of input size.
class Solution {
public:
   int countTriplets(vector<int>& arr, int target){
      // Size of input array
      int n = arr.size();
      // Variable to store count of valid triplets
      int count = 0;

      // Fix the first element of triplet
      for (int i = 0; i < n - 2; i++) {
         // Two pointers for finding other two elements
         int left  = i + 1;        // Points to element after i
         int right = n - 1;        // Points to last element

         // Keep moving pointers until they meet
         while (left < right) {
            // Calculate current sum of triplet
            int sum = arr[i] + arr[left] + arr[right];

            if (sum == target) {
               // Special case: all elements between left and right are same
               if (arr[left] == arr[right]) {
                  int range = right - left + 1;
                  // Use combination formula nC2 to count all possible pairs
                  count += (range * (range - 1)) / 2;
                  break;
               }

               // Count duplicates at left pointer
               int left_count = 1;
               while (left + 1 < right && arr[left] == arr[left + 1]) {
                  left_count++;
                  left++;
               }

               // Count duplicates at right pointer
               int right_count = 1;
               while (right - 1 > left && arr[right] == arr[right - 1]) {
                  right_count++;
                  right--;
               }

               // Add all possible combinations of left and right duplicates
               count += left_count * right_count;
               left++;
               right--;
            }
            // If sum is less than target, need larger values, move left
            else if (sum < target) {
               left++;
            }
            // If sum is more than target, need smaller values, move right
            else {
               right--;
            }
         }
      }
      return count;
   }
};

/************************************************************ JAVA ************************************************/

// Approach: Two pointers technique with fixed first element to find triplets in sorted array while handling duplicates using counting combinations.
// TC: O(n²) where n is size of array, as we have one outer loop and two pointers traversing array.
// SC: O(1) as we only use constant extra space regardless of input size.
class Solution {
   public int countTriplets(int[] arr, int target){
      // Size of input array
      int n = arr.length;
      // Variable to store count of valid triplets
      int count = 0;

      // Fix the first element of triplet
      for (int i = 0; i < n - 2; i++) {
         // Two pointers for finding other two elements
         int left  = i + 1;        // Points to element after i
         int right = n - 1;        // Points to last element

         // Keep moving pointers until they meet
         while (left < right) {
            // Calculate current sum of triplet
            int sum = arr[i] + arr[left] + arr[right];

            if (sum == target) {
               // Special case: all elements between left and right are same
               if (arr[left] == arr[right]) {
                  int range = right - left + 1;
                  // Use combination formula nC2 to count all possible pairs
                  count += (range * (range - 1)) / 2;
                  break;
               }

               // Count duplicates at left pointer
               int leftCount = 1;
               while (left + 1 < right && arr[left] == arr[left + 1]) {
                  leftCount++;
                  left++;
               }

               // Count duplicates at right pointer
               int rightCount = 1;
               while (right - 1 > left && arr[right] == arr[right - 1]) {
                  rightCount++;
                  right--;
               }

               // Add all possible combinations of left and right duplicates
               count += leftCount * rightCount;
               left++;
               right--;
            }
            // If sum is less than target, need larger values, move left
            else if (sum < target) {
               left++;
            }
            // If sum is more than target, need smaller values, move right
            else {
               right--;
            }
         }
      }
      return count;
   }
}
