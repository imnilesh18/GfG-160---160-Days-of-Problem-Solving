/*
 * Stickler Thief
 *
 * Stickler the thief wants to loot money from the houses arranged in a line. He cannot loot two consecutive houses and aims to maximize his total loot.
 * Given an array, arr[] where arr[i] represents the amount of money in the i-th house.
 * Determine the maximum amount he can loot.
 *
 * Examples:
 *
 * Input: arr[] = [6, 5, 5, 7, 4]
 * Output: 15
 * Explanation: Maximum amount he can get by looting 1st, 3rd and 5th house. Which is 6 + 5 + 4 = 15.
 *
 * Input: arr[] = [1, 5, 3]
 * Output: 5
 * Explanation: Loot only 2nd house and get maximum amount of 5.
 *
 * Input: arr[] = [4, 4, 4, 4]
 * Output: 8
 * Explanation: The optimal choice is to loot every alternate house. Looting the 1st and 3rd houses, or the 2nd and 4th, both give a maximum total of 4 + 4 = 8.
 *
 * Constraints:
 * 1 ≤ arr.size() ≤ 10^5
 * 1 ≤ arr[i] ≤ 10^4
 */

/************************************************************ C++ ************************************************/

// Approach (My Approach): Use recursion with memoization (top-down DP) to decide at each house whether to loot it (and then skip the next) or skip it.
// Time Complexity: O(n) because each index is processed once due to memoization.
// Space Complexity: O(n) due to the recursion stack and memoization array.
class Solution {
public:
    int t[100001];    // memoization array to store results for each index

    int solve(vector<int>& arr, int idx) {
        if (idx >= arr.size()) {
            return 0;
        }

        if (t[idx] != -1) {    // if already computed, return the stored result
            return t[idx];
        }

        int take = arr[idx] + solve(arr, idx + 2); // option to loot current house and then move two houses ahead
        int skip = solve(arr, idx + 1);            // option to skip current house and move to the next

        return t[idx] = max(take, skip);           // memoize and return the maximum loot from index idx
    }
    
    int findMaxSum(vector<int>& arr) {
        memset(t, -1, sizeof(t));    // initialize memoization array with -1
        return solve(arr, 0);
    }
};

/*
 * Dry Run:
 * Consider arr = [6, 5, 5, 7, 4]
 * - solve(arr, 0):
 *  take = 6 + solve(arr, 2)
 *  skip = solve(arr, 1)
 * - solve(arr, 2):
 *  take = 5 + solve(arr, 4)
 *  skip = solve(arr, 3)
 * - solve(arr, 4): returns 4 (base case: 4 + solve(arr, 6) where solve(arr,6) returns 0)
 * - solve(arr, 3): returns 7 (7 + solve(arr, 5) where solve(arr,5) returns 0)
 * - Thus, solve(arr,2) = max(5+4, 7) = max(9, 7) = 9
 * - solve(arr, 1):
 *  take = 5 + solve(arr, 3) = 5 + 7 = 12
 *  skip = solve(arr, 2) = 9
 * - Thus, solve(arr,1) = max(12, 9) = 12
 * - Finally, solve(arr, 0) = max(6 + 9, 12) = max(15, 12) = 15
 */

/************************************************************ JAVA ************************************************/

// Approach (My Approach): Use recursion with memoization (top-down DP) to decide at each house whether to loot it (and then skip the next) or skip it.
// Time Complexity: O(n) because each index is processed once due to memoization.
// Space Complexity: O(n) due to the recursion stack and memoization array.
class Solution {
    int[] t = new int[100001];  // memoization array to store results for each index

    int solve(int[] arr, int idx) {
        if (idx >= arr.length) {
            return 0;
        }

        if (t[idx] != -1) {  // if already computed, return the stored result
            return t[idx];
        }

        int take = arr[idx] + solve(arr, idx + 2); // option to loot current house and then move two houses ahead
        int skip = solve(arr, idx + 1);            // option to skip current house and move to the next

        return t[idx] = Math.max(take, skip);      // memoize and return the maximum loot from index idx
    }

    public int findMaxSum(int arr[]) {
        Arrays.fill(t, -1);  // initialize memoization array with -1
        return solve(arr, 0);
    }
}

/*
 * Dry Run:
 * Consider arr = [6, 5, 5, 7, 4]
 * - solve(arr, 0):
 *  take = 6 + solve(arr, 2)
 *  skip = solve(arr, 1)
 * - solve(arr, 2):
 *  take = 5 + solve(arr, 4)
 *  skip = solve(arr, 3)
 * - solve(arr, 4): returns 4 (base case: 4 + solve(arr, 6) where solve(arr,6) returns 0)
 * - solve(arr, 3): returns 7 (7 + solve(arr, 5) where solve(arr,5) returns 0)
 * - Thus, solve(arr,2) = Math.max(5+4, 7) = Math.max(9, 7) = 9
 * - solve(arr, 1):
 *  take = 5 + solve(arr, 3) = 5 + 7 = 12
 *  skip = solve(arr, 2) = 9
 * - Thus, solve(arr,1) = Math.max(12, 9) = 12
 * - Finally, solve(arr, 0) = Math.max(6 + 9, 12) = Math.max(15, 12) = 15
 */
