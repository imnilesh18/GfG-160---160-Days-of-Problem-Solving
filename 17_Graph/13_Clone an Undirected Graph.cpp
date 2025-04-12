/*
 * Clone an Undirected Graph
 *
 * Difficulty: Medium Accuracy: 67.49% Submissions: 31K+ Points: 4
 *
 * Given a connected undirected graph represented by adjacency list, adjList[][] with n nodes, having a distinct label from 0 to n-1, where each adj[i] represents the list of vertices connected to vertex i.
 *
 * Create a clone of the graph, where each node in the graph contains an integer val and an array (neighbors) of nodes, containing nodes that are adjacent to the current node.
 *
 * class Node {
 *  val: integer
 *  neighbors: List[Node]
 * }
 *
 * Your task is to complete the function cloneGraph( ) which takes a starting node of the graph as input and returns the copy of the given node as a reference to the cloned graph.
 *
 * Note: If you return a correct copy of the given graph, then the driver code will print true; and if an incorrect copy is generated or when you return the original node, the driver code will print false.
 *
 * Examples :
 *
 * Input: n = 4, adjList[][] = [[1, 2], [0, 2], [0, 1, 3], [2]]
 * Output: true
 * Explanation:
 * As the cloned graph is identical to the original one the driver code will print true.
 *
 * Input: n = 3, adjList[][] = [[1, 2], [0], [0]]
 * Output: true
 * Explanation:
 * As the cloned graph is identical to the original one the driver code will print true.
 *
 * Constraints:
 * 1 ≤ n ≤ 10^4
 * 0 ≤ no. of edges ≤ 10^5
 * 0 ≤ adjList[i][j] < n
 */

// Visual Representation of Input Graph:
//
// Input:
//
//   X 1----------2 Y
//     |          |
//     |          |
//     |          |
//   Z 4----------3 M
//
//   Value = 1                Value = 2
//   neighbours               neighbours
//   +-----+-----+-----+      +-----+-----+-----+
//   |  Y  |  Z  |     |      |  X  |  M  |     |
//   +-----+-----+-----+      +-----+-----+-----+
//
//   Value = 3                Value = 4
//   neighbours               neighbours
//   +-----+-----+-----+      +-----+-----+-----+
//   |  Y  |  Z  |     |      |  X  |  M  |     |
//   +-----+-----+-----+      +-----+-----+-----+

// Visual Representation of Output (Cloned) Graph:
//
// Output:
//
//   A 1----------2 B
//     |          |
//     |          |
//     |          |
//   D 4----------3 C
//
//   Value = 1                Value = 2
//   neighbours               neighbours
//   +-----+-----+-----+      +-----+-----+-----+
//   |  B  |  D  |     |      |  A  |  C  |     |
//   +-----+-----+-----+      +-----+-----+-----+
//
//   Value = 3                Value = 4
//   neighbours               neighbours
//   +-----+-----+-----+      +-----+-----+-----+
//   |  B  |  D  |     |      |  A  |  C  |     |
//   +-----+-----+-----+      +-----+-----+-----+

// Deep Copy Approach Explanation:
// We perform a DFS traversal starting from the given node. For each node encountered:
// 1. If the node is not in our map, we create a new node (clone) with the same value and add it to the map.
// 2. We then recursively clone all its neighbors, and add them to the current clone’s neighbor list.
// 3. If a neighbor is already cloned (exists in the map), we directly attach its clone to the neighbor list without creating a new node.

// Dry Run:
/*
 *
 * Dry Run
 *
 * Input:
 *
 *   X 1----------2 Y
 *     |          |
 *     |          |
 *     |          |
 *   M 4----------3 Z
 *
 *   Value = 1
 *   neighbours
 *   +-----+-----+-----+
 *   |  Y  |  M  |     |
 *   +-----+-----+-----+
 *    so now we created new node 1 with address A
 *
 *    A 1
 *
 *    Now we have to create deep copy of node 2 by performing DFS
 *
 *    A 1-----------2 B
 *
 *    Value = 1
 *    neighbours
 *    +-----+-----+-----+
 *    |  B  |     |     |
 *    +-----+-----+-----+
 *
 *    clone_node
 *    A 1-----------2 B
 *                  |
 *                  |
 *                  |
 *                  3 C
 *
 *    Value = 2
 *    neighbours
 *    +-----+-----+-----+
 *    |  A  |  C  |     |
 *    +-----+-----+-----+
 *
 *    To remember that neighbor of 2 is 1
 *    we will use map to store it
 *
 *    map
 *    +-----------+-----------+
 *    |  Old Node | New Node  |
 *    +-----------+-----------+
 *    |     1     |    1      |
 *    +-----------+-----------+
 *    |     2     |    2      |
 *    +-----------+-----------+
 *    |     3     |    3      |
 *    +-----------+-----------+
 *
 *    clone_node
 *    A 1-----------2 B
 *                  |
 *                  |
 *                  |
 *                  3 C
 *
 *    Value = 3
 *    neighbours
 *    +-----+-----+-----+
 *    |  B  |     |     |
 *    +-----+-----+-----+
 *
 *    map
 *    +-----------+-----------+
 *    |  Old Node | New Node  |
 *    +-----------+-----------+
 *    |     1     |    1      |
 *    +-----------+-----------+
 *    |     2     |    2      |
 *    +-----------+-----------+
 *    |     3     |    3      |
 *    +-----------+-----------+
 *    |     4     |    4      |
 *    +-----------+-----------+
 *
 *    clone_node
 *    A 1-----------2 B
 *                  |
 *                  |
 *                  |
 *    D 4-----------3 C
 *
 *      Value = 3
 *      neighbours
 *      +-----+-----+-----+
 *      |  B  |  D   |    |
 *      +-----+-----+-----+
 *
 *      clone_node
 *      A 1-----------2 B
 *        |           |
 *        |           |
 *        |           |
 *      D 4-----------3 C
 *
 *
 *      map
 *      +-----------+-----------+
 *      |  Old Node | New Node  |
 *      +-----------+-----------+
 *      |     1     |    1      |
 *      +-----------+-----------+
 *      |     2     |    2      |
 *      +-----------+-----------+
 *      |     3     |    3      |
 *      +-----------+-----------+
 *      |     4     |    4      |
 *      +-----------+-----------+
 *
 *        Value = 4
 *        neighbours
 *        +-----+-----+-----+
 *        |  A  |  C  |     |
 *        +-----+-----+-----+
 *
 */

