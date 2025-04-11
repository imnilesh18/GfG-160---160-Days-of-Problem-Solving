/*
 * Dijkstra Algorithm
 *
 * Difficulty: Medium Accuracy: 50.83% Submissions: 212K+ Points: 4 Average Time: 25m
 *
 * Given an undirected, weighted graph with V vertices numbered from 0 to V-1 and E edges, represented by 2d array edges[][], where edges[i]=[u, v, w] represents the edge between the nodes u and v having w edge weight.
 * You have to find the shortest distance of all the vertices from the source vertex src, and return an array of integers where the ith element denotes the shortest distance between ith node and source vertex src.
 *
 * Note: The Graph is connected and doesn't contain any negative weight edge.
 *
 * Examples:
 *
 * Input: V = 3, edges[][] = [[0, 1, 1], [1, 2, 3], [0, 2, 6]], src = 2
 * Output: [4, 3, 0]
 * Explanation:
 * Shortest Paths:
 * For 2 to 0 minimum distance will be 4. By following path 2 -> 1 -> 0
 * For 2 to 1 minimum distance will be 3. By following path 2 -> 1
 * For 2 to 2 minimum distance will be 0. By following path 2 -> 2
 *
 * Input: V = 5, edges[][] = [[0, 1, 4], [0, 2, 8], [1, 4, 6], [2, 3, 2], [3, 4, 10]], src = 0
 * Output: [0, 4, 8, 10, 10]
 * Explanation:
 * Shortest Paths:
 * For 0 to 1 minimum distance will be 4. By following path 0 -> 1
 * For 0 to 2 minimum distance will be 8. By following path 0 -> 2
 * For 0 to 3 minimum distance will be 10. By following path 0 -> 2 -> 3
 * For 0 to 4 minimum distance will be 10. By following path 0 -> 1 -> 4
 *
 * Constraints:
 * 1 ≤ V ≤ 10^5
 * 1 ≤ E = edges.size() ≤ 10^5
 * 0 ≤ edges[i][j] ≤ 10^4
 * 0 ≤ src < V
 */

//---------------------------------------------------------------------------------------------------------------------------------------------------

