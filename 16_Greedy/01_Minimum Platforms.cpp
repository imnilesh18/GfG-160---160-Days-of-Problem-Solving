/*
 * Minimum Platforms
 *
 * Difficulty: MediumAccuracy: 26.84%Submissions: 519K+Points: 4
 *
 * You are given the arrival times arr[] and departure times dep[] of all trains that arrive at a railway station on the same day. Your task is to determine the minimum number of platforms required at the station to ensure that no train is kept waiting.
 *
 * At any given time, the same platform cannot be used for both the arrival of one train and the departure of another. Therefore, when two trains arrive at the same time, or when one arrives before another departs, additional platforms are required to accommodate both trains.
 *
 * Examples:
 *
 * Input: arr[] = [900, 940, 950, 1100, 1500, 1800], dep[] = [910, 1200, 1120, 1130, 1900, 2000]
 * Output: 3
 * Explanation: There are three trains during the time 9:40 to 12:00. So we need a minimum of 3 platforms.
 *
 * Input: arr[] = [900, 1235, 1100], dep[] = [1000, 1240, 1200]
 * Output: 1
 * Explanation: All train times are mutually exclusive. So we need only one platform
 *
 * Input: arr[] = [1000, 935, 1100], dep[] = [1200, 1240, 1130]
 * Output: 3
 * Explanation: All 3 trains have to be there from 11:00 to 11:30
 *
 * Constraints:
 * 1≤ number of trains ≤ 50000
 * 0000 ≤ arr[i] ≤ dep[i] ≤ 2359
 * Note: Time intervals are in the 24-hour format(HHMM) , where the first two characters represent hour (between 00 to 23 ) and the last two characters represent minutes (this will be <= 59 and >= 0).
 */

/************************************************************ C++ ************************************************/

// Approach: Sort both arrival and departure arrays. Then, using two pointers, traverse the arrays.
//           Increment the platform count when a train arrives before or at the same time as the earliest departure,
//           otherwise decrement the count when a train departs. The maximum count observed is the required number of platforms.
// Time Complexity: O(n log n) due to the sorting of the arrays.
// Space Complexity: O(1) if the sorting is performed in-place.
class Solution {
public:
    // Function to find the minimum number of platforms required at the railway station
    // such that no train waits.
    int findPlatform(vector<int>& arr, vector<int>& dep) {
        int n = arr.size();

        // Sort the arrival times
        sort(begin(arr), end(arr));
        // Sort the departure times
        sort(begin(dep), end(dep));

        int cnt    = 0;     // Current number of platforms needed
        int maxCnt = 0;     // Maximum number of platforms needed

        int i = 0;          // Pointer for arrival times
        int j = 0;          // Pointer for departure times

        // Traverse the arrival and departure arrays
        while (i < n) {
            // If a train arrives before the earliest train departs,
            // increment the count (need an extra platform)
            if (arr[i] <= dep[j]) {
                cnt++;
                i++;
            } else {
                // Else, decrement the count (one train has departed)
                cnt--;
                j++;
            }
            // Update maximum platforms needed
            maxCnt = max(maxCnt, cnt);
        }
        return maxCnt;
    }
};

