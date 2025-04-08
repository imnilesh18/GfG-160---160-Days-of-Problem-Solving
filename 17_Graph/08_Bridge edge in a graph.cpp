/*
 * Bridge edge in a graph
 *
 * Difficulty: Medium Accuracy: 34.61% Submissions: 65K+ Points: 4
 *
 * Given an undirected graph with V vertices numbered from 0 to V-1 and E edges, represented by 2d array edges[][], where edges[i]=[u,v] represents the edge between the vertices u and v. Determine whether a specific edge between two vertices (c, d) is a bridge.
 *
 * Note:
 * An edge is called a bridge if removing it increases the number of connected components of the graph.
 * if there’s only one path between c and d (which is the edge itself), then that edge is a bridge.
 *
 * Examples :
 *
 * Input:
 *
 * c = 1, d = 2
 * Output: true
 * Explanation: From the graph, we can clearly see that blocking the edge 1-2 will result in disconnection of the graph.
 * Hence, it is a Bridge.
 *
 * Input:
 * c = 0, d = 2
 * Output: false
 *
 * Explanation:
 * Blocking the edge between nodes 0 and 2 won't affect the connectivity of the graph.
 * So, it's not a Bridge Edge. All the Bridge Edges in the graph are marked with a blue line in the above image.
 * Constraints:
 * 1 ≤ V, E ≤ 10^5
 * 0 ≤ c, d ≤ V-1
 */

/************************************************************ C++ ************************************************/

// Approach: DFS using Tarjan's algorithm to compute discovery and low times; then check if the given edge's removal disconnects the graph.
// Time Complexity: O(V + E) as each vertex and edge is visited once during DFS.
// Space Complexity: O(V + E) due to the recursion stack, visited, disc, low arrays, and the adjacency list.
class Solution {
public:
    // Helper function to perform DFS and update discovery and low values.
    void dfs(int u, int parent, vector<bool>& visited, vector<int>& disc, vector<int>& low,
             const vector<vector<int>>& adj, int& time, int c, int d, bool& bridgeFound) {
        visited[u] = true;                          // Mark current node as visited.
        disc[u]    = low[u] = ++time;               // Initialize discovery time and low value.

        for (int v : adj[u]) {                      // Iterate through all neighbors of u.
            // Skip the edge going back to the parent in the DFS tree.
            if (v == parent) {
                continue;
            }

            if (!visited[v]) {
                // Explore vertex v with u as its parent.
                dfs(v, u, visited, disc, low, adj, time, c, d, bridgeFound);

                // After returning, update the low value for u based on v's low value.
                low[u] = min(low[u], low[v]);

                // Check if the edge (u,v) is a bridge.
                if (low[v] > disc[u]) {
                    // Since the graph is undirected, the edge can be represented as (c,d) or (d,c).
                    if ((u == c && v == d) || (u == d && v == c)) {
                        bridgeFound = true;          // Mark that the specific edge is a bridge.
                    }
                }
            }else {
                // If v is already visited and is not the parent, update low[u] based on its discovery time.
                low[u] = min(low[u], disc[v]);
            }
        }
    }
    bool isBridge(int V, vector<vector<int>>& edges, int c, int d) {
        // Create an adjacency list for the graph.
        vector<vector<int>> adj(V);

        for (auto& edge : edges) {
            int u = edge[0], v = edge[1];
            adj[u].push_back(v);
            adj[v].push_back(u);     // Since the graph is undirected, add both directions.
        }

        // Initialize DFS data structures.
        vector<bool> visited(V, false);
        vector<int>  disc(V, -1);
        vector<int>  low(V, -1);
        int          time        = 0;
        bool         bridgeFound = false;

        // In case the graph is not fully connected, run DFS for every unvisited vertex.
        for (int i = 0; i < V; i++) {
            if (!visited[i]) {
                dfs(i, -1, visited, disc, low, adj, time, c, d, bridgeFound);
            }
        }

        return bridgeFound;
    }
};

