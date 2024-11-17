// Problem Link: https://www.geeksforgeeks.org/problems/rotate-array-by-n-elements-1587115621/1

/*
 * Rotate Array
 *
 * Given an unsorted array arr[]. Rotate the array to the left (counter-clockwise direction) by d steps, where d is a positive integer. Do the mentioned change in the array in place.
 * Note: Consider the array as circular.
 *
 * Examples :
 * Input: arr[] = [1, 2, 3, 4, 5], d = 2
 * Output: [3, 4, 5, 1, 2]
 * Explanation: when rotated by 2 elements, it becomes 3 4 5 1 2.
 *
 * Input: arr[] = [2, 4, 6, 8, 10, 12, 14, 16, 18, 20], d = 3
 * Output: [8, 10, 12, 14, 16, 18, 20, 2, 4, 6]
 * Explanation: when rotated by 3 elements, it becomes 8 10 12 14 16 18 20 2 4 6.
 *
 * Input: arr[] = [7, 3, 9, 1], d = 9
 * Output: [3, 9, 1, 7]
 * Explanation: when we rotate 9 times, we'll get 3 9 1 7 as resultant array.
 *
 * Constraints:
 * 1 <= arr.size(), d <= 10^5
 * 0 <= arr[i] <= 10^5
 */


/************************************************************ C++ ************************************************/

// Brute Force: Using Extra Space
// T.C: O(n + d)
// S.C: O(d)
class Solution {
public:
   // Function to rotate an array by d elements in counter-clockwise direction.
   void rotateArr(vector<int>& arr, int d) {
      int n = arr.size(); // Get the size of the array

      // If d is greater than the size of the array, reduce it by taking modulo n
      // This handles cases where d > n and ensures rotation is within bounds.
      d = d % n;

      // Step 1: Store the first d elements in a temporary array
      int temp[d];
      for (int i = 0; i < d; i++) {
         temp[i] = arr[i]; // Copy first d elements into temp
      }

      // Step 2: Shift the remaining elements in the array to the left
      for (int i = d; i < n; i++) {
         arr[i - d] = arr[i]; // Move elements from index d to n-1 to the start
      }

      // Step 3: Copy the elements from the temporary array back to the original array
      for (int i = n - d; i < n; i++) {
         arr[i] = temp[i - (n - d)]; // Fill the last d positions with temp array
      }
   }
};

// Optimal Approach: Using Reverse
// T.C: O(d) + O(n - d) + O(n) = O(2n)
// S.C: O(1)
class Solution {
public:
   // Function to rotate an array by d elements in counter-clockwise direction.
   void rotateArr(vector<int>& arr, int d) {
      int n = arr.size();

      // Ensure d is within bounds by using modulo.
      d = d % n;

      // Step 1: Reverse the first d elements
      reverse(arr.begin(), arr.begin() + d);

      // Step 2: Reverse the remaining elements
      reverse(arr.begin() + d, arr.end());

      // Step 3: Reverse the entire array
      reverse(arr.begin(), arr.end());
   }
};

/************************************************************ JAVA ************************************************/

// Brute Force: Using Extra Space
// T.C: O(n + d)
// S.C: O(d)
class Solution {
   // Function to rotate an array by d elements in a counter-clockwise direction.
   static void rotateArr(int arr[], int d) {
      int n = arr.length;   // Get the size of the array

      // If d is greater than the size of the array, reduce it using modulo n
      // This ensures rotations are within bounds.
      d = d % n;

      // Step 1: Store the first d elements in a temporary array
      int[] temp = new int[d];
      for (int i = 0; i < d; i++) {
         temp[i] = arr[i];    // Copy first d elements into temp
      }

      // Step 2: Shift the remaining elements in the array to the left
      for (int i = d; i < n; i++) {
         arr[i - d] = arr[i];    // Move elements from index d to n-1 to the start
      }

      // Step 3: Copy the elements from the temporary array back to the original array
      for (int i = 0; i < d; i++) {
         arr[n - d + i] = temp[i];    // Fill the last d positions with temp array
      }
   }
}

// Optimal Approach: Using Reverse
// T.C: O(d) + O(n - d) + O(n) = O(2n)
// S.C: O(1)
class Solution {
   // Function to rotate an array by d elements in counter-clockwise direction.
   static void rotateArr(int arr[], int d) {
      int n = arr.length;   // Get the size of the array

      // Handle cases where d is greater than n
      d = d % n;

      // Step 1: Reverse the first d elements
      reverse(arr, 0, d - 1);

      // Step 2: Reverse the remaining elements
      reverse(arr, d, n - 1);

      // Step 3: Reverse the entire array
      reverse(arr, 0, n - 1);
   }

   // Helper function to reverse a portion of the array
   private static void reverse(int[] arr, int start, int end) {
      while (start < end) {
         // Swap the elements at indices start and end
         int temp = arr[start];
         arr[start] = arr[end];
         arr[end] = temp;

         // Move the pointers towards the center
         start++;
         end--;
      }
   }
}

