/*
 * Minimum cost to connect all houses in a city
 *
 * Difficulty: Medium Accuracy: 78.36% Submissions: 4K+ Points: 4
 *
 * Given a 2D array houses[][], consisting of n 2D coordinates {x, y} where each coordinate represents the location of each house, the task is to find the minimum cost to connect all the houses of the city.
 *
 * The cost of connecting two houses is the Manhattan Distance between the two points (xi, yi) and (xj, yj) i.e., |xi – xj| + |yi – yj|, where |p| denotes the absolute value of p.
 *
 * Examples :
 *
 * Input: n = 5 houses[][] = [[0, 7], [0, 9], [20, 7], [30, 7], [40, 70]]
 * Output: 105
 * Explanation:
 * Connect house 1 (0, 7) and house 2 (0, 9) with cost = 2
 * Connect house 1 (0, 7) and house 3 (20, 7) with cost = 20
 * Connect house 3 (20, 7) with house 4 (30, 7) with cost = 10
 * At last, connect house 4 (30, 7) with house 5 (40, 70) with cost 73.
 * All the houses are connected now.
 * The overall minimum cost is 2 + 10 + 20 + 73 = 105.
 *
 * Input: n = 4 houses[][] = [[0, 0], [1, 1], [1, 3], [3, 0]]
 * Output: 7
 * Explanation:
 * Connect house 1 (0, 0) with house 2 (1, 1) with cost = 2
 * Connect house 2 (1, 1) with house 3 (1, 3) with cost = 2
 * Connect house 1 (0, 0) with house 4 (3, 0) with cost = 3
 * The overall minimum cost is 3 + 2 + 2 = 7.
 *
 * Constraint:
 * 1 ≤ n ≤ 10^3
 * 0 ≤ houses[i][j] ≤ 10^3
 */

/************************************************************ C++ ************************************************/

// Approach: Use Prim's algorithm to compute the Minimum Spanning Tree (MST) over houses by first creating a complete graph based on Manhattan distances.
// Time Complexity: O(V^2 log V) due to complete graph generation and MST extraction using a priority queue, where V is the number of houses.
// Space Complexity: O(V^2) for the complete graph storage and O(V) for auxiliary data structures.
class Solution {
public:
    typedef pair<int, int> P;    // P holds {edge_weight, node_index}

    // Prim's algorithm on the graph represented by an adjacency list.
    int PrimsAlgo(vector<vector<P>>& adj, int V) {
        // Priority queue to store the next edge candidate in ascending order of weight.
        priority_queue<P, vector<P>, greater<P>> pq;

        // Start from vertex 0 with weight 0.
        pq.push({ 0, 0 });

        // Vector to track which vertex has already been included in the MST.
        vector<bool> inMST(V, false);
        int          sum = 0; // To store the sum of weights in the MST.

        // Process the priority queue until it's empty.
        while (!pq.empty()) {
            auto p = pq.top();
            pq.pop();            // Remove the edge with the smallest weight.

            int wt   = p.first;  // The weight of the current edge.
            int node = p.second; // The current node to be included.

            // If the node is already in the MST, skip it.
            if (inMST[node]) {
                continue;
            }

            // Mark the node as included in the MST and add the weight to the sum.
            inMST[node] = true;
            sum        += wt;

            // Traverse the adjacency list for the current node.
            for (auto& tmp : adj[node]) {
                int neighbor    = tmp.first;    // Adjacent vertex.
                int neighbor_wt = tmp.second;   // Weight of the edge to the neighbor.

                // If the neighbor is not yet in the MST, push it into the priority queue.
                if (!inMST[neighbor]) {
                    pq.push({ neighbor_wt, neighbor });
                }
            }
        }
        // Return the total sum of weights in the MST.
        return sum;
    }
    // Function to calculate the minimum cost to connect all houses using Manhattan distance.
    int minCost(vector<vector<int>>& houses) {
        int V = houses.size();

        // Create an adjacency list for a complete graph where each house is a vertex.
        vector<vector<P>> adj(V);

        // Build complete graph: for every pair of houses, compute the Manhattan distance.
        for (int i = 0; i < V; i++) {
            for (int j = i + 1; j < V; j++) {
                int x1 = houses[i][0];
                int y1 = houses[i][1];

                int x2 = houses[j][0];
                int y2 = houses[j][1];

                // Manhattan distance.
                int d = abs(x1 - x2) + abs(y1 - y2);

                // Add bidirectional edges.
                adj[i].push_back({ j, d });
                adj[j].push_back({ i, d });
            }
        }
        // Compute the sum of the weights in the MST using Prim's algorithm.
        return PrimsAlgo(adj, V);
    }
};

