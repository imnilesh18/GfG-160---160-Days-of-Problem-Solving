/*
 * Longest Palindromic Subsequence
 *
 * Given a string s, return the length of the longest palindromic subsequence.
 *
 * A subsequence is a sequence that can be derived from the given sequence by deleting some or no elements without changing the order of the remaining elements.
 *
 * A palindromic sequence is a sequence that reads the same forward and backward.
 *
 * Examples:
 *
 * Input: s = "bbabcbcab"
 * Output: 7
 * Explanation: Subsequence "babcbab" is the longest subsequence which is also a palindrome.
 *
 * Input: s = "abcd"
 * Output: 1
 * Explanation: "a", "b", "c" and "d" are palindromic and all have a length 1.
 *
 * Input: s = "agbdba"
 * Output: 5
 * Explanation: The longest palindromic subsequence is "abdba", which has a length of 5. The characters in this subsequence are taken from the original string "agbdba", and they maintain the order of the string while forming a palindrome.
 *
 * Constraints:
 * 1 ≤ s.size() ≤ 1000
 * The string contains only lowercase letters.
 */

/************************************************************ C++ ************************************************/

// Approach: Use the LCS (Longest Common Subsequence) between the string and its reverse to find the longest palindromic subsequence.
// Time Complexity: O(n^2) - We fill a DP table of size n*n, where n is the length of the string.
// Space Complexity: O(n^2) - A 2D DP table of size n*n is used.
class Solution {
public:
    int longestPalinSubseq(string& s) {
        int    n  = s.size();
        string s1 = s;

        reverse(s1.begin(), s1.end());
        vector<vector<int> > dp(n + 1, vector<int>(n + 1, 0));

        // Fill the DP table using the LCS approach
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= n; j++) {
                if (s[i - 1] == s1[j - 1]) {
                    dp[i][j] = 1 + dp[i - 1][j - 1];
                }else{
                    dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
                }
            }
        }
        return dp[n][n];
    }
};

/*
 * Dry Run
 * --------
 * Input: s = "bbabcbcab"
 * Step 1: Reverse s to get s1 = "bacbcbabb"
 * Step 2: Initialize dp table of size (n+1) x (n+1) with zeros.
 * Step 3: Fill dp table:
 *  - When i = 1, j = 1 to n, compare characters of s and s1.
 *  - Continue for all indices, updating dp[i][j] based on whether characters match.
 * Step 4: Final dp[n][n] gives the length of the longest palindromic subsequence.
 * Output: 7 (The subsequence "babcbab")
 */

/************************************************************ JAVA ************************************************/

// Approach: Use the LCS (Longest Common Subsequence) between the string and its reverse to find the longest palindromic subsequence.
// Time Complexity: O(n^2) - We fill a DP table of size n*n, where n is the length of the string.
// Space Complexity: O(n^2) - A 2D DP table of size n*n is used.
class Solution {
    public int longestPalinSubseq(String s) {
        int    n  = s.length();
        String s1 = new StringBuilder(s).reverse().toString();
        int[][] dp = new int[n + 1][n + 1];

        // Fill the DP table using the LCS approach
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= n; j++) {
                if (s.charAt(i - 1) == s1.charAt(j - 1)) {
                    dp[i][j] = 1 + dp[i - 1][j - 1];
                }else{
                    dp[i][j] = Math.max(dp[i - 1][j], dp[i][j - 1]);
                }
            }
        }
        return dp[n][n];
    }
}

/*
 * Dry Run
 * --------
 * Input: s = "bbabcbcab"
 * Step 1: Reverse s to get s1 = "bacbcbabb"
 * Step 2: Initialize dp array of size (n+1) x (n+1) with zeros.
 * Step 3: Fill dp table:
 *  - For each i (1 to n) and j (1 to n), if the characters match, update dp[i][j] = 1 + dp[i-1][j-1]; otherwise take the maximum of dp[i-1][j] and dp[i][j-1].
 * Step 4: dp[n][n] holds the length of the longest palindromic subsequence.
 * Output: 7 (The subsequence "babcbab")
 */
