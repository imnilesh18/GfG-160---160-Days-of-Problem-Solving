/*
 * Tree Boundary Traversal
 *
 * Given a Binary Tree, find its Boundary Traversal. The traversal should be in the following order:
 * Left Boundary: This includes all the nodes on the path from the root to the leftmost leaf node. You must prefer the left child over the right child when traversing. Do not include leaf nodes in this section.
 * Leaf Nodes: All leaf nodes, in left-to-right order, that are not part of the left or right boundary.
 * Reverse Right Boundary: This includes all the nodes on the path from the rightmost leaf node to the root, traversed in reverse order. You must prefer the right child over the left child when traversing. Do not include the root in this section if it was already included in the left boundary.
 * Note: If the root doesn't have a left subtree or right subtree, then the root itself is the left or right boundary.
 *
 * Examples:
 * Input: root[] = [1, 2, 3, 4, 5, 6, 7, N, N, 8, 9, N, N, N, N]
 * Output: [1, 2, 4, 8, 9, 6, 7, 3]
 *
 * Input: root[] = [1, 2, N, 4, 9, 6, 5, N, 3, N, N, N, N 7, 8]
 * Output: [1, 2, 4, 6, 5, 7, 8]
 * As the root doesn't have a right subtree, the right boundary is not included in the traversal.
 *
 * Input: root[] = [1, N, 2, N, 3, N, 4, N, N]
 *   1
 *    \
 *     2
 *      \
 *       3
 *        \
 *         4
 *
 * Output: [1, 4, 3, 2]
 * Left boundary: [1] (as there is no left subtree)
 * Leaf nodes: [4]
 * Right boundary: [3, 2] (in reverse order)
 * Final traversal: [1, 4, 3, 2]
 *
 * Constraints:
 * 1 ≤ number of nodes ≤ 10^5
 * 1 ≤ node->data ≤ 10^5
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

// Approach: Perform boundary traversal by combining left boundary (excluding leaves), all leaves, and right boundary (in reverse, excluding leaves).
// Time Complexity: O(N) - Each node is visited at most once.
// Space Complexity: O(N) - In worst case, the result vector stores all nodes.
class Solution {
private:
   // Checks if a node is a leaf (i.e., has no left or right child)
   // Approach: Returns true if both left and right pointers are null.
   // Time Complexity: O(1) - Constant time check.
   // Space Complexity: O(1) - Uses constant extra space.
   bool isLeaf(Node* node) {
      return node != nullptr && node->left == nullptr && node->right == nullptr;
   }

   // Adds the left boundary nodes (excluding leaf nodes) to the result vector.
   // Approach: Traverse starting from root->left, preferring left child; if left is null, take right child.
   // Time Complexity: O(H) - Where H is the height of the tree.
   // Space Complexity: O(1) - Uses constant extra space.
   void addLeftBoundary(Node* root, vector<int>& result) {
      Node* curr = root->left;

      while (curr) {
         if (!isLeaf(curr)) {
            result.push_back(curr->data);
         }
         if (curr->left) {
            curr = curr->left;
         } else {
            curr = curr->right;
         }
      }
   }

   // Adds the right boundary nodes (excluding leaf nodes) to the result vector in reverse order.
   // Approach: Traverse starting from root->right, preferring right child; if right is null, take left child.
   //              Store nodes in a temporary vector and then append them in reverse order.
   // Time Complexity: O(H) - Where H is the height of the tree.
   // Space Complexity: O(H) - Extra space for the temporary vector.
   void addRightBoundary(Node* root, vector<int>& result) {
      Node*       curr = root->right;
      vector<int> temp;

      while (curr) {
         if (!isLeaf(curr)) {
            temp.push_back(curr->data);
         }
         if (curr->right) {
            curr = curr->right;
         } else {
            curr = curr->left;
         }
      }
      // Append the right boundary nodes in reverse order
      for (int i = temp.size() - 1; i >= 0; i--) {
         result.push_back(temp[i]);
      }
   }

   // Adds all leaf nodes to the result vector.
   // Approach: Recursively traverse the tree and add the node's data if it is a leaf.
   // Time Complexity: O(N) - Visits every node.
   // Space Complexity: O(H) - Recursive stack space where H is the height of the tree.
   void addLeaves(Node* root, vector<int>& result) {
      if (isLeaf(root)) {
         result.push_back(root->data);
         return;
      }
      if (root->left) {
         addLeaves(root->left, result);
      }
      if (root->right) {
         addLeaves(root->right, result);
      }
   }

public:
   // Performs the boundary traversal of the binary tree.
   // Approach: Add root (if not a leaf), then left boundary, then all leaf nodes, and finally right boundary in reverse.
   // Time Complexity: O(N) - Each node is processed at most once.
   // Space Complexity: O(N) - The result vector holds the boundary nodes.
   vector<int> boundaryTraversal(Node* root) {
      vector<int> result;

      if (!root) {
         return result;
      }

      if (!isLeaf(root)) {
         result.push_back(root->data);
      }

      addLeftBoundary(root, result);
      addLeaves(root, result);
      addRightBoundary(root, result);
      return result;
   }
};

/*
 *** Dry Run ***
 ***Consider the binary tree:
 *       1
 *      / \
 *     2   3
 *      \
 *       4
 *
 * Step 1: Add root (if not a leaf)
 * result = [1]
 *
 * Step 2: Add left boundary (excluding leaves)
 * Traverse from node 2:
 *  - Node 2 is not a leaf -> add 2
 *  - Prefer left: node 2 has no left, so move to right (node 4)
 *  - Node 4 is a leaf -> stop
 * result = [1, 2]
 *
 * Step 3: Add leaf nodes (in left-to-right order)
 * Traverse entire tree:
 *  - Node 4 is a leaf -> add 4
 *  - Node 3 is a leaf -> add 3
 * result = [1, 2, 4, 3]
 *
 * Step 4: Add right boundary (excluding leaves, in reverse)
 * Traverse from node 3:
 *  - Node 3 is a leaf -> do not add
 * result remains = [1, 2, 4, 3]
 *
 * Final Boundary Traversal: [1, 2, 4, 3]
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

// Approach: Perform boundary traversal by combining left boundary (excluding leaves), all leaves, and right boundary (in reverse, excluding leaves).
// Time Complexity: O(N) - Each node is visited at most once.
// Space Complexity: O(N) - In worst case, the result list stores all nodes.
class Solution {
   // Checks if a node is a leaf (i.e., has no left or right child)
   // Approach: Returns true if both left and right references are null.
   // Time Complexity: O(1) - Constant time check.
   // Space Complexity: O(1) - Uses constant extra space.
   private boolean isLeaf(Node node) {
      return node != null && node.left == null && node.right == null;
   }

   // Adds the left boundary nodes (excluding leaf nodes) to the result list.
   // Approach: Traverse starting from root.left, preferring left child; if left is null, take right child.
   // Time Complexity: O(H) - Where H is the height of the tree.
   // Space Complexity: O(1) - Uses constant extra space.
   private void addLeftBoundary(Node root, List<Integer> result) {
      Node curr = root.left;

      while (curr != null) {
         if (!isLeaf(curr)) {
            result.add(curr.data);
         }
         if (curr.left != null) {
            curr = curr.left;
         } else {
            curr = curr.right;
         }
      }
   }

   // Adds the right boundary nodes (excluding leaf nodes) to the result list in reverse order.
   // Approach: Traverse starting from root.right, preferring right child; if right is null, take left child.
   //              Store nodes in a temporary list and then append them in reverse order.
   // Time Complexity: O(H) - Where H is the height of the tree.
   // Space Complexity: O(H) - Extra space for the temporary list.
   private void addRightBoundary(Node root, List<Integer> result) {
      Node curr = root.right;
      ArrayList<Integer> temp = new ArrayList<>();

      while (curr != null) {
         if (!isLeaf(curr)) {
            temp.add(curr.data);
         }
         if (curr.right != null) {
            curr = curr.right;
         } else {
            curr = curr.left;
         }
      }
      // Append the right boundary nodes in reverse order
      for (int i = temp.size() - 1; i >= 0; i--) {
         result.add(temp.get(i));
      }
   }

   // Adds all leaf nodes to the result list.
   // Approach: Recursively traverse the tree and add the node's data if it is a leaf.
   // Time Complexity: O(N) - Visits every node.
   // Space Complexity: O(H) - Recursive stack space where H is the height of the tree.
   private void addLeaves(Node root, List<Integer> result) {
      if (isLeaf(root)) {
         result.add(root.data);
         return;
      }
      if (root.left != null) {
         addLeaves(root.left, result);
      }
      if (root.right != null) {
         addLeaves(root.right, result);
      }
   }

   // Performs the boundary traversal of the binary tree.
   // Approach: Add root (if not a leaf), then left boundary, then all leaf nodes, and finally right boundary in reverse.
   // Time Complexity: O(N) - Each node is processed at most once.
   // Space Complexity: O(N) - The result list holds the boundary nodes.
   public ArrayList<Integer> boundaryTraversal(Node root) {
      ArrayList<Integer> result = new ArrayList<>();

      if (root == null) {
         return result;
      }

      if (!isLeaf(root)) {
         result.add(root.data);
      }

      addLeftBoundary(root, result);
      addLeaves(root, result);
      addRightBoundary(root, result);

      return result;
   }
}

/*
 *** Dry Run ***
 ***Consider the binary tree:
 *       1
 *      / \
 *     2   3
 *      \
 *       4
 *
 * Step 1: Add root (if not a leaf)
 * result = [1]
 *
 * Step 2: Add left boundary (excluding leaves)
 * Traverse from node 2:
 *  - Node 2 is not a leaf -> add 2
 *  - Prefer left: node 2 has no left, so move to right (node 4)
 *  - Node 4 is a leaf -> stop
 * result = [1, 2]
 *
 * Step 3: Add leaf nodes (in left-to-right order)
 * Traverse entire tree:
 *  - Node 4 is a leaf -> add 4
 *  - Node 3 is a leaf -> add 3
 * result = [1, 2, 4, 3]
 *
 * Step 4: Add right boundary (excluding leaves, in reverse)
 * Traverse from node 3:
 *  - Node 3 is a leaf -> do not add
 * result remains = [1, 2, 4, 3]
 *
 * Final Boundary Traversal: [1, 2, 4, 3]
 */