/*
 *
 * Dry Run
 *
 * Example: houses = [[0, 7], [0, 9], [20, 7], [30, 7], [40, 70]]
 *
 * Step 1: Graph Construction (Complete Graph via Manhattan Distance)
 *  - Number of houses, V = 5.
 *
 *  Compute distances between each pair:
 *     Between house 0: (0,7) and house 1: (0,9) → d = |0-0| + |7-9| = 0 + 2 = 2
 *     Between house 0: (0,7) and house 2: (20,7) → d = |0-20| + |7-7| = 20 + 0 = 20
 *     Between house 0: (0,7) and house 3: (30,7) → d = |0-30| + |7-7| = 30 + 0 = 30
 *     Between house 0: (0,7) and house 4: (40,70) → d = |0-40| + |7-70| = 40 + 63 = 103
 *
 *     Between house 1: (0,9) and house 2: (20,7) → d = |0-20| + |9-7| = 20 + 2 = 22
 *     Between house 1: (0,9) and house 3: (30,7) → d = |0-30| + |9-7| = 30 + 2 = 32
 *     Between house 1: (0,9) and house 4: (40,70) → d = |0-40| + |9-70| = 40 + 61 = 101
 *
 *     Between house 2: (20,7) and house 3: (30,7) → d = |20-30| + |7-7| = 10 + 0 = 10
 *     Between house 2: (20,7) and house 4: (40,70) → d = |20-40| + |7-70| = 20 + 63 = 83
 *
 *     Between house 3: (30,7) and house 4: (40,70) → d = |30-40| + |7-70| = 10 + 63 = 73
 *
 *  The complete graph (adjacency list) is built as:
 *     adj[0] = { {1,2}, {2,20}, {3,30}, {4,103} }
 *     adj[1] = { {0,2}, {2,22}, {3,32}, {4,101} }
 *     adj[2] = { {0,20}, {1,22}, {3,10}, {4,83} }
 *     adj[3] = { {0,30}, {1,32}, {2,10}, {4,73} }
 *     adj[4] = { {0,103}, {1,101}, {2,83}, {3,73} }
 *
 * -------------------------------------------------------
 * Step 2: Running Prim's Algorithm to Find MST
 *
 *  Initialization:
 *     - Start with vertex 0.
 *     - Min Heap initially: { {0, 0} }  (i.e., edge weight 0 at vertex 0)
 *     - Visited array: [F, F, F, F, F]
 *     - Sum = 0
 *
 *  Iteration 1:
 *     - Pop {0, 0} from heap → current node = 0, wt = 0.
 *     - Mark vertex 0 as visited. Updated visited: [T, F, F, F, F]
 *     - Add wt=0 to sum → sum = 0.
 *     - For all neighbors of vertex 0, push into heap (if not visited):
 *         Push {2, 1} from edge 0-1.
 *         Push {20, 2} from edge 0-2.
 *         Push {30, 3} from edge 0-3.
 *         Push {103, 4} from edge 0-4.
 *     - Heap now: { {2,1}, {20,2}, {30,3}, {103,4} }
 *
 *  Iteration 2:
 *     - Pop {2, 1} (min weight 2) → current node = 1.
 *     - Mark vertex 1 as visited. Updated visited: [T, T, F, F, F]
 *     - Add wt=2 → sum = 0 + 2 = 2.
 *     - For neighbors of vertex 1:
 *         {0,2} skipped (0 already visited),
 *         Push {22, 2} from edge 1-2.
 *         Push {32, 3} from edge 1-3.
 *         Push {101, 4} from edge 1-4.
 *     - Heap now: { {20,2}, {22,2}, {30,3}, {32,3}, {103,4}, {101,4} }
 *
 *  Iteration 3:
 *     - Pop {20, 2} → current node = 2, wt = 20.
 *     - Mark vertex 2 as visited. Updated visited: [T, T, T, F, F]
 *     - Add wt=20 → sum = 2 + 20 = 22.
 *     - For neighbors of vertex 2:
 *         {0,20} and {1,22} skipped (visited),
 *         Push {10, 3} from edge 2-3.
 *         Push {83, 4} from edge 2-4.
 *     - Heap now: { {10,3}, {22,2}, {30,3}, {32,3}, {101,4}, {103,4}, {83,4} }
 *       (Note: duplicate or higher weight edges for same nodes can be in heap, they are skipped when popped if visited.)
 *
 *  Iteration 4:
 *     - Pop {10, 3} → current node = 3, wt = 10.
 *     - Mark vertex 3 as visited. Updated visited: [T, T, T, T, F]
 *     - Add wt=10 → sum = 22 + 10 = 32.
 *     - For neighbors of vertex 3:
 *         {0,30}, {1,32}, {2,10} skipped (visited),
 *         Push {73, 4} from edge 3-4.
 *     - Heap now: { {73,4}, {83,4}, {101,4}, {103,4}, ... }
 *
 *  Iteration 5:
 *     - Pop next minimal edge for an unvisited vertex; smallest is {73, 4} → current node = 4.
 *     - Mark vertex 4 as visited. Updated visited: [T, T, T, T, T]
 *     - Add wt=73 → sum = 32 + 73 = 105.
 *     - All vertices are now visited; the algorithm terminates.
 *
 * Final Result: The MST total weight (minimum cost to connect all houses) is 105.
 *
 * -------------------------------------------------------
 * Visual Recap of MST Connections (as per example explanation):
 *
 *   Connect house 0 (0,7) with house 1 (0,9)  → cost = 2
 *   Connect house 0 (0,7) with house 2 (20,7) → cost = 20
 *   Connect house 2 (20,7) with house 3 (30,7) → cost = 10
 *   Connect house 3 (30,7) with house 4 (40,70) → cost = 73
 *
 *   Total cost = 2 + 20 + 10 + 73 = 105
 *
 * This matches the output and confirms the correctness of the algorithm.
 */

