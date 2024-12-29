/*
 * Intersection of Two arrays with Duplicate Elements
 *
 * Given two integer arrays a[] and b[], you have to find the intersection of the two arrays. Intersection of two arrays is said to be elements that are common in both arrays. The intersection should not have duplicate elements and the result should contain items in any order.
 *
 * Note: The driver code will sort the resulting array in increasing order before printing.
 *
 * Examples:
 *
 * Input: a[] = [1, 2, 1, 3, 1], b[] = [3, 1, 3, 4, 1]
 * Output: [1, 3]
 * Explanation: 1 and 3 are the only common elements and we need to print only one occurrence of common elements.
 *
 * Input: a[] = [1, 1, 1], b[] = [1, 1, 1, 1, 1]
 * Output: [1]
 * Explanation: 1 is the only common element present in both the arrays.
 *
 * Input: a[] = [1, 2, 3], b[] = [4, 5, 6]
 * Output: []
 * Explanation: No common element in both the arrays.
 *
 * Constraints:
 * 1 ≤ a.size(), b.size() ≤ 10^5
 * 1 ≤ a[i], b[i] ≤ 10^5
 */

/************************************************************ C++ ************************************************/

// Approach 1 (Using hashmap): Use hash map to store frequency of first array elements, then check second array elements against it while ensuring no duplicates by marking used elements.
// TC: O(n + m) where n and m are lengths of arrays, as we traverse each array once and hash map operations are O(1).
// SC: O(min(n, m)) to store unique elements from the smaller array in the hash map.
class Solution {
public:
   vector<int> intersectionWithDuplicates(vector<int>& a, vector<int>& b){
      // Create a hash map to store frequency of elements from first array
      unordered_map<int, int> mp;

      // Vector to store the final result of common elements
      vector<int> result;

      // Count frequency of each element in first array 'a'
      // If element appears multiple times, its count will be > 1
      for (auto num : a) {
         mp[num]++;
      }

      // Check each element of second array 'b'
      for (auto num : b) {
         // If element exists in hash map and hasn't been used yet (count > 0)
         // This ensures we only add each common element once
         if (mp[num] > 0) {
            // Add the common element to result
            result.push_back(num);
            // Set count to 0 to mark this element as processed
            // This prevents adding duplicates to result
            mp[num] = 0;
         }
      }

      // Return the vector containing all common elements without duplicates
      return result;
   }
};

// Approach 2 (Using HashSet): Create a set of unique elements from first array, then check each element of second array against this set while ensuring no duplicates using find().
// TC: O(n) for creating set and O(n^2) for find operations in vector, making overall complexity O(n^2).
// SC: O(n) to store unique elements from first array in unordered_set and result vector.
class Solution {
public:
   vector<int> intersectionWithDuplicates(vector<int>& a, vector<int>& b) {
       // Vector to store common elements without duplicates 
       vector<int> result;
       
       // Store unique elements from first array in a hash set
       unordered_set<int> st;
       for(int num : a) {
           st.insert(num);
       }
       
       // Iterate through second array to find common elements
       for(int num : b) {
           // If number exists in set (is common) AND hasn't been added to result yet
           // count() checks if element exists in set
           // find() returns iterator to end if element not found in result vector
           if(st.count(num) && find(result.begin(), result.end(), num) == result.end()) {
               // Add the common element to result vector
               result.push_back(num);
           }
       }
       
       // Return vector containing intersection without duplicates
       return result;
   }
};

/************************************************************ JAVA ************************************************/

// Approach 1 (Using HashMap): Create a frequency map for first array elements, check second array against it and add to result while marking used elements with count=0.
// TC: O(n + m) where n and m are lengths of arrays since we traverse each array once with O(1) map operations.
// SC: O(min(n,m)) to store unique elements from smaller array in HashMap.
class Solution {
    public ArrayList<Integer> intersectionWithDuplicates(int[] a, int[] b) {
        // Create HashMap to store frequency of elements from first array
        HashMap<Integer, Integer> map = new HashMap<>();
        
        // ArrayList to store the result
        ArrayList<Integer> result = new ArrayList<>();
        
        // Count frequency of elements in first array
        for(int num : a) {
            map.put(num, map.getOrDefault(num, 0) + 1);
        }
        
        // Check elements in second array
        for(int num : b) {
            // If element exists and hasn't been used
            if(map.getOrDefault(num, 0) > 0) {
                result.add(num);
                // Mark as used by setting count to 0
                map.put(num, 0);
            }
        }
        
        return result;
    }
}

// Approach 2 (Using HashSet): Create a HashSet of unique elements from first array, then check each element of second array against this set while ensuring no duplicates.
// TC: O(n^2) due to contains() operation on ArrayList in each iteration of second loop.
// SC: O(n) to store unique elements from first array in HashSet and result ArrayList.
class Solution {
   public ArrayList<Integer> intersectionWithDuplicates(int[] a, int[] b) {
       // ArrayList to store common elements without duplicates
       ArrayList<Integer> result = new ArrayList<>();
       
       // Store unique elements from first array in a HashSet
       HashSet<Integer> st = new HashSet<>();
       for(int num : a) {
           st.add(num);
       }
       
       // Iterate through second array to find common elements 
       for(int num : b) {
           // If number exists in set AND hasn't been added to result yet 
           // contains() checks if element exists in set/result
           if(st.contains(num) && !result.contains(num)) {
               // Add the common element to result list
               result.add(num);
           }
       }
       
       return result;
   }
}