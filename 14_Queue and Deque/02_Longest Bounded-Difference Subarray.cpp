/*
 * Longest Bounded-Difference Subarray
 *
 * Given an array of positive integers arr[] and a non-negative integer x, the task is to find the longest sub-array where the absolute difference between any two elements is not greater than x.
 * If multiple such subarrays exist, return the one that starts at the smallest index.
 *
 * Examples:
 *
 * Input: arr[] = [8, 4, 2, 6, 7], x = 4
 * Output: [4, 2, 6]
 * Explanation: The sub-array described by index [1..3], i.e. [4, 2, 6] contains no such difference of two elements which is greater than 4.
 *
 * Input: arr[] = [15, 10, 1, 2, 4, 7, 2], x = 5
 * Output: [2, 4, 7, 2]
 * Explanation: The sub-array described by indexes [3..6], i.e. [2, 4, 7, 2] contains no such difference of two elements which is greater than 5.
 *
 * Constraints:
 * 1 <= arr.size() <= 10^5
 * 1 <= arr[i] <= 10^9
 * 0 <= x<= 10^9
 */

/************************************************************ C++ ************************************************/

// Approach 1: Use a sliding window with two heaps to track the current maximum and minimum in the window, and adjust the window when the difference exceeds x; track the best subarray.
// Time Complexity: O(n log n) - each element is pushed and popped from heaps at most once.
// Space Complexity: O(n) - in worst-case the heaps may contain all elements.
class Solution {
public:
    typedef pair<int, int> P;
    vector<int> longestSubarray(vector<int>& arr, int x) {
        int n = arr.size();      // size of the input array

        // maxPq: max heap to get the current maximum in the window
        // minPq: min heap to get the current minimum in the window
        priority_queue<P, vector<P>>             maxPq;
        priority_queue<P, vector<P>, greater<P>> minPq;

        int i         = 0; // start pointer of the sliding window
        int j         = 0; // end pointer of the sliding window
        int bestLen   = 0; // stores the maximum valid subarray length found
        int bestStart = 0; // stores the starting index of the best subarray

        while (j < n) {
            // Push the current element and its index into both heaps
            maxPq.push({ arr[j], j });
            minPq.push({ arr[j], j });

            // Check if the current window is valid (difference between max and min <= x)
            while (maxPq.top().first - minPq.top().first > x) {
                // Adjust the window: move start pointer i to one position after the minimum index among the top elements
                i = min(maxPq.top().second, minPq.top().second) + 1;

                // Remove elements from maxPq that are no longer in the current window
                while (!maxPq.empty() && maxPq.top().second < i) {
                    maxPq.pop();
                }

                // Remove elements from minPq that are no longer in the current window
                while (!minPq.empty() && minPq.top().second < i) {
                    minPq.pop();
                }
            }

            // Update best subarray if current window size is greater than bestLen
            if (j - i + 1 > bestLen) {
                bestLen   = j - i + 1;
                bestStart = i;
            }
            j++;      // move end pointer to the next element
        }

        // Return the subarray from bestStart to bestStart + bestLen - 1
        return vector<int>(arr.begin() + bestStart, arr.begin() + bestStart + bestLen);
    }
};

/*
 * Dry Run:
 * Input: arr = [8, 4, 2, 6, 7], x = 4
 * Initial state: i = 0, j = 0, bestLen = 0, bestStart = 0, maxPq = [], minPq = []
 *
 * Iteration 1:
 * j = 0, element = 8
 * maxPq becomes [(8,0)], minPq becomes [(8,0)]
 * Difference = 8 - 8 = 0 <= 4  -> Valid window [8]
 * Update bestLen = 1, bestStart = 0
 *
 * Iteration 2:
 * j = 1, element = 4
 * maxPq becomes [(8,0), (4,1)], minPq becomes [(4,1), (8,0)]
 * Difference = 8 - 4 = 4 <= 4  -> Valid window [8,4]
 * Update bestLen = 2, bestStart = 0
 *
 * Iteration 3:
 * j = 2, element = 2
 * maxPq becomes [(8,0), (4,1), (2,2)], minPq becomes [(2,2), (8,0), (4,1)]
 * Difference = 8 - 2 = 6 > 4  -> Invalid window; adjust i:
 *   i = min(index of 8, index of 2) + 1 = min(0,2) + 1 = 1
 *   Remove elements with index < 1: remove (8,0) from heaps
 * New window becomes [4,2] with difference = 4 - 2 = 2 <= 4
 * bestLen remains 2 (window size = 2)
 *
 * Iteration 4:
 * j = 3, element = 6
 * maxPq becomes [(6,3), (4,1), (2,2)], minPq becomes [(2,2), (4,1), (6,3)]
 * Difference = 6 - 2 = 4 <= 4  -> Valid window [4,2,6]
 * Update bestLen = 3, bestStart = 1
 *
 * Iteration 5:
 * j = 4, element = 7
 * maxPq becomes [(7,4), (6,3), (2,2), (4,1)], minPq becomes [(2,2), (4,1), (6,3), (7,4)]
 * Difference = 7 - 2 = 5 > 4  -> Invalid window; adjust i:
 *   i = min(index of 7, index of 2) + 1 = min(4,2) + 1 = 3
 *   Remove elements with index < 3: remove (4,1) and (2,2) from heaps
 * New window becomes [6,7] with difference = 7 - 6 = 1 <= 4
 * bestLen remains 3 (window size = 2)
 *
 * Final Output:
 * Return subarray from index bestStart = 1 with length bestLen = 3, i.e., [4, 2, 6]
 */

