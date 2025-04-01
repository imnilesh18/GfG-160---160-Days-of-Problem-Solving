/*
 * BFS of graph
 *
 * Difficulty: Easy Accuracy: 44.09% Submissions: 470K+ Points: 2 Average Time: 10m
 *
 * Given a connected undirected graph represented by a 2-d adjacency list adj[][], where each adj[i] represents the list of vertices connected to vertex i. Perform a Breadth First Search (BFS) traversal starting from vertex 0, visiting vertices from left to right according to the given adjacency list, and return a list containing the BFS traversal of the graph.
 *
 * Note: Do traverse in the same order as they are in the given adjacency list.
 *
 * Examples:
 *
 * Input: adj[][] = [[2, 3, 1], [0], [0, 4], [0], [2]]
 * Output: [0, 2, 3, 1, 4]
 * Explanation: Starting from 0, the BFS traversal will follow these steps:
 * Visit 0 → Output: 0
 * Visit 2 (first neighbor of 0) → Output: 0, 2
 * Visit 3 (next neighbor of 0) → Output: 0, 2, 3
 * Visit 1 (next neighbor of 0) → Output: 0, 2, 3,
 * Visit 4 (neighbor of 2) → Final Output: 0, 2, 3, 1, 4
 *
 * Input: adj[][] = [[1, 2], [0, 2], [0, 1, 3, 4], [2], [2]]
 * Output: [0, 1, 2, 3, 4]
 * Explanation: Starting from 0, the BFS traversal proceeds as follows:
 * Visit 0 → Output: 0
 * Visit 1 (the first neighbor of 0) → Output: 0, 1
 * Visit 2 (the next neighbor of 0) → Output: 0, 1, 2
 * Visit 3 (the first neighbor of 2 that hasn't been visited yet) → Output: 0, 1, 2, 3
 * Visit 4 (the next neighbor of 2) → Final Output: 0, 1, 2, 3, 4
 *
 * Constraints:
 * 1 ≤ adj.size() ≤ 10^4
 * 1 ≤ adj[i][j] ≤ 10^4
 */

/************************************************************ C++ ************************************************/

// Approach: Use iterative BFS using a queue; traverse each neighbor in the order provided, marking nodes visited when enqueued.
// Time Complexity: O(V + E) - Each vertex and edge is processed at most once during the BFS.
// Space Complexity: O(V) - Additional space for the queue and the visited array.
class Solution {
public:

