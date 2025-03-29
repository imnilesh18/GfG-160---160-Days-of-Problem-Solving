/*
 * Job Sequencing Problem
 *
 * Difficulty: MediumAccuracy: 34.51%Submissions: 289K+Points: 4
 *
 * You are given two arrays: deadline[], and profit[], which represent a set of jobs, where each job is associated with a deadline, and a profit. Each job takes 1 unit of time to complete, and only one job can be scheduled at a time. You will earn the profit associated with a job only if it is completed by its deadline.
 *
 * Your task is to find:
 * The maximum number of jobs that can be completed within their deadlines.
 * The total maximum profit earned by completing those jobs.
 *
 * Examples :
 *
 * Input: deadline[] = [4, 1, 1, 1], profit[] = [20, 10, 40, 30]
 * Output: [2, 60]
 * Explanation: Job1 and Job3 can be done with maximum profit of 60 (20+40).
 *
 * Input: deadline[] = [2, 1, 2, 1, 1], profit[] = [100, 19, 27, 25, 15]
 * Output: [2, 127]
 * Explanation: Job1 and Job3 can be done with maximum profit of 127 (100+27).
 *
 * Input: deadline[] = [3, 1, 2, 2], profit[] = [50, 10, 20, 30]
 * Output: [3, 100]
 * Explanation: Job1, Job3 and Job4 can be completed with a maximum profit of 100 (50 + 20 + 30).
 *
 * Constraints:
 * 1 ≤ deadline.size() == profit.size() ≤ 10^5
 * 1 ≤ deadline[i] ≤ deadline.size()
 * 1 ≤ profit[i] ≤ 500
 */

/************************************************************ C++ ************************************************/

// Approach: Sort jobs by deadline, then iterate through jobs and use a min-heap (priority queue) to keep the most profitable jobs that can be scheduled before their deadlines.
// Time Complexity: O(n log n) due to sorting and heap operations.
// Space Complexity: O(n) for storing job pairs and the heap.
class Solution {
public:
    vector<int> jobSequencing(vector<int>& deadline, vector<int>& profit) {
        int         n      = deadline.size();
        vector<int> result = { 0, 0 };  // result[0]: count of jobs, result[1]: total profit

        // Pair the profit and deadline of all the jobs together
        vector<pair<int, int> > jobs;

        for (int i = 0; i < n; i++) {
            jobs.push_back({ deadline[i], profit[i] });
        }

        // Sort the jobs based on deadline in ascending order
        sort(jobs.begin(), jobs.end());

        // Priority queue (min-heap) to maintain the profits of scheduled jobs
        // The top of the heap will always have the smallest profit among the selected jobs.
        priority_queue<int, vector<int>, greater<int>> pq;

        // Iterate through each job in sorted order
        for (const auto& job : jobs) {
            // If the number of scheduled jobs is less than the current job's deadline,
            // we can schedule this job.
            if (job.first > pq.size()) {
                pq.push(job.second);
            }
            // Otherwise, if the current job's profit is higher than the smallest profit in the heap,
            // replace that job with the current job to maximize total profit.
            else if (!pq.empty() && pq.top() < job.second) {
                pq.pop();
                pq.push(job.second);
            }
        }

        // Extract the final scheduled jobs from the heap to update the result:
        // result[0] will be the total number of jobs scheduled,
        // result[1] will be the sum of profits of those jobs.
        while (!pq.empty()) {
            result[1] += pq.top();
            pq.pop();
            result[0]++;
        }

        return result;
    }
};

