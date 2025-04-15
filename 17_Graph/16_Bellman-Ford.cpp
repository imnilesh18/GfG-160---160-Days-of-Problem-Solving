/*
 * Bellman-Ford
 *
 * Difficulty: Medium Accuracy: 48.11% Submissions: 189K+ Points: 4 Average Time: 25m
 *
 * Given an weighted graph with V vertices numbered from 0 to V-1 and E edges, represented by a 2d array edges[][], where edges[i] = [u, v, w] represents a direct edge from node u to v having w edge weight. You are also given a source vertex src.
 *
 * Your task is to compute the shortest distances from the source to all other vertices. If a vertex is unreachable from the source, its distance should be marked as 108. Additionally, if the graph contains a negative weight cycle, return [-1] to indicate that shortest paths cannot be reliably computed.
 *
 * Examples:
 *
 * Input: V = 5, edges[][] = [[1, 3, 2], [4, 3, -1], [2, 4, 1], [1, 2, 1], [0, 1, 5]], src = 0
 * Output: [0, 5, 6, 6, 7]
 * Explanation: Shortest Paths:
 * For 0 to 1 minimum distance will be 5. By following path 0 → 1
 * For 0 to 2 minimum distance will be 6. By following path 0 → 1  → 2
 * For 0 to 3 minimum distance will be 6. By following path 0 → 1  → 2 → 4 → 3
 * For 0 to 4 minimum distance will be 7. By following path 0 → 1  → 2 → 4
 *
 * Input: V = 4, edges[][] = [[0, 1, 4], [1, 2, -6], [2, 3, 5], [3, 1, -2]], src = 0
 * Output: [-1]
 * Explanation: The graph contains a negative weight cycle formed by the path 1 → 2 → 3 → 1, where the total weight of the cycle is negative.
 *
 * Constraints:
 * 1 ≤ V ≤ 100
 * 1 ≤ E = edges.size() ≤ V*(V-1)
 * -1000 ≤ w ≤ 1000
 * 0 ≤ src < V
 */

/************************************************************ C++ ************************************************/

// Approach: Use the Bellman-Ford algorithm by relaxing all edges V times; the Vth iteration is used to detect negative weight cycles.
// Time Complexity: O(V * E) - we perform V iterations over all E edges.
// Space Complexity: O(V) - we use an array of size V to store the distances.
class Solution {
public:
    vector<int> bellmanFord(int V, vector<vector<int> >& edges, int src) {
        // Initialize distances to all vertices as "infinite" (here represented by 1e8)
        vector<int> dist(V, 1e8);

        // Distance from source to itself is 0
        dist[src] = 0;

        // Relax all edges V times. The extra iteration (Vth) is for detecting a negative weight cycle.
        for (int i = 0; i < V; i++) {
            // Iterate over each edge in the graph
            for (vector<int> edge : edges) {
                int u  = edge[0];
                int v  = edge[1];
                int wt = edge[2];
                // If the source vertex u has been reached and the new distance is shorter, update it.
                if (dist[u] != 1e8 && dist[u] + wt < dist[v]) {
                    // If we are in the Vth iteration, a negative cycle exists.
                    if (i == V - 1) {
                        return { -1 };
                    }

                    // Otherwise, update the shortest distance to vertex v.
                    dist[v] = dist[u] + wt;
                }
            }
        }

        return dist;
    }
};

/*
 *
 * Dry Run
 * Example: V = 5, edges = [[1, 3, 2], [4, 3, -1], [2, 4, 1], [1, 2, 1], [0, 1, 5]], src = 0
 * Initial distances = [0, 1e8, 1e8, 1e8, 1e8]
 * Iteration 1:
 *  - Process edge [0, 1, 5]: update distance[1] from 1e8 to 5
 *  - Process edge [1, 2, 1]: update distance[2] from 1e8 to 5 + 1 = 6
 *  - Process edge [1, 3, 2]: update distance[3] from 1e8 to 5 + 2 = 7
 *  - Process edge [2, 4, 1]: update distance[4] from 1e8 to 6 + 1 = 7
 *  - Process edge [4, 3, -1]: update distance[3] from 7 to 7 + (-1) = 6
 * Subsequent iterations do not result in further updates.
 * Final distances = [0, 5, 6, 6, 7]
 */

/************************************************************ JAVA ************************************************/

// Approach: Use the Bellman-Ford algorithm by relaxing all edges V times; the extra iteration (Vth) is used to detect negative weight cycles.
// Time Complexity: O(V * E) - we perform V iterations over all E edges.
// Space Complexity: O(V) - we use an array of size V to store the distances.
class Solution {
    public int[] bellmanFord(int V, int[][] edges, int src) {
        // Initialize distances for all vertices as "infinite" (here represented by (int)1e8)
        int[] dist = new int[V];

        Arrays.fill(dist, (int)1e8);
        // Distance from source to itself is 0
        dist[src] = 0;

        // Relax all edges V times. The extra iteration (Vth) is for detecting negative weight cycles.
        for (int i = 0; i < V; i++) {
            // Iterate over each edge in the given array.
            for (int[] edge : edges) {
                int u  = edge[0];
                int v  = edge[1];
                int wt = edge[2];
                // If vertex u is reachable and going through u gives a shorter path to v, update.
                if (dist[u] != 1e8 && dist[u] + wt < dist[v]) {
                    // On the Vth iteration, if an update is possible, then a negative cycle exists.
                    if (i == V - 1) {
                        return new int[]{ -1 };
                    }

                    // Update the shortest distance to vertex v.
                    dist[v] = dist[u] + wt;
                }
            }
        }

        return dist;
    }
}

/*
 *
 * Dry Run
 * Example: V = 5, edges = [[1, 3, 2], [4, 3, -1], [2, 4, 1], [1, 2, 1], [0, 1, 5]], src = 0
 * Initial distances = [0, 1e8, 1e8, 1e8, 1e8]
 * Iteration 1:
 *  - Process edge [0, 1, 5]: update distance[1] from 1e8 to 5
 *  - Process edge [1, 2, 1]: update distance[2] from 1e8 to 5 + 1 = 6
 *  - Process edge [1, 3, 2]: update distance[3] from 1e8 to 5 + 2 = 7
 *  - Process edge [2, 4, 1]: update distance[4] from 1e8 to 6 + 1 = 7
 *  - Process edge [4, 3, -1]: update distance[3] from 7 to 7 + (-1) = 6
 * Subsequent iterations do not alter the distances further.
 * Final distances = [0, 5, 6, 6, 7]
 */
