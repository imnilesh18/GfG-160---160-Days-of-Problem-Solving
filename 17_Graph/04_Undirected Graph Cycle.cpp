/*
 * Undirected Graph Cycle
 *
 * Difficulty: Medium Accuracy: 30.13% Submissions: 541K+ Points: 4 Average Time: 20m
 *
 * Given an undirected graph with V vertices and E edges, represented as a 2D vector edges[][], where each entry edges[i] = [u, v] denotes an edge between vertices u and v, determine whether the graph contains a cycle or not.
 *
 * Examples:
 *
 * Input: V = 4, E = 4, edges[][] = [[0, 1], [0, 2], [1, 2], [2, 3]]
 * Output: true
 * Explanation:
 * 1 -> 2 -> 0 -> 1 is a cycle.
 *
 * Input: V = 4, E = 3, edges[][] = [[0, 1], [1, 2], [2, 3]]
 * Output: false
 * Explanation:
 * No cycle in the graph.
 *
 * Constraints:
 * 1 ≤ V ≤ 10^5
 * 1 ≤ E = edges.size() ≤ 10^5
 */

/************************************************************ C++ ************************************************/

// Approach 1 (DFS): We use DFS to traverse the graph, marking nodes as visited. When we find an already visited node (not the parent), we have detected a cycle.
// Time Complexity: O(V + E) - Every vertex and edge is processed once during DFS.
// Space Complexity: O(V + E) - Space for the visited array, recursion stack, and the adjacency list.
class Solution {
public:
    // DFS helper to detect a cycle in an undirected graph.
    bool isCycleDFS(unordered_map<int, vector<int>>& adj, int u, vector<bool>& visited, int parent) {
        visited[u] = true; // Mark current node as visited

        // Explore all adjacent nodes of u
        for (int& v : adj[u]) {
            if (v == parent) { // Skip the edge to the parent node to avoid false detection
                continue;
            }
            if (visited[v]) { // If v is already visited and not parent, cycle is detected
                return true;
            }
            if (isCycleDFS(adj, v, visited, u)) { // Recursively check deeper nodes
                return true;
            }
        }
        return false; // No cycle found in the current DFS path
    }

    // Main function to detect a cycle in the graph.
    bool isCycle(int V, vector<vector<int>>& edges) {
        vector<bool> visited(V, false);       // Array to keep track of visited vertices
        unordered_map<int, vector<int>> adj; // Adjacency list representation

        // Build the graph from the edge list
        for (auto& edge : edges) {
            int u = edge[0], v = edge[1];
            adj[u].push_back(v);
            adj[v].push_back(u);
        }

        // Check every component of the graph for cycles
        for (int i = 0; i < V; i++) {
            if (!visited[i] && isCycleDFS(adj, i, visited, -1)) {
                return true;
            }
        }
        return false; // No cycle detected in any component
    }
};

