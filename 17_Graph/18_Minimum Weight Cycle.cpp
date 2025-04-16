// GfG Link: https://www.geeksforgeeks.org/problems/minimum-weight-cycle/1

/*
 * Minimum Weight Cycle
 *
 * Difficulty: Hard Accuracy: 0.0% Submissions: 2+ Points: 8
 *
 * Given an undirected, weighted graph with V vertices numbered from 0 to V-1 and E edges, represented by a 2d array edges[][], where edges[i] = [u, v, w] represents the edge between the nodes u and v having w edge weight.
 * Your task is to find the minimum weight cycle in this graph.
 *
 * Examples:
 * Input: V = 5, edges[][] = [[0, 1, 2], [1, 2, 2], [1, 3, 1], [1, 4, 1], [0, 4, 3], [2, 3, 4]]
 * Output: 6
 * Explanation:
 * Minimum-weighted cycle is  0 → 1 → 4 → 0 with a total weight of 6(2 + 1 + 3)
 *
 * Input: V = 5, edges[][] = [[0, 1, 3], [1, 2, 2], [0, 4, 1], [1, 4, 2], [1, 3, 1], [3, 4, 2], [2, 3, 3]]
 * Output: 5
 * Explanation:
 * Minimum-weighted cycle is  1 → 3 → 4 → 1 with a total weight of 5(1 + 2 + 2)
 *
 * Constraints:
 * 1 ≤ V ≤ 100
 * 1 ≤ E = edges.size() ≤ 10^3
 * 1 ≤ edges[i][j] ≤ 100
 */

/************************************************************ C++ ************************************************/

// Approach: For each edge (u, v), find the shortest path from u to v ignoring that edge, and then add the edge weight to form a cycle. Keep track of the minimum cycle length.
// Time Complexity: O(E * (V + E) * log V), for each edge we run Dijkstra's algorithm.
// Space Complexity: O(V + E), for adjacency list and distance array.
class Solution {
public:
    // Function to construct adjacency list from edge list
    vector<vector<vector<int>>> constructAdj(int V, vector<vector<int>>& edges) {
        vector<vector<vector<int>>> adj(V); // adjacency list

        for (auto& edge : edges) {
            int u = edge[0], v = edge[1], w = edge[2];
            adj[u].push_back({ v, w }); // add neighbor and weight
            adj[v].push_back({ u, w }); // because the graph is undirected
        }
        return adj;
    }

    // Function to find shortest path between src and dest ignoring the edge (src, dest)
    int shortestPath(int V, vector<vector<vector<int>>>& adj, int src, int dest) {
        vector<int> dist(V, INT_MAX);   // distance array

        dist[src] = 0;

        // Min heap to get the node with minimum distance
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>> pq;
        pq.push({ 0, src });

        while (!pq.empty()) {
            pair<int, int> top = pq.top();
            pq.pop();
            int d = top.first, u = top.second;

            if (d > dist[u]) {
                continue;                // already found a better path
            }
            for (auto& neighbor : adj[u]) {
                int v = neighbor[0];
                int w = neighbor[1];

                // Skip the ignored edge (src, dest)
                if ((u == src && v == dest) || (u == dest && v == src)) {
                    continue;
                }

                if (dist[v] > dist[u] + w) {
                    dist[v] = dist[u] + w;
                    pq.push({ dist[v], v });
                }
            }
        }

        return dist[dest];   // shortest path from src to dest (excluding direct edge)
    }

    // Main function to find minimum weight cycle in the graph
    int findMinCycle(int V, vector<vector<int>>& edges) {
        vector<vector<vector<int>>> adj = constructAdj(V, edges); // build the graph
        int minCycle = INT_MAX;                                     // store minimum cycle length

        // Try to form cycle by removing each edge once and computing shortest path
        for (const auto& edge : edges) {
            int u = edge[0];
            int v = edge[1];
            int w = edge[2];

            int dist = shortestPath(V, adj, u, v);   // shortest path ignoring this edge

            if (dist != INT_MAX) {
                minCycle = min(minCycle, dist + w);   // total cycle = path + removed edge
            }
        }

        // If no cycle found, return -1
        return (minCycle == INT_MAX) ? -1 : minCycle;
    }
};

/*
 *
 * Dry Run
 *
 * Input:
 * V = 5
 * edges = [[0,1,2],[1,2,2],[1,3,1],[1,4,1],[0,4,3],[2,3,4]]
 *
 * Step 1: Build the graph using adjacency list.
 *
 * Step 2: For each edge:
 *  Try edge (0,1,2):
 *      Remove edge (0,1)
 *      Find shortest path from 0 to 1 → 0 → 4 → 1 → dist = 4
 *      Cycle = dist + edge weight = 4 + 2 = 6 → minCycle = 6
 *
 *  Try edge (1,2,2):
 *      Remove edge (1,2)
 *      Path 1 → 3 → 2 = 1 + 4 = 5 → Cycle = 5 + 2 = 7 → minCycle still 6
 *
 *  Try edge (1,3,1):
 *      Remove edge (1,3)
 *      Path 1 → 2 → 3 = 2 + 4 = 6 → Cycle = 6 + 1 = 7 → minCycle still 6
 *
 *  Try edge (1,4,1):
 *      Remove edge (1,4)
 *      Path 1 → 0 → 4 = 2 + 3 = 5 → Cycle = 5 + 1 = 6 → minCycle still 6
 *
 *  Try edge (0,4,3):
 *      Remove edge (0,4)
 *      Path 0 → 1 → 4 = 2 + 1 = 3 → Cycle = 3 + 3 = 6 → minCycle still 6
 *
 *  Try edge (2,3,4):
 *      Remove edge (2,3)
 *      Path 2 → 1 → 3 = 2 + 1 = 3 → Cycle = 3 + 4 = 7 → minCycle still 6
 *
 * Final Result: 6
 *
 *
 */

