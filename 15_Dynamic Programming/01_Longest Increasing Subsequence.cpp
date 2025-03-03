/*
 * Longest Increasing Subsequence
 *
 * Given an array arr[] of non-negative integers, the task is to find the length of the Longest Strictly Increasing Subsequence (LIS).
 *
 * A subsequence is strictly increasing if each element in the subsequence is strictly less than the next element.
 *
 * Examples:
 *
 * Input: arr[] = [5, 8, 3, 7, 9, 1]
 * Output: 3
 * Explanation: The longest strictly increasing subsequence could be [5, 7, 9], which has a length of 3.
 *
 * Input: arr[] = [0, 8, 4, 12, 2, 10, 6, 14, 1, 9, 5, 13, 3, 11, 7, 15]
 * Output: 6
 * Explanation: One of the possible longest strictly increasing subsequences is [0, 2, 6, 9, 13, 15], which has a length of 6.
 *
 * Input: arr[] = [3, 10, 2, 1, 20]
 * Output: 3
 * Explanation: The longest strictly increasing subsequence could be [3, 10, 20], which has a length of 3.
 *
 * Constraints:
 * 1 ≤ arr.size() ≤ 10^3
 * 0 ≤ arr[i] ≤ 10^6
 */

/************************************************************ C++ ************************************************/

// Approach 1 (Recursion): Use recursion to explore two possibilities at each element – either include the element (if it forms a strictly increasing sequence) or skip it – and return the maximum length obtained.
// Time Complexity: O(2^n) in the worst-case scenario since each element leads to two recursive calls (include or skip).
// Space Complexity: O(n) due to the maximum depth of the recursion stack.
class Solution {
public:
    int n;

    int solve(vector<int>& arr, int i, int P) {
        if (i >= n) {
            return 0;   // Base case: no more elements to process.
        }

        int take = 0;
        // If no previous element chosen (P == -1) or current element is greater than the last chosen element, consider taking it.
        if (P == -1 || arr[i] > arr[P]) {
            take = 1 + solve(arr, i + 1, i);
        }

        // Explore the option of skipping the current element.
        int skip = solve(arr, i + 1, P);
        return max(take, skip);
    }
    
    int lis(vector<int>& arr) {
        n = arr.size();
        return solve(arr, 0, -1);   // Start recursion with index 0 and no previous element.
    }
};

/*
 * Dry Run:
 * Input: arr[] = [5, 8, 3, 7, 9, 1]
 *
 * 1. Call lis(arr):
 * - n = 6
 * - Call solve(arr, 0, -1)
 *
 * 2. In solve(arr, 0, -1):
 * - i = 0, P = -1: Can take element 5.
 * - "Take" branch: 1 + solve(arr, 1, 0)
 * - "Skip" branch: solve(arr, 1, -1)
 *
 * 3. In solve(arr, 1, 0) (after taking 5):
 * - i = 1, P = 0: arr[1] = 8 > arr[0] = 5, can take 8.
 * - "Take" branch: 1 + solve(arr, 2, 1)
 * - "Skip" branch: solve(arr, 2, 0)
 *
 * 4. The recursion continues, exploring each branch:
 * - One valid path is: [5 (i=0), 7 (i=3), 9 (i=4)] yielding length 3.
 * - All branches are evaluated and the maximum length is returned.
 *
 * Final Output: The length of the longest strictly increasing subsequence is 3.
 */

// Approach 2 (Recursion + Memoization): Use recursion with memoization to avoid redundant calculations.
// At each element, decide whether to include it (if it forms a strictly increasing sequence) or skip it, and memoize the results to optimize overlapping subproblems.
// Time Complexity: O(n^2) due to exploring at most n*n states (each combination of index and previous index).
// Space Complexity: O(n^2) for the memoization table plus O(n) for the recursion stack.
class Solution {
public:
    int n;
    int t[1001][1001];

    int solve(vector<int>& arr, int i, int P) {
        if (i >= n) {
            return 0;   // Base case: Reached the end of the array.
        }

        // Return the memoized result if available for state (i, P) (only if P != -1)
        if (P != -1 && t[i][P] != -1) {
            return t[i][P];
        }

        int take = 0;
        // If no previous element is chosen (P == -1) or the current element is greater than the last chosen, include it.
        if (P == -1 || arr[i] > arr[P]) {
            take = 1 + solve(arr, i + 1, i);
        }

        // Option to skip the current element.
        int skip = solve(arr, i + 1, P);

        // Memoize the result for the current state if P is not -1.
        if (P != -1) {
            t[i][P] = max(take, skip);
        }

        return max(take, skip);
    }

    int lis(vector<int>& arr) {
        n = arr.size();
        memset(t, -1, sizeof(t));   // Initialize the memoization table with -1.
        return solve(arr, 0, -1);   // Start recursion with index 0 and no previous element chosen.
    }
};

