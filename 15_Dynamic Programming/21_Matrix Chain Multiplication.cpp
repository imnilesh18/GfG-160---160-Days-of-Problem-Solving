/*
 * Matrix Chain Multiplication
 *
 * Given an array arr[] which represents the dimensions of a sequence of matrices where the ith matrix has the dimensions (arr[i-1] x arr[i]) for i>=1, find the most efficient way to multiply these matrices together. The efficient way is the one that involves the least number of multiplications.
 *
 * Examples:
 *
 * Input: arr[] = [2, 1, 3, 4]
 * Output: 20
 * Explanation: There are 3 matrices of dimensions 2 × 1, 1 × 3, and 3 × 4, Let this 3 input matrices be M1, M2, and M3. There are two ways to multiply: ((M1 x M2) x M3) and (M1 x (M2 x M3)), note that the result of (M1 x M2) is a 2 x 3 matrix and result of (M2 x M3) is a 1 x 4 matrix.
 * ((M1 x M2) x M3)  requires (2 x 1 x 3) + (2 x 3 x 4) = 30
 * (M1 x (M2 x M3))  requires (1 x 3 x 4) + (2 x 1 x 4) = 20.
 * The minimum of these two is 20.
 *
 * Input: arr[] = [1, 2, 3, 4, 3]
 * Output: 30
 * Explanation: There are 4 matrices of dimensions 1 × 2, 2 × 3, 3 × 4, 4 × 3. Let this 4 input matrices be M1, M2, M3 and M4. The minimum number of multiplications are obtained by ((M1 x M2) x M3) x M4). The minimum number is (1 x 2 x 3) + (1 x 3 x 4) + (1 x 4 x 3) = 30.
 *
 * Input: arr[] = [3, 4]
 * Output: 0
 * Explanation: As there is only one matrix so, there is no cost of multiplication.
 *
 * Constraints:
 * 2 ≤ arr.size() ≤ 100
 * 1 ≤ arr[i] ≤ 200
 */

/************************************************************ C++ ************************************************/

// Approach 1 (Recursion + Memoization): Recursively split the matrix chain at every possible partition and calculate the cost of multiplying the sub-chains, using memoization (DP) to store already computed results.
// Time Complexity: O(n^3) -> For each sub-chain (O(n^2) subproblems) we iterate over possible partition points (O(n) per subproblem).
// Space Complexity: O(n^2) -> For memoization table, plus O(n) recursion stack which is dominated by O(n^2).
class Solution {
public:
    // Recursive function to calculate minimum multiplication cost for matrices i to j.
    int solve(int i, int j, vector<int>& arr, vector<vector<int> >& t) {
        // Base case: When there is only one matrix, no multiplication is needed.
        if (i == j) {
            return 0;
        }

        // If the subproblem has already been solved, return the stored result.
        if (t[i][j] != -1) {
            return t[i][j];
        }

        int mini = INT_MAX;

        // Try all possible partitions between i and j.
        for (int k = i; k < j; k++) {
            // Calculate the cost of multiplying the matrices from i to k and k+1 to j,
            // then add the cost of multiplying the two resultant matrices.
            int steps = arr[i - 1] * arr[k] * arr[j]      // Cost for multiplying the two resultant matrices.
                        + solve(i, k, arr, t)             // Cost of multiplying the left sub-chain.
                        + solve(k + 1, j, arr, t);        // Cost of multiplying the right sub-chain.

            // Update mini with the minimum cost found.
            mini = min(mini, steps);
        }

        // Store the computed result in memoization table and return it.
        return t[i][j] = mini;
    }
    
    // Main function to initiate the matrix chain multiplication calculation.
    int matrixMultiplication(vector<int>& arr) {
        int n = arr.size();
        // Create a DP table initialized with -1 to denote uncomputed subproblems.
        vector<vector<int> > t(n, vector<int>(n, -1));

        // We call solve from 1 to n-1 since the chain is represented from arr[0] to arr[n-1].
        return solve(1, n - 1, arr, t);
    }
};

/*
 * Dry Run:
 * Input: arr[] = [2, 1, 3, 4]
 * Matrices: M1 = 2x1, M2 = 1x3, M3 = 3x4
 *
 * Call: matrixMultiplication(arr) -> Calls solve(1, 3, arr, t)
 * -------------------------------------------------------------
 * solve(1, 3):
 * - For k = 1:
 *    Cost = (arr[0] * arr[1] * arr[3]) + solve(1, 1) + solve(2, 3)
 *         = (2 * 1 * 4) + 0 + solve(2, 3)
 *    -> solve(1, 1) returns 0 (base case)
 *
 *    Now compute solve(2, 3):
 *    solve(2, 3):
 *       - For k = 2:
 *           Cost = (arr[1] * arr[2] * arr[3]) + solve(2, 2) + solve(3, 3)
 *                = (1 * 3 * 4) + 0 + 0 = 12
 *       -> solve(2, 3) returns 12
 *
 *    So, for k = 1: Total cost = 8 + 12 = 20
 *
 * - For k = 2:
 *    Cost = (arr[0] * arr[2] * arr[3]) + solve(1, 2) + solve(3, 3)
 *         = (2 * 3 * 4) + solve(1, 2) + 0
 *         = 24 + solve(1, 2)
 *
 *    Now compute solve(1, 2):
 *    solve(1, 2):
 *       - For k = 1:
 *           Cost = (arr[0] * arr[1] * arr[2]) + solve(1, 1) + solve(2, 2)
 *                = (2 * 1 * 3) + 0 + 0 = 6
 *       -> solve(1, 2) returns 6
 *
 *    So, for k = 2: Total cost = 24 + 6 = 30
 *
 * - Compare both partition costs: min(20, 30) = 20
 *
 * Final Answer: 20
 */

