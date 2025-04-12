/*
 * Flood fill Algorithm
 *
 * Difficulty: Medium Accuracy: 41.11% Submissions: 133K+ Points: 4 Average Time: 15m
 *
 * You are given a 2D grid image[][] of size n*m, where each image[i][j] represents the color of a pixel in the image. Also provided a coordinate(sr, sc) representing the starting pixel (row and column) and a new color value newColor.
 *
 * Your task is to perform a flood fill starting from the pixel (sr, sc), changing its color to newColor and the color of all the connected pixels that have the same original color. Two pixels are considered connected if they are adjacent horizontally or vertically (not diagonally) and have the same original color.
 *
 * Examples:
 *
 * Input: image[][] = [[1, 1, 1, 0], [0, 1, 1, 1], [1, 0, 1, 1]], sr = 1, sc = 2, newColor = 2
 * Output: [[2, 2, 2, 0], [0, 2, 2, 2], [1, 0, 2, 2]]
 * Explanation: Starting from pixel (1, 2) with value 1, flood fill updates all connected pixels (up, down, left, right) with value 1 to 2, resulting in [[2, 2, 2, 0], [0, 2, 2, 2], [1, 0, 2, 2]].
 *
 * Input: image[][] = [[1, 1, 1], [1, 1, 0], [1, 0, 1]], sr = 1, sc = 1, newColor = 2
 * Output: [[2, 2, 2], [2, 2, 0], [2, 0, 1]]
 * Explanation: From the center of the image (with position (sr, sc) = (1, 1)), all pixels connected by a path of the same color as the starting pixel are colored with the new color.Note the bottom corner is not colored 2, because it is not 4-directionally connected to the starting pixel.
 *
 * Input: image[][] = [[0, 1, 0], [0, 1, 0]], sr = 0, sc = 1, newColor = 0
 * Output: [[0, 0, 0], [0, 0, 0]]
 * Explanation: Starting from pixel (0, 1) with value 1, flood fill changes all 4-directionally connected pixels with value 1 to 0, resulting in [[0, 0, 0], [0, 0, 0]]
 *
 * Constraints:
 * 1 ≤ n ≤ m ≤ 500
 * 0 ≤ image[i][j] ≤ 10
 * 0 ≤ newColor ≤ 10
 * 0 ≤ sr ≤ (n-1)
 * 0 ≤ sc ≤ (m-1)
 */

