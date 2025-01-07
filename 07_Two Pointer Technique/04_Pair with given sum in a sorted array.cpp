/*
 * Pair with given sum in a sorted array
 *
 * You are given an integer target and an array arr[]. You have to find number of pairs in arr[] which sums up to target. It is given that the elements of the arr[] are in sorted order.
 * Note: pairs should have elements of distinct indexes.
 *
 * Examples :
 *
 * Input: arr[] = [-1, 1, 5, 5, 7], target = 6
 * Output: 3
 * Explanation: There are 3 pairs which sum up to 6 : {1, 5}, {1, 5} and {-1, 7}.
 *
 * Input: arr[] = [1, 1, 1, 1], target = 2
 * Output: 6
 * Explanation: There are 6 pairs which sum up to 2 : {1, 1}, {1, 1}, {1, 1}, {1, 1}, {1, 1} and {1, 1}.
 *
 * Input: arr[] = [-1, 10, 10, 12, 15], target = 125
 * Output: 0
 * Explanation: There is no such pair which sums up to 4.
 *
 * Constraints:
 * -10^5 <= target <=10^5
 * 2 <= arr.size() <= 10^5
 * -10^5 <= arr[i] <= 10^5
 */

/************************************************************ C++ ************************************************/

// Approach: Use two pointers on sorted array, handle duplicates by counting them at both ends when sum equals target
// TC: O(n) - Single pass through array with two pointers
// SC: O(1) - Only uses constant extra space for variables
class Solution {
 public:
   int countPairs(vector<int> &arr, int target) {
       int left = 0;
       int right = arr.size() - 1; 
       int count = 0;
       
       while(left < right) {
           int sum = arr[left] + arr[right];
           
           if(sum == target) {
               // Handle case when all remaining elements are same 
               if(arr[left] == arr[right]) {
                   int len = right - left + 1;
                   count += (len * (len - 1)) / 2; // nC2 combinations
                   break;
               }
               
               // Count duplicates at left end
               int leftCount = 1;
               while(left < right && arr[left] == arr[left + 1]) {
                   leftCount++;
                   left++;
               }
               
               // Count duplicates at right end
               int rightCount = 1;
               while(right > left && arr[right] == arr[right -1]) {
                   rightCount++;
                   right--;
               }
               
               count += leftCount * rightCount; // Add all combinations of left and right duplicates
               left++;
               right--;
           }
           
           else if(sum > target) {
               right--; // Sum too large, decrease right pointer
           } else {
               left++; // Sum too small, increase left pointer
           }
       }
       
       return count;
   }
};

/************************************************************ JAVA ************************************************/

// Approach: Two pointers on sorted array, handle duplicates by counting them at both ends when sum equals target
// TC: O(n) - Single pass through array with two pointers
// SC: O(1) - Only uses constant extra space for variables
class Solution {
   int countPairs(int arr[], int target) {
       int left = 0;
       int right = arr.length - 1;
       int count = 0;
       
       while(left < right) {
           int sum = arr[left] + arr[right];
           
           if(sum == target) {
               // Handle case when all remaining elements are same
               if(arr[left] == arr[right]) {
                   int len = right - left + 1;
                   count += (len * (len - 1)) / 2; // nC2 combinations
                   break;
               }
               
               // Count duplicates at left end
               int leftCount = 1;
               while(left < right && arr[left] == arr[left + 1]) {
                   leftCount++;
                   left++;
               }
               
               // Count duplicates at right end 
               int rightCount = 1;
               while(right > left && arr[right] == arr[right - 1]) {
                   rightCount++;
                   right--;
               }
               
               count += leftCount * rightCount; // Add combinations of duplicates
               left++;
               right--;
           }
           else if(sum > target) right--; // Decrease right if sum too large
           else left++; // Increase left if sum too small
       }
       
       return count;
   }
}