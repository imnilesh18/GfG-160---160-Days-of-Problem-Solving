/*
 * Rotten Oranges
 *
 * Difficulty: Medium Accuracy: 46.02% Submissions: 161K+ Points: 4 Average Time: 20m
 *
 * Given a matrix mat[][] of dimension n * m where each cell in the matrix can have values 0, 1 or 2 which has the following meaning:
 * 0 : Empty cell
 * 1 : Cell have fresh oranges
 * 2 : Cell have rotten oranges
 *
 * We have to determine what is the earliest time after which all the oranges are rotten. A rotten orange at index (i, j) can rot other fresh orange at indexes (i-1, j), (i+1, j), (i, j-1), (i, j+1) (up, down, left and right) in a unit time.
 *
 * Note: Your task is to return the minimum time to rot all the fresh oranges. If not possible returns -1.
 *
 * Examples:
 *
 * Input: mat[][] = [[0, 1, 2], [0, 1, 2], [2, 1, 1]]
 * Output: 1
 * Explanation: Oranges at positions (0,2), (1,2), (2,0) will rot oranges at (0,1), (1,1), (2,2) and (2,1) in unit time.
 *
 * Input: mat[][] = [[2, 2, 0, 1]]
 * Output: -1
 * Explanation: Oranges at (0,0) and (0,1) can't rot orange at (0,3).
 *
 * Input: mat[][] = [[2, 2, 2], [0, 2, 0]]
 * Output: 0
 * Explanation: There is no fresh orange.
 *
 * Constraints:
 * 1 ≤ mat.size() ≤ 500
 * 1 ≤ mat[0].size() ≤ 500
 * mat[i][j] = {0, 1, 2}
 */

/************************************************************ C++ ************************************************/

// Approach: We perform a multi-source BFS starting from all initially rotten oranges, rotting adjacent fresh oranges one level at a time (each level representing one minute).
// Time Complexity: O(m*n) because every cell is processed at most once.
// Space Complexity: O(m*n) in the worst-case scenario when many cells are stored in the queue.
class Solution {
public:
    typedef pair<int, int> P;
    // Directions represent Up, Down, Left, Right movements.
    vector<vector<int>> directions{ { -1, 0 }, { 1, 0 }, { 0, -1 }, { 0, 1 } };

    int orangesRotting(vector<vector<int>>& grid) {
        int m = grid.size();
        int n = grid[0].size();

        queue<P> que;            // Queue for BFS.
        int      freshCount = 0; // Count of fresh oranges.

        // Enqueue initial rotten oranges and count fresh ones.
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (grid[i][j] == 2) {
                    que.push({ i, j }); // Add rotten orange position.
                } else if (grid[i][j] == 1) {
                    freshCount++;       // Count fresh orange.
                }
            }
        }

        // If no fresh orange exists, return 0.
        if (freshCount == 0) {
            return 0;
        }

        int minutes = 0;    // Minutes counter for the rotting process.

        // BFS: Process oranges minute by minute.
        while (!que.empty()) {
            int N = que.size();    // Number of oranges to process in this minute.
            while (N--) {
                P curr = que.front();
                que.pop();

                int i = curr.first;
                int j = curr.second;

                // Check all 4 adjacent cells.
                for (vector<int>& dir : directions) {
                    int new_i = i + dir[0];
                    int new_j = j + dir[1];

                    // If within bounds and a fresh orange is found, rot it.
                    if (new_i >= 0 && new_i < m && new_j >= 0 && new_j < n && grid[new_i][new_j] == 1) {
                        // Update the fresh orange to rotten.
                        grid[new_i][new_j] = 2;
                        que.push({ new_i, new_j });
                        freshCount--;
                    }
                }
            }
            minutes++;    // Increase the minute counter after processing one level.
        }

        // Return minutes - 1 because the last increment occurs after processing a level with no new rotten oranges.
        return freshCount == 0 ? (minutes - 1) : -1;
    }
};

