/*
 * Min Cost Climbing Stairs
 *
 * Given an array of integers cost[] where cost[i] is the cost of the ith step on a staircase.Once the cost is paid, you can either climb one or two steps.Return the minimum cost to reach the top of the floor.
 * Assume 0 - based Indexing.You can either start from the step with index 0, or the step with index 1.
 *
 * Examples:
 *
 * Input: cost[] = [10, 15, 20]
 * Output : 15
 * Explanation: Cheapest option is to start at cost[1], pay that cost, and go to the top.
 *
 * Input: cost[] = [1, 100, 1, 1, 1, 100, 1, 1, 100, 1]
 * Output : 6
 * Explanation: Cheapest option is to start on cost[0], and only step on 1s, skipping cost[3].
 *
 * Constraints:
 * 2 ≤ cost.size() ≤ 10 ^ 5
 * 0 ≤ cost[i] ≤ 999
 */

/************************************************************ C++ ************************************************/

// Approach 1: Use recursion with memoization (top-down dynamic programming) to compute the minimum cost from a given index by choosing either a one-step or two-step jump.
// Time Complexity: O(n) because each index is computed only once.
// Space Complexity: O(n) due to the recursion stack and memoization array.
class Solution {
public:
    int t[100001];  // Memoization array to store minimum cost for each index

    // Recursive function to compute minimum cost from the current index
    int solve(int idx, vector<int>& cost) {
        // If index is beyond the last step, no cost is incurred.
        if (idx >= cost.size()) {
            return 0;
        }

        // If already computed, return the stored result.
        if (t[idx] != -1) {
            return t[idx];
        }

        // Option 1: Take one step from current index.
        int a = cost[idx] + solve(idx + 1, cost);
        // Option 2: Take two steps from current index.
        int b = cost[idx] + solve(idx + 2, cost);

        // Store and return the minimum cost between the two options.
        return t[idx] = min(a, b);
    }
    // Function to compute the minimum cost to reach the top starting from index 0 or index 1.
    int minCostClimbingStairs(vector<int>& cost) {
        memset(t, -1, sizeof(t));  // Initialize memoization array with -1
        // Return the minimum cost starting from index 0 or 1.
        return min(solve(0, cost), solve(1, cost));
    }
};

/*
 * Dry Run:
 * For cost = [10, 15, 20]
 *
 * Starting from index 0:
 * - solve(0):
 *    Option 1: 10 + solve(1)
 *    Option 2: 10 + solve(2)
 * - solve(1):
 *    Option 1: 15 + solve(2)
 *    Option 2: 15 + solve(3) -> solve(3) returns 0 (base case)
 *    => solve(1) = 15 + min(solve(2), 0) = 15 + 0 = 15
 * - solve(2):
 *    Option 1: 20 + solve(3) -> 20 + 0 = 20
 *    Option 2: 20 + solve(4) -> solve(4) returns 0, so 20 + 0 = 20
 *    => solve(2) = 20
 * Thus,
 * - solve(0) = 10 + min(solve(1), solve(2)) = 10 + min(15, 20) = 25
 * Final Answer = min(solve(0), solve(1)) = min(25, 15) = 15
 */

// Approach 2: Bottom-up dynamic programming by modifying the cost array to store the minimum cost to reach each step.
// Time Complexity: O(n) because we traverse the array once.
// Space Complexity: O(1) as we update the input array in-place.
class Solution {
public:
    int minCostClimbingStairs(vector<int>& cost) {
        int n = cost.size();

        // If there are only two steps, return the minimum of the two costs.
        if (n == 2) {
            return min(cost[0], cost[1]);
        }

        // Update each step's cost as the cost to reach that step from the optimal previous step.
        for (int i = 2; i < n; i++) {
            cost[i] = cost[i] + min(cost[i - 1], cost[i - 2]);
        }

        // The answer is the minimum cost between the last step and the second last step.
        return min(cost[n - 1], cost[n - 2]);
    }
};

