/*
 * Smallest Positive Missing Number
 *
 * You are given an integer array arr[]. Your task is to find the smallest positive number missing from the array.
 * Note: Positive number starts from 1. The array can have negative integers too.
 *
 * Examples:
 *
 * Input: arr[] = [2, -3, 4, 1, 1, 7]
 * Output: 3
 * Explanation: Smallest positive missing number is 3.
 *
 * Input: arr[] = [5, 3, 2, 5, 1]
 * Output: 4
 * Explanation: Smallest positive missing number is 4.
 *
 * Input: arr[] = [-8, 0, -1, -4, -3]
 * Output: 1
 * Explanation: Smallest positive missing number is 1.
 *
 * Constraints:
 * 1 <= arr.size() <= 10^5
 * -10^6 <= arr[i] <= 10^6
 */

/************************************************************ JAVA ************************************************/

class Solution {
   // Function to find the smallest positive number missing from the array.
   public int missingNumber(int[] arr){
      int n = arr.length;

      Arrays.sort(arr);

      int num = 1;
      for (int i = 0; i < n; i++) {
         if (arr[i] <= 0) {
            continue;
         }
         if (i > 0 && arr[i] == arr[i - 1]) {
            continue;
         }
         if (arr[i] != num) {
            return num;
         }
         num++;
      }
      return num;
   }
}
