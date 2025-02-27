/*
 * Get Min from Stack
 *
 * Given q queries, You task is to implement the following four functions for a stack:
 *
 * push(x) – Insert an integer x onto the stack.
 * pop() – Remove the top element from the stack.
 * peek() - Return the top element from the stack. If the stack is empty, return -1.
 * getMin() – Retrieve the minimum element from the stack in O(1) time. If the stack is empty, return -1.
 * Each query can be one of the following:
 * 1 x : Push x onto the stack.
 * 2 : Pop the top element from the stack.
 * 3: Return the top element from the stack. If the stack is empty, return -1.
 * 4: Return the minimum element from the stack.
 *
 * Examples:
 *
 * Input: q = 7, queries = [[1, 2], [1, 3], [3], [2], [4], [1, 1], [4]]
 * Output: [3, 2, 1]
 * Explanation:
 * push(2): Stack is [2]
 * push(3): Stack is [2, 3]
 * peek(): Top element is 3
 * pop(): Removes 3, stack is [2]
 * getMin(): Minimum element is 2
 * push(1): Stack is [2, 1]
 * getMin(): Minimum element is 1
 *
 * Input: q = 4, queries = [[1, 4], [1, 2], [4], [3]]
 * Output: [2, 2]
 * Explanation:
 * push(4): Stack is [4]
 * push(2): Stack is [4, 2]
 * getMin(): Minimum element is 2
 * peek(): Top element is 2
 *
 * Input: q = 5, queries = [[1, 10], [4], [1, 5], [4], [2]]
 * Output: [10, 5]
 * Explanation:
 * push(10): Stack is [10]
 * getMin(): Minimum element is 10
 * push(5): Stack is [10, 5]
 * getMin(): Minimum element is 5
 * pop(): Removes 5, stack is [10]
 *
 * Constraints:
 * 1 <= q <= 10^5
 * 0 <= values on the stack <= 10^9
 */

/************************************************************ C++ ************************************************/

// Approach 1: Use a stack of pairs where each pair stores {element, current minimum} to achieve O(1) operations.
// TC: O(1) per operation (push, pop, peek, getMin) since each does constant work.
// SC: O(n) in the worst-case for storing n elements along with their current minimum.
class Solution {
public:
   // Stack stores pairs: {element, current minimum at that point}
   stack<pair<int, int> > st;

   // Constructor
   Solution() {
      // No initialization needed as st is automatically initialized
   }

   // Add an element to the top of Stack
   void push(int val) {
      // If stack is empty, push the element as both value and minimum.
      if (st.empty()) {
         st.push({ val, val });
      } else {
         // Else, push element with the minimum between current value and the previous minimum.
         st.push({ val, min(val, st.top().second) });
      }
   }

   // Remove the top element from the Stack
   void pop() {
      // Only pop if the stack is not empty.
      if (!st.empty()) {
         st.pop();
      }
   }

   // Returns top element of the Stack
   int peek() {
      // Return top element if available; otherwise return -1.
      return st.empty() ? -1 : st.top().first;
   }

   // Finds minimum element of Stack
   int getMin() {
      // Return the current minimum if available; otherwise return -1.
      return st.empty() ? -1 : st.top().second;
   }
};

/*
 * Dry Run:
 * ----------
 * push(2): Stack becomes [(2,2)]
 * push(3): Stack becomes [(2,2), (3, min(3,2)=2)]
 * peek(): returns 3 (top element from (3,2))
 * pop(): removes (3,2); Stack becomes [(2,2)]
 * getMin(): returns 2 (minimum from (2,2))
 * push(1): Stack becomes [(2,2), (1, min(1,2)=1)]
 * getMin(): returns 1 (minimum from (1,1))
 * ----------
 */

// Approach 2: Use one stack to store encoded values and a variable minElement to track the current minimum.
// TC: O(1) per operation since each push, pop, peek, and getMin operation does constant work.
// SC: O(n) in worst-case to store n elements.
class Solution {
public:
   // Stack to store encoded values (using long long to avoid overflow)
   stack<long long> st;
   // Variable to store the current minimum element
   long long minElement;

   // Constructor
   Solution() {
      // No explicit initialization for minElement needed here
   }

   // Add an element to the top of Stack
   void push(int x) {
      if (st.empty()) {
         st.push(x);
         minElement = x;
      } else {
         if (x < minElement) {
            // Push encoded value and update minElement
            st.push(2LL * x - minElement);
            minElement = x;
         } else {
            st.push(x);
         }
      }
   }

   // Remove the top element from the Stack
   void pop() {
      if (st.empty()) {
         return;
      }
      long long top = st.top();
      st.pop();
      if (top < minElement) {
         // Decode the previous minimum
         minElement = 2 * minElement - top;
      }
   }

