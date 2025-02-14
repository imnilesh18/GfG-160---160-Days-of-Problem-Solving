/*
 * Fixing Two nodes of a BST
 *
 * Given the root of a Binary search tree(BST), where exactly two nodes were swapped by mistake. Your task is to fix (or correct) the BST by swapping them back. Do not change the structure of the tree.
 * Note: It is guaranteed that the given input will form BST, except for 2 nodes that will be wrong. All changes must be reflected in the original Binary search tree(BST).
 *
 * Examples :
 * Input: root = [10, 5, 8, 2, 20]
 * Output: 1
 *
 * Explanation: The nodes 20 and 8 were swapped.
 * Input: root = [5, 10, 20, 2, 8]
 * Output: 1
 *
 * Explanation: The nodes 10 and 5 were swapped.
 * Constraints:
 * 1 ≤ Number of nodes ≤ 10^3
 */

/************************************************************ C++ ************************************************/

/*
 * class Node
 * {
 * public:
 * int data;
 * Node *left, *right;
 * Node(int val)
 * {
 *     data = val;
 *     left = right = NULL;
 * }
 * };
 */

// Approach: Perform an in-order traversal of the BST to identify the two nodes that are out of order and then swap their values.
// TC: O(N) - Each node is visited exactly once during traversal, where N is the number of nodes.
// SC: O(H) - The space complexity is O(H) due to the recursion stack, where H is the height of the BST.
class Solution {
public:
   Node* first = nullptr, * second = nullptr, * prev = nullptr;

   // In-order traversal to detect the swapped nodes in BST
   void inOrder(Node* root) {
      if (root == nullptr) {
         return;
      }

      // Traverse the left subtree
      inOrder(root->left);

      // If the previous node exists and current node's value is less than previous node's value, a violation is found
      if (prev && root->data < prev->data) {
         // For the first violation, mark the previous node as 'first'
         if (!first) {
            first = prev;
         }
         // For any violation, update the 'second' to the current node
         second = root;
      }

      // Update the previous node to current node
      prev = root;

      // Traverse the right subtree
      inOrder(root->right);
   }

   // Function to correct the BST by swapping the values of the two wrong nodes
   void correctBST(Node* root) {
      inOrder(root);                      // Identify the two nodes that are swapped
      if (first && second) {
         swap(first->data, second->data); // Swap the values to fix the BST
      }
   }
};

/*
 * Dry Run:
 * Consider the BST represented as [10, 5, 8, 2, 20] where nodes 20 and 8 are swapped.
 * The correct in-order sequence should be: 2, 5, 8, 10, 20.
 * The actual in-order sequence becomes: 2, 5, 10, 8, 20.
 * When processing nodes 10 and then 8, since 8 < 10, a violation is detected.
 * 'first' is set to node with value 10 and 'second' is set to node with value 8.
 * After the traversal completes, swapping the values of 'first' and 'second' results in a corrected BST.
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

// Approach: Perform an in-order traversal of the BST to identify the two nodes that are out of order and then swap their values.
// TC: O(N) - Each node is visited exactly once during traversal, where N is the number of nodes.
// SC: O(H) - The space complexity is O(H) due to the recursion stack, where H is the height of the BST.
class Solution {
   Node first = null, second = null, prev = null;

   // In-order traversal to detect the swapped nodes in the BST
   void inOrder(Node root) {
      if (root == null) {
         return;
      }

      // Traverse the left subtree
      inOrder(root.left);

      // Check for a violation of BST properties: current node should be greater than the previous node
      if (prev != null && root.data < prev.data) {
         // For the first violation, assign 'first' to the previous node
         if (first == null) {
            first = prev;
         }
         // Update 'second' to the current node (this will capture the last encountered violation)
         second = root;
      }

      // Update the previous node to the current node
      prev = root;

      // Traverse the right subtree
      inOrder(root.right);
   }

   // Function to correct the BST by swapping the values of the two nodes that were swapped by mistake
   void correctBST(Node root) {
      inOrder(root);   // Identify the two swapped nodes using in-order traversal
      if (first != null && second != null) {
         // Swap the data values of the two nodes to fix the BST
         int temp = first.data;
         first.data  = second.data;
         second.data = temp;
      }
   }
}

/*
 * Dry Run:
 * Consider the BST represented as [5, 10, 20, 2, 8] where nodes 10 and 5 are swapped.
 * The correct in-order sequence should be: 2, 5, 8, 10, 20.
 * The actual in-order sequence becomes: 2, 10, 8, 5, 20.
 * When processing nodes 10 and then 8, since 8 < 10, a violation is detected.
 * 'first' is set to node with value 10 and 'second' is set to node with value 8.
 * Later, processing nodes 8 and then 5, since 5 < 8, 'second' is updated to node with value 5.
 * After the traversal, swapping the values of 'first' (10) and 'second' (5) results in a corrected BST.
 */
