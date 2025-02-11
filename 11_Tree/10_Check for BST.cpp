/*
 * Check for BST
 *
 *
 * Given the root of a binary tree. Check whether it is a BST or not.
 * Note: We are considering that BSTs can not contain duplicate Nodes.
 * A BST is defined as follows:
 *
 * The left subtree of a node contains only nodes with keys less than the node's key.
 * The right subtree of a node contains only nodes with keys greater than the node's key.
 * Both the left and right subtrees must also be binary search trees.
 *
 * Examples:
 * Input: root = [2, 1, 3, N, N, N, 5]
 * Output: true
 * Explanation: The left subtree of every node contains smaller keys and right subtree of every node contains greater keys. Hence, the tree is a BST.
 *
 * Input: root = [2, N, 7, N, 6, N, 9]
 * Output: false
 * Explanation: Since the node to the right of node with key 7 has lesser key value, hence it is not a valid BST.
 *
 * Input: root = [10, 5, 20, N, N, 9, 25]
 * Output: false
 * Explanation: The node with key 9 present in the right subtree has lesser key value than root node.
 *
 * Constraints:
 * 1 ≤ number of nodes ≤ 10^5
 * 1 ≤ node->data ≤ 10^9
 */

/************************************************************ C++ ************************************************/

// Approach: Recursively verify that each node's value is between an allowed minimum and maximum range that is updated during traversal.
// Time Complexity: O(n) since every node is visited exactly once.
// Space Complexity: O(h) due to the recursion stack, where h is the height of the tree.
class Solution {
public:
   // Helper function to check BST properties by ensuring node->data is in the range (minVal, maxVal)
   bool check(Node* root, int minVal, int maxVal) {
      // If the node is null, it is considered a valid BST.
      if (!root) {
         return true;
      }

      // If the current node's data does not lie within the valid range, return false.
      if (root->data <= minVal || root->data >= maxVal) {
         return false;
      }

      // Recursively check the left subtree and right subtree with updated ranges.
      return check(root->left, minVal, root->data) && check(root->right, root->data, maxVal);
   }

   // Function to check whether a Binary Tree is a BST or not.
   bool isBST(Node* root) {
      return check(root, INT_MIN, INT_MAX);
   }
};

/*
 * Dry Run:
 * Consider the tree:
 *         2
 *        / \
 *       1   3
 * isBST(root) calls check(root, INT_MIN, INT_MAX)
 * For node 2: check that 2 is in (INT_MIN, INT_MAX) -> true, then recursively check left and right subtrees.
 * For left child (node 1): check that 1 is in (INT_MIN, 2) -> true, then its children are null so return true.
 * For right child (node 3): check that 3 is in (2, INT_MAX) -> true, then its children are null so return true.
 * Final result: true, indicating the tree is a valid BST.
 */

/************************************************************ JAVA ************************************************/

// Approach: Recursively verify that each node's value is between an allowed minimum and maximum range that is updated during traversal.
// Time Complexity: O(n) because every node is visited once.
// Space Complexity: O(h) due to the recursion stack, where h is the height of the tree.
class Solution {
   // Helper function to check BST properties by ensuring node.data is in the range (minVal, maxVal)
   boolean check(Node root, int minVal, int maxVal) {
      // If the node is null, it is considered a valid BST.
      if (root == null) {
         return true;
      }

      // If the current node's data does not lie within the valid range, return false.
      if (root.data <= minVal || root.data >= maxVal) {
         return false;
      }

      // Recursively check the left subtree and right subtree with updated ranges.
      return check(root.left, minVal, root.data) && check(root.right, root.data, maxVal);
   }

   // Function to check whether a Binary Tree is a BST or not.
   boolean isBST(Node root) {
      return check(root, Integer.MIN_VALUE, Integer.MAX_VALUE);
   }
}

/*
 * Dry Run:
 * Consider the tree:
 *         2
 *        / \
 *       1   3
 * isBST(root) calls check(root, Integer.MIN_VALUE, Integer.MAX_VALUE)
 * For node 2: check that 2 is in (Integer.MIN_VALUE, Integer.MAX_VALUE) -> true, then recursively check left and right subtrees.
 * For left child (node 1): check that 1 is in (Integer.MIN_VALUE, 2) -> true, then its children are null so return true.
 * For right child (node 3): check that 3 is in (2, Integer.MAX_VALUE) -> true, then its children are null so return true.
 * Final result: true, indicating the tree is a valid BST.
 */
