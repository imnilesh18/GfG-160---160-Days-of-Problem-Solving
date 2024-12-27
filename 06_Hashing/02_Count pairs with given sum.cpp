/*
 * Count pairs with given sum
 *
 * Given an array arr[] and an integer target. You have to find numbers of pairs in array arr[] which sums up to given target.
 *
 * Examples:
 *
 * Input: arr[] = [1, 5, 7, -1, 5], target = 6
 * Output: 3
 * Explanation: Pairs with sum 6 are (1, 5), (7, -1) and (1, 5).
 *
 * Input: arr[] = [1, 1, 1, 1], target = 2
 * Output: 6
 * Explanation: Pairs with sum 2 are (1, 1), (1, 1), (1, 1), (1, 1), (1, 1), (1, 1).
 *
 * Input: arr[] = [10, 12, 10, 15, -1], target = 125
 * Output: 0
 *
 * Constraints:
 * 1 <= arr.size() <= 10^5
 * -10^4 <= arr[i] <= 10^4
 * 1 <= target <= 10^4
 */

/************************************************************ C++ ************************************************/

// Approach: Use a hash map to store the frequency of elements, for each element, check if its complement (target - num) exists in the map, incrementing the count accordingly.
// Time Complexity: O(n) - Single traversal of the array with constant-time hash map operations.
// Space Complexity: O(n) - For storing elements and their frequencies in the hash map.
class Solution {
public:
   int countPairs(vector<int>&arr, int target){
      // Create a hash map to store the frequency of elements in the array
      unordered_map<int, int> mp;

      int cnt = 0;   // Initialize a counter for the number of valid pairs

      // Traverse the array
      for (int num : arr) {
         // Check if the complement (target - current number) exists in the map
         cnt += mp[target - num];

         // Increment the frequency of the current number in the map
         mp[num]++;
      }

      // Return the total count of pairs
      return cnt;
   }
};

/************************************************************ JAVA ************************************************/

// Approach: Use a HashMap to store frequencies of elements and count pairs by checking if the complement (target - num) exists in the map during traversal.
// Time Complexity: O(n) - Single traversal of the array and constant-time operations for HashMap.
// Space Complexity: O(n) - Space required to store elements in the HashMap.
class Solution {
   int countPairs(int arr[], int target){
      // Create a HashMap to store the frequency of elements
      HashMap<Integer, Integer> map = new HashMap<>();

      int count = 0;

      // Traverse the array
      for (int num : arr) {
         // Check if the complement (target - num) exists in the map and increment count
         count += map.getOrDefault(target - num, 0);

         // Update the frequency of the current element in the map
         map.put(num, map.getOrDefault(num, 0) + 1);
      }

      // Return the total count of pairs
      return count;
   }
}
