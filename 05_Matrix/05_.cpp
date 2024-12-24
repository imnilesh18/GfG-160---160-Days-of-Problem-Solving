// Approach-2:
// TC: O(log(m*n))
// SC: O(1)
class Solution {
public:
   bool searchMatrix(vector<vector<int> >& mat, int x){
      int m = mat.size();
      int n = mat[0].size();
      int l = 0;
      int r = n * m - 1;

      while (l <= r) {
         int mid = (l + r) / 2;
         int val = mat[mid / n][mid % n];

         if (val == x) {
            return true;
         }
         if (val < x) {
            l = mid + 1;
         } else {
            r = mid - 1;
         }
      }
      return false;
   }
};