   // Returns top element of the Stack
   int peek() {
      if (st.empty()) {
         return -1;
      }
      long long top = st.top();
      // If the top value is encoded, the actual top element is minElement
      if (top < minElement) {
         return (int)minElement;
      } else {
         return (int)top;
      }
   }

   // Finds minimum element of the Stack
   int getMin() {
      if (st.empty()) {
         return -1;
      }
      return (int)minElement;
   }
};

/*
 * Dry Run:
 * ----------
 * push(2): Stack becomes [2], minElement = 2
 * push(3): 3 >= minElement, so Stack becomes [2, 3], minElement remains 2
 * peek(): Top element is 3, returns 3
 * pop(): Removes 3; Stack becomes [2], minElement remains 2
 * getMin(): Returns 2 as minElement
 * push(1): 1 < minElement, so push encoded value = 2*1 - 2 = 0; Stack becomes [2, 0], minElement becomes 1
 * getMin(): Returns 1 as minElement
 * ----------
 */

/************************************************************ JAVA ************************************************/

// Approach 1: Use a stack (java.util.Stack) of int arrays where each array holds {element, current minimum} for O(1) operations.
// TC: O(1) per operation (push, pop, peek, getMin) as each does constant work.
// SC: O(n) in the worst-case for storing n elements along with their current minimum.
class Solution {
   // Stack to store pairs as int arrays: [element, current minimum]
   private Stack<int[]> st;

   // Constructor initializes the stack.
   public Solution() {
      st = new Stack<>();
   }

   // Add an element to the top of Stack
   public void push(int x) {
      if (st.isEmpty()) {
         // If empty, the element is the current minimum.
         st.push(new int[]{ x, x });
      } else {
         // Else, the current minimum is the minimum of x and the current minimum at the top.
         int currentMin = st.peek()[1];
         st.push(new int[]{ x, Math.min(x, currentMin) });
      }
   }

   // Remove the top element from the Stack
   public void pop() {
      // Only pop if the stack is not empty.
      if (!st.isEmpty()) {
         st.pop();
      }
   }

   // Returns top element of the Stack
   public int peek() {
      // Return top element if available; otherwise return -1.
      return st.isEmpty() ? -1 : st.peek()[0];
   }

   // Finds minimum element of the Stack
   public int getMin() {
      // Return the current minimum if available; otherwise return -1.
      return st.isEmpty() ? -1 : st.peek()[1];
   }
}

/*
 * Dry Run:
 * ----------
 * push(2): Stack becomes [[2,2]]
 * push(3): Stack becomes [[2,2], [3, min(3,2)=2]]
 * peek(): returns 3 (top element from [3,2])
 * pop(): removes top element; Stack becomes [[2,2]]
 * getMin(): returns 2 (minimum from [2,2])
 * push(1): Stack becomes [[2,2], [1, min(1,2)=1]]
 * getMin(): returns 1 (minimum from [1,1])
 * ----------
 */

// Approach 2: Use one stack to store encoded values and a variable minElement to track the current minimum.
// TC: O(1) per operation since each push, pop, peek, and getMin operation does constant work.
// SC: O(n) in worst-case to store n elements.
class Solution {
   // Stack to store encoded values
   private Stack<Long> st;
   // Variable to store the current minimum element
   private long minElement;

   // Constructor to initialize the stack
   public Solution() {
      st = new Stack<>();
   }

   // Add an element to the top of Stack
   public void push(int x) {
      if (st.isEmpty()) {
         st.push((long)x);
         minElement = x;
      } else {
         if (x < minElement) {
            // Push encoded value and update minElement
            st.push(2L * x - minElement);
            minElement = x;
         } else {
            st.push((long)x);
         }
      }
   }

   // Remove the top element from the Stack
   public void pop() {
      if (st.isEmpty()) {
         return;
      }
      long top = st.peek();
      st.pop();
      if (top < minElement) {
         // Decode the previous minimum
         minElement = 2 * minElement - top;
      }
   }

   // Returns top element of the Stack
   public int peek() {
      if (st.isEmpty()) {
         return -1;
      }
      long top = st.peek();
      // If the top value is encoded, the actual top element is minElement
      if (top < minElement) {
         return (int)minElement;
      } else {
         return (int)top;
      }
   }

   // Finds minimum element of the Stack
   public int getMin() {
      if (st.isEmpty()) {
         return -1;
      }
      return (int)minElement;
   }
}

/*
 * Dry Run:
 * ----------
 * push(2): Stack becomes [2], minElement = 2
 * push(3): 3 >= minElement, so Stack becomes [2, 3], minElement remains 2
 * peek(): Top element is 3, returns 3
 * pop(): Removes 3; Stack becomes [2], minElement remains 2
 * getMin(): Returns 2 as minElement
 * push(1): 1 < minElement, so push encoded value = 2*1 - 2 = 0; Stack becomes [2, 0], minElement becomes 1
 * getMin(): Returns 1 as minElement
 * ----------
 */
