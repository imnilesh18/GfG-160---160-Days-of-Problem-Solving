/*
 * Aggressive Cows
 *
 * You are given an array with unique elements of stalls[], which denote the position of a stall. You are also given an integer k which denotes the number of aggressive cows. Your task is to assign stalls to k cows such that the minimum distance between any two of them is the maximum possible.
 *
 * Examples :
 * Input: stalls[] = [1, 2, 4, 8, 9], k = 3
 * Output: 3
 * Explanation: The first cow can be placed at stalls[0],
 * the second cow can be placed at stalls[2] and
 * the third cow can be placed at stalls[3].
 * The minimum distance between cows, in this case, is 3, which also is the largest among all possible ways.
 *
 * Input: stalls[] = [10, 1, 2, 7, 5], k = 3
 * Output: 4
 * Explanation: The first cow can be placed at stalls[0],
 * the second cow can be placed at stalls[1] and
 * the third cow can be placed at stalls[4].
 * The minimum distance between cows, in this case, is 4, which also is the largest among all possible ways.
 *
 * Input: stalls[] = [2, 12, 11, 3, 26, 7], k = 5
 * Output: 1
 * Explanation: Each cow can be placed in any of the stalls, as the no. of stalls are exactly equal to the number of cows.
 * The minimum distance between cows, in this case, is 1, which also is the largest among all possible ways.
 *
 * Constraints:
 * 2 <= stalls.size() <= 10^6
 * 0 <= stalls[i] <= 10^8
 * 1 <= k <= stalls.size()
 */

/************************************************************ C++ ************************************************/

// Reason for TLE:
// The brute-force approach iterates over all possible distances (maxDist), which can be very large for large values of stalls and leads to inefficiency.
// Approach 1: Brute Force
// Time Complexity: O(n * maxDist) (sorting stalls takes O(n * log(n)), and checking placements for all distances up to maxDist takes O(n * maxDist)).
// Space Complexity: O(1) (no additional space used).
class Solution {
public:

   int aggressiveCows(vector<int>& stalls, int k){
      // Step 1: Sort the stall positions to consider distances in increasing order
      sort(stalls.begin(), stalls.end()); // O(n*log(n))

      // Step 2: Compute the maximum possible distance (from first to last stall)
      int maxDist = stalls.back() - stalls.front();

      int ans = 0;                                  // Stores the maximum minimum distance
      // Step 3: Iterate through all possible minimum distances from 1 to maxDist
      for (int dist = 1; dist <= maxDist; dist++) { // O(maxDist)
         int cowCount = 1;                          // Place the first cow in the first stall
         int prevPos  = stalls[0];                  // Track the position of the last placed cow

         // Step 4: Place cows greedily based on the minimum distance condition
         for (int i = 1; i < stalls.size(); i++) { // O(n)
            if (stalls[i] - prevPos >= dist) {     // Check if the distance is satisfied
               cowCount++;                         // Place a cow in the current stall
               prevPos = stalls[i];                // Update the last placed position
            }
         }

         // Step 5: If at least k cows can be placed, update the result
         if (cowCount >= k) {
            ans = dist; // Update the answer with the current minimum distance
         }
      }
      // Return the largest minimum distance where k cows can be placed
      return ans;
   }
};

