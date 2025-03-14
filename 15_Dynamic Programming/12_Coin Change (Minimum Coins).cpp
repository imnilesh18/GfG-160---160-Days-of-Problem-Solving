/*
 * Coin Change (Minimum Coins)
 *
 * You are given an array coins[], where each element represents a coin of a different denomination, and a target value sum. You have an unlimited supply of each coin type {coins1, coins2, ..., coinsm}.
 *
 * Your task is to determine the minimum number of coins needed to obtain the target sum. If it is not possible to form the sum using the given coins, return -1.
 *
 * Examples:
 *
 * Input: coins[] = [25, 10, 5], sum = 30
 * Output: 2
 * Explanation: Minimum 2 coins needed, 25 and 5
 *
 * Input: coins[] = [9, 6, 5, 1], sum = 19
 * Output: 3
 * Explanation: 19 = 9 + 9 + 1
 *
 * Input: coins[] = [5, 1], sum = 0
 * Output: 0
 * Explanation: For 0 sum, we do not need a coin
 *
 * Input: coins[] = [4, 6, 2], sum = 5
 * Output: -1
 * Explanation: Not possible to make the given sum.
 *
 * Constraints:
 * 1 ≤ sum * coins.size() ≤ 10^6
 * 0 <= sum <= 10^4
 * 1 <= coins[i] <= 10^4
 * 1 <= coins.size() <= 10^3
 */

/************************************************************ C++ ************************************************/

// Approach (My Approach): Use recursion with memoization (top-down DP) to decide whether to take a coin (unlimited supply) or skip it.
// Time Complexity: O(n * sum) since each state (index, current sum) is computed once, where n is the number of coins.
// Space Complexity: O(n * sum) for the memoization table and recursion call stack.
class Solution {
public:
    int n;
    vector<vector<int> > t;

    int solve(int idx, vector<int>& coins, int sum, int curr) {
        if (curr == sum) {
            return 0;
        }
        if (curr > sum) {
            return INT_MAX;
        }
        if (idx >= coins.size()) {
            return INT_MAX;
        }

        // Use memoized result if available.
        if (t[idx][curr] != -1) {
            return t[idx][curr];
        }

        // Option 1: take the coin at index 'idx' (unlimited supply)
        int takeRes = solve(idx, coins, sum, curr + coins[idx]);
        int take    = (takeRes == INT_MAX) ? INT_MAX : 1 + takeRes;
        // Option 2: skip this coin and move to the next index.
        int skip = solve(idx + 1, coins, sum, curr);

        return t[idx][curr] = min(take, skip);
    }
    int minCoins(vector<int>& coins, int sum) {
        n = coins.size();
        // Allocate memoization table: dimensions = [n] x [sum+1]
        t.assign(n, vector<int>(sum + 1, -1));
        int result = solve(0, coins, sum, 0);
        return (result == INT_MAX) ? -1 : result;
    }
};

/*
 * Dry Run
 * Input: coins[] = [25, 10, 5], sum = 30
 * Steps:
 * 1. Start at idx = 0, curr = 0.
 * Option: take coin 25 -> new state (0, 25).
 * 2. At state (0, 25):
 * - Taking coin 25 again -> state (0, 50) exceeds sum -> returns INT_MAX.
 * - Skipping coin 25 -> move to idx = 1, state (1, 25).
 * 3. At state (1, 25):
 * - Taking coin 10 -> state (1, 35) exceeds sum -> returns INT_MAX.
 * - Skipping coin 10 -> move to idx = 2, state (2, 25).
 * 4. At state (2, 25):
 * - Taking coin 5 -> state (2, 30) equals sum -> returns 0.
 * - Skipping coin 5 -> move to idx = 3, state (3, 25) is invalid -> returns INT_MAX.
 * Minimum coins at (2,25) = 1 (by taking coin 5).
 * 5. Backtracking to state (0,25):
 * Minimum = min(1 + result from taking, result from skipping) = 2.
 * Final Output: 2 coins are needed.
 */

/************************************************************ JAVA ************************************************/

// Approach (My Approach): Use recursion with memoization (top-down DP) to decide whether to take a coin (unlimited supply) or skip it.
// Time Complexity: O(n * sum) since each state (index, current sum) is computed once, where n is the number of coins.
// Space Complexity: O(n * sum) for the memoization table and recursion call stack.
class Solution {
    // Define a large value to represent an impossible solution.
    private final int INF = Integer.MAX_VALUE - 1;

    // Recursive helper function.
    private int solve(int idx, int curr, int sum, int[] coins, int[][] dp) {
        // If current sum equals target sum, no more coins are needed.
        if (curr == sum) {
            return 0;
        }
        // If current sum exceeds target, return INF.
        if (curr > sum) {
            return INF;
        }
        // If index is out of bounds, return INF.
        if (idx >= coins.length) {
            return INF;
        }

        // Return memoized result if available.
        if (dp[idx][curr] != -1) {
            return dp[idx][curr];
        }

        // Option 1: Take the coin at index 'idx' (unlimited supply)
        int takeRes = solve(idx, curr + coins[idx], sum, coins, dp);
        int take    = (takeRes == INF) ? INF : 1 + takeRes;
        // Option 2: Skip the coin at index 'idx'
        int skip = solve(idx + 1, curr, sum, coins, dp);

        dp[idx][curr] = Math.min(take, skip);
        return dp[idx][curr];
    }
    public int minCoins(int coins[], int sum) {
        int n = coins.length;

        // For 0 sum, no coins are needed.
        if (sum == 0) {
            return 0;
        }

        // Initialize memoization table: dimensions [n][sum + 1] with -1.
        int[][] dp = new int[n][sum + 1];
        for (int i = 0; i < n; i++) {
            Arrays.fill(dp[i], -1);
        }

        int result = solve(0, 0, sum, coins, dp);
        return (result >= INF) ? -1 : result;
    }
}

/*
 * Dry Run
 * Input: coins[] = [25, 10, 5], sum = 30
 * Steps:
 * 1. Call minCoins with coins and sum; initialize dp.
 * 2. At solve(0, 0, 30): choose to take coin 25 -> state becomes (0, 25).
 * 3. At solve(0, 25, 30): taking coin 25 leads to (0, 50) which exceeds sum, so try skipping.
 * 4. Skip coin 25, move to solve(1, 25, 30): try taking coin 10, which results in (1, 35) exceeding sum.
 * 5. At solve(1, 25, 30): skip coin 10, move to solve(2, 25, 30) and take coin 5 -> state becomes (2, 30), equals sum.
 * 6. Total coins used = 2 (25 and 5).
 * Final Output: 2 coins are needed.
 */
