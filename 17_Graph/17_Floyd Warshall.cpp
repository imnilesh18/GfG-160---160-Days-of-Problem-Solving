Floyd Warshall Algorithm

Multi source shortest path algorithm

Dijistra and bellman ford were like one source one destination were given and then find the shortest path between them

But in Floyd Warshall Algorithm:
Find shorteest distances between every pair of vertices in a given edge-weighted directed graph

Why directed??
It can be undirected also 
if undirected like 
      5
0 ---------  1

it can also be drawn like
      5 
0 ---------> 1
  <---------    
      5       

                   8 
               ←────────── 
          0                1
        │  ↑  ↖ ─────────→  
        │  │    \   3      │
        │  │      \        │
     7  │  │ 2      \ 5    │  2
        │  │         \     │  
        │  │           \   │ 
        ↓  │             \ ↓
          3   ←──────────  2
                   1

            
        So now, 
        V = 0, 1 , 2, 3
              8
        1 ─────────→ 0
             
                via(through)
        1 ─────────→ k ─────────→ 0
          
             2            5
        1 ─────────→ 2 ─────────→ 0   = 7 (which is less than 8)

                    


                   8 
               ←────────── 
          0                1
        │  ↑  ↖ ─────────→  
        │  │    \   3      │
        │  │      \        │
     7  │  │ 2      \ 5    │  2
        │  │         \     │  
        │  │           \   │ 
        ↓  │             \ ↓
          3   ←──────────  2
                   1

        Matrix Representation:

                     Columns
                0      1     2      3
            +------+------+------+------+
          0 |  0   |  3   |  ∞   |  7   |
            +------+------+------+------+
          1 |  8   |  0   |  2   |  ∞   |
            +------+------+------+------+
          2 |  5   |  ∞   |  0   |  1   |
            +------+------+------+------+
          3 |  2   |  ∞   |  ∞   |  0   |
            +------+------+------+------+ 

            Now from here if somone asks
            what is the minimum distance from 2 ─────────→ 3
            directly return vec[2][3] (now the thing is fill this matrix correctly)


                                 via 0              │  via 1  │  via 2  │    via 3
            ─────────────────────────────────────────────────────────────────────── 
            [0][1] = 3  │ 0 ─→ 0 ─→ 1 = 0 + 3 = 3   │  
            [0][2] = ∞  │ 0 ─→ 0 ─→ 2 = 0 + ∞ = ∞   │
            [0][3] = 7  │ 0 ─→ 0 ─→ 3 = 0 + 7 = 7   │
                        │                           │
            [1][0] = 8  │ 1 ─→ 0 ─→ 0 = 8 + 0 = 8   │
            [1][2] = 2  │ 1 ─→ 0 ─→ 2 = 8 + ∞ = ∞   │
            [1][3] = ∞  │ 1 ─→ 0 ─→ 3 = 8 + 7 = 15  │
                        │                           │
            [2][0] = 5  │ 2 ─→ 0 ─→ 0 = 5 + 0 = 5   │
            [2][1] = ∞  │ 2 ─→ 0 ─→ 1 = 5 + 3 = 8   │
            [2][3] = 1  │ 2 ─→ 0 ─→ 3 = 5 + 7 = 12  │
                        │                           │
            [3][0] = 2  │ 3 ─→ 0 ─→ 0 = 2 + 0 = 2   │
            [3][1] = ∞  │ 3 ─→ 0 ─→ 1 = 2 + 3 = 5   │
            [3][2] = ∞  │ 3 ─→ 0 ─→ 2 = 2 + ∞ = ∞   │

            now our few values got updated
            [1][3] = ∞ became [1][3] = 15
            [2][1] = ∞ became [2][1] = 8
            [3][1] = ∞ became [3][1] = 5

            hence our matrix will update

            similarly do for via 1, via 2, via 3
            and update the matrix
            and at the end final matrix will contain the final answer to any node


            via each vertex
            for(int via = 0; v < n; via++) {

                for(int i = 0; i < r; i++) {
                    for(int j = 0; j < c; j++) {
                        grid[i][j] = min(grid[i][j], grid[i][via] + grid[via][j]);
                    }
                }
            }

            return grid;  
            T.C: O(n³)


It can detect negative cycles as well


       4
   0 ───────→ 1
    ↖        │
      \      │ 
       \     │   -3
 -4     \    │
         \   │  
          \  ↓  
            2  

                   Columns
            0      1     2      
        +------+------+------+ 
      0 |  0   |      |      | 
        +------+------+------+ 
      1 |      |  0   |      |  
        +------+------+------+
      2 |      |      |  0   |  
        +------+------+------+ 
  

before that what is negative cycle

find the sum of the weights 4 + (-3) + (-4) = -3 
the Resultant is negative hence it is negative cycle

    via 1
0 ─→ 1 ─→ 2 ─→ 0 = 4 - 3 - 4 = -3

    via 2
1 ─→ 2 ─→ 0 ─→ 1 = - 3 - 4  + 4 = -3


  +------+------+------+ 
0 |  -3  |      |      | 
  +------+------+------+ 
1 |      |  -3  |      |  
  +------+------+------+
2 |      |      |  -3  |  
  +------+------+------+ 

hence, we know from 0 to 0 ↺  it will be 0 but here it will become -3
therefore we can put a simple check that, 
for(int i = 0; i < n; i++) {
    if(grid[i][i] < 0) {
        return "cycle is present";
    }
}

/*
Floyd Warshall

Difficulty: Medium Accuracy: 32.89% Submissions: 182K+ Points: 4 Average Time: 15m

You are given an weighted directed graph, represented by an adjacency matrix, dist[][] of size n x n, where dist[i][j] represents the weight of the edge from node i to node j. If there is no direct edge, dist[i][j] is set to a large value (i.e., 108) to represent infinity.
The graph may contain negative edge weights, but it does not contain any negative weight cycles.

Your task is to find the shortest distance between every pair of nodes i and j in the graph.

Note: Modify the distances for every pair in place.

Examples :

Input: dist[][] = [[0, 4, 108, 5, 108], [108, 0, 1, 108, 6], [2, 108, 0, 3, 108], [108, 108, 1, 0, 2], [1, 108, 108, 4, 0]]
Output: [[0, 4, 5, 5, 7], [3, 0, 1, 4, 6], [2, 6, 0, 3, 5], [3, 7, 1, 0, 2], [1, 5, 5, 4, 0]]
Explanation: Each cell dist[i][j] in the output shows the shortest distance from node i to node j, computed by considering all possible intermediate nodes. 

Input: dist[][] = [[0, -1, 2], [1, 0, 108], [3, 1, 0]]
Output: [[0, -1, 2], [1, 0, 3], [2, 1, 0]]
Explanation: Each cell dist[i][j] in the output shows the shortest distance from node i to node j, computed by considering all possible intermediate nodes.
From 2 to 0 shortest distance should be 2 by following path 2 -> 1 -> 0
From 1 to 2 shortest distance should be 3 by following path 1 -> 0 -> 2

Constraints:
1 ≤ dist.size() ≤ 100
-1000 ≤ dist[i][j] ≤ 1000
*/


/************************************************************ C++ ************************************************/

// Approach: Use the Floyd Warshall algorithm to compute the shortest path between every pair of vertices by iteratively updating the distance matrix.
// Time Complexity: O(n³) - Three nested loops over n vertices each.
// Space Complexity: O(1) - The algorithm updates the given grid in-place without using extra space.
class Solution {
public:
    void floydWarshall(vector<vector<int>> &grid) {
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
*Dry Run:
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
*Dry Run:
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