/* Flood fill Algorithm
 *
 *               Columns
 *           0       1      2
 *        +------+------+------+
 *      0 |   1  |  1   |  1   |
 *        +------+------+------+
 *      1 |  1   |  1   |  0   |
 *        +------+------+------+
 *      2 |  1   |  0   |  1   |
 *        +------+------+------+
 *
 * This matrix can be filled with any number (for example, 1, 2, 3...).
 *
 * sr = 1 (starting row)
 * sc = 1 (starting column)
 * newColor = 2
 *
 * So, at (1, 1) in the matrix the initial color is 1; we change it to 2 (newColor).
 *
 * Its 4 neighbors are:
 * (0, 1), (1, 0), (1, 2), and (2, 1)
 *
 * Among them, only (0, 1) and (1, 0) have the color 1.
 *
 * So we can update them, making them 2 (newColor).
 *
 *               Columns
 *           0       1      2
 *        +------+------+------+
 *      0 |   1  |  2   |  1   |
 *        +------+------+------+
 *      1 |  2   |  2   |  0   |
 *        +------+------+------+
 *      2 |  1   |  0   |  1   |
 *        +------+------+------+
 *
 * Now do the same for (1, 0):
 * Color among its 4 neighbors that are 1.
 *
 *               Columns
 *           0       1      2
 *        +------+------+------+
 *      0 |  2   |  2   |  1   |
 *        +------+------+------+
 *      1 |  2   |  2   |  0   |
 *        +------+------+------+
 *      2 |  2   |  0   |  1   |
 *        +------+------+------+
 *
 * Now do the same for (0, 1):
 * Color among its 4 neighbors that are 1.
 *
 *               Columns
 *           0       1      2
 *        +------+------+------+
 *      0 |  2   |  2   |  2   |
 *        +------+------+------+
 *      1 |  2   |  2   |  0   |
 *        +------+------+------+
 *      2 |  2   |  0   |  1   |
 *        +------+------+------+
 *
 * This will be the final matrix for the first example.
 *
 * --------------------------------------------------
 * Now, let's take one more example
 *
 *               Columns
 *           0       1      2
 *        +------+------+------+
 *      0 |  1   |  1   |  1   |
 *        +------+------+------+
 *      1 |  2   |  2   |  0   |
 *        +------+------+------+
 *      2 |  2   |  2   |  2   |
 *        +------+------+------+
 *
 * Parameters:
 * sr = 2 (starting row)
 * sc = 0 (starting column)
 * newColor = 3
 *
 * So, at (2, 0) the initial color is 2; change it to 3 (newColor),
 * and its 4 neighbors (which are also 2) will be colored.
 *
 *               Columns
 *           0       1      2
 *        +------+------+------+
 *      0 |  1   |  1   |  1   |
 *        +------+------+------+
 *      1 |  3   |  2   |  0   |
 *        +------+------+------+
 *      2 |  3   |  3   |  2   |
 *        +------+------+------+
 *
 * Now, for (1, 0) only (1, 1) is 2 so make it 3.
 *
 *               Columns
 *           0       1      2
 *        +------+------+------+
 *      0 |  1   |  1   |  1   |
 *        +------+------+------+
 *      1 |  3   |  3   |  0   |
 *        +------+------+------+
 *      2 |  3   |  3   |  2   |
 *        +------+------+------+
 *
 * Now, for (2, 1) only (2, 2) is 2 so make it 3.
 *
 *               Columns
 *           0       1      2
 *        +------+------+------+
 *      0 |  1   |  1   |  1   |
 *        +------+------+------+
 *      1 |  3   |  3   |  0   |
 *        +------+------+------+
 *      2 |  3   |  3   |  3   |
 *        +------+------+------+
 *
 * This is the final matrix for the second example.
 *
 * So, this is how you can flood fill.
 *
 * ---------------------------------------------------------------------------
 *
 * So now, how do we achieve this?
 *
 * Consider the initial matrix for flood fill:
 *
 *               Columns
 *           0       1      2
 *        +------+------+------+
 *      0 |  1   |  1   |  1   |
 *        +------+------+------+
 *      1 |  2   |  2   |  0   |
 *        +------+------+------+
 *      2 |  2   |  2   |  2   |
 *        +------+------+------+
 *
 * Parameters:
 * sr = 2 (starting row)
 * sc = 0 (starting column)
 * newColor = 3
 *
 * We can use either BFS or DFS; here, we choose DFS.
 *
 * To avoid modifying the given matrix, first create a copy (new_copy):
 *
 *               Columns
 *           0       1      2
 *        +------+------+------+
 *      0 |  1   |  1   |  1   |
 *        +------+------+------+
 *      1 |  2   |  2   |  0   |
 *        +------+------+------+
 *      2 |  2   |  2   |  2   |
 *        +------+------+------+
 *              (new_copy)
 *
 * Now, perform DFS starting from pixel (2, 0):
 *
 * DFS(2, 0)
 *
 *               Columns
 *           0       1      2
 *        +------+------+------+
 *      0 |  1   |  1   |  1   |
 *        +------+------+------+
 *      1 |  2   |  2   |  0   |
 *        +------+------+------+
 *      2 |  3   |  2   |  2   |
 *        +------+------+------+
 *
 * Explanation:
 * - The DFS call begins at (2, 0) in the new_copy, and the color changes from 2 to 3.
 *
 * Then the DFS branches from (2, 0) to its neighboring pixels:
 *
 *             DFS(2, 0)
 *             /       \
 *            /         \
 *       DFS(1, 0)      DFS(2, 1)
 *
 * Explanation:
 * - From (2, 0), DFS recursively visits its adjacent pixels that have the original color 2.
 * - It branches into two recursive calls: one for pixel (1, 0) (moving up) and one for pixel (2, 1) (moving right).
 *
 * So, it will go to (1, 0) next:
 *
 *               Columns
 *           0       1      2
 *        +------+------+------+
 *      0 |  1   |  1   |  1   |
 *        +------+------+------+
 *      1 |  3   |  2   |  0   |
 *        +------+------+------+
 *      2 |  3   |  2   |  2   |
 *        +------+------+------+
 *
 * Explanation:
 * - The pixel (1, 0) is updated to 3 by DFS.
 *
 * Now, from (1, 0), DFS processes its neighbors:
 *
 *                    DFS(2, 0)
 *                   /       \
 *                  /         \
 *              DFS(1, 0)      DFS(2, 1)
 *               /
 *              /
 *          DFS(1, 1)
 *
 * Explanation:
 * - From pixel (1, 0), DFS further recurses into (1, 1) because it is connected and has the original color 2.
 * - Pixel (1, 1) is updated to 3.
 *
 * Matrix after processing DFS(1, 1):
 *
 *               Columns
 *           0       1      2
 *        +------+------+------+
 *      0 |  1   |  1   |  1   |
 *        +------+------+------+
 *      1 |  3   |  3   |  0   |
 *        +------+------+------+
 *      2 |  3   |  2   |  2   |
 *        +------+------+------+
 *
 * Next, DFS from (2, 0) continues with DFS(2, 1):
 *
 *                      DFS(2, 0)
 *                      /       \
 *                     /         \
 *                 DFS(1, 0)      DFS(2, 1)
 *                   /
 *                 /
 *             DFS(1, 1)
 *               /
 *             /
 *           DFS(2, 1)
 *
 * Explanation:
 * - The DFS call now processes (2, 1), updating it to 3 if it has not already been processed.
 * - After updating (2, 1), the matrix now becomes:
 *
 *               Columns
 *           0       1      2
 *        +------+------+------+
 *      0 |  1   |  1   |  1   |
 *        +------+------+------+
 *      1 |  3   |  3   |  0   |
 *        +------+------+------+
 *      2 |  3   |  3   |  2   |
 *        +------+------+------+
 *
 * Then, DFS from (2, 1) recurses to its neighbor (2, 2):
 *
 *                        DFS(2, 0)
 *                        /       \
 *                       /         \
 *                   DFS(1, 0)      DFS(2, 1)
 *                     /
 *                    /
 *                DFS(1, 1)
 *                  /
 *                 /
 *              DFS(2, 1)
 *               /
 *              /
 *          DFS(2, 2)
 *
 * Explanation:
 * - The DFS call reaches (2, 2) and updates its value from 2 to 3.
 * - At this point, the matrix becomes:
 *
 *               Columns
 *           0       1      2
 *        +------+------+------+
 *      0 |  1   |  1   |  1   |
 *        +------+------+------+
 *      1 |  3   |  3   |  0   |
 *        +------+------+------+
 *      2 |  3   |  3   |  3   |
 *        +------+------+------+
 *
 * Then the recursion unwinds:
 *
 *                        DFS(2, 0)
 *                       / /      \
 *                      / /        \
 *                  DFS(1, 0)      DFS(2, 1) {this is already visited}
 *                    / /
 *                   / /
 *               DFS(1, 1)
 *                 / /
 *                / /
 *            DFS(2, 1)
 *              / /
 *             / /
 *         DFS(2, 2)
 *
 * Explanation:
 * - This DFS tree diagram shows the sequence and branching of the recursive DFS calls.
 * - Starting at (2, 0), the DFS branches to (1, 0) and (2, 1); then from (1, 0), it further recurses to (1, 1); and finally, from (2, 1), it recurses to (2, 2).
 * - Once all recursive calls complete, all 4-directionally connected pixels that had the original color 2 are updated to 3.
 *
 * Final Matrix after DFS Flood Fill:
 *
 *               Columns
 *           0       1      2
 *        +------+------+------+
 *      0 |  1   |  1   |  1   |
 *        +------+------+------+
 *      1 |  3   |  3   |  0   |
 *        +------+------+------+
 *      2 |  3   |  3   |  3   |
 *        +------+------+------+
 *
 * Overall Explanation:
 * - Flood fill is an algorithm that changes the color of a starting pixel and all 4-directionally connected pixels that share the same original color.
 * - In the first example, starting from (1, 1) with the color 1, flood fill updates that pixel and its connected neighbors with 1 to 2.
 * - In the second example, starting from (2, 0) with the color 2, the flood fill (using DFS) propagates through all connected pixels with the value 2, updating them to 3.
 * - The DFS tree diagram above illustrates the order of recursive calls:
 *     • DFS(2, 0) is the starting call.
 *     • It branches into DFS(1, 0) and DFS(2, 1).
 *     • From DFS(1, 0), the call further recurses to DFS(1, 1).
 *     • Finally, DFS(2, 1) recurses into DFS(2, 2).
 * - Each subsequent matrix representation shows the updated state of the image after the corresponding DFS calls.
 * - This detailed explanation, with both the DFS tree diagram and the step-by-step matrix updates, visually demonstrates how the flood fill algorithm operates using DFS.
 */

