/*
 * Longest Palindrome in a String
 *
 * Given a string s, your task is to find the longest palindromic substring within s.
 * A substring is a contiguous sequence of characters within a string, defined as s[i...j] where 0 ≤ i ≤ j < len(s).
 * A palindrome is a string that reads the same forward and backward. More formally, s is a palindrome if reverse(s) == s.
 * Note: If there are multiple palindromic substrings with the same length, return the first occurrence of the longest palindromic substring from left to right.
 *
 * Examples :
 *
 * Input: s = “forgeeksskeegfor”
 * Output: “geeksskeeg”
 * Explanation: There are several possible palindromic substrings like “kssk”, “ss”, “eeksskee” etc. But the substring “geeksskeeg” is the longest among all.
 *
 * Input: s = “Geeks”
 * Output: “ee”
 * Explanation: "ee" is the longest palindromic substring of "Geeks".
 * Input: s = “abc”
 * Output: “a”
 * Explanation: "a", "b" and "c" are longest palindromic substrings of same length. So, the first occurrence is returned.
 *
 * Constraints:
 * 1 ≤ s.size() ≤ 10^3
 * s consist of only lowercase English letters.
 */

/************************************************************ C++ ************************************************/

// Approach: Dynamic Programming using a 2D dp table to store whether s[i ... j] is a palindrome.
// Time Complexity: O(n^2) - we check all possible substrings.
// Space Complexity: O(n^2) - dp table storage.
class Solution {
public:
    string longestPalindrome(string& s) {
        int n = s.size();
        vector<vector<bool> > dp(n, vector<bool>(n, false));
        int start = 0, maxLen = 1;

        // All substrings of length 1 are palindromes.
        for (int i = 0; i < n; ++i) {
            dp[i][i] = true;
        }

        // Check for substrings of length 2.
        for (int i = 0; i < n - 1; ++i) {
            if (s[i] == s[i + 1]) {
                dp[i][i + 1] = true;
                if (maxLen < 2) {   // update only if first occurrence
                    start  = i;
                    maxLen = 2;
                }
            }
        }

        // Check for substrings of length greater than 2.
        for (int k = 3; k <= n; ++k) {
            for (int i = 0; i <= n - k; ++i) {
                int j = i + k - 1;
                if (dp[i + 1][j - 1] && s[i] == s[j]) {
                    dp[i][j] = true;
                    if (k > maxLen) {   // update only if a longer palindrome is found
                        start  = i;
                        maxLen = k;
                    }
                }
            }
        }

        return s.substr(start, maxLen);
    }
};

/*
 * Dry Run:
 * Input: s = "aaaabbaa"
 * 1. All single characters (e.g., "a") are marked as palindromes.
 * 2. For length 2, substrings like "aa" are detected. The first occurrence at index 0 updates start=0 and maxLen=2.
 * 3. For k>=3, each substring is checked using the dp table. For example, "aaa" and then longer substrings are evaluated.
 * 4. The longest palindrome (e.g., "aabbaa") is identified and returned.
 */

/************************************************************ JAVA ************************************************/

// Approach: Dynamic Programming using a 2D dp array to record if s[i...j] is a palindrome.
// Time Complexity: O(n^2) - we examine all substrings.
// Space Complexity: O(n^2) - dp array storage.
class Solution {
    static String longestPalindrome(String s) {
        int n = s.length();

        boolean[][] dp = new boolean[n][n];
        int start = 0, maxLen = 1;

        // All substrings of length 1 are palindromes.
        for (int i = 0; i < n; i++) {
            dp[i][i] = true;
        }

        // Check for substrings of length 2.
        for (int i = 0; i < n - 1; i++) {
            if (s.charAt(i) == s.charAt(i + 1)) {
                dp[i][i + 1] = true;
                if (maxLen < 2) { // update only if first occurrence
                    start  = i;
                    maxLen = 2;
                }
            }
        }

        // Check for substrings of length greater than 2.
        for (int k = 3; k <= n; k++) {
            for (int i = 0; i <= n - k; i++) {
                int j = i + k - 1;
                if (dp[i + 1][j - 1] && s.charAt(i) == s.charAt(j)) {
                    dp[i][j] = true;
                    if (k > maxLen) { // update only if a longer palindrome is found
                        start  = i;
                        maxLen = k;
                    }
                }
            }
        }

        return s.substring(start, start + maxLen);
    }
}

/*
 * Dry Run:
 * Input: s = "aaaabbaa"
 * 1. Initialize all single characters as palindromes in the dp array.
 * 2. For substrings of length 2, detect palindromes such as "aa" at index 0, then update start and maxLen accordingly.
 * 3. For k>=3, iterate over all possible substrings, update the dp array and record the starting index if a longer palindrome is found.
 * 4. The method returns the longest palindromic substring, e.g., "aabbaa".
 */
