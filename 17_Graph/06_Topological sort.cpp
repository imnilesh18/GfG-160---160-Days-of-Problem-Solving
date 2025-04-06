/*
 * Topological sort
 *
 * Difficulty: Medium Accuracy: 56.52% Submissions: 279K+ Points: 4 Average Time: 15m
 *
 * Given a Directed Acyclic Graph (DAG) of V (0 to V-1) vertices and E edges represented as a 2D list of edges[][], where each entry edges[i] = [u, v] denotes an directed edge u -> v. Return topological sort for the given graph.
 *
 * Topological sorting for Directed Acyclic Graph (DAG) is a linear ordering of vertices such that for every directed edge u -> v, vertex u comes before v in the ordering.
 * Note: As there are multiple Topological orders possible, you may return any of them. If your returned Topological sort is correct then the output will be true else false.
 *
 * Examples:
 *
 * Input: V = 4, E = 3, edges[][] = [[3, 0], [1, 0], [2, 0]]
 * Output: true
 * Explanation: The output true denotes that the order is valid. Few valid Topological orders for the given graph are:
 * [3, 2, 1, 0]
 * [1, 2, 3, 0]
 * [2, 3, 1, 0]
 *
 * Input: V = 6, E = 6, edges[][] = [[1, 3], [2, 3], [4, 1], [4, 0], [5, 0], [5,2]]
 * Output: true
 * Explanation: The output true denotes that the order is valid. Few valid Topological orders for the graph are:
 * [4, 5, 0, 1, 2, 3]
 * [5, 2, 4, 0, 1, 3]
 *
 * Constraints:
 * 2  ≤  V  ≤  10^3
 * 1  ≤  E = edges.size()  ≤  (V * (V - 1)) / 2
 */

/************************************************************ C++ ************************************************/

// Approach 1 (DFS): Use DFS to explore the graph and push each vertex onto a stack after visiting all its descendants; then, pop from the stack to get the topological order.
// Time Complexity: O(V + E) as every vertex and edge is visited once.
// Space Complexity: O(V) due to the recursion stack, visited array, and the stack used for ordering.
class Solution {
public:
    // DFS helper function to recursively traverse the graph.
    void DFS(unordered_map<int, vector<int>>& adj, int u, vector<bool>& visited, stack<int>& st) {
        // Mark the current node as visited.
        visited[u] = true;

        // Recursively visit all unvisited neighbors.
        for (int& v : adj[u]) {
            if (!visited[v]) {
                DFS(adj, v, visited, st);
            }
        }

        // After visiting all neighbors, push the current node to the stack.
        st.push(u);
    }

    // Function to return the topological order of the graph.
    vector<int> topoSort(int V, vector<vector<int>>& edges) {
        unordered_map<int, vector<int>> adj;

        // Build the adjacency list from the list of edges.
        for (auto& edge : edges) {
            int u = edge[0];
            int v = edge[1];
            // For a directed edge u -> v, add v to u's list.
            adj[u].push_back(v);
        }

        // Initialize the visited array for all vertices as false.
        vector<bool> visited(V, false);
        // Stack to store the vertices in topologically sorted order.
        stack<int> st;

        // Perform DFS for each vertex that hasn't been visited.
        for (int i = 0; i < V; i++) {
            if (!visited[i]) {
                DFS(adj, i, visited, st);
            }
        }

        // Extract the topological order by popping all vertices from the stack.
        vector<int> result;
        while (!st.empty()) {
            result.push_back(st.top());
            st.pop();
        }

        return result;
    }
};