/************************************************************ JAVA ************************************************/

// Approach: Use Prim's algorithm to compute the MST over a complete graph where the weight between two houses is the Manhattan distance.
// Time Complexity: O(V^2 log V) due to the complete graph generation and MST extraction using a priority queue.
// Space Complexity: O(V^2) for the graph storage and O(V) for auxiliary data structures.
class Solution {
    // Function to calculate the minimum cost to connect all houses using Manhattan distance.
    public int minCost(int[][] houses) {
        int V = houses.length;  // Number of houses, each house is a vertex.

        // Build an adjacency list for the complete graph.
        // Each element in adj is an ArrayList of int arrays, where int[] = {neighbor, weight}
        List<List<int[]>> adj = new ArrayList<>();

        for (int i = 0; i < V; i++) {
            adj.add(new ArrayList<>());
        }

        // Create complete graph: for every pair of houses, compute Manhattan distance.
        for (int i = 0; i < V; i++) {
            for (int j = i + 1; j < V; j++) {
                int x1 = houses[i][0], y1 = houses[i][1];
                int x2 = houses[j][0], y2 = houses[j][1];
                int d = Math.abs(x1 - x2) + Math.abs(y1 - y2);  // Manhattan distance.
                // Add bidirectional edges.
                adj.get(i).add(new int[] { j, d });
                adj.get(j).add(new int[] { i, d });
            }
        }

        // Prim's algorithm initialization.
        // Priority queue to store edge candidates as int[] {weight, node} in ascending order of weight.
        PriorityQueue<int[]> pq = new PriorityQueue<>((a, b)->a[0] - b[0]);
        boolean[] inMST = new boolean[V]; // Tracks if a house is already included in the MST.
        int sum = 0;                      // Sum of the weights of the edges in the MST.

        // Start from vertex 0 with initial weight 0.
        pq.add(new int[] { 0, 0 });

        // Process until the queue is empty.
        while (!pq.isEmpty()) {
            int[] curr = pq.poll();  // Remove the edge with the smallest weight.
            int wt   = curr[0];      // Edge weight.
            int node = curr[1];      // Current house/node.

            // If node is already included in MST, skip it.
            if (inMST[node]) {
                continue;
            }

            // Include the node in MST and add its edge weight to the sum.
            inMST[node] = true;
            sum        += wt;

            // Iterate over all adjacent edges of the current node.
            for (int[] edge : adj.get(node)) {
                int neighbor    = edge[0]; // Adjacent house.
                int neighbor_wt = edge[1]; // Weight of the edge connecting the current node to the neighbor.
                if (!inMST[neighbor]) {
                    pq.add(new int[] { neighbor_wt, neighbor });
                }
            }
        }
        return sum;
    }
}

