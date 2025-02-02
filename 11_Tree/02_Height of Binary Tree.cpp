/*
 * Height of Binary Tree
 *
 * Given a binary tree, find its height.
 * The height of a tree is defined as the number of edges on the longest path from the root to a leaf node. A leaf node is a node that does not have any children.
 *
 * Examples:
 *
 * Input: root[] = [12, 8, 18, 5, 11]
 * Output: 2
 * Explanation: One of the longest path from the root (node 12) goes through node 8 to node 5, which has 2 edges.
 *
 * Input: root[] = [1, 2, 3, 4, N, N, 5, N, N, 6, 7]
 * Output: 3
 * Explanation: The longest path from the root (node 1) to a leaf node 6 with 3 edge.
 *
 * Constraints:
 * 1 <= number of nodes <= 10^5
 * 0 <= node->data <= 10^5
 */

/************************************************************ C++ ************************************************/

// Approach 1: Recursively compute the height of the left and right subtrees and return 1 + max(height of left, height of right).
// The base case returns -1 for null nodes so that leaf nodes have a height of 0 (i.e., 0 edges).
// TC: O(n), where n is the number of nodes in the tree.
// SC: O(h), where h is the height of the tree (recursion stack space).
class Solution {
public:
   // Function to find the height of a binary tree.
   int height(Node* node) {
      // If the node is null, return -1 to indicate no edge exists.
      if (node == nullptr) {
         return -1;
      }

      // Recursively compute the height of the left subtree.
      int lh = height(node->left);
      // Recursively compute the height of the right subtree.
      int rh = height(node->right);

      // Return 1 plus the maximum height of the left and right subtrees.
      return 1 + max(lh, rh);
   }
};

/*
 * Dry Run:
 * Consider the following tree:
 *        12
 *       /  \
 *      8    18
 *     / \
 *    5   11
 *
 * Step-by-step:
 * 1. Call height(12)
 * - Calls height(8) and height(18)
 * 2. For node 8:
 * - Calls height(5) and height(11)
 * 3. For node 5:
 * - Calls height(nullptr) twice, both return -1.
 * - height(5) = 1 + max(-1, -1) = 0.
 * 4. For node 11:
 * - Similarly, height(11) = 0.
 * 5. Back to node 8:
 * - height(8) = 1 + max(0, 0) = 1.
 * 6. For node 18:
 * - Calls height(nullptr) twice, both return -1.
 * - height(18) = 1 + max(-1, -1) = 0.
 * 7. Finally, for node 12:
 * - height(12) = 1 + max(1, 0) = 2.
 * Output: 2 (The longest path has 2 edges: 12 -> 8 -> 5 or 12 -> 8 -> 11)
 */

// Approach 2: Perform a BFS (level order traversal) using a queue, incrementing a height counter for each level.
// TC: O(n) - every node is processed once.
// SC: O(n) - in the worst-case, the queue holds all nodes at the last level.
class Solution {
public:
   // Function to find the height of the binary tree.
   int height(Node* root) {
      // If the tree is empty, its height (number of edges) is -1.
      if (!root) {
         return -1;
      }

      // Queue to help in BFS traversal.
      queue<Node*> que;
      que.push(root);

      // Initialize height as -1 because we are counting edges.
      int height = -1;

      // Continue the traversal until there are no more nodes in the queue.
      while (!que.empty()) {
         // Increment height as we are going one level deeper.
         height++;

         // Get the number of nodes at the current level.
         int levelSize = que.size();

         // Process all nodes at the current level.
         for (int i = 0; i < levelSize; i++) {
            // Get the node at the front of the queue.
            Node* curr = que.front();
            que.pop();

            // If left child exists, add it to the queue for the next level.
            if (curr->left) {
               que.push(curr->left);
            }
            // If right child exists, add it to the queue for the next level.
            if (curr->right) {
               que.push(curr->right);
            }
         }
      }
      // After processing all levels, 'height' holds the number of edges.
      return height;
   }
};

/*
 * Dry Run:
 * Consider the following tree:
 *        10
 *       /  \
 *      5    15
 *     / \
 *    3   7
 *
 * Step-by-step:
 * 1. Start: queue = {10}, height = -1.
 * 2. Level 0: queue size = 1, height becomes 0.
 * - Process node 10, add children {5, 15} to queue.
 * 3. Level 1: queue = {5, 15}, height becomes 1.
 * - Process node 5, add children {3, 7} to queue.
 * - Process node 15, no children added.
 * 4. Level 2: queue = {3, 7}, height becomes 2.
 * - Process node 3, no children.
 * - Process node 7, no children.
 * 5. Queue empty, return height = 2.
 */

/************************************************************ JAVA ************************************************/

// Approach 1: Recursively compute the height of the left and right subtrees and return 1 + max(height of left, height of right).
// TC: O(n), where n is the number of nodes in the tree.
// SC: O(h), where h is the height of the tree (due to recursion stack space).
class Solution {
   int height(Node node) {
      // If the node is null, return -1 to indicate no edge exists.
      if (node == null) {
         return -1;
      }
      // Recursively compute the height of the left subtree.
      int lh = height(node.left);
      // Recursively compute the height of the right subtree.
      int rh = height(node.right);
      // Return 1 plus the maximum height of the left and right subtrees.
      return 1 + Math.max(lh, rh);
   }
}

// Approach 2: Perform a BFS (level order traversal) using a queue, incrementing a height counter for each level.
// TC: O(n) - every node is processed once.
// SC: O(n) - in the worst-case, the queue holds all nodes at the last level.
class Solution {
   // Function to find the height of a binary tree.
   int height(Node root) {
      // If the tree is empty, its height (number of edges) is -1.
      if (root == null) {
         return -1;
      }

      // Queue to help in BFS traversal.
      Queue<Node> queue = new LinkedList<>();
      queue.offer(root);

      // Initialize height as -1 because we are counting edges.
      int height = -1;

      // Continue the traversal until there are no more nodes in the queue.
      while (!queue.isEmpty()) {
         // Increment height as we are going one level deeper.
         height++;

         // Get the number of nodes at the current level.
         int levelSize = queue.size();

         // Process all nodes at the current level.
         for (int i = 0; i < levelSize; i++) {
            // Get the node at the front of the queue.
            Node curr = queue.poll();

            // If left child exists, add it to the queue for the next level.
            if (curr.left != null) {
               queue.offer(curr.left);
            }
            // If right child exists, add it to the queue for the next level.
            if (curr.right != null) {
               queue.offer(curr.right);
            }
         }
      }
      // After processing all levels, 'height' holds the number of edges.
      return height;
   }
}

/*
 * Dry Run:
 * Consider the following tree:
 *        10
 *       /  \
 *      5    15
 *     / \
 *    3   7
 *
 * Step-by-step:
 * 1. Start: queue = [10], height = -1.
 * 2. Level 0: queue size = 1, height becomes 0.
 * - Process node 10, add children [5, 15] to queue.
 * 3. Level 1: queue = [5, 15], height becomes 1.
 * - Process node 5, add children [3, 7] to queue.
 * - Process node 15, no children added.
 * 4. Level 2: queue = [3, 7], height becomes 2.
 * - Process node 3, no children.
 * - Process node 7, no children.
 * 5. Queue empty, return height = 2.
 */
