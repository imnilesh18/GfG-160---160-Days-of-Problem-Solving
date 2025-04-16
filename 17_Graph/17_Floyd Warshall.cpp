/*
 * =====================================================================
 * Floyd Warshall Algorithm - All-Pairs Shortest Path
 * =====================================================================
 *
 * Overview:
 * ---------
 * The Floyd Warshall Algorithm computes the shortest distances between
 * every pair of vertices in an edge-weighted graph. Unlike Dijkstra's
 * or Bellman-Ford which solve the "one source – one destination" problem,
 * this algorithm is designed to solve the "all-pairs" problem.
 *
 * Multi source shortest path algorithm
 *
 * Directed vs. Undirected Graphs:
 * ---------------------------------
 * - Although typically presented for directed graphs, the algorithm
 *   can be applied to undirected graphs as well.
 *
 * For an undirected graph:
 *         5
 *    0 ------- 1
 *
 * This undirected edge can be represented using two directed edges:
 *         5
 *    0 ------> 1
 *     <------
 *             5
 *
 * Example Graph:
 * --------------
 * Consider a graph with 4 vertices (0, 1, 2, 3) and edges represented
 * with the following drawing:
 *
 *                            8
 *                        ←──────────
 *                   0                1
 *                 │  ↑  ↖ ─────────→
 *                 │  │    \   3      │
 *                 │  │      \        │
 *              7  │  │ 2      \ 5    │  2
 *                 │  │         \     │
 *                 │  │           \   │
 *                 ↓  │             \ ↓
 *                   3   ←──────────  2
 *                            1
 *
 * Matrix Representation:
 * ----------------------
 * The graph can be represented as an adjacency matrix. For instance, if
 * we denote ∞ for no direct edge, one possible representation is:
 *
 *               Columns
 *          0      1      2      3
 *       +------+------+------+------+
 *     0 |   0  |   3  |   ∞  |   7  |
 *       +------+------+------+------+
 *     1 |   8  |   0  |   2  |   ∞  |
 *       +------+------+------+------+
 *     2 |   5  |   ∞  |   0  |   1  |
 *       +------+------+------+------+
 *     3 |   2  |   ∞  |   ∞  |   0  |
 *       +------+------+------+------+
 *
 * So now,
 * V = 0, 1 , 2, 3
 *       8
 * 1 ─────────→ 0
 *
 *         via(through)
 * 1 ─────────→ k ─────────→ 0
 *
 *      2            5
 * 1 ─────────→ 2 ─────────→ 0   = 7 (which is less than 8)
 *
 * For example, the minimum distance from vertex 2 to vertex 3 is directly
 * given by grid[2][3] after the matrix has been properly updated.
 *
 * Step-by-Step Process:
 * ---------------------
 * 1. **Initial Setup:**
 *    - Create the matrix with initial weights.
 *    - Use ∞ where there is no direct edge.
 *
 * 2. **Iterative Update:**
 *    - Consider each vertex as an intermediate vertex (denoted as 'via').
 *    - For every pair of vertices (i, j), update the matrix with:
 *
 *          grid[i][j] = min(grid[i][j], grid[i][via] + grid[via][j]);
 *
 *    - For example, consider the following intermediate steps:
 *
 *          Evaluating via 0:
 *
 *                               via 0              │  via 1  │  via 2  │    via 3
 *          ───────────────────────────────────────────────────────────────────────
 *          [0][1] = 3  │ 0 ─→ 0 ─→ 1 = 0 + 3 = 3   │
 *          [0][2] = ∞  │ 0 ─→ 0 ─→ 2 = 0 + ∞ = ∞   │
 *          [0][3] = 7  │ 0 ─→ 0 ─→ 3 = 0 + 7 = 7   │
 *                      │                           │
 *          [1][0] = 8  │ 1 ─→ 0 ─→ 0 = 8 + 0 = 8   │
 *          [1][2] = 2  │ 1 ─→ 0 ─→ 2 = 8 + ∞ = ∞   │
 *          [1][3] = ∞  │ 1 ─→ 0 ─→ 3 = 8 + 7 = 15  │
 *                      │                           │
 *          [2][0] = 5  │ 2 ─→ 0 ─→ 0 = 5 + 0 = 5   │
 *          [2][1] = ∞  │ 2 ─→ 0 ─→ 1 = 5 + 3 = 8   │
 *          [2][3] = 1  │ 2 ─→ 0 ─→ 3 = 5 + 7 = 12  │
 *                      │                           │
 *          [3][0] = 2  │ 3 ─→ 0 ─→ 0 = 2 + 0 = 2   │
 *          [3][1] = ∞  │ 3 ─→ 0 ─→ 1 = 2 + 3 = 5   │
 *          [3][2] = ∞  │ 3 ─→ 0 ─→ 2 = 2 + ∞ = ∞   │
 *
 *        - Updates:
 *          - [1][3] changes from ∞ to 15.
 *          - [2][1] changes from ∞ to 8.
 *          - [3][1] changes from ∞ to 5.
 *
 * 3. **Pseudocode Implementation:**
 *
 *    The following pseudocode summarizes the core idea of the algorithm:
 *
 *    ------------------------------------------------------
 *    for (int via = 0; via < n; via++) {
 *        for (int i = 0; i < n; i++) {
 *            for (int j = 0; j < n; j++) {
 *                grid[i][j] = min(grid[i][j], grid[i][via] + grid[via][j]);
 *            }
 *        }
 *    }
 *    return grid;
 *    ------------------------------------------------------
 *
 *    **Time Complexity:** O(n³)
 *
 * Detecting Negative Cycles:
 * --------------------------
 * The algorithm is capable of detecting negative weight cycles.
 * Consider the following example graph:
 *
 *                    Columns
 *             0      1     2
 *         +------+------+------+
 *       0 |  0   |      |      |
 *         +------+------+------+
 *       1 |      |  0   |      |
 *         +------+------+------+
 *       2 |      |      |  0   |
 *         +------+------+------+
 *
 *            4
 *        0 ───────→ 1
 *         ↖         │
 *           \       │
 *        -4   \     │   -3
 *              \    │
 *               \   │
 *                \  ↓
 *                  2
 *
 * - **Explanation:**
 *   - A negative cycle is identified if the total sum of weights in a cycle is negative.
 *   - For instance, for the cycle 0 → 1 → 2 → 0:
 *       - Sum: 4 + (-3) + (-4) = -3
 *   - Similarly, the cycle 1 → 2 → 0 → 1 gives:
 *       - Sum: (-3) + (-4) + 4 = -3
 *
 *   After executing the algorithm, if any vertex has a negative value on the diagonal
 *   (i.e., grid[i][i] < 0), then a negative cycle exists.
 *
 *     +------+------+------+
 *   0 |  -3  |      |      |
 *     +------+------+------+
 *   1 |      |  -3  |      |
 *     +------+------+------+
 *   2 |      |      |  -3  |
 *     +------+------+------+
 *
 *   **Cycle Detection Check:**
 *
 *   ------------------------------------------------------
 *   for (int i = 0; i < n; i++) {
 *       if (grid[i][i] < 0) {
 *           return "Cycle is present";
 *       }
 *   }
 *   ------------------------------------------------------
 *
 * Summary:
 * --------
 * - **Purpose:** Computes the shortest paths between every pair of vertices.
 * - **Graph Type:** Works for both directed and undirected graphs.
 * - **Methodology:** Iteratively updates the distance matrix by considering each vertex
 *   as an intermediate node.
 * - **Time Complexity:** O(n³)
 * - **Extra Feature:** Detects negative weight cycles.
 */