    void BFS(unordered_map<int, vector<int> >& adj, int u, vector<bool>& visited, vector<int>& result) {
        queue<int> que;

        // Enqueue the starting vertex and mark it as visited.
        que.push(u);
        visited[u] = true;
        result.push_back(u);

        while (!que.empty()) {
            int u = que.front();
            que.pop();

            // Process each neighbor of the current node.
            for (int& v : adj[u]) {
                if (!visited[v]) {
                    que.push(v);
                    visited[v] = true;
                    result.push_back(v);
                }
            }
        }
    }
    // Function to return Breadth First Traversal of given graph.
    vector<int> bfs(vector<vector<int> >& mp) {
        unordered_map<int, vector<int> > adj;
        int V = mp.size();

        for (int i = 0; i < V; i++) {
            for (auto it = mp[i].begin(); it != mp[i].end(); it++) {
                adj[i].push_back(*it);
            }
        }

        vector<bool> visited(V, false);
        vector<int>  result;
        BFS(adj, 0, visited, result);

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
 * Step-by-step BFS Traversal:
 *
 * Step 1: Start at node 0.
 *   Queue before: []
 *   Enqueue 0.
 *   Queue after: [0]
 *
 *   Graph Status:
 *             [*0*]  <-- starting node (visited)
 *           /   |   \
 *         2     3    1
 *         |
 *         4
 *
 *   Output: [0]
 *
 *   Box Representation of Queue:
 *   +---------+
 *   | Queue:  |
 *   |  [0]    |
 *   +---------+
 *
 * Step 2: Process node 0.
 *   Queue before processing: [0]
 *   Dequeue 0.
 *   Process neighbors of 0: 2, 3, 1.
 *     Enqueue 2 -> Queue becomes: [2]
 *     Enqueue 3 -> Queue becomes: [2, 3]
 *     Enqueue 1 -> Queue becomes: [2, 3, 1]
 *
 *   Graph Status after visiting node 0:
 *             [0]*      <-- node 0 visited
 *           /   |   \
 *         2     3    1   <-- nodes 2,3,1 are now enqueued (pending visit)
 *         |
 *         4
 *
 *   Box Representation of Queue:
 *   +-------------------+
 *   | Queue: [2, 3, 1]  |
 *   +-------------------+
 *
 *   Output: [0, 2, 3, 1]
 *
 * Step 3: Process node 2.
 *   Queue before processing: [2, 3, 1]
 *   Dequeue 2.
 *   Process neighbors of 2: 0, 4.
 *     0 is already visited.
 *     Enqueue 4 -> Queue becomes: [3, 1, 4]
 *
 *   Graph Status after visiting node 2:
 *             [0]*
 *           /   |   \
 *        [2]*   3    1   <-- node 2 visited; node 4 enqueued from node 2
 *         |
 *        [4]   <-- node 4 enqueued
 *
 *   Box Representation of Queue:
 *   +---------------------+
 *   | Queue: [3, 1, 4]    |
 *   +---------------------+
 *
 *   Output: [0, 2, 3, 1, 4]
 *
 * Step 4: Process node 3.
 *   Queue before processing: [3, 1, 4]
 *   Dequeue 3.
 *   Process neighbors of 3: 0.
 *     0 is already visited.
 *   Queue remains: [1, 4]
 *
 *   Graph Status after visiting node 3:
 *             [0]*
 *           /   |   \
 *        [2]* [3]*   1   <-- node 3 visited
 *         |
 *        [4]
 *
 *   Box Representation of Queue:
 *   +-------------+
 *   | Queue: [1, 4]|
 *   +-------------+
 *
 *   Output remains: [0, 2, 3, 1, 4]
 *
 * Step 5: Process node 1.
 *   Queue before processing: [1, 4]
 *   Dequeue 1.
 *   Process neighbors of 1: 0.
 *     0 is already visited.
 *   Queue remains: [4]
 *
 *   Graph Status after visiting node 1:
 *             [0]*
 *           /   |   \
 *        [2]* [3]* [1]*  <-- node 1 visited
 *         |
 *        [4]
 *
 *   Box Representation of Queue:
 *   +---------+
 *   | Queue: [4]|
 *   +---------+
 *
 *   Output remains: [0, 2, 3, 1, 4]
 *
 * Step 6: Process node 4.
 *   Queue before processing: [4]
 *   Dequeue 4.
 *   Process neighbors of 4: 2.
 *     2 is already visited.
 *   Queue becomes: []
 *
 *   Graph Status after visiting node 4:
 *             [0]*
 *           /   |   \
 *        [2]* [3]* [1]*
 *         |
 *        [4]*  <-- node 4 visited
 *
 *   Box Representation of Queue:
 *   +---------+
 *   | Queue: []|
 *   +---------+
 *
 *   Output remains: [0, 2, 3, 1, 4]
 *
 * Final BFS Traversal: [0, 2, 3, 1, 4]
 *
 * Legend: [x]* indicates node x has been visited.
 *
 */

/************************************************************ JAVA ************************************************/

// Approach: Use iterative BFS using a queue; traverse each neighbor in the order provided, marking nodes visited when enqueued.
// Time Complexity: O(V + E) - Each vertex and edge is processed at most once during the BFS.
// Space Complexity: O(V) - Additional space for the queue and the visited array.
class Solution {
    // Recursive BFS function that explores nodes and records the traversal order.
    void BFS(HashMap<Integer, ArrayList<Integer> > adj, int u, boolean[] visited, ArrayList<Integer> result) {
        Queue<Integer> que = new LinkedList<>();

        // Enqueue the starting vertex and mark it as visited.
        que.add(u);
        visited[u] = true;
        result.add(u);

        while (!que.isEmpty()) {
            int curr = que.poll();

            // Process each neighbor of the current node.
            for (int v : adj.get(curr)) {
                if (!visited[v]) {
                    que.add(v);
                    visited[v] = true;
                    result.add(v);
                }
            }
        }
    }
    // Function to return Breadth First Search Traversal of given graph.
    public ArrayList<Integer> bfs(ArrayList<ArrayList<Integer> > mp) {
        HashMap<Integer, ArrayList<Integer> > adj = new HashMap<>();
        int V = mp.size();

        for (int i = 0; i < V; i++) {
            adj.put(i, new ArrayList<Integer>());
            for (int v : mp.get(i)) {
                adj.get(i).add(v);
            }
        }

        boolean[] visited = new boolean[V];
        ArrayList<Integer> result = new ArrayList<>();
        BFS(adj, 0, visited, result);

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
 * Step-by-step BFS Traversal:
 *
 * Step 1: Start at node 0.
 *   Queue before: []
 *   Enqueue 0.
 *   Queue after: [0]
 *
 *   Graph Status:
 *             [*0*]  <-- starting node (visited)
 *           /   |   \
 *         2     3    1
 *         |
 *         4
 *
 *   Output: [0]
 *
 *   Box Representation of Queue:
 *   +---------+
 *   | Queue:  |
 *   |  [0]    |
 *   +---------+
 *
 * Step 2: Process node 0.
 *   Queue before processing: [0]
 *   Dequeue 0.
 *   Process neighbors of 0: 2, 3, 1.
 *     Enqueue 2 -> Queue becomes: [2]
 *     Enqueue 3 -> Queue becomes: [2, 3]
 *     Enqueue 1 -> Queue becomes: [2, 3, 1]
 *
 *   Graph Status after visiting node 0:
 *             [0]*      <-- node 0 visited
 *           /   |   \
 *         2     3    1   <-- nodes 2,3,1 are now enqueued (pending visit)
 *         |
 *         4
 *
 *   Box Representation of Queue:
 *   +-------------------+
 *   | Queue: [2, 3, 1]  |
 *   +-------------------+
 *
 *   Output: [0, 2, 3, 1]
 *
 * Step 3: Process node 2.
 *   Queue before processing: [2, 3, 1]
 *   Dequeue 2.
 *   Process neighbors of 2: 0, 4.
 *     0 is already visited.
 *     Enqueue 4 -> Queue becomes: [3, 1, 4]
 *
 *   Graph Status after visiting node 2:
 *             [0]*
 *           /   |   \
 *        [2]*   3    1   <-- node 2 visited; node 4 enqueued from node 2
 *         |
 *        [4]   <-- node 4 enqueued
 *
 *   Box Representation of Queue:
 *   +---------------------+
 *   | Queue: [3, 1, 4]    |
 *   +---------------------+
 *
 *   Output: [0, 2, 3, 1, 4]
 *
 * Step 4: Process node 3.
 *   Queue before processing: [3, 1, 4]
 *   Dequeue 3.
 *   Process neighbors of 3: 0.
 *     0 is already visited.
 *   Queue remains: [1, 4]
 *
 *   Graph Status after visiting node 3:
 *             [0]*
 *           /   |   \
 *        [2]* [3]*   1   <-- node 3 visited
 *         |
 *        [4]
 *
 *   Box Representation of Queue:
 *   +-------------+
 *   | Queue: [1, 4]|
 *   +-------------+
 *
 *   Output remains: [0, 2, 3, 1, 4]
 *
 * Step 5: Process node 1.
 *   Queue before processing: [1, 4]
 *   Dequeue 1.
 *   Process neighbors of 1: 0.
 *     0 is already visited.
 *   Queue remains: [4]
 *
 *   Graph Status after visiting node 1:
 *             [0]*
 *           /   |   \
 *        [2]* [3]* [1]*  <-- node 1 visited
 *         |
 *        [4]
 *
 *   Box Representation of Queue:
 *   +---------+
 *   | Queue: [4]|
 *   +---------+
 *
 *   Output remains: [0, 2, 3, 1, 4]
 *
 * Step 6: Process node 4.
 *   Queue before processing: [4]
 *   Dequeue 4.
 *   Process neighbors of 4: 2.
 *     2 is already visited.
 *   Queue becomes: []
 *
 *   Graph Status after visiting node 4:
 *             [0]*
 *           /   |   \
 *        [2]* [3]* [1]*
 *         |
 *        [4]*  <-- node 4 visited
 *
 *   Box Representation of Queue:
 *   +---------+
 *   | Queue: []|
 *   +---------+
 *
 *   Output remains: [0, 2, 3, 1, 4]
 *
 * Final BFS Traversal: [0, 2, 3, 1, 4]
 *
 * Legend: [x]* indicates node x has been visited.
 *
 */
