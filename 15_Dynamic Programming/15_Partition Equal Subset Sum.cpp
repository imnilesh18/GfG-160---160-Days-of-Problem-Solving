/*
 * Partition Equal Subset Sum
 * (Solve Subset Sum Problem first)
 *
 * Given an array arr[], determine if it can be partitioned into two subsets such that the sum of elements in both parts is the same.
 *
 * Note: Each element must be in exactly one subset.
 *
 * Examples:
 *
 * Input: arr = [1, 5, 11, 5]
 * Output: true
 * Explanation: The two parts are [1, 5, 5] and [11].
 *
 * Input: arr = [1, 3, 5]
 * Output: false
 * Explanation: This array can never be partitioned into two such parts.
 *
 * Constraints:
 * 1 ≤ arr.size ≤ 100
 * 1 ≤ arr[i] ≤ 200
 */

/*
 * Intuition:
 * 1. Calculate the Total Sum:
 * First, sum all the numbers in the array. This total represents the sum of both subsets combined.
 *
 * 2. Check if the Total is Even:
 * - If the total sum is odd, it's impossible to split it into two equal parts because two equal parts must sum to an even number. Hence, if the total is odd, the answer is immediately "not possible".
 * - If the total is even, then each subset must sum to exactly half of this total, i.e., totalSum/2.
 *
 * 3. Reduce the Problem:
 * Once you know the total is even, the problem simplifies to finding a subset of numbers that adds up to totalSum/2. This is because if one subset sums to totalSum/2, the remaining elements automatically sum to the other half (since totalSum = totalSum/2 + totalSum/2).
 *
 * 4. Subset Sum Problem:
 * The challenge now becomes a subset sum problem: Is there a combination of numbers in the array that equals totalSum/2? This can be solved using techniques like recursion with memoization or dynamic programming.
 */

/************************************************************ C++ ************************************************/

// Approach (My Approach): Calculate the total sum of the array. If it's odd, equal partitioning is impossible.
// If it's even, then each subset must sum to totalSum/2. Use recursion with memoization to determine
// if a subset exists with sum equal to totalSum/2.
// Time Complexity: O(n * target) where target = totalSum/2 (each state is computed once).
// Space Complexity: O(n * target) for the memoization table.
class Solution {
public:
    int t[201][10001]; // Memoization table to store results for each (index, currentSum)

    // Recursive function to determine if a subset with sum equal to 'sum' can be found.
    bool solve(vector<int>& arr, int sum, int currentSum, int idx) {
        // If current subset sum equals the target, partitioning is successful.
        if (currentSum == sum) {
            return true;
        }
        // If current sum exceeds the target or we've reached the end of the array, return false.
        if (currentSum > sum || idx >= arr.size()) {
            return false;
        }
        // Return previously computed result if available.
        if (t[idx][currentSum] != -1) {
            return t[idx][currentSum];
        }
        // Try including the current element in the subset.
        bool take = solve(arr, sum, currentSum + arr[idx], idx + 1);
        // Try excluding the current element from the subset.
        bool skip = solve(arr, sum, currentSum, idx + 1);

        // Store the result in memoization table and return it.
        return t[idx][currentSum] = (take || skip);
    }
    // Main function to check if the array can be partitioned into two subsets with equal sum.
    bool equalPartition(vector<int>& arr) {
        int n        = arr.size();
        int totalSum = 0;

        // Calculate total sum of the array.
        for (int i = 0; i < n; i++) {
            totalSum += arr[i];
        }
        // If total sum is odd, partitioning is impossible.
        if (totalSum % 2 != 0) {
            return false;
        }
        // Initialize memoization table with -1 to indicate uncomputed states.
        memset(t, -1, sizeof(t));
        // Check for a subset with sum equal to totalSum/2.
        return solve(arr, totalSum / 2, 0, 0);
    }
};