/*
 * Dry Run:
 * For cost = [10, 15, 20]
 * n = 3
 *
 * Iteration:
 * i = 2:
 *  cost[2] = 20 + min(cost[1], cost[0]) = 20 + min(15, 10) = 20 + 10 = 30
 * Updated cost array becomes: [10, 15, 30]
 *
 * Final Step:
 * Return min(cost[2], cost[1]) = min(30, 15) = 15
 */

/************************************************************ JAVA ************************************************/

// Approach 1: Use recursion with memoization (top-down dynamic programming) to compute the minimum cost from a given index by choosing either a one-step or two-step jump.
// Time Complexity: O(n) because each index is computed only once.
// Space Complexity: O(n) due to the recursion stack and memoization array.
class Solution {
    // Memoization array to store minimum cost for each index (size: 100001)
    static int[] t = new int[100001];

    // Recursive function to compute minimum cost from the current index
    static int solve(int idx, int[] cost) {
        // If index is beyond the last step, no cost is incurred.
        if (idx >= cost.length) {
            return 0;
        }

        // If already computed, return the stored result.
        if (t[idx] != -1) {
            return t[idx];
        }

        // Option 1: Take one step from current index.
        int a = cost[idx] + solve(idx + 1, cost);
        // Option 2: Take two steps from current index.
        int b = cost[idx] + solve(idx + 2, cost);

        // Store and return the minimum cost between the two options.
        return t[idx] = Math.min(a, b);
    }
    // Function to compute the minimum cost to reach the top starting from index 0 or index 1.
    static int minCostClimbingStairs(int[] cost) {
        // Initialize memoization array with -1
        for (int i = 0; i < t.length; i++) {
            t[i] = -1;
        }
        // Return the minimum cost starting from index 0 or 1.
        return Math.min(solve(0, cost), solve(1, cost));
    }
}

/*
 * Dry Run:
 * For cost = [10, 15, 20]
 *
 * Starting from index 0:
 * - solve(0):
 *    Option 1: 10 + solve(1)
 *    Option 2: 10 + solve(2)
 * - solve(1):
 *    Option 1: 15 + solve(2)
 *    Option 2: 15 + solve(3) -> solve(3) returns 0 (base case)
 *    => solve(1) = 15 + min(solve(2), 0) = 15 + 0 = 15
 * - solve(2):
 *    Option 1: 20 + solve(3) -> 20 + 0 = 20
 *    Option 2: 20 + solve(4) -> solve(4) returns 0, so 20 + 0 = 20
 *    => solve(2) = 20
 * Thus,
 * - solve(0) = 10 + min(solve(1), solve(2)) = 10 + min(15, 20) = 25
 * Final Answer = min(solve(0), solve(1)) = min(25, 15) = 15
 */

// Approach 2: Bottom-up dynamic programming by modifying the cost array to store the minimum cost to reach each step.
// Time Complexity: O(n) because we traverse the array once.
// Space Complexity: O(1) as we update the input array in-place.
class Solution {
    public int minCostClimbingStairs(int[] cost) {
        int n = cost.length;

        // If there are only two steps, return the minimum of the two costs.
        if (n == 2) {
            return Math.min(cost[0], cost[1]);
        }

        // Update each step's cost as the cost to reach that step from the optimal previous step.
        for (int i = 2; i < n; i++) {
            cost[i] = cost[i] + Math.min(cost[i - 1], cost[i - 2]);
        }

        // The answer is the minimum cost between the last step and the second last step.
        return Math.min(cost[n - 1], cost[n - 2]);
    }
}
/*
 * Dry Run:
 * For cost = [10, 15, 20]
 * n = 3
 *
 * Iteration:
 * i = 2:
 *  cost[2] = 20 + Math.min(cost[1], cost[0]) = 20 + Math.min(15, 10) = 20 + 10 = 30
 * Updated cost array becomes: [10, 15, 30]
 *
 * Final Step:
 * Return Math.min(cost[2], cost[1]) = Math.min(30, 15) = 15
 */
