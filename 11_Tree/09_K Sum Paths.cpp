/*
 * K Sum Paths
 *
 * Given a binary tree and an integer k, determine the number of downward-only paths where the sum of the node values in the path equals k. A path can start and end at any node within the tree but must always move downward (from parent to child).
 *
 * Examples:
 * Input: k = 7
 * Output: 3
 *
 * Input: k = 3
 * Output: 2
 * Path 1 : 1 -> 2 (Sum = 3)
 * Path 2 : 3 (Sum = 3)
 *
 * Constraints:
 * 1 ≤ number of nodes ≤ 10^4
 * -100 ≤ node value ≤ 100
 * -10^9 ≤ k ≤ 10^9
 */

/************************************************************ C++ ************************************************/

/*
 * struct Node {
 *  int data;
 *  Node *left;
 *  Node *right;
 *
 *  Node(int val) {
 *      data = val;
 *      left = right = NULL;
 *  }
 * };
 */

// Approach: Use DFS with a prefix sum hashmap to count paths with sum equal to k.
// Time Complexity: O(n) - Each node is visited once.
// Space Complexity: O(n) - In worst case, recursion stack and hashmap may store up to n entries.
class Solution {
public:
   int fill(Node* root, int k, int currSum, unordered_map<int, int>&prefixSum) {
      if (!root) {
         return 0;    // Base case: reached the end of a branch.
      }

      currSum += root->data;   // Update current cumulative sum with the current node's value.

      // Count the number of valid paths ending at the current node.
      int count = prefixSum[currSum - k];

      // Increment the frequency of the current cumulative sum.
      prefixSum[currSum]++;

      // Recursively count paths in the left and right subtrees.
      count += fill(root->left, k, currSum, prefixSum);
      count += fill(root->right, k, currSum, prefixSum);

      // Backtrack: Decrement the frequency to remove the current node's effect.
      prefixSum[currSum]--;

      return count;
   }

   // sumK: Returns the total number of downward paths with sum equal to k.
   int sumK(Node* root, int k) {
      unordered_map<int, int> prefixSum;

      prefixSum[0] = 1;   // Initialize with sum 0 to handle paths that equal k from the root.
      return fill(root, k, 0, prefixSum);
   }
};

/*
 * Dry Run Example
 * Consider the following binary tree:
 *    1
 *   / \
 *  2   3
 *
 * Let k = 3.
 *
 * Step-by-Step:
 * 1. At root (1): currSum = 0 + 1 = 1.
 * - Check prefixSum[1 - 3] = prefixSum[-2] (not present, count = 0).
 * - Update prefixSum: {0:1, 1:1}.
 * 2. Recurse into left child (2): currSum = 1 + 2 = 3.
 * - Check prefixSum[3 - 3] = prefixSum[0] = 1 (found 1 path: 1->2).
 * - Update prefixSum: {0:1, 1:1, 3:1}.
 * - Both children are null, so return count = 1.
 * - Backtrack: Decrement prefixSum[3] to 0.
 * 3. Recurse into right child (3) of root: currSum = 1 + 3 = 4.
 * - Check prefixSum[4 - 3] = prefixSum[1] = 1 (found 1 path: 3).
 * - Update prefixSum: {0:1, 1:1, 4:1}.
 * - Both children are null, so return count = 1.
 * - Backtrack: Decrement prefixSum[4] to 0.
 * 4. Backtrack at root: Decrement prefixSum[1] to 0.
 * Total paths with sum = 3: 1 (from left subtree) + 1 (from right subtree) = 2.
 *
 *** End of Dry Run ***
 */

/************************************************************ JAVA ************************************************/

/*
 * class Node {
 *  int data;
 *  Node left;
 *  Node right;
 *
 *  Node(int data) {
 *      this.data = data;
 *      left = null;
 *      right = null;
 *  }
 * }
 */

// Approach: Use DFS with a prefix sum hashmap to count downward paths with sum equal to k.
// Time Complexity: O(n) - Each node is processed once.
// Space Complexity: O(n) - Worst case due to recursion stack and hashmap storing up to n entries.
class Solution {
   private int fill(Node root, int k, int currSum, HashMap<Integer, Integer> prefixSum) {
      if (root == null) {
         return 0;    // Base case: reached the end of a branch.
      }

      currSum += root.data;   // Update current cumulative sum with the node's value.

      // Count the number of valid paths ending at the current node.
      int count = prefixSum.getOrDefault(currSum - k, 0);

      // Increment the frequency of the current cumulative sum.
      prefixSum.put(currSum, prefixSum.getOrDefault(currSum, 0) + 1);

      // Recursively count paths in the left and right subtrees.
      count += fill(root.left, k, currSum, prefixSum);
      count += fill(root.right, k, currSum, prefixSum);

      // Backtrack: Decrement the frequency to remove the current node's effect.
      prefixSum.put(currSum, prefixSum.get(currSum) - 1);

      return count;
   }

   // sumK: Returns the number of downward paths in the binary tree that sum to k.
   public int sumK(Node root, int k) {
      HashMap<Integer, Integer> prefixSum = new HashMap<>();

      prefixSum.put(0, 1);   // Initialize with sum 0 to handle paths that equal k from the root.
      return fill(root, k, 0, prefixSum);
   }
}

/*
 * Dry Run Example ***
 * Consider the following binary tree:
 *    1
 *   / \
 *  2   3
 *
 * Let k = 3.
 *
 * Step-by-Step:
 * 1. At root (1): currSum = 0 + 1 = 1.
 * - Check prefixSum for key (1 - 3) = -2; not present, so count = 0.
 * - Update prefixSum: {0=1, 1=1}.
 * 2. Recurse into left child (2): currSum = 1 + 2 = 3.
 * - Check prefixSum for key (3 - 3) = 0; value = 1 (found path: 1->2).
 * - Update prefixSum: {0=1, 1=1, 3=1}.
 * - Both children are null, so return count = 1.
 * - Backtrack: Decrement the count for currSum 3 in prefixSum.
 * 3. Recurse into right child (3) of root: currSum = 1 + 3 = 4.
 * - Check prefixSum for key (4 - 3) = 1; value = 1 (found path: 3).
 * - Update prefixSum: {0=1, 1=1, 4=1}.
 * - Both children are null, so return count = 1.
 * - Backtrack: Decrement the count for currSum 4 in prefixSum.
 * 4. Backtrack at root: Decrement the count for currSum 1 in prefixSum.
 * Total paths with sum = 3: 1 (from left subtree) + 1 (from right subtree) = 2.
 *** End of Dry Run ***
 */
