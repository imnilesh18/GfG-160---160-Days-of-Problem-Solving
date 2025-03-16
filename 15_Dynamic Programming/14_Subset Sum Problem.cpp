/*
 * Subset Sum Problem
 *
 * Given an array of positive integers arr[] and a value sum, determine if there is a subset of arr[] with sum equal to given sum.
 *
 * Examples:
 *
 * Input: arr[] = [3, 34, 4, 12, 5, 2], sum = 9
 * Output: true
 * Explanation: Here there exists a subset with target sum = 9, 4+3+2 = 9.
 *
 * Input: arr[] = [3, 34, 4, 12, 5, 2], sum = 30
 * Output: false
 * Explanation: There is no subset with target sum 30.
 *
 * Input: arr[] = [1, 2, 3], sum = 6
 * Output: true
 * Explanation: The entire array can be taken as a subset, giving 1 + 2 + 3 = 6.
 *
 * Constraints:
 * 1 <= arr.size() <= 200
 * 1<= arr[i] <= 200
 * 1<= sum <= 10^4
 */

/************************************************************ C++ ************************************************/

// Approach (My Approach): We use recursion with memoization (2D array) to explore all subset possibilities, caching results for each (idx, currentSum) state.
// Time Complexity: O(n * sum) because we compute at most n * sum states where n is the size of arr and sum is the target.
// Space Complexity: O(n * sum) for the memoization table plus O(n) for the recursion call stack in the worst case.
class Solution {
public:
    int t[201][10001];     // Memoization table dimensions: idx 0..200 and currentSum 0..10000

    bool solve(vector<int>& arr, int sum, int currentSum, int idx) {
        // If we reached the target sum, return true.
        if (currentSum == sum) {
            return true;
        }
        // If currentSum exceeds sum or no more elements to choose from, return false.
        if (currentSum > sum || idx >= arr.size()) {
            return false;
        }

        // If this state has already been computed, return the stored value.
        if (t[idx][currentSum] != -1) {
            return t[idx][currentSum];
        }

        // Explore the decision to include the current element (take) or exclude it (skip).
        bool take = solve(arr, sum, currentSum + arr[idx], idx + 1);
        bool skip = solve(arr, sum, currentSum, idx + 1);

        // Save the computed result in the memoization table and return it.
        return t[idx][currentSum] = (take || skip);
    }
    bool isSubsetSum(vector<int>& arr, int sum) {
        // Initialize memoization table with -1 to indicate uncomputed states.
        memset(t, -1, sizeof(t));
        return solve(arr, sum, 0, 0);
    }
};

/*
 * Dry Run:
 * Input: arr = [3, 34, 4, 12, 5, 2], sum = 9
 *
 * 1. Start at idx = 0, currentSum = 0.
 * - Include arr[0] (3) → new state: idx = 1, currentSum = 3.
 * 2. At idx = 1, currentSum = 3.
 * - Include arr[1] (34) → new state: idx = 2, currentSum = 37 (exceeds 9, returns false).
 * - Exclude arr[1] → new state: idx = 2, currentSum = 3.
 * 3. At idx = 2, currentSum = 3.
 * - Include arr[2] (4) → new state: idx = 3, currentSum = 7.
 * 4. At idx = 3, currentSum = 7.
 * - Include arr[3] (12) → new state: idx = 4, currentSum = 19 (exceeds 9, returns false).
 * - Exclude arr[3] → new state: idx = 4, currentSum = 7.
 * 5. At idx = 4, currentSum = 7.
 * - Include arr[4] (5) → new state: idx = 5, currentSum = 12 (exceeds 9, returns false).
 * - Exclude arr[4] → new state: idx = 5, currentSum = 7.
 * 6. At idx = 5, currentSum = 7.
 * - Include arr[5] (2) → new state: idx = 6, currentSum = 9 (equals target, returns true).
 * - Since a valid subset is found, true propagates back through all recursive calls.
 *
 * Output: true
 */

/************************************************************ JAVA ************************************************/

// Approach (My Approach): We use recursion with memoization (2D array) to explore all subset possibilities, caching results for each (idx, currentSum) state.
// Time Complexity: O(n * sum) because we compute at most n * sum states, where n is the number of elements and sum is the target.
// Space Complexity: O(n * sum) for the memoization table plus O(n) for the recursion call stack in worst case.
class Solution {
    static int[][] t = new int[201][10001]; // Memoization table: dimensions idx 0..200 and currentSum 0..10000

    static boolean solve(int[] arr, int sum, int currentSum, int idx) {
        // If we reached the target sum, return true.
        if (currentSum == sum) {
            return true;
        }
        // If currentSum exceeds sum or no more elements to choose from, return false.
        if (currentSum > sum || idx >= arr.length) {
            return false;
        }

        // If this state has already been computed, return the stored value.
        if (t[idx][currentSum] != -1) {
            return t[idx][currentSum] == 1;
        }

        // Explore the decision to include the current element (take) or exclude it (skip).
        boolean take = solve(arr, sum, currentSum + arr[idx], idx + 1);
        boolean skip = solve(arr, sum, currentSum, idx + 1);

        // Save the computed result in the memoization table.
        t[idx][currentSum] = (take || skip) ? 1 : 0;
        return take || skip;
    }
    static Boolean isSubsetSum(int arr[], int sum) {
        // Initialize memoization table with -1 indicating uncomputed states.
        for (int i = 0; i < t.length; i++) {
            for (int j = 0; j < t[0].length; j++) {
                t[i][j] = -1;
            }
        }
        return solve(arr, sum, 0, 0);
    }
}

/*
 * Dry Run:
 * Input: arr = [3, 34, 4, 12, 5, 2], sum = 9
 *
 * 1. Start at idx = 0, currentSum = 0.
 * - Include arr[0] (3) → new state: idx = 1, currentSum = 3.
 * 2. At idx = 1, currentSum = 3.
 * - Include arr[1] (34) → new state: idx = 2, currentSum = 37 (exceeds 9, returns false).
 * - Exclude arr[1] → new state: idx = 2, currentSum = 3.
 * 3. At idx = 2, currentSum = 3.
 * - Include arr[2] (4) → new state: idx = 3, currentSum = 7.
 * 4. At idx = 3, currentSum = 7.
 * - Include arr[3] (12) → new state: idx = 4, currentSum = 19 (exceeds 9, returns false).
 * - Exclude arr[3] → new state: idx = 4, currentSum = 7.
 * 5. At idx = 4, currentSum = 7.
 * - Include arr[4] (5) → new state: idx = 5, currentSum = 12 (exceeds 9, returns false).
 * - Exclude arr[4] → new state: idx = 5, currentSum = 7.
 * 6. At idx = 5, currentSum = 7.
 * - Include arr[5] (2) → new state: idx = 6, currentSum = 9 (equals target, returns true).
 * - Since a valid subset is found, true propagates back through all recursive calls.
 *
 * Output: true
 */
