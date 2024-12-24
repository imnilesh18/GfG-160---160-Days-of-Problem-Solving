/*
 * Set Matrix Zeroes
 *
 * You are given a 2D matrix mat[][] of size n×m. The task is to modify the matrix such that if mat[i][j] is 0, all the elements in the i-th row and j-th column are set to 0 and do it in constant space complexity.
 *
 * Examples:
 *
 * Input: mat[][] = [[1, -1, 1],
 *              [-1, 0, 1],
 *              [1, -1, 1]]
 * Output: [[1, 0, 1],
 *      [0, 0, 0],
 *      [1, 0, 1]]
 * Explanation: mat[1][1] = 0, so all elements in row 1 and column 1 are updated to zeroes.
 *
 * Input: mat[][] = [[0, 1, 2, 0],
 *              [3, 4, 5, 2],
 *              [1, 3, 1, 5]]
 * Output: [[0, 0, 0, 0],
 *      [0, 4, 5, 0],
 *      [0, 3, 1, 0]]
 * Explanation: mat[0][0] and mat[0][3] are 0s, so all elements in row 0, column 0 and column 3 are updated to zeroes.
 *
 * Constraints:
 * 1 ≤ n, m ≤ 500
 * - 2^31 ≤ mat[i][j] ≤ 2^31 - 1
 */

/************************************************************ C++ ************************************************/

// Brute Force: TLE also it will not work if the matrix contains -1.
// Approach 1: Traverse the matrix to find zeros, marking corresponding rows and columns with a placeholder (-1), then convert all -1 to 0 in a second traversal.
// Time Complexity: O(n³) - For each zero, marking rows and columns requires O(n + m), resulting in cubic complexity in the worst case.
// Space Complexity: O(1) - Operates directly on the input matrix without additional space usage.
class Solution {
public:

   // Function to mark all non-zero elements in the given row as a placeholder (-1).
   void markRow(vector<vector<int> >&mat, int n, int m, int i){
      for (int j = 0; j < m; j++) {
         // Only mark elements that are not already zero
         if (mat[i][j] != 0) {
            mat[i][j] = -1;     // Placeholder to indicate this needs to be set to 0 later
         }
      }
   }

   // Function to mark all non-zero elements in the given column as a placeholder (-1).
   void markCol(vector<vector<int> >&mat, int n, int m, int j){
      for (int i = 0; i < n; i++) {
         // Only mark elements that are not already zero
         if (mat[i][j] != 0) {
            mat[i][j] = -1;     // Placeholder to indicate this needs to be set to 0 later
         }
      }
   }

   // Main function to set matrix zeroes based on the problem requirements.
   void setMatrixZeroes(vector<vector<int> >&mat){
      int n = mat.size();       // Number of rows in the matrix
      int m = mat[0].size();    // Number of columns in the matrix

      // First pass: Identify rows and columns that need to be zeroed.
      for (int i = 0; i < n; i++) {
         for (int j = 0; j < m; j++) {
            // If the current element is zero, mark its row and column
            if (mat[i][j] == 0) {
               markRow(mat, n, m, i);      // Mark all non-zero elements in the row as placeholders
               markCol(mat, n, m, j);      // Mark all non-zero elements in the column as placeholders
            }
         }
      }

      // Second pass: Replace all placeholders (-1) with zeroes.
      for (int i = 0; i < n; i++) {
         for (int j = 0; j < m; j++) {
            // If the current element is a placeholder, set it to zero
            if (mat[i][j] == -1) {
               mat[i][j] = 0;
            }
         }
      }
   }
};

// Approach 2: Traverse the matrix twice; first, mark rows and columns that need to be zeroed, then update the matrix based on the marked rows and columns.
// Time Complexity: O(n * m) — Two passes over the matrix, each taking O(n * m) time.
// Space Complexity: O(n + m) — Extra space used for row[] and col[] arrays of size n and m respectively.

