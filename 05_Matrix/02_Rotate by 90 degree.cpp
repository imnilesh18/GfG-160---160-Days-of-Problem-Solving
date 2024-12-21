/*
 * Rotate by 90 degree
 *
 * Given a square matrix mat[][] of size n x n. The task is to rotate it by 90 degrees in an anti-clockwise direction without using any extra space.
 *
 * Examples:
 *
 * Input: mat[][] = [[1, 2, 3],
 *              [4, 5, 6]
 *              [7, 8, 9]]
 * Output: Rotated Matrix:
 * [3, 6, 9]
 * [2, 5, 8]
 * [1, 4, 7]
 *
 * Input: mat[][] = [[1, 2],
 *              [3, 4]]
 * Output: Rotated Matrix:
 * [2, 4]
 * [1, 3]
 *
 * Constraints:
 * 1 ≤ n ≤ 10^2
 * 0 <= mat[i][j] <= 10^3
 */

/************************************************************ C++ ************************************************/

// Approach: Transpose the matrix, then reverse each column.
// Time Complexity: O(N²) (transposing and reversing columns both take O(N²) for an N×N matrix).
// Space Complexity: O(1) (in-place modification of the matrix).
class Solution {
public:
   // Function to rotate the matrix anti-clockwise by 90 degrees.
   void rotateby90(vector<vector<int> >& mat){
      int n = mat.size();

      // Step 1: Transpose the matrix
      for (int i = 0; i < n; i++) {
         for (int j = i + 1; j < n; j++) {
            swap(mat[i][j], mat[j][i]);
         }
      }

      // Step 2: Reverse each column manually
      for (int j = 0; j < n; j++) {
         int top = 0, bottom = n - 1;
         while (top < bottom) {
            swap(mat[top][j], mat[bottom][j]);
            top++;
            bottom--;
         }
      }
   }
};

/************************************************************ JAVA ************************************************/

// Approach: Transpose the matrix, then reverse each column.
// Time Complexity: O(N²) (transposing and reversing columns both take O(N²) for an N×N matrix).
// Space Complexity: O(1) (in-place modification of the matrix).
class Solution {
   // Function to rotate the matrix anti-clockwise by 90 degrees.
   static void rotateby90(int mat[][]){
      int n = mat.length;

      // Step 1: Transpose the matrix
      for (int i = 0; i < n; i++) {
         for (int j = i + 1; j < n; j++) {
            int temp = mat[i][j];
            mat[i][j] = mat[j][i];
            mat[j][i] = temp;
         }
      }

      // Step 2: Reverse each column
      for (int j = 0; j < n; j++) {
         int top = 0, bottom = n - 1;
         while (top < bottom) {
            int temp = mat[top][j];
            mat[top][j]    = mat[bottom][j];
            mat[bottom][j] = temp;
            top++;
            bottom--;
         }
      }
   }
}
