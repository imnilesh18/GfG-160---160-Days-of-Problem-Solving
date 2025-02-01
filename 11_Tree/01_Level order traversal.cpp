/*
 * Level order traversal
 *
 * Given a root of a binary tree with n nodes, the task is to find its level order traversal. Level order traversal of a tree is breadth-first traversal for the tree.
 *
 * Examples:
 *
 * Input: root[] = [1, 2, 3]
 * Output: [[1], [2, 3]]
 *
 * Input: root[] = [10, 20, 30, 40, 50]
 * Output: [[10], [20, 30], [40, 50]]
 *
 * Input: root[] = [1, 3, 2, N, N, N, 4, 6, 5]
 * Output: [[1], [3, 2], [4], [6, 5]]
 *
 * Constraints:
 * 1 ≤ number of nodes ≤ 10^5
 * 0 ≤ node->data ≤ 10^9
 */

/************************************************************ C++ ************************************************/

/*
 * Approach: Use a queue to perform a breadth-first search (BFS) by processing nodes level by level.
 * TC: O(n) - Each node is visited once.
 * SC: O(n) - In worst-case, the queue may hold up to O(n) nodes (e.g., a full level in a complete tree).
 *
 * Example:
 *  Consider the binary tree:
 *         1
 *       /   \
 *      2     3
 *     / \   /
 *    4   5 6
 *  Level order traversal would output: [[1], [2, 3], [4, 5, 6]]
 *
 * Below is the commented code:
 */
class Solution {
public:
   vector<vector<int> > levelOrder(Node* root) {
      // Vector to store the final level order traversal result.
      vector<vector<int> > result;

      // Edge case: if the tree is empty, return an empty result.
      if (!root) {
         return result;
      }

      // Queue to help in BFS traversal.
      queue<Node*> que;
      // Start with the root node.
      que.push(root);

      // Continue the traversal until there are no more nodes in the queue.
      while (!que.empty()) {
         // Get the number of nodes at the current level.
         int levelSize = que.size();
         // Temporary vector to store node values at the current level.
         vector<int> temp;

         // Process all nodes at the current level.
         for (int i = 0; i < levelSize; i++) {
            // Get the node at the front of the queue.
            Node* curr = que.front();
            que.pop();      // Remove the node from the queue.

            // Add the node's data to the current level vector.
            temp.push_back(curr->data);

            // If left child exists, add it to the queue for the next level.
            if (curr->left) {
               que.push(curr->left);
            }
            // If right child exists, add it to the queue for the next level.
            if (curr->right) {
               que.push(curr->right);
            }
         }
         // After processing the level, add the level vector to the result.
         result.push_back(temp);
      }
      // Return the complete level order traversal.
      return result;
   }
};

/************************************************************ JAVA ************************************************/

/*
 * Approach: Use a queue to perform a breadth-first search (BFS) and process nodes level by level.
 * TC: O(n) - Every node is visited exactly once.
 * SC: O(n) - In the worst-case, the queue may hold all nodes of a level (e.g., in a complete binary tree).
 *
 * Example:
 *  Consider the binary tree:
 *         1
 *       /   \
 *      2     3
 *     / \   /
 *    4   5 6
 *  The level order traversal will output: [[1], [2, 3], [4, 5, 6]]
 */

class Solution {
   public ArrayList<ArrayList<Integer> > levelOrder(Node root) {
      // List to store the final level order traversal result.
      ArrayList<ArrayList<Integer> > result = new ArrayList<>();

      // Edge case: if the tree is empty, return an empty list.
      if (root == null) {
         return result;
      }

      // Queue to support the BFS traversal.
      Queue<Node> queue = new LinkedList<>();
      // Start with the root node.
      queue.add(root);

      // Process the nodes until there are none left in the queue.
      while (!queue.isEmpty()) {
         // Number of nodes at the current level.
         int levelSize = queue.size();
         // List to store the nodes' data for the current level.
         ArrayList<Integer> levelList = new ArrayList<>();

         // Process all nodes at the current level.
         for (int i = 0; i < levelSize; i++) {
            // Remove the front node from the queue.
            Node current = queue.poll();
            // Add the current node's data to the level list.
            levelList.add(current.data);

            // If left child exists, add it to the queue.
            if (current.left != null) {
               queue.add(current.left);
            }
            // If right child exists, add it to the queue.
            if (current.right != null) {
               queue.add(current.right);
            }
         }
         // Add the current level's list to the final result.
         result.add(levelList);
      }

      // Return the complete level order traversal.
      return result;
   }
}

/*
 * Dry Run for the example binary tree:
 *         1
 *       /   \
 *      2     3
 *     / \   /
 *    4   5 6
 *
 * Step 1: Initialize
 * - result = []
 * - queue = [1]
 *
 * --------------------------------------------------
 * Iteration 1: Process level 1
 * - Current queue: [1]
 * - levelSize = 1
 * - levelList = []
 *
 * For loop (i from 0 to 0):
 *  i = 0:
 *      - current = 1 (poll from queue)
 *      - levelList becomes [1]
 *      - Add left child 2 to queue -> queue becomes [2]
 *      - Add right child 3 to queue -> queue becomes [2, 3]
 *
 * After for loop:
 * - Add levelList [1] to result -> result becomes [[1]]
 * - Queue now: [2, 3]
 *
 * --------------------------------------------------
 * Iteration 2: Process level 2
 * - Current queue: [2, 3]
 * - levelSize = 2
 * - levelList = []
 *
 * For loop (i from 0 to 1):
 *  i = 0:
 *      - current = 2 (poll from queue)
 *      - levelList becomes [2]
 *      - Add left child 4 to queue -> queue becomes [3, 4]
 *      - Add right child 5 to queue -> queue becomes [3, 4, 5]
 *
 *  i = 1:
 *      - current = 3 (poll from queue)
 *      - levelList becomes [2, 3]
 *      - Add left child 6 to queue -> queue becomes [4, 5, 6]
 *      - No right child for node 3, so queue remains [4, 5, 6]
 *
 * After for loop:
 * - Add levelList [2, 3] to result -> result becomes [[1], [2, 3]]
 * - Queue now: [4, 5, 6]
 *
 * --------------------------------------------------
 * Iteration 3: Process level 3
 * - Current queue: [4, 5, 6]
 * - levelSize = 3
 * - levelList = []
 *
 * For loop (i from 0 to 2):
 *  i = 0:
 *      - current = 4 (poll from queue)
 *      - levelList becomes [4]
 *      - Node 4 has no children -> queue remains [5, 6]
 *
 *  i = 1:
 *      - current = 5 (poll from queue)
 *      - levelList becomes [4, 5]
 *      - Node 5 has no children -> queue remains [6]
 *
 *  i = 2:
 *      - current = 6 (poll from queue)
 *      - levelList becomes [4, 5, 6]
 *      - Node 6 has no children -> queue becomes []
 *
 * After for loop:
 * - Add levelList [4, 5, 6] to result -> result becomes [[1], [2, 3], [4, 5, 6]]
 * - Queue now: []
 *
 * --------------------------------------------------
 * End of traversal:
 * - The queue is empty, so the while loop terminates.
 * - Final result: [[1], [2, 3], [4, 5, 6]]
 */
