/*
 * Find H-Index
 *
 * Given an integer array citations[], where citations[i] is the number of citations a researcher received for the ith paper. The task is to find the H-index.
 *
 * H-Index is the largest value such that the researcher has at least H papers that have been cited at least H times.
 *
 * Examples:
 *
 * Input: citations[] = [3, 0, 5, 3, 0]
 * Output: 3
 * Explanation: There are at least 3 papers (3, 5, 3) with at least 3 citations.
 *
 * Input: citations[] = [5, 1, 2, 4, 1]
 * Output: 2
 * Explanation: There are 3 papers (with citation counts of 5, 2, and 4) that have 2 or more citations. However, the H-Index cannot be 3 because there aren't 3 papers with 3 or more citations.
 *
 * Input: citations[] = [0, 0]
 * Output: 0
 *
 * Constraints:
 * 1 ≤ citations.size() ≤ 10^6
 * 0 ≤ citations[i] ≤ 10^6
 */

/************************************************************ C++ ************************************************/

// Approach 1: Linear Search
// T.C: O(nlogn)
// S.C: O(1)
class Solution {
public:
   // Function to find the H-Index of a researcher based on the citations array
   int hIndex(vector<int>& citations){
      // Get the number of papers
      int n = citations.size();

      // Sort the citations array in ascending order
      // This helps in calculating how many papers have at least a certain number of citations
      sort(citations.begin(), citations.end());

      // Iterate through the sorted array to determine the H-Index
      for (int i = 0; i < n; i++) {
         // Width: Citation count of the current paper
         int width = citations[i];

         // Height: Number of papers with at least 'width' citations
         int height = n - i;

         // Check if we can form a "rectangle" where width >= height
         // This corresponds to the H-Index definition:
         // At least 'height' papers with at least 'height' citations
         if (width >= height) {
            return height; // Return the H-Index value (max square/rectangle height)
         }
      }

      // If no valid H-Index is found, return 0
      return 0;
   }
};

// Approach 2: Binary Search
// T.C: O(nlogn)
// S.C: O(1)
class Solution {
public:
   // Function to find H-Index using Binary Search
   int hIndex(vector<int>& citations){
      int n = citations.size();   // Get the number of papers

      // Sort the citations array in ascending order
      sort(citations.begin(), citations.end());

      // Initialize binary search boundaries
      int low = 0, high = n - 1, hIndex = 0;

      // Perform binary search
      while (low <= high) {
         // Calculate the middle index
         int mid = low + (high - low) / 2;

         // h is the potential H-Index, determined by the number of papers
         // with at least citations[mid] citations
         int h = n - mid;

         // Check if citations[mid] satisfies the H-Index condition
         if (citations[mid] >= h) {
            // If valid, update the H-Index and search the left half for a higher value
            hIndex = h;
            high   = mid - 1;   // Narrow the search range to the left
         } else {
            // Otherwise, search the right half for a higher citation count
            low = mid + 1;
         }
      }

      return hIndex;   // Return the maximum H-Index found
   }
};



/************************************************************ JAVA ************************************************/

// Approach 1: Linear Search
// T.C: O(nlogn)
// S.C: O(1)
class Solution {
   // Function to find the H-Index
   public int hIndex(int[] citations){
      int n = citations.length;   // Get the number of papers

      // Sort the citations array in ascending order
      Arrays.sort(citations);

      // Iterate through the sorted array to determine the H-Index
      for (int i = 0; i < n; i++) {
         // Width: Citation count of the current paper
         int width = citations[i];

         // Height: Number of papers with at least 'width' citations
         int height = n - i;

         // Check if we can form a "rectangle" where width >= height
         // This corresponds to the H-Index definition
         if (width >= height) {
            return height;     // Return the H-Index value
         }
      }

      // If no valid H-Index is found, return 0
      return 0;
   }
}

// Approach 2: Binary Search
// T.C: O(nlogn)
// S.C: O(1)
class Solution {
   // Function to find the H-Index using Binary Search
   public int hIndex(int[] citations){
      int n = citations.length;   // Get the number of papers

      // Sort the citations array in ascending order
      Arrays.sort(citations);

      // Initialize binary search boundaries
      int low = 0, high = n - 1, hIndex = 0;

      // Perform binary search
      while (low <= high) {
         // Calculate the middle index
         int mid = low + (high - low) / 2;

         // h is the potential H-Index, determined by the number of papers
         // with at least citations[mid] citations
         int h = n - mid;

         // Check if citations[mid] satisfies the H-Index condition
         if (citations[mid] >= h) {
            // If valid, update the H-Index and search the left half for a higher value
            hIndex = h;
            high   = mid - 1;   // Narrow the search range to the left
         } else {
            // Otherwise, search the right half for a higher citation count
            low = mid + 1;
         }
      }

      return hIndex;   // Return the maximum H-Index found
   }
}
