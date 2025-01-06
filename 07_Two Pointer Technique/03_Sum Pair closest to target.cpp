/*
 * Sum Pair closest to target
 *
 * Given an array arr[] and a number target, find a pair of elements (a, b) in arr[], where a<=b whose sum is closest to target.
 * Note: Return the pair in sorted order and if there are multiple such pairs return the pair with maximum absolute difference. If no such pair exists return an empty array.
 *
 * Examples:
 *
 * Input: arr[] = [10, 30, 20, 5], target = 25
 * Output: [5, 20]
 * Explanation: As 5 + 20 = 25 is closest to 25.
 *
 * Input: arr[] = [5, 2, 7, 1, 4], target = 10
 * Output: [2, 7]
 * Explanation: As (4, 7) and (2, 7) both are closest to 10, but absolute difference of (2, 7) is 5 and (4, 7) is 3. Hence, [2, 7] has maximum absolute difference and closest to target.
 *
 * Input: arr[] = [10], target = 10
 * Output: []
 * Explanation: As the input array has only 1 element, return an empty array.
 *
 * Constraints:
 * 1 <= arr.size() <= 2*10^5
 * 0 <= target<= 2*10^5
 * 0 <= arr[i] <= 10^5
 */

/************************************************************ C++ ************************************************/

// Approach: Sort the array and use a two-pointer technique to find the pair of numbers whose sum is closest to the target. Update the closest sum dynamically during iteration.
// Time Complexity: O(nlogn + n), where O(nlogn) is for sorting and O(n) is for the two-pointer traversal.
// Space Complexity: O(1), as no extra space is used apart from a few variables.
class Solution {
public:
   vector<int> sumClosest(vector<int>& arr, int target){
      int         n = arr.size();
      vector<int> ans;

      // Sort the array to enable the two-pointer approach
      sort(arr.begin(), arr.end());   // O(nlogn)

      int l       = 0;
      int r       = n - 1;
      int minDiff = INT_MAX;   // Initialize the minimum difference as a large value

      // Use the two-pointer technique to find the closest pair sum
      while (l < r) {   // O(n)
         int sum = arr[l] + arr[r];

         // Update the result if the current sum is closer to the target
         if (abs(target - sum) < minDiff) {
            minDiff = abs(target - sum);
            ans     = { arr[l], arr[r] };
         }

         // Adjust pointers based on comparison of sum and target
         if (sum > target) {
            r--;     // Move the right pointer to decrease the sum
         } else if (sum < target) {
            l++;     // Move the left pointer to increase the sum
         } else {
            // If the sum equals the target, return the result immediately
            return ans;
         }
      }

      return ans;   // Return the closest pair
   }
};

/************************************************************ JAVA ************************************************/

// Approach: Sort the array and use a two-pointer technique to find the pair of numbers whose sum is closest to the target.
// Time Complexity: O(nlogn + n), where O(nlogn) is for sorting and O(n) is for the two-pointer traversal.
// Space Complexity: O(1), as no extra space is used apart from a few variables.
class Solution {
   public List<Integer> sumClosest(int[] arr, int target){
      int           n   = arr.length;
      List<Integer> ans = new ArrayList<>();

      // Sort the array to use the two-pointer technique
      Arrays.sort(arr);   // O(nlogn)

      int l       = 0;
      int r       = n - 1;
      int minDiff = Integer.MAX_VALUE;   // Initialize minimum difference

      // Use two-pointer approach to find the closest sum
      while (l < r) {   // O(n)
         int sum = arr[l] + arr[r];

         // Update the result if the current sum is closer to the target
         if (Math.abs(target - sum) < minDiff) {
            minDiff = Math.abs(target - sum);
            ans     = Arrays.asList(arr[l], arr[r]);
         }

         // Adjust pointers based on the comparison of sum and target
         if (sum > target) {
            r--;     // Decrease the sum by moving the right pointer
         } else if (sum < target) {
            l++;     // Increase the sum by moving the left pointer
         } else {
            // If the sum equals the target, return the result immediately
            return ans;
         }
      }

      return ans;   // Return the closest pair
   }
}