/*
 *
 * Dry Run for the following graph with V = 6 and the adjacency list:
 *   0 -> 2, 3
 *   1 -> 4
 *   2 -> 3, 1
 *   3 -> 1
 *   4 -> (deadend)
 *   5 -> 1, 4
 *
 * Graph Visualization:
 *        ^ 3 -----> 1
 *       / ^       ^ |  \
 *     /   |     /   |    V
 *     0   |    /    |   > 4
 *      \  |   /     |/
 *       > 2         5
 *
 * Adjacency List Representation:
 *   0: [2, 3]
 *   1: [4]
 *   2: [3, 1]
 *   3: [1]
 *   4: []  (deadend)
 *   5: [1, 4]
 *
 * ------------------------------------------------------------
 * Step 0: Initial Visited Array:
 *   +-----+-----+-----+-----+-----+-----+
 *   |  0  |  1  |  2  |  3  |  4  |  5  |
 *   +-----+-----+-----+-----+-----+-----+
 *   |  F  |  F  |  F  |  F  |  F  |  F  |
 *   +-----+-----+-----+-----+-----+-----+
 *
 * ------------------------------------------------------------
 * Step 1: DFS from vertex 0 (i = 0)
 *   - Call DFS(0):
 *     -> Mark vertex 0 as visited.
 *
 *   Visited Array after DFS(0) is initiated:
 *   +-----+-----+-----+-----+-----+-----+
 *   |  0  |  1  |  2  |  3  |  4  |  5  |
 *   +-----+-----+-----+-----+-----+-----+
 *   |  T  |  F  |  F  |  F  |  F  |  F  |
 *   +-----+-----+-----+-----+-----+-----+
 *
 *   - Neighbors of 0: [2, 3]
 *
 * ------------------------------------------------------------
 * Step 2: DFS on neighbor 2 of vertex 0
 *   - Call DFS(2):
 *     -> Mark vertex 2 as visited.
 *
 *   Visited Array after marking vertex 2:
 *   +-----+-----+-----+-----+-----+-----+
 *   |  0  |  1  |  2  |  3  |  4  |  5  |
 *   +-----+-----+-----+-----+-----+-----+
 *   |  T  |  F  |  T  |  F  |  F  |  F  |
 *   +-----+-----+-----+-----+-----+-----+
 *
 *   - Neighbors of 2: [3, 1]
 *
 * ------------------------------------------------------------
 * Step 3: DFS on neighbor 3 of vertex 2
 *   - Call DFS(3):
 *     -> Mark vertex 3 as visited.
 *
 *   Visited Array after marking vertex 3:
 *   +-----+-----+-----+-----+-----+-----+
 *   |  0  |  1  |  2  |  3  |  4  |  5  |
 *   +-----+-----+-----+-----+-----+-----+
 *   |  T  |  F  |  T  |  T  |  F  |  F  |
 *   +-----+-----+-----+-----+-----+-----+
 *
 *   - Neighbors of 3: [1]
 *
 * ------------------------------------------------------------
 * Step 4: DFS on neighbor 1 of vertex 3
 *   - Call DFS(1):
 *     -> Mark vertex 1 as visited.
 *
 *   Visited Array after marking vertex 1:
 *   +-----+-----+-----+-----+-----+-----+
 *   |  0  |  1  |  2  |  3  |  4  |  5  |
 *   +-----+-----+-----+-----+-----+-----+
 *   |  T  |  T  |  T  |  T  |  F  |  F  |
 *   +-----+-----+-----+-----+-----+-----+
 *
 *   - Neighbors of 1: [4]
 *
 * ------------------------------------------------------------
 * Step 5: DFS on neighbor 4 of vertex 1
 *   - Call DFS(4):
 *     -> Mark vertex 4 as visited.
 *
 *   Visited Array after marking vertex 4:
 *   +-----+-----+-----+-----+-----+-----+
 *   |  0  |  1  |  2  |  3  |  4  |  5  |
 *   +-----+-----+-----+-----+-----+-----+
 *   |  T  |  T  |  T  |  T  |  T  |  F  |
 *   +-----+-----+-----+-----+-----+-----+
 *
 *   - Vertex 4 has no neighbors.
 *   - Push vertex 4 onto the stack.
 *
 *   Stack after DFS(4):
 *       +-----+
 *       |  4  |   <-- top
 *       +-----+
 *
 *   - Return from DFS(4) to DFS(1)
 *
 * ------------------------------------------------------------
 * Step 6: Back in DFS(1) (after DFS(4))
 *   - All neighbors of vertex 1 processed.
 *   - Push vertex 1 onto the stack.
 *
 *   Stack after DFS(1):
 *       +-----+
 *       |  1  |   <-- top
 *       +-----+
 *       |  4  |
 *       +-----+
 *
 *   - Return from DFS(1) to DFS(3)
 *
 * ------------------------------------------------------------
 * Step 7: Back in DFS(3) (after DFS(1))
 *   - All neighbors of vertex 3 processed.
 *   - Push vertex 3 onto the stack.
 *
 *   Stack after DFS(3):
 *       +-----+
 *       |  3  |   <-- top
 *       +-----+
 *       |  1  |
 *       +-----+
 *       |  4  |
 *       +-----+
 *
 *   - Return from DFS(3) to DFS(2)
 *
 * ------------------------------------------------------------
 * Step 8: Back in DFS(2) (after DFS(3))
 *   - Next neighbor of vertex 2 is 1, but vertex 1 is already visited.
 *   - All neighbors of vertex 2 processed.
 *   - Push vertex 2 onto the stack.
 *
 *   Stack after DFS(2):
 *       +-----+
 *       |  2  |   <-- top
 *       +-----+
 *       |  3  |
 *       +-----+
 *       |  1  |
 *       +-----+
 *       |  4  |
 *       +-----+
 *
 *   - Return from DFS(2) to DFS(0)
 *
 * ------------------------------------------------------------
 * Step 9: Back in DFS(0) (after DFS(2))
 *   - Next neighbor of vertex 0 is 3, but vertex 3 is already visited.
 *   - All neighbors of vertex 0 processed.
 *   - Push vertex 0 onto the stack.
 *
 *   Stack after DFS(0):
 *       +-----+
 *       |  0  |   <-- top
 *       +-----+
 *       |  2  |
 *       +-----+
 *       |  3  |
 *       +-----+
 *       |  1  |
 *       +-----+
 *       |  4  |
 *       +-----+
 *
 *   - Return from DFS(0)
 *
 * ------------------------------------------------------------
 * Step 10: Continue the DFS loop in topoSort:
 *   - i = 1: Vertex 1 is already visited; skip.
 *   - i = 2: Vertex 2 is already visited; skip.
 *   - i = 3: Vertex 3 is already visited; skip.
 *   - i = 4: Vertex 4 is already visited; skip.
 *   - i = 5: Vertex 5 is not visited.
 *
 * Step 11: DFS from vertex 5 (i = 5)
 *   - Call DFS(5):
 *     -> Mark vertex 5 as visited.
 *
 *   Visited Array after marking vertex 5:
 *   +-----+-----+-----+-----+-----+-----+
 *   |  0  |  1  |  2  |  3  |  4  |  5  |
 *   +-----+-----+-----+-----+-----+-----+
 *   |  T  |  T  |  T  |  T  |  T  |  T  |
 *   +-----+-----+-----+-----+-----+-----+
 *
 *   - Neighbors of 5: [1, 4]
 *       -> Both vertices 1 and 4 are already visited.
 *   - All neighbors processed.
 *   - Push vertex 5 onto the stack.
 *
 *   Stack after DFS(5):
 *       +-----+
 *       |  5  |   <-- top
 *       +-----+
 *       |  0  |
 *       +-----+
 *       |  2  |
 *       +-----+
 *       |  3  |
 *       +-----+
 *       |  1  |
 *       +-----+
 *       |  4  |
 *       +-----+
 *
 * ------------------------------------------------------------
 * Step 12: Final Step - Build Result from Stack
 *   - Pop elements from the stack to form the topological order:
 *       Pop 5 -> result becomes [5]
 *       Pop 0 -> result becomes [5, 0]
 *       Pop 2 -> result becomes [5, 0, 2]
 *       Pop 3 -> result becomes [5, 0, 2, 3]
 *       Pop 1 -> result becomes [5, 0, 2, 3, 1]
 *       Pop 4 -> result becomes [5, 0, 2, 3, 1, 4]
 *
 *   Final Result Array:
 *   +-----+-----+-----+-----+-----+-----+
 *   |  5  |  0  |  2  |  3  |  1  |  4  |
 *   +-----+-----+-----+-----+-----+-----+
 *
 * The resulting topological order is: [5, 0, 2, 3, 1, 4]
 *
 */

