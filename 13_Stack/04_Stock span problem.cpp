/*
 * Stock span problem
 *
 * The stock span problem is a financial problem where we have a series of daily price quotes for a stock and we need to calculate the span of stock price for all days. The span arr[i] of the stocks price on a given day i is defined as the maximum number of consecutive days just before the given day, for which the price of the stock on the given day is less than or equal to its price on the current day.
 *
 * Examples:
 *
 * Input: arr[] = [100, 80, 60, 70, 60, 75, 85]
 * Output: [1, 1, 1, 2, 1, 4, 6]
 * Explanation: Traversing the given input span 100 is greater than equal to 100 and there are no more elements behind it so the span is 1, 80 is greater than equal to 80 and smaller than 100 so the span is 1, 60 is greater than equal to 60 and smaller than 80 so the span is 1, 70 is greater than equal to 60,70 and smaller than 80 so the span is 2 and so on.  Hence the output will be 1 1 1 2 1 4 6.
 *
 * Input: arr[] = [10, 4, 5, 90, 120, 80]
 * Output: [1, 1, 2, 4, 5, 1]
 * Explanation: Traversing the given input span 10 is greater than equal to 10 and there are no more elements behind it so the span is 1, 4 is greater than equal to 4 and smaller than 10 so the span is 1, 5 is greater than equal to 4,5 and smaller than 10 so the span is 2,  and so on. Hence the output will be 1 1 2 4 5 1.
 *
 * Constraints:
 * 1 ≤ arr.size()≤ 10^5
 * 1 ≤ arr[i] ≤ 10^5
 */

/************************************************************ C++ ************************************************/

// Approach: Use a stack to store pairs of (price, span) and for each price, pop elements until a higher price is found, summing their spans.
// Time Complexity: O(n) as each element is pushed and popped at most once.
// Space Complexity: O(n) for the stack and the span array.
class Solution {
public:
   vector<int> calculateSpan(vector<int>& arr) {
      int                    n = arr.size();
      vector<int>            span(n, 0); // result vector to store span for each day
      stack<pair<int, int> > st;         // stack to store pairs: (price, span)

      for (int i = 0; i < n; i++) {
         int currSpan = 1;    // initialize span for current day

         // while the stack is not empty and the current price is greater than or equal to the price at the top of the stack
         while (!st.empty() && st.top().first <= arr[i]) {
            currSpan += st.top().second; // add the span of the popped element to current span
            st.pop();                    // remove the element as it is covered in current span
         }
         st.push({ arr[i], currSpan });  // push the current price and its span into the stack
         span[i] = currSpan;             // store the computed span for the current day
      }
      return span;                       // return the final span array
   }
};

/*
 * Dry Run
 * Input: [100, 80, 60, 70, 60, 75, 85]
 * i=0: currSpan = 1; stack empty; push (100, 1); span = [1]
 * i=1: currSpan = 1; top (100,1) > 80; push (80,1); span = [1, 1]
 * i=2: currSpan = 1; top (80,1) > 60; push (60,1); span = [1, 1, 1]
 * i=3: currSpan = 1; top (60,1) <= 70; pop -> currSpan becomes 2; now top (80,1) > 70; push (70,2); span = [1, 1, 1, 2]
 * i=4: currSpan = 1; top (70,2) > 60; push (60,1); span = [1, 1, 1, 2, 1]
 * i=5: currSpan = 1; top (60,1) <= 75; pop -> currSpan becomes 2; new top (70,2) <= 75; pop -> currSpan becomes 4; now top (80,1) > 75; push (75,4); span = [1, 1, 1, 2, 1, 4]
 * i=6: currSpan = 1; top (75,4) <= 85; pop -> currSpan becomes 5; new top (80,1) <= 85; pop -> currSpan becomes 6; stack empty; push (85,6); span = [1, 1, 1, 2, 1, 4, 6]
 * End Dry Run
 */

/************************************************************ JAVA ************************************************/

// Approach: Use a stack to store pairs (price, span) and compute each day's span by accumulating spans of consecutive lower or equal prices.
// Time Complexity: O(n) since every element is processed once.
// Space Complexity: O(n) for the stack and the result list.

// Helper class to store pair of (price, span)
class Pair {
   int price;
   int span;
   public Pair(int price, int span) {
      this.price = price;
      this.span  = span;
   }
}

class Solution {
   public ArrayList<Integer> calculateSpan(int[] arr) {
      int n = arr.length;
      ArrayList<Integer> span = new ArrayList<>(n); // result list to store span for each day
      Stack<Pair>        st   = new Stack<>();      // stack to store pairs: (price, span)

      for (int i = 0; i < n; i++) {
         int currSpan = 1;    // initialize span for the current day

         // while stack is not empty and the price at the top is less than or equal to current price
         while (!st.isEmpty() && st.peek().price <= arr[i]) {
            currSpan += st.peek().span;       // add the span from the popped element to current span
            st.pop();                         // remove the element as its span is merged with the current day's span
         }
         st.push(new Pair(arr[i], currSpan)); // push the current price and its span into the stack
         span.add(currSpan);                  // add the computed span to the result list
      }
      return span;                            // return the list of spans
   }
}

/*
 * Dry Run
 * Input: [10, 4, 5, 90, 120, 80]
 * i=0: currSpan = 1; stack empty; push (10,1); span = [1]
 * i=1: currSpan = 1; top (10,1) > 4; push (4,1); span = [1, 1]
 * i=2: currSpan = 1; top (4,1) <= 5; pop -> currSpan becomes 2; now top (10,1) > 5; push (5,2); span = [1, 1, 2]
 * i=3: currSpan = 1; top (5,2) <= 90; pop -> currSpan becomes 3; new top (10,1) <= 90; pop -> currSpan becomes 4; stack empty; push (90,4); span = [1, 1, 2, 4]
 * i=4: currSpan = 1; top (90,4) <= 120; pop -> currSpan becomes 5; stack empty; push (120,5); span = [1, 1, 2, 4, 5]
 * i=5: currSpan = 1; top (120,5) > 80; push (80,1); span = [1, 1, 2, 4, 5, 1]
 * End Dry Run
 */
