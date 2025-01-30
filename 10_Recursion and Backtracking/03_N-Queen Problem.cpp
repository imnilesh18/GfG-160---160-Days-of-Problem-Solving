/*
 * N-Queen Problem
 *
 * The n-queens puzzle is the problem of placing n queens on a (n × n) chessboard such that no two queens can attack each other. Note that two queens attack each other if they are placed on the same row, the same column, or the same diagonal.
 * Given an integer n, find all distinct solutions to the n-queens puzzle.
 * You can return your answer in any order but each solution should represent a distinct board configuration of the queen placements, where the solutions are represented as permutations of [1, 2, 3, ..., n]. In this representation, the number in the ith position denotes the row in which the queen is placed in the ith column.
 * For eg. below figure represents a chessboard [3 1 4 2].
 *
 * Examples:
 *
 * Input: n = 1
 * Output: [1]
 * Explaination: Only one queen can be placed in the single cell available.
 *
 * Input: n = 4
 * Output: [[2 4 1 3 ] [3 1 4 2 ]]
 * Explaination: There are 2 possible solutions for n = 4.
 *
 * Input: n = 2
 * Output: []
 * Explaination: There are no possible solutions for n = 2.
 *
 * Constraints:
 * 1 ≤ n ≤ 10
 */

/************************************************************ C++ ************************************************/

// Approach 1: Backtracking is used to explore all possible placements of queens row by row. If a valid placement is found, we recursively move to the next row. If a conflict occurs, we backtrack and try the next possibility. The solutions are stored in a specific format.
// Time Complexity: O(N!) – Since there are N choices for the first row, (N-1) for the second, (N-2) for the third, and so on, leading to N! possibilities.
// Space Complexity: O(N²) – The board uses O(N²) space, and additional space is used for storing results. The recursion stack takes O(N) space.
class Solution {
public:
   vector<vector<int> > result;  // Stores all valid solutions

   // Function to check if placing a queen at (row, col) is safe
   bool isValid(vector<vector<int> >&board, int row, int col) {
      // Check the column for another queen
      for (int i = row; i >= 0; i--) {
         if (board[i][col] != 0) {
            return false;
         }
      }

      // Check left diagonal (↖)
      for (int i = row, j = col; i >= 0 && j >= 0; i--, j--) {
         if (board[i][j] != 0) {
            return false;
         }
      }

      // Check right diagonal (↗)
      for (int i = row, j = col; i >= 0 && j < board.size(); i--, j++) {
         if (board[i][j] != 0) {
            return false;
         }
      }

      return true;    // Safe to place queen
   }

   // Recursive function to solve N-Queens
   void solve(vector<vector<int> >&board, int row) {
      // If all queens are placed, store the solution
      if (row == board.size()) {
         vector<int> solution;
         // Extract column-wise queen positions
         for (int col = 0; col < board.size(); col++) {
            for (int row = 0; row < board.size(); row++) {
               if (board[row][col] != 0) {
                  solution.push_back(row + 1);        // Convert to 1-based index
                  break;
               }
            }
         }
         result.push_back(solution);
         return;
      }

      // Try placing a queen in each column of the current row
      for (int i = 0; i < board.size(); i++) {
         if (isValid(board, row, i)) {
            board[row][i] = row + 1; // Place the queen (store row + 1)
            solve(board, row + 1);   // Recur for the next row
            board[row][i] = 0;       // Backtrack (remove queen)
         }
      }
   }

   // Main function to solve the N-Queens problem
   vector<vector<int> > nQueen(int n) {
      if (n == 0) {
         return {};
      }

      result.clear();                                   // Clear previous results
      vector<vector<int> > board(n, vector<int>(n, 0)); // Initialize empty board

      solve(board, 0);                                  // Start solving from the first row

      return result;                                    // Return all possible solutions
   }
};

// Approach 2: Backtracking with Hash Sets for column and diagonal checks. Instead of checking the board explicitly, we use sets to track occupied columns and diagonals, reducing the need for nested loops.
// Time Complexity: O(N!) – Since we place N queens one by one, and at each row, we try up to N possibilities, leading to factorial complexity.
// Space Complexity: O(N) – We use hash sets to store occupied columns and diagonals, and the recursion stack takes O(N) space.
class Solution {
public:
   vector<vector<int> > result;  // Stores all valid solutions

   // Recursive function to solve N-Queens using Hash Sets for optimization
   void solve(vector<int>& board, int row, unordered_set<int>& cols, unordered_set<int>& diags, unordered_set<int>& antiDiags) {
      // If all queens are placed, store the solution
      if (row == board.size()) {
         result.push_back(board);
         return;
      }

      // Try placing a queen in each column of the current row
      for (int col = 0; col < board.size(); col++) {
         int diag_id      = row - col; // Left diagonal identifier
         int anti_diag_id = row + col; // Right diagonal identifier

         // Check if the column or diagonals are already occupied
         if (cols.find(col) != cols.end() || diags.find(diag_id) != diags.end() || antiDiags.find(anti_diag_id) != antiDiags.end()) {
            continue;      // Skip this position if it causes a conflict
         }

         // Place the queen and mark its position
         cols.insert(col);
         diags.insert(diag_id);
         antiDiags.insert(anti_diag_id);
         board[row] = col + 1;     // Store the position as 1-based index

         // Recur for the next row
         solve(board, row + 1, cols, diags, antiDiags);

         // Backtrack: Remove the queen and unmark its position
         cols.erase(col);
         diags.erase(diag_id);
         antiDiags.erase(anti_diag_id);
         board[row] = 0;
      }
   }

