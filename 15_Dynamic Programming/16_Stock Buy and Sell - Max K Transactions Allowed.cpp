/*
 * Stock Buy and Sell - Max K Transactions Allowed
 *
 * In the stock market, a person buys a stock and sells it on some future date. You are given an array prices[] representing stock prices on different days and a positive integer k, find out the maximum profit a person can make in at-most k transactions.
 *
 * A transaction consists of buying and subsequently selling a stock and new transaction can start only when the previous transaction has been completed.
 *
 * Examples :
 *
 * Input: prices[] = [10, 22, 5, 80], k = 2
 * Output: 87
 * Explaination:
 * 1st transaction: Buy at 10 and sell at 22.
 * 2nd transaction : Buy at 5 and sell at 80.
 * Total Profit will be 12 + 75 = 87.
 *
 * Input: prices[] = [20, 580, 420, 900], k = 3
 * Output: 1040
 * Explaination:
 * 1st transaction: Buy at 20 and sell at 580.
 * 2nd transaction : Buy at 420 and sell at 900.
 * Total Profit will be 560 + 480 = 1040.
 *
 * Input: prices[] = [100, 90, 80, 50, 25],  k = 1
 * Output: 0
 * Explaination: Selling price is decreasing continuously
 * leading to loss. So seller cannot have any profit.
 *
 * Constraints:
 * 1 ≤ prices.size() ≤ 10^3
 * 1 ≤ k ≤ 200
 * 1 ≤ prices[i] ≤ 10^3
 */

/************************************************************ C++ ************************************************/

// Approach: Recursive solution with memoization. At each day, decide whether to perform a buy/sell action or skip, using DP to cache results.
// Time Complexity: O(n * 2*k) which simplifies to O(n*k) since there are 2*k transaction states and each is computed once.
// Space Complexity: O(n * 2*k) for the memoization table plus O(n) for the recursion stack.
class Solution {
public:
    int solve(vector<int>& prices, int k, int idx, int transNo, int n, vector<vector<int> >& t) {
        if (idx == n || transNo == 2 * k) {  // Base case: no more days or reached maximum transactions
            return 0;
        }

        if (t[idx][transNo] != -1) {  // Return cached result if already computed
            return t[idx][transNo];
        }

        if (transNo % 2 == 0) {                                                                // Buy phase
            t[idx][transNo] = max(-prices[idx] + solve(prices, k, idx + 1, transNo + 1, n, t), // Option to buy at current day
                                             0 + solve(prices, k, idx + 1, transNo, n, t));    // Option to skip buying
            return t[idx][transNo];
        }

        // Sell phase
        t[idx][transNo] = max(prices[idx] + solve(prices, k, idx + 1, transNo + 1, n, t),    // Option to sell at current day
                                        0 + solve(prices, k, idx + 1, transNo, n, t));       // Option to skip selling
        return t[idx][transNo];
    }
    
    int maxProfit(vector<int>& prices, int k) {
        int n = prices.size();
        vector<vector<int> > t(n, vector<int>(2 * k, -1));  // DP table of dimensions [n][2*k]

        return solve(prices, k, 0, 0, n, t);
    }
};

/*
 * Dry Run:
 * For prices[] = [10, 22, 5, 80] and k = 2:
 * - Start at idx = 0, transNo = 0 (Buy phase):
 *  Option 1: Buy at 10 -> profit = -10 + solve(idx=1, transNo=1)
 *  Option 2: Skip buying -> profit = solve(idx=1, transNo=0)
 * - At idx = 1:
 *  If Option 1 was taken, now in Sell phase (transNo=1):
 *      Option: Sell at 22 -> profit = 22 + solve(idx=2, transNo=2)
 *  If Option 2 was taken, still in Buy phase:
 *      Continue with similar decisions...
 * - Continue until all days are processed or 4 transactions (2 buys + 2 sells) are completed.
 * - Final max profit computed: 87 (buy at 10 and sell at 22 yields profit 12; buy at 5 and sell at 80 yields profit 75; total 12+75=87).
 */

/************************************************************ JAVA ************************************************/

// Approach: Recursive solution with memoization (DP). At each day, decide whether to buy or sell based on current state, caching results to avoid recomputation.
// Time Complexity: O(n * 2*k) which simplifies to O(n*k) since there are 2*k transaction states processed once each.
// Space Complexity: O(n * 2*k) for the DP table plus O(n) for the recursion stack.
class Solution {
    static int solve(int[] prices, int k, int idx, int transNo, int n, int[][] t) {
        if (idx == n || transNo == 2 * k) { // Base condition: all days processed or reached maximum transactions
            return 0;
        }
        if (t[idx][transNo] != Integer.MIN_VALUE) { // Return cached result if available
            return t[idx][transNo];
        }
        if (transNo % 2 == 0) { // Buy phase
            // Option 1: Buy at current day -> subtract prices[idx] and move to next state (transNo + 1)
            // Option 2: Skip buying -> remain in current state and move to next day
            return t[idx][transNo] = Math.max(-prices[idx] + solve(prices, k, idx + 1, transNo + 1, n, t),
                                                         0 + solve(prices, k, idx + 1, transNo, n, t));
        }
        // Sell phase
        // Option 1: Sell at current day -> add prices[idx] and move to next state (transNo + 1)
        // Option 2: Skip selling -> remain in current state and move to next day
        return t[idx][transNo] = Math.max(prices[idx] + solve(prices, k, idx + 1, transNo + 1, n, t),
                                                    0 + solve(prices, k, idx + 1, transNo, n, t));
    }

    static int maxProfit(int prices[], int k) {
        int n = prices.length;
        int[][] t = new int[n][2 * k];

        // Initialize dp array with a sentinel value to indicate uncomputed states
        for (int i = 0; i < n; i++) {
            Arrays.fill(t[i], Integer.MIN_VALUE);
        }
        return solve(prices, k, 0, 0, n, t);
    }
}
/*
 * Dry Run:
 * For prices[] = [10, 22, 5, 80] and k = 2:
 * - Starting at idx = 0, transNo = 0 (Buy phase):
 *   Option 1: Buy at 10 -> profit = -10 + solve(idx = 1, transNo = 1)
 *   Option 2: Skip buying -> profit = solve(idx = 1, transNo = 0)
 * - At idx = 1:
 *   If Option 1 was chosen, now in Sell phase (transNo = 1):
 *        Option: Sell at 22 -> profit = 22 + solve(idx = 2, transNo = 2)
 *   If Option 2 was chosen, remain in Buy phase:
 *        Continue with similar decision-making...
 * - Process continues until transactions complete or all days are processed.
 * - Final max profit computed: 87 (first transaction: buy at 10, sell at 22; second transaction: buy at 5, sell at 80).
 */
