/*
 * Unique Number II
 *
 * Difficulty: Medium Accuracy: 36.9% Submissions: 154K+ Points: 4 Average Time: 15m
 *
 * Given an array arr[] containing 2*n + 2 positive numbers, out of which 2*n numbers exist in pairs whereas the other two number occur exactly once and are distinct. Find the other two numbers. Return the answer in increasing order.
 *
 * Examples:
 *
 * Input: arr[] = [1, 2, 3, 2, 1, 4]
 * Output: [3, 4]
 * Explanation: 3 and 4 occur exactly once.
 *
 * Input: arr[] = [2, 1, 3, 2]
 * Output: [1, 3]
 * Explanation: 1 and 3 occur exactly once.
 *
 * Input: arr[] = [2, 1, 3, 3]
 * Output: [1, 2]
 * Explanation: 1 and 2 occur exactly once.
 *
 * Constraints:
 * 2 ≤ arr.size() ≤ 10^6
 * 1 ≤ arr[i] ≤ 5 * 10^6
 * arr.size() is even
 */

// Intuition:

/*
 * In the given array, every number appears **twice** except for **two unique numbers** that appear **only once**.
 * If we XOR all the elements together, the result will be `x ^ y`, where x and y are the two unique numbers.
 * Why? Because `a ^ a = 0` for any number `a`, and `0 ^ x = x`.
 *
 * Example: arr = [2, 4, 7, 9, 2, 4]
 * XOR all elements:
 * => 2 ^ 4 = 6
 * => 6 ^ 7 = 1
 * => 1 ^ 9 = 8
 * => 8 ^ 2 = 10
 * => 10 ^ 4 = 14 => Final XOR = 14 = x ^ y (i.e., 7 ^ 9 = 14)
 *
 * Now, we know that 14 is the XOR of the two unique numbers, but we don’t know which ones.
 * So, we find the **rightmost set bit** of the XOR result (bit where x and y differ). For 14 (1110), the rightmost set bit is at position 2.
 * We use this bit to divide the numbers into **two groups**:
 * - One group where this bit is **set**.
 * - One group where this bit is **not set**.
 *
 * Why does this help? Because x and y differ at this bit, so they will end up in **different groups**.
 * Then, we XOR elements in each group separately. All duplicate numbers cancel out, and we are left with x and y.
 *
 * Example continued:
 * Rightmost set bit of 14 = 2 (binary 0010)
 * Group 1 (bit set): [2, 7, 2] => 2 ^ 7 ^ 2 = 7
 * Group 2 (bit not set): [4, 9, 4] => 4 ^ 9 ^ 4 = 9
 * Final result: [7, 9]
 *
 */

/************************************************************ C++ ************************************************/

// Approach: Use XOR to eliminate all paired elements, then use the rightmost set bit to separate the two unique elements
// Time Complexity: O(n) - We traverse the array a constant number of times (3 times overall).
// Space Complexity: O(1) - We use only constant extra space, excluding the output vector.
class Solution {
public:
    vector<int> singleNum(vector<int>& arr) {
        // Get the XOR of the two numbers we need to find
        int xorVal = 0;

        for (auto i : arr) {
            xorVal ^= i;   // XOR all elements, paired ones cancel out
        }

        // Get the rightmost set bit (a bit where x and y differ)
        xorVal &= -xorVal;

        vector<int> res(2, 0);

        for (int num : arr) {
            // If the bit is not set, XOR with first result
            if ((num & xorVal) == 0) {
                res[0] ^= num;
            }
            // If the bit is set, XOR with second result
            else {
                res[1] ^= num;
            }
        }

        // Ensure the result is in increasing order
        if (res[0] > res[1]) {
            swap(res[0], res[1]);
        }

        return res;
    }
};

/*
 *
 * Dry Run
 *
 * Input: arr = [2, 4, 7, 9, 2, 4]
 *
 * Step 1: XOR all elements
 * 2 ^ 4 = 6
 * 6 ^ 7 = 1
 * 1 ^ 9 = 8
 * 8 ^ 2 = 10
 * 10 ^ 4 = 14 => xorVal = 14
 *
 * Step 2: Find rightmost set bit in 14 (1110) => 14 & (-14) = 2 (0010)
 *
 * Step 3: Partition into two groups using bit 2:
 * Group 1 (bit not set at position 2): [4, 9, 4]
 * Group 2 (bit set at position 2): [2, 7, 2]
 *
 * Group 1 XOR: 4 ^ 9 ^ 4 = 9
 * Group 2 XOR: 2 ^ 7 ^ 2 = 7
 *
 * Output (sorted): [7, 9]
 *
 */

/************************************************************ JAVA ************************************************/

// Approach: Use XOR to eliminate all paired elements, then use the rightmost set bit to differentiate the two unique elements
// Time Complexity: O(n) - Only a few linear passes over the array
// Space Complexity: O(1) - Constant extra space used for calculations
class Solution {
    public int[] singleNum(int[] arr) {
        // Step 1: Get the XOR of the two unique numbers
        int xorVal = 0;

        for (int i : arr) {
            xorVal ^= i; // Paired numbers cancel out, result is x ^ y
        }

        // Step 2: Get the rightmost set bit in xorVal
        xorVal &= -xorVal; // Isolates the lowest set bit (bit where x and y differ)

        // Step 3: Divide numbers into two groups and XOR them separately
        int[] res = new int[2];
        for (int num : arr) {
            if ((num & xorVal) == 0) {
                // Bit is not set => belongs to one group
                res[0] ^= num;
            } else {
                // Bit is set => belongs to another group
                res[1] ^= num;
            }
        }

        // Step 4: Ensure result is in ascending order
        if (res[0] > res[1]) {
            int temp = res[0];
            res[0] = res[1];
            res[1] = temp;
        }

        return res;
    }
}

/*
 *
 * Dry Run
 *
 * Input: arr = [2, 4, 7, 9, 2, 4]
 *
 * Step 1: XOR all elements
 * 2 ^ 4 = 6
 * 6 ^ 7 = 1
 * 1 ^ 9 = 8
 * 8 ^ 2 = 10
 * 10 ^ 4 = 14
 * => Final XOR = 14 (binary: 1110) = x ^ y (i.e., 7 ^ 9 = 14)
 *
 * Step 2: Find rightmost set bit of 14
 * 14 & -14 = 2 (binary: 0010)
 *
 * Step 3: Divide into two groups using bit 2:
 * Group 1 (bit not set): [4, 9, 4] => 4 ^ 9 ^ 4 = 9
 * Group 2 (bit set): [2, 7, 2] => 2 ^ 7 ^ 2 = 7
 *
 * Step 4: Return [7, 9] in sorted order => [7, 9]
 *
 */
