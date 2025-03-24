/*
 * Boolean Parenthesization
 *
 * You are given a boolean expression s containing
 *  'T' ---> true
 *  'F' ---> false
 * and following operators between symbols
 * &   ---> boolean AND
 * |   ---> boolean OR
 * ^   ---> boolean XOR
 * Count the number of ways we can parenthesize the expression so that the value of expression evaluates to true.
 *
 * Note: The answer is guaranteed to fit within a 32-bit integer.
 *
 * Examples:
 *
 * Input: s = "T|T&F^T"
 * Output: 4
 * Explaination: The expression evaluates to true in 4 ways: ((T|T)&(F^T)), (T|(T&(F^T))), (((T|T)&F)^T) and (T|((T&F)^T)).
 *
 * Input: s = "T^F|F"
 * Output: 2
 * Explaination: The expression evaluates to true in 2 ways: ((T^F)|F) and (T^(F|F)).
 *
 * Constraints:
 * 1 ≤ |s| ≤ 100
 */

/************************************************************ C++ ************************************************/

// Approach: Use recursion with memoization (DP) to count the number of ways to parenthesize the expression so that it evaluates to true.
// Time Complexity: O(n^3) - because for every subexpression (O(n^2) subproblems) we iterate over all possible operator partitions (O(n)).
// Space Complexity: O(n^3) - for storing computed results in a 3D DP table.
class Solution {
public:
    // Recursive helper function that computes the number of ways the substring s[i...j] can be evaluated to a boolean value.
    int solve(int i, int j, int isTrue, string& s, vector<vector<vector<int>>>& t) {
        // If the current substring indices are invalid, return 0 as there are no ways to evaluate.
        if (i > j) {
            return 0;
        }

        // If the substring consists of only one character, it's a base case.
        // Return 1 if the character matches the required boolean value, else return 0.
        if (i == j) {
            if (isTrue) {
                return s[i] == 'T';
            } else {
                return s[i] == 'F';
            }
        }

        // If the answer for this subproblem is already computed, return the stored result.
        if (t[i][j][isTrue] != -1) {
            return t[i][j][isTrue];
        }

        int ways = 0;
        // Iterate over the expression, considering only positions with operators (operators are at odd indices).
        for (int idx = i + 1; idx <= j - 1; idx += 2) {
            // Recursively compute the number of ways for the left substring to be true and false.
            int lT = solve(i, idx - 1, 1, s, t);
            int lF = solve(i, idx - 1, 0, s, t);
            // Recursively compute the number of ways for the right substring to be true and false.
            int rT = solve(idx + 1, j, 1, s, t);
            int rF = solve(idx + 1, j, 0, s, t);

            // Evaluate based on the current operator:
            if (s[idx] == '&') {
                // For AND, true only when both left and right are true.
                if (isTrue) {
                    ways += lT * rT;
                } else {
                    // False when any one (or both) of left or right are false.
                    ways += (lT * rF) + (lF * rT) + (lF * rF);
                }
            } else if (s[idx] == '|') {
                // For OR, true if at least one of left or right is true.
                if (isTrue) {
                    ways += (lT * rT) + (lT * rF) + (lF * rT);
                } else {
                    // False only when both left and right are false.
                    ways += lF * rF;
                }
            } else { // Operator '^' (XOR)
                // For XOR, true if exactly one of left or right is true.
                if (isTrue) {
                    ways += (lT * rF) + (lF * rT);
                } else {
                    // False if both are true or both are false.
                    ways += (lT * rT) + (lF * rF);
                }
            }
        }
        // Store the computed result in the DP table to avoid recomputation, then return it.
        return t[i][j][isTrue] = ways;
    }

    // Main function that initiates the recursive evaluation of the expression s.
    int countWays(string& s) {
        int n = s.size();
        // Create a 3D DP table of dimensions [n][n][2] initialized to -1.
        vector<vector<vector<int>>> t(n, vector<vector<int>>(n, vector<int>(2, -1)));

        // Evaluate the entire string (from index 0 to n-1) for a true outcome (isTrue = 1).
        return solve(0, n - 1, 1, s, t);
    }
};

/*
 * Dry Run:
 * For s = "T|T&F^T":
 * 1. countWays is called, and a DP table is initialized. Then solve(0,6,1,s,t) is invoked.
 * 2. At solve(0,6,1,s,t), the function loops over operators. The first operator at index 1 ('|') splits the expression:
 * - Left subexpression: "T" (indices 0 to 0), which is directly evaluated as true.
 * - Right subexpression: "T&F^T" (indices 2 to 6), which is further processed.
 * 3. In the right subexpression "T&F^T", the operator at index 3 ('&') is used to partition it:
 * - Left: "T" (index 2), and Right: "F^T" (indices 4 to 6).
 * 4. The subexpression "F^T" is split at index 5 ('^') into "F" and "T". Both are base cases.
 * 5. Each recursive call returns counts for true and false evaluations, which are combined based on the operator rules.
 * 6. Intermediate results are stored in the DP table and combined to yield the final count.
 * 7. The total number of ways to parenthesize "T|T&F^T" to yield true is returned.
 */

