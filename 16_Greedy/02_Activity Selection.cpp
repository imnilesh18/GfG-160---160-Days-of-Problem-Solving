/*
 * Activity Selection
 *
 * Difficulty: MediumAccuracy: 36.21%Submissions: 143K+Points: 4Average Time: 20m
 *
 * You are given a set of activities, each with a start time and a finish time, represented by the arrays start[] and finish[], respectively. A single person can perform only one activity at a time, meaning no two activities can overlap. Your task is to determine the maximum number of activities that a person can complete in a day.
 *
 * Examples:
 *
 * Input: start[] = [1, 3, 0, 5, 8, 5], finish[] = [2, 4, 6, 7, 9, 9]
 * Output: 4
 * Explanation: A person can perform at most four activities. The maximum set of activities that can be executed is {0, 1, 3, 4}
 *
 * Input: start[] = [10, 12, 20], finish[] = [20, 25, 30]
 * Output: 1
 * Explanation: A person can perform at most one activity.
 *
 * Input: start[] = [1, 3, 2, 5], finish[] = [2, 4, 3, 6]
 * Output: 3
 * Explanation: A person can perform activities 0, 1 and 3.
 *
 * Constraints:
 * 1 ≤ start.size() = finish.size() ≤ 2*10^5
 * 1 ≤ start[i] ≤ finish[i] ≤ 10^9
 */

/************************************************************ C++ ************************************************/

// Approach 1: Merge the start and finish arrays into pairs, sort the activities by finish time using a custom comparator,
// then use a greedy algorithm to select the maximum number of non-overlapping activities.
// Time Complexity: O(n log n) due to sorting.
// Space Complexity: O(n) for storing the merged vector of pairs.
class Solution {
public:
    int activitySelection(vector<int>& start, vector<int>& finish) {
        int n = start.size();
        vector<pair<int, int>> activities;

        // Merge start and finish into a vector of pairs (start, finish)
        for (int i = 0; i < n; i++) {
            activities.push_back({ start[i], finish[i] });
        }

        // Define the lambda comparator separately: sort by finish time (ascending)
        auto cmp = [](const pair<int, int>& a, const pair<int, int>& b) -> bool {
                       return a.second < b.second;
                   };

        // Sort activities based on finish time
        sort(activities.begin(), activities.end(), cmp);

        // Greedy algorithm to select maximum number of non-overlapping activities
        int count       = 1; // Select the first activity by default
        int last_finish = activities[0].second;

        // Iterate through remaining activities starting from index 1
        for (int i = 1; i < n; i++) {
            // If this activity starts strictly after the last selected one, choose it
            if (activities[i].first > last_finish) {
                count++;
                last_finish = activities[i].second;
            }
        }

        return count;
    }
};

/*
 * Dry Run:
 * Input:
 *  start[] = [1, 3, 0, 5, 8, 5]
 *  finish[] = [2, 4, 6, 7, 9, 9]
 *
 * Step 1: Merge arrays into pairs:
 *  activities = [(1,2), (3,4), (0,6), (5,7), (8,9), (5,9)]
 *
 * Step 2: Sort activities by finish time:
 *  Sorted activities = [(1,2), (3,4), (0,6), (5,7), (5,9), (8,9)]
 *  Indices:               0      1      2     3       4      5
 *
 * Step 3: Initialize:
 *  - Select first activity at index 0: (1,2)
 *  - Set last_finish = 2
 *  - Set count = 1
 *  - Pointer i starts at 1
 *
 * Visualization:
 *          [ (1,2) , (3,4) , (0,6) , (5,7) , (5,9) , (8,9) ]
 *             ^        ^       ^       ^       ^       ^
 * last_finish         i=1     i=2     i=3     i=4     i=5
 *
 * Step 4: Iterate through sorted activities:
 *  i = 1: Activity = (3,4)
 *       Compare: 3 > last_finish (2) → True
 *       Action: Select (3,4), update last_finish = 4, count = 2
 *       Pointer moves to i = 2
 *
 *  Visualization update:
 *       Selected: (1,2), (3,4)
 *       last_finish = 4
 *
 *  i = 2: Activity = (0,6)
 *       Compare: 0 > last_finish (4) → False
 *       Action: Skip (0,6), count remains 2, last_finish remains 4
 *       Pointer moves to i = 3
 *
 *  i = 3: Activity = (5,7)
 *       Compare: 5 > last_finish (4) → True
 *       Action: Select (5,7), update last_finish = 7, count = 3
 *       Pointer moves to i = 4
 *
 *  Visualization update:
 *       Selected: (1,2), (3,4), (5,7)
 *       last_finish = 7
 *
 *  i = 4: Activity = (5,9)
 *       Compare: 5 > last_finish (7) → False
 *       Action: Skip (5,9), count remains 3, last_finish remains 7
 *       Pointer moves to i = 5
 *
 *  i = 5: Activity = (8,9)
 *       Compare: 8 > last_finish (7) → True
 *       Action: Select (8,9), update last_finish = 9, count = 4
 *       Pointer moves beyond the array
 *
 * Final selected activities:
 *  (1,2), (3,4), (5,7), (8,9)
 * Final count = 4
 */

