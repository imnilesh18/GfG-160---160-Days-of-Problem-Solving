/*
 * Ways to Reach the n'th Stair
 *
 * There are n stairs, a person standing at the bottom wants to reach the top. The person can climb either 1 stair or 2 stairs at a time. Your task is to count the number of ways, the person can reach the top (order does matter).
 *
 * Examples:
 *
 * Input: n = 1
 * Output: 1
 * Explanation: There is only one way to climb 1 stair.
 *
 * Input: n = 2
 * Output: 2
 * Explanation: There are 2 ways to reach 2th stair: {1, 1} and {2}.
 *
 * Input: n = 4
 * Output: 5
 * Explanation: There are five ways to reach 4th stair: {1, 1, 1, 1}, {1, 1, 2}, {2, 1, 1}, {1, 2, 1} and {2, 2}.
 *
 * Constraints:
 * 1 ≤ n ≤ 44
 */

/************************************************************ C++ ************************************************/

// Approach: Use space-optimized dynamic programming by storing only the last two computed values.
// Time Complexity: O(n) - We iterate from 2 to n.
// Space Complexity: O(1) - Only constant extra space is used.
class Solution {
public:
    int countWays(int n) {
        // Base cases: when n is 0 or 1, there's only 1 way to climb.
        if (n == 0 || n == 1) {
            return 1;
        }
        int prev1 = 1, prev2 = 1;
        for (int i = 2; i <= n; i++) {
            int curr = prev1 + prev2;    // Current number of ways.
            prev2 = prev1;               // Update prev2 to the previous value of prev1.
            prev1 = curr;                // Update prev1 to the current computed ways.
        }
        return prev1;
    }
};

/*
 * Dry Run:
 * For n = 4:
 * - Initialization: prev1 = 1, prev2 = 1.
 * - i = 2: curr = 1 + 1 = 2; then update: prev2 = 1, prev1 = 2.
 * - i = 3: curr = 2 + 1 = 3; then update: prev2 = 2, prev1 = 3.
 * - i = 4: curr = 3 + 2 = 5; then update: prev2 = 3, prev1 = 5.
 * Output: 5
 */

/************************************************************ JAVA ************************************************/

// Approach: Use space-optimized dynamic programming by using two variables to store the last two computed values.
// Time Complexity: O(n) - Loop runs from 2 to n.
// Space Complexity: O(1) - Only constant extra space is required.
class Solution {
    int countWays(int n) {
        // Base cases: if n is 0 or 1, there's only 1 way to climb the stairs.
        if (n == 0 || n == 1) {
            return 1;
        }
        int prev1 = 1, prev2 = 1;
        for (int i = 2; i <= n; i++) {
            int curr = prev1 + prev2;  // Current number of ways to reach the i-th stair.
            prev2 = prev1;             // Update prev2 to the previous count.
            prev1 = curr;              // Update prev1 to the current computed count.
        }
        return prev1;
    }
}

/*
 * Dry Run:
 * For n = 4:
 * - Start: prev1 = 1, prev2 = 1.
 * - For i = 2: curr = 1 + 1 = 2; update: prev2 = 1, prev1 = 2.
 * - For i = 3: curr = 2 + 1 = 3; update: prev2 = 2, prev1 = 3.
 * - For i = 4: curr = 3 + 2 = 5; update: prev2 = 3, prev1 = 5.
 * Output: 5
 */
