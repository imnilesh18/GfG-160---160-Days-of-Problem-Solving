/*
 * Majority Element II
 *
 * You are given an array of integer arr[] where each number represents a vote to a candidate.Return the candidates that have votes greater than one - third of the total votes, If there 's not a majority vote, return an empty array.
 *
 * Note: The answer should be returned in an increasing format.
 *
 * Examples:
 * Input: arr[] = [2, 1, 5, 5, 5, 5, 6, 6, 6, 6, 6]
 * Output: [5, 6]
 * Explanation: 5 and 6 occur more n/3 times.
 *
 * Input: arr[] = [1, 2, 3, 4, 5]
 * Output: []
 * Explanation: no candidate occur more than n/3 times.
 *
 * Constraint:
 * 1 <= arr.size() <= 10^6
 * -10^9 <= arr[i] <= 10^9
 */

/************************************************************ C++ ************************************************/

// Time Complexity: O(N) + O(N), where N = size of the given array.
// Reason: The first O(N) is to calculate the counts and find the expected majority elements. The second one is to check if the calculated elements are the majority ones or not.
// Space Complexity: O(1) as we are only using a list that stores a maximum of 2 elements. The space used is so small that it can be considered constant.
class Solution {
public:
   // Function to find the majority elements in the array
   vector<int> findMajority(vector<int>& v){
      int n = v.size();       // size of the array

      int cnt1 = 0, cnt2 = 0; // counts
      int el1 = INT_MIN;      // element 1
      int el2 = INT_MIN;      // element 2

      // Applying the Extended Boyer-Moore's Voting Algorithm:
      for (int i = 0; i < n; i++) {
         if (cnt1 == 0 && el2 != v[i]) {
            cnt1 = 1;
            el1  = v[i];
         } else if (cnt2 == 0 && el1 != v[i]) {
            cnt2 = 1;
            el2  = v[i];
         } else if (v[i] == el1) {
            cnt1++;
         } else if (v[i] == el2) {
            cnt2++;
         } else {
            cnt1--, cnt2--;
         }
      }

      vector<int> ls;   // list of answers

      // Manually check if the stored elements in
      // el1 and el2 are the majority elements:
      cnt1 = 0, cnt2 = 0;
      for (int i = 0; i < n; i++) {
         if (v[i] == el1) {
            cnt1++;
         }
         if (v[i] == el2) {
            cnt2++;
         }
      }

      int mini = int(n / 3) + 1;
      if (cnt1 >= mini) {
         ls.push_back(el1);
      }
      if (cnt2 >= mini) {
         ls.push_back(el2);
      }

      // Sort the result to return in increasing order
      sort(ls.begin(), ls.end());   // TC --> O(2 * log2) ~ O(1)

      return ls;
   }
};

/************************************************************ JAVA ************************************************/

// Time Complexity: O(N) + O(N), where N = size of the given array.
// Reason: The first O(N) is to calculate the counts and find the expected majority elements. The second one is to check if the calculated elements are the majority ones or not.
// Space Complexity: O(1) as we are only using a list that stores a maximum of 2 elements. The space used is so small that it can be considered constant.

class Solution {
   // Function to find the majority elements in the array
   public List<Integer> findMajority(int[] nums){
      int n = nums.length;         // size of the array

      int cnt1 = 0, cnt2 = 0;      // counts
      int el1 = Integer.MIN_VALUE; // element 1
      int el2 = Integer.MIN_VALUE; // element 2

      // Applying the Extended Boyer-Moore's Voting Algorithm:
      for (int i = 0; i < n; i++) {
         if (cnt1 == 0 && el2 != nums[i]) {
            cnt1 = 1;
            el1  = nums[i];
         } else if (cnt2 == 0 && el1 != nums[i]) {
            cnt2 = 1;
            el2  = nums[i];
         } else if (nums[i] == el1) {
            cnt1++;
         } else if (nums[i] == el2) {
            cnt2++;
         } else {
            cnt1--;
            cnt2--;
         }
      }

      List<Integer> result = new ArrayList<>();   // list of answers

      // Manually check if the stored elements in el1 and el2 are the majority elements:
      cnt1 = 0;
      cnt2 = 0;
      for (int i = 0; i < n; i++) {
         if (nums[i] == el1) {
            cnt1++;
         }
         if (nums[i] == el2) {
            cnt2++;
         }
      }

      int mini = n / 3 + 1;
      if (cnt1 >= mini) {
         result.add(el1);
      }
      if (cnt2 >= mini) {
         result.add(el2);
      }

      // Sort the result to return in increasing order
      Collections.sort(result);

      return result;
   }
}
