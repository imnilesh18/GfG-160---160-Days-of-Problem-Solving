/*
 * Pair Sum in BST
 *
 * Given a Binary Search Tree(BST) and a target. Check whether there's a pair of Nodes in the BST with value summing up to the target.
 *
 * Examples:
 *
 * Input: root = [7, 3, 8, 2, 4, N, 9], target = 12
 *     bst
 * Output: True
 * Explanation: In the binary tree above, there are two nodes (8 and 4) that add up to 12.
 *
 * Input: root = [9, 5, 10, 2, 6, N, 12], target = 23
 *        bst-3
 * Output: False
 * Explanation: In the binary tree above, there are no such two nodes exists that add up to 23.
 *
 * Constraints:
 * 1 ≤ Number of Nodes ≤ 10^5
 * 1 ≤ target ≤ 10^6
 */

/************************************************************ C++ ************************************************/

/*
 * Node is as follows
 * class Node {
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

// Approach: Perform an inorder traversal of the BST to obtain a sorted array, then use a two-pointer approach to check if any two numbers sum up to the target.
// Time Complexity: O(n) – Inorder traversal and two-pointer search each take O(n).
// Space Complexity: O(n) – Extra space is used to store the inorder traversal.
class Solution {
public:
   // Two-pointer approach on sorted array to find a pair that sums to target.
   bool twoSum(vector<int> arr, int target) {
      int n     = arr.size();
      int left  = 0;
      int right = n - 1;

      while (left < right) {
         int sum = arr[left] + arr[right];

         if (sum == target) {
            return true;
         } else if (sum < target) {
            left++;
         } else {
            right--;
         }
      }

      return false;
   }

   // Inorder traversal to convert BST into a sorted array.
   void inorder(Node* root, vector<int>&arr) {
      if (!root) {
         return;
      }

      inorder(root->left, arr);
      arr.push_back(root->data);
      inorder(root->right, arr);
   }

   // Main function that integrates the inorder traversal and twoSum methods.
   bool findTarget(Node* root, int target) {
      vector<int> arr;

      inorder(root, arr);
      return twoSum(arr, target);
   }
};

/* DRY RUN:
 * Given BST:       7
 *                /   \
 *               3     8
 *              / \     \
 *             2   4     9
 * target = 12
 *
 * Inorder traversal yields sorted array: [2, 3, 4, 7, 8, 9]
 *
 * Two-pointer approach:
 *   left = 0, right = 5: arr[0] + arr[5] = 2 + 9 = 11 (< target) => left++
 *   left = 1, right = 5: arr[1] + arr[5] = 3 + 9 = 12 (== target) => return true
 */

/************************************************************ JAVA ************************************************/

/*
 * class Node {
 *  int data;
 *  Node left, right;
 *
 *  public Node(int d) {
 *      data = d;
 *      left = right = null;
 *  }
 * }
 */

// Approach: Perform an inorder traversal of the BST to obtain a sorted list, then use a two-pointer approach to check if any two numbers sum up to the target.
// Time Complexity: O(n) – Inorder traversal and two-pointer search each take O(n).
// Space Complexity: O(n) – Extra space is used to store the inorder traversal.
class Solution {
   // Two-pointer approach on sorted list to find a pair that sums to target.
   private boolean twoSum(List<Integer> arr, int target) {
      int left  = 0;
      int right = arr.size() - 1;

      while (left < right) {
         int sum = arr.get(left) + arr.get(right);

         if (sum == target) {
            return true;
         } else if (sum < target) {
            left++;
         } else {
            right--;
         }
      }
      return false;
   }

   // Inorder traversal to convert BST into a sorted list.
   private void inorder(Node root, List<Integer> arr) {
      if (root == null) {
         return;
      }
      inorder(root.left, arr);
      arr.add(root.data);
      inorder(root.right, arr);
   }

   public boolean findTarget(Node root, int target) {
      List<Integer> arr = new ArrayList<>();

      inorder(root, arr);
      return twoSum(arr, target);
   }
}

/* DRY RUN:
 * Given BST:       7
 *                /   \
 *               3     8
 *              / \     \
 *             2   4     9
 * target = 12
 *
 * Inorder traversal yields sorted list: [2, 3, 4, 7, 8, 9]
 *
 * Two-pointer approach:
 *   left = 0, right = 5: arr.get(0) + arr.get(5) = 2 + 9 = 11 (< target) => left++
 *   left = 1, right = 5: arr.get(1) + arr.get(5) = 3 + 9 = 12 (== target) => return true
 */
