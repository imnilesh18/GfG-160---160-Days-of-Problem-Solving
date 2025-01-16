/*
 * Product array puzzle
 *
 * Given an array, arr[] construct a product array, res[] where each element in res[i] is the product of all elements in arr[] except arr[i]. Return this resultant array, res[].
 * Note: Each element is res[] lies inside the 32-bit integer range.
 *
 * Examples:
 *
 * Input: arr[] = [10, 3, 5, 6, 2]
 * Output: [180, 600, 360, 300, 900]
 * Explanation: For i=0, res[i] = 3 * 5 * 6 * 2 is 180.
 * For i = 1, res[i] = 10 * 5 * 6 * 2 is 600.
 * For i = 2, res[i] = 10 * 3 * 6 * 2 is 360.
 * For i = 3, res[i] = 10 * 3 * 5 * 2 is 300.
 * For i = 4, res[i] = 10 * 3 * 5 * 6 is 900.
 *
 * Input: arr[] = [12, 0]
 * Output: [0, 12]
 * Explanation: For i = 0, res[i] is 0.
 * For i = 1, res[i] is 12.
 *
 * Constraints:
 * 2 <= arr.size() <= 10^5
 * -100 <= arr[i] <= 100
 */

/************************************************************ C++ ************************************************/

// Approach 1: Calculate product of all non-zero numbers and handle cases based on count of zeros in array
// Time Complexity: O(N) where N is size of array as we traverse array twice
// Space Complexity: O(1) excluding output array as we only use constant extra space for variables
class Solution {
public:
   vector<int> productExceptSelf(vector<int>& arr){
      int n = arr.size();
      // Variable to store product of all non-zero elements
      int allProducts = 1;
      // Counter to keep track of number of zeros in array
      int zeroCount = 0;
      // Store index of zero if there is exactly one zero
      int zeroIdx = -1;

      // First pass: Calculate product of all non-zero elements
      // and count number of zeros
      for (int i = 0; i < n; i++) {
         if (arr[i] == 0) {
            zeroCount++;
            zeroIdx = i;
         } else {
            allProducts *= arr[i];
         }
      }

      // Initialize result array with zeros
      vector<int> result(n, 0);

      // Case 1: If there are more than one zeros
      // All elements in result will be zero since product will always include at least one zero
      if (zeroCount > 1) {
         return result;
      }
      // Case 2: If there is exactly one zero
      // Only the element at zero's position will have non-zero value
      else if (zeroCount == 1) {
         result[zeroIdx] = allProducts;
      }
      // Case 3: If there are no zeros
      // Each element will be product of all numbers divided by itself
      else {
         for (int i = 0; i < n; i++) {
            result[i] = allProducts / arr[i];
         }
      }

      return result;
   }
};

// Approach 2: Use Prefix and Suffix product - for each index i, multiply prefix product (0 to i-1) with suffix product (i+1 to n-1)
// Time Complexity: O(N) where N is size of array as we traverse array twice - once for prefix and once for suffix products
// Space Complexity: O(1) excluding output array as we only use one variable 'prod' for suffix calculation
class Solution {
public:
   vector<int> productExceptSelf(vector<int>& arr){
      int n = arr.size();
      // Initialize result array with 1s since we'll multiply values into it
      vector<int> ans(n, 1);

      // First pass L->R: Calculate prefix products
      // For each index i, ans[i] will contain product of all numbers from index 0 to i-1
      for (int i = 1; i < n; i++) {
         ans[i] = ans[i - 1] * arr[i - 1];
      }

      // Second pass R->L: Calculate suffix products and combine with prefix
      // Variable prod maintains running product of all numbers from right
      int prod = 1;
      for (int i = n - 2; i >= 0; i--) {
         prod  *= arr[i + 1];      // Update prod to include next number from right
         ans[i] = ans[i] * prod;   // Multiply prefix product with suffix product
      }

      return ans;
   }
};

/************************************************************ JAVA ************************************************/

// Approach 1: Calculate product of all non-zero numbers and handle cases based on count of zeros in array
// Time Complexity: O(N) where N is size of array as we traverse array twice
// Space Complexity: O(1) excluding output array as we only use constant extra space for variables
class Solution {
   public static int[] productExceptSelf(int arr[]){
      int n = arr.length;
      // Variable to store product of all non-zero elements
      int allProducts = 1;
      // Counter to keep track of number of zeros in array
      int zeroCount = 0;
      // Store index of zero if there is exactly one zero
      int zeroIdx = -1;

      // First pass: Calculate product of all non-zero elements
      // and count number of zeros
      for (int i = 0; i < n; i++) {
         if (arr[i] == 0) {
            zeroCount++;
            zeroIdx = i;
         } else {
            allProducts *= arr[i];
         }
      }

      // Initialize result array with zeros
      int[] result = new int[n];

      // Case 1: If there are more than one zeros
      // All elements in result will be zero since product will always include at least one zero
      if (zeroCount > 1) {
         return result;
      }
      // Case 2: If there is exactly one zero
      // Only the element at zero's position will have non-zero value
      else if (zeroCount == 1) {
         result[zeroIdx] = allProducts;
      }
      // Case 3: If there are no zeros
      // Each element will be product of all numbers divided by itself
      else {
         for (int i = 0; i < n; i++) {
            result[i] = allProducts / arr[i];
         }
      }

      return result;
   }
}

// Approach 2: Use Prefix and Suffix product - for each index i, multiply prefix product (0 to i-1) with suffix product (i+1 to n-1)
// Time Complexity: O(N) where N is size of array as we traverse array twice - once for prefix and once for suffix products
// Space Complexity: O(1) excluding output array as we only use one variable 'prod' for suffix calculation
class Solution {
   public static int[] productExceptSelf(int arr[]){
      int n = arr.length;
      // Initialize result array with 1s since we'll multiply values into it
      int[] ans = new int[n];

      Arrays.fill(ans, 1);

      // First pass L->R: Calculate prefix products
      // For each index i, ans[i] will contain product of all numbers from index 0 to i-1
      for (int i = 1; i < n; i++) {
         ans[i] = ans[i - 1] * arr[i - 1];
      }

      // Second pass R->L: Calculate suffix products and combine with prefix
      // Variable prod maintains running product of all numbers from right
      int prod = 1;
      for (int i = n - 2; i >= 0; i--) {
         prod  *= arr[i + 1];      // Update prod to include next number from right
         ans[i] = ans[i] * prod;   // Multiply prefix product with suffix product
      }

      return ans;
   }
}
