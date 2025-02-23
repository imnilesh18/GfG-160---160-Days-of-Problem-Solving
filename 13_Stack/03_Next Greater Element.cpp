/*
 * Next Greater Element
 *
 * Given an array arr[ ] of integers, the task is to find the next greater element for each element of the array in order of their appearance in the array. Next greater element of an element in the array is the nearest element on the right which is greater than the current element.
 * If there does not exist next greater of current element, then next greater element for current element is -1. For example, next greater of the last element is always -1.
 *
 * Examples
 *
 * Input: arr[] = [1, 3, 2, 4]
 * Output: [3, 4, 4, -1]
 * Explanation: The next larger element to 1 is 3, 3 is 4, 2 is 4 and for 4, since it doesn't exist, it is -1.
 *
 * Input: arr[] = [6, 8, 0, 1, 3]
 * Output: [8, -1, 1, 3, -1]
 * Explanation: The next larger element to 6 is 8, for 8 there is no larger elements hence it is -1, for 0 it is 1 , for 1 it is 3 and then for 3 there is no larger element on right and hence -1.
 *
 * Input: arr[] = [10, 20, 30, 50]
 * Output: [20, 30, 50, -1]
 * Explanation: For a sorted array, the next element is next greater element also exxept for the last element.
 *
 * Input: arr[] = [50, 40, 30, 10]
 * Output: [-1, -1, -1, -1]
 * Explanation: There is no greater element for any of the elements in the array, so all are -1.
 *
 * Constraints:
 * 1 ≤ arr.size() ≤ 10^6
 * 0 ≤ arr[i] ≤ 10^9
 */

/************************************************************ C++ ************************************************/

// Approach: Traverse the array from right to left using a stack to keep track of the next greater element.
// TC: O(n) - each element is pushed and popped at most once.
// SC: O(n) - extra space for the stack and result vector.
class Solution {
public:
   // Function to find the next greater element for each element of the array.
   vector<int> nextLargerElement(vector<int>& arr) {
      int         n = arr.size();           // Get the size of the input array.
      stack<int>  st;                       // Stack to store potential next greater elements.
      vector<int> result(n, -1);            // Initialize result vector with -1 (default when no greater element exists).

      // Iterate from the last element to the first element.
      for (int i = n - 1; i >= 0; i--) {
         // Remove elements from the stack that are less than or equal to the current element.
         while (!st.empty() && st.top() <= arr[i]) {
            st.pop();                       // Pop elements that cannot be the next greater element.
         }
         // If the stack is not empty, the top element is the next greater element.
         if (!st.empty()) {
            result[i] = st.top();
         }
         // Push the current element onto the stack.
         st.push(arr[i]);
      }
      return result;                        // Return the result vector.
   }
};

/*
 * DRY RUN:
 *
 * Input: arr = [4, 5, 2, 25]
 * Iteration 1 (i = 3):
 *  Current element = 25, Stack = empty
 *  -> No greater element found, result[3] remains -1
 *  -> Push 25; Stack becomes [25]
 * Iteration 2 (i = 2):
 *  Current element = 2, Stack = [25]
 *  -> 25 > 2, so result[2] = 25
 *  -> Push 2; Stack becomes [25, 2]
 * Iteration 3 (i = 1):
 *  Current element = 5, Stack = [25, 2]
 *  -> Pop 2 (since 2 <= 5); Stack becomes [25]
 *  -> 25 > 5, so result[1] = 25
 *  -> Push 5; Stack becomes [25, 5]
 * Iteration 4 (i = 0):
 *  Current element = 4, Stack = [25, 5]
 *  -> 5 > 4, so result[0] = 5
 *  -> Push 4; Stack becomes [25, 5, 4]
 * Final Output: [5, 25, 25, -1]
 */

/************************************************************ JAVA ************************************************/

// Approach: Traverse the array from right to left using a stack to track potential next greater elements.
// TC: O(n) - Each element is pushed and popped at most once.
// SC: O(n) - Extra space is used for the stack and the result list.
class Solution {
   // Function to find the next greater element for each element of the array.
   public ArrayList<Integer> nextLargerElement(int[] arr) {
      int n = arr.length;                             // Get the number of elements in the input array.
      ArrayList<Integer> result = new ArrayList<>(n); // Initialize the result list with size n.

      // Initialize the result list with -1 for each element.
      for (int i = 0; i < n; i++) {
         result.add(-1);
      }

      Stack<Integer> stack = new Stack<>();    // Create a stack to store potential next greater elements.

      // Traverse the array from right to left.
      for (int i = n - 1; i >= 0; i--) {
         // Remove elements from the stack that are less than or equal to the current element.
         while (!stack.isEmpty() && stack.peek() <= arr[i]) {
            stack.pop();
         }
         // If the stack is not empty, the top element is the next greater element.
         if (!stack.isEmpty()) {
            result.set(i, stack.peek());
         }
         // Push the current element onto the stack.
         stack.push(arr[i]);
      }

      return result;    // Return the list containing next greater elements.
   }
}

/*
 * DRY RUN:
 *
 * Input: arr = [4, 5, 2, 25]
 * Iteration 1 (i = 3):
 *  Current element = 25, Stack = empty
 *  -> No greater element found, result[3] remains -1
 *  -> Push 25; Stack becomes [25]
 * Iteration 2 (i = 2):
 *  Current element = 2, Stack = [25]
 *  -> 25 > 2, so result[2] = 25
 *  -> Push 2; Stack becomes [25, 2]
 * Iteration 3 (i = 1):
 *  Current element = 5, Stack = [25, 2]
 *  -> Pop 2 (since 2 <= 5); Stack becomes [25]
 *  -> 25 > 5, so result[1] = 25
 *  -> Push 5; Stack becomes [25, 5]
 * Iteration 4 (i = 0):
 *  Current element = 4, Stack = [25, 5]
 *  -> 5 > 4, so result[0] = 5
 *  -> Push 4; Stack becomes [25, 5, 4]
 * Final Output: [5, 25, 25, -1]
 */
