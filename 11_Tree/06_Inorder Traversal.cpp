/*
 * Inorder Traversal
 *
 * Given a Binary Tree, your task is to return its In-Order Traversal.
 * An inorder traversal first visits the left child (including its entire subtree), then visits the node, and finally visits the right child (including its entire subtree).
 *
 * Examples:
 * Input: root[] = [1, 2, 3, 4, 5]
 * Output: [4, 2, 5, 1, 3]
 * Explanation: The in-order traversal of the given binary tree is [4, 2, 5, 1, 3].
 *
 * Input: root[] = [8, 1, 5, N, 7, 10, 6, N, 10, 6]
 * Output: [1, 7, 10, 8, 6, 10, 5, 6]
 * Explanation: The in-order traversal of the given binary tree is [1, 7, 10, 8, 6, 10, 5, 6].
 *
 * Constraints:
 * 1 <= number of nodes <= 10^5
 * 0 <= node->data <= 10^5
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

// Approach: Recursively perform an inorder traversal (left subtree, node, right subtree)
// and store each visited node's data in a result vector.
// Time Complexity: O(n) where n is the number of nodes, as each node is visited once.
// Space Complexity: O(h) where h is the height of the tree due to recursion stack space.
class Solution {
public:
   // Recursive helper function for inorder traversal.
   void solve(Node* root, vector<int>& result) {
      if (root == nullptr) {
         return;
      }
      // Traverse left subtree.
      solve(root->left, result);
      // Visit current node.
      result.push_back(root->data);
      // Traverse right subtree.
      solve(root->right, result);
   }

   // Returns a vector containing the inorder traversal of the tree.
   vector<int> inOrder(Node* root) {
      vector<int> result;

      solve(root, result);
      return result;
   }
};

/*
 * Dry Run Example:
 * For the binary tree:
 *       1
 *      / \
 *     2   3
 *    / \
 *   4   5
 * The traversal visits:
 * - Left subtree of 1 (inorder of node 2): traverse left (4), visit node 2, traverse right (5) → [4, 2, 5]
 * - Then visit 1
 * - Then right subtree of 1 (node 3) → [3]
 * Final result: [4, 2, 5, 1, 3]
 */

/************************************************************ JAVA ************************************************/

/* A Binary Tree node
 *
 * class Node {
 *  int data;
 *  Node left, right;
 * Node(int item)    {
 *      data = item;
 *      left = right = null;
 *  }
 * }
 */

// Approach: Recursively traverse the binary tree in inorder fashion (left, node, right)
// and add each visited node's data to an ArrayList.
// Time Complexity: O(n) where n is the number of nodes, as each node is visited exactly once.
// Space Complexity: O(h) where h is the height of the tree, due to the recursion call stack.
class Solution {
   // Helper function to perform inorder traversal and populate the result list.
   private void solve(Node root, ArrayList<Integer> result) {
      if (root == null) {
         return;
      }
      // Traverse left subtree.
      solve(root.left, result);
      // Add current node's data.
      result.add(root.data);
      // Traverse right subtree.
      solve(root.right, result);
   }

   // Function to return a list containing the inorder traversal of the tree.
   public ArrayList<Integer> inOrder(Node root) {
      ArrayList<Integer> result = new ArrayList<>();

      solve(root, result);
      return result;
   }
}

/*
 * Dry Run Example:
 * For the binary tree:
 *       1
 *      / \
 *     2   3
 *    / \
 *   4   5
 * The traversal processes:
 * - Inorder of node 2: traverse left (4), visit node 2, traverse right (5) → [4, 2, 5]
 * - Visit node 1
 * - Inorder of node 3 → [3]
 * Final result: [4, 2, 5, 1, 3]
 */
