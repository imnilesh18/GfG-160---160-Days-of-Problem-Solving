/*
 * Number of occurrence
 *
 * Given a sorted array, arr[] and a number target, you need to find the number of occurrences of target in arr[].
 *
 * Examples :
 *
 * Input: arr[] = [1, 1, 2, 2, 2, 2, 3], target = 2
 * Output: 4
 * Explanation: target = 2 occurs 4 times in the given array so the output is 4.
 *
 * Input: arr[] = [1, 1, 2, 2, 2, 2, 3], target = 4
 * Output: 0
 * Explanation: target = 4 is not present in the given array so the output is 0.
 *
 * Input: arr[] = [8, 9, 10, 12, 12, 12], target = 12
 * Output: 3
 * Explanation: target = 12 occurs 3 times in the given array so the output is 3.
 *
 * Constraints:
 * 1 ≤ arr.size() ≤ 10^6
 * 1 ≤ arr[i] ≤ 10^6
 * 1 ≤ target ≤ 10^6
 */

/************************************************************ C++ ************************************************/

// Approach 1: Linear Search
// Time and Space Complexities:
// Time Complexity: O(n) (Traverse the array of size n once).
// Space Complexity: O(1) (Constant space used for the counter cnt).
class Solution {
public:
   // Function to count the frequency of a target element in the array
   int countFreq(vector<int>& arr, int target){
      int cnt = 0;                           // Initialize counter to store frequency

      for (int i = 0; i < arr.size(); i++) { // Loop through each element in the array
         if (arr[i] == target) {             // If the current element matches the target
            cnt++;                           // Increment the counter
         }
      }
      return cnt;   // Return the final count
   }
};

// Approach 2: Binary Search
// Time Complexity: O(log n) (Two binary searches reduce the search space logarithmically).
// Space Complexity: O(1) (Constant space as no additional data structures are used) .
class Solution {
public:
   // Function to find the first occurrence of the target in a sorted array
   int firstOcc(vector<int>& arr, int target){
      int s = 0, e = arr.size() - 1; // Initialize start and end pointers
      int ans = -1;                  // Variable to store the index of the first occurrence

      while (s <= e) {               // Perform binary search
         int mid = s + (e - s) / 2;  // Avoid potential overflow // Calculate the middle index
         if (arr[mid] == target) {
            ans = mid;               // Update the answer with the current index
            e   = mid - 1;           // Move to the left half to find earlier occurrences
         } else if (arr[mid] > target) {
            e = mid - 1;             // Target lies in the left half
         } else {
            s = mid + 1;             // Target lies in the right half
         }
      }
      return ans;   // Return the index of the first occurrence, or -1 if not found
   }

   // Function to find the last occurrence of the target in a sorted array
   int lastOcc(vector<int>& arr, int target){
      int s = 0, e = arr.size() - 1; // Initialize start and end pointers
      int ans = -1;                  // Variable to store the index of the last occurrence

      while (s <= e) {               // Perform binary search
         int mid = s + (e - s) / 2;  // Avoid potential overflow // Calculate the middle index
         if (arr[mid] == target) {
            ans = mid;               // Update the answer with the current index
            s   = mid + 1;           // Move to the right half to find later occurrences
         } else if (arr[mid] > target) {
            e = mid - 1;             // Target lies in the left half
         } else {
            s = mid + 1;             // Target lies in the right half
         }
      }
      return ans;   // Return the index of the last occurrence, or -1 if not found
   }

   // Function to count the frequency of a target element in the array
   int countFreq(vector<int>& arr, int target){
      // If the target is not present, both firstOcc and lastOcc will return -1
      if (lastOcc(arr, target) == -1 && firstOcc(arr, target) == -1) {
         return 0;    // Target is not present in the array
      }
      // Calculate the frequency as the difference between last and first occurrence
      return lastOcc(arr, target) - firstOcc(arr, target) + 1;
   }
};



/************************************************************ JAVA ************************************************/

// Approach 1: Linear Search
// Time and Space Complexities:
// Time Complexity: O(n) (Traverse the array of size n once).
// Space Complexity: O(1) (Constant space used for the counter cnt).
class Solution {
   // Function to count the frequency of a target element in the array
   public int countFreq(int[] arr, int target){
      int cnt = 0;                           // Initialize counter to store frequency

      for (int i = 0; i < arr.length; i++) { // Loop through each element in the array
         if (arr[i] == target) {             // If the current element matches the target
            cnt++;                           // Increment the counter
         }
      }
      return cnt;   // Return the final count
   }
}

// Approach 2: Binary Search
// Time Complexity: O(log n) (Two binary searches reduce the search space logarithmically).
// Space Complexity: O(1) (Constant space as no additional data structures are used) .
class Solution {
   // Function to find the first occurrence of the target in a sorted array
   public int firstOcc(int[] arr, int target){
      int s = 0, e = arr.length - 1; // Initialize start and end pointers
      int ans = -1;                  // Variable to store the index of the first occurrence

      while (s <= e) {               // Perform binary search
         int mid = s + (e - s) / 2;  // Calculate the middle index (to avoid overflow)
         if (arr[mid] == target) {
            ans = mid;               // Update the answer with the current index
            e   = mid - 1;           // Move to the left half to find earlier occurrences
         } else if (arr[mid] > target) {
            e = mid - 1;             // Target lies in the left half
         } else {
            s = mid + 1;             // Target lies in the right half
         }
      }
      return ans;   // Return the index of the first occurrence, or -1 if not found
   }

   // Function to find the last occurrence of the target in a sorted array
   public int lastOcc(int[] arr, int target){
      int s = 0, e = arr.length - 1; // Initialize start and end pointers
      int ans = -1;                  // Variable to store the index of the last occurrence

      while (s <= e) {               // Perform binary search
         int mid = s + (e - s) / 2;  // Calculate the middle index (to avoid overflow)
         if (arr[mid] == target) {
            ans = mid;               // Update the answer with the current index
            s   = mid + 1;           // Move to the right half to find later occurrences
         } else if (arr[mid] > target) {
            e = mid - 1;             // Target lies in the left half
         } else {
            s = mid + 1;             // Target lies in the right half
         }
      }
      return ans;   // Return the index of the last occurrence, or -1 if not found
   }

   // Function to count the frequency of a target element in the array
   public int countFreq(int[] arr, int target){
      // If the target is not present, both firstOcc and lastOcc will return -1
      int first = firstOcc(arr, target);

      if (first == -1) {
         return 0;    // Target is not present in the array
      }
      // Calculate the frequency as the difference between last and first occurrence
      int last = lastOcc(arr, target);
      return last - first + 1;
   }
}
