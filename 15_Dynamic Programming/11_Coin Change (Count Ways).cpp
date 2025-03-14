/*
 * Coin Change (Count Ways)
 *
 * Given an integer array coins[ ] representing different denominations of currency and an integer sum, find the number of ways you can make sum by using different combinations from coins[ ].
 * Note: Assume that you have an infinite supply of each type of coin. Therefore, you can use any coin as many times as you want.
 * Answers are guaranteed to fit into a 32-bit integer.
 *
 * Examples:
 *
 * Input: coins[] = [1, 2, 3], sum = 4
 * Output: 4
 * Explanation: Four Possible ways are: [1, 1, 1, 1], [1, 1, 2], [2, 2], [1, 3].
 *
 * Input: coins[] = [2, 5, 3, 6], sum = 10
 * Output: 5
 * Explanation: Five Possible ways are: [2, 2, 2, 2, 2], [2, 2, 3, 3], [2, 2, 6], [2, 3, 5] and [5, 5].
 *
 * Input: coins[] = [5, 10], sum = 3
 * Output: 0
 * Explanation: Since all coin denominations are greater than sum, no combination can make the target sum.
 *
 * Constraints:
 * 1 <= sum <= 10^3
 * 1 <= coins[i] <= 10^4
 * 1 <= coins.size() <= 10^3
 */

/************************************************************ C++ ************************************************/

// Approach 1 (Test Cases Passed: 1010 /1111 Time limit exceeded.): Recursively try including the current coin (unlimited supply) or skipping it until the target sum is reached.
// Time Complexity: Exponential in worst-case due to exploring all combinations without memoization.
// Space Complexity: O(sum) due to recursion call stack in the worst-case.
class Solution {
public:
    int n;

    int solve(int i, vector<int>& coins, int sum) {
        // If the remaining sum is 0, one valid way is found.
        if (sum == 0) {
            return 1;
        }
        // If no more coins to consider, no valid combination exists.
        if (i == n) {
            return 0;
        }
        // If the current coin is greater than the remaining sum, skip it.
        if (coins[i] > sum) {
            return solve(i + 1, coins, sum);
        }
        // Option 1: Take the coin (stay at the same index due to infinite supply).
        int take = solve(i, coins, sum - coins[i]);
        // Option 2: Skip the coin (move to the next index).
        int skip = solve(i + 1, coins, sum);

        return take + skip;
    }
    int count(vector<int>& coins, int sum) {
        n = coins.size();
        return solve(0, coins, sum);
    }
};

/*
 * Dry Run:
 * Example: coins[] = [1, 2, 3], sum = 4
 * - Call solve(0, [1,2,3], 4)
 *  - Include coin 1: solve(0, [1,2,3], 3)
 *       - Include coin 1: solve(0, [1,2,3], 2)
 *            - Include coin 1: solve(0, [1,2,3], 1)
 *                  - Include coin 1: solve(0, [1,2,3], 0) -> returns 1 (valid combination: [1,1,1,1])
 *                  - Exclude coin 1: solve(1, [1,2,3], 1) -> returns 0 (no valid combination)
 *            - Exclude coin 1: solve(1, [1,2,3], 2)
 *                  - Include coin 2: solve(1, [1,2,3], 0) -> returns 1 (valid combination: [1,1,2])
 *       - Exclude coin 1: solve(1, [1,2,3], 3)
 *            - Skip coin 2 or include coin 3 eventually yielding:
 *                  - Include coin 3: solve(2, [1,2,3], 0) -> returns 1 (valid combination: [1,3])
 * - Total ways = 4 (also includes [2,2])
 */

// Approach 2: Use recursion with memoization to count the number of ways to form the target sum by either including the current coin (unlimited supply) or skipping it.
// Time Complexity: O(n * sum) since each state (index, remaining sum) is computed only once.
// Space Complexity: O(n * sum) for the memoization table and recursion stack.
// Note: t[1001][1001] is initialized based on the constraints (sum and number of coins up to 1000) to ensure sufficient space for all possible states.
class Solution {
public:
    int n;
    int t[1001][1001];   // Memoization table with dimensions based on problem constraints

