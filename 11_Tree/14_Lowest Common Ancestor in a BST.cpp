/*
 * Lowest Common Ancestor in a BST
 *
 * Given a Binary Search Tree (with all values unique) and two nodes n1 and n2 (n1 != n2). You may assume that both nodes exist in the tree. Find the Lowest Common Ancestor (LCA) of the given two nodes in the BST.
 *
 * LCA between two nodes n1 and n2 is defined as the lowest node that has both n1 and n2 as descendants (where we allow a node to be a descendant of itself).
 *
 * Examples:
 *
 * Input: root = [5, 4, 6, 3, N, N, 7, N, N, N, 8], n1 = 7, n2 = 8
 * Output: 7
 * Explanation: 7 is the closest node to both 7 and 8, which is also an ancestor of both the nodes.
 *
 * Input: root = [20, 8, 22, 4, 12, N, N, N, N, 10, 14], n1 = 8, n2 = 14
 * Output: 8
 * Explanation: 8 is the closest node to both 8 and 14, which is also an ancestor of both the nodes.
 *
 * Input: root = [2, 1, 3], n1 = 1, n2 = 3
 * Output: 2
 * Explanation: 2 is the closest node to both 1 and 3, which is also an ancestor of both the nodes.
 *
 * Constraints:
 * 1 <= number of nodes <= 10^5
 * 1 <= node->data <= 10^5
 * 1 <= n1, n2 <= 10^5
 */

/************************************************************ C++ ************************************************/

/*
 * // Tree Node
 * class Node {
 * public:
 *  int data;
 *  Node* left;
 *  Node* right;
 *
 *  // Constructor to initialize a new node
 *  Node(int val) {
 *      data = val;
 *      left = NULL;
 *      right = NULL;
 *  }
 * };
 */

// Approach: Traverse the BST using its properties. If both nodes are smaller than the current node, move left; if both are greater, move right; otherwise, the current node is the LCA.
// TC: O(h) where h is the height of the BST.
// SC: O(h) due to recursion stack space.
class Solution {
public:
   // Function to find the Lowest Common Ancestor (LCA) in a BST.
   Node* LCA(Node* root, Node* n1, Node* n2) {
      // If the current node is NULL, return NULL.
      if (!root) {
         return nullptr;
      }

      // If both n1 and n2 are smaller than root, then LCA lies in the left subtree.
      if (root->data > n1->data && root->data > n2->data) {
         return LCA(root->left, n1, n2);
      }

      // If both n1 and n2 are greater than root, then LCA lies in the right subtree.
      if (root->data < n1->data && root->data < n2->data) {
         return LCA(root->right, n1, n2);
      }

      // Otherwise, the current node is the LCA.
      return root;
   }
};

/*
 * Dry run:
 * Example BST:
 *         20
 *        /  \
 *       8    22
 *      / \
 *     4   12
 *         /  \
 *        10   14
 * n1 = 8, n2 = 14
 * Start at root (20): both 8 and 14 are less than 20, so move to the left subtree.
 * At node 8: since 8 equals one of our nodes, this node is the LCA.
 * Result: Node with value 8.
 */

/************************************************************ JAVA ************************************************/

/*
 * class Node
 * {
 *  int data;
 *  Node left, right;
 *
 *  public Node(int d)
 *  {
 *      data = d;
 *      left = right = null;
 *  }
 * }
 */

// Approach: Traverse the BST using its properties. If both nodes are smaller than the current node, move left; if both are greater, move right; otherwise, the current node is the LCA.
// TC: O(h) where h is the height of the BST.
// SC: O(h) due to recursion stack space.
class Solution {
   // Function to find the Lowest Common Ancestor (LCA) in a BST.
   Node LCA(Node root, Node n1, Node n2) {
      // If the current node is null, return null.
      if (root == null) {
         return null;
      }

      // If both n1 and n2 are smaller than the current node, then LCA lies in the left subtree.
      if (root.data > n1.data && root.data > n2.data) {
         return LCA(root.left, n1, n2);
      }

      // If both n1 and n2 are greater than the current node, then LCA lies in the right subtree.
      if (root.data < n1.data && root.data < n2.data) {
         return LCA(root.right, n1, n2);
      }

      // Otherwise, the current node is the LCA.
      return root;
   }
}

/* Dry run:
 * Example BST:
 *         20
 *        /  \
 *       8   22
 *      / \
 *     4   12
 *        /  \
 *      10   14
 * n1 = 8, n2 = 14
 * Start at root (20): both 8 and 14 are less than 20, so move to the left subtree.
 * At node 8: since 8 equals one of our nodes, this node is the LCA.
 * Result: Node with value 8.
 */