/*
 * Dry Run 1 (Detailed Visualization):
 *
 * Example Input:
 *     deadline[] = [4, 1, 1, 1]
 *     profit[]   = [20, 10, 40, 30]
 *
 * Step 1: Pair each job as (deadline, profit) and sort based on deadlines.
 *         Initial pairs: (4,20), (1,10), (1,40), (1,30)
 *         Sorted pairs (by deadline and then profit): (1,10), (1,30), (1,40), (4,20)
 *
 * Step 2: Process each job using the min-heap (visualized as a vertical stack with the top at the top).
 *
 * Initialize:
 *     Priority Queue (PQ): empty
 *
 * Iteration 1 (Job: (1,10)):
 *     - PQ size = 0, deadline = 1 → 1 > 0, so push profit 10.
 *     - PQ now (top at the top):
 *           +------+
 *       Top |  10  |
 *           +------+
 *
 * Iteration 2 (Job: (1,30)):
 *     - PQ size = 1, deadline = 1 → 1 is not greater than 1.
 *     - Check if current profit (30) > PQ.top() (10). Yes, so pop 10 and push 30.
 *     - PQ now:
 *           +------+
 *       Top |  30  |
 *           +------+
 *
 * Iteration 3 (Job: (1,40)):
 *     - PQ size = 1, deadline = 1 → 1 is not greater than 1.
 *     - Check if current profit (40) > PQ.top() (30). Yes, so pop 30 and push 40.
 *     - PQ now:
 *           +------+
 *       Top |  40  |
 *           +------+
 *
 * Iteration 4 (Job: (4,20)):
 *     - PQ size = 1, deadline = 4 → 4 > 1, so push profit 20.
 *     - PQ now (min-heap order, smallest profit at the top):
 *           +------+
 *       Top |  20  |   <-- smallest profit
 *           +------+
 *           |  40  |
 *           +------+
 *
 * Step 3: Aggregate results from PQ:
 *     - Pop from PQ: Remove 20 → result profit = 20, count = 1.
 *     - PQ now:
 *           +------+
 *       Top |  40  |
 *           +------+
 *     - Pop from PQ: Remove 40 → result profit = 20 + 40 = 60, count = 2.
 *
 * Final Result:
 *     result[0] = 2 (number of jobs scheduled)
 *     result[1] = 60 (total profit)
 *
 *
 * Dry Run 2 (Detailed Visualization):
 *
 * Example Input:
 *     deadline[] = [2, 6, 6, 5, 4, 2, 4, 2]
 *     profit[]   = [80, 70, 65, 60, 25, 22, 20, 10]
 *
 * Step 1: Pair each job as (deadline, profit) and sort them.
 *         Initial pairs: (2,80), (6,70), (6,65), (5,60), (4,25), (2,22), (4,20), (2,10)
 *         Sorted pairs (by deadline, then profit):
 *             (2,10), (2,22), (2,80), (4,20), (4,25), (5,60), (6,65), (6,70)
 *
 * Step 2: Process each job using a min-heap (visualized as a vertical stack, top at the top).
 *
 * Initialize:
 *     Priority Queue (PQ): empty
 *
 * Iteration 1 (Job: (2,10)):
 *     - PQ size = 0, deadline = 2 → 2 > 0, so push profit 10.
 *     - PQ now:
 *           +------+
 *       Top |  10  |
 *           +------+
 *
 * Iteration 2 (Job: (2,22)):
 *     - PQ size = 1, deadline = 2 → 2 > 1, so push profit 22.
 *     - PQ now:
 *           +------+
 *       Top |  10  |   <-- smallest profit
 *           +------+
 *           |  22  |
 *           +------+
 *
 * Iteration 3 (Job: (2,80)):
 *     - PQ size = 2, deadline = 2 → 2 is not greater than 2.
 *     - Check: profit 80 > PQ.top() (10)? Yes.
 *     - Action: Pop 10 and push 80.
 *     - PQ now:
 *           +------+
 *       Top |  22  |   <-- smallest profit
 *           +------+
 *           |  80  |
 *           +------+
 *
 * Iteration 4 (Job: (4,20)):
 *     - PQ size = 2, deadline = 4 → 4 > 2, so push profit 20.
 *     - PQ now:
 *           +------+
 *       Top |  20  |   <-- smallest profit (20 < 22)
 *           +------+
 *           |  80  |
 *           +------+
 *           |  22  |
 *           +------+
 *
 * Iteration 5 (Job: (4,25)):
 *     - PQ size = 3, deadline = 4 → 4 > 3, so push profit 25.
 *     - PQ now:
 *           +------+
 *       Top |  20  |   <-- smallest profit
 *           +------+
 *           |  25  |
 *           +------+
 *           |  22  |
 *           +------+
 *           |  80  |
 *           +------+
 *
 * Iteration 6 (Job: (5,60)):
 *     - PQ size = 4, deadline = 5 → 5 > 4, so push profit 60.
 *     - PQ now:
 *           +------+
 *       Top |  20  |   <-- smallest profit
 *           +------+
 *           |  25  |
 *           +------+
 *           |  22  |
 *           +------+
 *           |  80  |
 *           +------+
 *           |  60  |
 *           +------+
 *
 * Iteration 7 (Job: (6,65)):
 *     - PQ size = 5, deadline = 6 → 6 > 5, so push profit 65.
 *     - PQ now:
 *           +------+
 *       Top |  20  |   <-- smallest profit
 *           +------+
 *           |  25  |
 *           +------+
 *           |  22  |
 *           +------+
 *           |  80  |
 *           +------+
 *           |  60  |
 *           +------+
 *           |  65  |
 *           +------+
 *
 * Iteration 8 (Job: (6,70)):
 *     - PQ size = 6, deadline = 6 → 6 is not greater than 6.
 *     - Check: profit 70 > PQ.top() (20)? Yes.
 *     - Action: Pop 20 and push 70.
 *     - PQ now:
 *           +------+
 *       Top |  22  |   <-- smallest profit now
 *           +------+
 *           |  25  |
 *           +------+
 *           |  65  |
 *           +------+
 *           |  80  |
 *           +------+
 *           |  60  |
 *           +------+
 *           |  70  |
 *           +------+
 *
 * Step 3: Aggregate results from the PQ:
 *     - The PQ contains profits: 22, 25, 65, 80, 60, 70
 *     - Total jobs scheduled = 6
 *     - Total profit = 22 + 25 + 65 + 80 + 60 + 70 = 322
 *
 * Final Result:
 *     result[0] = 6 (number of jobs scheduled)
 *     result[1] = 322 (total profit)
 */

