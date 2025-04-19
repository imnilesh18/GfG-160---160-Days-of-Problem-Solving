/*
 * Maximum XOR of two numbers in an array
 *
 * Difficulty: Medium Accuracy: 50.0% Submissions: 19K+ Points: 4
 *
 * Given an array arr[] of non-negative integers of size n. Find the maximum possible XOR between two numbers present in the array.
 *
 * Examples:
 *
 * Input: arr[] = [25, 10, 2, 8, 5, 3]
 * Output: 28
 * Explanation: The maximum possible XOR is 5 ^ 25 = 28.
 *
 * Input: arr[] = [1, 2, 3, 4, 5, 6, 7]
 * Output: 7
 * Explanation : The maximum possible XOR is 1 ^ 6 = 7.
 *
 * Constraints:
 * 2 ≤ arr.size() ≤ 5*10^4
 * 1 ≤ arr[i] ≤ 10^6
 */

/************************************************************ C++ ************************************************/

// Approach: Use Trie to store binary representations of numbers and for each number, find the maximum XOR it can form with existing numbers in the Trie.
// Time Complexity: O(32 * n) = O(n), where 32 is the max number of bits and n is the array size.
// Space Complexity: O(32 * n) = O(n), Trie stores up to 32*n nodes.
class Solution {
public:

    // Node class representing each bit (0 or 1) in Trie
    class Node {
public:
        Node* one;
        Node* zero;
        Node() {
            one  = nullptr;
            zero = nullptr;
        }
    };

    // Trie class to insert numbers and find maximum XOR
    class Trie {
public:
        Node* root;
        Trie() {
            root = new Node();
        }
        // Function to insert number into Trie (bit by bit)
        void insert(int n) {
            Node* curr = root;

            for (int i = 31; i >= 0; i--) {
                int bit = (n >> i) & 1;

                // Insert 0-bit path
                if (bit == 0) {
                    if (curr->zero == NULL) {
                        curr->zero = new Node();
                    }
                    curr = curr->zero;
                }
                // Insert 1-bit path
                else {
                    if (curr->one == NULL) {
                        curr->one = new Node();
                    }
                    curr = curr->one;
                }
            }
        }
        // Find maximum XOR for given number using Trie
        int findXOR(int n) {
            Node* curr = root;
            int   res  = 0;

            for (int i = 31; i >= 0; i--) {
                int bit = (n >> i) & 1;

                // If current bit is 0, try to go to 1 to maximize XOR
                if (bit == 0) {
                    if (curr->one) {
                        res |= (1 << i);    // Set i-th bit in result
                        curr = curr->one;
                    } else {
                        curr = curr->zero;
                    }
                }
                // If current bit is 1, try to go to 0 to maximize XOR
                else {
                    if (curr->zero) {
                        res |= (1 << i);
                        curr = curr->zero;
                    } else {
                        curr = curr->one;
                    }
                }
            }

            return res;
        }
    };

    int maxXor(vector<int>& arr) {
        Trie* t   = new Trie();
        int   res = 0;

        // Insert first number into Trie
        t->insert(arr[0]);

        for (int i = 1; i < arr.size(); i++) {
            // For each number, compute max XOR with existing numbers in Trie
            res = max(res, t->findXOR(arr[i]));

            // Insert current number into Trie for future comparisons
            t->insert(arr[i]);
        }

        return res;
    }
};

/*
 * Dry Run:
 *
 * Input: arr = [25, 10, 2, 8, 5, 3]
 *
 * Step 1: Insert 25 into Trie
 * Step 2: Check XOR of 10 with Trie → 25 ^ 10 = 19 → max = 19
 * Step 3: Insert 10
 * Step 4: Check XOR of 2 with Trie → max becomes 27
 * Step 5: Insert 2
 * Step 6: Check XOR of 8 → max becomes 27 (still)
 * Step 7: Insert 8
 * Step 8: Check XOR of 5 → max becomes 28 (5 ^ 25)
 * Step 9: Insert 5
 * Step 10: Check XOR of 3 → remains 28
 * Final Answer = 28
 *
 */

/************************************************************ JAVA ************************************************/

// Approach: Use Trie to store binary representations of numbers and find max XOR for each number using bit manipulation.
// Time Complexity: O(32 * n) = O(n), where n = number of elements and 32 = number of bits.
// Space Complexity: O(32 * n) = O(n), due to Trie storing up to 32 * n nodes.
class Solution {
    // Node class for each Trie node (represents either 0 or 1)
    class Node {
        Node one;   // represents bit 1
        Node zero;  // represents bit 0

        Node() {
            one  = null;
            zero = null;
        }
    }

    // Trie class for inserting and finding XOR
    class Trie {
        Node root;

        Trie() {
            root = new Node();
        }
        // Insert a number into the Trie bit by bit (from MSB to LSB)
        void insert(int num) {
            Node curr = root;

            for (int i = 31; i >= 0; i--) {
                int bit = (num >> i) & 1;

                if (bit == 0) {
                    if (curr.zero == null) {
                        curr.zero = new Node();
                    }
                    curr = curr.zero;
                } else {
                    if (curr.one == null) {
                        curr.one = new Node();
                    }
                    curr = curr.one;
                }
            }
        }
        // Find the max XOR for a given number from Trie
        int findXOR(int num) {
            Node curr   = root;
            int  maxXor = 0;

            for (int i = 31; i >= 0; i--) {
                int bit = (num >> i) & 1;

                // Prefer opposite bit for maximizing XOR
                if (bit == 0) {
                    if (curr.one != null) {
                        maxXor |= (1 << i);
                        curr    = curr.one;
                    } else {
                        curr = curr.zero;
                    }
                } else {
                    if (curr.zero != null) {
                        maxXor |= (1 << i);
                        curr    = curr.zero;
                    } else {
                        curr = curr.one;
                    }
                }
            }

            return maxXor;
        }
    }

    public int maxXor(int[] arr) {
        Trie trie   = new Trie();
        int  result = 0;

        // Insert the first element
        trie.insert(arr[0]);

        for (int i = 1; i < arr.length; i++) {
            result = Math.max(result, trie.findXOR(arr[i]));
            trie.insert(arr[i]);
        }

        return result;
    }
}

/*
 * Dry Run:
 *
 * Input: arr = [25, 10, 2, 8, 5, 3]
 *
 * Step 1: Insert 25 into Trie
 * Step 2: Check XOR of 10 with Trie → 10 ^ 25 = 19 → max = 19
 * Step 3: Insert 10 into Trie
 * Step 4: Check XOR of 2 → max = 27 (2 ^ 25)
 * Step 5: Insert 2
 * Step 6: Check XOR of 8 → max = 27
 * Step 7: Insert 8
 * Step 8: Check XOR of 5 → max = 28 (5 ^ 25)
 * Step 9: Insert 5
 * Step 10: Check XOR of 3 → max remains 28
 * Final Answer = 28
 */
