/*
 * DFS of Graph
 *
 * Difficulty: Easy Accuracy: 63.07% Submissions: 324K+ Points: 2 Average Time: 5m
 *
 * Given a connected undirected graph represented by a 2-d adjacency list adj[][], where each adj[i] represents the list of vertices connected to vertex i. Perform a Depth First Search (DFS) traversal starting from vertex 0, visiting vertices from left to right as per the given adjacency list, and return a list containing the DFS traversal of the graph.
 *
 * Note: Do traverse in the same order as they are in the given adjacency list.
 *
 * Examples:
 *
 * Input: adj[][] = [[2, 3, 1], [0], [0, 4], [0], [2]]
 * Output: [0, 2, 4, 3, 1]
 * Explanation: Starting from 0, the DFS traversal proceeds as follows:
 * Visit 0 → Output: 0
 * Visit 2 (the first neighbor of 0) → Output: 0, 2
 * Visit 4 (the first neighbor of 2) → Output: 0, 2, 4
 * Backtrack to 2, then backtrack to 0, and visit 3 → Output: 0, 2, 4, 3
 * Finally, backtrack to 0 and visit 1 → Final Output: 0, 2, 4, 3, 1
 *
 * Input: adj[][] = [[1, 2], [0, 2], [0, 1, 3, 4], [2], [2]]
 * Output: [0, 1, 2, 3, 4]
 * Explanation: Starting from 0, the DFS traversal proceeds as follows:
 * Visit 0 → Output: 0
 * Visit 1 (the first neighbor of 0) → Output: 0, 1
 * Visit 2 (the first neighbor of 1) → Output: 0, 1, 2
 * Visit 3 (the first neighbor of 2) → Output: 0, 1, 2, 3
 * Backtrack to 2 and visit 4 → Final Output: 0, 1, 2, 3, 4
 *
 * Constraints:
 * 1 ≤ adj.size() ≤ 10^4
 * 1 ≤ adj[i][j] ≤ 10^4
 */

/************************************************************ C++ ************************************************/

// Approach: Use recursive DFS starting from node 0; traverse each neighbor in order and mark visited nodes to avoid cycles.
// Time Complexity: O(V + E) - Each vertex and edge is processed exactly once during DFS.
// Space Complexity: O(V) - Additional space for recursion stack and the visited array.
class Solution {
public:
    // Recursive DFS function that explores nodes and records the traversal order.
    void DFS(unordered_map<int, vector<int>>& adj, int u, vector<bool>& visited, vector<int>& result) {
        // If node u is already visited, return immediately.
        if (visited[u] == true) {
            return;
        }

        // Mark node u as visited and add it to the DFS result list.
        visited[u] = true;
        result.push_back(u);

        // Explore each neighbor of node u in the given order.
        for (int& v : adj[u]) {
            if (!visited[v]) {
                DFS(adj, v, visited, result);
            }
        }
    }
    
    // Function to initialize DFS on the given graph represented as a 2D adjacency list.
    vector<int> dfs(vector<vector<int>>& mp) {
        int V = mp.size();
        unordered_map<int, vector<int>> adj;

        // Build the adjacency list from the provided 2D vector.
        for (int u = 0; u < V; u++) {
            for (auto v = mp[u].begin(); v != mp[u].end(); v++) {
                adj[u].push_back(*v);
            }
        }

        vector<int>  result;              // To store the order of DFS traversal.
        vector<bool> visited(V, false);   // To track visited nodes.

        // Start DFS traversal from node 0.
        DFS(adj, 0, visited, result);

        return result;
    }
};

/*
 *
 * Dry Run:
 *
 * Given Graph (Adjacency List):
 *     0: [2, 3, 1]
 *     1: [0]
 *     2: [0, 4]
 *     3: [0]
 *     4: [2]
 *
 * Visual Representation:
 *
 *             0
 *           / | \
 *         2   3  1
 *         |
 *         4
 *
 * DFS Traversal Steps:
 *
 * Step 1: Start at node 0.
 *   DFS Order: [0]
 *   Visited: {0}
 *         0
 *         ^
 *
 * Step 2: Visit first neighbor of 0 -> node 2.
 *   DFS Order: [0, 2]
 *   Visited: {0, 2}
 *         0
 *         |
 *         2
 *         ^
 *
 * Step 3: From node 2, visit first neighbor -> node 0 (already visited), then node 4.
 *   DFS Order: [0, 2, 4]
 *   Visited: {0, 2, 4}
 *         0
 *         |
 *         2
 *         |
 *         4
 *         ^
 *
 * Step 4: Node 4 has neighbor 2 (already visited), so backtrack to node 2.
 *   Backtrack to node 2, no more unvisited neighbors; backtrack to node 0.
 *
 * Step 5: At node 0, next unvisited neighbor -> node 3.
 *   DFS Order: [0, 2, 4, 3]
 *   Visited: {0, 2, 4, 3}
 *         0
 *       / | \
 *     2   3  1
 *         ^
 *
 * Step 6: Node 3 has neighbor 0 (already visited); backtrack to node 0.
 *
 * Step 7: At node 0, final unvisited neighbor -> node 1.
 *   DFS Order: [0, 2, 4, 3, 1]
 *   Visited: {0, 1, 2, 3, 4}
 *         0
 *       / | \
 *     2   3  1
 *            ^
 *
 * Final DFS Traversal: [0, 2, 4, 3, 1]
 *
 * The '^' pointer indicates the current node being processed in the DFS traversal.
 *
 */

