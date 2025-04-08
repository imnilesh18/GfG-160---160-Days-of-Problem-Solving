/*
 * Articulation Point - II
 *
 * Difficulty: Hard Accuracy: 55.15% Submissions: 11K+ Points: 8 Average Time: 30m
 *
 * You are given an undirected graph with V vertices and E edges. The graph is represented as a 2D array edges[][], where each element edges[i] = [u, v] indicates an undirected edge between vertices u and v.
 * Your task is to return all the articulation points (or cut vertices) in the graph.
 * An articulation point is a vertex whose removal, along with all its connected edges, increases the number of connected components in the graph.
 * Note: The graph may be disconnected, i.e., it may consist of more than one connected component.
 * If no such point exists, return {-1}.
 *
 * Examples :
 * Input: V = 5, edges[][] = [[0, 1], [1, 4], [4, 3], [4, 2], [2, 3]]
 * Output: [1, 4]
 * Explanation: Removing the vertex 1 or 4 will disconnects the graph as-
 *
 * Input: V = 4, edges[][] = [[0, 1], [0, 2]]
 * Output: [0]
 * Explanation: Removing the vertex 0 will increase the number of disconnected components to 3.
 *
 * Constraints:
 * 1 ≤ V, E ≤ 10^4
 */
/************************************************************ C++ ************************************************/

// Approach: Use Tarjan's algorithm (DFS with discovery and low times) to find articulation points in O(V+E) time.
// Time Complexity: O(V + E) as we perform one DFS traversal of the graph.
// Space Complexity: O(V + E) for the recursive call stack, adjacency list, and auxiliary arrays.
class Solution {
public:
    vector<int> articulationPoints(int V, vector<vector<int>>& edges) {
        // Build adjacency list from the edge list
        vector<vector<int>> adj(V);

        for (auto& edge : edges) {
            int u = edge[0], v = edge[1];
            adj[u].push_back(v);
            adj[v].push_back(u);
        }

        // Arrays to store discovery times and low values
        vector<int> disc(V, -1), low(V, -1);
        // To store parent vertex in DFS tree, -1 indicates no parent (root)
        vector<int> parent(V, -1);
        // Boolean array to mark articulation points
        vector<bool> isArticulation(V, false);
        int          time = 0; // Global time counter for discovery times

        // DFS function to explore the graph and compute discovery/low times.
        function<void(int)> dfs = [&](int u) {
                                      // Set discovery time and low value
                                      disc[u] = low[u] = ++time;
                                      int children = 0; // Number of children in DFS tree for u

                                      // Explore all adjacent vertices of u
                                      for (int v : adj[u]) {
                                          if (disc[v] == -1) { // v is not visited
                                              parent[v] = u;
                                              children++;
                                              dfs(v); // Recurse
                                              // After recursion, update low value of u
                                              low[u] = min(low[u], low[v]);

                                              // Articulation point check:
                                              // Case 1: u is root of DFS tree and has more than one child.
                                              if (parent[u] == -1 && children > 1) {
                                                  isArticulation[u] = true;
                                              }
                                              // Case 2: If u is not root and low value of one of its child is more than or equal to disc[u].
                                              if (parent[u] != -1 && low[v] >= disc[u]) {
                                                  isArticulation[u] = true;
                                              }
                                          }else if (v != parent[u]) {
                                              // Update low value for back edge (ignore the edge to parent)
                                              low[u] = min(low[u], disc[v]);
                                          }
                                      }
                                  };

        // For disconnected graph, run DFS from all vertices not yet visited
        for (int i = 0; i < V; i++) {
            if (disc[i] == -1) {
                dfs(i);
            }
        }

        // Collect all articulation points
        vector<int> res;
        for (int i = 0; i < V; i++) {
            if (isArticulation[i]) {
                res.push_back(i);
            }
        }

        if (res.empty()) {
            return { -1 };    // Return -1 if no articulation points exist
        }
        // Optional: sort the result if needed
        sort(res.begin(), res.end());
        return res;
    }
};

