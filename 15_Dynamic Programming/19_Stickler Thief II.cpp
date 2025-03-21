/*
 * Stickler Thief II
 *
 * You are given an array arr[] which represents houses arranged in a circle, where each house has a certain value. A thief aims to maximize the total stolen value without robbing two adjacent houses.
 * Determine the maximum amount the thief can steal.
 *
 * Note: Since the houses are in a circle, the first and last houses are also considered adjacent.
 *
 * Examples:
 *
 * Input: arr[] = [2, 3, 2]
 * Output: 3
 * Explanation: arr[0] and arr[2] can't be robbed because they are adjacent houses. Thus, 3 is the maximum value thief can rob.
 *
 * Input: arr[] = [1, 2, 3, 1]
 * Output: 4
 * Explanation: Maximum stolen value: arr[0] + arr[2] = 1 + 3 = 4
 *
 * Input: arr[] = [2, 2, 3, 1, 2]
 * Output: 5
 * Explanation: Maximum stolen value: arr[0] + arr[2] = 2 + 3 = 5 or arr[2] + arr[4] = 3 + 2 = 5
 *
 * Constraints:
 * 2 ≤ arr.size() ≤ 10^5
 * 0 ≤ arr[i] ≤ 10^4
 */

/************************************************************ C++ ************************************************/

// Approach: Use recursion with memoization on two subproblems: (1) Houses from index 0 to n-2 and (2) Houses from index 1 to n-1. Then return the maximum.
// Time Complexity: O(n) per subproblem, overall O(n) since each subproblem covers roughly n houses.
// Space Complexity: O(n) for each memoization array (and recursion stack), which is acceptable given the constraints.
class Solution {
public:
    // Helper function to calculate maximum loot in a linear segment (from index idx to end).
    int solve(vector<int>& arr, int idx, int end, vector<int>& t) {
        if (idx > end) {
            return 0;
        }
        if (t[idx] != -1) {        // if already computed, return the stored result
            return t[idx];
        }
        int take = arr[idx] + solve(arr, idx + 2, end, t);     // option: take current house and skip the next
        int skip = solve(arr, idx + 1, end, t);                // option: skip current house and check the next
        return t[idx] = max(take, skip);                       // memoize and return the maximum loot from index idx
    }
    
    int maxValue(vector<int>& arr) {
        int n = arr.size();

        // Edge case: Only one house exists.
        if (n == 1) {
            return arr[0];
        }
        // Create separate memoization arrays for the two cases.
        vector<int> t1(n, -1), t2(n, -1);
        // Case 1: Exclude the last house (consider indices 0 to n-2)
        int case1 = solve(arr, 0, n - 2, t1);
        // Case 2: Exclude the first house (consider indices 1 to n-1)
        int case2 = solve(arr, 1, n - 1, t2);
        return max(case1, case2);
    }
};

/*
 * Dry Run
 * Input: arr[] = [2, 3, 2]
 * Case 1: Solve for indices [0, 1]
 *  - solve(arr, 0, 1, t1):
 *       idx = 0 -> take = 2 + solve(arr, 2, 1, t1) = 2 + 0 = 2; skip = solve(arr, 1, t1)
 *       idx = 1 -> take = 3 + solve(arr, 3, t1) = 3 + 0 = 3; skip = solve(arr, 2, t1) = 0
 *       => solve(arr, 1, t1) returns max(3, 0) = 3
 *       => solve(arr, 0, t1) returns max(2, 3) = 3
 *  - Case 1 Result = 3
 * Case 2: Solve for indices [1, 2]
 *  - solve(arr, 1, 2, t2):
 *       idx = 1 -> take = 3 + solve(arr, 3, t2) = 3 + 0 = 3; skip = solve(arr, 2, t2)
 *       idx = 2 -> take = 2 + solve(arr, 4, t2) = 2 + 0 = 2; skip = solve(arr, 3, t2) = 0
 *       => solve(arr, 2, t2) returns max(2, 0) = 2
 *       => solve(arr, 1, t2) returns max(3, 2) = 3
 *  - Case 2 Result = 3
 * Final Answer: max(3, 3) = 3
 */

/************************************************************ JAVA ************************************************/

// Approach: Use recursion with memoization on two subproblems: (1) Houses from index 0 to n-2 and (2) Houses from index 1 to n-1. Then return the maximum.
// Time Complexity: O(n) per subproblem, overall O(n) since each subproblem covers roughly n houses.
// Space Complexity: O(n) for each memoization array (and recursion stack), which is acceptable given the constraints.
class Solution {
    // Helper function to calculate maximum loot in a linear segment (from index idx to end).
    int solve(int[] arr, int idx, int end, int[] t) {
        if (idx > end) {
            return 0;
        }
        if (t[idx] != -1) {    // if already computed, return the stored result
            return t[idx];
        }
        int take = arr[idx] + solve(arr, idx + 2, end, t); // option: take current house and skip the next
        int skip = solve(arr, idx + 1, end, t);            // option: skip current house and check the next
        return t[idx] = Math.max(take, skip);              // memoize and return the maximum loot from index idx
    }

    int maxValue(int[] arr) {
        int n = arr.length;

        // Edge case: Only one house exists.
        if (n == 1) {
            return arr[0];
        }
        // Create separate memoization arrays for the two cases.
        int[] t1 = new int[n];
        int[] t2 = new int[n];
        Arrays.fill(t1, -1);
        Arrays.fill(t2, -1);
        // Case 1: Exclude the last house (consider indices 0 to n-2)
        int case1 = solve(arr, 0, n - 2, t1);
        // Case 2: Exclude the first house (consider indices 1 to n-1)
        int case2 = solve(arr, 1, n - 1, t2);
        return Math.max(case1, case2);
    }
}

/*
 * Dry Run
 * Input: arr[] = [1, 2, 3, 1]
 * Case 1: Solve for indices [0, 2]
 *  - solve(arr, 0, 2, t1):
 *       idx = 0 -> take = 1 + solve(arr, 2, t1) = 1 + ?; skip = solve(arr, 1, t1)
 *       idx = 2 -> take = 3 + solve(arr, 4, t1) = 3 + 0 = 3; skip = solve(arr, 3, t1) = 0
 *       => solve(arr, 2, t1) returns max(3, 0) = 3
 *       => For idx = 0: take = 1 + 3 = 4; now compute solve(arr, 1, t1)
 *       idx = 1 -> take = 2 + solve(arr, 3, t1) = 2 + 0 = 2; skip = solve(arr, 2, t1) = 3
 *       => solve(arr, 1, t1) returns max(2, 3) = 3
 *       => solve(arr, 0, t1) returns max(4, 3) = 4
 *  - Case 1 Result = 4
 * Case 2: Solve for indices [1, 3]
 *  - solve(arr, 1, 3, t2):
 *       idx = 1 -> take = 2 + solve(arr, 3, t2) = 2 + 0 = 2; skip = solve(arr, 2, t2)
 *       idx = 2 -> take = 3 + solve(arr, 4, t2) = 3 + 0 = 3; skip = solve(arr, 3, t2) = 0
 *       => solve(arr, 2, t2) returns max(3, 0) = 3
 *       => solve(arr, 1, t2) returns max(2, 3) = 3
 *  - Case 2 Result = 3
 * Final Answer: Math.max(4, 3) = 4
 */
