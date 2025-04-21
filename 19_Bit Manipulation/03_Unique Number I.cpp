/*
 * Unique Number I
 *
 * Difficulty: Easy Accuracy: 82.73% Submissions: 1K+ Points: 2
 *
 * Given a unsorted array arr[] of positive integers having all the numbers occurring exactly twice, except for one number which will occur only once. Find the number occurring only once.
 *
 * Examples :
 *
 * Input: arr[] = [1, 2, 1, 5, 5]
 * Output: 2
 * Explanation: Since 2 occurs once, while other numbers occur twice, 2 is the answer.
 *
 * Input: arr[] = [2, 30, 2, 15, 20, 30, 15]
 * Output: 20
 * Explanation: Since 20 occurs once, while other numbers occur twice, 20 is the answer.
 *
 * Constraints
 * 1 ≤  arr.size()  ≤ 10^6
 * 0 ≤ arr[i] ≤ 10^9
 */

// Intuition:

/*
 * This approach uses the XOR operation to find the unique element in an array where every other element appears twice. XOR of two identical numbers cancels them out (results in zero), so after XORing all the elements, only the element that appears once will remain.
 *
 * 1 ^ 2 ^ 1 ^ 5 ^ 5
 * = (1 ^ 1) ^ (5 ^ 5) ^ 2   // group identical pairs
 * = 0 ^ 0 ^ 2               // XOR of identical numbers is 0
 * = 2                       // only the unique number remains
 */

/************************************************************ C++ ************************************************/

// Approach: This approach uses the XOR operation to find the unique element in an array where every other element appears twice. XOR of two identical numbers cancels them out, so after XORing all elements, only the unique element remains.
// Time Complexity: O(n), since we traverse the array once.
// Space Complexity: O(1), as we use only one additional variable.
class Solution {
public:
    int findUnique(vector<int>& arr) {
        int result = 0;              // Initialize result to 0

        for (int i = 0; i < arr.size(); i++) {
            result ^= arr[i];        // XOR current element with result; duplicates cancel out
        }
        return result;               // result now holds the unique element
    }
};

/*
 *
 * Dry Run
 *
 * Input: arr = [1, 2, 1, 5, 5]
 * Step-by-step:
 *   result = 0
 *   result ^= 1    => result = 1
 *   result ^= 2    => result = 1 ^ 2 = 3
 *   result ^= 1    => result = 3 ^ 1 = 2
 *   result ^= 5    => result = 2 ^ 5 = 7
 *   result ^= 5    => result = 7 ^ 5 = 2
 * Output: 2
 */

/************************************************************ JAVA ************************************************/

// Approach: This approach uses the XOR operation to find the unique element in an array where every other element appears twice. XOR of two identical numbers cancels them out, so after XORing all elements, only the unique element remains.
// Time Complexity: O(n), since we traverse the array once.
// Space Complexity: O(1), as we use only one additional variable.
class Solution {
    public int findUnique(int[] arr) {
        int result = 0;                  // Initialize result to 0

        for (int i = 0; i < arr.length; i++) {
            result ^= arr[i];            // XOR current element; duplicates cancel out
        }
        return result;                   // result now holds the unique element
    }
}

/*
 *
 * Dry Run
 *
 * Input: arr = [1, 2, 1, 5, 5]
 * Step-by-step:
 *   result = 0
 *   result ^= 1    => result = 1
 *   result ^= 2    => result = 1 ^ 2 = 3
 *   result ^= 1    => result = 3 ^ 1 = 2
 *   result ^= 5    => result = 2 ^ 5 = 7
 *   result ^= 5    => result = 7 ^ 5 = 2
 * Output: 2
 */