// Approach 2 (BFS): Use Kahn's algorithm (BFS) to process vertices with zero indegree and reduce the indegree of their neighbors, collecting a valid topological order.
// Time Complexity: O(V + E) since each vertex and edge is processed once.
// Space Complexity: O(V) due to the indegree array, queue, and result vector.
class Solution {
public:
    vector<int> topoSort(int V, vector<vector<int>>& edges) {
        // Build the adjacency list for the graph.
        unordered_map<int, vector<int>> adj;

        for (auto& edge : edges) {
            int u = edge[0];
            int v = edge[1];
            // For a directed edge u -> v, add v to u's list.
            adj[u].push_back(v);
        }

        // Step 1: Initialize the indegree array for each vertex.
        vector<int> indegree(V, 0);
        for (int u = 0; u < V; u++) {
            for (int& v : adj[u]) {
                indegree[v]++;
            }
        }

        // Step 2: Enqueue all vertices with indegree 0.
        queue<int> que;
        for (int i = 0; i < V; i++) {
            if (indegree[i] == 0) {
                que.push(i);
            }
        }

        // Step 3: Process vertices in BFS manner.
        vector<int> result;
        while (!que.empty()) {
            int u = que.front();
            que.pop();
            result.push_back(u);

            // For each neighbor v, decrement its indegree.
            for (int& v : adj[u]) {
                indegree[v]--;
                // If indegree of v becomes 0, enqueue it.
                if (indegree[v] == 0) {
                    que.push(v);
                }
            }
        }
        return result;
    }
};

