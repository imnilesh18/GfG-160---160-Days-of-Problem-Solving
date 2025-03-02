/*
 * K Sized Subarray Maximum
 *
 * Given an array arr[] of integers and an integer k, your task is to find the maximum value for each contiguous subarray of size k. The output should be an array of maximum values corresponding to each contiguous subarray.
 *
 * Examples:
 *
 * Input: arr[] = [1, 2, 3, 1, 4, 5, 2, 3, 6], k = 3
 * Output: [3, 3, 4, 5, 5, 5, 6]
 * Explanation:
 * 1st contiguous subarray = [1 2 3] max = 3
 * 2nd contiguous subarray = [2 3 1] max = 3
 * 3rd contiguous subarray = [3 1 4] max = 4
 * 4th contiguous subarray = [1 4 5] max = 5
 * 5th contiguous subarray = [4 5 2] max = 5
 * 6th contiguous subarray = [5 2 3] max = 5
 * 7th contiguous subarray = [2 3 6] max = 6
 *
 * Input: arr[] = [8, 5, 10, 7, 9, 4, 15, 12, 90, 13], k = 4
 * Output: [10, 10, 10, 15, 15, 90, 90]
 * Explanation:
 * 1st contiguous subarray = [8 5 10 7], max = 10
 * 2nd contiguous subarray = [5 10 7 9], max = 10
 * 3rd contiguous subarray = [10 7 9 4], max = 10
 * 4th contiguous subarray = [7 9 4 15], max = 15
 * 5th contiguous subarray = [9 4 15 12], max = 15
 * 6th contiguous subarray = [4 15 12 90], max = 90
 * 7th contiguous subarray = [15 12 90 13], max = 90
 *
 * Input: arr[] = [5, 1, 3, 4, 2, 6], k = 1
 * Output: [5, 1, 3, 4, 2, 6]
 * Explanation:
 * When k = 1, each element in the array is its own subarray, so the output is simply the same array
 *
 * Constraints:
 * 1 ≤ arr.size() ≤ 10^6
 * 1 ≤ k ≤ arr.size()
 * 0 ≤ arr[i] ≤ 10^9
 */

/************************************************************ C++ ************************************************/

// Approach: Use a deque to maintain indices of potential maximum elements for each sliding window.
// Time Complexity: O(n) - Each element is processed at most twice (once when added and once when removed).
// Space Complexity: O(k) - The deque stores at most k indices at any time.
class Solution {
public:
    vector<int> maxOfSubarrays(vector<int>& arr, int k) {
        int         n = arr.size();
        deque<int>  deq;    // deque to store indices of potential maximums in the current window
        vector<int> result; // vector to store the maximum of each subarray

        for (int i = 0; i < n; i++) {
            // Remove indices that are out of the current window (i - k)
            while (!deq.empty() && deq.front() <= i - k) {
                deq.pop_front();
            }

            // Remove elements from the back that are smaller than the current element
            while (!deq.empty() && arr[i] > arr[deq.back()]) {
                deq.pop_back();
            }

            // Add current index to the deque
            deq.push_back(i);

            // Once the first window is reached, add the maximum (front of deque) to the result
            if (i >= k - 1) {
                result.push_back(arr[deq.front()]);
            }
        }
        return result;
    }
};

/*
 * Dry Run
 * Input: arr = [1, 2, 3, 1, 4, 5, 2, 3, 6], k = 3
 *
 * i = 0:
 *  deq = [0] (index 0 pushed)
 * i = 1:
 *  deq = [0] -> arr[1] (2) > arr[0] (1) so pop index 0, then push index 1 -> deq = [1]
 * i = 2:
 *  deq = [1] -> arr[2] (3) > arr[1] (2) so pop index 1, then push index 2 -> deq = [2]
 *  i >= k-1 (2 >= 2), so result = [arr[2]] = [3]
 * i = 3:
 *  Remove indices <= (3 - 3) = 0; deq = [2] remains (index 2 is valid)
 *  Push index 3 -> deq = [2, 3]
 *  result = [3, arr[2]] = [3, 3]
 * i = 4:
 *  deq = [2, 3] -> arr[4] (4) > arr[3] (1) so pop index 3; then arr[4] (4) > arr[2] (3) so pop index 2
 *  Push index 4 -> deq = [4]
 *  result = [3, 3, arr[4]] = [3, 3, 4]
 * i = 5:
 *  deq = [4] -> arr[5] (5) > arr[4] (4) so pop index 4; push index 5 -> deq = [5]
 *  result = [3, 3, 4, arr[5]] = [3, 3, 4, 5]
 * i = 6:
 *  deq = [5] (index 5 is within window [4,6]); push index 6 -> deq = [5, 6]
 *  result = [3, 3, 4, 5, arr[5]] = [3, 3, 4, 5, 5]
 * i = 7:
 *  Remove indices <= (7 - 3) = 4; deq = [5, 6] remains (both indices valid)
 *  arr[7] (3) is not greater than arr[6] (2)? Actually, arr[7] (3) > arr[6] (2) so pop index 6
 *  Push index 7 -> deq = [5, 7]
 *  result = [3, 3, 4, 5, 5, arr[5]] = [3, 3, 4, 5, 5, 5]
 * i = 8:
 *  Remove indices <= (8 - 3) = 5; deq front index 5 is removed -> deq = [7]
 *  arr[8] (6) > arr[7] (3) so pop index 7; push index 8 -> deq = [8]
 *  result = [3, 3, 4, 5, 5, 5, arr[8]] = [3, 3, 4, 5, 5, 5, 6]
 *
 * Final Output: [3, 3, 4, 5, 5, 5, 6]
 */

