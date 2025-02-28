/*
 * Evaluation of Postfix Expression
 *
 * You are given an array of strings arr that represents a valid arithmetic expression written in Reverse Polish Notation (Postfix Notation). Your task is to evaluate the expression and return an integer representing its value.
 *
 * Key Details:
 *
 * The valid operators are '+', '-', '*', and '/'.
 * Each operand is guaranteed to be a valid integer or another expression.
 * The division operation between two integers always rounds the result towards zero, discarding any fractional part.
 * No division by zero will occur in the input.
 * The input is a valid arithmetic expression in Reverse Polish Notation.
 * The result of the expression and all intermediate calculations will fit in a 32-bit signed integer.
 * Examples:
 *
 * Input: arr = ["2", "3", "1", "*", "+", "9", "-"]
 * Output: -4
 * Explanation: If the expression is converted into an infix expression, it will be 2 + (3 * 1) – 9 = 5 – 9 = -4.
 * Input: arr = ["100", "200", "+", "2", "/", "5", "*", "7", "+"]
 * Output: 757
 * Explanation: If the expression is converted into an infix expression, it will be ((100 + 200) / 2) * 5 + 7  = 150 * 5 + 7 = 757.
 * Constraints:
 *
 * 1 <= arr.size() <= 10^5
 * arr[i] is either an operator: "+", "-", "*", or "/", or an integer in the range [-10^4, 10^4]
 */

/************************************************************ C++ ************************************************/

// Approach: Use a stack to evaluate the postfix expression by processing each token; push numbers and compute results when encountering operators.
// TC: O(n) because each token is processed exactly once.
// SC: O(n) due to the stack used to store operands.
class Solution {
public:
   int evaluate(vector<string>& arr) {
      stack<int> st;   // Initialize a stack to store operands

      // Iterate through each token in the array
      for (string&token: arr) {
         // If token is an operator, perform the operation using the top two numbers from the stack
         if (token == "+" || token == "-" || token == "*" || token == "/") {
            int b = st.top();  // Pop the second operand
            st.pop();
            int a = st.top();  // Pop the first operand
            st.pop();
            int result;        // Variable to store the result of the operation
            if (token == "+") {
               result = a + b; // Addition
            } else if (token == "-") {
               result = a - b; // Subtraction
            } else if (token == "*") {
               result = a * b; // Multiplication
            } else if (token == "/") {
               result = a / b; // Division (truncates towards zero)
            }
            st.push(result);   // Push the result back onto the stack
         } else {
            // If token is an operand, convert it to an integer and push it onto the stack
            st.push(stoi(token));
         }
      }
      // The final result is the only element left on the stack
      return st.top();
   }
};

/*
 * Dry Run:
 * Input: arr = ["2", "3", "1", "*", "+", "9", "-"]
 * Process:
 *   Push 2 -> Stack: [2]
 *   Push 3 -> Stack: [2, 3]
 *   Push 1 -> Stack: [2, 3, 1]
 *   Encounter "*": Pop 1 and 3, compute 3*1 = 3, push 3 -> Stack: [2, 3]
 *   Encounter "+": Pop 3 and 2, compute 2+3 = 5, push 5 -> Stack: [5]
 *   Push 9 -> Stack: [5, 9]
 *   Encounter "-": Pop 9 and 5, compute 5-9 = -4, push -4 -> Stack: [-4]
 * Output: -4
 */

/************************************************************ JAVA ************************************************/

// Approach: Use a stack to evaluate the postfix expression by processing each token; push numbers and compute results when encountering operators.
// TC: O(n) because each token is processed exactly once.
// SC: O(n) due to the stack used to store operands.
class Solution {
   public int evaluate(String[] arr) {
      Stack<Integer> st = new Stack<>();   // Initialize a stack to store operands

      // Iterate through each token in the input array
      for (String token : arr) {
         // If token is an operator, perform the operation using the top two numbers from the stack
         if (token.equals("+") || token.equals("-") || token.equals("*") || token.equals("/")) {
            int b      = st.pop(); // Pop the second operand
            int a      = st.pop(); // Pop the first operand
            int result = 0;        // Variable to store the result of the operation
            if (token.equals("+")) {
               result = a + b;     // Addition
            } else if (token.equals("-")) {
               result = a - b;     // Subtraction
            } else if (token.equals("*")) {
               result = a * b;     // Multiplication
            } else if (token.equals("/")) {
               result = a / b;     // Division (truncates towards zero)
            }
            st.push(result);       // Push the computed result back onto the stack
         } else {
            // If token is an operand, parse it to an integer and push it onto the stack
            st.push(Integer.parseInt(token));
         }
      }
      // The final evaluated result is the only element remaining on the stack
      return st.peek();
   }
}

/*
 * Dry Run:
 * Input: arr = ["100", "200", "+", "2", "/", "5", "*", "7", "+"]
 * Process:
 *   Push 100 -> Stack: [100]
 *   Push 200 -> Stack: [100, 200]
 *   Encounter "+": Pop 200 and 100, compute 100+200 = 300, push 300 -> Stack: [300]
 *   Push 2 -> Stack: [300, 2]
 *   Encounter "/": Pop 2 and 300, compute 300/2 = 150, push 150 -> Stack: [150]
 *   Push 5 -> Stack: [150, 5]
 *   Encounter "*": Pop 5 and 150, compute 150*5 = 750, push 750 -> Stack: [750]
 *   Push 7 -> Stack: [750, 7]
 *   Encounter "+": Pop 7 and 750, compute 750+7 = 757, push 757 -> Stack: [757]
 * Output: 757
 */