/*
 *
 * Dry Run
 *
 * Consider the input 4x4 matrix with indices and initial values as follows:
 *
 *         Columns
 *           0    1    2    3
 *       +------+------+------+------+
 *  Row0 |  2   |  1   |  1   |  2   |   // (0,0)=2, (0,1)=1, (0,2)=1, (0,3)=2
 *       +------+------+------+------+
 *  Row1 |  1   |  1   |  1   |  1   |   // (1,0)=1, (1,1)=1, (1,2)=1, (1,3)=1
 *       +------+------+------+------+
 *  Row2 |  0   |  0   |  1   |  1   |   // (2,0)=0, (2,1)=0, (2,2)=1, (2,3)=1
 *       +------+------+------+------+
 *  Row3 |  0   |  0   |  0   |  0   |   // (3,0)=0, (3,1)=0, (3,2)=0, (3,3)=0
 *       +------+------+------+------+
 *
 * Initial Setup:
 * - Rotten oranges positions: (0,0) and (0,3).
 * - Fresh oranges positions: (0,1), (0,2), (1,0), (1,1), (1,2), (1,3), (2,2), (2,3).
 *   => freshCount = 8.
 *
 * Initial Queue:
 *     - Front -> (0,0)
 *     - Rear  -> (0,3)
 *
 * ----------------------------------------------------------------------
 * Minute 0: Process all oranges currently in the queue.
 *
 * Queue at start of Minute 0:
 *     +-----------+
 *     | (0,0)     |   <-- Front
 *     +-----------+
 *     | (0,3)     |   <-- Rear
 *     +-----------+
 *
 * Processing (0,0):
 *   - Check Up: ( -1,0 ) → Out of bounds.
 *   - Check Down: (1,0)
 *         Before update: grid[1][0] = 1.
 *         After update:  grid[1][0] becomes 2.
 *         Enqueue (1,0); freshCount becomes 7.
 *         Diagram of change:
 *         Before:
 *           Row1: | 1 | 1 | 1 | 1 |
 *         After:
 *           Row1: | 2 | 1 | 1 | 1 |
 *
 *   - Check Left: (0,-1) → Out of bounds.
 *   - Check Right: (0,1)
 *         Before update: grid[0][1] = 1.
 *         After update:  grid[0][1] becomes 2.
 *         Enqueue (0,1); freshCount becomes 6.
 *         Diagram of change:
 *         Before:
 *           Row0: | 2 | 1 | 1 | 2 |
 *         After:
 *           Row0: | 2 | 2 | 1 | 2 |
 *
 * Processing (0,3):
 *   - Check Up: ( -1,3 ) → Out of bounds.
 *   - Check Down: (1,3)
 *         Before update: grid[1][3] = 1.
 *         After update:  grid[1][3] becomes 2.
 *         Enqueue (1,3); freshCount becomes 5.
 *         Diagram of change:
 *         Before:
 *           Row1: | 2 | 1 | 1 | 1 |   (Note: (1,0) was already updated to 2)
 *         After:
 *           Row1: | 2 | 1 | 1 | 2 |
 *
 *   - Check Left: (0,2)
 *         Before update: grid[0][2] = 1.
 *         After update:  grid[0][2] becomes 2.
 *         Enqueue (0,2); freshCount becomes 4.
 *         Diagram of change:
 *         Before:
 *           Row0: | 2 | 2 | 1 | 2 |
 *         After:
 *           Row0: | 2 | 2 | 2 | 2 |
 *
 *   - Check Right: (0,4) → Out of bounds.
 *
 * Matrix after Minute 0:
 *         Columns
 *           0    1    2    3
 *       +------+------+------+------+
 *  Row0 |  2   |  2   |  2   |  2   |
 *       +------+------+------+------+
 *  Row1 |  2   |  1   |  1   |  2   |
 *       +------+------+------+------+
 *  Row2 |  0   |  0   |  1   |  1   |
 *       +------+------+------+------+
 *  Row3 |  0   |  0   |  0   |  0   |
 *       +------+------+------+------+
 *
 * Queue after Minute 0:
 *     +-----------+
 *     | (1,0)     |   <-- Pushed from (0,0)
 *     +-----------+
 *     | (0,1)     |   <-- Pushed from (0,0)
 *     +-----------+
 *     | (1,3)     |   <-- Pushed from (0,3)
 *     +-----------+
 *     | (0,2)     |   <-- Pushed from (0,3)
 *     +-----------+
 *
 * Minutes incremented to 1.
 *
 * ----------------------------------------------------------------------
 * Minute 1: Process the new queue.
 *
 * Queue at start of Minute 1:
 *     +-----------+
 *     | (1,0)     |   <-- Front
 *     +-----------+
 *     | (0,1)     |
 *     +-----------+
 *     | (1,3)     |
 *     +-----------+
 *     | (0,2)     |   <-- Rear
 *     +-----------+
 *
 * Processing (1,0):
 *   - Check Up: (0,0) → Already rotten.
 *   - Check Down: (2,0) → grid[2][0] = 0 (empty), no change.
 *   - Check Left: (1,-1) → Out of bounds.
 *   - Check Right: (1,1)
 *         Before update: grid[1][1] = 1.
 *         After update:  grid[1][1] becomes 2.
 *         Enqueue (1,1); freshCount becomes 3.
 *         Diagram of change:
 *         Before:
 *           Row1: | 2 | 1 | 1 | 2 |
 *         After:
 *           Row1: | 2 | 2 | 1 | 2 |
 *
 * Processing (0,1):
 *   - Check Up: (-1,1) → Out of bounds.
 *   - Check Down: (1,1) → Already rotten (just updated).
 *   - Check Left: (0,0) → Already rotten.
 *   - Check Right: (0,2) → Already rotten.
 *   (No changes.)
 *
 * Processing (1,3):
 *   - Check Up: (0,3) → Already rotten.
 *   - Check Down: (2,3)
 *         Before update: grid[2][3] = 1.
 *         After update:  grid[2][3] becomes 2.
 *         Enqueue (2,3); freshCount becomes 2.
 *         Diagram of change:
 *         Before:
 *           Row2: | 0 | 0 | 1 | 1 |
 *         After:
 *           Row2: | 0 | 0 | 1 | 2 |
 *
 *   - Check Left: (1,2)
 *         Before update: grid[1][2] = 1.
 *         After update:  grid[1][2] becomes 2.
 *         Enqueue (1,2); freshCount becomes 1.
 *         Diagram of change:
 *         Before:
 *           Row1: | 2 | 2 | 1 | 2 |
 *         After:
 *           Row1: | 2 | 2 | 2 | 2 |
 *
 *   - Check Right: (1,4) → Out of bounds.
 *
 * Processing (0,2):
 *   - Check Up: (-1,2) → Out of bounds.
 *   - Check Down: (1,2) → Already rotten (just updated).
 *   - Check Left: (0,1) → Already rotten.
 *   - Check Right: (0,3) → Already rotten.
 *   (No changes.)
 *
 * Matrix after Minute 1:
 *         Columns
 *           0    1    2    3
 *       +------+------+------+------+
 *  Row0 |  2   |  2   |  2   |  2   |
 *       +------+------+------+------+
 *  Row1 |  2   |  2   |  2   |  2   |
 *       +------+------+------+------+
 *  Row2 |  0   |  0   |  1   |  2   |
 *       +------+------+------+------+
 *  Row3 |  0   |  0   |  0   |  0   |
 *       +------+------+------+------+
 *
 * Queue after Minute 1:
 *     +-----------+
 *     | (1,1)     |   <-- Pushed from (1,0)
 *     +-----------+
 *     | (2,3)     |   <-- Pushed from (1,3)
 *     +-----------+
 *     | (1,2)     |   <-- Pushed from (1,3)
 *     +-----------+
 *
 * Minutes incremented to 2.
 *
 * ----------------------------------------------------------------------
 * Minute 2: Process the new queue.
 *
 * Queue at start of Minute 2:
 *     +-----------+
 *     | (1,1)     |   <-- Front
 *     +-----------+
 *     | (2,3)     |
 *     +-----------+
 *     | (1,2)     |   <-- Rear
 *     +-----------+
 *
 * Processing (1,1):
 *   - Check Up: (0,1) → Already rotten.
 *   - Check Down: (2,1) → grid[2][1] = 0 (empty), no change.
 *   - Check Left: (1,0) → Already rotten.
 *   - Check Right: (1,2) → Already rotten.
 *   (No changes.)
 *
 * Processing (2,3):
 *   - Check Up: (1,3) → Already rotten.
 *   - Check Down: (3,3) → grid[3][3] = 0 (empty), no change.
 *   - Check Left: (2,2)
 *         Before update: grid[2][2] = 1.
 *         After update:  grid[2][2] becomes 2.
 *         Enqueue (2,2); freshCount becomes 0.
 *         Diagram of change:
 *         Before:
 *           Row2: | 0 | 0 | 1 | 2 |
 *         After:
 *           Row2: | 0 | 0 | 2 | 2 |
 *
 *   - Check Right: (2,4) → Out of bounds.
 *
 * Processing (1,2):
 *   - Check Up: (0,2) → Already rotten.
 *   - Check Down: (2,2) → Already rotten (just updated).
 *   - Check Left: (1,1) → Already rotten.
 *   - Check Right: (1,3) → Already rotten.
 *   (No changes.)
 *
 * Matrix after Minute 2:
 *         Columns
 *           0    1    2    3
 *       +------+------+------+------+
 *  Row0 |  2   |  2   |  2   |  2   |
 *       +------+------+------+------+
 *  Row1 |  2   |  2   |  2   |  2   |
 *       +------+------+------+------+
 *  Row2 |  0   |  0   |  2   |  2   |
 *       +------+------+------+------+
 *  Row3 |  0   |  0   |  0   |  0   |
 *       +------+------+------+------+
 *
 * Queue after Minute 2:
 *     +-----------+
 *     | (2,2)     |   <-- Only element added
 *     +-----------+
 *
 * Minutes incremented to 3.
 *
 * ----------------------------------------------------------------------
 * Minute 3: Process the new queue.
 *
 * Queue at start of Minute 3:
 *     +-----------+
 *     | (2,2)     |   <-- Front & Rear
 *     +-----------+
 *
 * Processing (2,2):
 *   - Check Up: (1,2) → Already rotten.
 *   - Check Down: (3,2) → grid[3][2] = 0 (empty), no change.
 *   - Check Left: (2,1) → grid[2][1] = 0 (empty), no change.
 *   - Check Right: (2,3) → Already rotten.
 *   (No changes.)
 *
 * Queue becomes empty.
 *
 * Minutes incremented to 4.
 *
 * End of BFS:
 * - freshCount is now 0, meaning all fresh oranges have rotted.
 * - We return minutes - 1 because the last minute (from 3 to 4) was an extra increment after processing a level with no new changes.
 * Final Output = 4 - 1 = 3 minutes.
 *
 */