/*
 * Dry Run Visualization:
 * Sorted Arrays:
 *  arr = [900, 940, 950, 1100, 1500, 1800]
 *  dep = [910, 1120, 1130, 1200, 1900, 2000]
 *
 * Visualization of pointer movements:
 *
 * Step 1:
 *  i = 0, j = 0, cnt = 0
 *  Compare arr[0]=900 with dep[0]=910 → 900 <= 910, so increment cnt.
 *  cnt becomes 1.
 *  Visualization:
 *    arr: [900, 940, 950, 1100, 1500, 1800]
 *           ^
 *    dep: [910, 1120, 1130, 1200, 1900, 2000]
 *           ^
 *
 * Step 2:
 *  i = 1, j = 0, cnt = 1
 *  Compare arr[1]=940 with dep[0]=910 → 940 > 910, so decrement cnt.
 *  cnt becomes 0 and increment j.
 *  Visualization:
 *    arr: [900, 940, 950, 1100, 1500, 1800]
 *                ^
 *    dep: [910, 1120, 1130, 1200, 1900, 2000]
 *           ^
 *
 * Step 3:
 *  i = 1, j = 1, cnt = 0
 *  Compare arr[1]=940 with dep[1]=1120 → 940 <= 1120, so increment cnt.
 *  cnt becomes 1 and increment i.
 *  Visualization:
 *    arr: [900, 940, 950, 1100, 1500, 1800]
 *                ^
 *    dep: [910, 1120, 1130, 1200, 1900, 2000]
 *                ^
 *
 * Step 4:
 *  i = 2, j = 1, cnt = 1
 *  Compare arr[2]=950 with dep[1]=1120 → 950 <= 1120, so increment cnt.
 *  cnt becomes 2 and increment i.
 *  Visualization:
 *    arr: [900, 940, 950, 1100, 1500, 1800]
 *                     ^
 *    dep: [910, 1120, 1130, 1200, 1900, 2000]
 *                ^
 *
 * Step 5:
 *  i = 3, j = 1, cnt = 2
 *  Compare arr[3]=1100 with dep[1]=1120 → 1100 <= 1120, so increment cnt.
 *  cnt becomes 3 and increment i.
 *  Visualization:
 *    arr: [900, 940, 950, 1100, 1500, 1800]
 *                          ^
 *    dep: [910, 1120, 1130, 1200, 1900, 2000]
 *                ^
 *
 * Step 6:
 *  i = 4, j = 1, cnt = 3
 *  Compare arr[4]=1500 with dep[1]=1120 → 1500 > 1120, so decrement cnt.
 *  cnt becomes 2 and increment j.
 *  Visualization:
 *    arr: [900, 940, 950, 1100, 1500, 1800]
 *                          ^
 *    dep: [910, 1120, 1130, 1200, 1900, 2000]
 *                      ^
 *
 * Step 7:
 *  i = 4, j = 2, cnt = 2
 *  Compare arr[4]=1500 with dep[2]=1130 → 1500 > 1130, so decrement cnt.
 *  cnt becomes 1 and increment j.
 *  Visualization:
 *    arr: [900, 940, 950, 1100, 1500, 1800]
 *                                ^
 *    dep: [910, 1120, 1130, 1200, 1900, 2000]
 *                      ^
 *
 * Step 8:
 *  i = 4, j = 3, cnt = 1
 *  Compare arr[4]=1500 with dep[3]=1200 → 1500 > 1200, so decrement cnt.
 *  cnt becomes 0 and increment j.
 *  Visualization:
 *    arr: [900, 940, 950, 1100, 1500, 1800]
 *                                ^
 *    dep: [910, 1120, 1130, 1200, 1900, 2000]
 *                            ^
 *
 * Step 9:
 *  i = 4, j = 4, cnt = 0
 *  Compare arr[4]=1500 with dep[4]=1900 → 1500 <= 1900, so increment cnt.
 *  cnt becomes 1 and increment i.
 *  Visualization:
 *    arr: [900, 940, 950, 1100, 1500, 1800]
 *                                ^
 *    dep: [910, 1120, 1130, 1200, 1900, 2000]
 *                                  ^
 *
 * Step 10:
 *  i = 5, j = 4, cnt = 1
 *  Compare arr[5]=1800 with dep[4]=1900 → 1800 <= 1900, so increment cnt.
 *  cnt becomes 2 and increment i.
 *  Visualization:
 *    arr: [900, 940, 950, 1100, 1500, 1800]
 *                                       ^
 *    dep: [910, 1120, 1130, 1200, 1900, 2000]
 *                                  ^
 *
 * End:
 *  i = 6 (end of arr), maximum platforms recorded = 3.
 *
 * Final Output: 3 (Minimum number of platforms required)
 */

/************************************************************ JAVA ************************************************/

// Approach: Sort both arrival and departure arrays. Then, using two pointers, traverse the arrays.
//           Increment the platform count when a train arrives before or at the same time as the earliest departure,
//           otherwise decrement the count when a train departs. The maximum count observed is the required number of platforms.
// Time Complexity: O(n log n) due to the sorting of the arrays.
// Space Complexity: O(1) if the sorting is performed in-place.
class Solution {
    // Function to find the minimum number of platforms required at the
    // railway station such that no train waits.
    public static int findPlatform(int arr[], int dep[]) {
        int n = arr.length;

        // Sort the arrival and departure arrays
        Arrays.sort(arr);
        Arrays.sort(dep);

        int cnt    = 0;  // Current number of platforms needed
        int maxCnt = 0;  // Maximum number of platforms needed

        int i = 0;       // Pointer for arrival times
        int j = 0;       // Pointer for departure times

        // Traverse the arrays until all trains are processed
        while (i < n) {
            // If next train arrives before or at the same time as the current earliest departure,
            // increment platform count
            if (arr[i] <= dep[j]) {
                cnt++;
                i++;
            } else {
                // Otherwise, decrement the count as one train departs
                cnt--;
                j++;
            }
            maxCnt = Math.max(maxCnt, cnt);
        }
        return maxCnt;
    }
}

