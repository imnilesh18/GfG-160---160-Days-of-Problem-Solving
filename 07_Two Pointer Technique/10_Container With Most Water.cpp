/*
 * Container With Most Water
 *
 * Given an array arr[] of non-negative integers, where each element arr[i] represents the height of the vertical lines, find the maximum amount of water that can be contained between any two lines, together with the x-axis.
 * Note: In the case of a single vertical line it will not be able to hold water.
 *
 * Examples:
 *
 * Input: arr[] = [1, 5, 4, 3]
 * Output: 6
 * Explanation: 5 and 3 are 2 distance apart. So the size of the base is 2. Height of container = min(5, 3) = 3. So, total area to hold water = 3 * 2 = 6.
 *
 * Input: arr[] = [3, 1, 2, 4, 5]
 * Output: 12
 * Explanation: 5 and 3 are 4 distance apart. So the size of the base is 4. Height of container = min(5, 3) = 3. So, total area to hold water = 4 * 3 = 12.
 *
 * Input: arr[] = [2, 1, 8, 6, 4, 6, 5, 5]
 * Output: 25
 * Explanation: 8 and 5 are 5 distance apart. So the size of the base is 5. Height of container = min(8, 5) = 5. So, the total area to hold water = 5 * 5 = 25.
 *
 * Constraints:
 * 1<= arr.size() <=10^5
 * 1<= arr[i] <=10^4
 */
/************************************************************ C++ ************************************************/

// Approach: Use two-pointer technique - keep two pointers at start and end, calculate area between them, and move the pointer pointing to smaller height inward.
// TC: O(n) where n is the size of array - we traverse the array once with two pointers.
// SC: O(1) as we only use constant extra space regardless of input size.
class Solution {
public:
   int maxWater(vector<int>&arr){
      int n = arr.size();
      // Initialize two pointers at start and end of array
      int i = 0;
      int j = n - 1;

      // Variable to store maximum water that can be contained
      int maxWater = 0;

      // Continue until the two pointers meet
      while (i < j) {
         // Calculate width between the two lines
         int w = j - i;
         // Height will be minimum of the two lines
         int h = min(arr[i], arr[j]);

         // Calculate area that can hold water
         int area = w * h;

         // Update maxWater if current area is greater
         maxWater = max(maxWater, area);

         // Move the pointer pointing to smaller height
         // as moving the larger height pointer won't help in increasing area
         if (arr[i] > arr[j]) {
            j--;
         } else {
            i++;
         }
      }
      return maxWater;
   }
};

/************************************************************ JAVA ************************************************/

// Approach: Use two-pointer technique - keep two pointers at start and end, calculate area between them, and move the pointer pointing to smaller height inward.
// TC: O(n) where n is the size of array - we traverse the array once with two pointers.
// SC: O(1) as we only use constant extra space regardless of input size.
class Solution {
   public int maxWater(int arr[]){
      int n = arr.length;
      // Initialize two pointers at start and end of array
      int i = 0;
      int j = n - 1;

      // Variable to store maximum water that can be contained
      int maxWater = 0;

      // Continue until the two pointers meet
      while (i < j) {
         // Calculate width between the two lines
         int w = j - i;
         // Height will be minimum of the two lines
         int h = Math.min(arr[i], arr[j]);

         // Calculate area that can hold water
         int area = w * h;

         // Update maxWater if current area is greater
         maxWater = Math.max(maxWater, area);

         // Move the pointer pointing to smaller height
         // as moving the larger height pointer won't help in increasing area
         if (arr[i] > arr[j]) {
            j--;
         } else {
            i++;
         }
      }
      return maxWater;
   }
}
