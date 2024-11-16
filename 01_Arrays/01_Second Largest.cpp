/*
 * Second Largest
 *
 * Given an array of positive integers arr[], return the second largest element from the array. If the second largest element doesn't exist then return -1.
 * Note: The second largest element should not be equal to the largest element.
 *
 * Examples:
 * Input: arr[] = [12, 35, 1, 10, 34, 1]
 * Output: 34
 * Explanation: The largest element of the array is 35 and the second largest element is 34.
 *
 * Input: arr[] = [10, 5, 10]
 * Output: 5
 * Explanation: The largest element of the array is 10 and the second largest element is 5.
 *
 * Input: arr[] = [10, 10, 10]
 * Output: -1
 * Explanation: The largest element of the array is 10 and the second largest element does not exist.
 *
 * Constraints:
 * 2 ≤ arr.size() ≤ 10^5
 * 1 ≤ arr[i] ≤ 10^5
 */

// T.C : O(n)
// S.C : O(1)
class Solution {
public:
   // Function returns the second
   // largest elements
   int getSecondLargest(vector<int>& arr){
      int largest       = -1;
      int secondLargest = -1;

      for (int&num : arr) {
         if (num > largest) {
            secondLargest = largest;
            largest       = num;
         } else if (num < largest) {
            secondLargest = max(secondLargest, num);
         }
      }
      return secondLargest;
   }
};
