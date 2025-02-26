/*
 * Maximum of minimum for every window size
 *
 * Given an array of integers arr[], the task is to find the maximum of the minimum values for every possible window size in the array, where the window size ranges from 1 to arr.size().
 *
 * More formally, for each window size k, determine the smallest element in all windows of size k, and then find the largest value among these minimums where 1<=k<=arr.size().
 *
 * Examples :
 *
 * Input: arr[] = [10, 20, 30, 50, 10, 70, 30]
 * Output: [70, 30, 20, 10, 10, 10, 10]
 * Explanation:
 * 1. First element in output indicates maximum of minimums of all windows of size 1. Minimums of windows of size 1 are [10], [20], [30], [50], [10], [70] and [30]. Maximum of these minimums is 70.
 * 2. Second element in output indicates maximum of minimums of all windows of size 2. Minimums of windows of size 2 are [10], [20], [30], [10], [10], and [30]. Maximum of these minimums is 30.
 * 3. Third element in output indicates maximum of minimums of all windows of size 3. Minimums of windows of size 3 are [10], [20], [10], [10] and [10]. Maximum of these minimums is 20.
 * Similarly other elements of output are computed.
 *
 *
 * Input: arr[] = [10, 20, 30]
 * Output: [30, 20, 10]
 * Explanation: First element in output indicates maximum of minimums of all windows of size 1. Minimums of windows of size 1 are [10] , [20] , [30]. Maximum of these minimums are 30 and similarly other outputs can be computed
 *
 * Constraints:
 * 1 <= arr.size() <= 10^5
 * 1 <= arr[i] <= 10^6
 */

/************************************************************ C++ ************************************************/

// Approach: Use a monotonic stack to determine the window size for which each element is the minimum and update the result array with the maximum of these minimums.
// Time Complexity: O(n) as each element is pushed and popped at most once.
// Space Complexity: O(n) for the stack and result vector.
class Solution {
public:
   vector<int> maxOfMins(vector<int>& arr) {
      int n = arr.size();
      // result vector to store maximum of minimums for window sizes 1 to n (result[i] corresponds to window size i+1)
      vector<int> result(n, 0);
      // stack to store indices in increasing order of their corresponding array values
      stack<int> st;

      // Traverse each element in the array
      for (int i = 0; i < n; i++) {
         // While stack is not empty and the current element is less than the element at the top index of the stack
         while (!st.empty() && arr[st.top()] > arr[i]) {
            int index = st.top();
            st.pop();
            // If the stack is empty, then arr[index] is the minimum for window size 'i'
            if (st.empty()) {
               int range = i;          // window size where arr[index] is minimum
               result[range - 1] = max(result[range - 1], arr[index]);
            } else {
               // Else, window size is determined by the current index and the new top of the stack
               int range = i - st.top() - 1;
               result[range - 1] = max(result[range - 1], arr[index]);
            }
         }
         // Push current index onto the stack
         st.push(i);
      }

      // Process any remaining elements in the stack
      while (!st.empty()) {
         int index = st.top();
         st.pop();
         if (st.empty()) {
            int range = n;         // element is minimum for the entire array
            result[range - 1] = max(result[range - 1], arr[index]);
         } else {
            int range = n - st.top() - 1;
            result[range - 1] = max(result[range - 1], arr[index]);
         }
      }

      // Update the result array so that smaller window sizes have the maximum of minimums
      for (int i = n - 2; i >= 0; i--) {
         result[i] = max(result[i], result[i + 1]);
      }

      return result;
   }
};

/* Dry Run:
 * Input: arr = [10, 20, 30, 50, 10, 70, 30]
 * n = 7, result = [0, 0, 0, 0, 0, 0, 0], stack = []
 *
 * Iteration i = 0:
 * - Stack is empty, push index 0. stack = [0]
 *
 * Iteration i = 1:
 * - arr[st.top()] = 10 <= 20, push index 1. stack = [0, 1]
 *
 * Iteration i = 2:
 * - arr[st.top()] = 20 <= 30, push index 2. stack = [0, 1, 2]
 *
 * Iteration i = 3:
 * - arr[st.top()] = 30 <= 50, push index 3. stack = [0, 1, 2, 3]
 *
 * Iteration i = 4:
 * - arr[st.top()] = 50 > 10, pop index 3.
 *    stack becomes [0, 1, 2], window size = 4 - 2 - 1 = 1, update result[0] = max(0, 50) = 50.
 * - arr[st.top()] = 30 > 10, pop index 2.
 *    stack becomes [0, 1], window size = 4 - 1 - 1 = 2, update result[1] = max(0, 30) = 30.
 * - arr[st.top()] = 20 > 10, pop index 1.
 *    stack becomes [0], window size = 4 - 0 - 1 = 3, update result[2] = max(0, 20) = 20.
 * - Now, arr[st.top()] = 10 <= 10, push index 4. stack = [0, 4]
 *
 * Iteration i = 5:
 * - arr[st.top()] = 10 <= 70, push index 5. stack = [0, 4, 5]
 *
 * Iteration i = 6:
 * - arr[st.top()] = 70 > 30, pop index 5.
 *    stack becomes [0, 4], window size = 6 - 4 - 1 = 1, update result[0] = max(50, 70) = 70.
 * - Now, arr[st.top()] = 10 <= 30, push index 6. stack = [0, 4, 6]
 *
 * Process remaining stack:
 * - Pop index 6, stack becomes [0, 4], window size = 7 - 4 - 1 = 2, update result[1] = max(30, 30) = 30.
 * - Pop index 4, stack becomes [0], window size = 7 - 0 - 1 = 6, update result[5] = max(0, 10) = 10.
 * - Pop index 0, stack becomes empty, window size = 7, update result[6] = max(0, 10) = 10.
 *
 * Result before final loop: [70, 30, 20, 0, 0, 10, 10]
 * Final loop (backward update):
 * - i = 5: result[5] = max(10, 10) = 10.
 * - i = 4: result[4] = max(0, 10) = 10.
 * - i = 3: result[3] = max(0, 10) = 10.
 * - i = 2: result[2] = max(20, 10) = 20.
 * - i = 1: result[1] = max(30, 20) = 30.
 * - i = 0: result[0] = max(70, 30) = 70.
 *
 * Final Output: [70, 30, 20, 10, 10, 10, 10]
 */