/************************************************************ C++ ************************************************/

// Approach: Use DFS traversal to clone each node recursively while using a hashmap to maintain mapping between original and cloned nodes.
// Time Complexity: O(N + M) where N is the number of nodes and M is the number of edges (each node and edge is visited once).
// Space Complexity: O(N) due to the recursion stack and hashmap storing the cloned nodes.

/*
 * // Definition for a Node.
 * class Node {
 *  public:
 *      int val;
 *      vector<Node*> neighbors;
 *
 *      Node() {
 *          val = 0;
 *          neighbors = vector<Node*>();
 *      }
 *
 *      Node(int _val) {
 *          val = _val;
 *          neighbors = vector<Node*>();
 *      }
 *
 *      Node(int _val, vector<Node*> _neighbors) {
 *          val = _val;
 *          neighbors = _neighbors;
 *      }
 *  };
 */

class Solution {
public:
    unordered_map<Node*, Node*> mp;     // Map to store mapping between original node and cloned node

    // DFS Helper function to traverse the original graph and clone nodes recursively
    void DFS(Node* node, Node* clone_node) {
        // Traverse all neighbours of the current original node
        for (Node* n : node->neighbors) {
            // If the neighbor has not been cloned yet
            if (mp.find(n) == mp.end()) {
                // Create the clone for this neighbor
                Node* clone = new Node(n->val);         // Create a new node with the same value as original neighbor n
                mp[n] = clone;                          // Store the mapping from original node n to its clone
                clone_node->neighbors.push_back(clone); // Append the cloned neighbor to the current clone's neighbor list
                DFS(n, clone);                          // Recursively call DFS for the neighbor n to clone its neighbors
            } else {
                // If the neighbor is already cloned, directly use it from the map
                clone_node->neighbors.push_back(mp[n]);
            }
        }
    }

    // Main function to clone the entire graph given the starting node
    Node* cloneGraph(Node* node) {
        if (!node) {
            return nullptr;     // If the input node is null, return null
        }

        mp.clear();     // Clear the mapping before starting cloning to handle multiple calls

        // Create the clone for the input starting node
        Node* clone_node = new Node(node->val);
        mp[node] = clone_node; // Map the original node to its clone

        DFS(node, clone_node); // Start DFS traversal to clone all connected nodes

        return clone_node;     // Return the cloned graph's starting node
    }
};

/************************************************************ JAVA ************************************************/

// Approach: Use DFS traversal to clone each node recursively while using a HashMap to maintain mapping between original and cloned nodes.
// Time Complexity: O(N + M) where N is the number of nodes and M is the number of edges (each node and edge is visited once).
// Space Complexity: O(N) due to the recursion stack and HashMap storing the cloned nodes.

/*
 *  class Node{
 *      int val;
 *      ArrayList<Node> neighbors;
 *      public Node(){
 *          val = 0;
 *          neighbors = new ArrayList<>();
 *      }
 *
 *      public Node(int val){
 *          this.val = val;
 *          neighbors = new ArrayList<>();
 *      }
 *
 *      public Node(int val, ArrayList<Node> neighbors){
 *          this.val = val;
 *          this.neighbors = neighbors;
 *      }
 *  }
 */

class Solution {
    // HashMap to store the mapping between original node and cloned node
    private Map<Node, Node> mp = new HashMap<>();

    // DFS Helper function to traverse the original graph and clone nodes recursively
    private void dfs(Node node, Node cloneNode) {
        // Traverse all neighbors of the current original node
        for (Node n : node.neighbors) {
            // If the neighbor has not been cloned yet
            if (!mp.containsKey(n)) {
                // Create the clone for this neighbor with the same value as the original node
                Node clone = new Node(n.val);
                mp.put(n, clone);               // Map the original neighbor to its clone
                cloneNode.neighbors.add(clone); // Append the cloned neighbor to the current clone's neighbor list
                dfs(n, clone);                  // Recursively call DFS for the neighbor to clone its neighbors
            } else {
                // If the neighbor is already cloned, directly use it from the map
                cloneNode.neighbors.add(mp.get(n));
            }
        }
    }
    
    // Main function to clone the entire graph given the starting node
    public Node cloneGraph(Node node) {
        if (node == null) {
            return null;  // If the input node is null, return null
        }

        mp.clear();  // Clear the map to handle multiple calls

        // Create the clone for the input starting node
        Node cloneNode = new Node(node.val);
        mp.put(node, cloneNode); // Map the original node to its clone

        dfs(node, cloneNode);    // Start DFS traversal to clone all connected nodes

        return cloneNode;        // Return the cloned graph's starting node
    }
}
