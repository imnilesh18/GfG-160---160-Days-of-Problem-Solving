/*
 * Count Subarrays with given XOR
 *
 * Given an array of integers arr[] and a number k, count the number of subarrays having XOR of their elements as k.
 *
 * Examples:
 *
 * Input: arr[] = [4, 2, 2, 6, 4], k = 6
 * Output: 4
 * Explanation: The subarrays having XOR of their elements as 6 are [4, 2], [4, 2, 2, 6, 4], [2, 2, 6], and [6]. Hence, the answer is 4.
 *
 * Input: arr[] = [5, 6, 7, 8, 9], k = 5
 * Output: 2
 * Explanation: The subarrays having XOR of their elements as 5 are [5] and [5, 6, 7, 8, 9]. Hence, the answer is 2.
 *
 * Constraints:
 * 1 ≤ arr.size() ≤ 10^5
 * 0 ≤ arr[i] ≤ 10^5
 * 0 ≤ k ≤ 10^5
 */

/************************************************************ C++ ************************************************/

// Approach: Use prefix XOR technique with HashMap, storing XOR frequencies and finding subarrays with XOR k by checking for existing prefix XORs where y ^ k = cumXOR.
// Time Complexity: O(n) as we traverse array once and all hashmap operations take O(1) average time.
// Space Complexity: O(n) to store at most n cumulative XORs in the hashmap.
class Solution {
public:
   long subarrayXor(vector<int>&arr, int k){
      // Hash map to store the frequency of prefix XOR values
      unordered_map<int, int> mp;

      // Result variable to store count of subarrays with XOR = k
      // Using long to handle large counts
      long result = 0;

      // Variable to store running/cumulative XOR
      int cumXOR = 0;

      // Initialize map with XOR value 0 occurring once
      // This handles the case when prefix subarray has XOR = k
      mp.insert({ 0, 1 });

      // Traverse through the array
      for (int i = 0; i < arr.size(); i++) {
         // Update cumulative XOR by including current element
         cumXOR = cumXOR ^ arr[i];

         // Find value x such that (cumXOR ^ x = k)
         // Therefore x = (cumXOR ^ k)
         // If such x exists in map, those prefixes can form subarrays with XOR = k
         int x = cumXOR ^ k;

         // If x exists in map, add its frequency to result
         // as these many subarrays will have XOR = k
         if (mp.find(x) != mp.end()) {
            result += mp[x];
         }

         // Increment frequency of current cumulative XOR in map
         mp[cumXOR]++;
      }
      return result;
   }
};

/************************************************************ JAVA ************************************************/

// Approach: Use prefix XOR technique with HashMap, maintaining cumulative XOR and using the property that for any subarray with XOR k, there exists a prefix y where y ^ k = cumXOR.
// Time Complexity: O(n) where n is length of array as we traverse once and HashMap operations are O(1) average case.
// Space Complexity: O(n) to store at most n prefix XORs in the HashMap.
class Solution {
   public long subarrayXor(int arr[], int k){
      // HashMap to store the frequency of prefix XOR values
      HashMap<Integer, Integer> map = new HashMap<>();

      // Result variable to store count of subarrays with XOR = k
      // Using long to handle large counts
      long result = 0;

      // Variable to store running/cumulative XOR
      int cumXOR = 0;

      // Initialize map with XOR value 0 occurring once
      // This handles the case when prefix subarray has XOR = k
      map.put(0, 1);

      // Traverse through the array
      for (int i = 0; i < arr.length; i++) {
         // Update cumulative XOR by including current element
         cumXOR = cumXOR ^ arr[i];

         // Find value x such that (cumXOR ^ x = k)
         // Therefore x = (cumXOR ^ k)
         // If such x exists in map, those prefixes can form subarrays with XOR = k
         int x = cumXOR ^ k;

         // If x exists in map, add its frequency to result
         // as these many subarrays will have XOR = k
         if (map.containsKey(x)) {
            result += map.get(x);
         }

         // Increment frequency of current cumulative XOR in map
         map.put(cumXOR, map.getOrDefault(cumXOR, 0) + 1);
      }
      return result;
   }
}