/*
 *
 * Dry Run Visual Representation:
 *
 * Graph Structure:
 *
 *           0 --- 1 --- 2
 *                 |     |
 *                 4 --- 3
 *
 * Edges:
 *   0-1, 1-2, 1-4, 2-3, 3-4
 *
 *-----------------------------------------------------------
 * Step 1: Start DFS at Vertex 0 (t = time of visit)
 *
 * Visited Array:
 *  +-----+-----+-----+-----+-----+
 *  |  0  |  1  |  2  |  3  |  4  |
 *  +-----+-----+-----+-----+-----+
 *  |  T  |  F  |  F  |  F  |  F  |
 *  +-----+-----+-----+-----+-----+
 *     ^
 *  (Current: 0, t=1, Parent: -1)
 *
 * Graph State:
 *           (0: t=1, p=-1)
 *                |
 *         (others unvisited)
 *
 *-----------------------------------------------------------
 * Step 2: DFS from Vertex 0 -> Vertex 1
 *
 * Update:
 *  Vertex 1: t=2, Parent = 0
 *
 * Visited Array:
 *  +-----+-----+-----+-----+-----+
 *  |  0  |  1  |  2  |  3  |  4  |
 *  +-----+-----+-----+-----+-----+
 *  |  T  |  T  |  F  |  F  |  F  |
 *  +-----+-----+-----+-----+-----+
 *           ^
 *  (Current: 1, t=2, Parent: 0)
 *
 * Graph State:
 *           (0: t=1, p=-1) --- (1: t=2, p=0)
 *
 *-----------------------------------------------------------
 * Step 3: DFS from Vertex 1 -> Vertex 2
 *
 * Update:
 *  Vertex 2: t=3, Parent = 1
 *
 * Visited Array:
 *  +-----+-----+-----+-----+-----+
 *  |  0  |  1  |  2  |  3  |  4  |
 *  +-----+-----+-----+-----+-----+
 *  |  T  |  T  |  T  |  F  |  F  |
 *  +-----+-----+-----+-----+-----+
 *                 ^
 *  (Current: 2, t=3, Parent: 1)
 *
 * Graph State:
 *           (0: t=1, p=-1) --- (1: t=2, p=0) --- (2: t=3, p=1)
 *
 *-----------------------------------------------------------
 * Step 4: DFS from Vertex 2 -> Vertex 3
 *
 * Update:
 *  Vertex 3: t=4, Parent = 2
 *
 * Visited Array:
 *  +-----+-----+-----+-----+-----+
 *  |  0  |  1  |  2  |  3  |  4  |
 *  +-----+-----+-----+-----+-----+
 *  |  T  |  T  |  T  |  T  |  F  |
 *  +-----+-----+-----+-----+-----+
 *                       ^
 *  (Current: 3, t=4, Parent: 2)
 *
 * Graph State:
 *           (0: t=1, p=-1) --- (1: t=2, p=0) --- (2: t=3, p=1)
 *                                                 |
 *                                                (3: t=4, p=2)
 *
 *-----------------------------------------------------------
 * Step 5: DFS from Vertex 3 -> Vertex 4
 *
 * Update:
 *  Vertex 4: t=5, Parent = 3
 *
 * Visited Array:
 *  +-----+-----+-----+-----+-----+
 *  |  0  |  1  |  2  |  3  |  4  |
 *  +-----+-----+-----+-----+-----+
 *  |  T  |  T  |  T  |  T  |  T  |
 *  +-----+-----+-----+-----+-----+
 *                             ^
 *  (Current: 4, t=5, Parent: 3)
 *
 * Graph State:
 *           (0: t=1, p=-1) --- (1: t=2, p=0) --- (2: t=3, p=1)
 *                               |                 |
 *                              (4: t=5, p=3) --- (3: t=4, p=2)
 *
 *-----------------------------------------------------------
 * Step 6: DFS from Vertex 4 -> Check Neighbors
 *
 * Neighbors of Vertex 4: {1, 3}
 *   - For neighbor 3: It is the parent of 4 → Skip.
 *   - For neighbor 1: Already visited and not the parent → Cycle Detected!
 *
 * Final Corrected Graph Representation (Cycle Detection):
 *
 *           (0: t=1, p=-1) -- (1: t=2, p=0) ---- (2: t=3, p=1)
 *                              |                  |
 *                             (4: t=5, p=3) ---- (3: t=4, p=2)
 *
 * Cycle detected via the edge from 4 to 1.
 *
 *-----------------------------------------------------------
 * Final Outcome: **Cycle is detected in the graph.**
 */

// Approach 2 (BFS): Use BFS to detect a cycle in an undirected graph by checking if a visited neighbor is not the parent.
// Time Complexity: O(V + E) - Every vertex and edge is processed once during BFS.
// Space Complexity: O(V + E) - Space for the visited array, queue, and the adjacency list.
class Solution {
public:
    // BFS helper to detect a cycle in an undirected graph.
    // Parameters:
    //   adj: Adjacency list representing the graph.
    //   u: The starting vertex for BFS.
    //   visited: Array tracking visited vertices.
    // Returns true if a cycle is detected.
    bool isCycleBFS(unordered_map<int, vector<int>>& adj, int u, vector<bool>& visited) {
        // Queue stores pairs of (current vertex, parent vertex)
        queue<pair<int, int>> que;

        // Initialize the BFS with the starting vertex u and parent -1 (none)
        que.push({ u, -1 });
        visited[u] = true;  // Mark the starting vertex as visited

        // Process until the queue is empty
        while (!que.empty()) {
            // Get the front element from the queue
            pair<int, int> P = que.front();
            que.pop();

            int source = P.first;   // Current vertex being processed
            int parent = P.second;  // Parent of the current vertex

            // Traverse all adjacent vertices of the current vertex
            for (int& v : adj[source]) {
                // If the neighbor hasn't been visited, mark it and add to the queue
                if (!visited[v]) {
                    visited[v] = true;
                    que.push({ v, source });
                }
                // If the neighbor is visited and it's not the parent, a cycle is detected
                else if (v != parent) {
                    return true;
                }
            }
        }
        return false;  // Return false if no cycle is detected after processing all vertices in this component
    }

