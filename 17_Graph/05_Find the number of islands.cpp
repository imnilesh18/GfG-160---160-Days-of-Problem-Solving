/*
 * Find the number of islands
 *
 * Difficulty: Medium Accuracy: 42.12% Submissions: 233K+ Points: 4 Average Time: 20m
 *
 * Given a grid of size n*m (n is the number of rows and m is the number of columns in the grid) consisting of 'W's (Water) and 'L's (Land). Find the number of islands.
 *
 * Note: An island is either surrounded by water or the boundary of a grid and is formed by connecting adjacent lands horizontally or vertically or diagonally i.e., in all 8 directions.
 *
 * Examples:
 *
 * Input: grid[][] = [['L', 'L', 'W', 'W', 'W'], ['W', 'L', 'W', 'W', 'L'], ['L', 'W', 'W', 'L', 'L'], ['W', 'W', 'W', 'W', 'W'], ['L', 'W', 'L', 'L', 'W']]
 * Output: 4
 * Explanation:
 * The image below shows all the 4 islands in the grid.
 *
 * Input: grid[][] = [['W', 'L', 'L', 'L', 'W', 'W', 'W'], ['W', 'W', 'L', 'L', 'W', 'L', 'W']]
 * Output: 2
 * Expanation:
 * The image below shows 2 islands in the grid.
 *
 * Constraints:
 * 1 ≤ n, m ≤ 500
 * grid[i][j] = {'L', 'W'}
 */

/************************************************************ C++ ************************************************/

// Approach 1 (DFS): Use DFS to traverse each connected component (island) and mark visited land cells with '$' to avoid reprocessing.
// Time Complexity: O(n*m) where n is the number of rows and m is the number of columns, since each cell is processed once.
// Space Complexity: O(n*m) in the worst-case due to recursion stack in case the grid is filled with land.
class Solution {
public:
    // Depth First Search to mark all connected 'L' cells as visited ('$')
    void dfs(vector<vector<char>>& grid, int i, int j) {
        // If out of bounds or current cell is not land, return
        if (i < 0 || i >= grid.size() || j < 0 || j >= grid[0].size() || grid[i][j] != 'L') {
            return;
        }

        // Mark the current cell as visited
        grid[i][j] = '$';

        // Recursively visit all 8 neighboring cells
        // Vertical and Horizontal
        dfs(grid, i + 1, j);        // Down
        dfs(grid, i - 1, j);        // Up
        dfs(grid, i, j + 1);        // Right
        dfs(grid, i, j - 1);        // Left

        // Diagonals
        dfs(grid, i - 1, j - 1);        // Upper-Left
        dfs(grid, i - 1, j + 1);        // Upper-Right
        dfs(grid, i + 1, j - 1);        // Lower-Left
        dfs(grid, i + 1, j + 1);        // Lower-Right
    }
    // Function to count the number of islands in the grid
    int countIslands(vector<vector<char>>& grid) {
        int m = grid.size();
        int n = grid[0].size();

        int count = 0;

        // Iterate over every cell in the grid
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                // If the cell is land, it's part of an unvisited island
                if (grid[i][j] == 'L') {
                    dfs(grid, i, j);     // Mark the entire island as visited
                    count++;             // Increment island count
                }
            }
        }
        return count;
    }
};

