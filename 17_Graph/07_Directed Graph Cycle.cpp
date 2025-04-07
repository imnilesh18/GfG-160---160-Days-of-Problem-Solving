/*
 * Directed Graph Cycle
 *
 * Difficulty: Medium Accuracy: 27.88% Submissions: 467K+ Points: 4
 *
 * Given a Directed Graph with V vertices (Numbered from 0 to V-1) and E edges, check whether it contains any cycle or not.
 * The graph is represented as a 2D vector edges[][], where each entry edges[i] = [u, v] denotes an edge from verticex u to v.
 *
 * Examples:
 *
 * Input: V = 4, edges[][] = [[0, 1], [1, 2], [2, 3], [3, 3]]
 * Output: true
 * Explanation: 3 -> 3 is a cycle
 *
 * Input: V = 3, edges[][] = [[0, 1], [1, 2]]
 * Output: false
 * Explanation: no cycle in the graph
 *
 * Constraints:
 * 1 ≤ V, E ≤ 10^5
 */

/************************************************************ C++ ************************************************/

// Approach: Use DFS with recursion stack tracking to detect back edges that indicate a cycle in a directed graph.
// Time Complexity: O(V + E) - Each vertex and edge is visited once in the DFS traversal.
// Space Complexity: O(V) - Extra space for the visited and recursion stack arrays.
class Solution {
public:
    // DFS helper function to detect a cycle starting from vertex u
    bool isCycleDFS(unordered_map<int, vector<int>>& adj, int u, vector<bool>& visited, vector<bool>& inRecursion) {
        // Mark the current vertex as visited and add it to the recursion stack
        visited[u]     = true;       // Mark u as visited
        inRecursion[u] = true;       // Include u in the current recursion stack

        // Iterate through all adjacent vertices of u
        for (int& v : adj[u]) {
            // If vertex v is not visited, recursively call DFS on v
            if (!visited[v] && isCycleDFS(adj, v, visited, inRecursion)) {
                return true;      // Cycle detected in the DFS subtree rooted at v
            }
            // If vertex v is already in the recursion stack, a cycle is found
            else if (inRecursion[v]) {
                return true;      // Cycle detected due to back edge from u to v
            }
        }

        // Remove vertex u from the recursion stack before returning
        inRecursion[u] = false;
        return false;      // No cycle found starting from vertex u
    }
    // Function to check if the directed graph contains a cycle
    bool isCyclic(int V, vector<vector<int>>& edges) {
        unordered_map<int, vector<int>> adj;     // Adjacency list representation of the graph

        // Build the adjacency list from the given edges
        for (auto& edge : edges) {
            int u = edge[0];
            int v = edge[1];
            // Add edge from u to v (directed edge)
            adj[u].push_back(v);
        }

        // Create visited and recursion stack arrays to track visited nodes and the current DFS path
        vector<bool> visited(V, false);
        vector<bool> inRecursion(V, false);

        // Perform DFS from every vertex that has not been visited
        for (int i = 0; i < V; i++) {
            if (!visited[i] && isCycleDFS(adj, i, visited, inRecursion)) {
                return true;      // Cycle found in the DFS starting at vertex i
            }
        }

        return false;      // No cycle found in the graph
    }
};

/*
 * Dry Run:
 * Graph: V = 4, edges = [[0, 1], [1, 2], [2, 3], [3, 3]]
 * - Start DFS from vertex 0:
 *     - Mark 0 as visited and add to recursion stack.
 *     - Explore neighbor 1:
 *         - Mark 1 as visited and add to recursion stack.
 *         - Explore neighbor 2:
 *             - Mark 2 as visited and add to recursion stack.
 *             - Explore neighbor 3:
 *                 - Mark 3 as visited and add to recursion stack.
 *                 - Explore neighbor 3 (self-loop):
 *                     - 3 is already in the recursion stack → Cycle detected, return true.
 *             - DFS from vertex 3 returns true, propagate the true value.
 *         - DFS from vertex 2 returns true, propagate the true value.
 *     - DFS from vertex 1 returns true, propagate the true value.
 * - DFS from vertex 0 returns true, final output: cycle exists in the graph.
 */