// Approach 2(Using Min Heap): Use a min-heap (priority queue) to store activities as (finish, start) pairs,
// then process them in increasing order of finish time using a greedy strategy to select non-overlapping activities.
// Time Complexity: O(n log n) due to priority queue operations (insertion and removal).
// Space Complexity: O(n) for storing the activities in the priority queue.
class Solution {
public:
    typedef pair<int, int> P;
    int activitySelection(vector<int>& start, vector<int>& finish) {
        int n = start.size();
        // Create a min-heap (priority queue) that orders pairs lexicographically: first by finish time,
        // and if equal, by start time.
        priority_queue<P, vector<P>, greater<P>> pq;

        // Push all activities into the priority queue as (finish, start) pairs.
        for (int i = 0; i < n; i++) {
            pq.push({ finish[i], start[i] });
        }

        int last_time = -1;
        int result    = 0;
        // Process activities in order of increasing finish time.
        while (!pq.empty()) {
            P activity = pq.top();
            pq.pop();

            // If the current activity's start time is strictly greater than last_time, select it.
            if (activity.second > last_time) {
                last_time = activity.first;    // Update last_time to the current activity's finish time.
                result++;
            }
        }
        return result;
    }
};

/*
 * Dry Run (Detailed Visualization):
 *
 * Input:
 *     start[]  = [1, 3, 0, 5, 8, 5]
 *     finish[] = [2, 4, 6, 7, 9, 9]
 *
 * Step 1: Insert each activity as (finish, start) into the min-heap (priority queue).
 * The inserted pairs are:
 *     (2,1), (4,3), (6,0), (7,5), (9,8), (9,5)
 * Note: With lexicographical ordering, for pairs with equal finish times, the pair with the smaller start comes first.
 * Thus, between (9,8) and (9,5), (9,5) is considered smaller.
 *
 * Conceptual view of the priority queue (vertical stack, top at the top):
 *
 *          +-----------+
 *     Top ->| (2,1)   |   <-- smallest finish time
 *          +-----------+
 *          | (4,3)   |
 *          +-----------+
 *          | (6,0)   |
 *          +-----------+
 *          | (7,5)   |
 *          +-----------+
 *          | (9,5)   |   <-- (9,5) comes before (9,8) because 5 < 8
 *          +-----------+
 *          | (9,8)   |
 *          +-----------+
 *
 * Initialize:
 *     last_time = -1, result = 0
 *
 * --------------------------------------------------
 * Iteration 1:
 *     - PQ before pop:
 *          +-----------+
 *          | (2,1)   |   <-- Top
 *          +-----------+
 *          | (4,3)   |
 *          +-----------+
 *          | (6,0)   |
 *          +-----------+
 *          | (7,5)   |
 *          +-----------+
 *          | (9,5)   |
 *          +-----------+
 *          | (9,8)   |
 *          +-----------+
 *     - Pop: Remove (2,1).
 *     - Compare: activity.second = 1 > last_time (-1) → True.
 *     - Action: Select (2,1). Update last_time = 2, result becomes 1.
 *
 *     - PQ after pop (conceptual view):
 *          +-----------+
 *          | (4,3)   |   <-- New Top
 *          +-----------+
 *          | (6,0)   |
 *          +-----------+
 *          | (7,5)   |
 *          +-----------+
 *          | (9,5)   |
 *          +-----------+
 *          | (9,8)   |
 *          +-----------+
 *
 * --------------------------------------------------
 * Iteration 2:
 *     - PQ before pop:
 *          +-----------+
 *          | (4,3)   |   <-- Top
 *          +-----------+
 *          | (6,0)   |
 *          +-----------+
 *          | (7,5)   |
 *          +-----------+
 *          | (9,5)   |
 *          +-----------+
 *          | (9,8)   |
 *          +-----------+
 *     - Pop: Remove (4,3).
 *     - Compare: activity.second = 3 > last_time (2) → True.
 *     - Action: Select (4,3). Update last_time = 4, result becomes 2.
 *
 *     - PQ after pop:
 *          +-----------+
 *          | (6,0)   |   <-- New Top
 *          +-----------+
 *          | (7,5)   |
 *          +-----------+
 *          | (9,5)   |
 *          +-----------+
 *          | (9,8)   |
 *          +-----------+
 *
 * --------------------------------------------------
 * Iteration 3:
 *     - PQ before pop:
 *          +-----------+
 *          | (6,0)   |   <-- Top
 *          +-----------+
 *          | (7,5)   |
 *          +-----------+
 *          | (9,5)   |
 *          +-----------+
 *          | (9,8)   |
 *          +-----------+
 *     - Pop: Remove (6,0).
 *     - Compare: activity.second = 0 > last_time (4) → False.
 *     - Action: Skip (6,0). last_time remains 4, result remains 2.
 *
 *     - PQ after pop:
 *          +-----------+
 *          | (7,5)   |   <-- New Top
 *          +-----------+
 *          | (9,5)   |
 *          +-----------+
 *          | (9,8)   |
 *          +-----------+
 *
 * --------------------------------------------------
 * Iteration 4:
 *     - PQ before pop:
 *          +-----------+
 *          | (7,5)   |   <-- Top
 *          +-----------+
 *          | (9,5)   |
 *          +-----------+
 *          | (9,8)   |
 *          +-----------+
 *     - Pop: Remove (7,5).
 *     - Compare: activity.second = 5 > last_time (4) → True.
 *     - Action: Select (7,5). Update last_time = 7, result becomes 3.
 *
 *     - PQ after pop:
 *          +-----------+
 *          | (9,5)   |   <-- New Top
 *          +-----------+
 *          | (9,8)   |
 *          +-----------+
 *
 * --------------------------------------------------
 * Iteration 5:
 *     - PQ before pop:
 *          +-----------+
 *          | (9,5)   |   <-- Top
 *          +-----------+
 *          | (9,8)   |
 *          +-----------+
 *     - Pop: Remove (9,5).
 *     - Compare: activity.second = 5 > last_time (7) → False.
 *     - Action: Skip (9,5). last_time remains 7, result remains 3.
 *
 *     - PQ after pop:
 *          +-----------+
 *          | (9,8)   |   <-- New Top (only element left)
 *          +-----------+
 *
 * --------------------------------------------------
 * Iteration 6:
 *     - PQ before pop:
 *          +-----------+
 *          | (9,8)   |   <-- Top
 *          +-----------+
 *     - Pop: Remove (9,8).
 *     - Compare: activity.second = 8 > last_time (7) → True.
 *     - Action: Select (9,8). Update last_time = 9, result becomes 4.
 *
 *     - PQ after pop:
 *          (PQ is now empty)
 *
 * --------------------------------------------------
 * Final Result: 4 selected activities.
 */