/*
 * Dry Run:
 * Consider the following undirected graph:
 *    Number of vertices V = 5
 *    Edges: { {0,1}, {1,2}, {2,3}, {3,4}, {1,4} }
 * Given edge to check: (1,2)
 *
 * Initial state:
 *   visited  = [false, false, false, false, false]
 *   disc     = [-1, -1, -1, -1, -1]
 *   low      = [-1, -1, -1, -1, -1]
 *   time     = 0
 *   bridgeFound = false
 *
 * Step 1: DFS starts at vertex 0 (i=0 since visited[0] is false).
 *   Call: dfs(0, parent = -1)
 *     visited[0] becomes true
 *     time increments to 1; set disc[0] = low[0] = 1
 *     Neighbors of 0: {1}
 *
 * Step 2: For vertex 0, process neighbor 1.
 *   Since visited[1] is false, call: dfs(1, parent = 0)
 *     visited[1] becomes true
 *     time increments to 2; set disc[1] = low[1] = 2
 *     Neighbors of 1: {0, 2, 4}
 *     - For neighbor 0: skip, as it is the parent.
 *
 * Step 3: For vertex 1, process neighbor 2.
 *   Since visited[2] is false, call: dfs(2, parent = 1)
 *     visited[2] becomes true
 *     time increments to 3; set disc[2] = low[2] = 3
 *     Neighbors of 2: {1, 3}
 *     - For neighbor 1: skip, as it is the parent.
 *
 * Step 4: For vertex 2, process neighbor 3.
 *   Since visited[3] is false, call: dfs(3, parent = 2)
 *     visited[3] becomes true
 *     time increments to 4; set disc[3] = low[3] = 4
 *     Neighbors of 3: {2, 4}
 *     - For neighbor 2: skip, as it is the parent.
 *
 * Step 5: For vertex 3, process neighbor 4.
 *   Since visited[4] is false, call: dfs(4, parent = 3)
 *     visited[4] becomes true
 *     time increments to 5; set disc[4] = low[4] = 5
 *     Neighbors of 4: {3, 1}
 *     - For neighbor 3: skip, as it is the parent.
 *     - For neighbor 1: already visited (and not parent),
 *           update low[4] = min(low[4], disc[1]) = min(5, 2) = 2.
 *   End of DFS(4): low[4] = 2.
 *
 * Step 6: Back to DFS(3):
 *   After DFS(4) returns, update low[3] = min(low[3], low[4]) = min(4, 2) = 2.
 *   Check bridge condition for edge (3,4):
 *       If (low[4] > disc[3]) → 2 > 4 is false, so edge (3,4) is not a bridge.
 *   DFS(3) completes with low[3] = 2.
 *
 * Step 7: Back to DFS(2):
 *   After DFS(3) returns, update low[2] = min(low[2], low[3]) = min(3, 2) = 2.
 *   Check bridge condition for edge (2,3):
 *       If (low[3] > disc[2]) → 2 > 3 is false, so edge (2,3) is not a bridge.
 *   DFS(2) completes with low[2] = 2.
 *
 * Step 8: Back to DFS(1):
 *   After DFS(2) returns, update low[1] = min(low[1], low[2]) = min(2, 2) = 2.
 *   Check bridge condition for edge (1,2):
 *       If (low[2] > disc[1]) → 2 > 2 is false (note: condition requires strictly greater),
 *       so edge (1,2) is not marked as a bridge.
 *   Next, for DFS(1) continue to neighbor 4.
 *     For neighbor 4: already visited, update low[1] = min(low[1], disc[4]) = min(2, 5) = 2.
 *   DFS(1) completes with low[1] = 2.
 *
 * Step 9: Back to DFS(0):
 *   After DFS(1) returns, update low[0] = min(low[0], low[1]) = min(1, 2) = 1.
 *   DFS(0) completes with low[0] = 1.
 *
 * Final Status:
 *   visited  = [true, true, true, true, true]
 *   disc     = [1, 2, 3, 4, 5]
 *   low      = [1, 2, 2, 2, 2]
 *   bridgeFound = false, as no edge met the strict condition for being a bridge.
 *
 * Therefore, the function returns false for edge (1,2), indicating that removing edge (1,2) does not disconnect the graph.
 */

/************************************************************ JAVA ************************************************/

// Approach: DFS using Tarjan's algorithm to compute discovery and low times; then check if the given edge's removal disconnects the graph.
// Time Complexity: O(V + E) as each vertex and edge is visited once during DFS.
// Space Complexity: O(V + E) due to the recursion stack, visited, disc, low arrays, and the adjacency list.
class Solution {
    public boolean isBridge(int V, int[][] edges, int c, int d) {
        // Create an adjacency list for the graph.
        ArrayList<Integer>[] adj = new ArrayList[V];
        for (int i = 0; i < V; i++) {
            adj[i] = new ArrayList<>();
        }
        for (int[] edge : edges) {
            int u = edge[0], v = edge[1];
            adj[u].add(v);
            adj[v].add(u); // Since the graph is undirected, add both directions.
        }

        // Initialize DFS data structures.
        boolean[] visited = new boolean[V];
        int[] disc        = new int[V];
        int[] low         = new int[V];
        Arrays.fill(disc, -1);
        Arrays.fill(low, -1);

        // Use an array for time to simulate pass-by-reference.
        int[] time = new int[] { 0 };
        // Use a single-element boolean array to track if the given edge is found to be a bridge.
        boolean[] bridgeFound = new boolean[] { false };

        // In case the graph is not fully connected, run DFS for every unvisited vertex.
        for (int i = 0; i < V; i++) {
            if (!visited[i]) {
                dfs(i, -1, visited, disc, low, adj, time, c, d, bridgeFound);
            }
        }

        return bridgeFound[0];
    }
    // Helper function to perform DFS and update discovery and low values.
    private void dfs(int u, int parent, boolean[] visited, int[] disc, int[] low, ArrayList<Integer>[] adj,
                     int[] time, int c, int d, boolean[] bridgeFound) {
        visited[u] = true;                      // Mark current node as visited.
        disc[u]    = low[u] = ++time[0];        // Initialize discovery time and low value.

        for (int v : adj[u]) {                  // Iterate through all neighbors of u.
            // Skip the edge going back to the parent in the DFS tree.
            if (v == parent) {
                continue;
            }

            if (!visited[v]) {
                // Explore vertex v with u as its parent.
                dfs(v, u, visited, disc, low, adj, time, c, d, bridgeFound);

                // After returning, update the low value for u based on v's low value.
                low[u] = Math.min(low[u], low[v]);

                // Check if the edge (u,v) is a bridge.
                if (low[v] > disc[u]) {
                    // Since the graph is undirected, the edge can be represented as (c,d) or (d,c).
                    if ((u == c && v == d) || (u == d && v == c)) {
                        bridgeFound[0] = true;      // Mark that the specific edge is a bridge.
                    }
                }
            } else {
                // If v is already visited and is not the parent, update low[u] based on its discovery time.
                low[u] = Math.min(low[u], disc[v]);
            }
        }
    }
}