/*
 *
 * Dry Run for the following graph with V = 6 and the adjacency list:
 *  0 -> 2, 3
 *  1 -> 4
 *  2 -> 3, 1
 *  3 -> 1
 *  4 -> (deadend)
 *  5 -> 1, 4
 *
 *
 * Graph Visualization:
 *        ^ 3 -----> 1
 *       / ^       ^ |  \
 *     /   |     /   |    V
 *     0   |    /    |   > 4
 *      \  |   /     |/
 *       > 2         5
 *
 * Adjacency List Representation:
 *  0: [2, 3]
 *  1: [4]
 *  2: [3, 1]
 *  3: [1]
 *  4: []  (deadend)
 *  5: [1, 4]
 *
 * Step 1: Build the indegree array:
 *   Process each edge:
 *     - For 0 -> 2: indegree[2] becomes 1.
 *     - For 0 -> 3: indegree[3] becomes 1.
 *     - For 1 -> 4: indegree[4] becomes 1.
 *     - For 2 -> 3: indegree[3] becomes 2.
 *     - For 2 -> 1: indegree[1] becomes 1.
 *     - For 3 -> 1: indegree[1] becomes 2.
 *     - For 5 -> 1: indegree[1] becomes 3.
 *     - For 5 -> 4: indegree[4] becomes 2.
 *
 * Final Indegree Array:
 *  +-----+-----+-----+-----+-----+-----+
 *  |  0  |  1  |  2  |  3  |  4  |  5  |
 *  +-----+-----+-----+-----+-----+-----+
 *  |  0  |  3  |  1  |  2  |  2  |  0  |
 *  +-----+-----+-----+-----+-----+-----+
 *
 * Step 2: Initialize the queue with vertices having indegree 0.
 *   Vertices with indegree 0: 0 and 5.
 *
 * Queue at initialization:
 *     +-----+
 *     |  0  |   <-- Front
 *     +-----+
 *     |  5  |   <-- Rear
 *     +-----+
 *
 * Result Array: (initially empty)
 *     []
 *
 * Step 3: Process vertices using BFS.
 *
 * Iteration 1:
 *   - Dequeue vertex 0.
 *   - Append 0 to result: Result becomes [0].
 *   - Process neighbors of 0: [2, 3].
 *       For vertex 2: decrement indegree from 1 to 0; enqueue vertex 2.
 *       For vertex 3: decrement indegree from 2 to 1.
 *
 * Updated Indegree Array:
 *  +-----+-----+-----+-----+-----+-----+
 *  |  0  |  1  |  2  |  3  |  4  |  5  |
 *  +-----+-----+-----+-----+-----+-----+
 *  |  0  |  3  |  0  |  1  |  2  |  0  |
 *  +-----+-----+-----+-----+-----+-----+
 *
 * Queue after Iteration 1:
 *     +-----+
 *     |  5  |   <-- Front
 *     +-----+
 *     |  2  |   <-- Rear
 *     +-----+
 *
 * Result Array:
 *     +-----+
 *     |  0  |
 *     +-----+
 *
 * Iteration 2:
 *   - Dequeue vertex 5.
 *   - Append 5 to result: Result becomes [0, 5].
 *   - Process neighbors of 5: [1, 4].
 *       For vertex 1: decrement indegree from 3 to 2.
 *       For vertex 4: decrement indegree from 2 to 1.
 *
 * Updated Indegree Array:
 *  +-----+-----+-----+-----+-----+-----+
 *  |  0  |  1  |  2  |  3  |  4  |  5  |
 *  +-----+-----+-----+-----+-----+-----+
 *  |  0  |  2  |  0  |  1  |  1  |  0  |
 *  +-----+-----+-----+-----+-----+-----+
 *
 * Queue after Iteration 2:
 *     +-----+
 *     |  2  |   <-- Front/Rear
 *     +-----+
 *
 * Result Array:
 *     +-----+-----+
 *     |  0  |  5  |
 *     +-----+-----+
 *
 * Iteration 3:
 *   - Dequeue vertex 2.
 *   - Append 2 to result: Result becomes [0, 5, 2].
 *   - Process neighbors of 2: [3, 1].
 *       For vertex 3: decrement indegree from 1 to 0; enqueue vertex 3.
 *       For vertex 1: decrement indegree from 2 to 1.
 *
 * Updated Indegree Array:
 *  +-----+-----+-----+-----+-----+-----+
 *  |  0  |  1  |  2  |  3  |  4  |  5  |
 *  +-----+-----+-----+-----+-----+-----+
 *  |  0  |  1  |  0  |  0  |  1  |  0  |
 *  +-----+-----+-----+-----+-----+-----+
 *
 * Queue after Iteration 3:
 *     +-----+
 *     |  3  |   <-- Front/Rear
 *     +-----+
 *
 * Result Array:
 *     +-----+-----+-----+
 *     |  0  |  5  |  2  |
 *     +-----+-----+-----+
 *
 * Iteration 4:
 *   - Dequeue vertex 3.
 *   - Append 3 to result: Result becomes [0, 5, 2, 3].
 *   - Process neighbor of 3: [1].
 *       For vertex 1: decrement indegree from 1 to 0; enqueue vertex 1.
 *
 * Updated Indegree Array:
 *  +-----+-----+-----+-----+-----+-----+
 *  |  0  |  1  |  2  |  3  |  4  |  5  |
 *  +-----+-----+-----+-----+-----+-----+
 *  |  0  |  0  |  0  |  0  |  1  |  0  |
 *  +-----+-----+-----+-----+-----+-----+
 *
 * Queue after Iteration 4:
 *     +-----+
 *     |  1  |   <-- Front/Rear
 *     +-----+
 *
 * Result Array:
 *     +-----+-----+-----+-----+
 *     |  0  |  5  |  2  |  3  |
 *     +-----+-----+-----+-----+
 *
 * Iteration 5:
 *   - Dequeue vertex 1.
 *   - Append 1 to result: Result becomes [0, 5, 2, 3, 1].
 *   - Process neighbor of 1: [4].
 *       For vertex 4: decrement indegree from 1 to 0; enqueue vertex 4.
 *
 * Updated Indegree Array:
 *  +-----+-----+-----+-----+-----+-----+
 *  |  0  |  1  |  2  |  3  |  4  |  5  |
 *  +-----+-----+-----+-----+-----+-----+
 *  |  0  |  0  |  0  |  0  |  0  |  0  |
 *  +-----+-----+-----+-----+-----+-----+
 *
 * Queue after Iteration 5:
 *     +-----+
 *     |  4  |   <-- Front/Rear
 *     +-----+
 *
 * Result Array:
 *     +-----+-----+-----+-----+-----+
 *     |  0  |  5  |  2  |  3  |  1  |
 *     +-----+-----+-----+-----+-----+
 *
 * Iteration 6:
 *   - Dequeue vertex 4.
 *   - Append 4 to result: Result becomes [0, 5, 2, 3, 1, 4].
 *   - Vertex 4 has no neighbors.
 *
 * Final Queue: (empty)
 *
 * Final Topological Order (Result Array):
 *     +-----+-----+-----+-----+-----+-----+
 *     |  0  |  5  |  2  |  3  |  1  |  4  |
 *     +-----+-----+-----+-----+-----+-----+
 *
 * The output [0, 5, 2, 3, 1, 4] is a valid topological order for the given graph.
 *
 */