/*
 *
 * Dry Run:
 * Example Input Grid:
 *           0      1      2     3      4
 *       +------+------+------+------+------+
 * Row0  |  L   |  L   |  W   |  W   |  W   |
 *       +------+------+------+------+------+
 * Row1  |  W   |  L   |  W   |  W   |  L   |
 *       +------+------+------+------+------+
 * Row2  |  L   |  W   |  W   |  L   |  L   |
 *       +------+------+------+------+------+
 * Row3  |  W   |  W   |  W   |  W   |  W   |
 *       +------+------+------+------+------+
 * Row4  |  L   |  W   |  L   |  L   |  W   |
 *       +------+------+------+------+------+
 *
 * Step 1: Start scanning grid. At (0,0) = 'L'
 *   - Call DFS(0,0) and mark (0,0) as '$'
 *   Updated Grid:
 *           0      1      2     3      4
 *       +------+------+------+------+------+
 * Row0  |  $   |  L   |  W   |  W   |  W   |
 *       +------+------+------+------+------+
 * Row1  |  W   |  L   |  W   |  W   |  L   |
 *       +------+------+------+------+------+
 * Row2  |  L   |  W   |  W   |  L   |  L   |
 *       +------+------+------+------+------+
 * Row3  |  W   |  W   |  W   |  W   |  W   |
 *       +------+------+------+------+------+
 * Row4  |  L   |  W   |  L   |  L   |  W   |
 *       +------+------+------+------+------+
 *
 * Step 2: From (0,0), DFS explores neighbor (0,1) = 'L'
 *   - Call DFS(0,1) and mark (0,1) as '$'
 *   Updated Grid:
 *           0      1      2     3      4
 *       +------+------+------+------+------+
 * Row0  |  $   |  $   |  W   |  W   |  W   |
 *       +------+------+------+------+------+
 * Row1  |  W   |  L   |  W   |  W   |  L   |
 *       +------+------+------+------+------+
 * Row2  |  L   |  W   |  W   |  L   |  L   |
 *       +------+------+------+------+------+
 * Row3  |  W   |  W   |  W   |  W   |  W   |
 *       +------+------+------+------+------+
 * Row4  |  L   |  W   |  L   |  L   |  W   |
 *       +------+------+------+------+------+
 *
 * Step 3: From (0,1), DFS explores neighbor (1,1) = 'L'
 *   - Call DFS(1,1) and mark (1,1) as '$'
 *   Updated Grid:
 *           0      1      2     3      4
 *       +------+------+------+------+------+
 * Row0  |  $   |  $   |  W   |  W   |  W   |
 *       +------+------+------+------+------+
 * Row1  |  W   |  $   |  W   |  W   |  L   |
 *       +------+------+------+------+------+
 * Row2  |  L   |  W   |  W   |  L   |  L   |
 *       +------+------+------+------+------+
 * Row3  |  W   |  W   |  W   |  W   |  W   |
 *       +------+------+------+------+------+
 * Row4  |  L   |  W   |  L   |  L   |  W   |
 *       +------+------+------+------+------+
 *
 * Step 4: From (1,1), DFS explores diagonal neighbor (2,0) = 'L'
 *   - Call DFS(2,0) and mark (2,0) as '$'
 *   Updated Grid:
 *           0      1      2     3      4
 *       +------+------+------+------+------+
 * Row0  |  $   |  $   |  W   |  W   |  W   |
 *       +------+------+------+------+------+
 * Row1  |  W   |  $   |  W   |  W   |  L   |
 *       +------+------+------+------+------+
 * Row2  |  $   |  W   |  W   |  L   |  L   |
 *       +------+------+------+------+------+
 * Row3  |  W   |  W   |  W   |  W   |  W   |
 *       +------+------+------+------+------+
 * Row4  |  L   |  W   |  L   |  L   |  W   |
 *       +------+------+------+------+------+
 *
 * Island 1 Completed. Island count becomes 1.
 *
 * Step 5: Continue scanning grid. Next unvisited 'L' is at (1,4)
 *   - Call DFS(1,4) and mark (1,4) as '$'
 *   Updated Grid:
 *           0      1      2     3      4
 *       +------+------+------+------+------+
 * Row0  |  $   |  $   |  W   |  W   |  W   |
 *       +------+------+------+------+------+
 * Row1  |  W   |  $   |  W   |  W   |  $   |
 *       +------+------+------+------+------+
 * Row2  |  $   |  W   |  W   |  L   |  L   |
 *       +------+------+------+------+------+
 * Row3  |  W   |  W   |  W   |  W   |  W   |
 *       +------+------+------+------+------+
 * Row4  |  L   |  W   |  L   |  L   |  W   |
 *       +------+------+------+------+------+
 *
 * Step 6: From (1,4), DFS explores neighbor (2,4) = 'L'
 *   - Call DFS(2,4) and mark (2,4) as '$'
 *   Updated Grid:
 *           0      1      2     3      4
 *       +------+------+------+------+------+
 * Row0  |  $   |  $   |  W   |  W   |  W   |
 *       +------+------+------+------+------+
 * Row1  |  W   |  $   |  W   |  W   |  $   |
 *       +------+------+------+------+------+
 * Row2  |  $   |  W   |  W   |  L   |  $   |
 *       +------+------+------+------+------+
 * Row3  |  W   |  W   |  W   |  W   |  W   |
 *       +------+------+------+------+------+
 * Row4  |  L   |  W   |  L   |  L   |  W   |
 *       +------+------+------+------+------+
 *
 * Step 7: From (2,4), DFS explores neighbor (2,3) = 'L'
 *   - Call DFS(2,3) and mark (2,3) as '$'
 *   Updated Grid:
 *           0      1      2     3      4
 *       +------+------+------+------+------+
 * Row0  |  $   |  $   |  W   |  W   |  W   |
 *       +------+------+------+------+------+
 * Row1  |  W   |  $   |  W   |  W   |  $   |
 *       +------+------+------+------+------+
 * Row2  |  $   |  W   |  W   |  $   |  $   |
 *       +------+------+------+------+------+
 * Row3  |  W   |  W   |  W   |  W   |  W   |
 *       +------+------+------+------+------+
 * Row4  |  L   |  W   |  L   |  L   |  W   |
 *       +------+------+------+------+------+
 *
 * Island 2 Completed. Island count becomes 2.
 *
 * Step 8: Continue scanning grid. Next unvisited 'L' is at (4,0)
 *   - Call DFS(4,0) and mark (4,0) as '$'
 *   Updated Grid:
 *           0      1      2     3      4
 *       +------+------+------+------+------+
 * Row0  |  $   |  $   |  W   |  W   |  W   |
 *       +------+------+------+------+------+
 * Row1  |  W   |  $   |  W   |  W   |  $   |
 *       +------+------+------+------+------+
 * Row2  |  $   |  W   |  W   |  $   |  $   |
 *       +------+------+------+------+------+
 * Row3  |  W   |  W   |  W   |  W   |  W   |
 *       +------+------+------+------+------+
 * Row4  |  $   |  W   |  L   |  L   |  W   |
 *       +------+------+------+------+------+
 *
 * Island 3 Completed. Island count becomes 3.
 *
 * Step 9: Continue scanning grid. Next unvisited 'L' is at (4,2)
 *   - Call DFS(4,2) and mark (4,2) as '$'
 *   Updated Grid:
 *           0      1      2     3      4
 *       +------+------+------+------+------+
 * Row0  |  $   |  $   |  W   |  W   |  W   |
 *       +------+------+------+------+------+
 * Row1  |  W   |  $   |  W   |  W   |  $   |
 *       +------+------+------+------+------+
 * Row2  |  $   |  W   |  W   |  $   |  $   |
 *       +------+------+------+------+------+
 * Row3  |  W   |  W   |  W   |  W   |  W   |
 *       +------+------+------+------+------+
 * Row4  |  $   |  W   |  $   |  L   |  W   |
 *       +------+------+------+------+------+
 *
 * Step 10: From (4,2), DFS explores neighbor (4,3) = 'L'
 *   - Call DFS(4,3) and mark (4,3) as '$'
 *   Updated Grid:
 *           0      1      2     3      4
 *       +------+------+------+------+------+
 * Row0  |  $   |  $   |  W   |  W   |  W   |
 *       +------+------+------+------+------+
 * Row1  |  W   |  $   |  W   |  W   |  $   |
 *       +------+------+------+------+------+
 * Row2  |  $   |  W   |  W   |  $   |  $   |
 *       +------+------+------+------+------+
 * Row3  |  W   |  W   |  W   |  W   |  W   |
 *       +------+------+------+------+------+
 * Row4  |  $   |  W   |  $   |  $   |  W   |
 *       +------+------+------+------+------+
 *
 * Island 4 Completed. Island count becomes 4.
 *
 * Final Island Count = 4.
 *
 */