/************************************************************ JAVA ************************************************/

// Approach: We perform a multi-source BFS starting from all initially rotten oranges, rotting adjacent fresh oranges each minute.
// Time Complexity: O(m*n) because every cell is processed at most once.
// Space Complexity: O(m*n) in the worst-case scenario when the queue holds many cell positions.
class Solution {
    public int orangesRotting(int[][] grid) {
        int m = grid.length;
        int n = grid[0].length;
        // Directions represent Up, Down, Left, Right movements.
        int[][] directions = { { -1, 0 }, { 1, 0 }, { 0, -1 }, { 0, 1 } };

        Queue<int[]> que        = new LinkedList<>(); // Queue for BFS.
        int          freshCount = 0;                  // Count of fresh oranges.

        // Enqueue initial rotten oranges and count fresh ones.
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (grid[i][j] == 2) {
                    que.offer(new int[]{ i, j }); // Add rotten orange position.
                } else if (grid[i][j] == 1) {
                    freshCount++;                 // Count fresh orange.
                }
            }
        }

        // If no fresh orange exists, return 0.
        if (freshCount == 0) {
            return 0;
        }

        int minutes = 0;  // Minutes counter for the rotting process.

        // BFS: Process oranges minute by minute.
        while (!que.isEmpty()) {
            int N = que.size();  // Number of oranges to process in this minute.
            for (int i = 0; i < N; i++) {
                int[] curr = que.poll();
                int x = curr[0];
                int y = curr[1];

                // Check all 4 adjacent cells.
                for (int[] dir : directions) {
                    int new_x = x + dir[0];
                    int new_y = y + dir[1];

                    // If within bounds and a fresh orange is found, rot it.
                    if (new_x >= 0 && new_x < m && new_y >= 0 && new_y < n && grid[new_x][new_y] == 1) {
                        // Before update:
                        //   At index (" + new_x + ", " + new_y + "): Fresh orange (1)
                        // After update:
                        //   At index (" + new_x + ", " + new_y + "): Becomes rotten (2)
                        grid[new_x][new_y] = 2;
                        que.offer(new int[]{ new_x, new_y });
                        freshCount--;
                    }
                }
            }
            minutes++;  // Increase the minute counter after processing one level.
        }

        // Return minutes - 1 because the last increment occurs after processing a level with no new rotten oranges.
        return freshCount == 0 ? minutes - 1 : -1;
    }
}