/************************************************************ JAVA ************************************************/

// Approach: Sort jobs by deadline, then iterate through jobs and use a min-heap (priority queue)
// to keep the most profitable jobs that can be scheduled before their deadlines.
// Time Complexity: O(n log n) due to sorting and heap operations.
// Space Complexity: O(n) for storing job pairs and the heap.
class Solution {
    public ArrayList<Integer> jobSequencing(int[] deadline, int[] profit) {
        int n = deadline.length;
        ArrayList<Integer> result = new ArrayList<>();

        result.add(0);  // result.get(0): count of jobs scheduled
        result.add(0);  // result.get(1): total profit

        // Pair the profit and deadline of all the jobs together in a list of int arrays
        ArrayList<int[]> jobs = new ArrayList<>();
        for (int i = 0; i < n; i++) {
            jobs.add(new int[]{ deadline[i], profit[i] });
        }

        // Sort the jobs based on deadline in ascending order
        jobs.sort((a, b)->a[0] - b[0]);

        // Priority queue (min-heap) to maintain the profits of scheduled jobs.
        // The top of the heap will always have the smallest profit among the selected jobs.
        PriorityQueue<Integer> pq = new PriorityQueue<>();

        // Iterate through each job in sorted order
        for (int[] job : jobs) {
            // If the number of scheduled jobs is less than the current job's deadline,
            // we can schedule this job.
            if (job[0] > pq.size()) {
                pq.offer(job[1]);
            }
            // Otherwise, if the current job's profit is higher than the smallest profit in the heap,
            // replace that job with the current job to maximize total profit.
            else if (!pq.isEmpty() && pq.peek() < job[1]) {
                pq.poll();
                pq.offer(job[1]);
            }
        }

        // Extract the final scheduled jobs from the heap to update the result:
        // result.get(0) will be the total number of jobs scheduled,
        // result.get(1) will be the sum of profits of those jobs.
        while (!pq.isEmpty()) {
            result.set(1, result.get(1) + pq.poll());
            result.set(0, result.get(0) + 1);
        }

        return result;
    }
}