/*
 *
 * Dry Run
 *
 * Example: V = 5, edges = [[0, 1], [1, 4], [4, 3], [4, 2], [2, 3]]
 *
 * Visual Representation of the Graph:
 *         Indices:    0    1    2    3    4
 *                  +----+----+----+----+----+
 *         Vertices: | 0  | 1  | 2  | 3  | 4  |
 *                  +----+----+----+----+----+
 *
 * Adjacency List after construction:
 *    0: [1]
 *    1: [0, 4]
 *    2: [4, 3]
 *    3: [4, 2]
 *    4: [1, 3, 2]
 *
 * DFS Traversal (Using Tarjan's algorithm):
 *
 * Start DFS from vertex 0 (if not visited):
 *  - For vertex 0:
 *      disc[0] = low[0] = 1, time becomes 1.
 *      children count = 0.
 *      Explore neighbor: 1
 *          Vertex 1 not visited:
 *              parent[1] = 0, children for 0 becomes 1.
 *              DFS(1):
 *                disc[1] = low[1] = 2, time becomes 2.
 *                children count = 0.
 *                Explore neighbor: 0 (already visited and is parent, ignore).
 *                Explore neighbor: 4
 *                   Vertex 4 not visited:
 *                       parent[4] = 1, children for 1 becomes 1.
 *                       DFS(4):
 *                           disc[4] = low[4] = 3, time becomes 3.
 *                           children count = 0.
 *                           Explore neighbor: 1 (parent, ignore).
 *                           Explore neighbor: 3
 *                               Vertex 3 not visited:
 *                                   parent[3] = 4, children for 4 becomes 1.
 *                                   DFS(3):
 *                                       disc[3] = low[3] = 4, time becomes 4.
 *                                       children count = 0.
 *                                       Explore neighbor: 4 (parent, ignore).
 *                                       Explore neighbor: 2
 *                                           Vertex 2 not visited:
 *                                               parent[2] = 3, children for 3 becomes 1.
 *                                               DFS(2):
 *                                                   disc[2] = low[2] = 5, time becomes 5.
 *                                                   children count = 0.
 *                                                   Explore neighbor: 4
 *                                                       4 is visited and not parent of 2.
 *                                                       Update low[2] = min(low[2], disc[4]) = min(5, 3) = 3.
 *                                                   Explore neighbor: 3 (parent, ignore).
 *                                               End DFS(2):
 *                                               low[2] remains 3.
 *                                           Back in DFS(3):
 *                                           Update low[3] = min(low[3], low[2]) = min(4, 3) = 3.
 *                                   End DFS(3):
 *                                   For vertex 3, since parent is 4 and low[2] (3) < disc[3] (4), no articulation condition met.
 *                                   low[3] remains 3.
 *                           Back in DFS(4):
 *                           Update low[4] = min(low[4], low[3]) = min(3, 3) = 3.
 *                           Explore neighbor: 2
 *                               Vertex 2 already visited, and 2 is not parent of 4,
 *                               Update low[4] = min(low[4], disc[2]) = min(3, 5) = 3.
 *                       End DFS(4):
 *                       For vertex 4, parent is 1 and low[3] (3) >= disc[4] (3), so vertex 4 is an articulation point.
 *                       low[4] remains 3.
 *                Back in DFS(1):
 *                Update low[1] = min(low[1], low[4]) = min(2, 3) = 2.
 *          End DFS(1):
 *          For vertex 1, parent is 0 and low[4] (3) >= disc[1] (2), so vertex 1 is an articulation point.
 *          Update low[0] = min(low[0], low[1]) = min(1, 2) = 1.
 *  - End DFS(0):
 *  - For vertex 0 (being the root), children count is 1 → does not satisfy articulation condition.
 *
 * Articulation Points Identified:
 *   Vertex 1 (from DFS(1) check) and Vertex 4 (from DFS(4) check)
 *
 * Final Result: [1, 4]
 *
 */

/************************************************************ JAVA ************************************************/

// Approach: Use Tarjan's algorithm (DFS with discovery and low times) to find articulation points in O(V+E) time.
// Time Complexity: O(V + E) as we perform one DFS traversal of the graph.
// Space Complexity: O(V + E) for the recursive call stack, adjacency list, and auxiliary arrays.
class Solution {
    // Main function to return articulation points
    static ArrayList<Integer> articulationPoints(int V, int[][] edges) {
        // Build adjacency list from the edge list
        ArrayList<Integer>[] adj = new ArrayList[V];
        for (int i = 0; i < V; i++) {
            adj[i] = new ArrayList<>();
        }
        for (int[] edge : edges) {
            int u = edge[0], v = edge[1];
            adj[u].add(v);
            adj[v].add(u);
        }

        // Arrays to store discovery times and low values, initialized to -1 indicating unvisited nodes.
        int[] disc = new int[V];
        int[] low  = new int[V];
        Arrays.fill(disc, -1);
        Arrays.fill(low, -1);

        // Array to store parent for each vertex in DFS tree, -1 indicates no parent (root)
        int[] parent = new int[V];
        Arrays.fill(parent, -1);

        // Boolean array to mark articulation points
        boolean[] isArticulation = new boolean[V];

        // Global time counter wrapped in an array for mutability
        int[] time = new int[1]; // initially time[0] = 0

        // For disconnected graphs, run DFS for every vertex not yet visited
        for (int i = 0; i < V; i++) {
            if (disc[i] == -1) {
                dfs(i, adj, disc, low, parent, isArticulation, time);
            }
        }

        // Collect all articulation points into a result list
        ArrayList<Integer> res = new ArrayList<>();
        for (int i = 0; i < V; i++) {
            if (isArticulation[i]) {
                res.add(i);
            }
        }

        // If no articulation point exists, return {-1}
        if (res.isEmpty()) {
            res.add(-1);
        }

        Collections.sort(res); // Optional: sort the result if required
        return res;
    }
    // DFS helper method to compute discovery and low values.
    private static void dfs(int u, ArrayList<Integer>[] adj, int[] disc, int[] low, int[] parent,
                            boolean[] isArticulation, int[] time) {
        // Set discovery time and low value for vertex u
        disc[u] = low[u] = ++time[0];
        int children = 0; // Count of children in DFS tree for u

        // Traverse all adjacent vertices of u
        for (int v : adj[u]) {
            if (disc[v] == -1) { // If vertex v is not visited
                parent[v] = u;
                children++;
                dfs(v, adj, disc, low, parent, isArticulation, time);

                // Update low value of u based on the low value of its child v
                low[u] = Math.min(low[u], low[v]);

                // Articulation point check:
                // Case 1: u is root of DFS tree and has more than one child
                if (parent[u] == -1 && children > 1) {
                    isArticulation[u] = true;
                }
                // Case 2: u is not root and low value of child v is at least disc[u]
                if (parent[u] != -1 && low[v] >= disc[u]) {
                    isArticulation[u] = true;
                }
            }else if (v != parent[u])  { // For back edge (ignore edge to parent)
                low[u] = Math.min(low[u], disc[v]);
            }
        }
    }
}

