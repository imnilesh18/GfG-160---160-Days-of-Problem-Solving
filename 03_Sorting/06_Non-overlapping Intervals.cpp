/*
 * Non-overlapping Intervals
 *
 * Given a 2D array intervals[][] of representing intervals where intervals [i] = [starti, endi ]. Return the minimum number of intervals you need to remove to make the rest of the intervals non-overlapping.
 *
 * Examples:
 * Input: intervals[][] = [[1, 2], [2, 3], [3, 4], [1, 3]]
 * Output: 1
 * Explanation: [1, 3] can be removed and the rest of the intervals are non-overlapping.
 *
 * Input: intervals[][] = [[1, 3], [1, 3], [1, 3]]
 * Output: 2
 * Explanation: You need to remove two [1, 3] to make the rest of the intervals non-overlapping.
 *
 * Input: intervals[][] = [[1, 2], [5, 10], [18, 35], [40, 45]]
 * Output: 0
 * Explanation: All ranges are already non overlapping.
 *
 * Constraints:
 * 1 ≤ intervals.size() ≤  10^5
 |intervalsi| == 2
 * 0 ≤ starti < endi <=5*10^4
 */

/************************************************************ C++ ************************************************/

// Approach 1: Sorting
// T.C: O(nlogn) for sorting + O(n) for iteration ~ O(nlogn)
// S.C: O(1) as sorting is in-place and uses constant space
class Solution {
public:
   int minRemoval(vector<vector<int> >& intervals){
      // Sort intervals based on their start time
      sort(begin(intervals), end(intervals));

      int n     = intervals.size(); // Total number of intervals
      int i     = 0;                // Pointer to the current interval
      int j     = 1;                // Pointer to the next interval
      int count = 0;                // Counter to track the number of intervals removed

      while (j < n) {
         // Current interval
         vector<int> curr_interval = intervals[i];
         // Next interval
         vector<int> next_interval = intervals[j];

         int cs = curr_interval[0]; // Start time of the current interval
         int ce = curr_interval[1]; // End time of the current interval

         int ns = next_interval[0]; // Start time of the next interval
         int ne = next_interval[1]; // End time of the next interval

         if (ce <= ns) {
            // No overlapping: the current interval ends before the next interval starts
            // Safe to move to the next pair of intervals
            i = j; // Update current interval pointer
            j++;   // Move to the next interval
         } else if (ce <= ne) {
            // Overlapping case: the current interval ends before or at the same time as the next interval
            // Remove the next interval (increment count)
            j++;     // Move to the next interval
            count++; // Increment removal count
         } else if (ce > ne) {
            // Overlapping case: the current interval ends after the next interval
            // Remove the current interval by updating the current pointer to the next interval
            i = j;   // Update current interval pointer
            j++;     // Move to the next interval
            count++; // Increment removal count
         }
      }
      return count; // Return the total number of intervals removed
   }
};

// Approach 2: Sorting and using last interval (same but different implementation)
// T.C: O(nlogn) + O(n) ~ O(n)
// S.C: O(1)
class Solution {
public:
   int minRemoval(vector<vector<int> >&intervals){
      // Sort intervals based on their start times
      sort(begin(intervals), end(intervals));

      int         count = 0;                // Counter for the number of intervals to remove
      int         n     = intervals.size(); // Total number of intervals
      int         i     = 1;                // Pointer to iterate through intervals
      vector<int> L     = intervals[0];     // L represents the last interval in the non-overlapping set

      while (i < n) {
         int curr_end   = intervals[i][1]; // End of the current interval
         int curr_start = intervals[i][0]; // Start of the current interval
         int last_end   = L[1];            // End of the last interval in the non-overlapping set

         if (curr_start >= last_end) {
            // No overlap with the last interval
            // Update the last interval to the current interval
            L = intervals[i];
            i++;
         } else if (curr_end >= last_end) {
            // Overlap, but the current interval's end is beyond or equal to the last interval's end
            // Remove the current interval (increment count)
            count++;
            i++;
         } else if (curr_end < last_end) {
            // Overlap, and the current interval ends earlier than the last interval
            // Remove the last interval by updating L to the current interval
            count++;
            L = intervals[i];
            i++;
         }
      }
      return count;   // Return the total number of intervals removed
   }
};


/************************************************************ JAVA ************************************************/

// Approach 1: Sorting
// T.C: O(nlogn) for sorting + O(n) for iteration ~ O(nlogn)
// S.C: O(1) as sorting is in-place and uses constant space
class Solution {
   static int minRemoval(int intervals[][]){
      // Sort intervals based on their start time using a lambda expression
      Arrays.sort(intervals, (a, b)->Integer.compare(a[0], b[0]));

      int n     = intervals.length;
      int i     = 0;
      int j     = 1;
      int count = 0;

      while (j < n) {
         int[] curr_interval = intervals[i];
         int[] next_interval = intervals[j];

         int cs = curr_interval[0];
         int ce = curr_interval[1];

         int ns = next_interval[0];
         int ne = next_interval[1];

         if (ce <= ns) {    // No overlap
            i = j;
            j++;
         } else if (ce <= ne) {    // Overlap, remove the next interval
            j++;
            count++;
         } else {    // Overlap, remove the current interval
            i = j;
            j++;
            count++;
         }
      }
      return count;
   }
}

// Approach 2: Sorting and using last interval (same but different implementation)
// T.C: O(nlogn) + O(n) ~ O(n)
// S.C: O(1)
class Solution {
   public int minRemoval(int[][] intervals){
      // Sort intervals based on their start times
      Arrays.sort(intervals, (a, b)->Integer.compare(a[0], b[0]));

      int count = 0;                // Counter for the number of intervals to remove
      int n     = intervals.length; // Total number of intervals
      int i     = 1;                // Pointer to iterate through intervals
      int[] L = intervals[0];       // L represents the last interval in the non-overlapping set

      while (i < n) {
         int curr_end   = intervals[i][1]; // End of the current interval
         int curr_start = intervals[i][0]; // Start of the current interval
         int last_end   = L[1];            // End of the last interval in the non-overlapping set

         if (curr_start >= last_end) {
            // No overlap with the last interval
            // Update the last interval to the current interval
            L = intervals[i];
            i++;
         } else if (curr_end >= last_end) {
            // Overlap, but the current interval's end is beyond or equal to the last interval's end
            // Remove the current interval (increment count)
            count++;
            i++;
         } else if (curr_end < last_end) {
            // Overlap, and the current interval ends earlier than the last interval
            // Remove the last interval by updating L to the current interval
            count++;
            L = intervals[i];
            i++;
         }
      }
      return count;   // Return the total number of intervals removed
   }
}
