/*
 * Find Only Repetitive Element from 1 to n-1
 *
 * Difficulty: Easy Accuracy: 63.0% Submissions: 10K+ Points: 2
 *
 * Given an array arr[] of size n, filled with numbers from 1 to n-1 in random order. The array has only one repetitive element. Your task is to find the repetitive element.
 *
 * Note: It is guaranteed that there is a repeating element present in the array.
 *
 * Examples:
 *
 * Input: arr[] = [1, 3, 2, 3, 4]
 * Output: 3
 * Explanation: The number 3 is the only repeating element.
 *
 * Input: arr[] = [1, 5, 1, 2, 3, 4]
 * Output: 1
 * Explanation: The number 1 is the only repeating element.
 *
 * Input: arr[] = [1, 1]
 * Output: 1
 * Explanation: The array is of size 2 with both elements being 1, making 1 the repeating element.
 *
 * Constraints:
 * 2 ≤ arr.size() ≤ 10^5
 * 1 ≤ arr[i] ≤ n-1
 */

/************************************************************ C++ ************************************************/

// Approach: Use XOR to cancel out all numbers from 1 to n-1 and elements of the array. The remaining result is the duplicate.
// Time Complexity: O(n), as we loop through the array only once.
// Space Complexity: O(1), as we use only a single variable for XOR.
class Solution {
public:
    int findDuplicate(vector<int>& arr) {
        int n   = arr.size();
        int res = 0;

        // Loop through 0 to n-2, XOR all elements of the array and numbers from 1 to n-1
        for (int i = 0; i < n - 1; i++) {
            res = res ^ (i + 1) ^ arr[i];   // XORing i+1 (from range 1 to n-1) and arr[i]
        }

        // XOR the last element of the array
        res = res ^ arr[n - 1]; // Remaining XOR with last element to isolate the duplicate

        return res;             // This will be the repeating number
    }
};

/*
 *
 * Dry Run
 *
 * Input: arr[] = [1, 3, 2, 3, 4]
 * Size of array (n) = 5
 *
 * Step 1: res = 0
 * Step 2: Loop from i = 0 to n - 2 = 3
 *   i = 0 => res = 0 ^ 1 ^ 1 = 0
 *   i = 1 => res = 0 ^ 2 ^ 3 = 1
 *   i = 2 => res = 1 ^ 3 ^ 2 = 0
 *   i = 3 => res = 0 ^ 4 ^ 3 = 7
 * Step 3: res = 7 ^ arr[4] = 7 ^ 4 = 3
 *
 * Output: 3 (which is the duplicate element)
 *
 */

/************************************************************ JAVA ************************************************/

// Approach: Use XOR to cancel out all numbers from 1 to n-1 and elements of the array. The remaining result is the duplicate.
// Time Complexity: O(n), as we loop through the array only once.
// Space Complexity: O(1), as we use only a single variable for XOR.
class Solution {
    public int findDuplicate(int[] arr) {
        int n   = arr.length;
        int res = 0;

        // Loop through 0 to n-2, XOR all elements of the array and numbers from 1 to n-1
        for (int i = 0; i < n - 1; i++) {
            res = res ^ (i + 1) ^ arr[i]; // XORing i+1 (from range 1 to n-1) and arr[i]
        }

        // XOR the last element of the array
        res = res ^ arr[n - 1]; // Remaining XOR with last element to isolate the duplicate

        return res;             // This will be the repeating number
    }
}

/*
 *
 * Dry Run
 *
 * Input: arr[] = [1, 3, 2, 3, 4]
 * Size of array (n) = 5
 *
 * Step 1: res = 0
 * Step 2: Loop from i = 0 to n - 2 = 3
 *   i = 0 => res = 0 ^ 1 ^ 1 = 0
 *   i = 1 => res = 0 ^ 2 ^ 3 = 1
 *   i = 2 => res = 1 ^ 3 ^ 2 = 0
 *   i = 3 => res = 0 ^ 4 ^ 3 = 7
 * Step 3: res = 7 ^ arr[4] = 7 ^ 4 = 3
 *
 * Output: 3 (which is the duplicate element)
 *
 */