/*
 * Dry Run Visualization:
 * Sorted Arrays:
 *  arr = [900, 940, 950, 1100, 1500, 1800]
 *  dep = [910, 1120, 1130, 1200, 1900, 2000]
 *
 * Visualization of pointer movements:
 *
 * Step 1:
 *  i = 0, j = 0, cnt = 0
 *  Compare arr[0]=900 with dep[0]=910 → 900 <= 910, so increment cnt.
 *  cnt becomes 1.
 *  Visualization:
 *    arr: [900, 940, 950, 1100, 1500, 1800]
 *           ^
 *    dep: [910, 1120, 1130, 1200, 1900, 2000]
 *           ^
 *
 * Step 2:
 *  i = 1, j = 0, cnt = 1
 *  Compare arr[1]=940 with dep[0]=910 → 940 > 910, so decrement cnt.
 *  cnt becomes 0 and increment j.
 *  Visualization:
 *    arr: [900, 940, 950, 1100, 1500, 1800]
 *                ^
 *    dep: [910, 1120, 1130, 1200, 1900, 2000]
 *          ^
 *
 * Step 3:
 *  i = 1, j = 1, cnt = 0
 *  Compare arr[1]=940 with dep[1]=1120 → 940 <= 1120, so increment cnt.
 *  cnt becomes 1 and increment i.
 *  Visualization:
 *    arr: [900, 940, 950, 1100, 1500, 1800]
 *                ^
 *    dep: [910, 1120, 1130, 1200, 1900, 2000]
 *                ^
 *
 * Step 4:
 *  i = 2, j = 1, cnt = 1
 *  Compare arr[2]=950 with dep[1]=1120 → 950 <= 1120, so increment cnt.
 *  cnt becomes 2 and increment i.
 *  Visualization:
 *    arr: [900, 940, 950, 1100, 1500, 1800]
 *                     ^
 *    dep: [910, 1120, 1130, 1200, 1900, 2000]
 *                ^
 *
 * Step 5:
 *  i = 3, j = 1, cnt = 2
 *  Compare arr[3]=1100 with dep[1]=1120 → 1100 <= 1120, so increment cnt.
 *  cnt becomes 3 and increment i.
 *  Visualization:
 *    arr: [900, 940, 950, 1100, 1500, 1800]
 *                          ^
 *    dep: [910, 1120, 1130, 1200, 1900, 2000]
 *                ^
 *
 * Step 6:
 *  i = 4, j = 1, cnt = 3
 *  Compare arr[4]=1500 with dep[1]=1120 → 1500 > 1120, so decrement cnt.
 *  cnt becomes 2 and increment j.
 *  Visualization:
 *    arr: [900, 940, 950, 1100, 1500, 1800]
 *                                ^
 *    dep: [910, 1120, 1130, 1200, 1900, 2000]
 *                ^
 *
 * Step 7:
 *  i = 4, j = 2, cnt = 2
 *  Compare arr[4]=1500 with dep[2]=1130 → 1500 > 1130, so decrement cnt.
 *  cnt becomes 1 and increment j.
 *  Visualization:
 *    arr: [900, 940, 950, 1100, 1500, 1800]
 *                                ^
 *    dep: [910, 1120, 1130, 1200, 1900, 2000]
 *                      ^
 *
 * Step 8:
 *  i = 4, j = 3, cnt = 1
 *  Compare arr[4]=1500 with dep[3]=1200 → 1500 > 1200, so decrement cnt.
 *  cnt becomes 0 and increment j.
 *  Visualization:
 *    arr: [900, 940, 950, 1100, 1500, 1800]
 *                                ^
 *    dep: [910, 1120, 1130, 1200, 1900, 2000]
 *                            ^
 *
 * Step 9:
 *  i = 4, j = 4, cnt = 0
 *  Compare arr[4]=1500 with dep[4]=1900 → 1500 <= 1900, so increment cnt.
 *  cnt becomes 1 and increment i.
 *  Visualization:
 *    arr: [900, 940, 950, 1100, 1500, 1800]
 *                                 ^
 *    dep: [910, 1120, 1130, 1200, 1900, 2000]
 *                                  ^
 *
 * Step 10:
 *  i = 5, j = 4, cnt = 1
 *  Compare arr[5]=1800 with dep[4]=1900 → 1800 <= 1900, so increment cnt.
 *  cnt becomes 2 and increment i.
 *  Visualization:
 *    arr: [900, 940, 950, 1100, 1500, 1800]
 *                                      ^
 *    dep: [910, 1120, 1130, 1200, 1900, 2000]
 *                                   ^
 *
 * End:
 *  i = 6 (end of arr), maximum platforms recorded = 3.
 *
 * Final Output: 3 (Minimum number of platforms required)
 */