// Approach 2: Use a sliding window with a multiset to maintain the sorted elements of the window and track the longest valid subarray where the difference between the maximum and minimum is not greater than x.
// Time Complexity: O(n log n) - each insertion/deletion in the multiset takes O(log n) over n elements.
// Space Complexity: O(n) - in the worst-case the multiset stores all elements.
class Solution {
public:
    vector<int> longestSubarray(vector<int>& arr, int x) {
        int n = arr.size();          // size of the input array

        // multiset to maintain a sorted window of elements for quick access to min and max
        multiset<int> st;

        int i         = 0;     // start pointer of the sliding window
        int j         = 0;     // end pointer of the sliding window
        int bestLen   = 0;     // stores the maximum valid subarray length found
        int bestStart = 0;     // stores the starting index of the best subarray

        while (j < n) {        // iterate over the array
            st.insert(arr[j]); // insert current element into the multiset

            // while the current window is invalid (difference between max and min > x)
            while (*st.rbegin() - *st.begin() > x) {
                st.erase(st.find(arr[i]));     // remove the element at index i from the multiset
                i++;                           // move the start pointer to shrink the window
            }

            // update best subarray if current window size is greater than bestLen
            if (j - i + 1 > bestLen) {
                bestLen   = j - i + 1;
                bestStart = i;
            }
            j++;              // move end pointer to the next element
        }
        // return the subarray from bestStart to bestStart + bestLen - 1
        return vector<int>(arr.begin() + bestStart, arr.begin() + bestStart + bestLen);
    }
};

/*
 * Dry Run:
 * Input: arr = [8, 4, 2, 6, 7], x = 4
 * Initial state: i = 0, j = 0, bestLen = 0, bestStart = 0, st = {}
 *
 * Iteration 1:
 * j = 0, element = 8
 * st becomes {8}
 * Difference = 8 - 8 = 0 <= 4, window valid: [8]
 * Update bestLen = 1, bestStart = 0
 *
 * Iteration 2:
 * j = 1, element = 4
 * st becomes {4,8}
 * Difference = 8 - 4 = 4 <= 4, window valid: [8,4]
 * Update bestLen = 2, bestStart remains 0
 *
 * Iteration 3:
 * j = 2, element = 2
 * st becomes {2,4,8}
 * Difference = 8 - 2 = 6 > 4, window invalid
 * Remove arr[i]=8, i becomes 1, st becomes {2,4}
 * Now difference = 4 - 2 = 2 <= 4, window valid: [4,2]
 * bestLen remains 2
 *
 * Iteration 4:
 * j = 3, element = 6
 * st becomes {2,4,6}
 * Difference = 6 - 2 = 4 <= 4, window valid: [4,2,6]
 * Update bestLen = 3, bestStart = 1
 *
 * Iteration 5:
 * j = 4, element = 7
 * st becomes {2,4,6,7}
 * Difference = 7 - 2 = 5 > 4, window invalid
 * Remove arr[i]=4, i becomes 2, st becomes {2,6,7}
 * Difference = 7 - 2 = 5 > 4, still invalid
 * Remove arr[i]=2, i becomes 3, st becomes {6,7}
 * Now difference = 7 - 6 = 1 <= 4, window valid: [6,7]
 * bestLen remains 3
 *
 * Final Output:
 * Return subarray from index bestStart = 1 with length bestLen = 3, i.e., [4, 2, 6]
 */

