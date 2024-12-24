/*
 * Search in a sorted Matrix
 *
 * Given a strictly sorted 2D matrix mat[][] of size n x m and a number x.
 * Find whether the number x is present in the matrix or not.
 *
 * Note: In a strictly sorted matrix:
 * - Each row is sorted in strictly increasing order.
 * - The first element of the ith row (i != 0) is greater than the last element of the (i-1)th row.
 *
 * Examples:
 *
 * Input: mat[][] = [[1, 5, 9], [14, 20, 21], [30, 34, 43]], x = 14
 * Output: true
 * Explanation: 14 is present in the matrix, so output is true.
 *
 * Input: mat[][] = [[1, 5, 9, 11], [14, 20, 21, 26], [30, 34, 43, 50]], x = 42
 * Output: false
 * Explanation: 42 is not present in the matrix.
 *
 * Input: mat[][] = [[87, 96, 99], [101, 103, 111]], x = 101
 * Output: true
 * Explanation: 101 is present in the matrix.
 *
 * Constraints:
 * 1 <= n, m <= 1000
 * 1 <= mat[i][j] <= 10^9
 * 1 <= x <= 10^9
 */

/************************************************************ C++ ************************************************/

// Approach: Treat the 2D matrix as a 1D array and apply binary search. Calculate the row index as row = mid / columns and column index as col = mid % columns. Compare mat[row][col] with x, and adjust the search range (left, right) accordingly.
// Time Complexity: O(log(n * m)), where n is the number of rows and m is the number of columns. Binary search reduces the search space logarithmically.
// Space Complexity: O(1), as no additional data structures are used.
class Solution {
public:
   // Function to search a given number in a strictly sorted matrix.
   bool searchMatrix(vector<vector<int> >&mat, int x){
      int n = mat.size();           // Number of rows in the matrix.
      int m = mat[0].size();        // Number of columns in the matrix.

      int left  = 0;                // Start index of the "flattened" matrix.
      int right = m * n - 1;        // End index of the "flattened" matrix.

      // Binary search to find the element.
      while (left <= right) {
         int mid = left + (right - left) / 2;    // Midpoint index in the 1D representation.

         // Convert the 1D index to a 2D row and column:
         // Row = mid / number of columns.
         int row = mid / m;

         // Column = mid % number of columns.
         int col = mid % m;

         // Compare the current element with the target x.
         if (mat[row][col] == x) {
            return true;     // Element found.
         } else if (mat[row][col] < x) {
            left = mid + 1;  // Move to the right half.
         } else {
            right = mid - 1; // Move to the left half.
         }
      }
      return false;   // Element not found.
   }
};

/*
 * Explanation of 1D to 2D conversion:
 *
 * Given a 2D matrix with `n` rows and `m` columns, the total number of elements is `n * m`.
 * Each element in this 2D matrix can be indexed as if it were in a 1D array.
 *
 * To convert an index in the 1D representation (let's call it `mid`) into 2D indices:
 * - Row index = mid / m (integer division by the number of columns).
 * - Column index = mid % m (remainder when divided by the number of columns).
 *
 * Example:
 * Matrix: [[1, 5, 9],
 *          [14, 20, 21],
 *          [30, 34, 43]]
 *
 * Index 4 in the 1D representation corresponds to:
 * - Row = 4 / 3 = 1
 * - Column = 4 % 3 = 1
 * So, mat[1][1] = 20.
 */

/************************************************************ JAVA ************************************************/

// Approach: Treat the 2D matrix as a 1D array and apply binary search. Calculate the row index as row = mid / columns and column index as col = mid % columns. Compare mat[row][col] with x, and adjust the search range (left, right) accordingly.
// Time Complexity: O(log(n * m)), where n is the number of rows and m is the number of columns. Binary search reduces the search space logarithmically.
// Space Complexity: O(1), as no additional data structures are used.
class Solution {
   // Function to search a given number in row-column sorted matrix.
   public boolean searchMatrix(int[][] mat, int x){
      int n = mat.length;            // Number of rows in the matrix.
      int m = mat[0].length;         // Number of columns in the matrix.

      int left  = 0;                 // Start index of the "flattened" matrix.
      int right = n * m - 1;         // End index of the "flattened" matrix.

      // Binary search to find the element.
      while (left <= right) {
         int mid = left + (right - left) / 2;     // Midpoint index in the 1D representation.

         // Convert the 1D index to a 2D row and column:
         // Row = mid / number of columns.
         int row = mid / m;

         // Column = mid % number of columns.
         int col = mid % m;

         // Compare the current element with the target x.
         if (mat[row][col] == x) {
            return true;             // Element found.
         } else if (mat[row][col] < x) {
            left = mid + 1;          // Move to the right half.
         } else {
            right = mid - 1;         // Move to the left half.
         }
      }
      return false;                  // Element not found.
   }
}

/*
 * Explanation of 1D to 2D conversion:
 *
 * Given a 2D matrix with `n` rows and `m` columns, the total number of elements is `n * m`.
 * Each element in this 2D matrix can be indexed as if it were in a 1D array.
 *
 * To convert an index in the 1D representation (let's call it `mid`) into 2D indices:
 * - Row index = mid / m (integer division by the number of columns).
 * - Column index = mid % m (remainder when divided by the number of columns).
 *
 * Example:
 * Matrix: [[1, 5, 9],
 *          [14, 20, 21],
 *          [30, 34, 43]]
 *
 * Index 4 in the 1D representation corresponds to:
 * - Row = 4 / 3 = 1
 * - Column = 4 % 3 = 1
 * So, mat[1][1] = 20.
 */
