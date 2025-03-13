/*
 * 0 - 1 Knapsack Problem
 *
 * Given n items, each with a specific weight and value, and a knapsack with a capacity of W, the task is to put the items in the knapsack such that the sum of weights of the items <= W and the sum of values associated with them is maximized.
 * Note: You can either place an item entirely in the bag or leave it out entirely. Also, each item is available in single quantity.
 *
 * Examples :
 *
 * Input: W = 4, val[] = [1, 2, 3], wt[] = [4, 5, 1]
 * Output: 3
 * Explanation: Choose the last item, which weighs 1 unit and has a value of 3.
 *
 * Input: W = 3, val[] = [1, 2, 3], wt[] = [4, 5, 6]
 * Output: 0
 * Explanation: Every item has a weight exceeding the knapsack's capacity (3).
 *
 * Input: W = 5, val[] = [10, 40, 30, 50], wt[] = [5, 4, 2, 3]
 * Output: 80
 * Explanation: Choose the third item (value 30, weight 2) and the last item (value 50, weight 3) for a total value of 80.
 *
 * Constraints:
 * 2 ≤ val.size() = wt.size() ≤ 10^3
 * 1 ≤ W ≤ 10^3
 * 1 ≤ val[i] ≤ 10^3
 * 1 ≤ wt[i] ≤ 10^3
 */

/************************************************************ C++ ************************************************/

// Approach: Use dynamic programming with a 2D DP table to store maximum value for each sub-problem.
// Time Complexity: O(n * W), as we iterate through each item and every possible capacity.
// Space Complexity: O(n * W), due to the 2D DP table of size n x (W+1).
class Solution {
public:
    int knapsack(int W, vector<int>& val, vector<int>& wt) {
        int n = val.size();
        // Create a 2D DP table with dimensions n x (W+1) and initialize with 0.
        vector<vector<int> > dp(n, vector<int>(W + 1, 0));

        // Base condition: For the first item, if its weight is less than or equal to the capacity,
        // then for all capacities >= wt[0], the maximum value is val[0].
        for (int cap = wt[0]; cap <= W; cap++) {
            dp[0][cap] = val[0];
        }

        // Build the DP table using a bottom-up approach.
        for (int ind = 1; ind < n; ind++) {
            for (int cap = 0; cap <= W; cap++) {
                // Option 1: Do not take the current item.
                int notTaken = dp[ind - 1][cap];
                // Option 2: Take the current item (only if it fits in the current capacity).
                int taken = INT_MIN;
                if (wt[ind] <= cap) {
                    taken = val[ind] + dp[ind - 1][cap - wt[ind]];
                }
                // The current cell is the max of taking or not taking the item.
                dp[ind][cap] = max(notTaken, taken);
            }
        }
        // The final answer is in the bottom-right cell of the DP table.
        return dp[n - 1][W];
    }
};

/*
 * Dry Run:
 * For example, let W = 5, val = [10, 40, 30, 50], wt = [5, 4, 2, 3].
 *
 * Base Condition (Index 0):
 * - For capacities from 5 to 5, dp[0][cap] is set to 10.
 * dp[0] = [0, 0, 0, 0, 0, 10]
 *
 * For index 1 (item with weight 4, value 40):
 * - cap = 0 to 3: cannot take the item, so dp[1][cap] = dp[0][cap] (all 0).
 * - cap = 4: can take the item, dp[1][4] = max(dp[0][4] (0), 40 + dp[0][0] (0)) = 40.
 * - cap = 5: dp[1][5] = max(dp[0][5] (10), 40 + dp[0][1] (0)) = 40.
 *
 * For index 2 (item with weight 2, value 30) and index 3 (item with weight 3, value 50),
 * the DP table is updated similarly. The final answer at dp[3][5] becomes 80.
 */

/************************************************************ JAVA ************************************************/

// Approach: Use dynamic programming with a 2D DP table to store maximum value for each sub-problem.
// Time Complexity: O(n * W), as we iterate over each item and every capacity from 0 to W.
// Space Complexity: O(n * W), due to the use of a 2D DP table of size n x (W+1).
class Solution {
    public static int knapsack(int W, int val[], int wt[]) {
        int n = val.length;
        // Create a 2D DP table with dimensions n x (W+1) and initialize with 0.
        int dp[][] = new int[n][W + 1];

        // Base condition: For the first item, if its weight is less than or equal to the capacity,
        // then for all capacities >= wt[0], the maximum value is val[0].
        for (int cap = wt[0]; cap <= W; cap++) {
            dp[0][cap] = val[0];
        }

        // Build the DP table using a bottom-up approach.
        for (int ind = 1; ind < n; ind++) {
            for (int cap = 0; cap <= W; cap++) {
                // Option 1: Do not include the current item.
                int notTaken = dp[ind - 1][cap];
                // Option 2: Include the current item (if it fits in the knapsack).
                int taken = Integer.MIN_VALUE;
                if (wt[ind] <= cap) {
                    taken = val[ind] + dp[ind - 1][cap - wt[ind]];
                }
                // The cell dp[ind][cap] is the maximum of including or excluding the item.
                dp[ind][cap] = Math.max(notTaken, taken);
            }
        }
        // The final answer is at dp[n-1][W].
        return dp[n - 1][W];
    }
}

/*
 * Dry Run:
 * For example, let W = 5, val = [10, 40, 30, 50] and wt = [5, 4, 2, 3].
 *
 * Base Condition (Index 0):
 * - For capacities from 5 to 5, dp[0][cap] is set to 10.
 * dp[0] = [0, 0, 0, 0, 0, 10]
 *
 * For index 1 (item with weight 4, value 40):
 * - cap = 0 to 3: cannot take the item, so dp[1][cap] = dp[0][cap] (all 0).
 * - cap = 4: dp[1][4] = max(dp[0][4] (0), 40 + dp[0][0] (0)) = 40.
 * - cap = 5: dp[1][5] = max(dp[0][5] (10), 40 + dp[0][1] (0)) = 40.
 *
 * Continue similarly for index 2 and index 3.
 * Final answer: dp[3][5] equals 80.
 */
