/*
 * Diameter of a Binary Tree
 *
 * Given a binary tree, the diameter (also known as the width) is defined as the number of edges on the longest path between two leaf nodes in the tree. This path may or may not pass through the root. Your task is to find the diameter of the tree.
 *
 * Examples:
 *
 * Input: root[] = [1, 2, 3]
 * Output: 2
 * Explanation: The longest path has 2 edges (node 2 -> node 1 -> node 3).
 *
 * Input: root[] = [5, 8, 6, 3, 7, 9]
 * Output: 4
 * Explanation: The longest path has 4 edges (node 3 -> node 8 -> node 5 -> node 6 -> node 9).
 *
 * Constraints:
 * 1 ≤ number of nodes ≤ 10^5
 * 0 ≤ node->data ≤ 10^5
 */

/************************************************************ C++ ************************************************/

// Approach: Use postorder traversal to compute the height of each subtree while updating the diameter (the sum of left and right subtree heights at each node).
// Time Complexity: O(n)
// Space Complexity: O(n) (in the worst case, due to recursion stack)
class Solution {
public:
   // Helper function that computes the height of the tree while updating the diameter.
   // 'result' is updated with the maximum diameter found so far.
   int solve(Node* root, int& result) {
      // Base Case: If the node is NULL, its height is 0.
      if (!root) {
         return 0;
      }

      // Recursively compute the height of the left subtree.
      int lh = solve(root->left, result);
      // Recursively compute the height of the right subtree.
      int rh = solve(root->right, result);

      // The diameter at the current node is the sum of left and right subtree heights.
      // Update the result if this diameter is larger than the current maximum.
      result = max(result, lh + rh);

      // Return the height of the current node which is 1 (for the current node)
      // plus the maximum of the heights of its subtrees.
      return 1 + max(lh, rh);
   }

   // Main function to compute the diameter of the binary tree.
   int diameter(Node* root) {
      // If the tree is empty, its diameter is 0.
      if (!root) {
         return 0;
      }

      // Initialize result with the smallest possible value.
      int result = INT_MIN;

      // Begin the recursive process to compute heights and update diameter.
      solve(root, result);

      // Return the computed maximum diameter.
      return result;
   }
};

/*
 * Dry Run Example:
 * Consider the tree: [1, 2, 3]
 *     1
 *    / \
 *   2   3
 *
 * - Call diameter(root) with root = 1:
 * - solve(1, result) calls:
 *  - solve(2, result):
 * Node 2 has no children -> returns height = 1; result remains unchanged (initially INT_MIN or 0 if you assume 0 for empty tree).
 *  - solve(3, result):
 * Node 3 has no children -> returns height = 1; result remains unchanged.
 *  - At Node 1:
 * Left height (lh) = 1, Right height (rh) = 1.
 * Update result = max(result, 1 + 1) = 2.
 * Return height = 1 + max(1, 1) = 2.
 * - diameter() returns result = 2.
 */

/************************************************************ JAVA ************************************************/

// Approach: Use postorder traversal to compute the height of each subtree while updating the diameter (the sum of left and right subtree heights) at each node.
// Time Complexity: O(n)
// Space Complexity: O(n) (in the worst-case recursion stack)
class Solution {
   // Global variable 'result' to simulate C++ pass-by-reference for storing the maximum diameter.
   int result;

   // Equivalent of C++: int solve(Node* root, int& result)
   int solve(Node root) {
      // Base case: if the node is null, its height is 0.
      if (root == null) {
         return 0;
      }

      // Recursively compute the height of the left subtree.
      int lh = solve(root.left);
      // Recursively compute the height of the right subtree.
      int rh = solve(root.right);

      // Update 'result' with the maximum diameter found so far.
      result = Math.max(result, lh + rh);

      // Return the height of the current node.
      return 1 + Math.max(lh, rh);
   }

   // Equivalent of C++: int diameter(Node* root)
   int diameter(Node root) {
      // If the tree is empty, return 0.
      if (root == null) {
         return 0;
      }

      // Initialize 'result' to the smallest possible integer value.
      result = Integer.MIN_VALUE;

      // Compute the height of the tree, which updates 'result' with the maximum diameter.
      solve(root);

      // Return the maximum diameter found.
      return result;
   }
}

/*
 * Dry Run:
 * Consider the binary tree:
 *     1
 *    / \
 *   2   3
 *
 * Step 1: Call diameter(Node(1)):
 * - Check if root is null → false.
 * - Initialize result = Integer.MIN_VALUE.
 * - Call solve(Node(1)).
 *
 * Step 2: solve(Node(1)):
 * - Call solve(Node(2)):
 * Node(2) is not null.
 * Call solve(Node(2).left) → returns 0 (null).
 * Call solve(Node(2).right) → returns 0 (null).
 * Update result = max(Integer.MIN_VALUE, 0 + 0) = 0.
 * Return height = 1 + max(0, 0) = 1.
 * - Call solve(Node(1).right) → solve(Node(3)):
 * Node(3) is not null.
 * Call solve(Node(3).left) → returns 0 (null).
 * Call solve(Node(3).right) → returns 0 (null).
 * Update result = max(0, 0 + 0) = 0.
 * Return height = 1 + max(0, 0) = 1.
 * - Back at Node(1):
 * Left height (lh) = 1, right height (rh) = 1.
 * Update result = max(0, 1 + 1) = 2.
 * Return height = 1 + max(1, 1) = 2.
 *
 * Step 3: diameter(Node(1)) returns result = 2.
 */