/************************************************************ C++ ************************************************/

// Approach: Use DFS to recursively fill all 4-directionally connected pixels of the same initial color with the new color
// Time Complexity: O(m * n) where m = number of rows and n = number of columns, in worst-case all pixels are visited
// Space Complexity: O(m * n) for the 'ans' matrix + recursion stack in worst case
class Solution {
public:
    // DFS function to fill the connected region
    void DFS(int row, int col,
             vector<vector<int>>& ans,
             vector<vector<int>>& image,
             int newColor, int directions[][2], int iniColor) {
        ans[row][col] = newColor;              // Update the pixel with new color

        int m = image.size();                  // Total number of rows
        int n = image[0].size();               // Total number of columns

        for (int i = 0; i < 4; i++) {          // Loop over the 4 directions (up, right, down, left)
            int nRow = row + directions[i][0]; // Calculate new row
            int nCol = col + directions[i][1]; // Calculate new column

            // Check for valid pixel and if the color matches the original and hasn't been changed yet
            if (nRow >= 0 && nRow < m &&
                nCol >= 0 && nCol < n &&
                image[nRow][nCol] == iniColor && ans[nRow][nCol] != newColor) {
                DFS(nRow, nCol, ans, image, newColor, directions, iniColor);   // Recursive DFS call
            }
        }
    }

