/*
 * Parenthesis Checker
 *
 * Given a string s, composed of different combinations of '(' , ')', '{', '}', '[', ']', verify the validity of the arrangement.
 * An input string is valid if:
 *
 *       1. Open brackets must be closed by the same type of brackets.
 *       2. Open brackets must be closed in the correct order.
 *
 * Examples :
 *
 * Input: s = "[{()}]"
 * Output: true
 * Explanation: All the brackets are well-formed.
 *
 * Input: s = "[()()]{}"
 * Output: true
 * Explanation: All the brackets are well-formed.
 *
 * Input: s = "([]"
 * Output: False
 * Explanation: The expression is not balanced as there is a missing ')' at the end.
 *
 * Input: s = "([{]})"
 * Output: False
 * Explanation: The expression is not balanced as there is a closing ']' before the closing '}'.
 *
 * Constraints:
 * 1 ≤ s.size() ≤ 10^6
 * s[i] ∈ {'{', '}', '(', ')', '[', ']'}
 */


// Approach: Use a stack to validate balanced brackets by pushing opening brackets and matching them with closing brackets.
// TC: O(n) because we traverse each character once.
// SC: O(n) in the worst-case scenario when all characters are opening brackets.
class Solution {
public:
   bool isBalanced(string& s) {
      // Initialize a stack to store opening brackets.
      stack<char> st;

      // Process each character in the string.
      for (char&ch : s) {
         // If stack is empty or current character is an opening bracket, push it.
         if (st.empty() || ch == '(' || ch == '{' || ch == '[') {
            st.push(ch);
            continue;
         }

         // If current character is a closing bracket, check for a matching opening bracket.
         if (ch == ')') {
            if (st.top() == '(') {
               st.pop();
            }else {
               return false;
            }
         } else if (ch == '}') {
            if (st.top() == '{') {
               st.pop();
            }else {
               return false;
            }
         } else if (ch == ']') {
            if (st.top() == '[') {
               st.pop();
            }else {
               return false;
            }
         }
      }
      // Return true if all brackets are matched (stack is empty), else false.
      return st.empty();
   }
};

/*
 * Dry Run
 * Input: s = "[{()}]"
 * Iteration 1: ch = '[' -> Stack is empty, push '['; Stack: ['[']
 * Iteration 2: ch = '{' -> Push '{'; Stack: ['[', '{']
 * Iteration 3: ch = '(' -> Push '('; Stack: ['[', '{', '(']
 * Iteration 4: ch = ')' -> Top is '(', pop '('; Stack: ['[', '{']
 * Iteration 5: ch = '}' -> Top is '{', pop '{'; Stack: ['[']
 * Iteration 6: ch = ']' -> Top is '[', pop '['; Stack: []
 * Final: Stack is empty, hence the string is balanced.
 */

/************************************************************ JAVA ************************************************/

// Approach: Use a stack to validate balanced brackets by pushing opening brackets and matching them with closing brackets.
// TC: O(n) because we traverse each character once.
// SC: O(n) in the worst-case scenario when all characters are opening brackets.
class Solution {
   static boolean isBalanced(String s) {
      // Create a stack to store characters.
      Stack<Character> stack = new Stack<>();

      // Process each character in the string.
      for (int i = 0; i < s.length(); i++) {
         char ch = s.charAt(i);

         // If the stack is empty or the current character is an opening bracket, push it onto the stack.
         if (stack.empty() || ch == '(' || ch == '{' || ch == '[') {
            stack.push(ch);
            continue;
         }

         // If the current character is a closing bracket, check for a matching opening bracket.
         if (ch == ')') {
            if (!stack.empty() && stack.peek() == '(') {
               stack.pop();
            } else {
               return false;
            }
         } else if (ch == '}') {
            if (!stack.empty() && stack.peek() == '{') {
               stack.pop();
            } else {
               return false;
            }
         } else if (ch == ']') {
            if (!stack.empty() && stack.peek() == '[') {
               stack.pop();
            } else {
               return false;
            }
         }
      }
      // Return true if all brackets are matched (stack is empty), otherwise return false.
      return stack.empty();
   }
}

/*
 * Dry Run
 * Input: s = "[{()}]"
 * Iteration 1: ch = '[' -> Stack is empty, push '['; Stack: ['[']
 * Iteration 2: ch = '{' -> Push '{'; Stack: ['[', '{']
 * Iteration 3: ch = '(' -> Push '('; Stack: ['[', '{', '(']
 * Iteration 4: ch = ')' -> Top is '(', pop '('; Stack: ['[', '{']
 * Iteration 5: ch = '}' -> Top is '{', pop '{'; Stack: ['[']
 * Iteration 6: ch = ']' -> Top is '[', pop '['; Stack: []
 * Final: Stack is empty, hence the string is balanced.
 */
