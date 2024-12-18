/*
 * Allocate Minimum Pages
 *
 * You are given an array arr[] of integers, where each element arr[i] represents the number of pages in the ith book. You also have an integer k representing the number of students. The task is to allocate books to each student such that:
 * Each student receives atleast one book.
 * Each student is assigned a contiguous sequence of books.
 * No book is assigned to more than one student.
 * The objective is to minimize the maximum number of pages assigned to any student. In other words, out of all possible allocations, find the arrangement where the student who receives the most pages still has the smallest possible maximum.
 *
 * Note: Return -1 if a valid assignment is not possible, and allotment should be in contiguous order (see the explanation for better understanding).
 *
 * Examples:
 *
 * Input: arr[] = [12, 34, 67, 90], k = 2
 * Output: 113
 * Explanation: Allocation can be done in following ways:
 * [12] and [34, 67, 90] Maximum Pages = 191
 * [12, 34] and [67, 90] Maximum Pages = 157
 * [12, 34, 67] and [90] Maximum Pages = 113.
 * Therefore, the minimum of these cases is 113, which is selected as the output.
 *
 * Input: arr[] = [15, 17, 20], k = 5
 * Output: -1
 * Explanation: Allocation can not be done.
 *
 * Input: arr[] = [22, 23, 67], k = 1
 * Output: 112
 * Constraints:
 * 1 <=  arr.size() <= 10^6
 * 1 <= arr[i] <= 10^3
 * 1 <= k <= 10^3
 */

/************************************************************ C++ ************************************************/

// Approach: Binary search on the maximum pages combined with a greedy check for valid allocation.
// Time Complexity: O(N * log(S)) (binary search on sum S with O(N) for each allocation check).
// Space Complexity: O(1) (constant extra space).
class Solution {
public:
   // Function to check if it is possible to allocate books such that
   // no student gets more than maxPages pages.
   bool isPossible(vector<int>&arr, int n, int k, int maxPages){
      int studentCount = 1, currentSum = 0;

      for (int i = 0; i < n; i++) {
         if (arr[i] > maxPages) {
            return false;     // If a single book has more pages than maxPages, allocation is impossible.
         }
         if (currentSum + arr[i] > maxPages) {
            studentCount++;      // Allocate to a new student
            currentSum = arr[i]; // Start new allocation
            if (studentCount > k) {
               return false;     // More students required than available
            }
         } else {
            currentSum += arr[i];
         }
      }
      return true;
   }

   // Function to find the minimum number of pages.
   int findPages(vector<int>&arr, int k){
      int n = arr.size();

      if (k > n) {
         return -1;    // Not enough books for each student to get at least one
      }

      int low    = *max_element(arr.begin(), arr.end());
      int high   = accumulate(arr.begin(), arr.end(), 0);
      int result = -1;

      // Binary search on the number of pages.
      while (low <= high) {
         int mid = low + (high - low) / 2;
         if (isPossible(arr, n, k, mid)) {
            result = mid;     // Update result to the current valid allocation
            high   = mid - 1; // Try for a smaller maximum
         } else {
            low = mid + 1;    // Increase the maximum allowed pages
         }
      }

      return result;
   }
};

/************************************************************ JAVA ************************************************/

// Approach: Binary search on the maximum pages combined with a greedy check for valid allocation.
// Time Complexity: O(N * log(S)) (binary search on sum S with O(N) for each allocation check).
// Space Complexity: O(1) (constant extra space)
class Solution {
   // Function to check if it is possible to allocate books such that
   // no student gets more than maxPages pages.
   public static boolean isPossible(int[] arr, int n, int k, int maxPages){
      int studentCount = 1, currentSum = 0;

      for (int i = 0; i < n; i++) {
         if (arr[i] > maxPages) {
            return false;     // If a single book has more pages than maxPages, allocation is impossible.
         }
         if (currentSum + arr[i] > maxPages) {
            studentCount++;      // Allocate to a new student
            currentSum = arr[i]; // Start new allocation
            if (studentCount > k) {
               return false;     // More students required than available
            }
         } else {
            currentSum += arr[i];
         }
      }
      return true;
   }

   // Function to find the minimum number of pages.
   public static int findPages(int[] arr, int k){
      int n = arr.length;

      if (k > n) {
         return -1;    // Not enough books for each student to get at least one
      }

      int low = Integer.MIN_VALUE, high = 0;
      for (int i : arr) {
         low   = Math.max(low, i);
         high += i;
      }
      int result = -1;

      // Binary search on the number of pages.
      while (low <= high) {
         int mid = low + (high - low) / 2;
         if (isPossible(arr, n, k, mid)) {
            result = mid;     // Update result to the current valid allocation
            high   = mid - 1; // Try for a smaller maximum
         } else {
            low = mid + 1;    // Increase the maximum allowed pages
         }
      }

      return result;
   }
}