/************************************************************ JAVA ************************************************/

// Approach: Use a monotonic stack to determine the window size for which each element is the minimum and update the result list with the maximum of these minimums.
// Time Complexity: O(n) as each element is pushed and popped at most once.
// Space Complexity: O(n) for the stack and result list.
class Solution {
   public ArrayList<Integer> maxOfMins(int[] arr) {
      int n = arr.length;
      // Initialize result list with 0's for window sizes 1 to n (result.get(i) corresponds to window size i+1)
      ArrayList<Integer> result = new ArrayList<>(Collections.nCopies(n, 0));
      // Stack to store indices in increasing order of their corresponding values
      Stack<Integer> st = new Stack<>();

      // Traverse each element of the array
      for (int i = 0; i < n; i++) {
         // While stack is not empty and the current element is less than the element at the top index of the stack
         while (!st.isEmpty() && arr[st.peek()] > arr[i]) {
            int index = st.pop();
            if (st.isEmpty()) {
               int range = i;      // window size for which arr[index] is the minimum
               result.set(range - 1, Math.max(result.get(range - 1), arr[index]));
            } else {
               int range = i - st.peek() - 1;
               result.set(range - 1, Math.max(result.get(range - 1), arr[index]));
            }
         }
         // Push current index onto the stack
         st.push(i);
      }

      // Process remaining elements in the stack
      while (!st.isEmpty()) {
         int index = st.pop();
         if (st.isEmpty()) {
            int range = n;     // element is minimum for the entire array
            result.set(range - 1, Math.max(result.get(range - 1), arr[index]));
         } else {
            int range = n - st.peek() - 1;
            result.set(range - 1, Math.max(result.get(range - 1), arr[index]));
         }
      }

      // Update the result list to ensure smaller window sizes have the maximum of minimums
      for (int i = n - 2; i >= 0; i--) {
         result.set(i, Math.max(result.get(i), result.get(i + 1)));
      }

      return result;
   }
}

/* Dry Run:
 * Input: arr = [10, 20, 30, 50, 10, 70, 30]
 * n = 7, result = [0, 0, 0, 0, 0, 0, 0], stack = []
 *
 * Iteration i = 0:
 * - Stack is empty, push index 0. stack = [0]
 *
 * Iteration i = 1:
 * - arr[st.peek()] = 10 <= 20, push index 1. stack = [0, 1]
 *
 * Iteration i = 2:
 * - arr[st.peek()] = 20 <= 30, push index 2. stack = [0, 1, 2]
 *
 * Iteration i = 3:
 * - arr[st.peek()] = 30 <= 50, push index 3. stack = [0, 1, 2, 3]
 *
 * Iteration i = 4:
 * - arr[st.peek()] = 50 > 10, pop index 3.
 *    stack becomes [0, 1, 2], window size = 4 - 2 - 1 = 1, update result[0] = max(0, 50) = 50.
 * - arr[st.peek()] = 30 > 10, pop index 2.
 *    stack becomes [0, 1], window size = 4 - 1 - 1 = 2, update result[1] = max(0, 30) = 30.
 * - arr[st.peek()] = 20 > 10, pop index 1.
 *    stack becomes [0], window size = 4 - 0 - 1 = 3, update result[2] = max(0, 20) = 20.
 * - Now, arr[st.peek()] = 10 <= 10, push index 4. stack = [0, 4]
 *
 * Iteration i = 5:
 * - arr[st.peek()] = 10 <= 70, push index 5. stack = [0, 4, 5]
 *
 * Iteration i = 6:
 * - arr[st.peek()] = 70 > 30, pop index 5.
 *    stack becomes [0, 4], window size = 6 - 4 - 1 = 1, update result[0] = max(50, 70) = 70.
 * - Now, arr[st.peek()] = 10 <= 30, push index 6. stack = [0, 4, 6]
 *
 * Process remaining stack:
 * - Pop index 6, stack becomes [0, 4], window size = 7 - 4 - 1 = 2, update result[1] = max(30, 30) = 30.
 * - Pop index 4, stack becomes [0], window size = 7 - 0 - 1 = 6, update result[5] = max(0, 10) = 10.
 * - Pop index 0, stack becomes empty, window size = 7, update result[6] = max(0, 10) = 10.
 *
 * Result before final update: [70, 30, 20, 0, 0, 10, 10]
 * Final loop (backward update):
 * - i = 5: result[5] = max(10, 10) = 10.
 * - i = 4: result[4] = max(0, 10) = 10.
 * - i = 3: result[3] = max(0, 10) = 10.
 * - i = 2: result[2] = max(20, 10) = 20.
 * - i = 1: result[1] = max(30, 20) = 30.
 * - i = 0: result[0] = max(70, 30) = 70.
 *
 * Final Output: [70, 30, 20, 10, 10, 10, 10]
 */