// Step 1: We traverse the matrix to find cells that have a value of 0 and mark the corresponding row and column as needing to be zeroed out.
// Step 2: We then traverse the matrix again, and for each cell, we check the row and column markers (row[] and col[]) to decide whether we need to set the cell to 0.
class Solution {
public:
   // Function to set entire row and column to 0 if any element is 0
   void setMatrixZeroes(vector<vector<int> >&mat){
      int n = mat.size();    // Get the number of rows in the matrix
      int m = mat[0].size(); // Get the number of columns in the matrix

      // Create two arrays (rows and columns) to mark which rows and columns need to be set to 0
      int col[m] = { 0 }; // Array to mark columns
      int row[n] = { 0 }; // Array to mark rows

      // Traverse the matrix to find all elements equal to 0
      // Mark corresponding row and column in the row[] and col[] arrays
      for (int i = 0; i < n; i++) {
         for (int j = 0; j < m; j++) {
            if (mat[i][j] == 0) {
               row[i] = 1;      // Mark the row to be set to 0
               col[j] = 1;      // Mark the column to be set to 0
            }
         }
      }

      // Traverse the matrix again to set the entire row and column to 0
      // if the corresponding row[] or col[] element is marked
      for (int i = 0; i < n; i++) {
         for (int j = 0; j < m; j++) {
            if (row[i] || col[j]) {    // If row[i] or col[j] is 1, set mat[i][j] to 0
               mat[i][j] = 0;
            }
         }
      }
   }
};

/************************************************************ JAVA ************************************************/

// Brute Force: TLE also it will not work if the matrix contains -1.
// Approach 1: Traverse the matrix to find zeros, marking corresponding rows and columns with a placeholder (-1), then convert all -1 to 0 in a second traversal.
// Time Complexity: O(n³) - For each zero, marking rows and columns requires O(n + m), resulting in cubic complexity in the worst case.
// Space Complexity: O(1) - Operates directly on the input matrix without additional space usage.
class Solution {
   // Function to mark all non-zero elements in the given row as a placeholder (-1).
   public void markRow(int[][] mat, int n, int m, int i){
      for (int j = 0; j < m; j++) {
         // Only mark elements that are not already zero
         if (mat[i][j] != 0) {
            mat[i][j] = -1;     // Placeholder to indicate this needs to be set to 0 later
         }
      }
   }

   // Function to mark all non-zero elements in the given column as a placeholder (-1).
   public void markCol(int[][] mat, int n, int m, int j){
      for (int i = 0; i < n; i++) {
         // Only mark elements that are not already zero
         if (mat[i][j] != 0) {
            mat[i][j] = -1;     // Placeholder to indicate this needs to be set to 0 later
         }
      }
   }

   // Main function to set matrix zeroes based on the problem requirements.
   public void setMatrixZeroes(int[][] mat){
      int n = mat.length;    // Number of rows in the matrix
      int m = mat[0].length; // Number of columns in the matrix

      // First pass: Identify rows and columns that need to be zeroed.
      for (int i = 0; i < n; i++) {
         for (int j = 0; j < m; j++) {
            // If the current element is zero, mark its row and column
            if (mat[i][j] == 0) {
               markRow(mat, n, m, i);      // Mark all non-zero elements in the row as placeholders
               markCol(mat, n, m, j);      // Mark all non-zero elements in the column as placeholders
            }
         }
      }

      // Second pass: Replace all placeholders (-1) with zeroes.
      for (int i = 0; i < n; i++) {
         for (int j = 0; j < m; j++) {
            // If the current element is a placeholder, set it to zero
            if (mat[i][j] == -1) {
               mat[i][j] = 0;
            }
         }
      }
   }
}

// Approach 2: Traverse the matrix twice; first, mark rows and columns that need to be zeroed, then update the matrix based on the marked rows and columns.
// Time Complexity: O(n * m) — Two passes over the matrix, each taking O(n * m) time.
// Space Complexity: O(n + m) — Extra space used for row[] and col[] arrays of size n and m respectively.

// Step 1: We traverse the matrix to find cells that have a value of 0 and mark the corresponding row and column as needing to be zeroed out.
// Step 2: We then traverse the matrix again, and for each cell, we check the row and column markers (row[] and col[]) to decide whether we need to set the cell to 0.
class Solution {
   public void setMatrixZeroes(int[][] mat){
      int n = mat.length;
      int m = mat[0].length;

      int[] col = new int[m];   // Array to mark columns that need to be zeroed
      int[] row = new int[n];   // Array to mark rows that need to be zeroed

      // Traverse the matrix to find zeros and mark corresponding rows and columns
      for (int i = 0; i < n; i++) {
         for (int j = 0; j < m; j++) {
            if (mat[i][j] == 0) {
               row[i] = 1;      // Mark row i for zeroing
               col[j] = 1;      // Mark column j for zeroing
            }
         }
      }

      // Traverse the matrix again to set elements to zero based on row[] and col[] markings
      for (int i = 0; i < n; i++) {
         for (int j = 0; j < m; j++) {
            if (row[i] == 1 || col[j] == 1) {
               mat[i][j] = 0;      // Set the element to zero if its row or column is marked
            }
         }
      }
   }
}