/*
 * Dijkstra 's Algorithm
 *
 * input:
 *              0
 *             /  \
 *          1 /    \  6
 *           /      \
 *          1--------2   source
 *              3
 *
 * Explanation:
 * - This is the graph on which we run Dijkstra's algorithm.
 *-The nodes are labeled 0, 1, and 2. The source node is marked as "source".
 *-The edge weights are given on the edges.
 *
 * output: { 4, 3, 0 }
 *
 * Explanation:
 *-Dijkstra 's Algorithm gives the minimum distance from the source node to all the other nodes.
 * - For node 2, the resulting minimum distances to nodes 0, 1, and 3 are {4, 3, 0}.
 *
 * For node 2 to:  0, 1, 3
 *                {4, 3, 0}
 *
 * (Reiterated diagram for clarity)
 *
 *              0
 *             /  \
 *          1 /    \  6
 *           /      \
 *          1--------2   source
 *              3
 *
 * adj:
 * 2 -> {0, 6}, {1, 3}
 * 1 -> {2, 3}, {0, 1}
 * 0 -> {1, 1}, {2, 6}
 *
 * Explanation:
 * - The above adjacency list represents the graph:
 *   • For node 2, the neighbors are node 0 with edge weight 6 and node 1 with edge weight 3.
 *   • For node 1, the neighbors are node 2 with edge weight 3 and node 0 with edge weight 1.
 *   • For node 0, the neighbors are node 1 with edge weight 1 and node 2 with edge weight 6.
 *
 * For node 2 to:  0, 1, 3
 *                {4, 3, 0}
 *
 * Explanation:
 * - This line reiterates that from the source (node 2 in this case) the computed minimum distances
 *   are 4, 3, and 0, respectively.
 *
 * _______________________________________________________
 *
 *                0
 *               /  \
 *            1 /    \  6
 *             /      \
 *            1--------2   source
 *                3
 *
 *    adj:
 *    2 -> {0, 6}, {1, 3}
 *    1 -> {2, 3}, {0, 1}
 *    0 -> {1, 1}, {2, 6}
 *
 * Explanation:
 * - The graph is depicted again along with its adjacency list.
 *
 *  Result Array:
 *  +-----+-----+-----+
 *  |  0  |  1  |  2  |
 *  +-----+-----+-----+
 *  |  ∞  |  ∞  |  ∞  |
 *  +-----+-----+-----+
 *
 * Explanation:
 * - Initially, the distance (result) array is set to infinity (∞) for all nodes, meaning the minimum
 *   distance from the source to each node is unknown and assumed infinitely large.
 *
 *    |            |
 *    |            |
 *    |            |
 *    |            |
 *    |            |
 *    |            |
 *    |____________|
 *      min_heap
 *
 * Explanation:
 * - The min heap (or priority queue) is shown here as empty at the beginning.
 *
 * Now, we know result[source] = 0.
 * So,
 *
 *  Result Array:
 *  +-----+-----+-----+
 *  |  0  |  1  |  2  |
 *  +-----+-----+-----+
 *  |  ∞  |  ∞  |  0  |
 *  +-----+-----+-----+
 *
 * Explanation:
 * - We update the distance for the source node (node 2) to 0.
 *
 * So, push {0, 2}.
 *
 *    |            |
 *    |            |
 *    |            |
 *    |            |
 *    |------------|         {0, 2} -> {distance, node}
 *    |   {0, 2}   |
 *    |____________|
 *      min_heap
 *
 * Explanation:
 * - We push the tuple {0, 2} into the min heap, meaning node 2 has a current distance of 0.
 *
 * ----------------------------------------------
 * Now, pop it {0, 2}.
 *
 *    |            |
 *    |            |
 *    |            |
 *    |            |
 *    |            |
 *    |            |
 *    |____________|
 *      min_heap
 *
 * Explanation:
 * - We now pop the smallest element from the min heap, which is {0, 2}.
 *
 * Pop = {0, 2}
 * dist = 0
 * node = 2
 *
 * Explanation:
 * - The popped element indicates that the distance to node 2 is 0.
 *
 * Now check from 2 where we can go.
 * adj:
 * 2 -> {0, 6}, {1, 3}
 * 1 -> {2, 3}, {0, 1}
 * 0 -> {1, 1}, {2, 6}
 *
 * Explanation:
 * - For node 2, based on the adjacency list, its neighbors are:
 *   • Node 0 with weight 6.
 *   • Node 1 with weight 3.
 *
 * Neighbor = 0
 * dist = 6
 *
 *                0
 *               /  \
 *            1 /    \  6
 *             /      \
 *            1--------2   source
 *                3
 *
 * So,
 * - From node 2 to itself is 0.
 * - Then from node 2 to node 0, the total distance would be 0 + 6 = 6.
 *
 * It is better than ∞, so update the result array for node 0 to 6,
 * and push it into the min heap {6, 0}.
 *
 *  Result Array:
 *  +-----+-----+-----+
 *  |  0  |  1  |  2  |
 *  +-----+-----+-----+
 *  |  6  |  ∞  |  0  |
 *  +-----+-----+-----+
 *
 *    |            |
 *    |            |
 *    |            |
 *    |            |
 *    |------------|         {6, 0} -> {distance, node}
 *    |   {6, 0}   |
 *    |____________|
 *      min_heap
 *
 * Explanation:
 * - The result array is updated with a distance of 6 for node 0.
 * - We push {6, 0} into the min heap as a candidate path.
 *
 * (Note: At this point, we again observe the popped element {0, 2} with dist = 0, node = 2.)
 *
 * Pop = {0, 2}
 * dist = 0
 * node = 2
 *
 * Now check from 2 for other neighbors.
 *    adj:
 *    2 -> {0, 6}, {1, 3}
 *    1 -> {2, 3}, {0, 1}
 *    0 -> {1, 1}, {2, 6}
 *
 * From 2, neighbor = 1 with dist = 3.
 *
 *                0
 *               /  \
 *            1 /    \  6
 *             /      \
 *            1--------2   source
 *                3
 *
 * So,
 * - From node 2 to itself is 0.
 * - Then from node 2 to node 1, the total distance is 0 + 3 = 3.
 *
 * It is better than ∞, so update the result array for node 1 to 3,
 * and push it into the min heap {3, 1}.
 *
 *  Result Array:
 *  +-----+-----+-----+
 *  |  0  |  1  |  2  |
 *  +-----+-----+-----+
 *  |  6  |  3  |  0  |
 *  +-----+-----+-----+
 *
 *    |            |
 *    |            |
 *    |------------|
 *    |   {3, 1}   |         {3, 1} -> {distance, node}
 *    |------------|         {6, 0} -> {distance, node}
 *    |   {6, 0}   |
 *    |____________|
 *      min_heap
 *
 * Explanation:
 * - The result array now has updated distances: node 0 → 6, node 1 → 3, node 2 → 0.
 * - The min heap now contains {3, 1} and {6, 0}.
 *
 * Again, checking the adjacencies from node 2, we have explored all its neighbors.
 *    adj:
 *    2 -> {0, 6}, {1, 3}
 *    1 -> {2, 3}, {0, 1}
 *    0 -> {1, 1}, {2, 6}
 *
 * --------------------------------------------------------
 *
 * Now, pop the next element {3, 1} from the min heap.
 *
 *    |            |
 *    |            |
 *    |            |
 *    |            |
 *    |------------|         {6, 0} -> {distance, node}
 *    |   {6, 0}   |
 *    |____________|
 *      min_heap
 *
 * Pop = {3, 1}
 * dist = 3
 * node = 1
 *
 * Now check from node 1 where we can go.
 * adj:
 * 2 -> {0, 6}, {1, 3}
 * 1 -> {2, 3}, {0, 1}
 * 0 -> {1, 1}, {2, 6}
 *
 * Explanation:
 * - For node 1, its neighbors are node 2 with weight 3 and node 0 with weight 1.
 *
 * For neighbor = 2, dist = 3.
 *
 *                0
 *               /  \
 *            1 /    \  6
 *             /      \
 *            1--------2   source
 *                3
 *
 * So,
 * - From node 2 to node 1 the distance is 3.
 * - Then from node 1 to node 2 the total would be 3 + 3 = 6.
 *
 * It is not better than the current best for node 2 (which is 0), so do not update.
 *
 * Result Array remains:
 *  +-----+-----+-----+
 *  |  0  |  1  |  2  |
 *  +-----+-----+-----+
 *  |  6  |  3  |  0  |
 *  +-----+-----+-----+
 *
 * And min heap still contains {6, 0}.
 *
 * Now, from node 1 check the other neighbor.
 *
 * Pop = {3, 1}
 * dist = 3
 * node = 1
 *
 * adj:
 * 2 -> {0, 6}, {1, 3}
 * 1 -> {2, 3}, {0, 1}
 * 0 -> {1, 1}, {2, 6}
 *
 * For neighbor = 0, dist = 1.
 *
 *                0
 *               /  \
 *            1 /    \  6
 *             /      \
 *            1--------2   source
 *                3
 *
 * So,
 * - From node 2 to node 1 is 3.
 * - Then from node 1 to node 0 is 3 + 1 = 4.
 *
 * It is better than the current best for node 0 (6), so update the result array for node 0 to 4.
 * And push {4, 0} into the min heap.
 *
 *  Result Array:
 *  +-----+-----+-----+
 *  |  0  |  1  |  2  |
 *  +-----+-----+-----+
 *  |  4  |  3  |  0  |
 *  +-----+-----+-----+
 *
 *    |            |
 *    |            |
 *    |------------|
 *    |   {4, 0}   |         {4, 0} -> {distance, node}
 *    |------------|         {6, 0} -> {distance, node}
 *    |   {6, 0}   |
 *    |____________|
 *      min_heap
 *
 * Explanation:
 * - The result array is now updated with node 0 having distance 4.
 * - The min heap now has both {4, 0} and the older {6, 0}; when {6, 0} is later popped, it will be ignored if node 0 is already settled.
 *
 * Again, checking adjacencies from node 1, we have explored all its neighbors.
 * adj:
 * 2 -> {0, 6}, {1, 3}
 * 1 -> {2, 3}, {0, 1}
 * 0 -> {1, 1}, {2, 6}
 *
 * --------------------------------------------------------
 *
 * Now, pop the next element {4, 0} from the min heap.
 *
 *    |            |
 *    |            |
 *    |            |
 *    |            |
 *    |------------|         {6, 0} -> {distance, node}
 *    |   {6, 0}   |
 *    |____________|
 *      min_heap
 *
 * Pop = {4, 0}
 * dist = 4
 * node = 0
 *
 * Now check from node 0 where we can go.
 * adj:
 * 2 -> {0, 6}, {1, 3}
 * 1 -> {2, 3}, {0, 1}
 * 0 -> {1, 1}, {2, 6}
 *
 * For neighbor = 1, dist = 1.
 *
 *                0
 *               /  \
 *            1 /    \  6
 *             /      \
 *            1--------2   source
 *                3
 *
 * So,
 * - From node 2 to node 0 we have 4,
 * - Then from node 0 to node 1 is 4 + 1 = 5.
 *
 * It is not better than the current best for node 1 (3), so do not update.
 *
 * Result Array remains:
 *  +-----+-----+-----+
 *  |  0  |  1  |  2  |
 *  +-----+-----+-----+
 *  |  4  |  3  |  0  |
 *  +-----+-----+-----+
 *
 * Pop = {4, 0}
 * dist = 4
 * node = 0
 *
 * adj:
 * 2 -> {0, 6}, {1, 3}
 * 1 -> {2, 3}, {0, 1}
 * 0 -> {1, 1}, {2, 6}
 *
 * Also check neighbor = 2, dist = 6.
 *
 *                0
 *               /  \
 *            1 /    \  6
 *             /      \
 *            1--------2   source
 *                3
 *
 * Total from node 0: 4 + 6 = 10, not better than the current best for node 2 (0).
 *
 * Result Array remains unchanged.
 *  +-----+-----+-----+
 *  |  0  |  1  |  2  |
 *  +-----+-----+-----+
 *  |  4  |  3  |  0  |
 *  +-----+-----+-----+
 *
 * The min heap still holds {6, 0} from earlier.
 *
 *    |            |
 *    |            |
 *    |            |
 *    |            |
 *    |------------|         {6, 0} -> {distance, node}
 *    |   {6, 0}   |
 *    |____________|
 *      min_heap
 *
 * -------------------------------------------------
 *
 * Now, pop {6, 0} from the min heap.
 *
 *    |            |
 *    |            |
 *    |            |
 *    |            |
 *    |            |
 *    |            |
 *    |____________|
 *      min_heap
 *
 * Pop = {6, 0}
 * dist = 6
 * node = 0
 *
 * Check from node 0:
 * adj:
 * 2 -> {0, 6}, {1, 3}
 * 1 -> {2, 3}, {0, 1}
 * 0 -> {1, 1}, {2, 6}
 *
 * For neighbor = 1, dist = 1.
 *
 *                0
 *               /  \
 *            1 /    \  6
 *             /      \
 *            1--------2   source
 *                3
 *
 * Total from node 0: 6 + 1 = 7, not better than current best for node 1 (3).
 *
 * So, do not update.
 *
 * Result Array remains:
 *  +-----+-----+-----+
 *  |  0  |  1  |  2  |
 *  +-----+-----+-----+
 *  |  4  |  3  |  0  |
 *  +-----+-----+-----+
 *
 * Pop = {6, 0}
 * dist = 6
 * node = 0
 *
 * Also, check neighbor = 2, dist = 6.
 * adj:
 * 2 -> {0, 6}, {1, 3}
 * 1 -> {2, 3}, {0, 1}
 * 0 -> {1, 1}, {2, 6}
 *
 *                0
 *               /  \
 *            1 /    \  6
 *             /      \
 *            1--------2   source
 *                3
 *
 * Total: 6 + 6 = 12, not better than current best for node 2 (0).
 *
 * Result Array remains unchanged.
 *  +-----+-----+-----+
 *  |  0  |  1  |  2  |
 *  +-----+-----+-----+
 *  |  4  |  3  |  0  |
 *  +-----+-----+-----+
 *
 * The min heap is now empty.
 *    |            |
 *    |            |
 *    |            |
 *    |            |
 *    |            |
 *    |            |
 *    |____________|
 *      min_heap
 *
 * ----------------------------------------------------
 *
 * Final Result Array:
 *  +-----+-----+-----+
 *  |  0  |  1  |  2  |
 *  +-----+-----+-----+
 *  |  4  |  3  |  0  |
 *  +-----+-----+-----+
 *
 * Hence, this is the final answer.
 *
 * Explanation:
 * - The priority queue (min heap) ensures that at each step we get the node with the smallest temporary distance.
 * - We update the result array (which holds the minimum distances from the source) only if a shorter path is found.
 * - In this example, the final minimum distances from the source (node 2) to nodes 0, 1, 3 are {4, 3, 0} respectively.
 *
 * Why use a priority queue?
 * - The priority queue (min heap) gives the shortest path at the top.
 * - This allows us to always process the node with the current smallest known distance,
 *   ensuring an efficient and optimal solution as outlined by Dijkstra's algorithm.
 */