    // Main function to detect a cycle in the graph using BFS.
    // Parameters:
    //   V: Number of vertices.
    //   edges: List of edges where each edge is represented as a vector of two integers.
    // Returns true if the graph contains a cycle.
    bool isCycle(int V, vector<vector<int>>& edges) {
        vector<bool> visited(V, false);       // Array to keep track of visited vertices
        unordered_map<int, vector<int>> adj; // Adjacency list representation of the graph

        // Build the graph from the edge list
        for (auto& edge : edges) {
            int u = edge[0], v = edge[1];
            adj[u].push_back(v);
            adj[v].push_back(u);
        }

        // Check every connected component of the graph for cycles using BFS
        for (int i = 0; i < V; i++) {
            if (!visited[i] && isCycleBFS(adj, i, visited)) {
                return true;
            }
        }
        return false;  // No cycle detected in any component
    }
};

/*
 *
 * Dry Run Visual Representation for BFS Cycle Detection:
 *
 * Graph Structure (Before BFS starts):
 *
 *           0 --- 1 --- 2
 *                 |     |
 *                 4 --- 3
 *
 * Edges:
 *   0-1, 1-2, 1-4, 2-3, 3-4
 *
 * Initial State:
 *   Visited Array:
 *    +-----+-----+-----+-----+-----+
 *    |  0  |  1  |  2  |  3  |  4  |
 *    +-----+-----+-----+-----+-----+
 *    |  F  |  F  |  F  |  F  |  F  |
 *    +-----+-----+-----+-----+-----+
 *
 *   Queue: empty
 *
 *-----------------------------------------------------------
 * Step 1: Start BFS at Vertex 0:
 *   - Enqueue: (0, -1)
 *   - Mark visited[0] = T
 *
 *   Visited Array:
 *    +-----+-----+-----+-----+-----+
 *    |  0  |  1  |  2  |  3  |  4  |
 *    +-----+-----+-----+-----+-----+
 *    |  T  |  F  |  F  |  F  |  F  |
 *    +-----+-----+-----+-----+-----+
 *
 *   Queue:
 *    +---------+
 *    | (0,-1)  |
 *    +---------+
 *
 *   Graph State:
 *           (0: start, p=-1)
 *                |
 *         (others unvisited)
 *
 *-----------------------------------------------------------
 * Step 2: Process Vertex 0:
 *   - Dequeue: (0, -1)
 *   - Neighbors of 0: [1]
 *   - For neighbor 1: not visited → mark visited[1] = T, Enqueue (1, 0)
 *
 *   Visited Array:
 *    +-----+-----+-----+-----+-----+
 *    |  0  |  1  |  2  |  3  |  4  |
 *    +-----+-----+-----+-----+-----+
 *    |  T  |  T  |  F  |  F  |  F  |
 *    +-----+-----+-----+-----+-----+
 *
 *   Queue:
 *    +---------+
 *    | (1, 0)  |
 *    +---------+
 *
 *   Graph State:
 *           (0: start, p=-1) --- (1: discovered from 0)
 *
 *-----------------------------------------------------------
 * Step 3: Process Vertex 1:
 *   - Dequeue: (1, 0)
 *   - Neighbors of 1: [0, 2, 4]
 *       • For neighbor 0: already visited and equals parent (0) → skip.
 *       • For neighbor 2: not visited → mark visited[2] = T, Enqueue (2, 1)
 *       • For neighbor 4: not visited → mark visited[4] = T, Enqueue (4, 1)
 *
 *   Visited Array:
 *    +-----+-----+-----+-----+-----+
 *    |  0  |  1  |  2  |  3  |  4  |
 *    +-----+-----+-----+-----+-----+
 *    |  T  |  T  |  T  |  F  |  T  |
 *    +-----+-----+-----+-----+-----+
 *
 *   Queue:
 *    +---------+---------+
 *    | (2,1)   | (4,1)   |
 *    +---------+---------+
 *
 *   Graph State:
 *           (0: start, p=-1) --- (1: discovered from 0)
 *                                  /         \
 *                 (2: discovered from 1)   (4: discovered from 1)
 *
 *-----------------------------------------------------------
 * Step 4: Process Vertex 2:
 *   - Dequeue: (2, 1)
 *   - Neighbors of 2: [1, 3]
 *       • For neighbor 1: already visited and equals parent (1) → skip.
 *       • For neighbor 3: not visited → mark visited[3] = T, Enqueue (3, 2)
 *
 *   Visited Array:
 *    +-----+-----+-----+-----+-----+
 *    |  0  |  1  |  2  |  3  |  4  |
 *    +-----+-----+-----+-----+-----+
 *    |  T  |  T  |  T  |  T  |  T  |
 *    +-----+-----+-----+-----+-----+
 *
 *   Queue:
 *    +---------+---------+
 *    | (4,1)   | (3,2)   |
 *    +---------+---------+
 *
 *   Graph State:
 *           (0: start, p=-1) --- (1: discovered from 0) --- (2: discovered from 1)
 *                                  |                           |
 *                   (4: discovered from 1)         (3: discovered from 2)
 *
 *-----------------------------------------------------------
 * Step 5: Process Vertex 4:
 *   - Dequeue: (4, 1)
 *   - Neighbors of 4: [1, 3]
 *       • For neighbor 1: already visited and equals parent (1) → skip.
 *       • For neighbor 3: already visited but NOT equal to parent (parent=1, 3 ≠ 1) → Cycle Detected!
 *
 *   Queue (at time of detection):
 *    +---------+
 *    | (3,2)   |
 *    +---------+
 *
 *   Final Graph State (Cycle Detected):
 *           (0: start, p=-1) --- (1: discovered from 0) --- (2: discovered from 1)
 *                                  |                           |
 *                   (4: discovered from 1)         (3: discovered from 2)
 *                                    \-----------------------/
 *                       Cycle detected via edge conflict (4 -> 3)
 *
 * Final Outcome: Cycle is detected in the graph.
 *
 */

