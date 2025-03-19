/*
 * Stock Buy and Sell – Max 2 Transactions Allowed
 *
 * In daily share trading, a trader buys shares and sells them on the same day. If the trader is allowed to make at most 2 transactions in a day, find out the maximum profit that a share trader could have made.
 *
 * You are given an array prices[] representing stock prices throughout the day. Note that the second transaction can only start after the first one is complete (buy->sell->buy->sell).
 *
 * Examples:
 *
 * Input: prices[] = [10, 22, 5, 75, 65, 80]
 * Output: 87
 * Explanation:
 * Trader will buy at 10 and sells at 22.
 * Profit earned in 1st transaction = 22 - 10 = 12.
 * Then he buys at 5 and sell at 80.
 * Profit earned in 2nd transaction = 80 - 5 = 75.
 * Total profit earned = 12 + 75 = 87.
 *
 * Input: prices[] = [2, 30, 15, 10, 8, 25, 80]
 * Output: 100
 * Explanation:
 * Trader will buy at 2 and sells at 30.
 * Profit earned in 1st transaction = 30 - 2 = 28.
 * Then he buys at 8 and sell at 80.
 * Profit earned in 2nd transaction = 80 - 8 = 72.
 * Total profit earned = 28 + 72 = 100.
 *
 * Constraints:
 * 1 <= prices.size() <= 10^5
 * 1 <= prices[i] <= 10^5
 */

/************************************************************ C++ ************************************************/

// Approach: Recursive DP with memoization; at each day, decide to buy, sell or skip, caching results in a DP table.
// Time Complexity: O(n * 2*k) where n is the number of days and k=2, so effectively O(n).
// Space Complexity: O(n * 2*k) for the DP table plus O(n) recursion stack.
class Solution {
public:
    // Recursive helper function
    int solve(vector<int>& prices, int k, int idx, int transNo, int n, vector<vector<int> >& t) {
        if (idx == n || transNo == 2 * k) {    // Base case: no more days or reached maximum transactions
            return 0;
        }
        if (t[idx][transNo] != -1) {    // Return cached result if already computed
            return t[idx][transNo];
        }
        if (transNo % 2 == 0) {                                                                // Buy phase
            t[idx][transNo] = max(-prices[idx] + solve(prices, k, idx + 1, transNo + 1, n, t), // Option to buy at current day
                                             0 + solve(prices, k, idx + 1, transNo, n, t));    // Option to skip buying
        } else {                                                                               // Sell phase
            t[idx][transNo] = max(prices[idx] + solve(prices, k, idx + 1, transNo + 1, n, t),  // Option to sell at current day
                                            0 + solve(prices, k, idx + 1, transNo, n, t));     // Option to skip selling
        }
        return t[idx][transNo];
    }

    int maxProfit(vector<int>& prices) {
        int k = 2;                                         // Maximum allowed transactions (2 transactions: 2 buys and 2 sells)
        int n = prices.size();
        vector<vector<int> > t(n, vector<int>(2 * k, -1)); // DP table for memoization

        return solve(prices, k, 0, 0, n, t);
    }
};

/*
 * Dry Run
 * For prices[] = [10, 22, 5, 80] and k = 2:
 * 1. Start at idx = 0, transNo = 0 (Buy phase):
 * - Option 1: Buy at 10 -> profit = -10 + solve(idx=1, transNo=1)
 * - Option 2: Skip buying -> profit = solve(idx=1, transNo=0)
 * 2. At idx = 1:
 * - If Option 1 was taken, now in Sell phase (transNo=1):
 *     - Option: Sell at 22 -> profit = 22 + solve(idx=2, transNo=2)
 * - If Option 2 was taken, still in Buy phase:
 *     - Continue with similar decisions...
 * 3. Continue until all days are processed or 4 transactions (2 buys + 2 sells) are completed.
 * Final maximum profit computed = 87 (buy at 10 and sell at 22 yields profit 12; buy at 5 and sell at 80 yields profit 75; total = 12+75=87).
 */

/************************************************************ JAVA ************************************************/

// Approach: Recursive DP with memoization; at each day, decide to buy, sell or skip, caching results in a DP table.
// Time Complexity: O(n * 2*k) where n is the number of days and k=2, so effectively O(n).
// Space Complexity: O(n * 2*k) for the DP table plus O(n) recursion stack.
class Solution {
    // Recursive helper function
    private static int solve(int[] prices, int k, int idx, int transNo, int n, int[][] t) {
        if (idx == n || transNo == 2 * k) { // Base case: no more days or reached maximum transactions
            return 0;
        }
        if (t[idx][transNo] != -1) { // Return cached result if already computed
            return t[idx][transNo];
        }
        if (transNo % 2 == 0) {                                                                     // Buy phase
            t[idx][transNo] = Math.max(-prices[idx] + solve(prices, k, idx + 1, transNo + 1, n, t), // Option to buy at current day
                                                  0 + solve(prices, k, idx + 1, transNo, n, t));    // Option to skip buying
        } else {                                                                                    // Sell phase
            t[idx][transNo] = Math.max(prices[idx] + solve(prices, k, idx + 1, transNo + 1, n, t),  // Option to sell at current day
                                                 0 + solve(prices, k, idx + 1, transNo, n, t));     // Option to skip selling
        }
        return t[idx][transNo];
    }
    
    public static int maxProfit(int[] prices) {
        int k = 2;                     // Maximum allowed transactions (2 transactions: 2 buys and 2 sells)
        int n = prices.length;
        int[][] t = new int[n][2 * k]; // DP table for memoization

        // Initialize DP table with -1
        for (int i = 0; i < n; i++) {
            Arrays.fill(t[i], -1);
        }
        return solve(prices, k, 0, 0, n, t);
    }
}

/*
 * Dry Run
 * For prices[] = [10, 22, 5, 80] and k = 2:
 * 1. Start at idx = 0, transNo = 0 (Buy phase):
 * - Option 1: Buy at 10 -> profit = -10 + solve(idx=1, transNo=1)
 * - Option 2: Skip buying -> profit = solve(idx=1, transNo=0)
 * 2. At idx = 1:
 * - If Option 1 was taken, now in Sell phase (transNo=1):
 *     - Option: Sell at 22 -> profit = 22 + solve(idx=2, transNo=2)
 * - If Option 2 was taken, still in Buy phase:
 *     - Continue with similar decisions...
 * 3. Continue until all days are processed or 4 transactions (2 buys + 2 sells) are completed.
 * Final maximum profit computed = 87 (buy at 10 and sell at 22 yields profit 12; buy at 5 and sell at 80 yields profit 75; total = 12+75=87).
 */
