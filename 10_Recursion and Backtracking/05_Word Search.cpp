/*
 * Word Search
 *
 * You are given a two-dimensional mat[][] of size n*m containing English alphabets and a string word. Check if the word exists on the mat. The word can be constructed by using letters from adjacent cells, either horizontally or vertically. The same cell cannot be used more than once.
 *
 * Examples :
 *
 * Input: mat[][] = [['T', 'E', 'E'], ['S', 'G', 'K'], ['T', 'E', 'L']], word = "GEEK"
 * Output: true
 * Explanation:
 * The letter cells which are used to construct the "GEEK" are colored.
 *
 * Input: mat[][] = [['T', 'E', 'U'], ['S', 'G', 'K'], ['T', 'E', 'L']], word = "GEEK"
 * Output: false
 * Explanation:
 * It is impossible to construct the string word from the mat using each cell only once.
 *
 * Input: mat[][] = [['A', 'B', 'A'], ['B', 'A', 'B']], word = "AB"
 * Output: true
 * Explanation:
 * There are multiple ways to construct the word "AB".
 *
 * Constraints:
 * 1 ≤ n, m ≤ 6
 * 1 ≤ L ≤ 15
 * mat and word consists of only lowercase and uppercase English letters.
 */

/************************************************************ C++ ************************************************/

// Approach: Use DFS with backtracking starting from each cell that matches the first character, marking visited cells to avoid reuse.
// TC: O(n*m*4^L) where L is the length of the word.
// SC: O(L) due to recursion stack.
class Solution {
public:
   int m, n;   // dimensions of the matrix
   // Directions representing down, up, right, left movements
   vector<vector<int> > directions{ { 1, 0 }, { -1, 0 }, { 0, 1 }, { 0, -1 } };

   /*
    * Recursive helper function to search for the word in the matrix.
    * @param mat: The matrix of characters.
    * @param i, j: Current cell coordinates.
    * @param idx: Current index in the word that we are trying to match.
    * @param word: The target word to search for.
    * @return: true if the word can be formed from this cell onward, false otherwise.
    */
   bool find(vector<vector<char> >& mat, int i, int j, int idx, string& word) {
      // If we have matched the entire word, return true
      if (idx == word.length()) {
         return true;
      }

      // Check for out-of-bound indices or already visited cell (marked as '$')
      if (i < 0 || j < 0 || i >= m || j >= n || mat[i][j] == '$') {
         return false;
      }

      // If current cell character does not match the current word character, return false
      if (mat[i][j] != word[idx]) {
         return false;
      }

      // Store the current cell character and mark the cell as visited by replacing it with a special character '$'
      char temp = mat[i][j];
      mat[i][j] = '$';

      // Explore all 4 adjacent directions (down, up, right, left)
      for (auto&dir : directions) {
         int new_i = i + dir[0];
         int new_j = j + dir[1];

         // Recursive call: if the word can be found from the next cell, return true
         if (find(mat, new_i, new_j, idx + 1, word)) {
            return true;
         }
      }

      // Backtrack: restore the original character in the cell
      mat[i][j] = temp;

      // Return false if the word could not be formed starting from this cell
      return false;
   }

   /*
    * Main function to check if the given word exists in the matrix.
    * @param mat: The 2D matrix of characters.
    * @param word: The word to search for.
    * @return: true if the word exists in the matrix, false otherwise.
    */
   bool isWordExist(vector<vector<char> >& mat, string& word) {
      // Get the dimensions of the matrix
      m = mat.size();
      n = mat[0].size();

      // Traverse each cell in the matrix
      for (int i = 0; i < m; i++) {
         for (int j = 0; j < n; j++) {
            // If the current cell matches the first character of the word,
            // start a depth-first search from that cell.
            if (mat[i][j] == word[0] && find(mat, i, j, 0, word)) {
               return true;
            }
         }
      }

      // Return false if the word is not found in any path
      return false;
   }
};

/************************************************************ JAVA ************************************************/

// Approach: Use DFS with backtracking starting from each cell that matches the first character; mark visited cells to avoid reuse.
// TC: O(n*m*4^L), where L is the length of the word.
// SC: O(L) due to the recursion stack.
class Solution {
   // Dimensions of the matrix
   static int m, n;
   // Directions array representing down, up, right, and left moves
   static int[][] directions = { { 1, 0 }, { -1, 0 }, { 0, 1 }, { 0, -1 } };

   /**
    * Recursive helper function to search for the word in the matrix using DFS and backtracking.
    * @param mat 2D character matrix.
    * @param i Current row index.
    * @param j Current column index.
    * @param idx Current index in the word.
    * @param word The target word.
    * @return true if the word can be constructed from this cell onward, otherwise false.
    */
   static private boolean find(char[][] mat, int i, int j, int idx, String word) {
      // If we have matched all characters in the word, return true.
      if (idx == word.length()) {
         return true;
      }

      // Check for out-of-bound indices or if the cell is already visited (marked by '$').
      if (i < 0 || j < 0 || i >= m || j >= n || mat[i][j] == '$') {
         return false;
      }

      // If the current cell's character does not match the corresponding word character, return false.
      if (mat[i][j] != word.charAt(idx)) {
         return false;
      }

      // Mark the cell as visited by storing its character and replacing it with a special character.
      char temp = mat[i][j];
      mat[i][j] = '$';

      // Explore all 4 adjacent directions (down, up, right, left).
      for (int[] dir : directions) {
         int new_i = i + dir[0];
         int new_j = j + dir[1];
         if (find(mat, new_i, new_j, idx + 1, word)) {
            return true;
         }
      }

      // Backtrack: restore the original character in the cell.
      mat[i][j] = temp;

      // Return false if the word could not be formed from this cell.
      return false;
   }

   /**
    * Checks if the given word exists in the matrix.
    * @param mat 2D character matrix.
    * @param word The word to search for.
    * @return true if the word exists in the matrix, otherwise false.
    */
   static public boolean isWordExist(char[][] mat, String word) {
      // Set matrix dimensions
      m = mat.length;
      n = mat[0].length;

      // Iterate through every cell in the matrix
      for (int i = 0; i < m; i++) {
         for (int j = 0; j < n; j++) {
            // If the current cell matches the first character of the word,
            // start a depth-first search (DFS) from that cell.
            if (mat[i][j] == word.charAt(0) && find(mat, i, j, 0, word)) {
               return true;
            }
         }
      }
      // Return false if the word is not found in any path.
      return false;
   }
}