/************************************************************ JAVA ************************************************/

// Approach 1 (DFS): We use DFS to traverse the graph, marking nodes as visited. When we find an already visited node (not the parent), we have detected a cycle.
// Time Complexity: O(V + E) - Every vertex and edge is processed once during DFS.
// Space Complexity: O(V + E) - Space for the visited array, recursion stack, and the adjacency list.
class Solution {
    // DFS helper to detect a cycle in an undirected graph.
    private boolean isCycleDFS(ArrayList<Integer>[] adj, int u, boolean[] visited, int parent) {
        visited[u] = true; // Mark current node as visited

        // Explore all adjacent nodes of u
        for (int v : adj[u]) {
            if (v == parent) { // Skip the edge to the parent node to avoid false detection
                continue;
            }
            if (visited[v]) { // If v is already visited and not the parent, cycle is detected
                return true;
            }
            if (isCycleDFS(adj, v, visited, u)) { // Recursively check deeper nodes
                return true;
            }
        }
        return false; // No cycle found in the current DFS path
    }
    public boolean isCycle(int V, int[][] edges) {
        boolean[] visited = new boolean[V]; // Array to keep track of visited vertices
        // Adjacency list representation
        ArrayList<Integer>[] adj = new ArrayList[V];
        for (int i = 0; i < V; i++) {
            adj[i] = new ArrayList<>();
        }

        // Build the graph from the edge list
        for (int[] edge : edges) {
            int u = edge[0], v = edge[1];
            adj[u].add(v);
            adj[v].add(u);
        }

        // Check every component of the graph for cycles
        for (int i = 0; i < V; i++) {
            if (!visited[i] && isCycleDFS(adj, i, visited, -1)) {
                return true;
            }
        }
        return false; // No cycle detected in any component
    }
}