/*
 *
 * Dry Run
 *
 * Consider the input 4x4 matrix with indices and initial values as follows:
 *
 *         Columns
 *           0     1     2     3
 *       +------+------+------+------+
 *  Row0 |  2   |  1   |  1   |  2   |   // (0,0)=2, (0,1)=1, (0,2)=1, (0,3)=2
 *       +------+------+------+------+
 *  Row1 |  1   |  1   |  1   |  1   |   // (1,0)=1, (1,1)=1, (1,2)=1, (1,3)=1
 *       +------+------+------+------+
 *  Row2 |  0   |  0   |  1   |  1   |   // (2,0)=0, (2,1)=0, (2,2)=1, (2,3)=1
 *       +------+------+------+------+
 *  Row3 |  0   |  0   |  0   |  0   |   // (3,0)=0, (3,1)=0, (3,2)=0, (3,3)=0
 *       +------+------+------+------+
 *
 * Initial Setup:
 * - Rotten oranges positions: (0,0) and (0,3).
 * - Fresh oranges positions: (0,1), (0,2), (1,0), (1,1), (1,2), (1,3), (2,2), (2,3).
 *   => freshCount = 8.
 *
 * Initial Queue:
 *     - Front -> (0,0)
 *     - Rear  -> (0,3)
 *
 * ----------------------------------------------------------------------
 * Minute 0: Process all oranges currently in the queue.
 *
 * Queue at start of Minute 0:
 *     +-----------+
 *     | (0,0)     |   <-- Front
 *     +-----------+
 *     | (0,3)     |   <-- Rear
 *     +-----------+
 *
 * Processing (0,0):
 *   - Check Up: ( -1,0 ) → Out of bounds.
 *   - Check Down: (1,0)
 *         Before update: grid[1][0] = 1.
 *         After update:  grid[1][0] becomes 2.
 *         Enqueue (1,0); freshCount becomes 7.
 *         Diagram of change:
 *         Before:
 *           Row1: | 1 | 1 | 1 | 1 |
 *         After:
 *           Row1: | 2 | 1 | 1 | 1 |
 *
 *   - Check Left: (0,-1) → Out of bounds.
 *   - Check Right: (0,1)
 *         Before update: grid[0][1] = 1.
 *         After update:  grid[0][1] becomes 2.
 *         Enqueue (0,1); freshCount becomes 6.
 *         Diagram of change:
 *         Before:
 *           Row0: | 2 | 1 | 1 | 2 |
 *         After:
 *           Row0: | 2 | 2 | 1 | 2 |
 *
 * Processing (0,3):
 *   - Check Up: ( -1,3 ) → Out of bounds.
 *   - Check Down: (1,3)
 *         Before update: grid[1][3] = 1.
 *         After update:  grid[1][3] becomes 2.
 *         Enqueue (1,3); freshCount becomes 5.
 *         Diagram of change:
 *         Before:
 *           Row1: | 2 | 1 | 1 | 1 |   (Note: (1,0) was already updated to 2)
 *         After:
 *           Row1: | 2 | 1 | 1 | 2 |
 *
 *   - Check Left: (0,2)
 *         Before update: grid[0][2] = 1.
 *         After update:  grid[0][2] becomes 2.
 *         Enqueue (0,2); freshCount becomes 4.
 *         Diagram of change:
 *         Before:
 *           Row0: | 2 | 2 | 1 | 2 |
 *         After:
 *           Row0: | 2 | 2 | 2 | 2 |
 *
 *   - Check Right: (0,4) → Out of bounds.
 *
 * Matrix after Minute 0:
 *         Columns
 *           0     1     2     3
 *       +------+------+------+------+
 *  Row0 |  2   |  2   |  2   |  2   |
 *       +------+------+------+------+
 *  Row1 |  2   |  1   |  1   |  2   |
 *       +------+------+------+------+
 *  Row2 |  0   |  0   |  1   |  1   |
 *       +------+------+------+------+
 *  Row3 |  0   |  0   |  0   |  0   |
 *       +------+------+------+------+
 *
 * Queue after Minute 0:
 *         Order in queue:
 *             Front -> (1,0)
 *                      (0,1)
 *                      (1,3)
 *             Rear  -> (0,2)
 *
 * Minutes incremented to 1.
 *
 * ----------------------------------------------------------------------
 * Minute 1: Process the new queue.
 *
 * Queue at start of Minute 1:
 *     +-----------+
 *     | (1,0)     |   <-- Front
 *     +-----------+
 *     | (0,1)     |
 *     +-----------+
 *     | (1,3)     |
 *     +-----------+
 *     | (0,2)     |   <-- Rear
 *     +-----------+
 *
 * Processing (1,0):
 *   - Check Up: (0,0) → Already rotten.
 *   - Check Down: (2,0) → grid[2][0] = 0 (empty), no change.
 *   - Check Left: (1,-1) → Out of bounds.
 *   - Check Right: (1,1)
 *         Before update: grid[1][1] = 1.
 *         After update:  grid[1][1] becomes 2.
 *         Enqueue (1,1); freshCount becomes 3.
 *         Diagram of change:
 *         Before:
 *           Row1: | 2 | 1 | 1 | 2 |
 *         After:
 *           Row1: | 2 | 2 | 1 | 2 |
 *
 * Processing (0,1):
 *   - Check Up: (-1,1) → Out of bounds.
 *   - Check Down: (1,1) → Already rotten (just updated).
 *   - Check Left: (0,0) → Already rotten.
 *   - Check Right: (0,2) → Already rotten.
 *   (No changes.)
 *
 * Processing (1,3):
 *   - Check Up: (0,3) → Already rotten.
 *   - Check Down: (2,3)
 *         Before update: grid[2][3] = 1.
 *         After update:  grid[2][3] becomes 2.
 *         Enqueue (2,3); freshCount becomes 2.
 *         Diagram of change:
 *         Before:
 *           Row2: | 0 | 0 | 1 | 1 |
 *         After:
 *           Row2: | 0 | 0 | 1 | 2 |
 *
 *   - Check Left: (1,2)
 *         Before update: grid[1][2] = 1.
 *         After update:  grid[1][2] becomes 2.
 *         Enqueue (1,2); freshCount becomes 1.
 *         Diagram of change:
 *         Before:
 *           Row1: | 2 | 2 | 1 | 2 |
 *         After:
 *           Row1: | 2 | 2 | 2 | 2 |
 *
 *   - Check Right: (1,4) → Out of bounds.
 *
 * Processing (0,2):
 *   - Check Up: (-1,2) → Out of bounds.
 *   - Check Down: (1,2) → Already rotten (just updated).
 *   - Check Left: (0,1) → Already rotten.
 *   - Check Right: (0,3) → Already rotten.
 *   (No changes.)
 *
 * Matrix after Minute 1:
 *         Columns
 *           0     1     2     3
 *       +------+------+------+------+
 *  Row0 |  2   |  2   |  2   |  2   |
 *       +------+------+------+------+
 *  Row1 |  2   |  2   |  2   |  2   |
 *       +------+------+------+------+
 *  Row2 |  0   |  0   |  1   |  2   |
 *       +------+------+------+------+
 *  Row3 |  0   |  0   |  0   |  0   |
 *       +------+------+------+------+
 *
 * Queue after Minute 1:
 *             Front -> (1,1)
 *                      (2,3)
 *             Rear  -> (1,2)
 *
 * Minutes incremented to 2.
 *
 * ----------------------------------------------------------------------
 * Minute 2: Process the new queue.
 *
 * Queue at start of Minute 2:
 *     +-----------+
 *     | (1,1)     |   <-- Front
 *     +-----------+
 *     | (2,3)     |
 *     +-----------+
 *     | (1,2)     |   <-- Rear
 *     +-----------+
 *
 * Processing (1,1):
 *   - Check Up: (0,1) → Already rotten.
 *   - Check Down: (2,1) → grid[2][1] = 0 (empty), no change.
 *   - Check Left: (1,0) → Already rotten.
 *   - Check Right: (1,2) → Already rotten.
 *   (No changes.)
 *
 * Processing (2,3):
 *   - Check Up: (1,3) → Already rotten.
 *   - Check Down: (3,3) → grid[3][3] = 0 (empty), no change.
 *   - Check Left: (2,2)
 *         Before update: grid[2][2] = 1.
 *         After update:  grid[2][2] becomes 2.
 *         Enqueue (2,2); freshCount becomes 0.
 *         Diagram of change:
 *         Before:
 *           Row2: | 0 | 0 | 1 | 2 |
 *         After:
 *           Row2: | 0 | 0 | 2 | 2 |
 *
 *   - Check Right: (2,4) → Out of bounds.
 *
 * Processing (1,2):
 *   - Check Up: (0,2) → Already rotten.
 *   - Check Down: (2,2) → Already rotten (just updated).
 *   - Check Left: (1,1) → Already rotten.
 *   - Check Right: (1,3) → Already rotten.
 *   (No changes.)
 *
 * Matrix after Minute 2:
 *         Columns
 *           0     1     2     3
 *       +------+------+------+------+
 *  Row0 |  2   |  2   |  2   |  2   |
 *       +------+------+------+------+
 *  Row1 |  2   |  2   |  2   |  2   |
 *       +------+------+------+------+
 *  Row2 |  0   |  0   |  2   |  2   |
 *       +------+------+------+------+
 *  Row3 |  0   |  0   |  0   |  0   |
 *       +------+------+------+------+
 *
 * Queue after Minute 2:
 *     +-----------+
 *     | (2,2)     |   <-- Only element added
 *     +-----------+
 *
 * Minutes incremented to 3.
 *
 * ----------------------------------------------------------------------
 * Minute 3: Process the new queue.
 *
 * Queue at start of Minute 3:
 *     +-----------+
 *     | (2,2)     |   <-- Front & Rear
 *     +-----------+
 *
 * Processing (2,2):
 *   - Check Up: (1,2) → Already rotten.
 *   - Check Down: (3,2) → grid[3][2] = 0 (empty), no change.
 *   - Check Left: (2,1) → grid[2][1] = 0 (empty), no change.
 *   - Check Right: (2,3) → Already rotten.
 *   (No changes.)
 *
 * Queue becomes empty.
 *
 * Minutes incremented to 4.
 *
 * End of BFS:
 * - freshCount is now 0, meaning all fresh oranges have rotted.
 * - We return minutes - 1 because the last minute (from 3 to 4) was an extra increment after processing a level with no new changes.
 * Final Output = 4 - 1 = 3 minutes.
 *
 */