   // Main function to solve the N-Queens problem
   vector<vector<int> > nQueen(int n) {
      if (n == 0) {
         return {};                            // Edge case: No solution for n = 0
      }
      vector<int>        board(n, 0);          // Initialize board
      unordered_set<int> cols;                 // Track occupied columns
      unordered_set<int> diags;                // Track occupied left diagonals
      unordered_set<int> antiDiags;            // Track occupied right diagonals

      solve(board, 0, cols, diags, antiDiags); // Start solving from the first row

      return result;                           // Return all valid solutions
   }
};


/************************************************************ JAVA ************************************************/

// Approach 1: Backtracking is used to explore all possible placements of queens row by row. If a valid placement is found, we recursively move to the next row. If a conflict occurs, we backtrack and try the next possibility. The solutions are stored in a specific format.
// Time Complexity: O(N!) – Since there are N choices for the first row, (N-1) for the second, (N-2) for the third, and so on, leading to N! possibilities.
// Space Complexity: O(N²) – The board uses O(N²) space, and additional space is used for storing results. The recursion stack takes O(N) space.
class Solution {
   private ArrayList<ArrayList<Integer> > result = new ArrayList<>();

   // Function to check if placing a queen at (row, col) is safe
   private boolean isValid(int[][] board, int row, int col) {
      // Check column for another queen
      for (int i = row; i >= 0; i--) {
         if (board[i][col] != 0) {
            return false;
         }
      }

      // Check left diagonal (↖)
      for (int i = row, j = col; i >= 0 && j >= 0; i--, j--) {
         if (board[i][j] != 0) {
            return false;
         }
      }

      // Check right diagonal (↗)
      for (int i = row, j = col; i >= 0 && j < board.length; i--, j++) {
         if (board[i][j] != 0) {
            return false;
         }
      }

      return true;    // Safe to place queen
   }

   // Recursive function to solve N-Queens
   private void solve(int[][] board, int row) {
      // If all queens are placed, store the solution
      if (row == board.length) {
         ArrayList<Integer> solution = new ArrayList<>();
         // Extract column-wise queen positions
         for (int col = 0; col < board.length; col++) {
            for (int i = 0; i < board.length; i++) {
               if (board[i][col] != 0) {
                  solution.add(i + 1);        // Convert to 1-based index
                  break;
               }
            }
         }
         result.add(solution);
         return;
      }

      // Try placing a queen in each column of the current row
      for (int i = 0; i < board.length; i++) {
         if (isValid(board, row, i)) {
            board[row][i] = row + 1; // Place the queen (store row + 1)
            solve(board, row + 1);   // Recur for the next row
            board[row][i] = 0;       // Backtrack (remove queen)
         }
      }
   }

   // Main function to solve the N-Queens problem
   public ArrayList<ArrayList<Integer> > nQueen(int n) {
      result.clear();                // Clear previous results
      int[][] board = new int[n][n]; // Initialize empty board

      solve(board, 0);               // Start solving from the first row

      return result;                 // Return all possible solutions
   }
}

// Approach 2: Backtracking with HashSets for efficient column and diagonal checks. Instead of checking the board explicitly, we use sets to track occupied columns and diagonals, reducing unnecessary iterations.
// Time Complexity: O(N!) – Since we place N queens one by one, and at each row, we try up to N possibilities, leading to factorial complexity.
// Space Complexity: O(N) – We use hash sets to store occupied columns and diagonals, and the recursion stack takes O(N) space.
class Solution {
   public ArrayList<ArrayList<Integer> > nQueen(int n) {
      // List to store all possible solutions
      ArrayList<ArrayList<Integer> > result = new ArrayList<>();

      // Edge case: No solution for n = 0
      if (n == 0) {
         return result;
      }

      // Board representation (stores column positions of queens in each row)
      int[] board = new int[n];
      Arrays.fill(board, -1);

      // HashSets to track occupied columns and diagonals
      HashSet<Integer> cols      = new HashSet<>();
      HashSet<Integer> diags     = new HashSet<>();
      HashSet<Integer> antiDiags = new HashSet<>();

      // Start solving from the first row
      solve(n, 0, board, cols, diags, antiDiags, result);

      return result;
   }

   // Recursive function to solve N-Queens using HashSets for optimization
   private void solve(int n, int row, int[] board, HashSet<Integer> cols,
                      HashSet<Integer> diags, HashSet<Integer> antiDiags,
                      ArrayList<ArrayList<Integer> > result) {
      // If all queens are placed, store the solution
      if (row == n) {
         ArrayList<Integer> solution = new ArrayList<>();
         for (int i = 0; i < n; i++) {
            solution.add(board[i] + 1);     // Convert to 1-based index
         }
         result.add(solution);
         return;
      }

      // Try placing a queen in each column of the current row
      for (int col = 0; col < n; col++) {
         int diag_id      = row - col; // Left diagonal identifier
         int anti_diag_id = row + col; // Right diagonal identifier

         // Check if the column or diagonals are already occupied
         if (cols.contains(col) || diags.contains(diag_id) || antiDiags.contains(anti_diag_id)) {
            continue;     // Skip this position if it causes a conflict
         }

         // Place the queen and mark its position
         cols.add(col);
         diags.add(diag_id);
         antiDiags.add(anti_diag_id);
         board[row] = col;     // Store column position (0-based)

         // Recur for the next row
         solve(n, row + 1, board, cols, diags, antiDiags, result);

         // Backtrack: Remove the queen and unmark its position
         cols.remove(col);
         diags.remove(diag_id);
         antiDiags.remove(anti_diag_id);
         board[row] = -1;
      }
   }
}