    int solve(int i, vector<int>& coins, int sum) {
        // If the remaining sum is 0, a valid combination is found.
        if (sum == 0) {
            return 1;
        }

        // If no coins are left to consider, return 0 as no valid combination can be formed.
        if (i == n) {
            return 0;
        }

        // Return the stored result if this state has already been computed.
        if (t[i][sum] != -1) {
            return t[i][sum];
        }

        // If the current coin's value is greater than the remaining sum, skip this coin.
        if (coins[i] > sum) {
            return t[i][sum] = solve(i + 1, coins, sum);
        }

        // Option 1: Include the current coin (stay at the same index since coins can be reused).
        int take = solve(i, coins, sum - coins[i]);
        // Option 2: Exclude the current coin and move to the next index.
        int skip = solve(i + 1, coins, sum);

        return t[i][sum] = take + skip;
    }
    int count(vector<int>& coins, int sum) {
        n = coins.size();
        memset(t, -1, sizeof(t));   // Initialize the memoization table with -1
        return solve(0, coins, sum);
    }
};

/*
 * Dry Run:
 * Example: coins[] = [1, 2, 3], sum = 4
 * 1. Call solve(0, [1,2,3], 4)
 * - Current coin = 1 (since 1 <= 4):
 *   a) Take coin 1: solve(0, [1,2,3], 3)
 *       i) Take coin 1: solve(0, [1,2,3], 2)
 *           - Take coin 1: solve(0, [1,2,3], 1)
 * Take coin 1: solve(0, [1,2,3], 0) returns 1 (combination: [1,1,1,1])
 * Skip coin 1: solve(1, [1,2,3], 1) returns 0 (no valid combination)
 *           - Skip coin 1: solve(1, [1,2,3], 2)
 * Take coin 2: solve(1, [1,2,3], 0) returns 1 (combination: [1,1,2])
 *       ii) Skip coin 1: solve(1, [1,2,3], 3)
 *           - Eventually, taking coin 3 yields: solve(2, [1,2,3], 0) returns 1 (combination: [1,3])
 *   b) Skip coin 1: solve(1, [1,2,3], 4)
 *       - Eventually, including coin 2 twice gives the combination: [2,2] returning 1
 * Total ways = 1 (from [1,1,1,1]) + 1 (from [1,1,2]) + 1 (from [1,3]) + 1 (from [2,2]) = 4
 */

/************************************************************ JAVA ************************************************/

// Approach 1 (Test Cases Passed: 1010 /1111 Time limit exceeded.): Use recursion to either include the current coin (with infinite supply) or skip it, accumulating valid combinations that sum to the target.
// Time Complexity: Exponential due to recursive exploration of all coin combinations without memoization.
// Space Complexity: O(sum) because of the recursion stack in worst-case scenarios.
class Solution {
    private int solve(int[] coins, int sum, int index) {
        // If the remaining sum is 0, a valid combination is found.
        if (sum == 0) {
            return 1;
        }
        // If all coins have been considered, return 0 as no valid combination is possible.
        if (index == coins.length) {
            return 0;
        }
        // If the current coin exceeds the remaining sum, skip it.
        if (coins[index] > sum) {
            return solve(coins, sum, index + 1);
        }
        // Option 1: Include the current coin and remain at the same index.
        int take = solve(coins, sum - coins[index], index);
        // Option 2: Exclude the current coin and move to the next.
        int skip = solve(coins, sum, index + 1);

        return take + skip;
    }
    public int count(int coins[], int sum) {
        return solve(coins, sum, 0);
    }
}