//---------------------------------------------------------------------------------------------------------------------------------------------------

/************************************************************ C++ ************************************************/

// Approach: Use Dijkstra's algorithm to compute the shortest distance from the source to all other vertices in a weighted graph using a priority queue.
// Time Complexity: O(E log V) where E is the number of edges and V is the number of vertices.
// Space Complexity: O(V + E) for storing the adjacency list and the result array.
class Solution {
public:
    // Function that returns the shortest distance from 'source' to every other vertex in the graph.
    vector<int> dijkstra(int V, vector<vector<int>>& edges, int source) {
        // Build the adjacency list: for each edge, add both directions for an undirected graph.
        unordered_map<int, vector<pair<int, int>>> adj;

        for (auto& e : edges) {
            int u = e[0];               // starting vertex of the edge
            int v = e[1];               // ending vertex of the edge
            int w = e[2];               // edge weight
            adj[u].push_back({ v, w });
            adj[v].push_back({ u, w }); // Omit this line if the graph is directed
        }

        // Priority queue stores pairs {distance, node} and orders by smallest distance first.
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;

        // Initialize result array with INF for all vertices.
        vector<int> result(V, INT_MAX);

        // Distance from source to itself is 0.
        result[source] = 0;
        pq.push({ 0, source });

        // Process the graph: while there are vertices to process in the priority queue.
        while (!pq.empty()) {
            int d    = pq.top().first;  // current shortest distance for this node
            int node = pq.top().second; // current node
            pq.pop();

            // Check all adjacent nodes of the current node.
            for (auto& vec : adj[node]) {
                int adjNode = vec.first;     // neighbor node
                int wt      = vec.second;    // weight of edge from current node to neighbor

                // If the distance to neighbor through current node is shorter, update and push into PQ.
                if (d + wt < result[adjNode]) {
                    result[adjNode] = d + wt;
                    pq.push({ d + wt, adjNode });
                }
            }
        }

        // Return the computed shortest distances from source to all vertices.
        return result;
    }
};