// Approach 2 (Bottom-Up): Use bottom-up dynamic programming to build a table t where t[i][j] represents the minimum number of multiplications needed to compute the product of matrices i to j.
// Time Complexity: O(n^3) - Three nested loops to fill the DP table over the matrix dimensions.
// Space Complexity: O(n^2) - A DP table of size n x n is used.
class Solution {
public:
    int matrixMultiplication(vector<int>& arr) {
        int n = arr.size();

        int t[n][n];

        // Initialize diagonal entries to 0 as multiplying one matrix requires no multiplication.
        for (int i = 1; i < n; i++) {
            t[i][i] = 0;
        }

        // Fill the DP table in bottom-up fashion.
        for (int i = n - 1; i >= 1; i--) {
            for (int j = i + 1; j < n; j++) {
                int mini = INT_MAX;
                // Try every possible split point between i and j.
                for (int k = i; k < j; k++) {
                    int steps = arr[i - 1] * arr[k] * arr[j]  // Cost for multiplying the resulting matrices.
                                + t[i][k]                     // Cost for multiplying matrices from i to k.
                                + t[k + 1][j];                // Cost for multiplying matrices from k+1 to j.

                    mini = min(mini, steps);
                }
                t[i][j] = mini;
            }
        }
        return t[1][n - 1];
    }
};

/*
 * Dry Run:
 * Input: arr[] = [2, 1, 3, 4]
 * Matrices: M1 = 2x1, M2 = 1x3, M3 = 3x4
 *
 * Step 1: Initialization
 * t[1][1] = 0, t[2][2] = 0, t[3][3] = 0
 *
 * Step 2: Fill the DP table:
 * For i = 3: No j exists such that j > i, so move to i = 2.
 *
 * For i = 2:
 *  For j = 3:
 *    For k = 2:
 *      steps = arr[1] * arr[2] * arr[3] + t[2][2] + t[3][3]
 *            = 1 * 3 * 4 + 0 + 0 = 12
 *    t[2][3] = 12
 *
 * For i = 1:
 *  For j = 2:
 *    For k = 1:
 *      steps = arr[0] * arr[1] * arr[2] + t[1][1] + t[2][2]
 *            = 2 * 1 * 3 + 0 + 0 = 6
 *    t[1][2] = 6
 *
 *  For j = 3:
 *    For k = 1:
 *      steps = arr[0] * arr[1] * arr[3] + t[1][1] + t[2][3]
 *            = 2 * 1 * 4 + 0 + 12 = 20
 *    For k = 2:
 *      steps = arr[0] * arr[2] * arr[3] + t[1][2] + t[3][3]
 *            = 2 * 3 * 4 + 6 + 0 = 30
 *    t[1][3] = min(20, 30) = 20
 *
 * Final Answer: t[1][3] = 20
 */

/************************************************************ JAVA ************************************************/

// Approach 1 (Recursion + Memoization): Recursively split the matrix chain at every possible partition and calculate the cost of multiplying the sub-chains, using memoization (DP) to store already computed results.
// Time Complexity: O(n^3) -> For each sub-chain (O(n^2) subproblems) we iterate over possible partition points (O(n) per subproblem).
// Space Complexity: O(n^2) -> For memoization table, plus O(n) recursion stack which is dominated by O(n^2).
class Solution {
    // Recursive function to calculate minimum multiplication cost for matrices i to j.
    static int solve(int i, int j, int arr[], int t[][]) {
        // Base case: When there is only one matrix, no multiplication is needed.
        if (i == j) {
            return 0;
        }

        // If the subproblem has already been solved, return the stored result.
        if (t[i][j] != -1) {
            return t[i][j];
        }

        int mini = Integer.MAX_VALUE;

        // Try all possible partitions between i and j.
        for (int k = i; k < j; k++) {
            // Calculate the cost of multiplying the matrices from i to k and k+1 to j,
            // then add the cost of multiplying the two resultant matrices.
            int steps = arr[i - 1] * arr[k] * arr[j]    // Cost for multiplying the two resultant matrices.
                        + solve(i, k, arr, t)           // Cost of multiplying the left sub-chain.
                        + solve(k + 1, j, arr, t);      // Cost of multiplying the right sub-chain.

            // Update mini with the minimum cost found.
            mini = Math.min(mini, steps);
        }

        // Store the computed result in memoization table and return it.
        return t[i][j] = mini;
    }

