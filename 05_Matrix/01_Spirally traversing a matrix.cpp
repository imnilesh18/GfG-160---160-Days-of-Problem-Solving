/*
 * Spirally traversing a matrix
 *
 * You are given a rectangular matrix mat[][] of size n x m, and your task is to return an array while traversing the matrix in spiral form.
 *
 * Examples:
 *
 * Input: mat[][] = [[1, 2, 3, 4], [5, 6, 7, 8], [9, 10, 11, 12], [13, 14, 15, 16]]
 * Output: [1, 2, 3, 4, 8, 12, 16, 15, 14, 13, 9, 5, 6, 7, 11, 10]
 * Explanation:
 *
 * Input: mat[][] = [[1, 2, 3, 4, 5, 6], [7, 8, 9, 10, 11, 12], [13, 14, 15, 16, 17, 18]]
 * Output: [1, 2, 3, 4, 5, 6, 12, 18, 17, 16, 15, 14, 13, 7, 8, 9, 10, 11]
 * Explanation: Applying same technique as shown above.
 *
 * Input: mat[][] = [[32, 44, 27, 23], [54, 28, 50, 62]]
 * Output: [32, 44, 27, 23, 62, 50, 28, 54]
 * Explanation: Applying same technique as shown above, output will be [32, 44, 27, 23, 62, 50, 28, 54].
 *
 * Constraints:
 * 1 <= n, m <= 1000
 * 0 <= mat[i][j]<= 100
 */

/************************************************************ C++ ************************************************/

// Approach: Use boundary traversal with four pointers (top, bottom, left, right) to traverse the matrix in a spiral order.
// Time Complexity: O(n * m) (Each element is visited once).
// Space Complexity: O(1) (Output vector is the only additional space used).
class Solution {
public:
   vector<int> spirallyTraverse(vector<vector<int> >& mat){
      vector<int> result;   // Vector to store the spiral order of elements

      // Define the boundaries of the matrix
      int top    = 0;                     // Top row boundary
      int left   = 0;                     // Left column boundary
      int bottom = mat.size() - 1;        // Bottom row boundary
      int right  = mat[0].size() - 1;     // Right column boundary

      // Traverse the matrix in a spiral order
      while (top <= bottom && left <= right) {
         // Traverse from left to right along the top row
         for (int i = left; i <= right; i++) {
            result.push_back(mat[top][i]);
         }
         top++;    // Move the top boundary down

         // Traverse from top to bottom along the right column
         for (int i = top; i <= bottom; i++) {
            result.push_back(mat[i][right]);
         }
         right--;    // Move the right boundary left

         // Check if the bottom row still needs to be traversed
         if (top <= bottom) {
            // Traverse from right to left along the bottom row
            for (int i = right; i >= left; i--) {
               result.push_back(mat[bottom][i]);
            }
         }
         bottom--;    // Move the bottom boundary up

         // Check if the left column still needs to be traversed
         if (left <= right) {
            // Traverse from bottom to top along the left column
            for (int i = bottom; i >= top; i--) {
               result.push_back(mat[i][left]);
            }
         }
         left++;    // Move the left boundary right
      }

      // Return the spiral order of elements
      return result;
   }
};

/************************************************************ JAVA ************************************************/

// Approach: Use boundary traversal with four pointers (top, bottom, left, right) to traverse the matrix in a spiral order.
// Time Complexity: O(n * m) (Each element is visited once).
// Space Complexity: O(1) (Output vector is the only additional space used).
class Solution {
   public ArrayList<Integer> spirallyTraverse(int[][] mat){
      ArrayList<Integer> result = new ArrayList<>(); // List to store the spiral order of elements

      // Define the boundaries of the matrix
      int top    = 0;                   // Top row boundary
      int left   = 0;                   // Left column boundary
      int bottom = mat.length - 1;      // Bottom row boundary
      int right  = mat[0].length - 1;   // Right column boundary

      // Traverse the matrix in a spiral order
      while (top <= bottom && left <= right) {
         // Traverse from left to right along the top row
         for (int i = left; i <= right; i++) {
            result.add(mat[top][i]);
         }
         top++; // Move the top boundary down

         // Traverse from top to bottom along the right column
         for (int i = top; i <= bottom; i++) {
            result.add(mat[i][right]);
         }
         right--; // Move the right boundary left

         // Check if the bottom row still needs to be traversed
         if (top <= bottom) {
            // Traverse from right to left along the bottom row
            for (int i = right; i >= left; i--) {
               result.add(mat[bottom][i]);
            }
         }
         bottom--; // Move the bottom boundary up

         // Check if the left column still needs to be traversed
         if (left <= right) {
            // Traverse from bottom to top along the left column
            for (int i = bottom; i >= top; i--) {
               result.add(mat[i][left]);
            }
         }
         left++; // Move the left boundary right
      }

      // Return the spiral order of elements
      return result;
   }
}
