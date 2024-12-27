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

// Approach (Brute Force): Use three nested loops to check all possible combinations of indices (i,j,k) where i<j<k and find if their corresponding array values sum to zero.
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

/************************************************************ JAVA ************************************************/

// Approach (Brute Force): Use three nested loops to check all possible combinations of indices (i,j,k) where i<j<k and find if their corresponding array values sum to zero.
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
