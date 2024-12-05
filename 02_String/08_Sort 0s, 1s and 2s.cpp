/*
 * Sort 0s, 1s and 2s
 *
 * Given an array arr[] containing only 0s, 1s, and 2s. Sort the array in ascending order.
 *
 * Examples:
 * Input: arr[] = [0, 1, 2, 0, 1, 2]
 * Output: [0, 0, 1, 1, 2, 2]
 * Explanation: 0s 1s and 2s are segregated into ascending order.
 *
 * Input: arr[] = [0, 1, 1, 0, 1, 2, 1, 2, 0, 0, 0, 1]
 * Output: [0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 2, 2]
 * Explanation: 0s 1s and 2s are segregated into ascending order.
 *
 * Constraints:
 * 1 <= arr.size() <= 10^6
 * 0 <= arr[i] <= 2
 */

/*
 * The algorithm used here is based on the Dutch National Flag problem, which was proposed by Edsger W. Dijkstra.
 *
 * Problem Description
 * The Dutch National Flag problem is about sorting an array containing three distinct elements (e.g., 0, 1, and 2) into a specific order: all elements of the first type come first, followed by all elements of the second type, and finally, all elements of the third type.
 *
 * Algorithm Explanation
 * In this context:
 * 0 corresponds to the "red" region.
 * 1 corresponds to the "white" region.
 * 2 corresponds to the "blue" region.
 *
 * The algorithm works with three pointers:
 * low: Marks the boundary for 0s (red region).
 * mid: The current element being checked.
 * high: Marks the boundary for 2s (blue region).
 *
 * Steps:
 * Start with all elements unclassified.
 * If the current element (arr[mid]) is:
 * 0: Swap it with the element at low, then move both low and mid forward.
 * 1: It's already in the correct region; just move mid forward.
 * 2: Swap it with the element at high, then move high backward.
 * Repeat until mid surpasses high.
 *
 * Why It Works
 * The algorithm partitions the array into three regions in one pass:
 * [0 ... low-1]: All 0s.
 * [low ... mid-1]: All 1s.
 * [high+1 ... n-1]: All 2s.
 * This ensures sorting is achieved in O(n) time and O(1) space.
 *
 * The provided algorithm is an implementation of the Dutch National Flag theorem.
 */

/************************************************************ C++ ************************************************/

// T.C: O(n)
// S.C: O(1)
class Solution {
public:
   void sort012(vector<int>& arr){
      int n = arr.size();
      int low = 0, mid = 0, high = n - 1;

      while (mid <= high) {
         if (arr[mid] == 0) {
            swap(arr[low], arr[mid]);
            low++;
            mid++;
         } else if (arr[mid] == 1) {
            mid++;
         } else {
            swap(arr[mid], arr[high]);
            high--;
         }
      }
   }
};

/************************************************************ JAVA ************************************************/

// T.C: O(n)
// S.C: O(1)
class Solution {
   public static void swap(int[] arr, int i, int j){
      int temp = arr[i];

      arr[i] = arr[j];
      arr[j] = temp;
   }

   // Function to sort an array of 0s, 1s, and 2s
   public void sort012(int[] arr){
      int n    = arr.length;
      int low  = 0;
      int mid  = 0;
      int high = n - 1;

      while (mid <= high) {
         if (arr[mid] == 0) {
            swap(arr, mid, low);
            low++;
            mid++;
         }else if (arr[mid] == 1) {
            mid++;
         }else {
            swap(arr, mid, high);
            high--;
         }
      }
   }
}
