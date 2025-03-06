/*
 * Longest Common Subsequence
 *
 * Given two strings s1 and s2, return the length of their longest common subsequence (LCS). If there is no common subsequence, return 0.
 *
 * A subsequence is a sequence that can be derived from the given string by deleting some or no elements without changing the order of the remaining elements. For example, "ABE" is a subsequence of "ABCDE".
 *
 * Examples:
 *
 * Input: s1 = "ABCDGH", s2 = "AEDFHR"
 * Output: 3
 * Explanation: The longest common subsequence of "ABCDGH" and "AEDFHR" is "ADH", which has a length of 3.
 *
 * Input: s1 = "ABC", s2 = "AC"
 * Output: 2
 * Explanation: The longest common subsequence of "ABC" and "AC" is "AC", which has a length of 2.
 *
 * Input: s1 = "XYZW", s2 = "XYWZ"
 * Output: 3
 * Explanation: The longest common subsequences of "XYZW" and "XYWZ" are "XYZ" and "XYW", both of length 3.
 * Constraints:
 * 1<= s1.size(), s2.size() <=10^3
 * Both strings s1 and s2 contain only uppercase English letters.
 */

/************************************************************ C++ ************************************************/

// Approach: Bottom-up DP with space optimization using only two rows of the DP table.
// Time Complexity: O(m*n) where m and n are the lengths of s1 and s2, since we iterate through all subproblems.
// Space Complexity: O(n) because we only maintain two rows of size (n+1).
class Solution {
public:
    int lcs(string& s1, string& s2) {
        int m = s1.length();
        int n = s2.length();
        // dp table with 2 rows and (n+1) columns, initialized to 0
        vector<vector<int> > dp(2, vector<int>(n + 1, 0));

        for (int i = 0; i <= m; i++) {
            for (int j = 0; j <= n; j++) {
                // Base condition: if any string is empty, LCS length is 0
                if (i == 0 || j == 0) {
                    dp[i % 2][j] = 0;
                }
                // If current characters match, add 1 to the result from the previous row and previous column
                else if (s1[i - 1] == s2[j - 1]) {
                    dp[i % 2][j] = 1 + dp[(i + 1) % 2][j - 1];
                }
                // Else, take the maximum value from either left cell or the cell from the previous row
                else{
                    dp[i % 2][j] = max(dp[i % 2][j - 1], dp[(i + 1) % 2][j]);
                }
            }
        }
        return dp[m % 2][n];
    }
};

/*
 * Dry Run
 * Example: s1 = "abc", s2 = "abc"
 *
 * Initialization:
 * m = 3, n = 3
 * dp = [ [0, 0, 0, 0],
 *       [0, 0, 0, 0] ]
 *
 * Iteration:
 * i = 0: Base row, dp[0][:] remains [0, 0, 0, 0].
 *
 * i = 1 (processing character 'a' from s1):
 *  j = 0: dp[1][0] = 0 (base case).
 *  j = 1: s1[0] ('a') == s2[0] ('a') -> dp[1][1] = 1 + dp[0][0] = 1.
 *  j = 2: s1[0] ('a') != s2[1] ('b') -> dp[1][2] = max(dp[1][1], dp[0][2]) = 1.
 *  j = 3: s1[0] ('a') != s2[2] ('c') -> dp[1][3] = max(dp[1][2], dp[0][3]) = 1.
 *  dp now becomes: [ [0, 0, 0, 0],
 *                    [0, 1, 1, 1] ].
 *
 * i = 2 (processing character 'b' from s1):
 *  j = 0: dp[0][0] = 0 (base case, row index: i % 2 = 0).
 *  j = 1: s1[1] ('b') != s2[0] ('a') -> dp[0][1] = max(dp[0][0], dp[1][1]) = 1.
 *  j = 2: s1[1] ('b') == s2[1] ('b') -> dp[0][2] = 1 + dp[1][1] = 2.
 *  j = 3: s1[1] ('b') != s2[2] ('c') -> dp[0][3] = max(dp[0][2], dp[1][3]) = 2.
 *  dp now becomes: [ [0, 1, 2, 2],
 *                    [0, 1, 1, 1] ].
 *
 * i = 3 (processing character 'c' from s1):
 *  j = 0: dp[1][0] = 0 (base case, row index: i % 2 = 1).
 *  j = 1: s1[2] ('c') != s2[0] ('a') -> dp[1][1] = max(dp[1][0], dp[0][1]) = 1.
 *  j = 2: s1[2] ('c') != s2[1] ('b') -> dp[1][2] = max(dp[1][1], dp[0][2]) = 2.
 *  j = 3: s1[2] ('c') == s2[2] ('c') -> dp[1][3] = 1 + dp[0][2] = 3.
 *  dp now becomes: [ [0, 1, 2, 2],
 *                    [0, 1, 2, 3] ].
 *
 * Final
 */

