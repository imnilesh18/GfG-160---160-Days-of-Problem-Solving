/*
 * Count distinct elements in every window
 *
 * Given an integer array arr[] and a number k. Find the count of distinct elements in every window of size k in the array.
 *
 * Examples:
 *
 * Input: arr[] = [1, 2, 1, 3, 4, 2, 3], k = 4
 * Output:  [3, 4, 4, 3]
 * Explanation: Window 1 of size k = 4 is 1 2 1 3. Number of distinct elements in this window are 3.
 * Window 2 of size k = 4 is 2 1 3 4. Number of distinct elements in this window are 4.
 * Window 3 of size k = 4 is 1 3 4 2. Number of distinct elements in this window are 4.
 * Window 4 of size k = 4 is 3 4 2 3. Number of distinct elements in this window are 3.
 *
 * Input: arr[] = [4, 1, 1], k = 2
 * Output: [2, 1]
 * Explanation: Window 1 of size k = 2 is 4 1. Number of distinct elements in this window are 2.
 * Window 2 of size k = 2 is 1 1. Number of distinct elements in this window is 1.
 *
 * Input: arr[] = [1, 1, 1, 1, 1], k = 3
 * Output: [1, 1, 1]
 *
 * Constraints:
 * 1 <= k <= arr.size() <= 10^5
 * 1 <= arr[i] <= 10^5
 */

/************************************************************ C++ ************************************************/

// Approach: Use sliding window technique with hashmap, where for each window of size k we track frequency of elements. Map's size gives us count of distinct elements since duplicate elements are counted only once.
// TC: O(0 -> k -> n) = O(0 + k + (n-k)) ≈ O(n) [Window initialization: O(k), Sliding window processing: O(n-k)]
// SC: O(n) which includes storage for result array of size (n-k+1) and hashmap storing at most k elements at any time
class Solution {
public:
   vector<int> countDistinct(vector<int>&arr, int k){
      // Vector to store count of distinct elements for each window
      vector<int> result;

      // Hash map to store frequency of elements in current window
      unordered_map<int, int> mp;

      // Process first window of size k
      for (int i = 0; i < k; i++) {
         mp[arr[i]]++;     // Add elements and their frequencies to map
      }

      // Add count of distinct elements in first window
      result.push_back(mp.size());

      // Process remaining windows
      for (int i = k; i < arr.size(); i++) {
         // Remove leftmost element of previous window
         mp[arr[i - k]]--;

         // If frequency becomes 0, remove element from map
         if (mp[arr[i - k]] == 0) {
            mp.erase(arr[i - k]);
         }

         // Add new element to current window
         mp[arr[i]]++;

         // Add count of distinct elements in current window
         result.push_back(mp.size());
      }

      return result;
   }
};

/************************************************************ JAVA ************************************************/

// Approach: Use sliding window technique with hashmap, where for each window of size k we track frequency of elements. Map's size gives us count of distinct elements since duplicate elements are counted only once.
// TC: O(0 -> k -> n) = O(0 + k + (n-k)) ≈ O(n) [Window initialization: O(k), Sliding window processing: O(n-k)]
// SC: O(n) which includes storage for ArrayList of size (n-k+1) and HashMap storing at most k elements at any time
class Solution {
   ArrayList<Integer> countDistinct(int arr[], int k){
      // ArrayList to store count of distinct elements for each window
      ArrayList<Integer> result = new ArrayList<>();

      // HashMap to store frequency of elements in current window
      HashMap<Integer, Integer> mp = new HashMap<>();

      // Process first window of size k
      for (int i = 0; i < k; i++) {
         mp.put(arr[i], mp.getOrDefault(arr[i], 0) + 1);
      }

      // Add count of distinct elements in first window
      result.add(mp.size());

      // Process remaining windows
      for (int i = k; i < arr.length; i++) {
         // Remove leftmost element of previous window
         mp.put(arr[i - k], mp.get(arr[i - k]) - 1);

         // If frequency becomes 0, remove element from map
         if (mp.get(arr[i - k]) == 0) {
            mp.remove(arr[i - k]);
         }

         // Add new element to current window
         mp.put(arr[i], mp.getOrDefault(arr[i], 0) + 1);

         // Add count of distinct elements in current window
         result.add(mp.size());
      }

      return result;
   }
}
