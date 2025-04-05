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

class Solution {
public:
    // Function to check whether a cell can be visited
    bool isSafe(vector<vector<char> >& grid, int r, int c, vector<vector<bool> >& visited) {
        int row = grid.size();
        int col = grid[0].size();

        return (r >= 0) && (r < row) &&
               (c >= 0) && (c < col) &&
               (grid[r][c] == 'L' && !visited[r][c]);
    }
    // DFS function to explore all connected land cells
    void dfs(vector<vector<char> >& grid, int r, int c, vector<vector<bool> >& visited) {
        vector<int> rNbr = { -1, -1, -1, 0, 0, 1, 1, 1 };
        vector<int> cNbr = { -1, 0, 1, -1, 1, -1, 0, 1 };

        visited[r][c] = true;

        for (int k = 0; k < 8; ++k) {
            int newR = r + rNbr[k];
            int newC = c + cNbr[k];
            if (isSafe(grid, newR, newC, visited)) {
                dfs(grid, newR, newC, visited);
            }
        }
    }
    // Main function to count number of islands
    int countIslands(vector<vector<char> >& grid) {
        int row = grid.size();
        int col = grid[0].size();

        vector<vector<bool> > visited(row, vector<bool>(col, false));
        int count = 0;

        for (int r = 0; r < row; ++r) {
            for (int c = 0; c < col; ++c) {
                if (grid[r][c] == 'L' && !visited[r][c]) {
                    dfs(grid, r, c, visited);
                    ++count;
                }
            }
        }
        return count;
    }
};

/************************************************************ JAVA ************************************************/

class Solution {
    public int countIslands(char[][] grid) {
        int row = grid.length;
        int col = grid[0].length;

        boolean[][] visited = new boolean[row][col];
        int count = 0;

        for (int r = 0; r < row; ++r) {
            for (int c = 0; c < col; ++c) {
                if (grid[r][c] == 'L' && !visited[r][c]) {
                    dfs(grid, r, c, visited);
                    ++count;
                }
            }
        }
        return count;
    }
    private boolean isSafe(char[][] grid, int r, int c, boolean[][] visited) {
        int row = grid.length;
        int col = grid[0].length;

        return (r >= 0) && (r < row) &&
               (c >= 0) && (c < col) &&
               (grid[r][c] == 'L' && !visited[r][c]);
    }
    private void dfs(char[][] grid, int r, int c, boolean[][] visited) {
        int[] rNbr = { -1, -1, -1, 0, 0, 1, 1, 1 };
        int[] cNbr = { -1, 0, 1, -1, 1, -1, 0, 1 };

        visited[r][c] = true;

        for (int k = 0; k < 8; ++k) {
            int newR = r + rNbr[k];
            int newC = c + cNbr[k];
            if (isSafe(grid, newR, newC, visited)) {
                dfs(grid, newR, newC, visited);
            }
        }
    }
}