/************************************************************ JAVA ************************************************/

// Approach: Use recursion with memoization (DP) to count ways to parenthesize the expression so that it evaluates to true.
// Time Complexity: O(n^3) - due to recursively splitting the expression into all possible subexpressions and iterating over all operators.
// Space Complexity: O(n^3) - for the 3D memoization array 't' that stores results for subproblems.
class Solution {
    // Recursive helper function that returns the number of ways the substring s[i...j] can evaluate to the boolean value represented by isTrue.
    static int solve(int i, int j, int isTrue, String s, int[][][] t) {
        // If the substring indices are invalid, return 0 ways.
        if (i > j) {
            return 0;
        }

        // Base case: if the substring is a single character, return 1 if it matches the desired boolean value, otherwise 0.
        if (i == j) {
            if (isTrue == 1) {
                return s.charAt(i) == 'T' ? 1 : 0;
            } else {
                return s.charAt(i) == 'F' ? 1 : 0;
            }
        }

        // If this subproblem has already been computed, return the stored result from t.
        if (t[i][j][isTrue] != -1) {
            return t[i][j][isTrue];
        }

        int ways = 0;
        // Iterate over the string, considering only operator positions (which are at odd indices).
        for (int idx = i + 1; idx <= j - 1; idx += 2) {
            // Recursively calculate the number of ways for the left substring to evaluate to true and false.
            int lT = solve(i, idx - 1, 1, s, t);
            int lF = solve(i, idx - 1, 0, s, t);
            // Recursively calculate the number of ways for the right substring to evaluate to true and false.
            int rT = solve(idx + 1, j, 1, s, t);
            int rF = solve(idx + 1, j, 0, s, t);

            // Evaluate based on the operator at the current index:
            if (s.charAt(idx) == '&') {
                // For AND: expression is true only if both left and right are true.
                if (isTrue == 1) {
                    ways += lT * rT;
                } else {
                    // If false: any case where at least one side is false.
                    ways += (lT * rF) + (lF * rT) + (lF * rF);
                }
            } else if (s.charAt(idx) == '|') {
                // For OR: expression is true if at least one side is true.
                if (isTrue == 1) {
                    ways += (lT * rT) + (lT * rF) + (lF * rT);
                } else {
                    // For false: only when both left and right are false.
                    ways += lF * rF;
                }
            } else { // Operator '^' for XOR
                // For XOR: true if exactly one of the sides is true.
                if (isTrue == 1) {
                    ways += (lT * rF) + (lF * rT);
                } else {
                    // For false: when both sides are true or both are false.
                    ways += (lT * rT) + (lF * rF);
                }
            }
        }
        // Store the computed result in t and return it.
        t[i][j][isTrue] = ways;
        return ways;
    }

    // Main function that returns the total number of ways to parenthesize the expression s so that it evaluates to true.
    static int countWays(String s) {
        int n = s.length();
        // Create a 3D DP array 't' with dimensions [n][n][2] and initialize each entry with -1.
        int[][][] t = new int[n][n][2];

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                t[i][j][0] = -1;
                t[i][j][1] = -1;
            }
        }
        // Evaluate the entire expression (from index 0 to n-1) for a true outcome (isTrue = 1) and return the result.
        return solve(0, n - 1, 1, s, t);
    }
}

/*
 * Dry Run:
 * For s = "T|T&F^T":
 * 1. countWays("T|T&F^T") initializes the 3D array 't' and calls solve(0, 6, 1, s, t).
 * 2. In solve(0,6,1,s,t), the function iterates over operators in s. The first operator at index 1 ('|') splits the expression:
 * - Left subexpression: "T" (index 0 to 0), which is a base case evaluating to true.
 * - Right subexpression: "T&F^T" (index 2 to 6), which is further processed.
 * 3. For "T&F^T", the operator at index 3 ('&') splits it into:
 * - Left: "T" (index 2), a base case returning true.
 * - Right: "F^T" (index 4 to 6), which is split at index 5 ('^') into:
 *   - Left: "F" (index 4) and Right: "T" (index 6); both are base cases.
 * 4. Each recursive call returns counts for true and false evaluations, which are then combined using the operator rules:
 * - For '|': true if at least one side is true.
 * - For '&': true if both sides are true.
 * - For '^': true if exactly one side is true.
 * 5. The intermediate results are memoized in the array 't', and finally, the aggregated result (the total number of ways to parenthesize s to yield true) is returned.
 */
