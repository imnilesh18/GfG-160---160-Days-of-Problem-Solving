/*
 * Find All Triplets with Zero Sum
 *
 * Given an array arr[], find all possible triplets i, j, k in the arr[] whose sum of elements is equals to zero.
 * Returned triplet should also be internally sorted i.e. i<j<k.
 *
 * Examples:
 *
 * Input: arr[] = [0, -1, 2, -3, 1]
 * Output: [[0, 1, 4], [2, 3, 4]]
 * Explanation: Triplets with sum 0 are:
 * arr[0] + arr[1] + arr[4] = 0 + (-1) + 1 = 0
 * arr[2] + arr[3] + arr[4] = 2 + (-3) + 1 = 0
 *
 * Input: arr[] = [1, -2, 1, 0, 5]
 * Output: [[0, 1, 2]]
 * Explanation: Only triplet which satisfies the condition is arr[0] + arr[1] + arr[2] = 1 + (-2) + 1 = 0
 *
 * Input: arr[] = [2, 3, 1, 0, 5]
 * Output: [[]]
 * Explanation: There is no triplet with sum 0.
 *
 * Constraints:
 * 3 <= arr.size() <= 10^3
 * -10^4 <= arr[i] <= 10^4
 */

/************************************************************ C++ ************************************************/

// Approach 1 (Brute Force): Use three nested loops to check all possible combinations of indices (i,j,k) where i<j<k and find if their corresponding array values sum to zero.
// TC: O(n³) - three nested loops to check all possible combinations of three indices.
// SC: O(1) - no extra space used except for result vector which is for output storage.
class Solution {
public:
   vector<vector<int> > findTriplets(vector<int>& arr){
      int n = arr.size();
      vector<vector<int> > result;

      // For each possible i, j, k combination where i < j < k
      for (int i = 0; i < n - 2; i++) {
         for (int j = i + 1; j < n - 1; j++) {
            for (int k = j + 1; k < n; k++) {
               // Check if sum is zero and add indices if true
               if (arr[i] + arr[j] + arr[k] == 0) {
                  result.push_back({ i, j, k });
               }
            }
         }
      }

      return result;    // Simply return empty vector if no triplets found
   }
};

// Approach 2 (Using Hashmap): Fix first element, use hashmap to store elements after it and their indices, then for each j find if needed element (0-arr[i]-arr[j]) exists in map.
// TC: O(n²) where n is array size as we use two nested loops and hashmap operations are O(1).
// SC: O(n) for storing elements and their indices in hashmap for each iteration of outer loop.
class Solution {
public:
   vector<vector<int> > findTriplets(vector<int>&arr){
      int n = arr.size();
      vector<vector<int> > result; // To store triplet indices

      // Fix first element arr[i]
      for (int i = 0; i < n - 2; i++) {
         // Hash map to store element -> indices mapping
         unordered_map<int, vector<int> > mp;

         // For each element after i
         for (int j = i + 1; j < n; j++) {
            // Calculate required third element to make sum zero
            int needed = 0 - arr[i] - arr[j];

            // If required element exists in hash map
            if (mp.count(needed)) {
               // Add all possible triplets using indices from map
               for (int k : mp[needed]) {
                  result.push_back({ i, k, j });
               }
            }

            // Store current element and its index in map
            mp[arr[j]].push_back(j);
         }
      }
      return result;
   }
};

/************************************************************ JAVA ************************************************/

// Approach 1 (Brute Force): Use three nested loops to check all possible combinations of indices (i,j,k) where i<j<k and find if their corresponding array values sum to zero.
// TC: O(n³) - three nested loops to check all possible combinations of three indices.
// SC: O(1) - no extra space used except for result vector which is for output storage.
class Solution {
   public List<List<Integer> > findTriplets(int[] arr){
      int n = arr.length;
      List<List<Integer> > result = new ArrayList<>();

      // For each possible i, j, k combination where i < j < k
      for (int i = 0; i < n - 2; i++) {
         for (int j = i + 1; j < n - 1; j++) {
            for (int k = j + 1; k < n; k++) {
               // Check if sum is zero and add indices if true
               if (arr[i] + arr[j] + arr[k] == 0) {
                  result.add(Arrays.asList(i, j, k));
               }
            }
         }
      }

      return result;
   }
}

// Approach 2 (Using Hashmap): Fix first element, use HashMap to store elements after it and their indices, then for each j find if needed element (0-arr[i]-arr[j]) exists in map.
// TC: O(n²) where n is array length as we use two nested loops and HashMap operations are O(1).
// SC: O(n) for storing elements and their indices in HashMap for each iteration of outer loop.
class Solution {
   public List<List<Integer> > findTriplets(int[] arr){
      int n = arr.length;
      List<List<Integer> > result = new ArrayList<>();

      // Fix first element arr[i]
      for (int i = 0; i < n - 2; i++) {
         // HashMap to store element -> indices mapping
         Map<Integer, List<Integer> > map = new HashMap<>();

         // For each element after i
         for (int j = i + 1; j < n; j++) {
            // Calculate required third element to make sum zero
            int needed = 0 - arr[i] - arr[j];

            // If required element exists in hash map
            if (map.containsKey(needed)) {
               // Add all possible triplets using indices from map
               for (int k : map.get(needed)) {
                  result.add(Arrays.asList(i, k, j));
               }
            }

            // Store current element and its index in map
            map.computeIfAbsent(arr[j], k->new ArrayList<>()).add(j);
         }
      }
      return result;
   }
}