/*
 * Dry Run:
 * Input: arr[] = [5, 8, 3, 7, 9, 1]
 *
 * 1. Call lis(arr):
 * - n is set to 6.
 * - Memoization table t is initialized with -1.
 * - Call solve(arr, 0, -1).
 *
 * 2. In solve(arr, 0, -1):
 * - i = 0, P = -1, so we can take arr[0] (5).
 * - "Take" branch: Compute 1 + solve(arr, 1, 0).
 * - "Skip" branch: Compute solve(arr, 1, -1).
 *
 * 3. In solve(arr, 1, 0) [after taking arr[0]=5]:
 * - i = 1, P = 0, and arr[1] (8) > arr[0] (5) so we can take arr[1].
 * - "Take" branch: Compute 1 + solve(arr, 2, 1).
 * - "Skip" branch: Compute solve(arr, 2, 0).
 * - Result is stored in t[1][0].
 *
 * 4. Similarly, solve(arr, 1, -1) is computed for the branch where arr[0] was skipped.
 * - Recursion continues, evaluating and memoizing states as needed.
 *
 * 5. Among the various recursive paths, one valid increasing subsequence is: [5 (i=0), 7 (i=3), 9 (i=4)] with length 3.
 *
 * Final Output: The length of the longest strictly increasing subsequence is 3.
 */

/************************************************************ JAVA ************************************************/

// Approach 1 (Recursion): Use recursion to explore two possibilities (include or skip) for each element to build the longest strictly increasing subsequence.
// Time Complexity: O(2^n) in the worst-case as each element leads to two recursive calls.
// Space Complexity: O(n) due to the recursion stack.
class Solution {
    private static int solve(int arr[], int i, int prevIndex) {
        if (i >= arr.length) {
            return 0;
        }

        int take = 0;
        if (prevIndex == -1 || arr[i] > arr[prevIndex]) {
            take = 1 + solve(arr, i + 1, i);
        }
        int skip = solve(arr, i + 1, prevIndex);
        return Math.max(take, skip);
    }

    static int lis(int arr[]) {
        return solve(arr, 0, -1);
    }
}
/*
 * Dry Run:
 * Input: arr[] = [5, 8, 3, 7, 9, 1]
 *
 * 1. Call lis(arr):
 * - Calls solve(arr, 0, -1)
 * 2. In solve(arr, 0, -1):
 * - i = 0, prevIndex = -1 → Can take element 5.
 * - "Take" branch: 1 + solve(arr, 1, 0)
 * - "Skip" branch: solve(arr, 1, -1)
 * 3. In solve(arr, 1, 0):
 * - i = 1, prevIndex = 0, arr[1] (8) > arr[0] (5) → Can take element 8.
 * - "Take" branch: 1 + solve(arr, 2, 1)
 * - "Skip" branch: solve(arr, 2, 0)
 * 4. The recursion continues exploring both branches.
 * 5. One valid path: [5, 7, 9] yielding length 3.
 *
 * Final Output: 3
 */

// Approach 2 (Recursion + Memoization): Use recursion with memoization to cache results for each (i, prevIndex) state, avoiding redundant calculations.
// Time Complexity: O(n^2) due to caching of each state (i, prevIndex).
// Space Complexity: O(n^2) for the memoization table plus O(n) for the recursion stack.
class Solution {
    private static int solve(int arr[], int i, int prevIndex, int[][] dp) {
        int n = arr.length;

        if (i >= n) {
            return 0;
        }

        // Map prevIndex to dp index: use (prevIndex + 1) to handle prevIndex == -1.
        if (dp[i][prevIndex + 1] != -1) {
            return dp[i][prevIndex + 1];
        }

        int take = 0;
        if (prevIndex == -1 || arr[i] > arr[prevIndex]) {
            take = 1 + solve(arr, i + 1, i, dp);
        }
        int skip = solve(arr, i + 1, prevIndex, dp);
        dp[i][prevIndex + 1] = Math.max(take, skip);
        return dp[i][prevIndex + 1];
    }
    static int lis(int arr[]) {
        int n = arr.length;
        // Create a memoization table with dimensions (n+1) x (n+1), mapping prevIndex -1 to index 0.
        int[][] dp = new int[n + 1][n + 1];

        for (int i = 0; i <= n; i++) {
            Arrays.fill(dp[i], -1);
        }
        return solve(arr, 0, -1, dp);
    }
}
/*
 * Dry Run:
 * Input: arr[] = [5, 8, 3, 7, 9, 1]
 *
 * 1. Call lis(arr):
 * - n = 6, dp is a 7x7 table initialized with -1.
 * - Calls solve(arr, 0, -1, dp).
 * 2. In solve(arr, 0, -1, dp):
 * - i = 0, prevIndex = -1 → Can take element 5.
 * - "Take" branch: 1 + solve(arr, 1, 0, dp)
 * - "Skip" branch: solve(arr, 1, -1, dp)
 * - Result is stored in dp[0][0] (since -1 + 1 = 0).
 * 3. In solve(arr, 1, 0, dp):
 * - i = 1, prevIndex = 0, arr[1] (8) > arr[0] (5) → Can take element 8.
 * - "Take" branch: 1 + solve(arr, 2, 1, dp)
 * - "Skip" branch: solve(arr, 2, 0, dp)
 * - Result is stored in dp[1][1] (since 0 + 1 = 1).
 * 4. The recursion continues, caching results in the dp table to avoid recomputation.
 * 5. One valid increasing subsequence: [5, 7, 9] with length 3 is found.
 *
 * Final Output: 3
 */