// GfG Link: https://www.geeksforgeeks.org/problems/implementing-floyd-warshall2042/1

/*
 * Floyd Warshall
 *
 * Difficulty: Medium Accuracy: 32.89% Submissions: 182K+ Points: 4 Average Time: 15m
 *
 * You are given an weighted directed graph, represented by an adjacency matrix, dist[][] of size n x n, where dist[i][j] represents the weight of the edge from node i to node j. If there is no direct edge, dist[i][j] is set to a large value (i.e., 108) to represent infinity.
 * The graph may contain negative edge weights, but it does not contain any negative weight cycles.
 *
 * Your task is to find the shortest distance between every pair of nodes i and j in the graph.
 *
 * Note: Modify the distances for every pair in place.
 *
 * Examples :
 *
 * Input: dist[][] = [[0, 4, 108, 5, 108], [108, 0, 1, 108, 6], [2, 108, 0, 3, 108], [108, 108, 1, 0, 2], [1, 108, 108, 4, 0]]
 * Output: [[0, 4, 5, 5, 7], [3, 0, 1, 4, 6], [2, 6, 0, 3, 5], [3, 7, 1, 0, 2], [1, 5, 5, 4, 0]]
 * Explanation: Each cell dist[i][j] in the output shows the shortest distance from node i to node j, computed by considering all possible intermediate nodes.
 *
 * Input: dist[][] = [[0, -1, 2], [1, 0, 108], [3, 1, 0]]
 * Output: [[0, -1, 2], [1, 0, 3], [2, 1, 0]]
 * Explanation: Each cell dist[i][j] in the output shows the shortest distance from node i to node j, computed by considering all possible intermediate nodes.
 * From 2 to 0 shortest distance should be 2 by following path 2 -> 1 -> 0
 * From 1 to 2 shortest distance should be 3 by following path 1 -> 0 -> 2
 *
 * Constraints:
 * 1 ≤ dist.size() ≤ 100
 * -1000 ≤ dist[i][j] ≤ 1000
 */

/************************************************************ C++ ************************************************/

