/*
 * k-th Smallest in BST
 *
 * Given a BST and an integer k, the task is to find the kth smallest element in the BST. If there is no kth smallest element present then return -1.
 *
 * Examples:
 *
 * Input: root = [2, 1, 3], k = 2
 * Output: 2
 * Explanation: 2 is the 2nd smallest element in the BST.
 *
 * Input: root = [2, 1, 3], k = 5
 * Output: -1
 * Explanation: There is no 5th smallest element in the BST as the size of BST is 3.
 *
 * Input: root = [20, 8, 22, 4, 12, N, N, N, N, 10, 14], k = 3
 * Output: 10
 * Explanation: 10 is the 3rd smallest element in the BST.
 *
 * Constraints:
 * 1 <= number of nodes, k <= 10^5
 * 1 <= node->data <= 10^5
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

// Approach: Inorder traversal of the BST; decrement k at each visited node until k becomes 0, then record the current node's data as the kth smallest element.
// TC: O(n) in worst-case when k equals the number of nodes; SC: O(h) where h is the height of the BST (due to recursion).
// Dry run is provided below.
class Solution {
public:
   // Helper function to perform inorder traversal.
   // It decrements k for each visited node and sets result when k becomes 0.
   void inorder(Node* root, int&k, int&result) {
      if (!root) {     // If the current node is null, return.
         return;
      }

      // Traverse left subtree.
      inorder(root->left, k, result);

      // Early termination if kth smallest element is already found.
      if (k == 0) {
         return;
      }

      // Process current node.
      k--;          // Decrement k since we've visited one more node.
      if (k == 0) { // If k is 0, current node is the kth smallest.
         result = root->data;
         return;
      }

      // Traverse right subtree.
      inorder(root->right, k, result);
   }

   // Main function to return the kth smallest element in the BST.
   int kthSmallest(Node* root, int k) {
      int result = -1;          // Initialize result to -1 (default if kth smallest doesn't exist).

      inorder(root, k, result); // Perform inorder traversal to update result.
      return result;
   }
};

/*
 * Dry Run Example for C++:
 * BST:
 *       2
 *      / \
 *     1   3
 * k = 2
 *
 * Steps:
 * 1. Call kthSmallest(root=2, k=2) -> result initialized to -1.
 * 2. Inorder traversal starts at root 2.
 * 3. Traverse left subtree: call inorder(root=1, k=2).
 * - For node 1: left child is null, so return.
 * - Process node 1: decrement k from 2 to 1.
 * - k != 0, so traverse right subtree (null) and return.
 * 4. Return to node 2: check if k==0 (k=1), then process node 2.
 * - Decrement k from 1 to 0.
 * - k == 0, so set result = 2.
 * 5. Terminate further traversal; kth smallest element found is 2.
 * End Dry Run Example
 */

/************************************************************ JAVA ************************************************/

/*
 * class Node {
 *  int data;
 *  Node left, right;
 *  public Node(int d) {
 *      data = d;
 *      left = right = null;
 *  }
 * }
 */

// Approach: Perform an inorder traversal (left, node, right) of the BST.
//           Use global variables to decrement k and capture the kth smallest element.
// TC: O(n) in worst-case when k equals the number of nodes; SC: O(h) due to recursion (h is the height of the BST).
// Dry run is provided below.
class Solution {
   // Global variables to store the current k value and the result.
   private int kVal;
   private int result;

   // Helper function to perform inorder traversal.
   // Decrements kVal for each visited node and sets result when kVal becomes 0.
   private void inorder(Node root) {
      if (root == null) {
         return;    // If the current node is null, return.
      }

      inorder(root.left); // Traverse left subtree.

      if (kVal == 0) {    // Early termination if kth smallest element is already found.
         return;
      }

      kVal--;          // Decrement kVal for the current node.
      if (kVal == 0) { // If kVal becomes 0, current node is the kth smallest.
         result = root.data;
         return;
      }

      inorder(root.right);   // Traverse right subtree.
   }

   // Return the kth smallest element in the given BST.
   public int kthSmallest(Node root, int k) {
      kVal   = k;           // Initialize the global k value.
      result = -1;          // Initialize result to -1 (default if kth smallest doesn't exist).
      inorder(root);        // Perform inorder traversal to update result.
      return result;        // Return the kth smallest element.
   }
}

/*
 * Dry Run Example for Java:
 * BST:
 *       2
 *      / \
 *     1   3
 * k = 2
 *
 * Steps:
 * 1. Call kthSmallest(root=2, k=2) -> kVal is set to 2, result is -1.
 * 2. Inorder traversal starts at root (2).
 * 3. Traverse left subtree: call inorder(root=1).
 * - For node 1: left child is null, so return.
 * - Process node 1: decrement kVal from 2 to 1.
 * - kVal != 0, so traverse right subtree (null) and return.
 * 4. Return to node 2: check if kVal == 0 (kVal is 1), then process node 2.
 * - Decrement kVal from 1 to 0.
 * - kVal == 0, so set result = 2.
 * 5. Terminate further traversal; kth smallest element found is 2.
 * End Dry Run Example
 */