/************************************************************ JAVA ************************************************/

// Approach: Bottom-up DP with space optimization using only two rows of the DP table.
// Time Complexity: O(m*n) where m and n are the lengths of s1 and s2, as we process every cell in the table.
// Space Complexity: O(n) because we only maintain two rows of size (n+1).
class Solution {
    static int lcs(String s1, String s2) {
        int m = s1.length();
        int n = s2.length();
        // dp table with 2 rows and (n+1) columns, initialized to 0
        int[][] dp = new int[2][n + 1];

        for (int i = 0; i <= m; i++) {
            for (int j = 0; j <= n; j++) {
                // Base condition: if any string is empty, LCS length is 0
                if (i == 0 || j == 0) {
                    dp[i % 2][j] = 0;
                }
                // If current characters match, add 1 to the result from the previous row and previous column
                else if (s1.charAt(i - 1) == s2.charAt(j - 1)) {
                    dp[i % 2][j] = 1 + dp[(i + 1) % 2][j - 1];
                }
                // Else, take the maximum value from either left cell or the cell from the previous row
                else{
                    dp[i % 2][j] = Math.max(dp[i % 2][j - 1], dp[(i + 1) % 2][j]);
                }
            }
        }
        return dp[m % 2][n];
    }
}

/*
 * Dry Run
 * Example: s1 = "abc", s2 = "abc"
 *
 * Initialization:
 * m = 3, n = 3
 * dp = new int[2][4] initialized to zeros.
 *
 * Iteration:
 * i = 0: Base row, dp[0][:] remains [0, 0, 0, 0].
 *
 * i = 1 (processing character 'a' from s1):
 *  j = 0: dp[1][0] = 0 (base case).
 *  j = 1: s1.charAt(0) ('a') == s2.charAt(0) ('a') -> dp[1][1] = 1 + dp[0][0] = 1.
 *  j = 2: s1.charAt(0) ('a') != s2.charAt(1) ('b') -> dp[1][2] = Math.max(dp[1][1], dp[0][2]) = 1.
 *  j = 3: s1.charAt(0) ('a') != s2.charAt(2) ('c') -> dp[1][3] = Math.max(dp[1][2], dp[0][3]) = 1.
 *  dp now becomes: [ [0, 0, 0, 0],
 *                    [0, 1, 1, 1] ].
 *
 * i = 2 (processing character 'b' from s1):
 *  j = 0: dp[0][0] = 0 (base case, row index: i % 2 = 0).
 *  j = 1: s1.charAt(1) ('b') != s2.charAt(0) ('a') -> dp[0][1] = Math.max(dp[0][0], dp[1][1]) = 1.
 *  j = 2: s1.charAt(1) ('b') == s2.charAt(1) ('b') -> dp[0][2] = 1 + dp[1][1] = 2.
 *  j = 3: s1.charAt(1) ('b') != s2.charAt(2) ('c') -> dp[0][3] = Math.max(dp[0][2], dp[1][3]) = 2.
 *  dp now becomes: [ [0, 1, 2, 2],
 *                    [0, 1, 1, 1] ].
 *
 * i = 3 (processing character 'c' from s1):
 *  j = 0: dp[1][0] = 0 (base case, row index: i % 2 = 1).
 *  j = 1: s1.charAt(2) ('c') != s2.charAt(0) ('a') -> dp[1][1] = Math.max(dp[1][0], dp[0][1]) = 1.
 *  j = 2: s1.charAt(2) ('c') != s2.charAt(1) ('b') -> dp[1][2] = Math.max(dp[1][1], dp[0][2]) = 2.
 *  j = 3: s1.charAt(2) ('c') == s2.charAt(2) ('c') -> dp[1][3] = 1 + dp[0][2] = 3.
 *  dp now becomes: [ [0, 1, 2, 2],
 *                    [0, 1, 2, 3] ].
 *
 * Final Result: dp[m % 2][n] = dp[3 % 2][3] = dp[1][3] = 3.
 */