/*
 *
 * Dry Run
 *
 * Example: houses = [[0, 7], [0, 9], [20, 7], [30, 7], [40, 70]]
 *
 * Step 1: Graph Construction (Complete Graph via Manhattan Distance)
 *  - Number of houses, V = 5.
 *
 *  Calculate Manhattan distances between each pair:
 *    - Between house 0: (0,7) and house 1: (0,9)
 *         d = |0-0| + |7-9| = 0 + 2 = 2
 *    - Between house 0: (0,7) and house 2: (20,7)
 *         d = |0-20| + |7-7| = 20 + 0 = 20
 *    - Between house 0: (0,7) and house 3: (30,7)
 *         d = |0-30| + |7-7| = 30 + 0 = 30
 *    - Between house 0: (0,7) and house 4: (40,70)
 *         d = |0-40| + |7-70| = 40 + 63 = 103
 *
 *    - Between house 1: (0,9) and house 2: (20,7)
 *         d = |0-20| + |9-7| = 20 + 2 = 22
 *    - Between house 1: (0,9) and house 3: (30,7)
 *         d = |0-30| + |9-7| = 30 + 2 = 32
 *    - Between house 1: (0,9) and house 4: (40,70)
 *         d = |0-40| + |9-70| = 40 + 61 = 101
 *
 *    - Between house 2: (20,7) and house 3: (30,7)
 *         d = |20-30| + |7-7| = 10 + 0 = 10
 *    - Between house 2: (20,7) and house 4: (40,70)
 *         d = |20-40| + |7-70| = 20 + 63 = 83
 *
 *    - Between house 3: (30,7) and house 4: (40,70)
 *         d = |30-40| + |7-70| = 10 + 63 = 73
 *
 *  The adjacency list will be built as follows:
 *    adj[0] = { {1,2}, {2,20}, {3,30}, {4,103} }
 *    adj[1] = { {0,2}, {2,22}, {3,32}, {4,101} }
 *    adj[2] = { {0,20}, {1,22}, {3,10}, {4,83} }
 *    adj[3] = { {0,30}, {1,32}, {2,10}, {4,73} }
 *    adj[4] = { {0,103}, {1,101}, {2,83}, {3,73} }
 *
 * -------------------------------------------------------
 * Step 2: Executing Prim's Algorithm to Find MST
 *
 *  Initialization:
 *    - Start with vertex 0.
 *    - Priority Queue (min-heap) initially: { {0, 0} }  (edge weight 0 at vertex 0)
 *    - Visited Array: [F, F, F, F, F]
 *    - Sum = 0
 *
 *  Iteration 1:
 *    - Pop {0,0} → current node = 0, wt = 0.
 *    - Mark vertex 0 as visited. Updated visited: [T, F, F, F, F]
 *    - Add wt=0 to sum → sum = 0.
 *    - For neighbors of vertex 0:
 *         Push {2,1} from edge 0-1.
 *         Push {20,2} from edge 0-2.
 *         Push {30,3} from edge 0-3.
 *         Push {103,4} from edge 0-4.
 *    - Min-heap now: { {2,1}, {20,2}, {30,3}, {103,4} }
 *
 *  Iteration 2:
 *    - Pop {2,1} (smallest weight 2) → current node = 1.
 *    - Mark vertex 1 as visited. Visited: [T, T, F, F, F]
 *    - Add wt=2 → sum = 0 + 2 = 2.
 *    - For neighbors of vertex 1:
 *         Skip {0,2} (already visited).
 *         Push {22,2} from edge 1-2.
 *         Push {32,3} from edge 1-3.
 *         Push {101,4} from edge 1-4.
 *    - Min-heap now includes: { {20,2}, {22,2}, {30,3}, {32,3}, {103,4}, {101,4} }
 *
 *  Iteration 3:
 *    - Pop {20,2} → current node = 2, wt = 20.
 *    - Mark vertex 2 as visited. Visited: [T, T, T, F, F]
 *    - Add wt=20 → sum = 2 + 20 = 22.
 *    - For neighbors of vertex 2:
 *         Skip {0,20} and {1,22} (both visited).
 *         Push {10,3} from edge 2-3.
 *         Push {83,4} from edge 2-4.
 *    - Min-heap now: { {10,3}, {22,2}, {30,3}, {32,3}, {101,4}, {103,4}, {83,4} }
 *
 *  Iteration 4:
 *    - Pop {10,3} → current node = 3, wt = 10.
 *    - Mark vertex 3 as visited. Visited: [T, T, T, T, F]
 *    - Add wt=10 → sum = 22 + 10 = 32.
 *    - For neighbors of vertex 3:
 *         Skip {0,30}, {1,32}, {2,10} (visited).
 *         Push {73,4} from edge 3-4.
 *    - Min-heap now: { {73,4}, {83,4}, {101,4}, {103,4}, ... }
 *
 *  Iteration 5:
 *    - Pop the smallest edge for an unvisited vertex: {73,4} → current node = 4.
 *    - Mark vertex 4 as visited. Visited: [T, T, T, T, T]
 *    - Add wt=73 → sum = 32 + 73 = 105.
 *    - Now, all vertices are visited; MST construction is complete.
 *
 * Final Result: The MST total weight is 105.
 *
 * -------------------------------------------------------
 * Visual Recap (Based on Example):
 *
 *   Connect house 0 (0,7) with house 1 (0,9)  → cost = 2
 *   Connect house 0 (0,7) with house 2 (20,7) → cost = 20
 *   Connect house 2 (20,7) with house 3 (30,7) → cost = 10
 *   Connect house 3 (30,7) with house 4 (40,70) → cost = 73
 *
 *   Total cost = 2 + 20 + 10 + 73 = 105
 *
 * This confirms the algorithm's output.
 */
