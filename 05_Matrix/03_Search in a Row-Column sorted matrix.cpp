/*
 * Search in a Row-Column sorted matrix
 *
 * Given a 2D integer matrix mat[][] of size n x m, where every row and column is sorted in increasing order and a number x, the task is to find whether element x is present in the matrix.
 *
 * Examples:
 * Input: mat[][] = [[3, 30, 38],[20, 52, 54],[35, 60, 69]], x = 62
 * Output: false
 * Explanation: 62 is not present in the matrix, so output is false.
 *
 * Input: mat[][] = [[18, 21, 27],[38, 55, 67]], x = 55
 * Output: true
 * Explanation: 55 is present in the matrix.
 *
 * Input: mat[][] = [[1, 2, 3],[4, 5, 6],[7, 8, 9]], x = 3
 * Output: true
 * Explanation: 3 is present in the matrix.
 *
 * Constraints:
 * 1 <= n, m <=1000
 * 1 <= mat[i][j] <= 10^9
 * 1<= x <= 10^9
 */

/************************************************************ C++ ************************************************/

// Approach: Start from the top-right corner and iteratively move left for smaller values or down for larger values until the target is found or boundaries are crossed.
// Time Complexity: O(n + m) (Each row or column is traversed at most once).
// Space Complexity: O(1) (No extra space is used).
class Solution {
public:
   bool matSearch(vector<vector<int> >&mat, int x){
      int n = mat.size();    // Number of rows in the matrix
      int m = mat[0].size(); // Number of columns in the matrix

      int row = 0;           // Start from the top-right corner
      int col = m - 1;       // Top-right column index

      // Traverse the matrix
      while (row < n && col >= 0) {
         if (mat[row][col] == x) {
            return true;      // If the current element matches x, return true
         }

         // If the current element is greater than x, move left
         if (mat[row][col] > x) {
            col--;
         }
         // If the current element is smaller than x, move down
         else {
            row++;
         }
      }

      return false;    // If we exit the loop, x is not found in the matrix
   }
};

/************************************************************ JAVA ************************************************/

// Approach: Start from the top-right corner and iteratively move left for smaller values or down for larger values until the target is found or boundaries are crossed.
// Time Complexity: O(n + m) (Each row or column is traversed at most once).
// Space Complexity: O(1) (No extra space is used).
class Solution {
   public static boolean matSearch(int mat[][], int x){
      int n = mat.length;    // Number of rows in the matrix
      int m = mat[0].length; // Number of columns in the matrix

      int row = 0;           // Start from the top-right corner
      int col = m - 1;       // Column index of the top-right corner

      // Traverse the matrix
      while (row < n && col >= 0) {
         if (mat[row][col] == x) {
            return true;      // If the current element matches x, return true
         }

         // If the current element is greater than x, move left to a smaller element
         if (mat[row][col] > x) {
            col--;
         }
         // If the current element is smaller than x, move down to a larger element
         else {
            row++;
         }
      }

      return false;    // If we exit the loop, x is not found in the matrix
   }
}