//Approach-2 (BFS)
//T.C : O(m*n) - Every cell is processed once.
//S.C : O(m*n) - In worst-case, the queue may hold a large portion of the grid.
class Solution {
public:
    // Directions vector for 8 possible moves (vertical, horizontal, and diagonal)
    vector<pair<int, int>> directions { { 1, 0 }, { -1, 0 }, { 0, 1 }, { 0, -1 }, { -1, -1 }, { -1, 1 }, { 1, -1 }, { 1, 1 } };

    // BFS to traverse and mark an island starting from cell (i, j)
    // Parameters:
    //   grid: 2D grid representing the map ('L' for Land, 'W' for Water)
    //   i, j: Starting coordinates for BFS
    //   que: Queue used for BFS traversal
    void bfs(vector<vector<char>>& grid, int i, int j, queue<pair<int, int>>& que) {
        // Push the starting cell into the queue and mark it as visited ('$')
        que.push({ i, j });
        grid[i][j] = '$';

        // Lambda function to check if the cell (i, j) is safe (in bounds and is 'L')
        auto isSafe = [&](int i, int j) {
                          if (i < 0 || i >= grid.size() || j < 0 || j >= grid[0].size() || grid[i][j] != 'L') {
                              return false;
                          }
                          return true;
                      };

        while (!que.empty()) {
            auto curr = que.front();
            que.pop();

            // Check all 8 neighboring cells
            for (auto& dir : directions) {
                int i_ = curr.first + dir.first;
                int j_ = curr.second + dir.second;

                if (isSafe(i_, j_)) {
                    que.push({ i_, j_ });
                    grid[i_][j_] = '$';
                }
            }
        }
    }
    // Count the number of islands in the grid using BFS.
    // Parameters:
    //   grid: 2D grid of characters ('L' for Land, 'W' for Water)
    // Returns the number of islands.
    int countIslands(vector<vector<char>>& grid) {
        if (grid.size() == 0) {
            return 0;
        }

        int m     = grid.size();
        int n     = grid[0].size();
        int count = 0;
        queue<pair<int, int>> que;     // Queue for BFS

        // Iterate over every cell in the grid
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                // When an unvisited 'L' is found, perform BFS and increment island count
                if (grid[i][j] == 'L') {
                    bfs(grid, i, j, que);
                    count++;
                }
            }
        }
        return count;
    }
};