/*
 * Dry Run 1 (Detailed Visualization):
 *
 * Example Input:
 *     deadline[] = [4, 1, 1, 1]
 *     profit[]   = [20, 10, 40, 30]
 *
 * Step 1: Pair each job as {deadline, profit} and sort based on deadlines.
 *         Initial pairs: {4,20}, {1,10}, {1,40}, {1,30}
 *         Sorted pairs: {1,10}, {1,40}, {1,30}, {4,20}
 *
 * Step 2: Process each job using a min-heap.
 *
 * Initialize:
 *     Priority Queue (PQ): empty
 *
 * Iteration 1 (Job: {1,10}):
 *     - PQ size = 0, deadline = 1 → 1 > 0, so push profit 10.
 *     - PQ now (top at the top):
 *           +------+
 *       Top |  10  |
 *           +------+
 *
 * Iteration 2 (Job: {1,40}):
 *     - PQ size = 1, deadline = 1 → 1 is not greater than 1.
 *     - Check: profit 40 > PQ.peek() (10)? Yes.
 *     - Action: Remove 10 and push 40.
 *     - PQ now:
 *           +------+
 *       Top |  40  |
 *           +------+
 *
 * Iteration 3 (Job: {1,30}):
 *     - PQ size = 1, deadline = 1 → 1 is not greater than 1.
 *     - Check: profit 30 > PQ.peek() (40)? No.
 *     - Action: Do nothing.
 *     - PQ remains:
 *           +------+
 *       Top |  40  |
 *           +------+
 *
 * Iteration 4 (Job: {4,20}):
 *     - PQ size = 1, deadline = 4 → 4 > 1, so push profit 20.
 *     - PQ now (min-heap order, smallest profit at the top):
 *           +------+
 *       Top |  20  |   <-- smallest profit
 *           +------+
 *           |  40  |
 *           +------+
 *
 * Step 3: Aggregate results from PQ:
 *     - Remove 20 → result profit = 20, count = 1.
 *     - Remove 40 → result profit = 20 + 40 = 60, count = 2.
 *
 * Final Result:
 *     result.get(0) = 2 (jobs scheduled)
 *     result.get(1) = 60 (total profit)
 *
 *
 * Dry Run 2 (Detailed Visualization):
 *
 * Example Input:
 *     deadline[] = [2, 6, 6, 5, 4, 2, 4, 2]
 *     profit[]   = [80, 70, 65, 60, 25, 22, 20, 10]
 *
 * Step 1: Pair each job as {deadline, profit} and sort them.
 *         Initial pairs: {2,80}, {6,70}, {6,65}, {5,60}, {4,25}, {2,22}, {4,20}, {2,10}
 *         Sorted pairs: {2,80}, {2,22}, {2,10}, {4,25}, {4,20}, {5,60}, {6,70}, {6,65}
 *
 * Step 2: Process each job using a min-heap.
 *
 * Initialize:
 *     Priority Queue (PQ): empty
 *
 * Iteration 1 (Job: {2,80}):
 *     - PQ size = 0, deadline = 2 → 2 > 0, so push profit 80.
 *     - PQ now:
 *           +------+
 *       Top |  80  |
 *           +------+
 *
 * Iteration 2 (Job: {2,22}):
 *     - PQ size = 1, deadline = 2 → 2 > 1, so push profit 22.
 *     - PQ now:
 *           +------+
 *       Top |  22  |   <-- smallest profit
 *           +------+
 *           |  80  |
 *           +------+
 *
 * Iteration 3 (Job: {2,10}):
 *     - PQ size = 2, deadline = 2 → 2 is not greater than 2.
 *     - Check: profit 10 > PQ.peek() (22)? No.
 *     - Action: Do nothing.
 *     - PQ remains:
 *           +------+
 *       Top |  22  |
 *           +------+
 *           |  80  |
 *           +------+
 *
 * Iteration 4 (Job: {4,25}):
 *     - PQ size = 2, deadline = 4 → 4 > 2, so push profit 25.
 *     - PQ now:
 *           +------+
 *       Top |  22  |   <-- smallest profit
 *           +------+
 *           |  80  |
 *           +------+
 *           |  25  |
 *           +------+
 *
 * Iteration 5 (Job: {4,20}):
 *     - PQ size = 3, deadline = 4 → 4 > 3, so push profit 20.
 *     - PQ now:
 *           +------+
 *       Top |  20  |   <-- smallest profit
 *           +------+
 *           |  22  |
 *           +------+
 *           |  80  |
 *           +------+
 *           |  25  |
 *           +------+
 *
 * Iteration 6 (Job: {5,60}):
 *     - PQ size = 4, deadline = 5 → 5 > 4, so push profit 60.
 *     - PQ now:
 *           +------+
 *       Top |  20  |   <-- smallest profit
 *           +------+
 *           |  22  |
 *           +------+
 *           |  80  |
 *           +------+
 *           |  25  |
 *           +------+
 *           |  60  |
 *           +------+
 *
 * Iteration 7 (Job: {6,70}):
 *     - PQ size = 5, deadline = 6 → 6 > 5, so push profit 70.
 *     - PQ now:
 *           +------+
 *       Top |  20  |   <-- smallest profit
 *           +------+
 *           |  22  |
 *           +------+
 *           |  80  |
 *           +------+
 *           |  25  |
 *           +------+
 *           |  60  |
 *           +------+
 *           |  70  |
 *           +------+
 *
 * Iteration 8 (Job: {6,65}):
 *     - PQ size = 6, deadline = 6 → 6 is not greater than 6.
 *     - Check: profit 65 > PQ.peek() (20)? Yes.
 *     - Action: Remove 20 and push 65.
 *     - PQ now:
 *           +------+
 *       Top |  22  |   <-- smallest profit now
 *           +------+
 *           |  25  |
 *           +------+
 *           |  65  |
 *           +------+
 *           |  80  |
 *           +------+
 *           |  60  |
 *           +------+
 *           |  70  |
 *           +------+
 *
 * Step 3: Aggregate results from the PQ:
 *     - The PQ contains profits: 22, 25, 65, 80, 60, 70
 *     - Total jobs scheduled = 6
 *     - Total profit = 22 + 25 + 65 + 80 + 60 + 70 = 322
 *
 * Final Result:
 *     result.get(0) = 6 (jobs scheduled)
 *     result.get(1) = 322 (total profit)
 */
