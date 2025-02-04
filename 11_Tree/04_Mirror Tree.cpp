/*
 * Mirror Tree
 *
 * Given a binary tree, convert the binary tree to its Mirror tree.
 * Mirror of a Binary Tree T is another Binary Tree M(T) with left and right children of all non-leaf nodes interchanged.
 *
 * Examples:
 *
 * Input: root[] = [1, 2, 3, N, N, 4]
 * Output: [1, 3, 2, N, 4]
 * Explanation:
 * In the inverted tree, every non-leaf node has its left and right child interchanged.
 *
 * Input: root[] = [1, 2, 3, 4, 5]
 * Output: [1, 3, 2, N, N, 5, 4]
 * Explanation:
 * In the inverted tree, every non-leaf node has its left and right child interchanged.
 *
 * Constraints:
 * 1 ≤ number of nodes ≤ 10^5
 * 1 ≤ node->data ≤ 10^5
 */

/************************************************************ C++ ************************************************/

// Approach : Recursively swap the left and right children of every node to create the mirror image of the tree.
// Time Complexity: O(n) – Each node is visited exactly once.
// Space Complexity: O(h) – Space used in the recursion stack, where h is the height of the tree(O(n) in the worst case of a skewed tree).

/*
 * Mirror Tree
 *
 * Given a binary tree, convert the binary tree to its Mirror tree.
 * Mirror of a Binary Tree T is another Binary Tree M(T) with left and right children of all non-leaf nodes interchanged.
 *
 * Example:
 * Input: root[] = [1, 2, 3, 4, 5]
 * Binary Tree:
 *         1
 *       /   \
 *      2     3
 *     / \
 *    4   5
 *
 * Output: [1, 3, 2, N, N, 5, 4]
 * Mirror Tree:
 *         1
 *       /   \
 *      3     2
 *           / \
 *          5   4
 */

class Solution {
public:
   // Function to convert a binary tree into its mirror tree.
   void mirror(Node* node) {
      // Base case: if the current node is NULL, return.
      if (!node) {
         return;
      }

      // Swap the left and right children of the current node.
      Node* temp = node->left;
      node->left  = node->right;
      node->right = temp;

      // Recursively call mirror on the left subtree (which was originally the right subtree).
      mirror(node->left);
      // Recursively call mirror on the right subtree (which was originally the left subtree).
      mirror(node->right);
   }
};

/*
 * Dry Run Example (copy-paste format):
 *
 * Consider the binary tree:
 *      1
 *     / \
 *    2   3
 *   / \
 *  4   5
 *
 * 1. At Node 1:
 * - Swap children: left becomes 3, right becomes 2.
 * - Tree now:
 *       1
 *      / \
 *     3   2
 *        / \
 *       4   5
 * - Recursively process left child (Node 3) and then right child (Node 2).
 *
 * 2. At Node 3 (left child of Node 1):
 * - Node 3 has no children.
 * - Base case reached; return.
 *
 * 3. At Node 2 (right child of Node 1):
 * - Swap children: left becomes 5, right becomes 4.
 * - Tree now:
 *       1
 *      / \
 *     3   2
 *        / \
 *       5   4
 * - Recursively process left child (Node 5) and then right child (Node 4).
 *
 * 4. At Node 5 (left child of Node 2):
 * - Node 5 has no children.
 * - Base case reached; return.
 *
 * 5. At Node 4 (right child of Node 2):
 * - Node 4 has no children.
 * - Base case reached; return.
 *
 * Final mirror tree:
 *      1
 *     / \
 *    3   2
 *       / \
 *      5   4
 */

/************************************************************ JAVA ************************************************/

// Approach: Recursively swap the left and right children of every node to create the mirror image of the tree.
// Time Complexity: O(n) – Each node is visited exactly once.
// Space Complexity: O(h) – Space used in the recursion stack, where h is the height of the tree (O(n) in the worst case of a skewed tree).

/*
 * Mirror Tree
 *
 * Given a binary tree, convert the binary tree to its Mirror tree.
 * Mirror of a Binary Tree T is another Binary Tree M(T) with left and right children of all non-leaf nodes interchanged.
 *
 * Example:
 * Input: root[] = [1, 2, 3, 4, 5]
 * Binary Tree:
 *         1
 *       /   \
 *      2     3
 *     / \
 *    4   5
 *
 * Output: [1, 3, 2, N, N, 5, 4]
 * Mirror Tree:
 *         1
 *       /   \
 *      3     2
 *           / \
 *          5   4
 */
class Solution {
   // Function to convert a binary tree into its mirror tree.
   void mirror(Node node) {
      // Base case: if the current node is null, return.
      if (node == null) {
         return;
      }

      // Swap the left and right children of the current node.
      Node temp = node.left;
      node.left  = node.right;
      node.right = temp;

      // Recursively call mirror on the left subtree (which was originally the right subtree).
      mirror(node.left);
      // Recursively call mirror on the right subtree (which was originally the left subtree).
      mirror(node.right);
   }
}

/*
 * Dry Run Example (copy-paste format):
 *
 * Consider the binary tree:
 *      1
 *     / \
 *    2   3
 *   / \
 *  4   5
 *
 * 1. At Node 1:
 * - Swap children: left becomes 3, right becomes 2.
 * - Tree now:
 *       1
 *      / \
 *     3   2
 *        / \
 *       4   5
 * - Recursively process left child (Node 3) and then right child (Node 2).
 *
 * 2. At Node 3 (left child of Node 1):
 * - Node 3 has no children.
 * - Base case reached; return.
 *
 * 3. At Node 2 (right child of Node 1):
 * - Swap children: left becomes 5, right becomes 4.
 * - Tree now:
 *       1
 *      / \
 *     3   2
 *        / \
 *       5   4
 * - Recursively process left child (Node 5) and then right child (Node 4).
 *
 * 4. At Node 5 (left child of Node 2):
 * - Node 5 has no children.
 * - Base case reached; return.
 *
 * 5. At Node 4 (right child of Node 2):
 * - Node 4 has no children.
 * - Base case reached; return.
 *
 * Final mirror tree:
 *      1
 *     / \
 *    3   2
 *       / \
 *      5   4
 */