/*
 *
 * Dry Run
 *
 * Example: V = 5, edges = [[0, 1], [1, 4], [4, 3], [4, 2], [2, 3]]
 *
 * Visual Representation of the Graph:
 *         Indices:     0    1    2    3    4
 *                  +-----+-----+-----+-----+-----+
 *         Vertices: |  0  |  1  |  2  |  3  |  4  |
 *                  +-----+-----+-----+-----+-----+
 *
 * Adjacency List after construction:
 *   Vertex 0: [1]
 *   Vertex 1: [0, 4]
 *   Vertex 2: [4, 3]
 *   Vertex 3: [4, 2]
 *   Vertex 4: [1, 3, 2]
 *
 * DFS Traversal using Tarjan's algorithm:
 *
 * Start DFS from vertex 0 (if not visited):
 *  - For vertex 0:
 *      disc[0] = low[0] = 1, time becomes 1.
 *      children count = 0.
 *      Explore neighbor: 1.
 *          Vertex 1 is unvisited:
 *              parent[1] = 0, children of 0 becomes 1.
 *              DFS(1):
 *                disc[1] = low[1] = 2, time becomes 2.
 *                children count = 0.
 *                Explore neighbor: 0 (already visited and parent, ignore).
 *                Explore neighbor: 4.
 *                   Vertex 4 is unvisited:
 *                       parent[4] = 1, children of 1 becomes 1.
 *                       DFS(4):
 *                           disc[4] = low[4] = 3, time becomes 3.
 *                           children count = 0.
 *                           Explore neighbor: 1 (parent, ignore).
 *                           Explore neighbor: 3.
 *                               Vertex 3 is unvisited:
 *                                   parent[3] = 4, children of 4 becomes 1.
 *                                   DFS(3):
 *                                       disc[3] = low[3] = 4, time becomes 4.
 *                                       children count = 0.
 *                                       Explore neighbor: 4 (parent, ignore).
 *                                       Explore neighbor: 2.
 *                                           Vertex 2 is unvisited:
 *                                               parent[2] = 3, children of 3 becomes 1.
 *                                               DFS(2):
 *                                                   disc[2] = low[2] = 5, time becomes 5.
 *                                                   children count = 0.
 *                                                   Explore neighbor: 4:
 *                                                       4 is visited and not parent of 2.
 *                                                       Update low[2] = min(low[2], disc[4]) = min(5, 3) = 3.
 *                                                   Explore neighbor: 3 (parent, ignore).
 *                                               End DFS(2):
 *                                               low[2] remains 3.
 *                                           Back in DFS(3):
 *                                           Update low[3] = min(low[3], low[2]) = min(4, 3) = 3.
 *                                   End DFS(3):
 *                                   For vertex 3, parent is 4 and low[2] (3) < disc[3] (4); not an articulation point.
 *                                   low[3] remains 3.
 *                           Back in DFS(4):
 *                           Update low[4] = min(low[4], low[3]) = min(3, 3) = 3.
 *                           Explore neighbor: 2:
 *                               Vertex 2 is already visited, and 2 is not parent of 4.
 *                               Update low[4] = min(low[4], disc[2]) = min(3, 5) = 3.
 *                       End DFS(4):
 *                       For vertex 4, since parent[1] != -1 and low[3] (3) >= disc[4] (3),
 *                       mark vertex 4 as an articulation point.
 *                       low[4] remains 3.
 *                Back in DFS(1):
 *                Update low[1] = min(low[1], low[4]) = min(2, 3) = 2.
 *          End DFS(1):
 *          For vertex 1, since parent[0] == -1 (0 is root) is false but low[4] (3) >= disc[1] (2),
 *          mark vertex 1 as an articulation point.
 *          Update low[0] = min(low[0], low[1]) = min(1, 2) = 1.
 *  - End DFS(0):
 *  - For vertex 0 (root) with only one child, no articulation condition.
 *
 * Articulation Points Identified:
 *   Vertex 1 (from DFS(1) check) and Vertex 4 (from DFS(4) check)
 *
 * Final Result: [1, 4]
 */