/*
 * Visual Representation:
 *
 * Graph Structure:
 *       0
 *        \
 *         1
 *          \
 *           2
 *            \
 *             3
 *             |
 *             └───> (back to itself, self-loop)
 *
 * DFS Call Stack Evolution:
 * Start DFS(0): [0]
 *   → DFS(1): [0, 1]
 *       → DFS(2): [0, 1, 2]
 *           → DFS(3): [0, 1, 2, 3]
 *               → DFS(3): Encounter 3 again in the current stack -> Cycle Detected!
 *
 * This diagram shows how the DFS traversal follows the chain from 0 to 3 and then detects the self-loop at 3.
 */

/************************************************************ JAVA ************************************************/

// Approach: Use DFS with recursion stack tracking to detect back edges that indicate a cycle in a directed graph.
// Time Complexity: O(V + E) - Each vertex and edge is visited once in the DFS traversal.
// Space Complexity: O(V) - Extra space for the visited and recursion stack arrays.
class Solution {
    // DFS helper function to detect a cycle starting from vertex u
    private boolean isCycleDFS(Map<Integer, List<Integer>> adj, int u, boolean[] visited, boolean[] inRecursion) {
        visited[u]     = true;      // Mark u as visited
        inRecursion[u] = true;      // Include u in the current recursion stack

        // Iterate through all adjacent vertices of u
        for (int v : adj.get(u)) {
            // If vertex v is not visited, recursively call DFS on v
            if (!visited[v] && isCycleDFS(adj, v, visited, inRecursion)) {
                return true;        // Cycle detected in the DFS subtree rooted at v
            }
            // If vertex v is already in the recursion stack, a cycle is found
            else if (inRecursion[v]) {
                return true;        // Cycle detected due to back edge from u to v
            }
        }

        inRecursion[u] = false;     // Remove u from the recursion stack before returning
        return false;               // No cycle found starting from vertex u
    }
    public boolean isCyclic(int V, int[][] edges) {
        // Create the adjacency list representation of the graph using a HashMap
        Map<Integer, List<Integer>> adj = new HashMap<>();

        for (int i = 0; i < V; i++) {
            adj.put(i, new ArrayList<>());
        }
        // Build the adjacency list from the given edges
        for (int[] edge : edges) {
            int u = edge[0];
            int v = edge[1];
            // For a directed edge u -> v, add v to u's list.
            adj.get(u).add(v);
        }

        // Create visited and recursion stack arrays to track visited nodes and the current DFS path
        boolean[] visited     = new boolean[V];
        boolean[] inRecursion = new boolean[V];

        // Perform DFS from every vertex that has not been visited
        for (int i = 0; i < V; i++) {
            if (!visited[i] && isCycleDFS(adj, i, visited, inRecursion)) {
                return true;        // Cycle found in the DFS starting at vertex i
            }
        }

        return false;               // No cycle found in the graph
    }
}
/*
 * Dry Run:
 * Graph: V = 4, edges = [[0, 1], [1, 2], [2, 3], [3, 3]]
 *
 * - Build adjacency list:
 *       0 -> [1]
 *       1 -> [2]
 *       2 -> [3]
 *       3 -> [3]
 *
 * - Start DFS from vertex 0:
 *     - Mark 0 as visited and add to recursion stack.
 *     - Explore neighbor 1:
 *         - Mark 1 as visited and add to recursion stack.
 *         - Explore neighbor 2:
 *             - Mark 2 as visited and add to recursion stack.
 *             - Explore neighbor 3:
 *                 - Mark 3 as visited and add to recursion stack.
 *                 - Explore neighbor 3 (self-loop):
 *                     - 3 is already in the recursion stack → Cycle detected, return true.
 *             - DFS from vertex 3 returns true, propagate the true value.
 *         - DFS from vertex 2 returns true, propagate the true value.
 *     - DFS from vertex 1 returns true, propagate the true value.
 * - DFS from vertex 0 returns true, final output: cycle exists in the graph.
 *
 * Visual Representation:
 *       0
 *        \
 *         1
 *          \
 *           2
 *            \
 *             3
 *             |
 *             └───> (back to itself, self-loop)
 */