/************************************************************ JAVA ************************************************/

// Approach 1 (DFS): Use DFS to explore the graph and push each vertex onto a stack after visiting all its descendants; then, pop from the stack to get the topological order.
// Time Complexity: O(V + E) as every vertex and edge is visited once.
// Space Complexity: O(V) due to the recursion stack, visited array, and the stack used for ordering.
class Solution {
    // DFS helper method to recursively traverse the graph.
    private static void DFS(int u, ArrayList<ArrayList<Integer>> adj, boolean[] visited, Stack<Integer> stack) {
        // Mark the current vertex as visited.
        visited[u] = true;

        // Visit all the neighbors of the current vertex.
        for (int v : adj.get(u)) {
            if (!visited[v]) {
                DFS(v, adj, visited, stack);
            }
        }

        // After visiting all neighbors, push the current vertex onto the stack.
        stack.push(u);
    }
    
    public static ArrayList<Integer> topoSort(int V, int[][] edges) {
        // Create an adjacency list for the graph.
        ArrayList<ArrayList<Integer>> adj = new ArrayList<>();

        for (int i = 0; i < V; i++) {
            adj.add(new ArrayList<Integer>());
        }

        // Build the graph: for each edge u -> v, add v to the adjacency list of u.
        for (int[] edge : edges) {
            int u = edge[0];
            int v = edge[1];
            adj.get(u).add(v);
        }

        // Initialize the visited array to keep track of visited vertices.
        boolean[] visited = new boolean[V];
        // Stack to store the vertices in topologically sorted order.
        Stack<Integer> stack = new Stack<>();

        // Perform DFS for every vertex that has not been visited.
        for (int i = 0; i < V; i++) {
            if (!visited[i]) {
                DFS(i, adj, visited, stack);
            }
        }

        // Extract the topological order by popping vertices from the stack.
        ArrayList<Integer> result = new ArrayList<>();
        while (!stack.isEmpty()) {
            result.add(stack.pop());
        }

        return result;
    }
}