/************************************************************ JAVA ************************************************/

// Approach 1: Use a sliding window with two heaps to track the current maximum and minimum in the window,and adjust the window when the difference exceeds x; track the best subarray.
// Time Complexity: O(n log n) - each element is pushed and popped from heaps at most once.
// Space Complexity: O(n) - in worst-case the heaps may contain all elements.
class Solution {
    class Pair {
        int val, index;
        Pair(int val, int index) {
            this.val   = val;
            this.index = index;
        }
    }

    public ArrayList<Integer> longestSubarray(int[] arr, int x) {
        int n = arr.length;      // size of the input array

        // maxPq: max heap to get the current maximum in the window
        PriorityQueue<Pair> maxPq = new PriorityQueue<>((a, b)->b.val - a.val);
        // minPq: min heap to get the current minimum in the window
        PriorityQueue<Pair> minPq = new PriorityQueue<>((a, b)->a.val - b.val);

        int i         = 0; // start pointer of the sliding window
        int j         = 0; // end pointer of the sliding window
        int bestLen   = 0; // stores the maximum valid subarray length found
        int bestStart = 0; // stores the starting index of the best subarray

        while (j < n) {
            // Push the current element and its index into both heaps
            maxPq.offer(new Pair(arr[j], j));
            minPq.offer(new Pair(arr[j], j));

            // Check if the current window is valid (difference between max and min <= x)
            while (!maxPq.isEmpty() && !minPq.isEmpty() && maxPq.peek().val - minPq.peek().val > x) {
                // Adjust the window: move start pointer i to one position after the minimum index among the top elements
                i = Math.min(maxPq.peek().index, minPq.peek().index) + 1;

                // Remove elements from maxPq that are no longer in the current window
                while (!maxPq.isEmpty() && maxPq.peek().index < i) {
                    maxPq.poll();
                }

                // Remove elements from minPq that are no longer in the current window
                while (!minPq.isEmpty() && minPq.peek().index < i) {
                    minPq.poll();
                }
            }

            // Update best subarray if current window size is greater than bestLen
            if (j - i + 1 > bestLen) {
                bestLen   = j - i + 1;
                bestStart = i;
            }
            j++;  // move end pointer to the next element
        }

        // Build the result subarray from bestStart to bestStart + bestLen - 1
        ArrayList<Integer> result = new ArrayList<>();
        for (int k = bestStart; k < bestStart + bestLen; k++) {
            result.add(arr[k]);
        }
        return result;
    }
}

/*
 * Dry Run:
 * Input: arr = [8, 4, 2, 6, 7], x = 4
 * Initial state: i = 0, j = 0, bestLen = 0, bestStart = 0, maxPq = [], minPq = []
 *
 * Iteration 1:
 * j = 0, element = 8
 * maxPq becomes [(8,0)], minPq becomes [(8,0)]
 * Difference = 8 - 8 = 0 <= 4  -> Valid window [8]
 * Update bestLen = 1, bestStart = 0
 *
 * Iteration 2:
 * j = 1, element = 4
 * maxPq becomes [(8,0), (4,1)], minPq becomes [(4,1), (8,0)]
 * Difference = 8 - 4 = 4 <= 4  -> Valid window [8,4]
 * Update bestLen = 2, bestStart = 0
 *
 * Iteration 3:
 * j = 2, element = 2
 * maxPq becomes [(8,0), (4,1), (2,2)], minPq becomes [(2,2), (8,0), (4,1)]
 * Difference = 8 - 2 = 6 > 4  -> Invalid window; adjust i:
 *  i = min(index of 8, index of 2) + 1 = min(0,2) + 1 = 1
 *  Remove elements with index < 1: remove (8,0) from heaps
 * New window becomes [4,2] with difference = 4 - 2 = 2 <= 4
 * bestLen remains 2 (window size = 2)
 *
 * Iteration 4:
 * j = 3, element = 6
 * maxPq becomes [(6,3), (4,1), (2,2)], minPq becomes [(2,2), (4,1), (6,3)]
 * Difference = 6 - 2 = 4 <= 4  -> Valid window [4,2,6]
 * Update bestLen = 3, bestStart = 1
 *
 * Iteration 5:
 * j = 4, element = 7
 * maxPq becomes [(7,4), (6,3), (2,2), (4,1)], minPq becomes [(2,2), (4,1), (6,3), (7,4)]
 * Difference = 7 - 2 = 5 > 4  -> Invalid window; adjust i:
 *  i = min(index of 7, index of 2) + 1 = min(4,2) + 1 = 3
 *  Remove elements with index < 3: remove (4,1) and (2,2) from heaps
 * New window becomes [6,7] with difference = 7 - 6 = 1 <= 4
 * bestLen remains 3 (window size = 2)
 *
 * Final Output:
 * Return subarray from index bestStart = 1 with length bestLen = 3, i.e., [4, 2, 6]
 */