/************************************************************ JAVA ************************************************/

// Approach 1: Merge start and finish arrays into a list of activities, sort by finish time using a custom comparator,
// then apply a greedy algorithm to count the maximum number of non-overlapping activities.
// Time Complexity: O(n log n) due to sorting.
// Space Complexity: O(n) for storing the list of activities.
class Solution {
    // Define an inner class to represent an activity with start and finish times
    static class Activity {
        int start;
        int finish;

        Activity(int start, int finish) {
            this.start  = start;
            this.finish = finish;
        }
    }

    public int activitySelection(int[] start, int[] finish) {
        int            n          = start.length;
        List<Activity> activities = new ArrayList<>();

        // Merge start and finish arrays into a list of Activity objects
        for (int i = 0; i < n; i++) {
            activities.add(new Activity(start[i], finish[i]));
        }

        // Define and use a lambda comparator to sort activities based on finish time (ascending)
        activities.sort((a, b)->a.finish - b.finish);

        // Greedy algorithm to select maximum number of non-overlapping activities
        int count      = 1; // Select the first activity by default
        int lastFinish = activities.get(0).finish;

        // Iterate through the sorted list starting from index 1
        for (int i = 1; i < n; i++) {
            // If this activity starts strictly after the last selected activity's finish time, select it
            if (activities.get(i).start > lastFinish) {
                count++;
                lastFinish = activities.get(i).finish;
            }
        }

        return count;
    }
}

