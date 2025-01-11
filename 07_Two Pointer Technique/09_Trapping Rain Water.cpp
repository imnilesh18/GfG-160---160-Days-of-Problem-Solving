/*
 * Trapping Rain Water
 *
 * Given an array arr[] with non-negative integers representing the height of blocks. If the width of each block is 1, compute how much water can be trapped between the blocks during the rainy season.
 *
 * Examples:
 *
 * Input: arr[] = [3, 0, 1, 0, 4, 0 2]
 * Output: 10
 * Explanation: Total water trapped = 0 + 3 + 2 + 3 + 0 + 2 + 0 = 10 units.
 *
 * Input: arr[] = [3, 0, 2, 0, 4]
 * Output: 7
 * Explanation: Total water trapped = 0 + 3 + 1 + 3 + 0 = 7 units.
 *
 * Input: arr[] = [1, 2, 3, 4]
 * Output: 0
 * Explanation: We cannot trap water as there is no height bound on both sides.
 *
 * Input: arr[] = [2, 1, 5, 3, 1, 0, 4]
 * Output: 9
 * Explanation: Total water trapped = 0 + 1 + 0 + 1 + 3 + 4 + 0 = 9 units.
 *
 * Constraints:
 * 1 < arr.size() < 10^5
 * 0 < arr[i] < 10^3
 */

/************************************************************ C++ ************************************************/

// Approach 1 (Better): For each position, water trapped = min(maximum height to left, maximum height to right) - current height. We precompute left and right maximum heights using auxiliary arrays.
// Time Complexity: O(n) where n is the size of input array - requires three passes through the array.
// Space Complexity: O(n) for storing the two auxiliary arrays leftMax and rightMax.
class Solution {
public:
   int maxWater(vector<int>&arr){
      int n = arr.size();

      // Create array to store maximum height to the left of each element
      vector<int> leftMax(n);

      leftMax[0] = arr[0];                         // First element's left max is itself
      for (int i = 1; i < n; i++) {
         leftMax[i] = max(leftMax[i - 1], arr[i]); // Compare current height with previous max
      }

      // Create array to store maximum height to the right of each element
      vector<int> rightMax(n);
      rightMax[n - 1] = arr[n - 1];                  // Last element's right max is itself
      for (int i = n - 2; i >= 0; i--) {
         rightMax[i] = max(rightMax[i + 1], arr[i]); // Compare current height with next max
      }

      // Calculate water trapped at each position
      int waterTrapped = 0;
      for (int i = 0; i < n; i++) {
         // Water at current position = min(leftMax, rightMax) - current height
         int h = min(leftMax[i], rightMax[i]) - arr[i];
         waterTrapped += h;
      }
      return waterTrapped;
   }
};

// Approach 2 (Optimal): Uses two pointer technique - compares heights at boundaries and moves inward while keeping track of maximum heights seen so far from both sides.
// Time Complexity: O(n) where n is size of array - single pass through array using two pointers.
// Space Complexity: O(1) as we only use constant extra space regardless of input size.
class Solution {
public:
   int maxWater(vector<int>&arr){
      int n = arr.size();
      // Two pointers - left and right, and variables to track maximum heights
      int l = 0, r = n - 1, leftMax = 0, rightMax = 0;
      int res = 0;

      while (l <= r) {
         // If left boundary is smaller than right boundary
         if (arr[l] <= arr[r]) {
            // If current height is greater than leftMax, update leftMax
            if (arr[l] >= leftMax) {
               leftMax = arr[l];
            }
            // Else add the trapped water (difference between leftMax and current height)
            else {
               res += leftMax - arr[l];
            }
            l++;
         }
         // If right boundary is smaller than left boundary
         else {
            // If current height is greater than rightMax, update rightMax
            if (arr[r] >= rightMax) {
               rightMax = arr[r];
            }
            // Else add the trapped water (difference between rightMax and current height)
            else {
               res += rightMax - arr[r];
            }
            r--;
         }
      }
      return res;
   }
};

/************************************************************ JAVA ************************************************/

// Approach 1 (Better): For each position, water trapped = min(maximum height to left, maximum height to right) - current height. We precompute left and right maximum heights using auxiliary arrays.
// Time Complexity: O(n) where n is the size of input array - requires three passes through the array.
// Space Complexity: O(n) for storing the two auxiliary arrays leftMax and rightMax.
class Solution {
   public int maxWater(int arr[]){
      int n = arr.length;

      // Create array to store maximum height to the left of each element
      int[] leftMax = new int[n];

      leftMax[0] = arr[0];                              // First element's left max is itself
      for (int i = 1; i < n; i++) {
         leftMax[i] = Math.max(leftMax[i - 1], arr[i]); // Compare current height with previous max
      }

      // Create array to store maximum height to the right of each element
      int[] rightMax  = new int[n];
      rightMax[n - 1] = arr[n - 1];                       // Last element's right max is itself
      for (int i = n - 2; i >= 0; i--) {
         rightMax[i] = Math.max(rightMax[i + 1], arr[i]); // Compare current height with next max
      }

      // Calculate water trapped at each position
      int waterTrapped = 0;
      for (int i = 0; i < n; i++) {
         // Water at current position = min(leftMax, rightMax) - current height
         int h = Math.min(leftMax[i], rightMax[i]) - arr[i];
         waterTrapped += h;
      }
      return waterTrapped;
   }
}

// Approach 2 (Optimal): Uses two pointer technique - compares heights at boundaries and moves inward while keeping track of maximum heights seen so far from both sides.
// Time Complexity: O(n) where n is size of array - single pass through array using two pointers.
// Space Complexity: O(1) as we only use constant extra space regardless of input size.
class Solution {
   public int trap(int[] arr){
      int n = arr.length;
      // Two pointers - left and right, and variables to track maximum heights
      int l = 0, r = n - 1, leftMax = 0, rightMax = 0;
      int res = 0;

      while (l <= r) {
         // If left boundary is smaller than right boundary
         if (arr[l] <= arr[r]) {
            // If current height is greater than leftMax, update leftMax
            if (arr[l] >= leftMax) {
               leftMax = arr[l];
            }
            // Else add the trapped water (difference between leftMax and current height)
            else {
               res += leftMax - arr[l];
            }
            l++;
         }
         // If right boundary is smaller than left boundary
         else {
            // If current height is greater than rightMax, update rightMax
            if (arr[r] >= rightMax) {
               rightMax = arr[r];
            }
            // Else add the trapped water (difference between rightMax and current height)
            else {
               res += rightMax - arr[r];
            }
            r--;
         }
      }
      return res;
   }
}
