/*
 * Stock Buy and Sell – Multiple Transaction Allowed
 *
 * The cost of stock on each day is given in an array price[]. Each day you may decide to either buy or sell the stock at price[i], you can even buy and sell the stock on the same day. Find the maximum profit that you can get.
 * Note: A stock can only be sold if it has been bought previously and multiple stocks cannot be held on any given day.
 *
 * Examples:
 * Input: prices[] = [100, 180, 260, 310, 40, 535, 695]
 * Output: 865
 * Explanation: Buy the stock on day 0 and sell it on day 3 => 310 – 100 = 210. Buy the stock on day 4 and sell it on day 6 => 695 – 40 = 655. Maximum Profit = 210 + 655 = 865.
 *
 * Input: prices[] = [4, 2, 2, 2, 4]
 * Output: 2
 * Explanation: Buy the stock on day 3 and sell it on day 4 => 4 – 2 = 2. Maximum Profit = 2.
 *
 * Constraints:
 * 1 <= prices.size() <= 10^5
 * 0 <= prices[i] <= 10^4
 */

/************************************************************ C++ ************************************************/

// T.C : O(n)
// S.C: O(1)
class Solution {
public:
   int maximumProfit(vector<int>&prices){
      int n         = prices.size();
      int maxProfit = 0;

      // Loop through the array to calculate profit
      for (int i = 1; i < n; i++) {
         if (prices[i] > prices[i - 1]) {
            maxProfit += (prices[i] - prices[i - 1]);
         }
      }

      return maxProfit;
   }
};

/************************************************************ JAVA ************************************************/

// T.C : O(n)
// S.C: O(1)
class Solution {
   public int maximumProfit(int prices[]){
      // Initialize maxProfit to store the total profit
      int maxProfit = 0;

      // Loop through the array to calculate profit
      for (int i = 1; i < prices.length; i++) {
         // If the price on the current day is greater than the previous day,
         // add the difference to maxProfit
         if (prices[i] > prices[i - 1]) {
            maxProfit += prices[i] - prices[i - 1];
         }
      }

      // Return the maximum profit
      return maxProfit;
   }
}
