/*
 * Add Binary Strings
 *
 * Given two binary strings s1 and s2 consisting of only 0s and 1s. Find the resultant string after adding the two Binary Strings.
 * Note: The input strings may contain leading zeros but the output string should not have any leading zeros.
 *
 * Input: s1 = "1101", s2 = "111"
 * Output: 10100
 * Explanation:
 * 1101
 + 111
 + 10100
 +
 + Input: s1 = "00100", s2 = "010"
 + Output: 110
 + Explanation:
 + 100
 +  10
 + 110
 +
 + Constraints:
 + 1 ≤s1.size(), s2.size()≤ 10^6
 */

/************************************************************ C++ ************************************************/

// T.C: O(n1 + n2) where n1 is length of s1 string and n2 is length of s2 string
// S.C: O(1)
class Solution {
public:
   string addBinary(string& s1, string& s2){
      int    n1 = s1.length();
      int    n2 = s2.length();
      int    i = 0, carry = 0;
      string ans = "";

      while (i < n1 || i < n2 || carry != 0) {
         int x = (i < n1 && s1[n1 - i - 1] == '1') ? 1 : 0; // Get the binary digit from s1
         int y = (i < n2 && s2[n2 - i - 1] == '1') ? 1 : 0; // Get the binary digit from s2

         int sum = x + y + carry;                           // Sum of both digits and carry
         ans   = char((sum % 2) + '0') + ans;               // Prepend the binary digit to the result
         carry = sum / 2;                                   // Update carry for the next iteration
         i++;
      }
      // Remove leading zeros from the result, if any
      while (ans.length() > 1 && ans[0] == '0') {
         ans.erase(0, 1);
      }

      return ans;
   }
};

/************************************************************ JAVA ************************************************/

// T.C: O(n1 + n2) where n1 is length of s1 string and n2 is length of s2 string
// S.C: O(1)
class Solution {
   public String addBinary(String s1, String s2){
      int           n1 = s1.length();
      int           n2 = s2.length();
      int           i = 0, carry = 0;
      StringBuilder ans = new StringBuilder();   // Use StringBuilder for efficient string manipulation

      // Process the binary strings from the least significant digit
      while (i < n1 || i < n2 || carry != 0) {
         int x = (i < n1 && s1.charAt(n1 - i - 1) == '1') ? 1 : 0; // Get the binary digit from s1
         int y = (i < n2 && s2.charAt(n2 - i - 1) == '1') ? 1 : 0; // Get the binary digit from s2

         int sum = x + y + carry;                                  // Sum of both digits and carry
         ans.append(sum % 2);                                      // Append the current binary digit to the result
         carry = sum / 2;                                          // Update carry for the next iteration
         i++;
      }

      // Reverse the result since we built it backwards
      ans.reverse();

      // Remove leading zeros, if any
      while (ans.length() > 1 && ans.charAt(0) == '0') {
         ans.deleteCharAt(0);
      }

      return ans.toString();   // Convert StringBuilder to String
   }
}