// Approach: Use the Floyd Warshall algorithm to compute the shortest path between every pair of vertices by iteratively updating the distance matrix.
// Time Complexity: O(n³) - Three nested loops over n vertices each.
// Space Complexity: O(1) - The algorithm updates the given grid in-place without using extra space.
class Solution {
public:
    void floydWarshall(vector<vector<int> >& grid) {
        int n = grid.size();

        // Iterate through all vertices as an intermediate "via" node.
        for (int via = 0; via < n; via++) {
            // For each possible starting vertex i.
            for (int i = 0; i < n; i++) {
                // For each possible destination vertex j.
                for (int j = 0; j < n; j++) {
                    // Check if the path from i -> via and via -> j is valid (i.e., not equal to the "infinity" value 1e8).
                    if (grid[i][via] != 1e8 && grid[via][j] != 1e8) {
                        // Update the minimum distance from vertex i to j.
                        grid[i][j] = min(grid[i][j], grid[i][via] + grid[via][j]);
                    }
                }
            }
        }
    }
};

/*
 *
 * Dry Run:
 *
 * Consider the following 3x3 grid (n = 3) where 1e8 represents infinity (no direct path):
 *    [  0,       3,    1e8 ]
 *    [ 1e8,      0,      1   ]
 *    [  2,     1e8,      0   ]
 *
 * Iteration with via = 0:
 *   - For i = 2, j = 1:
 *       grid[2][0] = 2 and grid[0][1] = 3 => possible new distance = 2 + 3 = 5.
 *       Since 5 < grid[2][1] (which is 1e8), update grid[2][1] = 5.
 *
 * Grid after via = 0 becomes:
 *    [  0,       3,    1e8 ]
 *    [ 1e8,      0,      1   ]
 *    [  2,       5,      0   ]
 *
 * Iteration with via = 1:
 *   - For i = 0, j = 2:
 *       grid[0][1] = 3 and grid[1][2] = 1 => possible new distance = 3 + 1 = 4.
 *       Since 4 < grid[0][2] (which is 1e8), update grid[0][2] = 4.
 *
 * Grid after via = 1 becomes:
 *    [  0,       3,      4 ]
 *    [ 1e8,      0,      1 ]
 *    [  2,       5,      0 ]
 *
 * Iteration with via = 2:
 *   - For i = 0, j = 1:
 *       grid[0][2] = 4 and grid[2][1] = 5 => possible new distance = 4 + 5 = 9.
 *       Since 9 is not < grid[0][1] (which is 3), no update is made.
 *
 * Final grid after all iterations:
 *    [  0,       3,      4 ]
 *    [ 1e8,      0,      1 ]
 *    [  2,       5,      0 ]
 *
 */

/************************************************************ JAVA ************************************************/

// Approach: Use the Floyd Warshall algorithm to update the distance matrix for all-pairs shortest paths by considering each vertex as an intermediate.
// Time Complexity: O(n³) - Three nested loops over n vertices each.
// Space Complexity: O(1) - In-place modification of the input grid.
class Solution {
    public void floydWarshall(int[][] grid) {
        int n = grid.length;  // n represents the number of vertices in the grid

        // Iterate through each vertex to use as an intermediate "via" node.
        for (int via = 0; via < n; via++) {
            // For each source vertex i:
            for (int i = 0; i < n; i++) {
                // For each destination vertex j:
                for (int j = 0; j < n; j++) {
                    // Check if the path from i to "via" and "via" to j is valid (not set as infinity, e.g., 100000000).
                    if (grid[i][via] != 100000000 && grid[via][j] != 100000000) {
                        // Update the shortest distance from i to j by considering the intermediate vertex "via".
                        grid[i][j] = Math.min(grid[i][j], grid[i][via] + grid[via][j]);
                    }
                }
            }
        }
    }
}

/*
 *
 * Dry Run:
 *
 * Consider an initial 3x3 grid (n = 3) with 100000000 representing infinity:
 *
 *     [ 0,         3,   100000000 ]
 *     [ 100000000,   0,   1         ]
 *     [ 2,   100000000,   0         ]
 *
 * Iteration with via = 0:
 *   - Check i = 2, j = 1:
 *       grid[2][0] = 2 and grid[0][1] = 3.
 *       Potential new distance = 2 + 3 = 5.
 *       Since 5 < 100000000 (current grid[2][1]), update grid[2][1] = 5.
 *
 * Grid after via = 0:
 *     [ 0,         3,   100000000 ]
 *     [ 100000000,   0,   1         ]
 *     [ 2,         5,    0         ]
 *
 * Iteration with via = 1:
 *   - Check i = 0, j = 2:
 *       grid[0][1] = 3 and grid[1][2] = 1.
 *       Potential new distance = 3 + 1 = 4.
 *       Since 4 < 100000000 (current grid[0][2]), update grid[0][2] = 4.
 *
 * Grid after via = 1:
 *     [ 0,    3,   4 ]
 *     [ 100000000,   0,   1 ]
 *     [ 2,    5,   0 ]
 *
 * Iteration with via = 2:
 *   - Check i = 0, j = 1:
 *       grid[0][2] = 4 and grid[2][1] = 5.
 *       Potential new distance = 4 + 5 = 9.
 *       Since 9 > grid[0][1] (which is 3), no update is made.
 *
 * Final grid after all iterations:
 *     [ 0,    3,   4 ]
 *     [ 100000000,   0,   1 ]
 *     [ 2,    5,   0 ]
 */
