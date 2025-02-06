/*
 * Construct Tree from Inorder & Preorder
 *
 * Given two arrays representing the inorder and preorder traversals of a binary tree, construct the tree and return the root node of the constructed tree.
 * Note: The output is written in postorder traversal.
 *
 * Examples:
 *
 * Input: inorder[] = [1, 6, 8, 7], preorder[] = [1, 6, 7, 8]
 * Output: [8, 7, 6, 1]
 * Explanation: The tree will look like
 *
 * Input: inorder[] = [3, 1, 4, 0, 2, 5], preorder[] = [0, 1, 3, 4, 2, 5]
 * Output: [3, 4, 1, 5, 2, 0]
 * Explanation: The tree will look like
 *
 * Input: inorder[] = [2, 5, 4, 1, 3], preorder[] = [1, 4, 5, 2, 3]
 * Output: [2, 5, 4, 3, 1]
 * Explanation: The tree will look like
 *
 * Constraints:
 * 1 ≤ number of nodes ≤ 10^3
 * 0 ≤ nodes -> data ≤ 10^3
 * Both the inorder and preorder arrays contain unique values.
 */

/************************************************************ C++ ************************************************/

/*
 * Definition of the Node class
 * class Node {
 * public:
 *  int data;
 *  Node *left;
 *  Node *right;
 *
 *  Node(int x) {
 *      data = x;
 *      left = NULL;
 *      right = NULL;
 *  }
 * };
 */

// Approach: Recursively construct the tree by taking the next element from the preorder array as the root,
//           then finding its index in the inorder array to split the tree into left and right subtrees.
// Time Complexity: O(n^2) in the worst-case (skewed tree due to linear search in inorder),
//                  though average can be O(n) with a balanced tree and optimization using a hashmap.
// Space Complexity: O(n) due to recursion stack space.
class Solution {
public:
   // Recursive helper function to construct the tree.
   Node* solve(vector<int>&inorder, vector<int>&preorder, int start, int end, int&idx) {
      // Base case: if there are no elements to construct the tree.
      if (start > end) {
         return nullptr;
      }

      // Pick current node from Preorder traversal using idx and increment idx.
      int rootVal = preorder[idx];
      int i       = start;
      // Find the index of the current root in inorder array.
      for (; i <= end; i++) {
         if (inorder[i] == rootVal) {
            break;
         }
      }
      idx++;   // Move to the next index in preorder.

      // Create a new node with the current root value.
      Node* root = new Node(rootVal);

      // Recursively build the left subtree.
      root->left = solve(inorder, preorder, start, i - 1, idx);
      // Recursively build the right subtree.
      root->right = solve(inorder, preorder, i + 1, end, idx);

      return root;
   }

   // Function to build the tree from given inorder and preorder traversals.
   Node*buildTree(vector<int>&inorder, vector<int>&preorder) {
      int n   = preorder.size();
      int idx = 0;    // Initialize index for preorder traversal.

      return solve(inorder, preorder, 0, n - 1, idx);
   }
};

/*
 * Dry Run Example: For inorder = [1, 6, 8, 7] and preorder = [1, 6, 7, 8]:
 *  - preIndex = 0: rootVal = 1, found at index 0 in inorder.
 *       -> Left subtree: inorder indices [0, -1] -> returns NULL.
 *       -> Right subtree: inorder indices [1, 3].
 *  - preIndex = 1: rootVal = 6, found at index 1 in inorder.
 *       -> Left subtree: inorder indices [1, 0] -> returns NULL.
 *       -> Right subtree: inorder indices [2, 3].
 *  - preIndex = 2: rootVal = 7, found at index 3 in inorder.
 *       -> Left subtree: inorder indices [2, 2].
 *  - preIndex = 3: rootVal = 8, found at index 2 in inorder.
 *       -> Left and right subtrees: no elements.
 *  Final tree (postorder traversal): [8, 7, 6, 1]
 */

/************************************************************ JAVA ************************************************/

/*
 * class Node {
 *  int data;
 *  Node left, right;
 *
 *  Node(int key) {
 *      data = key;
 *      left = right = null;
 *  }
 * }
 */

// Approach: Recursively build the binary tree using the preorder array to determine the root and
//           splitting the inorder array into left and right subtrees based on the root’s index.
// Time Complexity: O(n^2) in the worst-case (skewed tree with linear search in inorder),
//                  though average is O(n) with balanced trees and optimization using a hashmap.
// Space Complexity: O(n) due to recursion stack space.
class Solution {
   // A helper index pointer to keep track of the current root in the preorder array.
   // Since Java is pass-by-value for primitives, we use a static variable here.
   private static int preIndex;

   // Recursive helper function to construct the tree.
   private static Node solve(int inorder[], int preorder[], int start, int end) {
      // Base case: if there are no elements to construct the tree.
      if (start > end) {
         return null;
      }

      // Pick current node from Preorder traversal using preIndex and increment preIndex.
      int  rootVal = preorder[preIndex++];
      Node root    = new Node(rootVal);

      // If the node has no children then return.
      if (start == end) {
         return root;
      }

      // Find the index of the current root in inorder array.
      int i;
      for (i = start; i <= end; i++) {
         if (inorder[i] == rootVal) {
            break;
         }
      }

      // Recursively build the left subtree using elements before the index in inorder.
      root.left = solve(inorder, preorder, start, i - 1);
      // Recursively build the right subtree using elements after the index in inorder.
      root.right = solve(inorder, preorder, i + 1, end);

      return root;
   }

   // Main function to build tree from inorder and preorder arrays.
   public static Node buildTree(int inorder[], int preorder[]) {
      preIndex = 0;    // Initialize index to start from the first element of the preorder array.
      return solve(inorder, preorder, 0, inorder.length - 1);
   }
}

/*
 * Dry Run Example: For inorder = [1, 6, 8, 7] and preorder = [1, 6, 7, 8]:
 *  - preIndex = 0: rootVal = 1, found at index 0 in inorder.
 *       -> Left subtree: inorder indices [0, -1] -> returns null.
 *       -> Right subtree: inorder indices [1, 3].
 *  - preIndex = 1: rootVal = 6, found at index 1 in inorder.
 *       -> Left subtree: inorder indices [1, 0] -> returns null.
 *       -> Right subtree: inorder indices [2, 3].
 *  - preIndex = 2: rootVal = 7, found at index 3 in inorder.
 *       -> Left subtree: inorder indices [2, 2].
 *  - preIndex = 3: rootVal = 8, found at index 2 in inorder.
 *       -> Left and right subtrees: no elements.
 *  Final tree (postorder traversal): [8, 7, 6, 1]
 */