/*
 *
 * Dry Run Visual Representation for BFS Island Counting on the Example Grid:
 *
 * Example Grid:
 *
 *          0      1      2     3      4
 *       +------+------+------+------+------+
 * Row0  |  L   |  L   |  W   |  W   |  W   |
 *       +------+------+------+------+------+
 * Row1  |  W   |  L   |  W   |  W   |  L   |
 *       +------+------+------+------+------+
 * Row2  |  L   |  W   |  W   |  L   |  L   |
 *       +------+------+------+------+------+
 * Row3  |  W   |  W   |  W   |  W   |  W   |
 *       +------+------+------+------+------+
 * Row4  |  L   |  W   |  L   |  L   |  W   |
 *       +------+------+------+------+------+
 *
 * -----------------------------------------------------------
 * BFS for Island 1 (Starting at (0,0)):
 *
 * Step 1: Start BFS at (0,0)
 *   - Enqueue (0,0) and mark grid[0][0] as '$'
 *
 *   Grid State:
 *          0      1      2     3      4
 *       +------+------+------+------+------+
 * Row0  |  $   |  L   |  W   |  W   |  W   |
 *       +------+------+------+------+------+
 * Row1  |  W   |  L   |  W   |  W   |  L   |
 *       +------+------+------+------+------+
 * Row2  |  L   |  W   |  W   |  L   |  L   |
 *       +------+------+------+------+------+
 * Row3  |  W   |  W   |  W   |  W   |  W   |
 *       +------+------+------+------+------+
 * Row4  |  L   |  W   |  L   |  L   |  W   |
 *       +------+------+------+------+------+
 *
 *   Queue at start of Minute 0:
 *         +-----------+
 *         | (0,0)     |   <-- Front & Rear
 *         +-----------+
 *
 * Step 2: Process (0,0)
 *   - Dequeue (0,0)
 *   - Neighbors of (0,0): (0,1) and (1,1) are 'L'
 *   - Mark (0,1) and (1,1) as '$' and enqueue them.
 *
 *   Grid State:
 *          0      1      2     3      4
 *       +------+------+------+------+------+
 * Row0  |  $   |  $   |  W   |  W   |  W   |
 *       +------+------+------+------+------+
 * Row1  |  W   |  $   |  W   |  W   |  L   |
 *       +------+------+------+------+------+
 * Row2  |  L   |  W   |  W   |  L   |  L   |
 *       +------+------+------+------+------+
 * Row3  |  W   |  W   |  W   |  W   |  W   |
 *       +------+------+------+------+------+
 * Row4  |  L   |  W   |  L   |  L   |  W   |
 *       +------+------+------+------+------+
 *
 *   Queue after Minute 0:
 *         +-----------+-----------+
 *         | (0,1)     | (1,1)     |  <-- Front: (0,1), Rear: (1,1)
 *         +-----------+-----------+
 *
 * Step 3: Process (0,1)
 *   - Dequeue (0,1)
 *   - Neighbors of (0,1): All either out-of-bound, Water, or already visited ('$')
 *   - No new cell enqueued.
 *
 *   Queue now:
 *         +-----------+
 *         | (1,1)     |  <-- Front & Rear
 *         +-----------+
 *
 * Step 4: Process (1,1)
 *   - Dequeue (1,1)
 *   - Neighbors of (1,1): (2,0) is 'L'
 *   - Mark (2,0) as '$' and enqueue (2,0)
 *
 *   Grid State:
 *          0      1      2     3      4
 *       +------+------+------+------+------+
 * Row0  |  $   |  $   |  W   |  W   |  W   |
 *       +------+------+------+------+------+
 * Row1  |  W   |  $   |  W   |  W   |  L   |
 *       +------+------+------+------+------+
 * Row2  |  $   |  W   |  W   |  L   |  L   |
 *       +------+------+------+------+------+
 * Row3  |  W   |  W   |  W   |  W   |  W   |
 *       +------+------+------+------+------+
 * Row4  |  L   |  W   |  L   |  L   |  W   |
 *       +------+------+------+------+------+
 *
 *   Queue now:
 *         +-----------+
 *         | (2,0)     |  <-- Front & Rear
 *         +-----------+
 *
 * Step 5: Process (2,0)
 *   - Dequeue (2,0)
 *   - Neighbors of (2,0): All are either Water, out-of-bound, or already visited.
 *   - No new cell enqueued.
 *
 *   Queue becomes empty.
 *
 *   => Island 1 completed. Island count becomes 1.
 *
 * -----------------------------------------------------------
 * BFS for Island 2 (Starting at (1,4)):
 *
 * Step 6: Start BFS at (1,4)
 *   - Enqueue (1,4) and mark grid[1][4] as '$'
 *
 *   Grid State:
 *          0      1      2     3      4
 *       +------+------+------+------+------+
 * Row0  |  $   |  $   |  W   |  W   |  W   |
 *       +------+------+------+------+------+
 * Row1  |  W   |  $   |  W   |  W   |  $   |
 *       +------+------+------+------+------+
 * Row2  |  $   |  W   |  W   |  L   |  L   |
 *       +------+------+------+------+------+
 * Row3  |  W   |  W   |  W   |  W   |  W   |
 *       +------+------+------+------+------+
 * Row4  |  L   |  W   |  L   |  L   |  W   |
 *       +------+------+------+------+------+
 *
 *   Queue at start of Minute 0 for Island 2:
 *         +-----------+
 *         | (1,4)     |  <-- Front & Rear
 *         +-----------+
 *
 * Step 7: Process (1,4)
 *   - Dequeue (1,4)
 *   - Neighbors of (1,4): (2,4) and (2,3) are 'L'
 *   - Mark (2,4) and (2,3) as '$' and enqueue them.
 *
 *   Grid State:
 *          0      1      2     3      4
 *       +------+------+------+------+------+
 * Row0  |  $   |  $   |  W   |  W   |  W   |
 *       +------+------+------+------+------+
 * Row1  |  W   |  $   |  W   |  W   |  $   |
 *       +------+------+------+------+------+
 * Row2  |  $   |  W   |  W   |  $   |  $   |
 *       +------+------+------+------+------+
 * Row3  |  W   |  W   |  W   |  W   |  W   |
 *       +------+------+------+------+------+
 * Row4  |  L   |  W   |  L   |  L   |  W   |
 *       +------+------+------+------+------+
 *
 *   Queue after processing (1,4):
 *         +-----------+-----------+
 *         | (2,4)     | (2,3)     |  <-- Front: (2,4), Rear: (2,3)
 *         +-----------+-----------+
 *
 * Step 8: Process (2,4)
 *   - Dequeue (2,4)
 *   - Neighbors of (2,4): All neighbors are either out-of-bound, Water, or already visited.
 *   - No new cell enqueued.
 *
 *   Queue now:
 *         +-----------+
 *         | (2,3)     |  <-- Front & Rear
 *         +-----------+
 *
 * Step 9: Process (2,3)
 *   - Dequeue (2,3)
 *   - Neighbors of (2,3): All neighbors are either out-of-bound, Water, or already visited.
 *   - No new cell enqueued.
 *
 *   Queue becomes empty.
 *
 *   => Island 2 completed. Island count becomes 2.
 *
 * -----------------------------------------------------------
 * BFS for Island 3 (Starting at (4,0)):
 *
 * Step 10: Start BFS at (4,0)
 *   - Enqueue (4,0) and mark grid[4][0] as '$'
 *
 *   Grid State:
 *          0      1      2     3      4
 *       +------+------+------+------+------+
 * Row0  |  $   |  $   |  W   |  W   |  W   |
 *       +------+------+------+------+------+
 * Row1  |  W   |  $   |  W   |  W   |  $   |
 *       +------+------+------+------+------+
 * Row2  |  $   |  W   |  W   |  $   |  $   |
 *       +------+------+------+------+------+
 * Row3  |  W   |  W   |  W   |  W   |  W   |
 *       +------+------+------+------+------+
 * Row4  |  $   |  W   |  L   |  L   |  W   |
 *       +------+------+------+------+------+
 *
 *   Queue for Island 3:
 *         +-----------+
 *         | (4,0)     |  <-- Front & Rear
 *         +-----------+
 *
 * Step 11: Process (4,0)
 *   - Dequeue (4,0)
 *   - Neighbors of (4,0): All neighbors are either out-of-bound, Water, or not 'L'.
 *   - No new cell enqueued.
 *
 *   Queue becomes empty.
 *
 *   => Island 3 completed. Island count becomes 3.
 *
 * -----------------------------------------------------------
 * BFS for Island 4 (Starting at (4,2)):
 *
 * Step 12: Start BFS at (4,2)
 *   - Enqueue (4,2) and mark grid[4][2] as '$'
 *
 *   Grid State:
 *          0      1      2     3      4
 *       +------+------+------+------+------+
 * Row0  |  $   |  $   |  W   |  W   |  W   |
 *       +------+------+------+------+------+
 * Row1  |  W   |  $   |  W   |  W   |  $   |
 *       +------+------+------+------+------+
 * Row2  |  $   |  W   |  W   |  $   |  $   |
 *       +------+------+------+------+------+
 * Row3  |  W   |  W   |  W   |  W   |  W   |
 *       +------+------+------+------+------+
 * Row4  |  $   |  W   |  $   |  L   |  W   |
 *       +------+------+------+------+------+
 *
 *   Queue at start for Island 4:
 *         +-----------+
 *         | (4,2)     |  <-- Front & Rear
 *         +-----------+
 *
 * Step 13: Process (4,2)
 *   - Dequeue (4,2)
 *   - Neighbors of (4,2): (4,3) is 'L'
 *   - Mark (4,3) as '$' and enqueue (4,3)
 *
 *   Grid State:
 *          0      1      2     3      4
 *       +------+------+------+------+------+
 * Row0  |  $   |  $   |  W   |  W   |  W   |
 *       +------+------+------+------+------+
 * Row1  |  W   |  $   |  W   |  W   |  $   |
 *       +------+------+------+------+------+
 * Row2  |  $   |  W   |  W   |  $   |  $   |
 *       +------+------+------+------+------+
 * Row3  |  W   |  W   |  W   |  W   |  W   |
 *       +------+------+------+------+------+
 * Row4  |  $   |  W   |  $   |  $   |  W   |
 *       +------+------+------+------+------+
 *
 *   Queue now:
 *         +-----------+
 *         | (4,3)     |  <-- Front & Rear
 *         +-----------+
 *
 * Step 14: Process (4,3)
 *   - Dequeue (4,3)
 *   - Neighbors of (4,3): All neighbors are either out-of-bound, Water, or already visited.
 *   - No new cell enqueued.
 *
 *   Queue becomes empty.
 *
 *   => Island 4 completed. Island count becomes 4.
 *
 * Final Outcome: Total Island Count = 4.
 *
 */