/*
 * Dry Run:
 * Input:
 *  start[]  = [1, 3, 0, 5, 8, 5]
 *  finish[] = [2, 4, 6, 7, 9, 9]
 *
 * Step 1: Merge arrays into activities list:
 *  activities = [ (1,2), (3,4), (0,6), (5,7), (8,9), (5,9) ]
 *
 * Step 2: Sort activities by finish time:
 *  Sorted activities = [ (1,2), (3,4), (0,6), (5,7), (5,9), (8,9) ]
 *  Indices:                0      1      2      3      4      5
 *
 * Step 3: Initialize:
 *  - Select first activity at index 0: (1,2)
 *  - Set lastFinish = 2
 *  - Set count = 1
 *  - Pointer i starts at index 1
 *
 * Visualization:
 *           [ (1,2) , (3,4) , (0,6) , (5,7) , (5,9) , (8,9) ]
 *               ^       ^       ^       ^       ^       ^
 * lastFinish           i=1     i=2     i=3     i=4     i=5
 *
 * Step 4: Iterate through sorted activities:
 *  i = 1: Activity = (3,4)
 *       Compare: 3 > lastFinish (2) → True
 *       Action: Select (3,4), update lastFinish = 4, count becomes 2
 *
 *  i = 2: Activity = (0,6)
 *       Compare: 0 > lastFinish (4) → False
 *       Action: Skip (0,6), count remains 2, lastFinish remains 4
 *
 *  i = 3: Activity = (5,7)
 *       Compare: 5 > lastFinish (4) → True
 *       Action: Select (5,7), update lastFinish = 7, count becomes 3
 *
 *  i = 4: Activity = (5,9)
 *       Compare: 5 > lastFinish (7) → False
 *       Action: Skip (5,9), count remains 3, lastFinish remains 7
 *
 *  i = 5: Activity = (8,9)
 *       Compare: 8 > lastFinish (7) → True
 *       Action: Select (8,9), update lastFinish = 9, count becomes 4
 *
 * Final selected activities:
 *  (1,2), (3,4), (5,7), (8,9)
 * Final count = 4
 */

// Approach 2 (Using Min Heap): Use a min-heap (PriorityQueue) to store activities as {finish, start} arrays,
// then process them in increasing order of finish time using a greedy strategy to select non-overlapping activities.
// Time Complexity: O(n log n) due to PriorityQueue operations (insertion and removal).
// Space Complexity: O(n) for storing the activities in the PriorityQueue.
class Solution {
    public int activitySelection(int[] start, int[] finish) {
        int n = start.length;
        // Create a PriorityQueue that orders activities by finish time (first element).
        PriorityQueue<int[]> pq = new PriorityQueue<>((a, b)->{
            if (a[0] != b[0]) {
                return a[0] - b[0];
            }
            return a[1] - b[1];
        });

        // Add all activities into the PriorityQueue as {finish, start} arrays.
        for (int i = 0; i < n; i++) {
            pq.offer(new int[] { finish[i], start[i] });
        }

        int lastTime = -1;
        int result   = 0;
        // Process the PriorityQueue until it is empty.
        while (!pq.isEmpty()) {
            int[] activity = pq.poll();

            // If the activity's start time is strictly greater than lastTime, select it.
            if (activity[1] > lastTime) {
                lastTime = activity[0];  // Update lastTime to the activity's finish time.
                result++;
            }
        }
        return result;
    }
}

