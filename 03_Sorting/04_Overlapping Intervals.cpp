/*
 * Overlapping Intervals
 *
 * Given an array of Intervals arr[][], where arr[i] = [starti, endi]. The task is to merge all of the overlapping Intervals.
 *
 * Examples:
 * Input: arr[][] = [[1,3],[2,4],[6,8],[9,10]]
 * Output: [[1,4], [6,8], [9,10]]
 * Explanation: In the given intervals we have only two overlapping intervals here, [1,3] and [2,4] which on merging will become [1,4]. Therefore we will return [[1,4], [6,8], [9,10]].
 *
 * Input: arr[][] = [[6,8],[1,9],[2,4],[4,7]]
 * Output: [[1,9]]
 * Explanation: In the given intervals all the intervals overlap with the interval [1,9]. Therefore we will return [1,9].
 *
 * Constraints:
 * 1 ≤ arr.size() ≤ 10^5
 * 0 ≤ starti ≤ endi ≤ 10^5
 */

/************************************************************ C++ ************************************************/

// Approach: (Using BIT/Fenwick Tree Approach)
// T.C: O(nlogn)
// S.C: O(1)
class Solution {
public:
   vector<vector<int> > mergeOverlap(vector<vector<int> >& arr){
      // Step 1: Sort the intervals based on the start time
      // Sorting helps in processing intervals in increasing order of their start times
      sort(arr.begin(), arr.end());

      // Step 2: Initialize a result vector to store the merged intervals
      vector<vector<int> > result;

      // Step 3: Iterate over each interval in the sorted array
      for (vector<int> interval : arr) {
         // If the result is empty or the current interval does not overlap with the last interval
         if (result.empty() || result.back()[1] < interval[0]) {
            // Add the current interval to the result as a new non-overlapping interval
            result.push_back(interval);
         } else {
            // If the intervals overlap, merge them by updating the end time
            // Use the maximum end time between the two overlapping intervals
            result.back()[1] = max(result.back()[1], interval[1]);
         }
      }

      // Step 4: Return the merged intervals
      return result;
   }
};


/************************************************************ JAVA ************************************************/

// Approach: (Using BIT/Fenwick Tree Approach)
// T.C: O(nlogn)
// S.C: O(1)
class Solution {
   public List<int[]> mergeOverlap(int[][] arr){
      // Step 1: Sort the intervals based on the start time using a lambda expression
      Arrays.sort(arr, (a, b)->a[0] - b[0]);

      // Step 2: Initialize a result list to store the merged intervals
      List<int[]> result = new ArrayList<>();

      // Step 3: Iterate over each interval in the sorted array
      for (int[] interval : arr) {
         // If the result is empty or the current interval does not overlap with the last interval
         if (result.isEmpty() || result.get(result.size() - 1)[1] < interval[0]) {
            // Add the current interval to the result as a new non-overlapping interval
            result.add(interval);
         } else {
            // If the intervals overlap, merge them by updating the end time
            result.get(result.size() - 1)[1] = Math.max(result.get(result.size() - 1)[1], interval[1]);
         }
      }

      // Step 4: Return the merged intervals
      return result;
   }
}