    vector<vector<int>> floodFill(vector<vector<int>>& image, int sr, int sc, int newColor) {
        int iniColor = image[sr][sc];   // Get the initial color at starting pixel

        if (iniColor == newColor) {
            return image;   // If initial color is already newColor, return original image
        }

        vector<vector<int>> ans = image; // Copy original image to avoid modifying it
        int directions[4][2]     = {
            { -1, 0 },                    // Up
            {  0, 1 },                    // Right
            {  1, 0 },                    // Down
            {  0,-1 }                     // Left
        };

        DFS(sr, sc, ans, image, newColor, directions, iniColor); // Start DFS from the source
        return ans;                                              // Return the filled image
    }
};

/*
 *
 * Dry Run
 *
 * Input: image = {
 *  {1, 1, 1},
 *  {1, 1, 0},
 *  {1, 0, 1}
 *}, sr = 1, sc = 1, newColor = 2
 *
 * Initial color at (1,1) is 1
 *
 * DFS starts at (1,1) -> change it to 2
 *
 * Neighbors of (1,1): (0,1), (1,0) are 1 -> DFS to them
 *
 *(0,1) -> change to 2 -> check its neighbors
 *  -> (0,0) is 1 -> change to 2
 *  -> (0,2) is 1 -> change to 2
 *
 *(1,0) -> change to 2 -> (2,0) is 1 -> change to 2
 *
 * Final matrix:
 *  {2, 2, 2}
 *  {2, 2, 0}
 *  {2, 0, 1}
 *
 */

/************************************************************ JAVA ************************************************/

// Approach: Use DFS to recursively fill all 4-directionally connected pixels of the same initial color with the new color
// Time Complexity: O(m * n) where m = number of rows and n = number of columns, in worst-case all pixels are visited
// Space Complexity: O(m * n) for the 'ans' matrix + recursion stack in worst case
class Solution {
    // DFS function to fill the connected region
    public void DFS(int row, int col,
                    int[][] ans,
                    int[][] image,
                    int newColor, int[][] directions, int iniColor) {
        ans[row][col] = newColor;              // Update the pixel with new color

        int m = image.length;                  // Total number of rows
        int n = image[0].length;               // Total number of columns

        for (int i = 0; i < 4; i++) {          // Loop over the 4 directions (up, right, down, left)
            int nRow = row + directions[i][0]; // Calculate new row
            int nCol = col + directions[i][1]; // Calculate new column

            // Check for valid pixel and if the color matches the original and hasn't been changed yet
            if (nRow >= 0 && nRow < m &&
                nCol >= 0 && nCol < n &&
                image[nRow][nCol] == iniColor && ans[nRow][nCol] != newColor) {
                DFS(nRow, nCol, ans, image, newColor, directions, iniColor); // Recursive DFS call
            }
        }
    }
    
    public int[][] floodFill(int[][] image, int sr, int sc, int newColor) {
        int iniColor = image[sr][sc];  // Get the initial color at starting pixel

        if (iniColor == newColor) {
            return image;             // If initial color is already newColor, return original image
        }

        int[][] ans = new int[image.length][image[0].length]; // Create a copy of original image
        for (int i = 0; i < image.length; i++) {
            for (int j = 0; j < image[0].length; j++) {
                ans[i][j] = image[i][j];
            }
        }

        int[][] directions = {
            { -1, 0 }, // Up
            {  0, 1 }, // Right
            {  1, 0 }, // Down
            {  0,-1 } // Left
        };

        DFS(sr, sc, ans, image, newColor, directions, iniColor); // Start DFS from the source
        return ans;                                              // Return the filled image
    }
}

/*
 *
 * Dry Run
 *
 * Input: image = {
 *  {1, 1, 1},
 *  {1, 1, 0},
 *  {1, 0, 1}
 *}, sr = 1, sc = 1, newColor = 2
 *
 * Initial color at (1,1) is 1
 *
 * DFS starts at (1,1) -> change it to 2
 *
 * Neighbors of (1,1): (0,1), (1,0) are 1 -> DFS to them
 *
 *(0,1) -> change to 2 -> check its neighbors
 *  -> (0,0) is 1 -> change to 2
 *  -> (0,2) is 1 -> change to 2
 *
 *(1,0) -> change to 2 -> (2,0) is 1 -> change to 2
 *
 * Final matrix:
 *  {2, 2, 2}
 *  {2, 2, 0}
 *  {2, 0, 1}
 *
 */