/*
 *
 * Dry Run
 *
 * Example:
 * V = 3, edges = [ [0, 1, 5], [1, 2, 3], [0, 2, 1] ], source = 0
 *
 * Graph Visual Representation:
 *         (0)
 *         / \
 *    5   /   \  1
 *       /     \
 *     (1)----- (2)
 *           3
 *
 * Explanation:
 * 1. Build adjacency list:
 *    adj[0] = { {1, 5}, {2, 1} }
 *    adj[1] = { {0, 5}, {2, 3} }
 *    adj[2] = { {1, 3}, {0, 1} }
 *
 * 2. Initialize:
 *    result = [0, ∞, ∞] (distance from source 0 to 0 is 0, others are ∞)
 *    Priority queue (pq): { {0, 0} }
 *
 * 3. Iteration 1:
 *    - Pop from pq: {0, 0}  (d = 0, node = 0)
 *    - For each neighbor of node 0:
 *         * Neighbor 1 with weight 5:
 *              new distance = 0 + 5 = 5, update result[1] from ∞ to 5.
 *              Push {5, 1} into pq.
 *         * Neighbor 2 with weight 1:
 *              new distance = 0 + 1 = 1, update result[2] from ∞ to 1.
 *              Push {1, 2} into pq.
 *    - Now, result = [0, 5, 1]
 *    - pq now has: { {1, 2}, {5, 1} } (min-heap orders by smallest distance first)
 *
 * 4. Iteration 2:
 *    - Pop from pq: {1, 2} (d = 1, node = 2)
 *    - For each neighbor of node 2:
 *         * Neighbor 1 with weight 3:
 *              new distance = 1 + 3 = 4, which is less than result[1] (currently 5).
 *              Update result[1] = 4.
 *              Push {4, 1} into pq.
 *         * Neighbor 0 with weight 1:
 *              new distance = 1 + 1 = 2, but result[0] is already 0, so no update.
 *    - Now, result = [0, 4, 1]
 *    - pq now has: { {4, 1}, {5, 1} }
 *
 * 5. Iteration 3:
 *    - Pop from pq: {4, 1} (d = 4, node = 1)
 *    - For each neighbor of node 1:
 *         * Neighbor 0 with weight 5:
 *              new distance = 4 + 5 = 9, not better than result[0] = 0.
 *         * Neighbor 2 with weight 3:
 *              new distance = 4 + 3 = 7, not better than result[2] = 1.
 *    - No updates; result remains: [0, 4, 1]
 *    - pq still has: { {5, 1} }
 *
 * 6. Iteration 4:
 *    - Pop from pq: {5, 1} (d = 5, node = 1)
 *    - Node 1 is already processed (result[1] = 4 is smaller), so skip.
 *    - pq is now empty.
 *
 * Final Output:
 *    result = [0, 4, 1]
 *
 * This means:
 * - The shortest distance from node 0 to node 0 is 0.
 * - The shortest distance from node 0 to node 1 is 4.
 * - The shortest distance from node 0 to node 2 is 1.
 *
 * Dijkstra's algorithm thus gives us the minimum distances from the source to all other nodes.
 */

