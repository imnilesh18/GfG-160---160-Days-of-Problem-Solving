/*
 * Histogram Max Rectangular Area
 *
 * You are given a histogram represented by an array arr, where each element of the array denotes the height of the bars in the histogram. All bars have the same width of 1 unit.
 *
 * Your task is to find the largest rectangular area possible in the given histogram, where the rectangle can be formed using a number of contiguous bars.
 *
 * Examples:
 *
 * Input: arr[] = [60, 20, 50, 40, 10, 50, 60]
 * Largest-Rectangular-Area-in-a-Histogram
 * Output: 100
 * Explanation: We get the maximum by picking bars highlighted above in green (50, and 60). The area is computed (smallest height) * (no. of the picked bars) = 50 * 2 = 100.
 *
 * Input: arr[] = [3, 5, 1, 7, 5, 9]
 * Output: 15
 * Explanation:  We get the maximum by picking bars 7, 5 and 9. The area is computed (smallest height) * (no. of the picked bars) = 5 * 3 = 15.
 *
 * Input: arr[] = [3]
 * Output: 3
 * Explanation: In this example the largest area would be 3 of height 3 and width 1.
 *
 * Constraints:
 * 1 ≤ arr.size() ≤ 10^5
 * 0 ≤ arr[i] ≤ 10^4
 */

/************************************************************ C++ ************************************************/

// Approach: Use two stacks to compute the previous and next smaller element indices for each bar, then calculate the area as height * (next - previous - 1).
// TC: O(n) - Each element is pushed and popped at most once in the stack.
// SC: O(n) - Extra space is used for stacks and auxiliary arrays.
class Solution {
public:
   int getMaxArea(vector<int>&arr) {
      int         n = arr.size();
      vector<int> prevSmaller(n), nextSmaller(n);
      int         maxArea = 0;
      stack<int>  s;

      // Compute Previous Smaller Elements for each bar
      for (int i = 0; i < n; i++) {
         // Pop elements until finding a bar lower than arr[i]
         while (!s.empty() && arr[s.top()] >= arr[i]) {
            s.pop();
         }
         // If stack is empty, no previous smaller exists; else top of stack is the previous smaller index
         prevSmaller[i] = s.empty() ? -1 : s.top();
         s.push(i);
      }

      // Clear the stack for next computation
      while (!s.empty()) {
         s.pop();
      }

      // Compute Next Smaller Elements for each bar (traversing from right to left)
      for (int i = n - 1; i >= 0; i--) {
         // Pop elements until finding a bar lower than arr[i]
         while (!s.empty() && arr[s.top()] >= arr[i]) {
            s.pop();
         }
         // If stack is empty, no next smaller exists; else top of stack is the next smaller index
         nextSmaller[i] = s.empty() ? n : s.top();
         s.push(i);
      }

      // Calculate the maximum rectangular area for each bar using its previous and next smaller indices
      for (int i = 0; i < n; i++) {
         int width = nextSmaller[i] - prevSmaller[i] - 1; // Width of rectangle with arr[i] as the smallest bar
         int area  = arr[i] * width;                      // Area using current bar's height
         maxArea = max(maxArea, area);                    // Update maximum area if needed
      }

      return maxArea;
   }
};

/*
 * Dry Run:
 * For arr[] = [60, 20, 50, 40, 10, 50, 60]:
 * Index 0: height=60, prevSmaller=-1, nextSmaller=1, width=1, area=60
 * Index 1: height=20, prevSmaller=-1, nextSmaller=4, width=4, area=80
 * Index 2: height=50, prevSmaller=1, nextSmaller=3, width=1, area=50
 * Index 3: height=40, prevSmaller=1, nextSmaller=4, width=2, area=80
 * Index 4: height=10, prevSmaller=-1, nextSmaller=7, width=7, area=70
 * Index 5: height=50, prevSmaller=4, nextSmaller=7, width=2, area=100
 * Index 6: height=60, prevSmaller=5, nextSmaller=7, width=1, area=60
 * Maximum Area = 100
 */

/************************************************************ JAVA ************************************************/

// Approach: Use two stacks to compute the previous and next smaller element indices for each bar, then calculate the area as height * (next - previous - 1).
// TC: O(n) - Each element is processed once in both previous and next smaller computations.
// SC: O(n) - Extra space is used for stacks and auxiliary arrays.
class Solution {
   public static int getMaxArea(int arr[]) {
      int n = arr.length;
      int[] prevSmaller = new int[n];
      int[] nextSmaller = new int[n];
      int maxArea = 0;

      Stack<Integer> stack = new Stack<>();

      // Compute Previous Smaller Elements for each bar
      for (int i = 0; i < n; i++) {
         // Pop elements until a bar smaller than arr[i] is found
         while (!stack.isEmpty() && arr[stack.peek()] >= arr[i]) {
            stack.pop();
         }
         // If stack is empty, no previous smaller exists; otherwise, top of stack is the previous smaller index
         prevSmaller[i] = stack.isEmpty() ? -1 : stack.peek();
         stack.push(i);
      }

      // Clear the stack for next computation
      while (!stack.isEmpty()) {
         stack.pop();
      }

      // Compute Next Smaller Elements for each bar (traversing from right to left)
      for (int i = n - 1; i >= 0; i--) {
         // Pop elements until a bar smaller than arr[i] is found
         while (!stack.isEmpty() && arr[stack.peek()] >= arr[i]) {
            stack.pop();
         }
         // If stack is empty, no next smaller exists; otherwise, top of stack is the next smaller index
         nextSmaller[i] = stack.isEmpty() ? n : stack.peek();
         stack.push(i);
      }

      // Calculate the maximum rectangular area using the computed indices
      for (int i = 0; i < n; i++) {
         int width = nextSmaller[i] - prevSmaller[i] - 1; // Width of the rectangle with arr[i] as the smallest bar
         int area  = arr[i] * width;                      // Area using current bar's height
         maxArea = Math.max(maxArea, area);               // Update maximum area if current area is larger
      }

      return maxArea;
   }
}

/*
 * Dry Run:
 * For arr[] = [60, 20, 50, 40, 10, 50, 60]:
 * Index 0: height=60, prevSmaller=-1, nextSmaller=1, width=1, area=60
 * Index 1: height=20, prevSmaller=-1, nextSmaller=4, width=4, area=80
 * Index 2: height=50, prevSmaller=1, nextSmaller=3, width=1, area=50
 * Index 3: height=40, prevSmaller=1, nextSmaller=4, width=2, area=80
 * Index 4: height=10, prevSmaller=-1, nextSmaller=7, width=7, area=70
 * Index 5: height=50, prevSmaller=4, nextSmaller=7, width=2, area=100
 * Index 6: height=60, prevSmaller=5, nextSmaller=7, width=1, area=60
 * Maximum Area = 100
 */
