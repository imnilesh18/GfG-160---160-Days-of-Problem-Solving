/*
 * Serialize and deserialize a binary tree
 *
 * Serialization is to store a tree in an array so that it can be later restored and deserialization is reading tree back from the array. Complete the functions
 *
 * serialize() : stores the tree into an array a and returns the array.
 * deSerialize() : deserializes the array to the tree and returns the root of the tree.
 * Note: Multiple nodes can have the same data and the node values are always positive integers. Your code will be correct if the tree returned by deSerialize(serialize(input_tree)) is same as the input tree. Driver code will print the in-order traversal of the tree returned by deSerialize(serialize(input_tree)).
 *
 * Examples :
 *
 * Input: root = [1, 2, 3]
 * Output: [2, 1, 3]
 *
 * Input: root = [10, 20, 30, 40, 60, N, N]
 * Output: [40, 20, 60, 10, 30]
 *
 * Constraints:
 * 1 <= Number of nodes <= 10^4
 * 1 <= Data of a node <= 10^9
 */

/************************************************************ C++ ************************************************/

/* A binary tree node has data, pointer to left child
 * and a pointer to right child
 * struct Node
 * {
 * int data;
 * Node* left;
 * Node* right;
 * };
 */

// Approach: Use pre-order traversal with a null marker (-1) for serialization, and recursive deserialization by reading array elements sequentially.
// Time Complexity: O(n) - each node is visited once.
// Space Complexity: O(n) - space for the serialized array and recursion stack.
class Solution {
public:
   // Helper function for serialization using pre-order traversal
   void serializeHelper(Node* root, vector<int>& arr) {
      // If node is null, add marker (-1) and return
      if (root == nullptr) {
         arr.push_back(-1);      // -1 indicates a null node
         return;
      }
      // Add current node's data
      arr.push_back(root->data);
      // Recursively serialize left subtree
      serializeHelper(root->left, arr);
      // Recursively serialize right subtree
      serializeHelper(root->right, arr);
   }

   // Function to serialize a tree and return an array of node values
   vector<int> serialize(Node* root) {
      vector<int> arr;

      serializeHelper(root, arr);     // Build the serialized array
      return arr;
   }

   // Helper function for deserialization using pre-order logic
   Node* deSerializeHelper(const vector<int>& arr, int& index) {
      // If index is out of bounds or current element is marker, increment index and return null
      if (index >= arr.size() || arr[index] == -1) {
         index++;      // Move to next element
         return nullptr;
      }
      // Create a new node with the current value
      Node* root = new Node(arr[index++]);
      // Recursively build left subtree
      root->left = deSerializeHelper(arr, index);
      // Recursively build right subtree
      root->right = deSerializeHelper(arr, index);
      return root;
   }

   // Function to deserialize an array and reconstruct the binary tree
   Node* deSerialize(vector<int>& arr) {
      int index = 0;

      return deSerializeHelper(arr, index);     // Rebuild tree starting from index 0
   }
}

/*
 * DRY RUN:
 *
 * Input Tree:
 *     1
 *    / \
 *   2   3
 *
 * Serialization Steps:
 * - Start at root (1): Add 1 to array.
 * - Move to left child (2): Add 2.
 * - Left child of 2 is null: Add -1.
 * - Right child of 2 is null: Add -1.
 * - Move to right child of 1 (3): Add 3.
 * - Left child of 3 is null: Add -1.
 * - Right child of 3 is null: Add -1.
 * Final serialized array: [1, 2, -1, -1, 3, -1, -1]
 *
 * Deserialization Steps:
 * - index=0: Value 1, create node 1.
 * - index=1: Value 2, create node 2 as left child of 1.
 * - index=2: Value -1, null left child for node 2.
 * - index=3: Value -1, null right child for node 2.
 * - index=4: Value 3, create node 3 as right child of 1.
 * - index=5: Value -1, null left child for node 3.
 * - index=6: Value -1, null right child for node 3.
 * Tree reconstructed successfully.
 *
 */

/************************************************************ JAVA ************************************************/

/*
 * Complete the given function
 * Node is as follows:
 * class Tree{
 *  int data;
 *  Tree left,right;
 *  Tree(int d){
 *      data=d;
 *      left=right=null;
 *  }
 * }*/

// Approach: Use pre-order traversal with a null marker (-1) for serialization, and recursive deserialization reading sequentially from the list.
// Time Complexity: O(n) - each node is processed once.
// Space Complexity: O(n) - space for the serialized list and recursion stack.
class Tree {
   // Helper function for serialization using pre-order traversal
   private void serializeHelper(Node root, ArrayList<Integer> arr) {
      // If node is null, add marker (-1) and return
      if (root == null) {
         arr.add(-1);    // -1 indicates a null node
         return;
      }
      // Add current node's data to the list
      arr.add(root.data);
      // Recursively serialize left subtree
      serializeHelper(root.left, arr);
      // Recursively serialize right subtree
      serializeHelper(root.right, arr);
   }

   // Function to serialize a tree and return an ArrayList containing the serialized nodes
   public ArrayList<Integer> serialize(Node root) {
      ArrayList<Integer> arr = new ArrayList<>();

      serializeHelper(root, arr);   // Build the serialized list
      return arr;
   }

   // Helper function for deserialization using pre-order logic
   private Node deSerializeHelper(ArrayList<Integer> arr, int[] index) {
      // If index is out of bounds or current element is marker, increment index and return null
      if (index[0] >= arr.size() || arr.get(index[0]) == -1) {
         index[0]++;    // Move to next element
         return null;
      }
      // Create a new node with the current value
      Node root = new Node(arr.get(index[0]++));
      // Recursively build left subtree
      root.left = deSerializeHelper(arr, index);
      // Recursively build right subtree
      root.right = deSerializeHelper(arr, index);
      return root;
   }

   // Function to deserialize an ArrayList and reconstruct the binary tree
   public Node deSerialize(ArrayList<Integer> arr) {
      int[] index = { 0 };                  // Array to simulate pass-by-reference for index

      return deSerializeHelper(arr, index); // Rebuild tree starting from index 0
   }
}

/*
 * DRY RUN:
 *
 * Input Tree:
 *    1
 *   / \
 *  2   3
 *
 * Serialization Steps:
 * - Start at root (1): Add 1 to list.
 * - Move to left child (2): Add 2.
 * - Left child of 2 is null: Add -1.
 * - Right child of 2 is null: Add -1.
 * - Move to right child of 1 (3): Add 3.
 * - Left child of 3 is null: Add -1.
 * - Right child of 3 is null: Add -1.
 * Final serialized list: [1, 2, -1, -1, 3, -1, -1]
 *
 * Deserialization Steps:
 * - index=0: Value 1, create node 1.
 * - index=1: Value 2, create node 2 as left child of 1.
 * - index=2: Value -1, null left child for node 2.
 * - index=3: Value -1, null right child for node 2.
 * - index=4: Value 3, create node 3 as right child of 1.
 * - index=5: Value -1, null left child for node 3.
 * - index=6: Value -1, null right child for node 3.
 * Tree reconstructed successfully.
 */