/************************************************************ JAVA ************************************************/

// Approach 1 (DFS): Use DFS to traverse each connected component (island) and mark visited land cells with '$' to avoid reprocessing.
// Time Complexity: O(n*m) where n is the number of rows and m is the number of columns, since each cell is processed once.
// Space Complexity: O(n*m) in the worst-case due to recursion stack in case the grid is filled with land.
class Solution {
    // Depth First Search to mark all connected 'L' cells as visited ('$')
    public void dfs(char[][] grid, int i, int j) {
        // If out of bounds or current cell is not land, return
        if (i < 0 || i >= grid.length || j < 0 || j >= grid[0].length || grid[i][j] != 'L') {
            return;
        }

        // Mark the current cell as visited
        grid[i][j] = '$';

        // Recursively visit all 8 neighboring cells
        // Vertical and Horizontal
        dfs(grid, i + 1, j);    // Down
        dfs(grid, i - 1, j);    // Up
        dfs(grid, i, j + 1);    // Right
        dfs(grid, i, j - 1);    // Left

        // Diagonals
        dfs(grid, i - 1, j - 1);    // Upper-Left
        dfs(grid, i - 1, j + 1);    // Upper-Right
        dfs(grid, i + 1, j - 1);    // Lower-Left
        dfs(grid, i + 1, j + 1);    // Lower-Right
    }
    // Function to count the number of islands in the grid
    public int countIslands(char[][] grid) {
        int m = grid.length;
        int n = grid[0].length;

        int count = 0;

        // Iterate over every cell in the grid
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                // If the cell is land, it's part of an unvisited island
                if (grid[i][j] == 'L') {
                    dfs(grid, i, j); // Mark the entire island as visited
                    count++;         // Increment island count
                }
            }
        }
        return count;
    }
}

