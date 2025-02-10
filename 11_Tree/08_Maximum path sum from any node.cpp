/*
 * Maximum path sum from any node
 *
 * Given a binary tree, the task is to find the maximum path sum. The path may start and end at any node in the tree.
 *
 * Examples:
 *
 * Input: root[] = [10, 2, 10, 20, 1, N, -25, N, N, N, N, 3, 4]
 * Output: 42
 * Explanation:
 * Max path sum is represented using green colour nodes in the above binary tree.
 *
 * Input: root[] = [-17, 11, 4, 20, -2, 10]
 * Output: 31
 * Explanation:
 * Max path sum is represented using green colour nodes in the above binary tree.
 *
 * Constraints:
 * 1 ≤ number of nodes ≤ 10^3
 * -10^4 ≤ node->data ≤ 10^4
 */

/************************************************************ C++ ************************************************/

/*
 * // Tree Node
 * class Node {
 * public:
 * int data;
 * Node *left;
 * Node *right;
 *
 * Node(int val) {
 *     data = val;
 *     left = right = NULL;
 * }
 * };
 */

// Approach: Use recursion to calculate maximum path sums at each node by considering three cases:
// 1) path passing through the node including both subtrees,
// 2) path including one child, and
// 3) the node itself; update a global maximum accordingly.
// TC: O(n) where n is the number of nodes in the tree.
// SC: O(h) where h is the height of the tree (recursion stack).
class Solution {
public:
   int maxSum;  // Global variable to store the maximum path sum

   // Recursive function to compute the maximum path sum from the current node.
   int solve(Node* root) {
      if (!root) {
         return 0;    // Base case: return 0 if the node is null.
      }

      int lh = solve(root->left);                                         // Maximum path sum from the left subtree.
      int rh = solve(root->right);                                        // Maximum path sum from the right subtree.

      int sumThroughRoot = lh + rh + root->data;                          // Path sum when including both left and right subtrees and the current node.
      int maxChildPath   = max(lh, rh) + root->data;                      // Maximum path sum when extending through one child.
      int singleNode     = root->data;                                    // Path sum considering only the current node.

      maxSum = max({ maxSum, sumThroughRoot, maxChildPath, singleNode }); // Update global maximum with the best option.

      return max(maxChildPath, singleNode);                               // Return the maximum path sum extendable to the parent.
   }

   // Function to return maximum path sum from any node in a tree.
   int findMaxSum(Node* root) {
      maxSum = INT_MIN;   // Initialize maxSum to the smallest integer.
      solve(root);        // Start recursive computation from the root.
      return maxSum;      // Return the overall maximum path sum.
   }
};

/*
 * Dry Run:
 * For the tree:
 *         10
 *        /  \
 *       2    10
 *      / \      \
 *    20   1     -25
 *                /  \
 *               3    4
 *
 * solve(20) returns 20.
 * solve(1) returns 1.
 * At node 2:
 *   lh = 20, rh = 1.
 *   sumThroughRoot = 20 + 1 + 2 = 23.
 *   maxChildPath = max(20, 1) + 2 = 22.
 *   singleNode = 2.
 *   maxSum = max(INT_MIN, 23, 22, 2) = 23.
 *   Returns max(22, 2) = 22.
 *
 * solve(3) returns 3.
 * solve(4) returns 4.
 * At node -25:
 *   lh = 3, rh = 4.
 *   sumThroughRoot = 3 + 4 - 25 = -18.
 *   maxChildPath = max(3, 4) - 25 = -21.
 *   singleNode = -25.
 *   maxSum = max(23, -18, -21, -25) = 23.
 *   Returns max(-21, -25) = -21.
 *
 * At node 10 (right child of root):
 *   lh = 0, rh = -21.
 *   sumThroughRoot = 0 + (-21) + 10 = -11.
 *   maxChildPath = max(0, -21) + 10 = 10.
 *   singleNode = 10.
 *   maxSum = max(23, -11, 10, 10) = 23.
 *   Returns max(10, 10) = 10.
 *
 * At root node (10):
 *   lh = 22, rh = 10.
 *   sumThroughRoot = 22 + 10 + 10 = 42.
 *   maxChildPath = max(22, 10) + 10 = 32.
 *   singleNode = 10.
 *   maxSum = max(23, 42, 32, 10) = 42.
 *   Returns max(32, 10) = 32.
 *
 * Final maximum path sum = 42.
 */

