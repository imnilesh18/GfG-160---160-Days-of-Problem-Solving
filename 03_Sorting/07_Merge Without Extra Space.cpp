/*
 * Merge Without Extra Space
 *
 * Given two sorted arrays a[] and b[] of size n and m respectively, the task is to merge them in sorted order without using any extra space. Modify a[] so that it contains the first n elements and modify b[] so that it contains the last m elements.
 *
 * Examples:
 * Input: a[] = [2, 4, 7, 10], b[] = [2, 3]
 * Output:
 * 2 2 3 4
 * 7 10
 * Explanation: After merging the two non-decreasing arrays, we get, 2 2 3 4 7 10
 *
 * Input: a[] = [1, 5, 9, 10, 15, 20], b[] = [2, 3, 8, 13]
 * Output:
 * 1 2 3 5 8 9
 * 10 13 15 20
 * Explanation: After merging two sorted arrays we get 5 10 12 18 20.
 *
 * Input: a[] = [0, 1], b[] = [2, 3]
 * Output:
 * 0 1
 * 2 3
 * Explanation: After merging two sorted arrays we get 0 1 2 3.
 *
 * Constraints:
 * 1 <= a.size(), b.size() <= 10^5
 * 0 <= a[i], b[i] <= 10^7
 */

/************************************************************ C++ ************************************************/

// Approach: Merging and sorting arrays.
// Time Complexity: O(n + m) + O(n * log n) + O(m * log m) (O(n + m) for merging, O(n log n) and O(m log m) for sorting both arrays).
// Space Complexity: O(1) (in-place swaps, no extra space used).
class Solution {
public:
   void mergeArrays(vector<int>& a, vector<int>& b){
      int n = a.size();
      int m = b.size();

      int i = n - 1; // Last element of 1st array
      int j = 0;     // First element of 2nd array

      while (i >= 0 && j < m) {
         if (a[i] > b[j]) {
            // swap
            swap(a[i], b[j]);

            i--;
            j++;
         }else  {
            break;
         }
      }

      sort(a.begin(), a.end());
      sort(b.begin(), b.end());
   }
};


/************************************************************ JAVA ************************************************/

// Approach: Merging and sorting arrays.
// Time Complexity: O(n + m) + O(n * log n) + O(m * log m) (O(n + m) for merging, O(n log n) and O(m log m) for sorting both arrays).
// Space Complexity: O(1) (in-place swaps, no extra space used).
class Solution {
   // Function to merge the arrays.
   public void mergeArrays(int a[], int b[]){
      // code here
      int n = a.length;
      int m = b.length;

      int i = n - 1; // Last elemesnt of 1st array
      int j = 0;     // First element of 2nd array

      while (i >= 0 && j < m) {
         if (a[i] > b[j]) {
            // swap
            int temp = a[i];
            a[i] = b[j];
            b[j] = temp;

            i--;
            j++;
         }else {
            break;
         }
      }

      Arrays.sort(a);
      Arrays.sort(b);
   }
}
