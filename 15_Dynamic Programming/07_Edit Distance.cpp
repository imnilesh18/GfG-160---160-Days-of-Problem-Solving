/*
 * Edit Distance
 *
 * Given two strings s1 and s2. Return the minimum number of operations required to convert s1 to s2.
 * The possible operations are permitted:
 * Insert a character at any position of the string.
 * Remove any character from the string.
 * Replace any character from the string with any other character.
 *
 * Examples:
 *
 * Input: s1 = "geek", s2 = "gesek"
 * Output: 1
 * Explanation: One operation is required, inserting 's' between two 'e' in s1.
 *
 * Input: s1 = "gfg", s2 = "gfg"
 * Output: 0
 * Explanation: Both strings are same.
 *
 * Input: s1 = "abcd", s2 = "bcfe"
 * Output: 3
 * Explanation: We can convert s1 into s2 by removing ‘a’, replacing ‘d’ with ‘f’ and inserting ‘e’ at the end.
 *
 * Constraints:
 * 1 ≤ s1.length(), s2.length() ≤ 10^3
 * Both the strings are in lowercase.
 */

/************************************************************ C++ ************************************************/

// Approach: Bottom-up dynamic programming where dp[i][j] stores the edit distance between the first i characters of s1 and first j characters of s2.
// Time Complexity: O(m*n) where m and n are the lengths of s1 and s2 respectively, as we fill a 2D table of size (m+1)*(n+1).
// Space Complexity: O(m*n) for storing the dp table.
class Solution {
public:
    int editDistance(string& s1, string& s2) {
        int m = s1.length();
        int n = s2.length();
        vector<vector<int> > dp(m + 1, vector<int>(n + 1, 0));

        // Fill dp table
        for (int i = 0; i <= m; i++) {
            for (int j = 0; j <= n; j++) {
                // If one of the strings is empty, the edit distance equals the length of the other string.
                if (i == 0 || j == 0) {
                    dp[i][j] = i + j;
                }
                // If characters are the same, no new operation is required.
                else if (s1[i - 1] == s2[j - 1]) {
                    dp[i][j] = dp[i - 1][j - 1];
                }
                // If characters differ, consider insert, remove, and replace operations.
                else{
                    dp[i][j] = 1 + min({ dp[i][j - 1], dp[i - 1][j], dp[i - 1][j - 1] });
                }
            }
        }
        return dp[m][n];
    }
};

/*
 * Dry Run:
 * s1 = "abcd", s2 = "bcfe"
 * Initial dp table dimensions: 5 x 5 (indices 0 to 4)
 * -------------------------------------------------
 * i\j   0    1    2    3    4
 * 0    [0,   1,   2,   3,   4]
 * 1    [1,   ?,   ?,   ?,   ?]
 * 2    [2,   ?,   ?,   ?,   ?]
 * 3    [3,   ?,   ?,   ?,   ?]
 * 4    [4,   ?,   ?,   ?,   ?]
 *
 * For i=1, j=1:
 * s1[0] = 'a' and s2[0] = 'b' (different)
 * dp[1][1] = 1 + min(dp[1][0]=1, dp[0][1]=1, dp[0][0]=0) = 1
 *
 * The table is filled similarly and finally, dp[4][4] becomes 3, meaning 3 operations are required.
 */

/************************************************************ JAVA ************************************************/

// Approach: Bottom-up dynamic programming using a 2D array where dp[i][j] represents the edit distance
// between the first i characters of s1 and the first j characters of s2.
// Time Complexity: O(m*n) where m and n are the lengths of s1 and s2 respectively, due to the nested loops over the dp table.
// Space Complexity: O(m*n) for the dp table used to store computed edit distances.
class Solution {
    public int editDistance(String s1, String s2) {
        int m = s1.length();
        int n = s2.length();
        int[][] dp = new int[m + 1][n + 1];

        // Fill dp table
        for (int i = 0; i <= m; i++) {
            for (int j = 0; j <= n; j++) {
                // Base case: if one string is empty, edit distance equals the length of the other string.
                if (i == 0 || j == 0) {
                    dp[i][j] = i + j;
                }
                // If characters match, no additional cost is incurred.
                else if (s1.charAt(i - 1) == s2.charAt(j - 1)) {
                    dp[i][j] = dp[i - 1][j - 1];
                }
                // If characters differ, consider the minimum of insertion, deletion, or substitution.
                else{
                    dp[i][j] = 1 + Math.min(dp[i][j - 1], Math.min(dp[i - 1][j], dp[i - 1][j - 1]));
                }
            }
        }
        return dp[m][n];
    }
}

/*
 * Dry Run:
 * s1 = "abcd", s2 = "bcfe"
 * Initial dp table dimensions: 5 x 5 (indices 0 to 4)
 * -------------------------------------------------
 * i\j   0    1    2    3    4
 * 0    [0,   1,   2,   3,   4]
 * 1    [1,   ?,   ?,   ?,   ?]
 * 2    [2,   ?,   ?,   ?,   ?]
 * 3    [3,   ?,   ?,   ?,   ?]
 * 4    [4,   ?,   ?,   ?,   ?]
 *
 * For i=1, j=1:
 * s1.charAt(0) = 'a' and s2.charAt(0) = 'b' (different)
 * dp[1][1] = 1 + min(dp[1][0]=1, dp[0][1]=1, dp[0][0]=0) = 1
 *
 * The table is filled similarly and finally, dp[4][4] becomes 3, indicating that 3 operations are required.
 */
