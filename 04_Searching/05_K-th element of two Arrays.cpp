/*
 * K-th element of two Arrays
 *
 * Given two sorted arrays a[] and b[] and an element k, the task is to find the element that would be at the kth position of the combined sorted array.
 *
 * Examples :
 * Input: a[] = [2, 3, 6, 7, 9], b[] = [1, 4, 8, 10], k = 5
 * Output: 6
 * Explanation: The final combined sorted array would be [1, 2, 3, 4, 6, 7, 8, 9, 10]. The 5th element of this array is 6.
 *
 * Input: a[] = [100, 112, 256, 349, 770], b[] = [72, 86, 113, 119, 265, 445, 892], k = 7
 * Output: 256
 * Explanation: Combined sorted array is [72, 86, 100, 112, 113, 119, 256, 265, 349, 445, 770, 892]. The 7th element of this array is 256.
 *
 * Constraints:
 * 1 <= a.size(), b.size() <= 10^6
 * 1 <= k <= a.size() + b.size()
 * 0 <= a[i], b[i] < 10^8
 */

/************************************************************ C++ ************************************************/

// Approach: Binary search on smaller array to partition a and b, ensuring valid split with k elements in total.
// Time Complexity: O(log(min(n, m))) (binary search on the smaller array).
// Space Complexity: O(1) (no extra space used).
class Solution {
public:
   int kthElement(vector<int>& a, vector<int>& b, int k){
      int n = a.size();
      int m = b.size();

      // Ensure the first array is smaller to simplify binary search
      if (n > m) {
         return kthElement(b, a, k);
      }

      // Define the search range for the partition in the smaller array
      int lo = max(0, k - m);   // Minimum elements to take from `a`
      int hi = min(k, n);       // Maximum elements to take from `a`

      while (lo <= hi) {
         int mid1 = (lo + hi) / 2;      // Partition index for `a`
         int mid2 = k - mid1;           // Partition index for `b`

         // Edge cases: values from `a` around the partition
         int l1 = (mid1 == 0 ? INT_MIN : a[mid1 - 1]);    // Left of `a`'s partition
         int r1 = (mid1 == n ? INT_MAX : a[mid1]);        // Right of `a`'s partition

         // Edge cases: values from `b` around the partition
         int l2 = (mid2 == 0 ? INT_MIN : b[mid2 - 1]);    // Left of `b`'s partition
         int r2 = (mid2 == m ? INT_MAX : b[mid2]);        // Right of `b`'s partition

         // Check if we found a valid partition
         if (l1 <= r2 && l2 <= r1) {
            return max(l1, l2);     // The kth element is the maximum of left parts
         }

         // If `l1 > r2`, move the partition in `a` to the left
         if (l1 > r2) {
            hi = mid1 - 1;
         }
         // Otherwise, move the partition in `a` to the right
         else {
            lo = mid1 + 1;
         }
      }

      return -1;   // This line should never be reached
   }
};

/************************************************************ JAVA ************************************************/

// Approach: Binary search on smaller array to partition a and b, ensuring valid split with k elements in total.
// Time Complexity: O(log(min(n, m))) (binary search on the smaller array).
// Space Complexity: O(1) (no extra space used).
class Solution {
   public int kthElement(int a[], int b[], int k){
      // Lengths of the arrays
      int n = a.length;
      int m = b.length;

      // Ensure that array `a` is the smaller array
      if (n > m) {
         return kthElement(b, a, k);
      }

      // Binary search range for the partition index in `a`
      int lo = Math.max(0, k - m);   // Minimum index to consider in `a`
      int hi = Math.min(k, n);       // Maximum index to consider in `a`

      while (lo <= hi) {
         // Partition indices
         int mid1 = (lo + hi) / 2;     // Partition index in `a`
         int mid2 = k - mid1;          // Partition index in `b`

         // Elements to the left and right of the partition in `a`
         int l1 = (mid1 == 0 ? Integer.MIN_VALUE : a[mid1 - 1]);    // Left element in `a`
         int r1 = (mid1 == n ? Integer.MAX_VALUE : a[mid1]);        // Right element in `a`

         // Elements to the left and right of the partition in `b`
         int l2 = (mid2 == 0 ? Integer.MIN_VALUE : b[mid2 - 1]);    // Left element in `b`
         int r2 = (mid2 == m ? Integer.MAX_VALUE : b[mid2]);        // Right element in `b`

         // Check if a valid partition is achieved
         if (l1 <= r2 && l2 <= r1) {
            // Maximum of left elements is the kth element
            return Math.max(l1, l2);
         }

         // Adjust binary search range
         if (l1 > r2) {
            // Move the partition in `a` to the left
            hi = mid1 - 1;
         } else {
            // Move the partition in `a` to the right
            lo = mid1 + 1;
         }
      }

      // This point should never be reached
      return 0;
   }
}
