/*
 * Equilibrium Point
 *
 * Given an array arr[] of non-negative numbers. The task is to find the first equilibrium point in the array.
 * The equilibrium point in an array is an index (0-based indexing) such that the sum of all elements before that index is the same as the sum of elements after it. Return -1 if no such point exists.
 *
 * Examples:
 * Input: arr[] = [1, 2, 0, 3]
 * Output: 2
 * Explanation: The sum of left of index 2 is 1 + 2 = 3 and sum on right of index 2 is 0 + 3 = 3.
 *
 * Input: arr[] = [1, 1, 1, 1]
 * Output: -1
 * Explanation: There is no equilibrium index in the array.
 *
 * Input: arr[] = [-7, 1, 5, 2, -4, 3, 0]
 * Output: 3
 * Explanation: The sum of left of index 3 is -7 + 1 + 5 = -1 and sum on right of index 3 is -4 + 3 + 0 = -1.
 *
 * Constraints:
 * 3 <= arr.size() <= 10^6
 * 0 <= arr[i] <= 10^9
 */

/************************************************************ C++ ************************************************/

// Approach 1: Use prefix and suffix arrays to store cumulative sums from the start and end of the array, respectively. Compare values at each index, and return the index where prefix sum equals suffix sum; otherwise, return -1.
// Time Complexity: O(n) - Two traversals to fill prefix and suffix arrays and one for comparison.
// Space Complexity: O(n) - For storing prefix and suffix arrays.
class Solution {
public:
   // Function to find the equilibrium point in the array.
   int findEquilibrium(vector<int>&arr){
      int n = arr.size();   // Get the size of the array

      // Edge case: If array has less than 3 elements, no equilibrium point can exist.
      if (n < 3) {
         return -1;
      }

      // Create a prefix sum array to store cumulative sums from the start of the array.
      vector<int> prefix(n, 0);
      prefix[0] = arr[0];   // Initialize the first element of prefix with the first element of arr

      // Fill the prefix sum array
      for (int i = 1; i < n; i++) {
         prefix[i] = prefix[i - 1] + arr[i];
      }

      // Create a suffix sum array to store cumulative sums from the end of the array.
      vector<int> suffix(n, 0);
      suffix[n - 1] = arr[n - 1];   // Initialize the last element of suffix with the last element of arr

      // Fill the suffix sum array
      for (int i = n - 2; i >= 0; i--) {
         suffix[i] = suffix[i + 1] + arr[i];
      }

      // Iterate through the array to find the equilibrium index
      for (int i = 0; i < n; i++) {
         // Check if the prefix sum at index i equals the suffix sum at index i
         if (prefix[i] == suffix[i]) {
            return i;     // Return the equilibrium index
         }
      }

      // If no equilibrium index is found, return -1
      return -1;
   }
};

// Approach 2: Calculate the totalSum of the array. Iterate through the array, dynamically calculate suffixSum using the formula suffixSum = totalSum - prefixSum - arr[i]. Check if prefixSum == suffixSum. If true, return the index. Update prefixSum after checking. If no equilibrium point exists, return -1.
// Time Complexity: O(n) - Single traversal of the array and O(n) for accumulate.
// Space Complexity: O(1) - No extra space used apart from a few variables.
class Solution {
public:
   // Function to find equilibrium point in the array.
   int findEquilibrium(vector<int>&arr){
      int n = arr.size();   // Get the size of the array

      // Calculate the total sum of the array elements
      int totalSum = accumulate(arr.begin(), arr.end(), 0);

      int prefixSum = 0;   // Initialize prefix sum to 0

      // Iterate through the array
      for (int i = 0; i < n; i++) {
         // Calculate suffix sum for the current index
         int suffixSum = totalSum - prefixSum - arr[i];

         // Check if the prefix sum equals the suffix sum
         if (prefixSum == suffixSum) {
            return i;     // Return the equilibrium index
         }

         // Update the prefix sum by adding the current element
         prefixSum += arr[i];
      }

      // If no equilibrium index is found, return -1
      return -1;
   }
};

/************************************************************ JAVA ************************************************/

// Approach 1: Use prefix and suffix arrays to store cumulative sums from the start and end of the array, respectively. Compare values at each index, and return the index where prefix sum equals suffix sum; otherwise, return -1.
// Time Complexity: O(n) - Two traversals to fill prefix and suffix arrays and one for comparison.
// Space Complexity: O(n) - For storing prefix and suffix arrays.
class Solution {
   // Function to find equilibrium point in the array.
   public static int findEquilibrium(int[] arr){
      int n = arr.length;   // Get the size of the array

      // Edge case: If array has less than 3 elements, no equilibrium point can exist.
      if (n < 3) {
         return -1;
      }

      // Create a prefix sum array to store cumulative sums from the start of the array.
      int[] prefix = new int[n];
      prefix[0]    = arr[0]; // Initialize the first element of prefix with the first element of arr

      // Fill the prefix sum array
      for (int i = 1; i < n; i++) {
         prefix[i] = prefix[i - 1] + arr[i];
      }

      // Create a suffix sum array to store cumulative sums from the end of the array.
      int[] suffix  = new int[n];
      suffix[n - 1] = arr[n - 1];   // Initialize the last element of suffix with the last element of arr

      // Fill the suffix sum array
      for (int i = n - 2; i >= 0; i--) {
         suffix[i] = suffix[i + 1] + arr[i];
      }

      // Iterate through the array to find the equilibrium index
      for (int i = 0; i < n; i++) {
         // Check if the prefix sum at index i equals the suffix sum at index i
         if (prefix[i] == suffix[i]) {
            return i;     // Return the equilibrium index
         }
      }

      // If no equilibrium index is found, return -1
      return -1;
   }
}

// Approach 2: Calculate totalSum of the array, then iterate through the array to dynamically calculate suffixSum using the formula suffixSum = totalSum - prefixSum - arr[i]. Compare prefixSum with suffixSum, and return the index where they match. If no equilibrium point is found, return -1.
// Time Complexity: O(n) - Single traversal of the array for calculating totalSum and one for comparison.
// Space Complexity: O(1) - No extra space used apart from a few variables.
class Solution {
   // Function to find equilibrium point in the array.
   public static int findEquilibrium(int[] arr){
      int n = arr.length;    // Get the size of the array

      // Calculate the total sum of the array elements
      int totalSum = 0;

      for (int num : arr) {
         totalSum += num;
      }

      int prefixSum = 0;     // Initialize prefix sum to 0

      // Iterate through the array
      for (int i = 0; i < n; i++) {
         // Calculate suffix sum for the current index
         int suffixSum = totalSum - prefixSum - arr[i];

         // Check if the prefix sum equals the suffix sum
         if (prefixSum == suffixSum) {
            return i;         // Return the equilibrium index
         }

         // Update the prefix sum by adding the current element
         prefixSum += arr[i];
      }

      // If no equilibrium index is found, return -1
      return -1;
   }
}
