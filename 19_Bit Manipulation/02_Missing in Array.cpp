/*
 * Missing in Array
 *
 * Difficulty: Easy Accuracy: 29.59% Submissions: 1.4M Points: 2 verage Time: 15m
 *
 * You are given an array arr[] of size n - 1 that contains distinct integers in the range from 1 to n (inclusive). This array represents a permutation of the integers from 1 to n with one element missing. Your task is to identify and return the missing element.
 *
 * Examples:
 *
 * Input: arr[] = [1, 2, 3, 5]
 * Output: 4
 * Explanation: All the numbers from 1 to 5 are present except 4.
 *
 * Input: arr[] = [8, 2, 4, 5, 3, 7, 1]
 * Output: 6
 * Explanation: All the numbers from 1 to 8 are present except 6.
 *
 * Input: arr[] = [1]
 * Output: 2
 * Explanation: Only 1 is present so the missing element is 2.
 *
 * Constraints:
 * 1 ≤ arr.size() ≤ 10^6
 * 1 ≤ arr[i] ≤ arr.size() + 1
 */

// Intuition:

// We leverage XOR properties where x ^ x = 0 and x ^ 0 = x, so pairing all numbers 1..n with the array elements cancels out present numbers, leaving only the missing one. :contentReference[oaicite:0]{index=0}
// Example:
//   arr = [1, 2, 3, 5], n = 5
//   xor_all = 1 ^ 2 ^ 3 ^ 4 ^ 5 = 1        // XOR of full range 1..n :contentReference[oaicite:1]{index=1}
//   xor_arr = 1 ^ 2 ^ 3 ^ 5     = 5        // XOR of array elements :contentReference[oaicite:2]{index=2}
//   missing = xor_all ^ xor_arr = 1 ^ 5   = 4

/************************************************************ C++ ************************************************/

// Approach: Compute XOR of all numbers from 1 to n and XOR of array elements; the XOR of these two results gives the missing number.
// Time Complexity: O(n) – one loop to XOR the array and one loop to XOR 1..n.
// Space Complexity: O(1) – uses only a few integer variables.
class Solution {
public:
    int missingNum(vector<int>& arr) {
        int n = arr.size() + 1;      // Full range is 1..n when array has n–1 elements
        int xor1 = 0, xor2 = 0;      // xor1 will hold XOR of 1..n; xor2 holds XOR of array

        // XOR all array elements
        for (int i = 0; i < n - 1; i++) {
            xor2 ^= arr[i];
        }

        // XOR all numbers from 1 to n
        for (int i = 1; i <= n; i++) {
            xor1 ^= i;
        }

        // The missing number is the XOR of these two results
        return xor1 ^ xor2;
    }
};

/*
 *
 * Dry Run
 *
 * Example: arr = [1, 2, 3, 5]
 * n = arr.size() + 1 = 4 + 1 = 5
 *
 * Step 1: XOR array elements
 *   xor2 = 1 ^ 2 ^ 3 ^ 5
 *        = ((1 ^ 2) ^ 3) ^ 5
 *        = (3 ^ 3) ^ 5
 *        = 0 ^ 5
 *        = 5
 *
 * Step 2: XOR numbers 1 to n
 *   xor1 = 1 ^ 2 ^ 3 ^ 4 ^ 5
 *        = (((1 ^ 2) ^ 3) ^ 4) ^ 5
 *        = ((3 ^ 3) ^ 4) ^ 5
 *        = (0 ^ 4) ^ 5
 *        = 4 ^ 5
 *        = 1
 *
 * Step 3: Missing number = xor1 ^ xor2 = 1 ^ 5 = 4
 *
 */

/************************************************************ JAVA ************************************************/

// Approach: Compute XOR of all numbers from 1 to n and XOR of array elements; the XOR of these two results is the missing number.
// Time Complexity: O(n) – one pass to XOR the array and one pass for numbers 1 through n.
// Space Complexity: O(1) – uses only constant extra space.
class Solution {
    public int missingNum(int[] arr) {
        int n = arr.length + 1;    // Array has n–1 elements, so full range is 1..n
        int xor1 = 0, xor2 = 0;    // xor1 for 1..n, xor2 for array elements

        // XOR all array elements
        for (int i = 0; i < arr.length; i++) {
            xor2 ^= arr[i];       // accumulate XOR of arr[i]
        }

        // XOR all numbers from 1 to n
        for (int i = 1; i <= n; i++) {
            xor1 ^= i;            // accumulate XOR of i
        }

        // Missing number is xor1 ^ xor2
        return xor1 ^ xor2;
    }
}

/*
 *
 * Dry Run
 *
 * Example: arr = [1, 2, 3, 5]
 * n = arr.length + 1 = 4 + 1 = 5
 *
 * Step 1: XOR array elements
 *   xor2 = 1 ^ 2 ^ 3 ^ 5
 *        = (1 ^ 2) = 3
 *        = (3 ^ 3) = 0
 *        = (0 ^ 5) = 5
 *
 * Step 2: XOR numbers 1 to n
 *   xor1 = 1 ^ 2 ^ 3 ^ 4 ^ 5
 *        = (1 ^ 2) = 3
 *        = (3 ^ 3) = 0
 *        = (0 ^ 4) = 4
 *        = (4 ^ 5) = 1
 *
 * Step 3: Missing number = xor1 ^ xor2 = 1 ^ 5 = 4
 *
 */