/************************************************************ JAVA ************************************************/

/*
 * Node defined as
 * class Node{
 *  int data;
 *  Node left,right;
 *  Node(int d){
 *      data=d;
 *      left=right=null;
 *  }
 * }
 */

// Approach: Use recursion to calculate maximum path sums at each node by considering three cases:
// 1) path passing through the node including both subtrees,
// 2) path including one child, and
// 3) the node itself; update a global maximum accordingly.
// TC: O(n) where n is the number of nodes in the tree.
// SC: O(h) where h is the height of the tree (recursion stack).
class Solution {
   int maxSum;  // Global variable to store the maximum path sum

   // Recursive function to compute the maximum path sum from the current node.
   int solve(Node root) {
      if (root == null) {
         return 0;    // Base case: return 0 if the node is null.
      }

      int lh = solve(root.left);                                                               // Maximum path sum from the left subtree.
      int rh = solve(root.right);                                                              // Maximum path sum from the right subtree.

      int sumThroughRoot = lh + rh + root.data;                                                // Path sum when including both left and right subtrees and the current node.
      int maxChildPath   = Math.max(lh, rh) + root.data;                                       // Maximum path sum when extending through one child.
      int singleNode     = root.data;                                                          // Path sum considering only the current node.

      maxSum = Math.max(maxSum, Math.max(sumThroughRoot, Math.max(maxChildPath, singleNode))); // Update global maximum.

      return Math.max(maxChildPath, singleNode);                                               // Return the maximum path sum extendable to the parent.
   }

   // Function to return maximum path sum from any node in a tree.
   int findMaxSum(Node node) {
      maxSum = Integer.MIN_VALUE;   // Initialize maxSum to the smallest integer.
      solve(node);                  // Start recursive computation from the given node.
      return maxSum;                // Return the overall maximum path sum.
   }
}

/*
 * Dry Run:
 * For the tree:
 *         10
 *        /  \
 *       2    10
 *      / \      \
 *    20   1     -25
 *                /  \
 *               3    4
 *
 * solve(20) returns 20.
 * solve(1) returns 1.
 * At node 2:
 *   lh = 20, rh = 1.
 *   sumThroughRoot = 20 + 1 + 2 = 23.
 *   maxChildPath = Math.max(20, 1) + 2 = 22.
 *   singleNode = 2.
 *   maxSum = Math.max(Integer.MIN_VALUE, 23, 22, 2) = 23.
 *   Returns Math.max(22, 2) = 22.
 *
 * solve(3) returns 3.
 * solve(4) returns 4.
 * At node -25:
 *   lh = 3, rh = 4.
 *   sumThroughRoot = 3 + 4 - 25 = -18.
 *   maxChildPath = Math.max(3, 4) - 25 = -21.
 *   singleNode = -25.
 *   maxSum = Math.max(23, -18, -21, -25) = 23.
 *   Returns Math.max(-21, -25) = -21.
 *
 * At node 10 (right child of root):
 *   lh = 0, rh = -21.
 *   sumThroughRoot = 0 + (-21) + 10 = -11.
 *   maxChildPath = Math.max(0, -21) + 10 = 10.
 *   singleNode = 10.
 *   maxSum = Math.max(23, -11, 10, 10) = 23.
 *   Returns Math.max(10, 10) = 10.
 *
 * At root node (10):
 *   lh = 22, rh = 10.
 *   sumThroughRoot = 22 + 10 + 10 = 42.
 *   maxChildPath = Math.max(22, 10) + 10 = 32.
 *   singleNode = 10.
 *   maxSum = Math.max(23, 42, 32, 10) = 42.
 *   Returns Math.max(32, 10) = 32.
 *
 * Final maximum path sum = 42.
 */