// Approach 2: Binary search on the minimum distance, combined with a greedy check to validate cow placement at each midpoint.
// Time Complexity: O(N * log(max_distance)) (sorting takes O(N), binary search has log(max_distance) iterations, and placement validation is O(N) per iteration).
// Space Complexity: O(1) (no additional data structures used).
class Solution {
public:
   int aggressiveCows(vector<int>&stalls, int k){
      // Sort the stalls array to place cows in a sorted order
      sort(stalls.begin(), stalls.end());

      // Initialize the search range for the minimum distance
      int end   = stalls.back() - stalls.front(); // Maximum possible distance
      int start = 1;                              // Minimum distance possible between cows
      int ans   = 0;                              // Variable to store the largest minimum distance

      // Binary search for the optimal minimum distance
      while (start <= end) {
         int mid = start + (end - start) / 2;    // Midpoint of the current range

         // Variables to track the number of cows placed and their positions
         int cowCount = 1;         // Place the first cow in the first stall
         int prevPos  = stalls[0]; // Position of the last placed cow

         // Try placing cows with at least 'mid' distance apart
         for (int i = 1; i < stalls.size(); i++) {
            if (stalls[i] - prevPos >= mid) { // Check if the gap is at least 'mid'
               cowCount++;                    // Place another cow
               prevPos = stalls[i];           // Update the position of the last placed cow
            }
         }

         // If we can place all k cows with at least 'mid' distance apart
         if (cowCount >= k) {
            ans   = mid;     // Update the answer
            start = mid + 1; // Search for a larger distance
         } else {
            end = mid - 1;   // Search for a smaller distance
         }
      }

      return ans;   // Return the largest minimum distance found
   }
};

/************************************************************ JAVA ************************************************/

// Reason for TLE:
// The brute-force approach iterates over all possible distances (maxDist), which can be very large for large values of stalls and leads to inefficiency.
// Approach: Brute Force
// Time Complexity: O(n * maxDist) (sorting stalls takes O(n * log(n)), and checking placements for all distances up to maxDist takes O(n * maxDist)).
// Space Complexity: O(1) (no additional space used).
class Solution {
   public static int aggressiveCows(int[] stalls, int k){
      // Sort the stalls array
      Arrays.sort(stalls);

      int maxDist = stalls[stalls.length - 1] - stalls[0];   // Maximum possible distance
      int ans     = 0;

      // Iterate over possible distances from 1 to maxDist
      for (int dist = 1; dist <= maxDist; dist++) {
         int cowCount = 1;    // Place the first cow in the first stall
         int prevPos  = stalls[0];

         // Try placing cows with at least 'dist' distance
         for (int i = 1; i < stalls.length; i++) {
            if (stalls[i] - prevPos >= dist) {
               cowCount++;
               prevPos = stalls[i];
            }
         }

         // If it's possible to place all k cows with this distance, update the answer
         if (cowCount >= k) {
            ans = dist;
         }
      }

      return ans;
   }
}

// Approach 2: Binary search on the minimum distance, combined with a greedy check to validate cow placement at each midpoint.
// Time Complexity: O(N * log(max_distance)) (sorting takes O(N), binary search has log(max_distance) iterations, and placement validation is O(N) per iteration).
// Space Complexity: O(1) (no additional data structures used).
class Solution {
   public static int aggressiveCows(int[] stalls, int k){
      // Sort the stalls array to place cows in a sorted order
      Arrays.sort(stalls);

      // Initialize the search range for the minimum distance
      int end   = stalls[stalls.length - 1] - stalls[0]; // Maximum possible distance
      int start = 1;                                     // Minimum distance possible between cows
      int ans   = 0;                                     // Variable to store the largest minimum distance

      // Binary search for the optimal minimum distance
      while (start <= end) {
         int mid = start + (end - start) / 2;    // Midpoint of the current range

         // Variables to track the number of cows placed and their positions
         int cowCount = 1;         // Place the first cow in the first stall
         int prevPos  = stalls[0]; // Position of the last placed cow

         // Try placing cows with at least 'mid' distance apart
         for (int i = 1; i < stalls.length; i++) {
            if (stalls[i] - prevPos >= mid) { // Check if the gap is at least 'mid'
               cowCount++;                    // Place another cow
               prevPos = stalls[i];           // Update the position of the last placed cow
            }
         }

         // If we can place all k cows with at least 'mid' distance apart
         if (cowCount >= k) {
            ans   = mid;     // Update the answer
            start = mid + 1; // Search for a larger distance
         } else {
            end = mid - 1;   // Search for a smaller distance
         }
      }

      return ans;   // Return the largest minimum distance found
   }
}