/************************************************************ JAVA ************************************************/

// Approach: For each edge, find the shortest path between its vertices (u, v) ignoring this edge. Then add the edge back to complete the cycle and keep track of the minimum cycle weight.
// Time Complexity: O(E * (V + E) * log V), since for each edge we run Dijkstra's algorithm.
// Space Complexity: O(V + E), for adjacency list and distance array.
class Solution {
    // Function to construct adjacency list from edge list
    private ArrayList<ArrayList<int[] constructAdj(int V, int[][] edges) {
        ArrayList<ArrayList<int[]>> adj = new ArrayList<>();

        for (int i = 0; i < V; i++) {
            adj.add(new ArrayList<>());
        }

        for (int[] edge : edges) {
            int u = edge[0], v = edge[1], w = edge[2];
            adj.get(u).add(new int[]{ v, w }); // undirected graph
            adj.get(v).add(new int[]{ u, w });
        }
        return adj;
    }

    // Function to compute shortest path from src to dest ignoring edge (src, dest)
    private int shortestPath(int V, ArrayList<ArrayList<int[]>> adj, int src, int dest) {
        int[] dist = new int[V];

        Arrays.fill(dist, Integer.MAX_VALUE);
        dist[src] = 0;

        PriorityQueue<int[]> pq = new PriorityQueue<>(Comparator.comparingInt(a->a[0]));
        pq.offer(new int[]{ 0, src });

        while (!pq.isEmpty()) {
            int[] current = pq.poll();
            int d = current[0];
            int u = current[1];

            if (d > dist[u]) {
                continue;
            }

            for (int[] neighbor : adj.get(u)) {
                int v = neighbor[0];
                int w = neighbor[1];

                // Skip the edge (src, dest)
                if ((u == src && v == dest) || (u == dest && v == src)) {
                    continue;
                }

                if (dist[v] > dist[u] + w) {
                    dist[v] = dist[u] + w;
                    pq.offer(new int[]{ dist[v], v });
                }
            }
        }

        return dist[dest]; // returns shortest distance or MAX_VALUE if unreachable
    }

    // Main function to find minimum weight cycle
    public int findMinCycle(int V, int[][] edges) {
        ArrayList<ArrayList<int[]>> adj = constructAdj(V, edges);
        int minCycle = Integer.MAX_VALUE;

        for (int[] edge : edges) {
            int u = edge[0], v = edge[1], w = edge[2];

            int dist = shortestPath(V, adj, u, v); // ignore current edge

            if (dist != Integer.MAX_VALUE) {
                minCycle = Math.min(minCycle, dist + w); // cycle weight = shortest path + ignored edge
            }
        }

        return (minCycle == Integer.MAX_VALUE) ? -1 : minCycle; // if no cycle found
    }
}

/*
 *
 * Dry Run
 *
 * Input:
 * V = 5
 * edges = [[0,1,2],[1,2,2],[1,3,1],[1,4,1],[0,4,3],[2,3,4]]
 *
 * Step 1: Construct adjacency list.
 *
 * Step 2: Loop through each edge:
 * → Edge (0,1,2):
 *    Remove edge (0,1), find path 0 → 4 → 1 = 3 + 1 = 4
 *    Add edge weight: 4 + 2 = 6 → minCycle = 6
 * → Edge (1,2,2):
 *    Remove edge (1,2), path 1 → 3 → 2 = 1 + 4 = 5
 *    Cycle = 5 + 2 = 7 → minCycle = 6
 * → Edge (1,3,1):
 *    Remove edge (1,3), path 1 → 2 → 3 = 2 + 4 = 6
 *    Cycle = 6 + 1 = 7 → minCycle = 6
 * → Edge (1,4,1):
 *    Remove edge (1,4), path 1 → 0 → 4 = 2 + 3 = 5
 *    Cycle = 5 + 1 = 6 → minCycle = 6
 * → Edge (0,4,3):
 *    Remove edge (0,4), path 0 → 1 → 4 = 2 + 1 = 3
 *    Cycle = 3 + 3 = 6 → minCycle = 6
 * → Edge (2,3,4):
 *    Remove edge (2,3), path 2 → 1 → 3 = 2 + 1 = 3
 *    Cycle = 3 + 4 = 7 → minCycle = 6
 *
 * Final Output: 6
 *
 */