/*
 *
 * Dry Run Visual Representation:
 *
 * Graph Structure:
 *
 *           0 --- 1 --- 2
 *                 |     |
 *                 4 --- 3
 *
 * Edges:
 *   0-1, 1-2, 1-4, 2-3, 3-4
 *
 *-----------------------------------------------------------
 * Step 1: Start DFS at Vertex 0 (t = time of visit)
 *
 * Visited Array:
 *  +-----+-----+-----+-----+-----+
 *  |  0  |  1  |  2  |  3  |  4  |
 *  +-----+-----+-----+-----+-----+
 *  |  T  |  F  |  F  |  F  |  F  |
 *  +-----+-----+-----+-----+-----+
 *     ^
 *  (Current: 0, t=1, Parent: -1)
 *
 * Graph State:
 *           (0: t=1, p=-1)
 *                |
 *         (others unvisited)
 *
 *-----------------------------------------------------------
 * Step 2: DFS from Vertex 0 -> Vertex 1
 *
 * Update:
 *  Vertex 1: t=2, Parent = 0
 *
 * Visited Array:
 *  +-----+-----+-----+-----+-----+
 *  |  0  |  1  |  2  |  3  |  4  |
 *  +-----+-----+-----+-----+-----+
 *  |  T  |  T  |  F  |  F  |  F  |
 *  +-----+-----+-----+-----+-----+
 *           ^
 *  (Current: 1, t=2, Parent: 0)
 *
 * Graph State:
 *           (0: t=1, p=-1) --- (1: t=2, p=0)
 *
 *-----------------------------------------------------------
 * Step 3: DFS from Vertex 1 -> Vertex 2
 *
 * Update:
 *  Vertex 2: t=3, Parent = 1
 *
 * Visited Array:
 *  +-----+-----+-----+-----+-----+
 *  |  0  |  1  |  2  |  3  |  4  |
 *  +-----+-----+-----+-----+-----+
 *  |  T  |  T  |  T  |  F  |  F  |
 *  +-----+-----+-----+-----+-----+
 *                 ^
 *  (Current: 2, t=3, Parent: 1)
 *
 * Graph State:
 *           (0: t=1, p=-1) --- (1: t=2, p=0) --- (2: t=3, p=1)
 *
 *-----------------------------------------------------------
 * Step 4: DFS from Vertex 2 -> Vertex 3
 *
 * Update:
 *  Vertex 3: t=4, Parent = 2
 *
 * Visited Array:
 *  +-----+-----+-----+-----+-----+
 *  |  0  |  1  |  2  |  3  |  4  |
 *  +-----+-----+-----+-----+-----+
 *  |  T  |  T  |  T  |  T  |  F  |
 *  +-----+-----+-----+-----+-----+
 *                       ^
 *  (Current: 3, t=4, Parent: 2)
 *
 * Graph State:
 *           (0: t=1, p=-1) --- (1: t=2, p=0) --- (2: t=3, p=1)
 *                                                 |
 *                                                (3: t=4, p=2)
 *
 *-----------------------------------------------------------
 * Step 5: DFS from Vertex 2 -> Vertex 3 -> Vertex 4
 *
 * Update:
 *  Vertex 4: t=5, Parent = 3
 *
 * Visited Array:
 *  +-----+-----+-----+-----+-----+
 *  |  0  |  1  |  2  |  3  |  4  |
 *  +-----+-----+-----+-----+-----+
 *  |  T  |  T  |  T  |  T  |  T  |
 *  +-----+-----+-----+-----+-----+
 *                             ^
 *  (Current: 4, t=5, Parent: 3)
 *
 * Graph State:
 *           (0: t=1, p=-1) -- (1: t=2, p=0) --- (2: t=3, p=1)
 *                              |                 |
 *                            (4: t=5, p=3) --- (3: t=4, p=2)
 *
 *-----------------------------------------------------------
 * Step 6: DFS from Vertex 4 -> Check Neighbors
 *
 * Neighbors of Vertex 4: {1, 3}
 *   - For neighbor 3: It is the parent of 4 → Skip.
 *   - For neighbor 1: Already visited and not the parent → Cycle Detected!
 *
 * Final Corrected Graph Representation (Cycle Detection):
 *
 *           (0: t=1, p=-1) -- (1: t=2, p=0) ---- (2: t=3, p=1)
 *                              |                  |
 *                             (4: t=5, p=3) ---- (3: t=4, p=2)
 *
 * Cycle detected via the edge from 4 to 1.
 *
 *-----------------------------------------------------------
 * Final Outcome: **Cycle is detected in the graph.**
 */