/*
 *
 * Dry Run:
 * Example Input Grid:
 *           0      1      2     3      4
 *       +------+------+------+------+------+
 * Row0  |  L   |  L   |  W   |  W   |  W   |
 *       +------+------+------+------+------+
 * Row1  |  W   |  L   |  W   |  W   |  L   |
 *       +------+------+------+------+------+
 * Row2  |  L   |  W   |  W   |  L   |  L   |
 *       +------+------+------+------+------+
 * Row3  |  W   |  W   |  W   |  W   |  W   |
 *       +------+------+------+------+------+
 * Row4  |  L   |  W   |  L   |  L   |  W   |
 *       +------+------+------+------+------+
 *
 * Step 1: Start scanning grid. At (0,0) = 'L'
 *   - Call DFS(0,0) and mark (0,0) as '$'
 *   Updated Grid:
 *           0      1      2     3      4
 *       +------+------+------+------+------+
 * Row0  |  $   |  L   |  W   |  W   |  W   |
 *       +------+------+------+------+------+
 * Row1  |  W   |  L   |  W   |  W   |  L   |
 *       +------+------+------+------+------+
 * Row2  |  L   |  W   |  W   |  L   |  L   |
 *       +------+------+------+------+------+
 * Row3  |  W   |  W   |  W   |  W   |  W   |
 *       +------+------+------+------+------+
 * Row4  |  L   |  W   |  L   |  L   |  W   |
 *       +------+------+------+------+------+
 *
 * Step 2: From (0,0), DFS explores neighbor (0,1) = 'L'
 *   - Call DFS(0,1) and mark (0,1) as '$'
 *   Updated Grid:
 *           0      1      2     3      4
 *       +------+------+------+------+------+
 * Row0  |  $   |  $   |  W   |  W   |  W   |
 *       +------+------+------+------+------+
 * Row1  |  W   |  L   |  W   |  W   |  L   |
 *       +------+------+------+------+------+
 * Row2  |  L   |  W   |  W   |  L   |  L   |
 *       +------+------+------+------+------+
 * Row3  |  W   |  W   |  W   |  W   |  W   |
 *       +------+------+------+------+------+
 * Row4  |  L   |  W   |  L   |  L   |  W   |
 *       +------+------+------+------+------+
 *
 * Step 3: From (0,1), DFS explores neighbor (1,1) = 'L'
 *   - Call DFS(1,1) and mark (1,1) as '$'
 *   Updated Grid:
 *           0      1      2     3      4
 *       +------+------+------+------+------+
 * Row0  |  $   |  $   |  W   |  W   |  W   |
 *       +------+------+------+------+------+
 * Row1  |  W   |  $   |  W   |  W   |  L   |
 *       +------+------+------+------+------+
 * Row2  |  L   |  W   |  W   |  L   |  L   |
 *       +------+------+------+------+------+
 * Row3  |  W   |  W   |  W   |  W   |  W   |
 *       +------+------+------+------+------+
 * Row4  |  L   |  W   |  L   |  L   |  W   |
 *       +------+------+------+------+------+
 *
 * Step 4: From (1,1), DFS explores diagonal neighbor (2,0) = 'L'
 *   - Call DFS(2,0) and mark (2,0) as '$'
 *   Updated Grid:
 *           0      1      2     3      4
 *       +------+------+------+------+------+
 * Row0  |  $   |  $   |  W   |  W   |  W   |
 *       +------+------+------+------+------+
 * Row1  |  W   |  $   |  W   |  W   |  L   |
 *       +------+------+------+------+------+
 * Row2  |  $   |  W   |  W   |  L   |  L   |
 *       +------+------+------+------+------+
 * Row3  |  W   |  W   |  W   |  W   |  W   |
 *       +------+------+------+------+------+
 * Row4  |  L   |  W   |  L   |  L   |  W   |
 *       +------+------+------+------+------+
 *
 * Island 1 Completed. Island count becomes 1.
 *
 * Step 5: Continue scanning grid. Next unvisited 'L' is at (1,4)
 *   - Call DFS(1,4) and mark (1,4) as '$'
 *   Updated Grid:
 *           0      1      2     3      4
 *       +------+------+------+------+------+
 * Row0  |  $   |  $   |  W   |  W   |  W   |
 *       +------+------+------+------+------+
 * Row1  |  W   |  $   |  W   |  W   |  $   |
 *       +------+------+------+------+------+
 * Row2  |  $   |  W   |  W   |  L   |  L   |
 *       +------+------+------+------+------+
 * Row3  |  W   |  W   |  W   |  W   |  W   |
 *       +------+------+------+------+------+
 * Row4  |  L   |  W   |  L   |  L   |  W   |
 *       +------+------+------+------+------+
 *
 * Step 6: From (1,4), DFS explores neighbor (2,4) = 'L'
 *   - Call DFS(2,4) and mark (2,4) as '$'
 *   Updated Grid:
 *           0      1      2     3      4
 *       +------+------+------+------+------+
 * Row0  |  $   |  $   |  W   |  W   |  W   |
 *       +------+------+------+------+------+
 * Row1  |  W   |  $   |  W   |  W   |  $   |
 *       +------+------+------+------+------+
 * Row2  |  $   |  W   |  W   |  L   |  $   |
 *       +------+------+------+------+------+
 * Row3  |  W   |  W   |  W   |  W   |  W   |
 *       +------+------+------+------+------+
 * Row4  |  L   |  W   |  L   |  L   |  W   |
 *       +------+------+------+------+------+
 *
 * Step 7: From (2,4), DFS explores neighbor (2,3) = 'L'
 *   - Call DFS(2,3) and mark (2,3) as '$'
 *   Updated Grid:
 *           0      1      2     3      4
 *       +------+------+------+------+------+
 * Row0  |  $   |  $   |  W   |  W   |  W   |
 *       +------+------+------+------+------+
 * Row1  |  W   |  $   |  W   |  W   |  $   |
 *       +------+------+------+------+------+
 * Row2  |  $   |  W   |  W   |  $   |  $   |
 *       +------+------+------+------+------+
 * Row3  |  W   |  W   |  W   |  W   |  W   |
 *       +------+------+------+------+------+
 * Row4  |  L   |  W   |  L   |  L   |  W   |
 *       +------+------+------+------+------+
 *
 * Island 2 Completed. Island count becomes 2.
 *
 * Step 8: Continue scanning grid. Next unvisited 'L' is at (4,0)
 *   - Call DFS(4,0) and mark (4,0) as '$'
 *   Updated Grid:
 *           0      1      2     3      4
 *       +------+------+------+------+------+
 * Row0  |  $   |  $   |  W   |  W   |  W   |
 *       +------+------+------+------+------+
 * Row1  |  W   |  $   |  W   |  W   |  $   |
 *       +------+------+------+------+------+
 * Row2  |  $   |  W   |  W   |  $   |  $   |
 *       +------+------+------+------+------+
 * Row3  |  W   |  W   |  W   |  W   |  W   |
 *       +------+------+------+------+------+
 * Row4  |  $   |  W   |  L   |  L   |  W   |
 *       +------+------+------+------+------+
 *
 * Island 3 Completed. Island count becomes 3.
 *
 * Step 9: Continue scanning grid. Next unvisited 'L' is at (4,2)
 *   - Call DFS(4,2) and mark (4,2) as '$'
 *   Updated Grid:
 *           0      1      2     3      4
 *       +------+------+------+------+------+
 * Row0  |  $   |  $   |  W   |  W   |  W   |
 *       +------+------+------+------+------+
 * Row1  |  W   |  $   |  W   |  W   |  $   |
 *       +------+------+------+------+------+
 * Row2  |  $   |  W   |  W   |  $   |  $   |
 *       +------+------+------+------+------+
 * Row3  |  W   |  W   |  W   |  W   |  W   |
 *       +------+------+------+------+------+
 * Row4  |  $   |  W   |  $   |  L   |  W   |
 *       +------+------+------+------+------+
 *
 * Step 10: From (4,2), DFS explores neighbor (4,3) = 'L'
 *   - Call DFS(4,3) and mark (4,3) as '$'
 *   Updated Grid:
 *           0      1      2     3      4
 *       +------+------+------+------+------+
 * Row0  |  $   |  $   |  W   |  W   |  W   |
 *       +------+------+------+------+------+
 * Row1  |  W   |  $   |  W   |  W   |  $   |
 *       +------+------+------+------+------+
 * Row2  |  $   |  W   |  W   |  $   |  $   |
 *       +------+------+------+------+------+
 * Row3  |  W   |  W   |  W   |  W   |  W   |
 *       +------+------+------+------+------+
 * Row4  |  $   |  W   |  $   |  $   |  W   |
 *       +------+------+------+------+------+
 *
 * Island 4 Completed. Island count becomes 4.
 *
 * Final Island Count = 4.
 *
 */

//Approach-2 (BFS)
//T.C : O(m*n) - Every cell is processed once.
//S.C : O(m*n) - In worst-case, the queue may hold a large portion of the grid.
class Solution {
    // Note: In Java, we need a custom Pair class.
    static class Pair {
        int first;
        int second;
        Pair(int first, int second) {
            this.first  = first;
            this.second = second;
        }
    }

    // Directions vector for 8 possible moves (vertical, horizontal, and diagonal)
    List<Pair> directions = Arrays.asList(new Pair(1, 0), new Pair(-1, 0), new Pair(0, 1), new Pair(0, -1), new Pair(-1, -1), new Pair(-1, 1), new Pair(1, -1), new Pair(1, 1));

