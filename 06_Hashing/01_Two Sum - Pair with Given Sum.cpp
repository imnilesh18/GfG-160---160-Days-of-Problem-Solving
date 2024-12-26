/*
 * Two Sum - Pair with Given Sum
 *
 * Given an array arr[] of positive integers and another integer target. Determine if there exists two distinct indices such that the sum of there elements is equals to target.
 *
 * Examples:
 * Input: arr[] = [1, 4, 45, 6, 10, 8], target = 16
 * Output: true
 * Explanation: arr[3] + arr[4] = 6 + 10 = 16.
 *
 * Input: arr[] = [1, 2, 4, 3, 6], target = 11
 * Output: false
 * Explanation: None of the pair makes a sum of 11.
 *
 * Constraints:
 * 1 ≤ arr.size ≤ 10^5
 * 1 ≤ arr[i] ≤ 10^5
 * 1 ≤ target ≤ 2*10^5
 */

/************************************************************ C++ ************************************************/

// Approach: Use an unordered set to keep track of elements seen so far. For each element in the array, calculate its complement (target - arr[i]). If the complement exists in the set, return true. Otherwise, add the current element to the set. If no pair is found after traversing the array, return false.
// Time Complexity: O(n) - Each element is processed once, and set operations (find, insert) are O(1) on average.
// Space Complexity: O(n) - Additional space is used to store elements in the unordered set.
class Solution {
public:
   bool twoSum(vector<int>& arr, int target){
      unordered_set<int> st;   // To store elements we've encountered

      for (int num : arr) {
         int remaining = target - num;

         // Check if the complement exists in the set
         if (st.find(remaining) != st.end()) {
            return true;     // Pair found
         }

         // Add the current number to the set
         st.insert(num);
      }

      return false;   // No such pair found
   }
};

/************************************************************ JAVA ************************************************/

// Approach: Traverse the array while maintaining a HashSet to store elements seen so far. For each element, compute its complement (target - num) and check if it exists in the set. If it does, return true. Otherwise, add the current element to the set. If the loop completes without finding a pair, return false.
// Time Complexity: O(n) - The array is traversed once, and each HashSet operation (add and contains) is O(1) on average.
// Space Complexity:O(n) - In the worst case, the HashSet stores all n elements of the array.
class Solution {
   boolean twoSum(int arr[], int target){
      // Create a set to store elements of the array
      HashSet<Integer> st = new HashSet<>();

      // Traverse the array
      for (int num : arr) {
         // Calculate the complement
         int complement = target - num;

         // Check if the complement exists in the set
         if (st.contains(complement)) {
            return true;     // Pair found
         }

         // Add the current element to the set
         st.add(num);
      }

      // If no pair is found, return false
      return false;
   }
}