// Approach 2 (BFS): Use BFS to detect a cycle in an undirected graph by checking if a visited neighbor is not the parent.
// Time Complexity: O(V + E) - Every vertex and edge is processed once during BFS.
// Space Complexity: O(V + E) - Space for the visited array, queue, and the adjacency list.
class Solution {
    // Helper class to store a pair of (current vertex, parent vertex)
    private static class Pair {
        int vertex;
        int parent;
        Pair(int vertex, int parent) {
            this.vertex = vertex;
            this.parent = parent;
        }
    }

    // BFS helper to detect a cycle in an undirected graph.
    // Parameters:
    //   adj: Adjacency list representing the graph.
    //   u: The starting vertex for BFS.
    //   visited: Array tracking visited vertices.
    // Returns true if a cycle is detected.
    private boolean isCycleBFS(ArrayList<Integer>[] adj, int u, boolean[] visited) {
        // Queue stores pairs of (current vertex, parent vertex)
        Queue<Pair> queue = new LinkedList<>();

        // Initialize the BFS with the starting vertex u and parent -1 (none)
        queue.offer(new Pair(u, -1));
        visited[u] = true;  // Mark the starting vertex as visited

        // Process until the queue is empty
        while (!queue.isEmpty()) {
            // Get the front element from the queue
            Pair p      = queue.poll();
            int  source = p.vertex;  // Current vertex being processed
            int  parent = p.parent;  // Parent of the current vertex

            // Traverse all adjacent vertices of the current vertex
            for (int v : adj[source]) {
                // If the neighbor hasn't been visited, mark it and add to the queue
                if (!visited[v]) {
                    visited[v] = true;
                    queue.offer(new Pair(v, source));
                }
                // If the neighbor is visited and it's not the parent, a cycle is detected
                else if (v != parent) {
                    return true;
                }
            }
        }
        return false;  // Return false if no cycle is detected after processing all vertices in this component
    }
    // Main function to detect a cycle in the graph using BFS.
    // Parameters:
    //   V: Number of vertices.
    //   edges: List of edges where each edge is represented as a 2D array.
    // Returns true if the graph contains a cycle.
    public boolean isCycle(int V, int[][] edges) {
        boolean[] visited = new boolean[V];       // Array to keep track of visited vertices
        // Adjacency list representation of the graph
        ArrayList<Integer>[] adj = new ArrayList[V];
        for (int i = 0; i < V; i++) {
            adj[i] = new ArrayList<>();
        }

        // Build the graph from the edge list
        for (int[] edge : edges) {
            int u = edge[0], v = edge[1];
            adj[u].add(v);
            adj[v].add(u);
        }

        // Check every connected component of the graph for cycles using BFS
        for (int i = 0; i < V; i++) {
            if (!visited[i] && isCycleBFS(adj, i, visited)) {
                return true;
            }
        }
        return false;  // No cycle detected in any component
    }
}