    // BFS to traverse and mark an island starting from cell (i, j)
    // Parameters:
    //   grid: 2D grid representing the map ('L' for Land, 'W' for Water)
    //   i, j: Starting coordinates for BFS
    //   que: Queue used for BFS traversal
    void bfs(char[][] grid, int i, int j, Queue<Pair> que) {
        // Push the starting cell into the queue and mark it as visited ('$')
        que.offer(new Pair(i, j));
        grid[i][j] = '$';

        // Instead of a lambda, we use a helper method isSafe defined below.

        while (!que.isEmpty()) {
            Pair curr = que.poll();

            // Check all 8 neighboring cells
            for (Pair dir : directions) {
                int i_ = curr.first + dir.first;
                int j_ = curr.second + dir.second;

                if (isSafe(grid, i_, j_)) {
                    que.offer(new Pair(i_, j_));
                    grid[i_][j_] = '$';
                }
            }
        }
    }
    // Helper method to check if the cell (i, j) is safe (in bounds and is 'L')
    boolean isSafe(char[][] grid, int i, int j) {
        if (i < 0 || i >= grid.length || j < 0 || j >= grid[0].length || grid[i][j] != 'L') {
            return false;
        }
        return true;
    }
    public int countIslands(char[][] grid) {
        if (grid.length == 0) {
            return 0;
        }

        int         m     = grid.length;
        int         n     = grid[0].length;
        int         count = 0;
        Queue<Pair> que   = new LinkedList<>();   // Queue for BFS

        // Iterate over every cell in the grid
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                // When an unvisited 'L' is found, perform BFS and increment island count
                if (grid[i][j] == 'L') {
                    bfs(grid, i, j, que);
                    count++;
                }
            }
        }
        return count;
    }
}