/*
 * Dry Run (Detailed Visualization):
 *
 * Input:
 *     start[]  = [1, 3, 0, 5, 8, 5]
 *     finish[] = [2, 4, 6, 7, 9, 9]
 *
 * Step 1: Add each activity as {finish, start} to the PriorityQueue.
 * Inserted activities:
 *     {2,1}, {4,3}, {6,0}, {7,5}, {9,8}, {9,5}
 * Lexicographical order implies that between {9,8} and {9,5}, {9,5} is considered smaller.
 *
 * Conceptual view of the PriorityQueue (vertical stack, top at the top):
 *
 *          +-----------+
 *     Top ->| {2,1}   |   <-- smallest finish time
 *          +-----------+
 *          | {4,3}   |
 *          +-----------+
 *          | {6,0}   |
 *          +-----------+
 *          | {7,5}   |
 *          +-----------+
 *          | {9,5}   |   <-- {9,5} comes before {9,8} because 5 < 8
 *          +-----------+
 *          | {9,8}   |
 *          +-----------+
 *
 * Initialize:
 *     lastTime = -1, result = 0
 *
 * --------------------------------------------------
 * Iteration 1:
 *     - PQ before poll:
 *          +-----------+
 *          | {2,1}   |   <-- Top
 *          +-----------+
 *          | {4,3}   |
 *          +-----------+
 *          | {6,0}   |
 *          +-----------+
 *          | {7,5}   |
 *          +-----------+
 *          | {9,5}   |
 *          +-----------+
 *          | {9,8}   |
 *          +-----------+
 *     - Poll: Remove {2,1}.
 *     - Compare: activity[1] = 1 > lastTime (-1) → True.
 *     - Action: Select {2,1}. Update lastTime = 2, result becomes 1.
 *
 *     - PQ after poll:
 *          +-----------+
 *          | {4,3}   |   <-- New Top
 *          +-----------+
 *          | {6,0}   |
 *          +-----------+
 *          | {7,5}   |
 *          +-----------+
 *          | {9,5}   |
 *          +-----------+
 *          | {9,8}   |
 *          +-----------+
 *
 * --------------------------------------------------
 * Iteration 2:
 *     - PQ before poll:
 *          +-----------+
 *          | {4,3}   |   <-- Top
 *          +-----------+
 *          | {6,0}   |
 *          +-----------+
 *          | {7,5}   |
 *          +-----------+
 *          | {9,5}   |
 *          +-----------+
 *          | {9,8}   |
 *          +-----------+
 *     - Poll: Remove {4,3}.
 *     - Compare: activity[1] = 3 > lastTime (2) → True.
 *     - Action: Select {4,3}. Update lastTime = 4, result becomes 2.
 *
 *     - PQ after poll:
 *          +-----------+
 *          | {6,0}   |   <-- New Top
 *          +-----------+
 *          | {7,5}   |
 *          +-----------+
 *          | {9,5}   |
 *          +-----------+
 *          | {9,8}   |
 *          +-----------+
 *
 * --------------------------------------------------
 * Iteration 3:
 *     - PQ before poll:
 *          +-----------+
 *          | {6,0}   |   <-- Top
 *          +-----------+
 *          | {7,5}   |
 *          +-----------+
 *          | {9,5}   |
 *          +-----------+
 *          | {9,8}   |
 *          +-----------+
 *     - Poll: Remove {6,0}.
 *     - Compare: activity[1] = 0 > lastTime (4) → False.
 *     - Action: Skip {6,0}; lastTime remains 4, result remains 2.
 *
 *     - PQ after poll:
 *          +-----------+
 *          | {7,5}   |   <-- New Top
 *          +-----------+
 *          | {9,5}   |
 *          +-----------+
 *          | {9,8}   |
 *          +-----------+
 *
 * --------------------------------------------------
 * Iteration 4:
 *     - PQ before poll:
 *          +-----------+
 *          | {7,5}   |   <-- Top
 *          +-----------+
 *          | {9,5}   |
 *          +-----------+
 *          | {9,8}   |
 *          +-----------+
 *     - Poll: Remove {7,5}.
 *     - Compare: activity[1] = 5 > lastTime (4) → True.
 *     - Action: Select {7,5}. Update lastTime = 7, result becomes 3.
 *
 *     - PQ after poll:
 *          +-----------+
 *          | {9,5}   |   <-- New Top
 *          +-----------+
 *          | {9,8}   |
 *          +-----------+
 *
 * --------------------------------------------------
 * Iteration 5:
 *     - PQ before poll:
 *          +-----------+
 *          | {9,5}   |   <-- Top
 *          +-----------+
 *          | {9,8}   |
 *          +-----------+
 *     - Poll: Remove {9,5}.
 *     - Compare: activity[1] = 5 > lastTime (7) → False.
 *     - Action: Skip {9,5}; lastTime remains 7, result remains 3.
 *
 *     - PQ after poll:
 *          +-----------+
 *          | {9,8}   |   <-- New Top (only element left)
 *          +-----------+
 *
 * --------------------------------------------------
 * Iteration 6:
 *     - PQ before poll:
 *          +-----------+
 *          | {9,8}   |   <-- Top
 *          +-----------+
 *     - Poll: Remove {9,8}.
 *     - Compare: activity[1] = 8 > lastTime (7) → True.
 *     - Action: Select {9,8}. Update lastTime = 9, result becomes 4.
 *
 *     - PQ after poll:
 *          (PQ is now empty)
 *
 * --------------------------------------------------
 * Final Result: 4 selected activities.
 */