/*
 *
 * Dry Run Visual Representation for BFS Cycle Detection:
 *
 * Graph Structure (Before BFS starts):
 *
 *           0 --- 1 --- 2
 *                 |     |
 *                 4 --- 3
 *
 * Edges:
 *   0-1, 1-2, 1-4, 2-3, 3-4
 *
 * Initial State:
 *   Visited Array:
 *    +-----+-----+-----+-----+-----+
 *    |  0  |  1  |  2  |  3  |  4  |
 *    +-----+-----+-----+-----+-----+
 *    |  F  |  F  |  F  |  F  |  F  |
 *    +-----+-----+-----+-----+-----+
 *
 *   Queue: empty
 *
 *-----------------------------------------------------------
 * Step 1: Start BFS at Vertex 0:
 *   - Enqueue: (0, -1)
 *   - Mark visited[0] = T
 *
 *   Visited Array:
 *    +-----+-----+-----+-----+-----+
 *    |  0  |  1  |  2  |  3  |  4  |
 *    +-----+-----+-----+-----+-----+
 *    |  T  |  F  |  F  |  F  |  F  |
 *    +-----+-----+-----+-----+-----+
 *
 *   Queue:
 *    +---------+
 *    | (0,-1)  |
 *    +---------+
 *
 *   Graph State:
 *           (0: start, p=-1)
 *                |
 *         (others unvisited)
 *
 *-----------------------------------------------------------
 * Step 2: Process Vertex 0:
 *   - Dequeue: (0, -1)
 *   - Neighbors of 0: [1]
 *   - For neighbor 1: not visited → mark visited[1] = T, Enqueue (1, 0)
 *
 *   Visited Array:
 *    +-----+-----+-----+-----+-----+
 *    |  0  |  1  |  2  |  3  |  4  |
 *    +-----+-----+-----+-----+-----+
 *    |  T  |  T  |  F  |  F  |  F  |
 *    +-----+-----+-----+-----+-----+
 *
 *   Queue:
 *    +---------+
 *    | (1, 0)  |
 *    +---------+
 *
 *   Graph State:
 *           (0: start, p=-1) --- (1: discovered from 0)
 *
 *-----------------------------------------------------------
 * Step 3: Process Vertex 1:
 *   - Dequeue: (1, 0)
 *   - Neighbors of 1: [0, 2, 4]
 *       • For neighbor 0: already visited and equals parent (0) → skip.
 *       • For neighbor 2: not visited → mark visited[2] = T, Enqueue (2, 1)
 *       • For neighbor 4: not visited → mark visited[4] = T, Enqueue (4, 1)
 *
 *   Visited Array:
 *    +-----+-----+-----+-----+-----+
 *    |  0  |  1  |  2  |  3  |  4  |
 *    +-----+-----+-----+-----+-----+
 *    |  T  |  T  |  T  |  F  |  T  |
 *    +-----+-----+-----+-----+-----+
 *
 *   Queue:
 *    +---------+---------+
 *    | (2,1)   | (4,1)   |
 *    +---------+---------+
 *
 *   Graph State:
 *           (0: start, p=-1) --- (1: discovered from 0)
 *                                  /         \
 *                 (2: discovered from 1)   (4: discovered from 1)
 *
 *-----------------------------------------------------------
 * Step 4: Process Vertex 2:
 *   - Dequeue: (2, 1)
 *   - Neighbors of 2: [1, 3]
 *       • For neighbor 1: already visited and equals parent (1) → skip.
 *       • For neighbor 3: not visited → mark visited[3] = T, Enqueue (3, 2)
 *
 *   Visited Array:
 *    +-----+-----+-----+-----+-----+
 *    |  0  |  1  |  2  |  3  |  4  |
 *    +-----+-----+-----+-----+-----+
 *    |  T  |  T  |  T  |  T  |  T  |
 *    +-----+-----+-----+-----+-----+
 *
 *   Queue:
 *    +---------+---------+
 *    | (4,1)   | (3,2)   |
 *    +---------+---------+
 *
 *   Graph State:
 *           (0: start, p=-1) --- (1: discovered from 0) --- (2: discovered from 1)
 *                                  |                           |
 *                   (4: discovered from 1)         (3: discovered from 2)
 *
 *-----------------------------------------------------------
 * Step 5: Process Vertex 4:
 *   - Dequeue: (4, 1)
 *   - Neighbors of 4: [1, 3]
 *       • For neighbor 1: already visited and equals parent (1) → skip.
 *       • For neighbor 3: already visited but NOT equal to parent (parent=1, 3 ≠ 1) → Cycle Detected!
 *
 *   Queue (at time of detection):
 *    +---------+
 *    | (3,2)   |
 *    +---------+
 *
 *   Final Graph State (Cycle Detected):
 *           (0: start, p=-1) --- (1: discovered from 0) --- (2: discovered from 1)
 *                                  |                           |
 *                   (4: discovered from 1)         (3: discovered from 2)
 *                                    \-----------------------/
 *                       Cycle detected via edge conflict (4 -> 3)
 *
 * Final Outcome: Cycle is detected in the graph.
 *
 */
