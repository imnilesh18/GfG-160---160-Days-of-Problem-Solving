/*
 * Minimum Jumps
 *
 * You are given an array arr[] of non-negative numbers. Each number tells you the maximum number of steps you can jump forward from that position.
 *
 * For example:
 *
 * If arr[i] = 3, you can jump to index i + 1, i + 2, or i + 3 from position i.
 * If arr[i] = 0, you cannot jump forward from that position.
 * Your task is to find the minimum number of jumps needed to move from the first position in the array to the last position.
 *
 * Note:  Return -1 if you can't reach the end of the array.
 *
 * Examples :
 *
 * Input: arr[] = [1, 3, 5, 8, 9, 2, 6, 7, 6, 8, 9]
 * Output: 3
 * Explanation: First jump from 1st element to 2nd element with value 3. From here we jump to 5th element with value 9, and from here we will jump to the last.
 *
 * Input: arr = [1, 4, 3, 2, 6, 7]
 * Output: 2
 * Explanation: First we jump from the 1st to 2nd element and then jump to the last element.
 *
 * Input: arr = [0, 10, 20]
 * Output: -1
 * Explanation: We cannot go anywhere from the 1st element.
 *
 * Constraints:
 * 2 ≤ arr.size() ≤ 10^4
 * 0 ≤ arr[i] ≤ 10^4
 */

/************************************************************ C++ ************************************************/

// Approach (My Approach): Use recursion with memoization to explore each jump from the current index and cache results to avoid recomputation.
// Time Complexity: O(n^2) in the worst-case scenario, as each index may explore up to arr[idx] jumps.
// Space Complexity: O(n) due to the memoization array and recursion call stack.
class Solution {
public:
    // Recursive function to compute minimum jumps from index 'idx' to the end
    int solve(vector<int>& arr, int n, int idx, vector<int>& dp) {
        // Base case: If we're at the last index, no more jumps are needed.
        if (idx == n - 1) {
            return 0;
        }
        // If out of bounds or no jump can be made, return a large number.
        if (idx >= n || arr[idx] == 0) {
            return INT_MAX;
        }
        // Return cached result if available.
        if (dp[idx] != -1) {
            return dp[idx];
        }

        int minJump = INT_MAX;
        // Try all possible jump lengths from 1 to arr[idx]
        for (int i = 1; i <= arr[idx]; i++) {
            int res = solve(arr, n, idx + i, dp);     // 'res' = minimum jumps from index (idx + i) to end
            if (res != INT_MAX) {                     // Only consider valid paths
                minJump = min(minJump, 1 + res);      // Candidate = 1 (for current jump) + res (jumps from next index)
            }
        }

        dp[idx] = minJump;     // Cache the computed minimum jumps for index 'idx'
        return dp[idx];
    }
    // Function to calculate minimum jumps to reach the end of the array
    int minJumps(vector<int>& arr) {
        int         n = arr.size();
        vector<int> dp(n, -1);                  // Memoization array initialized with -1
        int         ans = solve(arr, n, 0, dp);

        return ans == INT_MAX ? -1 : ans;     // If unreachable, return -1
    }
};

/*
 * Dry Run
 * ---------
 * Consider a simpler input: arr = [2, 3, 1, 1, 4] with n = 5
 *
 * Step 1: Call solve(arr, 5, 0, dp) at idx = 0, arr[0] = 2
 *  - Possible jumps from idx 0: jump of 1 (to idx 1) and jump of 2 (to idx 2)
 *
 * Step 2: For jump of 1 from idx 0:
 *  Call solve(arr, 5, 1, dp) at idx = 1, arr[1] = 3
 *  - Possible jumps from idx 1: jump of 1 (to idx 2), jump of 2 (to idx 3), and jump of 3 (to idx 4)
 *
 * Step 3: At idx 1:
 *  a) For jump of 1 from idx 1:
 *       Call solve(arr, 5, 2, dp) at idx = 2, arr[2] = 1
 *       - Only jump from idx 2: jump of 1 (to idx 3)
 *
 *       Call solve(arr, 5, 3, dp) at idx = 3, arr[3] = 1
 *       - Only jump from idx 3: jump of 1 (to idx 4)
 *
 *       Call solve(arr, 5, 4, dp) at idx = 4 → Base case reached, returns 0.
 *       Back at idx 3: Candidate = 1 + 0 = 1, so solve(arr, 5, 3, dp) returns 1.
 *       Back at idx 2: Candidate = 1 + 1 = 2, so solve(arr, 5, 2, dp) returns 2.
 *
 *  b) For jump of 2 from idx 1:
 *       Call solve(arr, 5, 3, dp) at idx = 3, returns 1 (as computed above).
 *       Candidate = 1 + 1 = 2.
 *
 *  c) For jump of 3 from idx 1:
 *       Call solve(arr, 5, 4, dp) at idx = 4 → Base case, returns 0.
 *       Candidate = 1 + 0 = 1.
 *
 *  - At idx 1, the minimum candidate = min(3, 2, 1) = 1, so solve(arr, 5, 1, dp) returns 1.
 *
 * Step 4: For jump of 2 from idx 0:
 *  Call solve(arr, 5, 2, dp) at idx = 2, which returns 2 (as computed above).
 *  Candidate = 1 + 2 = 3.
 *
 * Step 5: At idx 0, the minimum candidate = min( (1 + solve(idx 1)= 1+1 =2), (1 + solve(idx 2)= 1+2 =3) ) = 2.
 *  Thus, solve(arr, 5, 0, dp) returns 2.
 *
 * Final Answer: 2 jumps are required to reach the end of the array.
 */