/*
 *
 * Dry Run for Input: V = 4, edges = [[3, 0], [1, 0], [2, 0]]
 *
 * Graph Representation:
 *         3      1      2
 *          \     |     /
 *           \    |    /
 *             -> 0 <-
 *
 * Adjacency List:
 *  3: [0]
 *  1: [0]
 *  2: [0]
 *  0: []  (no outgoing edges)
 *
 * Visited Array Evolution:
 * Initially:
 *  +-----+-----+-----+-----+
 *  |  0  |  1  |  2  |  3  |
 *  +-----+-----+-----+-----+
 *  |  F  |  F  |  F  |  F  |
 *  +-----+-----+-----+-----+
 *
 * After processing vertex 0 (i = 0):
 *  - Call DFS(0):
 *      Mark visited[0] = T.
 *      Since adj.get(0) is empty, push 0 into the stack.
 *
 *  Visited Array:
 *  +-----+-----+-----+-----+
 *  |  0  |  1  |  2  |  3  |
 *  +-----+-----+-----+-----+
 *  |  T  |  F  |  F  |  F  |
 *  +-----+-----+-----+-----+
 *
 *  Stack after DFS(0):
 *     +-----+
 *     |  0  |   <-- top
 *     +-----+
 *
 * After processing vertex 1 (i = 1):
 *  - Call DFS(1):
 *      Mark visited[1] = T.
 *      Traverse adj.get(1): contains [0]. Since visited[0] is T, skip DFS for 0.
 *      Push 1 into the stack.
 *
 *  Visited Array:
 *  +-----+-----+-----+-----+
 *  |  0  |  1  |  2  |  3  |
 *  +-----+-----+-----+-----+
 *  |  T  |  T  |  F  |  F  |
 *  +-----+-----+-----+-----+
 *
 *  Stack after DFS(1):
 *     +-----+
 *     |  1  |   <-- top
 *     +-----+
 *     |  0  |
 *     +-----+
 *
 * After processing vertex 2 (i = 2):
 *  - Call DFS(2):
 *      Mark visited[2] = T.
 *      Traverse adj.get(2): contains [0]. Since visited[0] is T, skip DFS for 0.
 *      Push 2 into the stack.
 *
 *  Visited Array:
 *  +-----+-----+-----+-----+
 *  |  0  |  1  |  2  |  3  |
 *  +-----+-----+-----+-----+
 *  |  T  |  T  |  T  |  F  |
 *  +-----+-----+-----+-----+
 *
 *  Stack after DFS(2):
 *     +-----+
 *     |  2  |   <-- top
 *     +-----+
 *     |  1  |
 *     +-----+
 *     |  0  |
 *     +-----+
 *
 * After processing vertex 3 (i = 3):
 *  - Call DFS(3):
 *      Mark visited[3] = T.
 *      Traverse adj.get(3): contains [0]. Since visited[0] is T, skip DFS for 0.
 *      Push 3 into the stack.
 *
 *  Visited Array:
 *  +-----+-----+-----+-----+
 *  |  0  |  1  |  2  |  3  |
 *  +-----+-----+-----+-----+
 *  |  T  |  T  |  T  |  T  |
 *  +-----+-----+-----+-----+
 *
 *  Stack after DFS(3):
 *     +-----+
 *     |  3  |   <-- top
 *     +-----+
 *     |  2  |
 *     +-----+
 *     |  1  |
 *     +-----+
 *     |  0  |
 *     +-----+
 *
 * Final Topological Order (obtained by popping the stack):
 *  - Pop 3 -> result: [3]
 *  - Pop 2 -> result: [3, 2]
 *  - Pop 1 -> result: [3, 2, 1]
 *  - Pop 0 -> result: [3, 2, 1, 0]
 *
 * Final Output: [3, 2, 1, 0] which is a valid topological sort.
 *
 */