/************************************************************ JAVA ************************************************/

// Approach: Use a deque to store indices of potential maximums for each sliding window.
// Time Complexity: O(n) - Each element is processed at most twice (added and removed).
// Space Complexity: O(k) - The deque stores at most k indices at any time.
class Solution {
    public ArrayList<Integer> maxOfSubarrays(int arr[], int k) {
        // Get the length of the array
        int n = arr.length;
        // Result list to store maximums for each subarray
        ArrayList<Integer> result = new ArrayList<>();
        // Deque to store indices of potential maximum values for each sliding window
        Deque<Integer> deq = new LinkedList<>();

        // Loop through every element in the array
        for (int i = 0; i < n; i++) {
            // Remove indices from the front if they are out of the current window (i - k)
            while (!deq.isEmpty() && deq.peekFirst() <= i - k) {
                deq.pollFirst();
            }

            // Remove from the back all indices whose corresponding values are less than the current element
            while (!deq.isEmpty() && arr[i] >= arr[deq.peekLast()]) {
                deq.pollLast();
            }

            // Add current index to the deque
            deq.offerLast(i);

            // Once the first window is reached (i >= k-1), add the current maximum to result
            if (i >= k - 1) {
                result.add(arr[deq.peekFirst()]);
            }
        }
        return result;
    }
}

/*
 * Dry Run
 * Input: arr = [1, 2, 3, 1, 4, 5, 2, 3, 6], k = 3
 *
 * i = 0:
 *  deq = [0] (index 0 is added)
 * i = 1:
 *  deq = [] (pop index 0 because arr[1]=2 >= arr[0]=1), then add index 1 -> deq = [1]
 * i = 2:
 *  deq = [] (pop index 1 because arr[2]=3 >= arr[1]=2), then add index 2 -> deq = [2]
 *  i >= k-1 so result = [arr[2]] = [3]
 * i = 3:
 *  deq = [2] (index 2 is still in the window), add index 3 -> deq = [2, 3]
 *  result = [3, arr[2]] = [3, 3]
 * i = 4:
 *  deq = [2, 3] (pop index 3 since arr[4]=4 >= arr[3]=1; pop index 2 since arr[4]=4 >= arr[2]=3),
 *  then add index 4 -> deq = [4]
 *  result = [3, 3, arr[4]] = [3, 3, 4]
 * i = 5:
 *  deq = [4] (pop index 4 since arr[5]=5 >= arr[4]=4), then add index 5 -> deq = [5]
 *  result = [3, 3, 4, arr[5]] = [3, 3, 4, 5]
 * i = 6:
 *  deq = [5] (index 5 is within window), add index 6 -> deq = [5, 6]
 *  result = [3, 3, 4, 5, arr[5]] = [3, 3, 4, 5, 5]
 * i = 7:
 *  deq = [5, 6] (no index removed; index 5 is valid),
 *  remove index 6 since arr[7]=3 >= arr[6]=2, add index 7 -> deq = [5, 7]
 *  result = [3, 3, 4, 5, 5, arr[5]] = [3, 3, 4, 5, 5, 5]
 * i = 8:
 *  deq = [5, 7] (remove index 5 because 5 <= 8-3),
 *  remove index 7 since arr[8]=6 >= arr[7]=3, add index 8 -> deq = [8]
 *  result = [3, 3, 4, 5, 5, 5, arr[8]] = [3, 3, 4, 5, 5, 5, 6]
 *
 * Final Output: [3, 3, 4, 5, 5, 5, 6]
 */
