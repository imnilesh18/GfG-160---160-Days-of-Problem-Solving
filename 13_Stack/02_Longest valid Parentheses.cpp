/*
 * Longest valid Parentheses
 *
 * Given a string s consisting of opening and closing parenthesis '(' and ')'. Find the length of the longest valid parenthesis substring.
 * A parenthesis string is valid if:
 * For every opening parenthesis, there is a closing parenthesis.
 * The closing parenthesis must be after its opening parenthesis.
 *
 * Examples :
 * Input: s = "((()"
 * Output: 2
 * Explanation: The longest valid parenthesis substring is "()".
 *
 * Input: s = ")()())"
 * Output: 4
 * Explanation: The longest valid parenthesis substring is "()()".
 *
 * Input: s = "())()"
 * Output: 2
 * Explanation: The longest valid parenthesis substring is "()".
 *
 * Constraints:
 * 1 ≤ s.size() ≤ 10^6
 * s consists of '(' and ')' only
 */

/************************************************************ C++ ************************************************/

// Approach: Use a stack to store indices of unmatched parentheses and compute valid substring lengths by taking the difference between the current index and the index at the top of the stack.
// TC: O(n) - We traverse the string once.
// SC: O(n) - In the worst-case, the stack may store all indices (when all characters are '(').
class Solution {
public:
   int maxLength(string& s) {
      // Initialize stack with -1 to serve as the base index for valid substrings
      stack<int> st;

      st.push(-1);

      // Variable to store the maximum valid substring length found
      int max_len = 0;

      // Traverse each character in the string
      for (int i = 0; i < s.length(); i++) {
         if (s[i] == '(') {
            // If the character is '(', push its index onto the stack
            st.push(i);
         } else {
            // If the character is ')', pop the top element from the stack
            st.pop();
            if (st.empty()) {
               // If the stack becomes empty, push the current index to set a new base
               st.push(i);
            } else {
               // Calculate valid substring length and update max_len if it's longer than current max
               max_len = max(max_len, i - st.top());
            }
         }
      }

      return max_len;
   }
};

/*
 * DRY RUN:
 * Input: s = ")()())"
 * Initial stack: [-1]
 * i = 0, char = ')': pop stack -> stack becomes empty, then push 0 -> stack: [0]
 * i = 1, char = '(': push index 1 -> stack: [0, 1]
 * i = 2, char = ')': pop stack (removes index 1) -> stack: [0], valid length = 2 - 0 = 2, max_len = 2
 * i = 3, char = '(': push index 3 -> stack: [0, 3]
 * i = 4, char = ')': pop stack (removes index 3) -> stack: [0], valid length = 4 - 0 = 4, max_len = 4
 * i = 5, char = ')': pop stack (removes index 0) -> stack becomes empty, then push 5 -> stack: [5]
 * Final max_len = 4
 */

/************************************************************ JAVA ************************************************/

// Approach: Use a stack to store indices of unmatched parentheses and compute valid substring lengths by taking the difference between the current index and the index at the top of the stack.
// TC: O(n) - We iterate over the string once.
// SC: O(n) - In the worst-case, the stack holds all indices when all characters are '('.
class Solution {
   static int maxLength(String s) {
      // Initialize a stack with -1 to serve as the base index for valid substring calculations
      Stack<Integer> st = new Stack<>();

      st.push(-1);

      // Variable to store the maximum valid substring length found
      int max_len = 0;

      // Traverse each character in the string
      for (int i = 0; i < s.length(); i++) {
         char ch = s.charAt(i);
         if (ch == '(') {
            // If the character is '(', push its index onto the stack
            st.push(i);
         } else {
            // If the character is ')', pop the top element from the stack
            st.pop();
            if (st.isEmpty()) {
               // If the stack is empty, push the current index as the new base
               st.push(i);
            } else {
               // Calculate valid substring length and update max_len if it's larger than the current max
               max_len = Math.max(max_len, i - st.peek());
            }
         }
      }

      return max_len;
   }
}

/*
 * DRY RUN:
 * Input: s = ")()())"
 * Initial stack: [-1]
 * i = 0, char = ')': pop stack -> stack becomes empty, then push 0 -> stack: [0]
 * i = 1, char = '(': push index 1 -> stack: [0, 1]
 * i = 2, char = ')': pop stack (removes index 1) -> stack: [0], valid length = 2 - 0 = 2, max_len = 2
 * i = 3, char = '(': push index 3 -> stack: [0, 3]
 * i = 4, char = ')': pop stack (removes index 3) -> stack: [0], valid length = 4 - 0 = 4, max_len = 4
 * i = 5, char = ')': pop stack (removes index 0) -> stack becomes empty, then push 5 -> stack: [5]
 * Final max_len = 4
 */