/************************************************************ JAVA ************************************************/

// Approach: Use Dijkstra's algorithm to compute the shortest distances from the source vertex to all other vertices
// by building an adjacency list from the edges and then processing nodes using a min-heap (priority queue).
// Time Complexity: O(E log V), where E is the number of edges and V is the number of vertices.
// Space Complexity: O(V + E) for the adjacency list, result array, and the priority queue.
class Solution {
    public int[] dijkstra(int V, int[][] edges, int source) {
        // Build the adjacency list.
        // 'adj' maps a vertex to a list of pairs {neighbor, weight}.
        List<List<int[]>> adj = new ArrayList<>();

        for (int i = 0; i < V; i++) {
            adj.add(new ArrayList<>());
        }

        // For each edge, add both directions (since the graph is undirected).
        for (int[] e : edges) {
            int u = e[0];                      // starting vertex of the edge
            int v = e[1];                      // ending vertex of the edge
            int w = e[2];                      // weight of the edge
            adj.get(u).add(new int[]{ v, w });
            adj.get(v).add(new int[]{ u, w }); // omit this line if the graph is directed
        }

        // Priority queue to store pairs {distance, node} in ascending order of distance.
        PriorityQueue<int[]> pq = new PriorityQueue<>((a, b)->a[0] - b[0]);

        // Create and initialize the result array with infinity.
        int[] result = new int[V];
        Arrays.fill(result, Integer.MAX_VALUE);

        // Distance from the source to itself is 0.
        result[source] = 0;
        pq.offer(new int[]{ 0, source });  // Push {0, source} into the priority queue.

        // Process the priority queue until it is empty.
        while (!pq.isEmpty()) {
            // Get the current smallest distance and corresponding node.
            int d    = pq.peek()[0]; // Current distance
            int node = pq.peek()[1]; // Current node
            pq.poll();               // Remove the element with the smallest distance.

            // For each adjacent vertex (neighbor) of the current node.
            for (int[] vec : adj.get(node)) {
                int adjNode = vec[0];    // The neighbor node.
                int wt      = vec[1];    // The weight of the edge from 'node' to 'adjNode'.

                // If the newly calculated distance is smaller, update and push the neighbor.
                if (d + wt < result[adjNode]) {
                    result[adjNode] = d + wt;
                    pq.offer(new int[]{ result[adjNode], adjNode });
                }
            }
        }

        // Return the array of shortest distances from the source.
        return result;
    }
}

