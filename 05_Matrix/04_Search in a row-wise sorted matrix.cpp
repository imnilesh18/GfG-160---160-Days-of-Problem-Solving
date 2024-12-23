/*
 * Search in a row-wise sorted matrix
 *
 * Given a row-wise sorted 2D matrix mat[][] of size n x m and an integer x, find whether element x is present in the matrix.
 * Note: In a row-wise sorted matrix, each row is sorted in itself, i.e. for any i, j within bounds, mat[i][j] <= mat[i][j+1].
 *
 * Examples :
 *
 * Input: mat[][] = [[3, 4, 9],[2, 5, 6],[9, 25, 27]], x = 9
 * Output: true
 * Explanation: 9 is present in the matrix, so the output is true.
 *
 * Input: mat[][] = [[19, 22, 27, 38, 55, 67]], x = 56
 * Output: false
 * Explanation: 56 is not present in the matrix, so the output is false.
 *
 * Input: mat[][] = [[1, 2, 9],[65, 69, 75]], x = 91
 * Output: false
 * Explanation: 91 is not present in the matrix.
 *
 * Constraints:
 * 1 <= n, m <= 1000
 * 1 <= mat[i][j] <= 10^5
 * 1 <= x <= 10^5
 */

/************************************************************ C++ ************************************************/

// Approach: Use binary search to check each row of the row-wise sorted matrix for the target value.
// Time Complexity: O(n * log m) (binary search in each of n rows with m columns).
// Space Complexity: O(1) (no additional space is used).
class Solution {
public:
   // Function to search a given number in a row-wise sorted matrix.
   bool searchRowMatrix(vector<vector<int> >&mat, int x){
      int n = mat.size();   // Number of rows in the matrix

      // Iterate through each row of the matrix
      for (int i = 0; i < n; i++) {
         int l = 0, h = mat[0].size() - 1;    // Initialize binary search for the current row

         // Perform binary search in the current row
         while (l <= h) {
            int mid = l + (h - l) / 2;     // Calculate mid index to prevent overflow

            if (mat[i][mid] == x) {
               return true;      // If element is found, return true
            }

            if (mat[i][mid] < x) {
               l = mid + 1;      // If mid value is less than x, search in the right half
            } else {
               h = mid - 1;      // If mid value is greater than x, search in the left half
            }
         }
      }

      return false;   // If element is not found in any row, return false
   }
};

/************************************************************ JAVA ************************************************/

// Approach: Use binary search to check each row of the row-wise sorted matrix for the target value.
// Time Complexity: O(n * log m) (binary search in each of n rows with m columns).
// Space Complexity: O(1) (no additional space is used).
class Solution {
   // Function to search a given number in row-column sorted matrix.
   public boolean searchRowMatrix(int[][] mat, int x){
      int n = mat.length;    // Number of rows
      int m = mat[0].length; // Number of columns

      // Iterate through each row
      for (int i = 0; i < n; i++) {
         int low = 0, high = m - 1;

         // Apply binary search in the current row
         while (low <= high) {
            int mid = low + (high - low) / 2;

            if (mat[i][mid] == x) {
               return true;      // Element found
            }

            if (mat[i][mid] < x) {
               low = mid + 1;      // Search in the right half
            } else {
               high = mid - 1;     // Search in the left half
            }
         }
      }

      return false;   // Element not found
   }
}