/*
 * Dry Run:
 * Consider the following undirected graph:
 *    Number of vertices V = 5
 *    Edges: { {0,1}, {1,2}, {2,3}, {3,4}, {1,4} }
 * Given edge to check: (1,2)
 *
 * Initial state:
 *   visited    = [false, false, false, false, false]
 *   disc       = [-1, -1, -1, -1, -1]
 *   low        = [-1, -1, -1, -1, -1]
 *   time       = 0
 *   bridgeFound= false
 *
 * Step 1: DFS starts at vertex 0 (i=0 since visited[0] is false).
 *   Call: dfs(0, parent = -1)
 *     visited[0] becomes true.
 *     time increments to 1; set disc[0] = low[0] = 1.
 *     Neighbors of 0: {1}
 *
 * Step 2: For vertex 0, process neighbor 1.
 *   Since visited[1] is false, call: dfs(1, parent = 0)
 *     visited[1] becomes true.
 *     time increments to 2; set disc[1] = low[1] = 2.
 *     Neighbors of 1: {0, 2, 4}.
 *     - For neighbor 0: skip, as it is the parent.
 *
 * Step 3: For vertex 1, process neighbor 2.
 *   Since visited[2] is false, call: dfs(2, parent = 1)
 *     visited[2] becomes true.
 *     time increments to 3; set disc[2] = low[2] = 3.
 *     Neighbors of 2: {1, 3}.
 *     - For neighbor 1: skip, as it is the parent.
 *
 * Step 4: For vertex 2, process neighbor 3.
 *   Since visited[3] is false, call: dfs(3, parent = 2)
 *     visited[3] becomes true.
 *     time increments to 4; set disc[3] = low[3] = 4.
 *     Neighbors of 3: {2, 4}.
 *     - For neighbor 2: skip, as it is the parent.
 *
 * Step 5: For vertex 3, process neighbor 4.
 *   Since visited[4] is false, call: dfs(4, parent = 3)
 *     visited[4] becomes true.
 *     time increments to 5; set disc[4] = low[4] = 5.
 *     Neighbors of 4: {3, 1}.
 *     - For neighbor 3: skip, as it is the parent.
 *     - For neighbor 1: already visited (and not parent),
 *           update low[4] = min(low[4], disc[1]) = min(5, 2) = 2.
 *   End of DFS(4): low[4] becomes 2.
 *
 * Step 6: Back to DFS(3):
 *   After DFS(4) returns, update low[3] = min(low[3], low[4]) = min(4, 2) = 2.
 *   Check bridge condition for edge (3,4):
 *       If (low[4] > disc[3]) → 2 > 4 is false, so edge (3,4) is not a bridge.
 *   DFS(3) completes with low[3] = 2.
 *
 * Step 7: Back to DFS(2):
 *   After DFS(3) returns, update low[2] = min(low[2], low[3]) = min(3, 2) = 2.
 *   Check bridge condition for edge (2,3):
 *       If (low[3] > disc[2]) → 2 > 3 is false, so edge (2,3) is not a bridge.
 *   DFS(2) completes with low[2] = 2.
 *
 * Step 8: Back to DFS(1):
 *   After DFS(2) returns, update low[1] = min(low[1], low[2]) = min(2, 2) = 2.
 *   Check bridge condition for edge (1,2):
 *       If (low[2] > disc[1]) → 2 > 2 is false (condition requires strictly greater),
 *       so edge (1,2) is not marked as a bridge.
 *   Next, for DFS(1) continue to neighbor 4.
 *     For neighbor 4: already visited, update low[1] = min(low[1], disc[4]) = min(2, 5) = 2.
 *   DFS(1) completes with low[1] = 2.
 *
 * Step 9: Back to DFS(0):
 *   After DFS(1) returns, update low[0] = min(low[0], low[1]) = min(1, 2) = 1.
 *   DFS(0) completes with low[0] = 1.
 *
 * Final State:
 *   visited    = [true, true, true, true, true]
 *   disc       = [1, 2, 3, 4, 5]
 *   low        = [1, 2, 2, 2, 2]
 *   bridgeFound= false, as no edge met the strict condition for being a bridge.
 *
 * Therefore, the function returns false for edge (1,2), indicating that removing edge (1,2) does not disconnect the graph.
 */