/************************************************************ JAVA ************************************************/

// Approach: Use recursive DFS starting from node 0; traverse each neighbor in order and mark visited nodes to avoid cycles.
// Time Complexity: O(V + E) - Each vertex and edge is processed exactly once during DFS.
// Space Complexity: O(V) - Additional space for recursion stack and the visited array.
class Solution {
    // Recursive DFS function that explores nodes and records the traversal order.
    void DFS(HashMap<Integer, ArrayList<Integer>> adj, int u, boolean[] visited, ArrayList<Integer> result) {
        // If node u is already visited, return immediately.
        if (visited[u] == true) {
            return;
        }

        // Mark node u as visited and add it to the DFS result list.
        visited[u] = true;
        result.add(u);

        // Explore each neighbor of node u in the given order.
        for (int v : adj.get(u)) {
            if (!visited[v]) {
                DFS(adj, v, visited, result);
            }
        }
    }

    // Function to initialize DFS on the given graph represented as a 2D adjacency list.
    public ArrayList<Integer> dfs(ArrayList<ArrayList<Integer>> mp) {
        int V = mp.size();
        HashMap<Integer, ArrayList<Integer>> adj = new HashMap<>();

        // Build the adjacency list from the provided 2D list.
        for (int u = 0; u < V; u++) {
            // Create a new ArrayList for each vertex in the map.
            adj.put(u, new ArrayList<Integer>());
            for (int v : mp.get(u)) {
                adj.get(u).add(v);
            }
        }

        ArrayList<Integer> result = new ArrayList<>(); // To store the order of DFS traversal.
        boolean[] visited = new boolean[V];            // To track visited nodes.

        // Start DFS traversal from node 0.
        DFS(adj, 0, visited, result);

        return result;
    }
}

/*
 *
 * Dry Run:
 *
 * Given Graph (Adjacency List):
 *     0: [2, 3, 1]
 *     1: [0]
 *     2: [0, 4]
 *     3: [0]
 *     4: [2]
 *
 * Visual Representation:
 *
 *             0
 *           / | \
 *         2   3  1
 *         |
 *         4
 *
 * DFS Traversal Steps:
 *
 * Step 1: Start at node 0.
 *   DFS Order: [0]
 *   Visited: {0}
 *         0
 *         ^
 *
 * Step 2: Visit first neighbor of 0 -> node 2.
 *   DFS Order: [0, 2]
 *   Visited: {0, 2}
 *         0
 *         |
 *         2
 *         ^
 *
 * Step 3: From node 2, visit first neighbor -> node 0 (already visited), then node 4.
 *   DFS Order: [0, 2, 4]
 *   Visited: {0, 2, 4}
 *         0
 *         |
 *         2
 *         |
 *         4
 *         ^
 *
 * Step 4: Node 4 has neighbor 2 (already visited), so backtrack to node 2.
 *   Backtrack to node 2, no more unvisited neighbors; backtrack to node 0.
 *
 * Step 5: At node 0, next unvisited neighbor -> node 3.
 *   DFS Order: [0, 2, 4, 3]
 *   Visited: {0, 2, 4, 3}
 *         0
 *       / | \
 *     2   3  1
 *         ^
 *
 * Step 6: Node 3 has neighbor 0 (already visited); backtrack to node 0.
 *
 * Step 7: At node 0, final unvisited neighbor -> node 1.
 *   DFS Order: [0, 2, 4, 3, 1]
 *   Visited: {0, 1, 2, 3, 4}
 *         0
 *       / | \
 *     2   3  1
 *            ^
 *
 * Final DFS Traversal: [0, 2, 4, 3, 1]
 *
 * The '^' pointer indicates the current node being processed in the DFS traversal.
 *
 */
