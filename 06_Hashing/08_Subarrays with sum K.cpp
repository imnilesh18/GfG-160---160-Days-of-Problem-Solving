/*
 * Subarrays with sum K
 *
 * Given an unsorted array of integers, find the number of continuous subarrays having sum exactly equal to a given number k.
 *
 * Examples:
 *
 * Input: arr = [10, 2, -2, -20, 10], k = -10
 * Output: 3
 * Explaination: Subarrays: arr[0...3], arr[1...4], arr[3...4] have sum exactly equal to -10.
 *
 * Input: arr = [9, 4, 20, 3, 10, 5], k = 33
 * Output: 2
 * Explaination: Subarrays: arr[0...2], arr[2...4] have sum exactly equal to 33.
 *
 * Input: arr = [1, 3, 5], k = 0
 * Output: 0
 * Explaination: No subarray with 0 sum.
 *
 * Constraints:
 * 1 ≤ arr.size() ≤ 10^5
 * -10^3 ≤ arr[i] ≤ 10^3
 * -10^7 ≤ k ≤ 10^7
 */

/************************************************************ C++ ************************************************/

// Approach: Use prefix sum and hash map to store cumulative sum frequencies. For each index, check if (cumSum - k) exists in map, which indicates presence of a subarray with sum k.
// Time Complexity: O(n) where n is the size of input array as we traverse the array once.
// Space Complexity: O(n) to store cumulative sums in the hash map.
class Solution {
public:
   int countSubarrays(vector<int>& arr, int k){
      // Map to store cumulative sum frequencies
      unordered_map<int, int> mp;
      int result = 0;

      // Running sum of elements
      int cumSum = 0;

      // Initialize map with sum 0 having frequency 1
      // This handles the case when the entire subarray from start has sum k
      mp.insert({ 0, 1 });

      for (int i = 0; i < arr.size(); i++) {
         // Add current element to running sum
         cumSum += arr[i];

         // If (cumSum - k) exists in map, it means we found a subarray with sum k
         // Add its frequency to result
         if (mp.find(cumSum - k) != mp.end()) {
            result += mp[cumSum - k];
         }

         // Increment frequency of current cumulative sum in map
         mp[cumSum]++;
      }

      return result;
   }
};

/************************************************************ JAVA ************************************************/

// Approach: Use prefix sum technique with HashMap to store frequencies of cumulative sums and find subarrays with sum k by checking if (cumSum - k) exists in map.
// Time Complexity: O(n) where n is length of array since we traverse array once and HashMap operations are O(1) on average.
// Space Complexity: O(n) to store at most n cumulative sums in the HashMap.
class Solution {
    public int countSubarrays(int arr[], int k) {
        // HashMap to store the frequency of cumulative sums
        HashMap<Integer, Integer> map = new HashMap<>();
        
        // Initialize variables for result and running sum
        int result = 0;
        int cumSum = 0;
        
        // Initialize map with sum 0 having count 1
        // This handles the case when subarray starts from index 0
        map.put(0, 1);
        
        // Traverse through the array
        for(int i = 0; i < arr.length; i++) {
            // Add current element to cumulative sum
            cumSum += arr[i];
            
            // If (cumSum - k) exists in map, add its frequency to result
            // This means we found a subarray with sum k
            if(map.containsKey(cumSum - k)) {
                result += map.get(cumSum - k);
            }
            
            // Add or update the frequency of current cumulative sum in map
            map.put(cumSum, map.getOrDefault(cumSum, 0) + 1);
        }
        
        return result;
    }
}