/*
 * Dry Run:
 * Example: coins[] = [1, 2, 3], sum = 4
 * - Call solve([1,2,3], 4, 0)
 *  - Include coin 1: solve([1,2,3], 3, 0)
 *       - Include coin 1: solve([1,2,3], 2, 0)
 *            - Include coin 1: solve([1,2,3], 1, 0)
 *                  - Include coin 1: solve([1,2,3], 0, 0) -> returns 1 (valid combination: [1,1,1,1])
 *                  - Exclude coin 1: solve([1,2,3], 1, 1) -> returns 0 (no valid combination)
 *            - Exclude coin 1: solve([1,2,3], 2, 1)
 *                  - Include coin 2: solve([1,2,3], 0, 1) -> returns 1 (valid combination: [1,1,2])
 *       - Exclude coin 1: solve([1,2,3], 3, 1)
 *            - Eventually, including coin 3 gives:
 *                  - Include coin 3: solve([1,2,3], 0, 2) -> returns 1 (valid combination: [1,3])
 * - Total ways = 4 (including the combination [2,2] found during different recursive paths)
 */

// Approach 2: Use recursion with memoization to determine the number of ways to form the target sum by either including the current coin (with unlimited supply) or skipping it.
// Time Complexity: O(n * sum) as each (index, remaining sum) state is computed only once due to memoization.
// Space Complexity: O(n * sum) for the memoization table and recursion stack.
// Note: The memo table is initialized with dimensions [coins.length+1][sum+1] based on the problem constraints (up to 1000 coins and sum up to 1000).
class Solution {
    int[][] memo; // Memoization table

    private int solve(int[] coins, int sum, int index) {
        // Base case: If the remaining sum is 0, one valid combination is found.
        if (sum == 0) {
            return 1;
        }
        // Base case: If all coins have been considered, return 0 as no valid combination exists.
        if (index == coins.length) {
            return 0;
        }
        // Return the computed result if available.
        if (memo[index][sum] != -1) {
            return memo[index][sum];
        }
        // If the current coin's value is greater than the remaining sum, skip this coin.
        if (coins[index] > sum) {
            memo[index][sum] = solve(coins, sum, index + 1);
            return memo[index][sum];
        }
        // Option 1: Include the current coin (remain at the same index for unlimited supply).
        int take = solve(coins, sum - coins[index], index);
        // Option 2: Exclude the current coin and move to the next index.
        int skip = solve(coins, sum, index + 1);

        memo[index][sum] = take + skip;
        return memo[index][sum];
    }
    public int count(int coins[], int sum) {
        // Initialize memoization table with -1 to indicate uncomputed states.
        memo = new int[coins.length + 1][sum + 1];
        for (int i = 0; i <= coins.length; i++) {
            Arrays.fill(memo[i], -1);
        }
        return solve(coins, sum, 0);
    }
}

/*
 * Dry Run:
 * Example: coins[] = [1, 2, 3], sum = 4
 * 1. Call solve(coins, 4, 0) with coin at index 0 = 1:
 * - Option take: solve(coins, 3, 0)
 *     i) Take coin 1: solve(coins, 2, 0)
 *         - Take coin 1: solve(coins, 1, 0)
 * Take coin 1: solve(coins, 0, 0) returns 1 (combination: [1,1,1,1])
 * Skip coin 1: solve(coins, 1, 1) returns 0 (no valid combination)
 *         - Skip coin 1: solve(coins, 2, 1)
 * Take coin 2: solve(coins, 0, 1) returns 1 (combination: [1,1,2])
 *     ii) Skip coin 1: solve(coins, 3, 1)
 *         - Eventually, taking coin 3 gives: solve(coins, 0, 2) returns 1 (combination: [1,3])
 * - Option skip: solve(coins, 4, 1)
 *     - Eventually, including coin 2 twice leads to: combination [2,2] returning 1
 * Total ways = 1 (from [1,1,1,1]) + 1 (from [1,1,2]) + 1 (from [1,3]) + 1 (from [2,2]) = 4
 */