/************************************************************ JAVA ************************************************/

// Approach (My Approach): Use recursion with memoization to explore all possible jump paths and cache results to avoid redundant computations.
// Time Complexity: O(n^2) in the worst-case scenario, as each index may try up to arr[idx] jumps.
// Space Complexity: O(n) due to the recursion call stack and the dp array.
class Solution {
    static int solve(int[] arr, int n, int idx, int[] dp) {
        if (idx == n - 1) { // Base case: reached the last index, no more jumps needed.
            return 0;
        }
        if (idx >= n || arr[idx] == 0) { // If index is out of bounds or no jump can be made from this index.
            return Integer.MAX_VALUE;
        }
        if (dp[idx] != -1) { // If the result for this index is already computed, return it.
            return dp[idx];
        }

        int minJump = Integer.MAX_VALUE;              // Initialize minJump to a very high value.
        for (int i = 1; i <= arr[idx]; i++) {         // Try all possible jump lengths from the current index.
            int res = solve(arr, n, idx + i, dp);     // res: minimum jumps needed from index (idx + i) to the end.
            if (res != Integer.MAX_VALUE) {           // Only consider the candidate if the path is valid.
                minJump = Math.min(minJump, 1 + res); // Update minJump with candidate: 1 (for the current jump) + res.
            }
        }

        return dp[idx] = minJump; // Cache the computed minimum jumps for the current index.
    }
    static int minJumps(int[] arr) {
        int n = arr.length;    // Get the size of the array.
        int[] dp = new int[n]; // Create a dp array for memoization.

        for (int i = 0; i < n; i++) {
            dp[i] = -1;                             // Initialize the dp array with -1.
        }
        int ans = solve(arr, n, 0, dp);             // Compute the minimum jumps starting from index 0.
        return ans == Integer.MAX_VALUE ? -1 : ans; // If the end is unreachable, return -1; otherwise, return the answer.
    }
}

/*
 * Dry Run
 * ---------
 * For arr = [2, 3, 1, 1, 4] with n = 5:
 *
 * 1. Call solve(arr, 5, 0, dp) at idx=0, arr[0]=2:
 * - Possible jumps from idx 0: jump of 1 (to idx 1) and jump of 2 (to idx 2).
 *
 * 2. For jump of 1 from idx 0:
 * - Call solve(arr, 5, 1, dp) at idx=1, arr[1]=3.
 *   - Possible jumps from idx 1: jump of 1 (to idx 2), jump of 2 (to idx 3), jump of 3 (to idx 4).
 *
 *   a) For jump of 1 from idx 1:
 *      - Call solve(arr, 5, 2, dp) at idx=2, arr[2]=1.
 *        - Only jump from idx 2: jump of 1 (to idx 3).
 *        - Call solve(arr, 5, 3, dp) at idx=3, arr[3]=1.
 *          - Only jump from idx 3: jump of 1 (to idx 4).
 *          - Call solve(arr, 5, 4, dp) at idx=4 → Base case reached, returns 0.
 *        - Candidate at idx=3 = 1 + 0 = 1; solve(arr, 5, 3, dp) returns 1.
 *      - Candidate at idx=2 = 1 + 1 = 2; solve(arr, 5, 2, dp) returns 2.
 *
 *   b) For jump of 2 from idx 1:
 *      - Call solve(arr, 5, 3, dp) at idx=3, returns 1.
 *      - Candidate = 1 + 1 = 2.
 *
 *   c) For jump of 3 from idx 1:
 *      - Call solve(arr, 5, 4, dp) at idx=4 → Base case, returns 0.
 *      - Candidate = 1 + 0 = 1.
 *
 *   - At idx=1, the minimum candidate = min(3, 2, 1) = 1; solve(arr, 5, 1, dp) returns 1.
 *
 * 3. For jump of 2 from idx 0:
 * - Call solve(arr, 5, 2, dp) at idx=2, returns 2.
 * - Candidate = 1 + 2 = 3.
 *
 * 4. At idx=0, the minimum candidate = min( (1 + solve(1)= 1+1 =2), (1 + solve(2)= 1+2 =3) ) = 2; solve(arr, 5, 0, dp) returns 2.
 *
 * Final Answer: 2 jumps are required to reach the end.
 */
