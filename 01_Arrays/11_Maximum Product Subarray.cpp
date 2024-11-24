/*
 * Maximum Product Subarray
 *
 * Given an array arr[] that contains positive and negative integers (may contain 0 as well). Find the maximum product that we can get in a subarray of arr.
 *
 * Note: It is guaranteed that the output fits in a 32-bit integer.
 *
 * Examples
 * Input: arr[] = [-2, 6, -3, -10, 0, 2]
 * Output: 180
 * Explanation: The subarray with maximum product is {6, -3, -10} with product = 6 * (-3) * (-10) = 180.
 *
 * Input: arr[] = [-1, -3, -10, 0, 60]
 * Output: 60
 * Explanation: The subarray with maximum product is {60}.
 *
 * Input: arr[] = [2, 3, 4]
 * Output: 24
 * Explanation: For an array with all positive elements, the result is product of all elements.
 *
 * Constraints:
 * 1 ≤ arr.size() ≤ 10^6
 * -10  ≤  arr[i]  ≤  10
 */

/************************************************************ C++ ************************************************/

// T.C: O(n)
// S.C: O(1)
class Solution {
public:
   // Function to find maximum product subarray
   int maxProduct(vector<int>& arr){
      // Initialize variables
      int n             = arr.size();
      int maxProduct    = arr[0];
      int maxEndingHere = arr[0];
      int minEndingHere = arr[0];

      // Iterate through the array
      for (int i = 1; i < n; ++i) {
         if (arr[i] < 0) {
            // Swap max and min when current element is negative
            swap(maxEndingHere, minEndingHere);
         }

         // Update maxEndingHere and minEndingHere
         maxEndingHere = max(arr[i], maxEndingHere * arr[i]);
         minEndingHere = min(arr[i], minEndingHere * arr[i]);

         // Update global maximum product
         maxProduct = max(maxProduct, maxEndingHere);
      }

      return maxProduct;
   }
};

/************************************************************ JAVA ************************************************/

// T.C: O(n)
// S.C: O(1)

class Solution {
   // Function to find maximum product subarray
   int maxProduct(int[] arr){
      // Initialize variables
      int maxProduct    = arr[0];
      int maxEndingHere = arr[0];
      int minEndingHere = arr[0];

      // Iterate through the array
      for (int i = 1; i < arr.length; i++) {
         // If the current element is negative, swap max and min
         if (arr[i] < 0) {
            int temp = maxEndingHere;
            maxEndingHere = minEndingHere;
            minEndingHere = temp;
         }

         // Update maxEndingHere and minEndingHere
         maxEndingHere = Math.max(arr[i], maxEndingHere * arr[i]);
         minEndingHere = Math.min(arr[i], minEndingHere * arr[i]);

         // Update global maximum product
         maxProduct = Math.max(maxProduct, maxEndingHere);
      }

      return maxProduct;
   }
}