/*
 *
 * Dry Run
 *
 * Example:
 * V = 3, edges = [ [0, 1, 5], [1, 2, 3], [0, 2, 1] ], source = 0
 *
 * Graph Visual Representation:
 *         (0)
 *         / \
 *    5   /   \  1
 *       /     \
 *     (1)----- (2)
 *           3
 *
 * Step 1: Build the adjacency list:
 *    adj[0] = { {1,5}, {2,1} }
 *    adj[1] = { {0,5}, {2,3} }
 *    adj[2] = { {1,3}, {0,1} }
 *
 * Step 2: Initialization:
 *    - result = [0, ∞, ∞] because the source is 0.
 *    - Priority queue (pq): [{0, 0}]
 *
 * Step 3: Process the priority queue:
 *
 *   Iteration 1:
 *     - pq.peek() gives {0, 0} → d = 0, node = 0.
 *     - Pop {0, 0}. Now, process neighbors of node 0.
 *       • For neighbor 1 with weight 5: new distance = 0 + 5 = 5, update result[1] = 5, push {5, 1}.
 *       • For neighbor 2 with weight 1: new distance = 0 + 1 = 1, update result[2] = 1, push {1, 2}.
 *     - result = [0, 5, 1]
 *     - pq now contains: [{1, 2}, {5, 1}]
 *
 *   Iteration 2:
 *     - pq.peek() gives {1, 2} → d = 1, node = 2.
 *     - Pop {1, 2}. Process neighbors of node 2.
 *       • For neighbor 1 with weight 3: new distance = 1 + 3 = 4, which is less than result[1] (5), so update result[1] = 4, push {4, 1}.
 *       • For neighbor 0 with weight 1: new distance = 1 + 1 = 2, but result[0] is 0, so no update.
 *     - result becomes [0, 4, 1]
 *     - pq now contains: [{4, 1}, {5, 1}]
 *
 *   Iteration 3:
 *     - pq.peek() gives {4, 1} → d = 4, node = 1.
 *     - Pop {4, 1}. Process neighbors of node 1.
 *       • For neighbor 0 with weight 5: new distance = 4 + 5 = 9, but result[0] is 0, so no update.
 *       • For neighbor 2 with weight 3: new distance = 4 + 3 = 7, but result[2] is 1, so no update.
 *     - result remains [0, 4, 1].
 *     - pq still contains: [{5, 1}]
 *
 *   Iteration 4:
 *     - Pop {5, 1}. Now, since node 1 already has a better distance (4), ignore this element.
 *     - pq is now empty.
 *
 * Final result array: [0, 4, 1]
 *
 * Explanation:
 * - The shortest distance from node 0 to node 0 is 0.
 * - The shortest distance from node 0 to node 1 is 4.
 * - The shortest distance from node 0 to node 2 is 1.
 *
 * Dijkstra's algorithm therefore returns the minimum distances: [0, 4, 1].
 */