/*
 * Dry Run:
 * Input: arr = [1, 5, 11, 5]
 * totalSum = 22, target = 11
 * Initial call: solve(arr, 11, 0, 0)
 *  At idx = 0, currentSum = 0 -> try including 1:
 *      Call: solve(arr, 11, 1, 1)
 *          At idx = 1, currentSum = 1 -> try including 5:
 *              Call: solve(arr, 11, 6, 2)
 *                  At idx = 2, currentSum = 6 -> try including 11:
 *                      currentSum becomes 17 (exceeds target) -> returns false.
 *                  At idx = 2, currentSum = 6 -> try excluding 11:
 *                      Call: solve(arr, 11, 6, 3)
 *                          At idx = 3, currentSum = 6 -> try including 5:
 *                              Call: solve(arr, 11, 11, 4)
 *                                  currentSum equals target -> returns true.
 * Since one branch returns true, the final answer is true.
 */

/************************************************************ JAVA ************************************************/

// Approach (My Approach): Calculate the total sum of the array. If it's odd, equal partitioning is impossible.
// If it's even, then each subset must sum to totalSum/2. Use recursion with memoization to determine
// if a subset exists with sum equal to totalSum/2.
// Time Complexity: O(n * target) where target = totalSum/2 (each state is computed once).
// Space Complexity: O(n * target) for the memoization table.
class Solution {
    static int[][] t; // Memoization table to store results for each (index, currentSum)

    // Recursive function to determine if a subset with sum equal to 'sum' can be found.
    static boolean solve(int[] arr, int sum, int currentSum, int idx) {
        // If current subset sum equals the target, partitioning is successful.
        if (currentSum == sum) {
            return true;
        }
        // If current sum exceeds the target or we've reached the end of the array, return false.
        if (currentSum > sum || idx >= arr.length) {
            return false;
        }
        // Return previously computed result if available.
        if (t[idx][currentSum] != -1) {
            return t[idx][currentSum] == 1;
        }
        // Try including the current element in the subset.
        boolean take = solve(arr, sum, currentSum + arr[idx], idx + 1);
        // Try excluding the current element from the subset.
        boolean skip = solve(arr, sum, currentSum, idx + 1);

        // Store the result in memoization table: 1 for true, 0 for false.
        t[idx][currentSum] = (take || skip) ? 1 : 0;
        return take || skip;
    }
    // Main function to check if the array can be partitioned into two subsets with equal sum.
    static boolean equalPartition(int arr[]) {
        int totalSum = 0;

        // Calculate total sum of the array.
        for (int num : arr) {
            totalSum += num;
        }
        // If total sum is odd, partitioning is impossible.
        if (totalSum % 2 != 0) {
            return false;
        }
        int target = totalSum / 2;
        // Initialize memoization table with -1 to indicate uncomputed states.
        t = new int[arr.length][target + 1];
        for (int i = 0; i < arr.length; i++) {
            Arrays.fill(t[i], -1);
        }
        // Check for a subset with sum equal to totalSum/2.
        return solve(arr, target, 0, 0);
    }
}

/*
 * Dry Run:
 * Input: arr = [1, 5, 11, 5]
 * totalSum = 22, target = 11
 * Initial call: solve(arr, 11, 0, 0)
 *  At idx = 0, currentSum = 0 -> try including 1:
 *      Call: solve(arr, 11, 1, 1)
 *          At idx = 1, currentSum = 1 -> try including 5:
 *              Call: solve(arr, 11, 6, 2)
 *                  At idx = 2, currentSum = 6 -> try including 11:
 *                      currentSum becomes 17 (exceeds target) -> returns false.
 *                  At idx = 2, currentSum = 6 -> try excluding 11:
 *                      Call: solve(arr, 11, 6, 3)
 *                          At idx = 3, currentSum = 6 -> try including 5:
 *                              Call: solve(arr, 11, 11, 4)
 *                                  currentSum equals target -> returns true.
 * Since one branch returns true, equalPartition returns true.
 */