// Approach 2: Use a sliding window with a TreeMap as a multiset to maintain the sorted elements of the window and track the longest valid subarray where the difference between the maximum and minimum is not greater than x.
// Time Complexity: O(n log n) - each insertion/deletion in the TreeMap takes O(log n) over n elements.
// Space Complexity: O(n) - in the worst-case the TreeMap stores all elements.
class Solution {
    public ArrayList<Integer> longestSubarray(int[] arr, int x) {
        int n = arr.length;  // size of the input array

        // TreeMap to maintain a sorted window of elements (acting as a multiset) for quick access to min and max
        TreeMap<Integer, Integer> tm = new TreeMap<>();

        int i         = 0; // start pointer of the sliding window
        int j         = 0; // end pointer of the sliding window
        int bestLen   = 0; // stores the maximum valid subarray length found
        int bestStart = 0; // stores the starting index of the best subarray

        while (j < n) {    // iterate over the array
            // Insert current element into the TreeMap, updating its frequency
            tm.put(arr[j], tm.getOrDefault(arr[j], 0) + 1);

            // while the current window is invalid (difference between max and min > x)
            while (tm.lastKey() - tm.firstKey() > x) {
                // Remove the element at index i from the TreeMap
                int count = tm.get(arr[i]);
                if (count == 1) {
                    tm.remove(arr[i]);
                } else {
                    tm.put(arr[i], count - 1);
                }
                i++;  // move the start pointer to shrink the window
            }

            // update best subarray if current window size is greater than bestLen
            if (j - i + 1 > bestLen) {
                bestLen   = j - i + 1;
                bestStart = i;
            }
            j++;  // move end pointer to the next element
        }

        // Build and return the subarray from bestStart to bestStart + bestLen - 1
        ArrayList<Integer> res = new ArrayList<>();
        for (int k = bestStart; k < bestStart + bestLen; k++) {
            res.add(arr[k]);
        }
        return res;
    }
}

/*
 * Dry Run:
 * Input: arr = [8, 4, 2, 6, 7], x = 4
 * Initial state: i = 0, j = 0, bestLen = 0, bestStart = 0, tm = {}
 *
 * Iteration 1:
 * j = 0, element = 8
 * tm becomes {8=1}
 * Difference = 8 - 8 = 0 <= 4, window valid: [8]
 * Update bestLen = 1, bestStart = 0
 *
 * Iteration 2:
 * j = 1, element = 4
 * tm becomes {4=1, 8=1}
 * Difference = 8 - 4 = 4 <= 4, window valid: [8, 4]
 * Update bestLen = 2, bestStart remains 0
 *
 * Iteration 3:
 * j = 2, element = 2
 * tm becomes {2=1, 4=1, 8=1}
 * Difference = 8 - 2 = 6 > 4, window invalid
 * Remove arr[i]=8, i becomes 1, tm becomes {2=1, 4=1}
 * Now difference = 4 - 2 = 2 <= 4, window valid: [4, 2]
 * bestLen remains 2
 *
 * Iteration 4:
 * j = 3, element = 6
 * tm becomes {2=1, 4=1, 6=1}
 * Difference = 6 - 2 = 4 <= 4, window valid: [4, 2, 6]
 * Update bestLen = 3, bestStart = 1
 *
 * Iteration 5:
 * j = 4, element = 7
 * tm becomes {2=1, 4=1, 6=1, 7=1}
 * Difference = 7 - 2 = 5 > 4, window invalid
 * Remove arr[i]=4, i becomes 2, tm becomes {2=1, 6=1, 7=1}
 * Difference = 7 - 2 = 5 > 4, still invalid
 * Remove arr[i]=2, i becomes 3, tm becomes {6=1, 7=1}
 * Now difference = 7 - 6 = 1 <= 4, window valid: [6, 7]
 * bestLen remains 3
 *
 * Final Output:
 * Return subarray from index bestStart = 1 with length bestLen = 3, i.e., [4, 2, 6]
 */
