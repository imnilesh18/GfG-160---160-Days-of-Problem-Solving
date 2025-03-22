/*
 * Total Decoding Messages
 *
 * A message containing letters A-Z is being encoded to numbers using the following mapping:
 *
 * 'A' -> 1
 * 'B' -> 2
 * ...
 * 'Z' -> 26
 *
 * You are given a string digits. You have to determine the total number of ways that message can be decoded.
 *
 * Examples:
 *
 * Input: digits = "123"
 * Output: 3
 * Explanation: "123" can be decoded as "ABC"(1, 2, 3), "LC"(12, 3) and "AW"(1, 23).
 *
 * Input: digits = "90"
 * Output: 0
 * Explanation: "90" cannot be decoded, as it's an invalid string and we cannot decode '0'.
 *
 * Input: digits = "05"
 * Output: 0
 * Explanation: "05" cannot be mapped to "E" because of the leading zero ("5" is different from "05"), the string is not a valid encoding message.
 *
 * Constraints:
 * 1 ≤ digits.size() ≤ 10^3
 */

/************************************************************ C++ ************************************************/

// Approach 1 (Recursion with Memoization): This code uses recursion with memoization (top-down dynamic programming). The function 'solve' recursively calculates the number of ways to decode the substring starting at index i and stores the results in the memoization array t to avoid recomputation.
// Time Complexity: O(n) - Each index is computed once where n is the length of the input string.
// Space Complexity: O(n) - Due to the recursion call stack and the memoization array.
class Solution {
public:
    int t[1001]; // Memoization array to store results for subproblems

    int solve(int i, string& s, int n) {
        // If result is already computed for index i, return it
        if (t[i] != -1) {
            return t[i];
        }
        // If reached the end of the string, it is a valid decoding
        if (i == n) {
            return t[i] = 1;
        }

        // If the current digit is '0', it cannot be decoded
        if (s[i] == '0') {
            return t[i] = 0;
        }

        // Decode using one digit
        int result = solve(i + 1, s, n);

        // Check if two digits form a valid number (10 to 26)
        if (i + 1 < n) {
            if (s[i] == '1' || (s[i] == '2' && s[i + 1] <= '6')) {
                result += solve(i + 2, s, n);
            }
        }

        // Store the computed result in the memoization array and return it
        return t[i] = result;
    }

    int countWays(string& digits) {
        int n = digits.length();

        memset(t, -1, sizeof(t)); // Initialize the memoization array with -1
        return solve(0, digits, n);
    }
};

/*
 * Dry Run
 * Example: digits = "123"
 * n = 3
 * Call: solve(0, "123", 3)
 * s[0] = '1', not '0'
 * -> result = solve(1, "123", 3)
 *     Call: solve(1, "123", 3)
 *        s[1] = '2', not '0'
 *        -> result = solve(2, "123", 3)
 *            Call: solve(2, "123", 3)
 *               s[2] = '3', not '0'
 *               -> result = solve(3, "123", 3)
 *                   Call: solve(3, "123", 3)
 *                      i == n so return 1.
 *               Back to solve(2): result = 1, no valid two-digit check because i+1 == 3.
 *               Returns 1.
 *        Back to solve(1): result = 1, then check two-digit possibility: s[1]='2' and s[2]='3' form "23" which is valid.
 *                   -> result += solve(3, "123", 3) returns 1.
 *        Sum = 1 + 1 = 2, return 2.
 * Back to solve(0): result = 2, then check two-digit possibility: s[0]='1' and s[1]='2' form "12" which is valid.
 *              -> result += solve(2, "123", 3) returns 1.
 * Sum = 2 + 1 = 3, return 3.
 * Final countWays returns 3.
 */

// Approach 2 (Bottom Up): Iterative dynamic programming (bottom-up) where we fill a dp array 't' from right to left with the number of ways to decode the substring starting at each index.
// Time Complexity: O(n) - We traverse the string once, where n is the length of the input string.
// Space Complexity: O(n) - We use an extra vector of size n+1 to store the number of decoding ways.
class Solution {
public:
    int countWays(string& s) {
        int         n = s.length();
        vector<int> t(n + 1, 0); // t[i] = ways to decode string s from index i to n

        t[n] = 1;                // Base case: An empty substring has one valid decoding

        for (int i = n - 1; i >= 0; i--) {
            if (s[i] == '0') {
                t[i] = 0;        // '0' cannot be decoded into any letter
            } else {
                t[i] = t[i + 1]; // Decode s[i] as a single digit

                if (i + 1 < n) {
                    // Check if s[i] and s[i+1] form a valid two-digit number (10 to 26)
                    if (s[i] == '1' || (s[i] == '2' && s[i + 1] <= '6')) {
                        t[i] += t[i + 2];
                    }
                }
            }
        }
        return t[0]; // Number of ways to decode the entire string
    }
};

/*
 * Dry Run
 * Example: s = "123"
 * n = 3
 * Initialization: t = [0, 0, 0, 1]
 *
 * Iteration:
 * i = 2, s[2] = '3' (not '0'), so:
 *  t[2] = t[3] = 1
 *  (No two-digit possibility since i+1 == n)
 *  t becomes [0, 0, 1, 1]
 *
 * i = 1, s[1] = '2' (not '0'), so:
 *  t[1] = t[2] = 1
 *  Check two-digit: s[1]='2' and s[2]='3' form "23" which is valid:
 *  t[1] += t[3] (1) => t[1] becomes 2
 *  t becomes [0, 2, 1, 1]
 *
 * i = 0, s[0] = '1' (not '0'), so:
 *  t[0] = t[1] = 2
 *  Check two-digit: s[0]='1' and s[1]='2' form "12" which is valid:
 *  t[0] += t[2] (1) => t[0] becomes 3
 *  t becomes [3, 2, 1, 1]
 *
 * Return t[0] = 3.
 */

