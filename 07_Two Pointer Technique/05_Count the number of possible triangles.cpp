/*
 * Count the number of possible triangles
 *
 * Given an integer array arr[]. Find the number of triangles that can be formed with three different array elements as lengths of three sides of the triangle.
 *
 * A triangle with three given sides is only possible if sum of any two sides is always greater than the third side.
 *
 * Examples:
 * Input: arr[] = [4, 6, 3, 7]
 * Output: 3
 * Explanation: There are three triangles possible [3, 4, 6], [4, 6, 7] and [3, 6, 7]. Note that [3, 4, 7] is not a possible triangle.
 * Input: arr[] = [10, 21, 22, 100, 101, 200, 300]
 * Output: 6
 * Explanation: There can be 6 possible triangles: [10, 21, 22], [21, 100, 101], [22, 100, 101], [10, 100, 101], [100, 101, 200] and [101, 200, 300]
 * Input: arr[] = [1, 2, 3]
 * Output: 0
 * Explanation: No triangles are possible.
 *
 * Constraints:
 * 3 <= arr.size() <= 10^3
 * 1 <= arr[i] <= 10^5
 */

/************************************************************ C++ ************************************************/

// Approach: Sort the array and use a binary search to count the number of valid triangles formed by each pair of sides.
// Time Complexity: O(n² * log n), where `n` is the number of elements in the array (due to nested loops and binary search).
// Space Complexity: O(n), for storing the sorted array.
class Solution {
private:
   // Binary search function to find the first index with a value >= x
   int binarySearch(vector<int>& arr, int left, int right, int x){
      // While the range is valid (right >= left)
      while (right >= left && right < arr.size()) {
         // Calculate mid index
         int mid = left + (right - left) / 2;

         // If the value at mid is greater than or equal to x, search in the left part
         if (arr[mid] >= x) {
            right = mid - 1;
         } else {
            // Otherwise, search in the right part
            left = mid + 1;
         }
      }
      // Return the left index, which is the first element >= x
      return left;
   }

public:
   // Function to count the number of possible triangles
   int countTriangles(vector<int>& arr){
      int count = 0;          // Variable to store the number of triangles
      int n     = arr.size(); // Size of the array

      // Sort the array to use binary search effectively
      sort(arr.begin(), arr.end());

      // Iterate through the array with the first pointer (i)
      for (int i = 0; i < n - 2; i++) {
         int k = i + 2;    // Initialize the third pointer (k) to i + 2

         // Iterate with the second pointer (j), which starts from i + 1
         for (int j = i + 1; j < n - 1 && arr[i] != 0; j++) {
            // Perform binary search to find the index where the sum of arr[i] and arr[j] is greater
            k = binarySearch(arr, k, n - 1, arr[i] + arr[j]);

            // Add the count of triangles formed by arr[i] and arr[j]
            count += k - j - 1;
         }
      }

      // Return the total count of triangles
      return count;
   }
};

/************************************************************ JAVA ************************************************/

// Approach: Sort the array and use a binary search to count the number of valid triangles formed by each pair of sides.
// Time Complexity: O(n² * log n), where `n` is the number of elements in the array (due to nested loops and binary search).
// Space Complexity: O(n), for storing the sorted array.
class Solution {
    // Binary search function to find the first index with a value >= x
    static int binarySearch(int arr[], int left, int right, int x) {
        // While the range is valid (right >= left)
        while (right >= left && right < arr.length) {
            // Calculate mid index
            int mid = left + (right - left) / 2;
            
            // If the value at mid is greater than or equal to x, search in the left part
            if (arr[mid] >= x) {
                right = mid - 1;
            } else {
                // Otherwise, search in the right part
                left = mid + 1;
            }
        }
        // Return the left index, which is the first element >= x
        return left;
    }
    
    // Function to count the number of possible triangles.
    static int countTriangles(int arr[]) {
        int count = 0; // Variable to store the number of triangles
        int n = arr.length; // Size of the array
        
        // Sort the array to use binary search effectively
        Arrays.sort(arr);
        
        // Iterate through the array with the first pointer (i)
        for (int i = 0; i < n - 2; i++) {
            int k = i + 2; // Initialize the third pointer (k) to i + 2
            
            // Iterate with the second pointer (j), which starts from i + 1
            for (int j = i + 1; j < n - 1 && arr[i] != 0; j++) {
                // Perform binary search to find the index where the sum of arr[i] and arr[j] is greater
                k = binarySearch(arr, k, n - 1, arr[i] + arr[j]);
                
                // Add the count of triangles formed by arr[i] and arr[j]
                count += k - j - 1;
            }
        }
        
        // Return the total count of triangles
        return count;
    }
}