    // Main function to initiate the matrix chain multiplication calculation.
    static int matrixMultiplication(int arr[]) {
        int n = arr.length;
        // Create a DP table initialized with -1 to denote uncomputed subproblems.
        int t[][] = new int[n][n];

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                t[i][j] = -1;
            }
        }
        // We call solve from 1 to n-1 since the chain is represented from arr[0] to arr[n-1].
        return solve(1, n - 1, arr, t);
    }
}

/*
 * Dry Run:
 * Input: arr[] = [2, 1, 3, 4]
 * Matrices: M1 = 2x1, M2 = 1x3, M3 = 3x4
 *
 * Call: matrixMultiplication(arr) -> Calls solve(1, 3, arr, t)
 * -------------------------------------------------------------
 * solve(1, 3):
 * - For k = 1:
 *    Cost = (arr[0] * arr[1] * arr[3]) + solve(1, 1) + solve(2, 3)
 *         = (2 * 1 * 4) + 0 + solve(2, 3)
 *    -> solve(1, 1) returns 0 (base case)
 *
 *    Now compute solve(2, 3):
 *    solve(2, 3):
 *       - For k = 2:
 *           Cost = (arr[1] * arr[2] * arr[3]) + solve(2, 2) + solve(3, 3)
 *                = (1 * 3 * 4) + 0 + 0 = 12
 *       -> solve(2, 3) returns 12
 *
 *    So, for k = 1: Total cost = 8 + 12 = 20
 *
 * - For k = 2:
 *    Cost = (arr[0] * arr[2] * arr[3]) + solve(1, 2) + solve(3, 3)
 *         = (2 * 3 * 4) + solve(1, 2) + 0
 *         = 24 + solve(1, 2)
 *
 *    Now compute solve(1, 2):
 *    solve(1, 2):
 *       - For k = 1:
 *           Cost = (arr[0] * arr[1] * arr[2]) + solve(1, 1) + solve(2, 2)
 *                = (2 * 1 * 3) + 0 + 0 = 6
 *       -> solve(1, 2) returns 6
 *
 *    So, for k = 2: Total cost = 24 + 6 = 30
 *
 * - Compare both partition costs: min(20, 30) = 20
 *
 * Final Answer: 20
 */

// Approach 2 (Bottom-Up): Use bottom-up dynamic programming to fill a 2D table t where t[i][j] holds the minimum multiplication cost for multiplying matrices from index i to j.
// Time Complexity: O(n^3) - Triple nested loops iterate over the possible sub-chain lengths and partition points.
// Space Complexity: O(n^2) - A DP table of size n x n is maintained to store the computed costs.
class Solution {
    public static int matrixMultiplication(int[] arr) {
        int n = arr.length;
        int[][] t = new int[n][n];

        // Initialize the diagonal entries to 0 because a single matrix multiplication has no cost.
        for (int i = 1; i < n; i++) {
            t[i][i] = 0;
        }

        // Fill the DP table in bottom-up manner.
        for (int i = n - 1; i >= 1; i--) {
            for (int j = i + 1; j < n; j++) {
                int mini = Integer.MAX_VALUE;
                // Evaluate all possible partition points.
                for (int k = i; k < j; k++) {
                    int steps = arr[i - 1] * arr[k] * arr[j] // Cost for multiplying the two resulting matrices.
                                + t[i][k]                    // Cost for multiplying the sub-chain from i to k.
                                + t[k + 1][j];               // Cost for multiplying the sub-chain from k+1 to j.
                    mini = Math.min(mini, steps);
                }
                t[i][j] = mini;
            }
        }
        return t[1][n - 1];
    }
}

/*
 * Dry Run:
 * Input: arr[] = [2, 1, 3, 4]
 * Matrices: M1 = 2x1, M2 = 1x3, M3 = 3x4
 *
 * Step 1: Initialization
 * Set t[1][1] = 0, t[2][2] = 0, t[3][3] = 0
 *
 * Step 2: Fill the DP table:
 * For i = 3: (No valid j exists where j > i)
 *
 * For i = 2:
 *  For j = 3:
 *    For k = 2:
 *      steps = arr[1] * arr[2] * arr[3] + t[2][2] + t[3][3]
 *            = 1 * 3 * 4 + 0 + 0 = 12
 *    t[2][3] = 12
 *
 * For i = 1:
 *  For j = 2:
 *    For k = 1:
 *      steps = arr[0] * arr[1] * arr[2] + t[1][1] + t[2][2]
 *            = 2 * 1 * 3 + 0 + 0 = 6
 *    t[1][2] = 6
 *
 *  For j = 3:
 *    For k = 1:
 *      steps = arr[0] * arr[1] * arr[3] + t[1][1] + t[2][3]
 *            = 2 * 1 * 4 + 0 + 12 = 20
 *    For k = 2:
 *      steps = arr[0] * arr[2] * arr[3] + t[1][2] + t[3][3]
 *            = 2 * 3 * 4 + 6 + 0 = 30
 *    t[1][3] = min(20, 30) = 20
 *
 * Final Answer: t[1][3] = 20
 */