/*
 *
 * Dry Run Visual Representation for BFS Island Counting on the Example Grid:
 *
 * Example Grid:
 *
 *          0      1      2     3      4
 *       +------+------+------+------+------+
 * Row0  |  L   |  L   |  W   |  W   |  W   |
 *       +------+------+------+------+------+
 * Row1  |  W   |  L   |  W   |  W   |  L   |
 *       +------+------+------+------+------+
 * Row2  |  L   |  W   |  W   |  L   |  L   |
 *       +------+------+------+------+------+
 * Row3  |  W   |  W   |  W   |  W   |  W   |
 *       +------+------+------+------+------+
 * Row4  |  L   |  W   |  L   |  L   |  W   |
 *       +------+------+------+------+------+
 *
 * -----------------------------------------------------------
 * BFS for Island 1 (Starting at (0,0)):
 *
 * Step 1: Start BFS at (0,0)
 *   - Enqueue (0,0) and mark grid[0][0] as '$'
 *
 *   Grid State:
 *          0      1      2     3      4
 *       +------+------+------+------+------+
 * Row0  |  $   |  L   |  W   |  W   |  W   |
 *       +------+------+------+------+------+
 * Row1  |  W   |  L   |  W   |  W   |  L   |
 *       +------+------+------+------+------+
 * Row2  |  L   |  W   |  W   |  L   |  L   |
 *       +------+------+------+------+------+
 * Row3  |  W   |  W   |  W   |  W   |  W   |
 *       +------+------+------+------+------+
 * Row4  |  L   |  W   |  L   |  L   |  W   |
 *       +------+------+------+------+------+
 *
 *   Queue at start of Minute 0:
 *         +-----------+
 *         | (0,0)     |   <-- Front & Rear
 *         +-----------+
 *
 * Step 2: Process (0,0)
 *   - Dequeue (0,0)
 *   - Neighbors of (0,0): (0,1) and (1,1) are 'L'
 *   - Mark (0,1) and (1,1) as '$' and enqueue them.
 *
 *   Grid State:
 *          0      1      2     3      4
 *       +------+------+------+------+------+
 * Row0  |  $   |  $   |  W   |  W   |  W   |
 *       +------+------+------+------+------+
 * Row1  |  W   |  $   |  W   |  W   |  L   |
 *       +------+------+------+------+------+
 * Row2  |  L   |  W   |  W   |  L   |  L   |
 *       +------+------+------+------+------+
 * Row3  |  W   |  W   |  W   |  W   |  W   |
 *       +------+------+------+------+------+
 * Row4  |  L   |  W   |  L   |  L   |  W   |
 *       +------+------+------+------+------+
 *
 *   Queue after Minute 0:
 *         +-----------+-----------+
 *         | (0,1)     | (1,1)     |  <-- Front: (0,1), Rear: (1,1)
 *         +-----------+-----------+
 *
 * Step 3: Process (0,1)
 *   - Dequeue (0,1)
 *   - Neighbors of (0,1): All either out-of-bound, Water, or already visited ('$')
 *   - No new cell enqueued.
 *
 *   Queue now:
 *         +-----------+
 *         | (1,1)     |  <-- Front & Rear
 *         +-----------+
 *
 * Step 4: Process (1,1)
 *   - Dequeue (1,1)
 *   - Neighbors of (1,1): (2,0) is 'L'
 *   - Mark (2,0) as '$' and enqueue (2,0)
 *
 *   Grid State:
 *          0      1      2     3      4
 *       +------+------+------+------+------+
 * Row0  |  $   |  $   |  W   |  W   |  W   |
 *       +------+------+------+------+------+
 * Row1  |  W   |  $   |  W   |  W   |  L   |
 *       +------+------+------+------+------+
 * Row2  |  $   |  W   |  W   |  L   |  L   |
 *       +------+------+------+------+------+
 * Row3  |  W   |  W   |  W   |  W   |  W   |
 *       +------+------+------+------+------+
 * Row4  |  L   |  W   |  L   |  L   |  W   |
 *       +------+------+------+------+------+
 *
 *   Queue now:
 *         +-----------+
 *         | (2,0)     |  <-- Front & Rear
 *         +-----------+
 *
 * Step 5: Process (2,0)
 *   - Dequeue (2,0)
 *   - Neighbors of (2,0): All are either Water, out-of-bound, or already visited.
 *   - No new cell enqueued.
 *
 *   Queue becomes empty.
 *
 *   => Island 1 completed. Island count becomes 1.
 *
 * -----------------------------------------------------------
 * BFS for Island 2 (Starting at (1,4)):
 *
 * Step 6: Start BFS at (1,4)
 *   - Enqueue (1,4) and mark grid[1][4] as '$'
 *
 *   Grid State:
 *          0      1      2     3      4
 *       +------+------+------+------+------+
 * Row0  |  $   |  $   |  W   |  W   |  W   |
 *       +------+------+------+------+------+
 * Row1  |  W   |  $   |  W   |  W   |  $   |
 *       +------+------+------+------+------+
 * Row2  |  $   |  W   |  W   |  L   |  L   |
 *       +------+------+------+------+------+
 * Row3  |  W   |  W   |  W   |  W   |  W   |
 *       +------+------+------+------+------+
 * Row4  |  L   |  W   |  L   |  L   |  W   |
 *       +------+------+------+------+------+
 *
 *   Queue at start of Minute 0 for Island 2:
 *         +-----------+
 *         | (1,4)     |  <-- Front & Rear
 *         +-----------+
 *
 * Step 7: Process (1,4)
 *   - Dequeue (1,4)
 *   - Neighbors of (1,4): (2,4) and (2,3) are 'L'
 *   - Mark (2,4) and (2,3) as '$' and enqueue them.
 *
 *   Grid State:
 *          0      1      2     3      4
 *       +------+------+------+------+------+
 * Row0  |  $   |  $   |  W   |  W   |  W   |
 *       +------+------+------+------+------+
 * Row1  |  W   |  $   |  W   |  W   |  $   |
 *       +------+------+------+------+------+
 * Row2  |  $   |  W   |  W   |  $   |  $   |
 *       +------+------+------+------+------+
 * Row3  |  W   |  W   |  W   |  W   |  W   |
 *       +------+------+------+------+------+
 * Row4  |  L   |  W   |  L   |  L   |  W   |
 *       +------+------+------+------+------+
 *
 *   Queue after processing (1,4):
 *         +-----------+-----------+
 *         | (2,4)     | (2,3)     |  <-- Front: (2,4), Rear: (2,3)
 *         +-----------+-----------+
 *
 * Step 8: Process (2,4)
 *   - Dequeue (2,4)
 *   - Neighbors of (2,4): All neighbors are either out-of-bound, Water, or already visited.
 *   - No new cell enqueued.
 *
 *   Queue now:
 *         +-----------+
 *         | (2,3)     |  <-- Front & Rear
 *         +-----------+
 *
 * Step 9: Process (2,3)
 *   - Dequeue (2,3)
 *   - Neighbors of (2,3): All neighbors are either out-of-bound, Water, or already visited.
 *   - No new cell enqueued.
 *
 *   Queue becomes empty.
 *
 *   => Island 2 completed. Island count becomes 2.
 *
 * -----------------------------------------------------------
 * BFS for Island 3 (Starting at (4,0)):
 *
 * Step 10: Start BFS at (4,0)
 *   - Enqueue (4,0) and mark grid[4][0] as '$'
 *
 *   Grid State:
 *          0      1      2     3      4
 *       +------+------+------+------+------+
 * Row0  |  $   |  $   |  W   |  W   |  W   |
 *       +------+------+------+------+------+
 * Row1  |  W   |  $   |  W   |  W   |  $   |
 *       +------+------+------+------+------+
 * Row2  |  $   |  W   |  W   |  $   |  $   |
 *       +------+------+------+------+------+
 * Row3  |  W   |  W   |  W   |  W   |  W   |
 *       +------+------+------+------+------+
 * Row4  |  $   |  W   |  L   |  L   |  W   |
 *       +------+------+------+------+------+
 *
 *   Queue for Island 3:
 *         +-----------+
 *         | (4,0)     |  <-- Front & Rear
 *         +-----------+
 *
 * Step 11: Process (4,0)
 *   - Dequeue (4,0)
 *   - Neighbors of (4,0): All neighbors are either out-of-bound, Water, or not 'L'.
 *   - No new cell enqueued.
 *
 *   Queue becomes empty.
 *
 *   => Island 3 completed. Island count becomes 3.
 *
 * -----------------------------------------------------------
 * BFS for Island 4 (Starting at (4,2)):
 *
 * Step 12: Start BFS at (4,2)
 *   - Enqueue (4,2) and mark grid[4][2] as '$'
 *
 *   Grid State:
 *          0      1      2     3      4
 *       +------+------+------+------+------+
 * Row0  |  $   |  $   |  W   |  W   |  W   |
 *       +------+------+------+------+------+
 * Row1  |  W   |  $   |  W   |  W   |  $   |
 *       +------+------+------+------+------+
 * Row2  |  $   |  W   |  W   |  $   |  $   |
 *       +------+------+------+------+------+
 * Row3  |  W   |  W   |  W   |  W   |  W   |
 *       +------+------+------+------+------+
 * Row4  |  $   |  W   |  $   |  L   |  W   |
 *       +------+------+------+------+------+
 *
 *   Queue at start for Island 4:
 *         +-----------+
 *         | (4,2)     |  <-- Front & Rear
 *         +-----------+
 *
 * Step 13: Process (4,2)
 *   - Dequeue (4,2)
 *   - Neighbors of (4,2): (4,3) is 'L'
 *   - Mark (4,3) as '$' and enqueue (4,3)
 *
 *   Grid State:
 *          0      1      2     3      4
 *       +------+------+------+------+------+
 * Row0  |  $   |  $   |  W   |  W   |  W   |
 *       +------+------+------+------+------+
 * Row1  |  W   |  $   |  W   |  W   |  $   |
 *       +------+------+------+------+------+
 * Row2  |  $   |  W   |  W   |  $   |  $   |
 *       +------+------+------+------+------+
 * Row3  |  W   |  W   |  W   |  W   |  W   |
 *       +------+------+------+------+------+
 * Row4  |  $   |  W   |  $   |  $   |  W   |
 *       +------+------+------+------+------+
 *
 *   Queue now:
 *         +-----------+
 *         | (4,3)     |  <-- Front & Rear
 *         +-----------+
 *
 * Step 14: Process (4,3)
 *   - Dequeue (4,3)
 *   - Neighbors of (4,3): All neighbors are either out-of-bound, Water, or already visited.
 *   - No new cell enqueued.
 *
 *   Queue becomes empty.
 *
 *   => Island 4 completed. Island count becomes 4.
 *
 * Final Outcome: Total Island Count = 4.
 *
 */