// Approach 2 (BFS): Use Kahn's algorithm (BFS) to process vertices with zero indegree, update neighbors and form a valid topological order.
// Time Complexity: O(V + E) since each vertex and edge is processed once.
// Space Complexity: O(V) due to the indegree array, queue, and result list.
class Solution {
    public static ArrayList<Integer> topoSort(int V, int[][] edges) {
        // Create an adjacency list for V vertices.
        ArrayList<ArrayList<Integer>> adj = new ArrayList<>();

        for (int i = 0; i < V; i++) {
            adj.add(new ArrayList<Integer>());
        }

        // Build the graph: For each edge u -> v, add v to u's list.
        for (int[] edge : edges) {
            int u = edge[0], v = edge[1];
            adj.get(u).add(v);
        }

        // Initialize the indegree array for each vertex.
        int[] indegree = new int[V];
        for (int u = 0; u < V; u++) {
            for (int v : adj.get(u)) {
                indegree[v]++;
            }
        }

        // Initialize the queue with all vertices having indegree 0.
        Queue<Integer> queue = new LinkedList<>();
        for (int i = 0; i < V; i++) {
            if (indegree[i] == 0) {
                queue.offer(i);
            }
        }

        // Process vertices using BFS.
        ArrayList<Integer> result = new ArrayList<>();
        while (!queue.isEmpty()) {
            int u = queue.poll();
            result.add(u);

            // For each neighbor of u, decrement its indegree.
            for (int v : adj.get(u)) {
                indegree[v]--;
                // If indegree becomes 0, add it to the queue.
                if (indegree[v] == 0) {
                    queue.offer(v);
                }
            }
        }
        return result;
    }
}