/************************************************************ JAVA ************************************************/

// Approach 1 (Recursion with Memoization): This code uses recursion with memoization (top-down dynamic programming). The function 'solve' recursively calculates the number of ways to decode the substring starting at index i and stores the results in the memoization array t to avoid recomputation.
// Time Complexity: O(n) - Each index is computed once where n is the length of the input string.
// Space Complexity: O(n) - Due to the recursion call stack and the memoization array.
class Solution {
    int[] t = new int[1001]; // Memoization array to store results for subproblems

    public int solve(int i, String s, int n) {
        // If result is already computed for index i, return it
        if (t[i] != -1) {
            return t[i];
        }
        // If reached the end of the string, it is a valid decoding
        if (i == n) {
            return t[i] = 1;
        }

        // If the current digit is '0', it cannot be decoded
        if (s.charAt(i) == '0') {
            return t[i] = 0;
        }

        // Decode using one digit
        int result = solve(i + 1, s, n);

        // Check if two digits form a valid number (10 to 26)
        if (i + 1 < n) {
            if (s.charAt(i) == '1' || (s.charAt(i) == '2' && s.charAt(i + 1) <= '6')) {
                result += solve(i + 2, s, n);
            }
        }

        // Store the computed result in the memoization array and return it
        return t[i] = result;
    }
    
    public int countWays(String digits) {
        int n = digits.length();

        Arrays.fill(t, -1); // Initialize the memoization array with -1
        return solve(0, digits, n);
    }
}

/*
 * Dry Run
 * Example: digits = "123"
 * n = 3
 * Call: solve(0, "123", 3)
 * s.charAt(0) = '1', not '0'
 * -> result = solve(1, "123", 3)
 *     Call: solve(1, "123", 3)
 *        s.charAt(1) = '2', not '0'
 *        -> result = solve(2, "123", 3)
 *            Call: solve(2, "123", 3)
 *               s.charAt(2) = '3', not '0'
 *               -> result = solve(3, "123", 3)
 *                   Call: solve(3, "123", 3)
 *                      i == n so return 1.
 *               Back to solve(2): result = 1, no valid two-digit check because i+1 == 3.
 *               Returns 1.
 *        Back to solve(1): result = 1, then check two-digit possibility: s.charAt(1)='2' and s.charAt(2)='3' form "23" which is valid.
 *                   -> result += solve(3, "123", 3) returns 1.
 *        Sum = 1 + 1 = 2, return 2.
 * Back to solve(0): result = 2, then check two-digit possibility: s.charAt(0)='1' and s.charAt(1)='2' form "12" which is valid.
 *              -> result += solve(2, "123", 3) returns 1.
 * Sum = 2 + 1 = 3, return 3.
 * Final countWays returns 3.
 */

// Approach 2 (Bottom Up): Iterative dynamic programming (bottom-up) where we fill a dp array 't' from right to left with the number of ways to decode the substring starting at each index.
// Time Complexity: O(n) - We traverse the string once, where n is the length of the input string.
// Space Complexity: O(n) - We use an extra array of size n+1 to store the number of decoding ways.
class Solution {
    public int countWays(String s) {
        int n = s.length();
        int[] t = new int[n + 1]; // t[i] = ways to decode string s from index i to n

        t[n] = 1;                 // Base case: An empty substring has one valid decoding

        for (int i = n - 1; i >= 0; i--) {
            if (s.charAt(i) == '0') {
                t[i] = 0;        // '0' cannot be decoded into any letter
            } else {
                t[i] = t[i + 1]; // Decode s.charAt(i) as a single digit
                if (i + 1 < n) {
                    // Check if s.charAt(i) and s.charAt(i+1) form a valid two-digit number (10 to 26)
                    if (s.charAt(i) == '1' || (s.charAt(i) == '2' && s.charAt(i + 1) <= '6')) {
                        t[i] += t[i + 2];
                    }
                }
            }
        }
        return t[0]; // Number of ways to decode the entire string
    }
}

/*
 * Dry Run
 * Example: s = "123"
 * n = 3
 * Initialization: t = [0, 0, 0, 1]
 *
 * Iteration:
 * i = 2, s.charAt(2) = '3' (not '0'), so:
 *  t[2] = t[3] = 1
 *  (No two-digit possibility since i+1 == n)
 *  t becomes [0, 0, 1, 1]
 *
 * i = 1, s.charAt(1) = '2' (not '0'), so:
 *  t[1] = t[2] = 1
 *  Check two-digit: s.charAt(1)='2' and s.charAt(2)='3' form "23" which is valid:
 *  t[1] += t[3] (1) => t[1] becomes 2
 *  t becomes [0, 2, 1, 1]
 *
 * i = 0, s.charAt(0) = '1' (not '0'), so:
 *  t[0] = t[1] = 2
 *  Check two-digit: s.charAt(0)='1' and s.charAt(1)='2' form "12" which is valid:
 *  t[0] += t[2] (1) => t[0] becomes 3
 *  t becomes [3, 2, 1, 1]
 *
 * Return t[0] = 3.
 */