/*
 *
 * Dry Run for the following graph with V = 6 and the adjacency list:
 *  0 -> 2, 3
 *  1 -> 4
 *  2 -> 3, 1
 *  3 -> 1
 *  4 -> (deadend)
 *  5 -> 1, 4
 *
 * Graph Visualization:
 *        ^ 3 -----> 1
 *       / ^       ^ \
 *     /   |     /   |  V
 *     0   |    /    | > 4
 *      \  |   /     |/
 *       > 2         5
 *
 * Step 1: Build the indegree array:
 *   Process each edge:
 *     - For 0 -> 2: indegree[2] becomes 1.
 *     - For 0 -> 3: indegree[3] becomes 1.
 *     - For 1 -> 4: indegree[4] becomes 1.
 *     - For 2 -> 3: indegree[3] becomes 2.
 *     - For 2 -> 1: indegree[1] becomes 1.
 *     - For 3 -> 1: indegree[1] becomes 2.
 *     - For 5 -> 1: indegree[1] becomes 3.
 *     - For 5 -> 4: indegree[4] becomes 2.
 *
 * Final Indegree Array:
 *  +-----+-----+-----+-----+-----+-----+
 *  |  0  |  1  |  2  |  3  |  4  |  5  |
 *  +-----+-----+-----+-----+-----+-----+
 *  |  0  |  3  |  1  |  2  |  2  |  0  |
 *  +-----+-----+-----+-----+-----+-----+
 *
 * Step 2: Initialize the queue with vertices having indegree 0.
 *   Vertices with indegree 0: 0 and 5.
 *
 * Queue at initialization:
 *     +-----+
 *     |  0  |   <-- Front
 *     +-----+
 *     |  5  |   <-- Rear
 *     +-----+
 *
 * Result Array: (initially empty)
 *     []
 *
 * Step 3: Process vertices using BFS.
 *
 * Iteration 1:
 *   - Dequeue vertex 0.
 *   - Append 0 to result: Result becomes [0].
 *   - Process neighbors of 0: [2, 3].
 *       For vertex 2: decrement indegree from 1 to 0; enqueue vertex 2.
 *       For vertex 3: decrement indegree from 2 to 1.
 *
 * Updated Indegree Array:
 *  +-----+-----+-----+-----+-----+-----+
 *  |  0  |  1  |  2  |  3  |  4  |  5  |
 *  +-----+-----+-----+-----+-----+-----+
 *  |  0  |  3  |  0  |  1  |  2  |  0  |
 *  +-----+-----+-----+-----+-----+-----+
 *
 * Queue after Iteration 1:
 *     +-----+
 *     |  5  |   <-- Front
 *     +-----+
 *     |  2  |   <-- Rear
 *     +-----+
 *
 * Iteration 2:
 *   - Dequeue vertex 5.
 *   - Append 5 to result: Result becomes [0, 5].
 *   - Process neighbors of 5: [1, 4].
 *       For vertex 1: decrement indegree from 3 to 2.
 *       For vertex 4: decrement indegree from 2 to 1.
 *
 * Updated Indegree Array:
 *  +-----+-----+-----+-----+-----+-----+
 *  |  0  |  1  |  2  |  3  |  4  |  5  |
 *  +-----+-----+-----+-----+-----+-----+
 *  |  0  |  2  |  0  |  1  |  1  |  0  |
 *  +-----+-----+-----+-----+-----+-----+
 *
 * Queue after Iteration 2:
 *     +-----+
 *     |  2  |   <-- Front/Rear
 *     +-----+
 *
 * Iteration 3:
 *   - Dequeue vertex 2.
 *   - Append 2 to result: Result becomes [0, 5, 2].
 *   - Process neighbors of 2: [3, 1].
 *       For vertex 3: decrement indegree from 1 to 0; enqueue vertex 3.
 *       For vertex 1: decrement indegree from 2 to 1.
 *
 * Updated Indegree Array:
 *  +-----+-----+-----+-----+-----+-----+
 *  |  0  |  1  |  2  |  3  |  4  |  5  |
 *  +-----+-----+-----+-----+-----+-----+
 *  |  0  |  1  |  0  |  0  |  1  |  0  |
 *  +-----+-----+-----+-----+-----+-----+
 *
 * Queue after Iteration 3:
 *     +-----+
 *     |  3  |   <-- Front/Rear
 *     +-----+
 *
 * Iteration 4:
 *   - Dequeue vertex 3.
 *   - Append 3 to result: Result becomes [0, 5, 2, 3].
 *   - Process neighbor of 3: [1].
 *       For vertex 1: decrement indegree from 1 to 0; enqueue vertex 1.
 *
 * Updated Indegree Array:
 *  +-----+-----+-----+-----+-----+-----+
 *  |  0  |  1  |  2  |  3  |  4  |  5  |
 *  +-----+-----+-----+-----+-----+-----+
 *  |  0  |  0  |  0  |  0  |  1  |  0  |
 *  +-----+-----+-----+-----+-----+-----+
 *
 * Queue after Iteration 4:
 *     +-----+
 *     |  1  |   <-- Front/Rear
 *     +-----+
 *
 * Iteration 5:
 *   - Dequeue vertex 1.
 *   - Append 1 to result: Result becomes [0, 5, 2, 3, 1].
 *   - Process neighbor of 1: [4].
 *       For vertex 4: decrement indegree from 1 to 0; enqueue vertex 4.
 *
 * Updated Indegree Array:
 *  +-----+-----+-----+-----+-----+-----+
 *  |  0  |  1  |  2  |  3  |  4  |  5  |
 *  +-----+-----+-----+-----+-----+-----+
 *  |  0  |  0  |  0  |  0  |  0  |  0  |
 *  +-----+-----+-----+-----+-----+-----+
 *
 * Queue after Iteration 5:
 *     +-----+
 *     |  4  |   <-- Front/Rear
 *     +-----+
 *
 * Iteration 6:
 *   - Dequeue vertex 4.
 *   - Append 4 to result: Result becomes [0, 5, 2, 3, 1, 4].
 *   - Vertex 4 has no neighbors.
 *
 * Final Queue: (empty)
 *
 * Final Topological Order (Result Array):
 *     +-----+-----+-----+-----+-----+-----+
 *     |  0  |  5  |  2  |  3  |  1  |  4  |
 *     +-----+-----+-----+-----+-----+-----+
 *
 * The output [0, 5, 2, 3, 1, 4] is a valid topological sort for the given graph.
 *
 */
