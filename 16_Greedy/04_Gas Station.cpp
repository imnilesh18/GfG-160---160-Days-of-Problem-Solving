/*
 * Gas Station
 *
 * Difficulty: MediumAccuracy: 34.79%Submissions: 184K+Points: 4Average Time: 20m
 *
 * There are some gas stations along a circular route. You are given two integer arrays gas[] denoted as the amount of gas present at each station and cost[] denoted as the cost of travelling to the next station. You have a car with an unlimited gas tank. You begin the journey with an empty tank from one of the gas stations. Return the index of the starting gas station if it's possible to travel around the circuit without running out of gas at any station in a clockwise direction. If there is no such starting station exists, return -1.
 * Note: If a solution exists, it is guaranteed to be unique.
 *
 * Examples:
 *
 * Input: gas[] = [4, 5, 7, 4], cost[]= [6, 6, 3, 5]
 * Output: 2
 * Explanation: It is possible to travel around the circuit from station at index 2. Amount of gas at station 2 is (0 + 7) = 7.
 * Travel to station 3. Available gas = (7 – 3 + 4) = 8.
 * Travel to station 0. Available gas = (8 – 5 + 4) = 7.
 * Travel to station 1. Available gas = (7 – 6 + 5) = 6.
 * Return to station 2. Available gas = (6 – 6) = 0.
 *
 * Input: gas[] = [1, 2, 3, 4, 5], cost[] = [3, 4, 5, 1, 2]
 * Output: 3
 * Explanation: It is possible to travel around the circuit from station at index 3. Amount of gas at station 3 is (0 + 4) = 4.
 * Travel to station 4. Available gas = 4 – 1 + 5 = 8.
 * Travel to station 0. Available gas = 8 – 2 + 1 = 7.
 * Travel to station 1. Available gas= 7 – 3 + 2 = 6.
 * Travel to station 2. Available gas = 6 – 4 + 3 = 5.
 * Travel to station 3. The cost is 5. The gas is just enough to travel back to station 3.
 *
 * Input: gas[] = [3, 9], cost[] = [7, 6]
 * Output: -1
 * Explanation: There is no gas station to start with such that you can complete the circuit.
 *
 * Constraints:
 * 1 ≤ gas.size(), cost.size() ≤ 10^6
 * 1 ≤ gas[i], cost[i] ≤ 10^3
 */

/************************************************************ C++ ************************************************/

// Approach 1 (Brute force TLE: 1110 /1111): For each station, if gas[i] >= cost[i], simulate the journey.
// Time Complexity: O(n^2) in the worst-case scenario because for each station, the simulation may traverse nearly all stations.
// Space Complexity: O(1) as we only use a constant amount of extra variables.
class Solution {
    public int startStation(int[] gas, int[] cost) {
        int n = gas.length;

        for (int i = 0; i < n; i++) { // Try each station as a potential starting point.
            if (gas[i] < cost[i]) {   // If station i doesn't have enough gas to leave, skip.
                continue;
            }

            int j       = (i + 1) % n;               // j points to the next station in a circular fashion.
            int currGas = gas[i] - cost[i] + gas[j]; // After leaving i and arriving at j.

            while (j != i) {                         // Continue until we complete a full circle.
                if (currGas < cost[j]) {             // If current gas is insufficient to leave station j, break.
                    break;
                }
                int costForMovingFromThisj = cost[j];                // Cost to leave station j.
                j       = (j + 1) % n;                               // Move to the next station.
                currGas = currGas - costForMovingFromThisj + gas[j]; // Update current gas.
            }

            if (j == i) {   // If we successfully returned to the starting station, return i.
                return i;
            }
        }
        return -1;   // No valid starting station found.
    }
}

/*
 * Dry Run Visualization:
 *
 * Input:
 *   gas  = [4,  5,  7,  4]
 *   cost = [6,  6,   3,  5]
 *
 * -------------------------------------------------
 * Step 1: Try i = 0
 * -------------------------------------------------
 * [ Index:   0    1    2    3 ]
 * [ Gas:    [4,   5,   7,   4] ]
 * [ Cost:   [6,   6,   3,   5] ]
 *   *        i -> 0
 *   * Check: gas[0] (4) < cost[0] (6)
 *   * Decision: Skip station 0.
 *
 * -------------------------------------------------
 * Step 2: Try i = 1
 * -------------------------------------------------
 * [ Index:   0    1    2    3 ]
 * [ Gas:    [4,   5,   7,   4] ]
 * [ Cost:   [6,   6,   3,   5] ]
 *                 i -> 1
 *   * Check: gas[1] (5) < cost[1] (6)
 *   * Decision: Skip station 1.
 *
 * -------------------------------------------------
 * Step 3: Try i = 2 (Potential Start)
 * -------------------------------------------------
 * [ Index:   0    1    2    3 ]
 * [ Gas:    [4,   5,   7,   4] ]
 * [ Cost:   [6,   6,   3,   5] ]
 *                      i -> 2
 *
 * At i = 2:
 *   * Available gas = gas[2] = 7
 *   * Cost to leave station 2 = cost[2] = 3
 *   * After leaving i: Remaining gas = 7 - 3 = 4
 *   * Set pointer: j = (2 + 1) % 4 = 3
 *   * At station j = 3: Add gas[3] = 4
 *   * Updated currGas = 4 + 4 = 8
 *
 * Visual State:
 * +--------------------------------------------------+
 * | Stations:      0    1    2    3                  |
 * | Gas:          [4,   5,   7,   4]                 |
 * | Cost:         [6,   6,   3,   5]                 |
 * | Starting index i = 2                             |
 * | j is at index 3                                  |
 * | currGas = 8                                      |
 * +--------------------------------------------------+
 *
 * -------------------------------------------------
 * Step 3.1: At j = 3
 * -------------------------------------------------
 * [ Index:   0    1    2    3 ]
 * [ Gas:    [4,   5,   7,   4] ]
 * [ Cost:   [6,   6,   3,   5] ]
 *                      i    j -> 3
 *   * At station 3: currGas = 8, cost[3] = 5
 *   * Check: 8 >= 5 → OK to leave.
 *   * Subtract cost: 8 - 5 = 3
 *   * Move j: j = (3 + 1) % 4 = 0
 *   * At new j = 0: Add gas[0] = 4
 *   * Updated currGas = 3 + 4 = 7
 *
 * Visual State:
 * +--------------------------------------------------+
 * | i remains at index 2                           |
 * | j moves to index 0                             |
 * | currGas updated to 7                           |
 * +--------------------------------------------------+
 *
 * -------------------------------------------------
 * Step 3.2: At j = 0
 * -------------------------------------------------
 * [ Index:   0    1    2    3 ]
 * [ Gas:    [4,   5,   7,   4] ]
 * [ Cost:   [6,   6,   3,   5] ]
 *            j -> 0    i
 *   * At station 0: currGas = 7, cost[0] = 6
 *   * Check: 7 >= 6 → OK to leave.
 *   * Subtract cost: 7 - 6 = 1
 *   * Move j: j = (0 + 1) % 4 = 1
 *   * At new j = 1: Add gas[1] = 5
 *   * Updated currGas = 1 + 5 = 6
 *
 * Visual State:
 * +--------------------------------------------------+
 * | i remains at index 2                           |
 * | j moves to index 1                             |
 * | currGas updated to 6                           |
 * +--------------------------------------------------+
 *
 * -------------------------------------------------
 * Step 3.3: At j = 1
 * -------------------------------------------------
 * [ Index:   0    1    2    3 ]
 * [ Gas:    [4,   5,   7,   4] ]
 * [ Cost:   [6,   6,   3,   5] ]
 *                 j -> 1
 *   * At station 1: currGas = 6, cost[1] = 6
 *   * Check: 6 >= 6 → Exactly enough to leave.
 *   * Subtract cost: 6 - 6 = 0
 *   * Move j: j = (1 + 1) % 4 = 2
 *   * At new j = 2: Add gas[2] = 7
 *   * Updated currGas = 0 + 7 = 7
 *
 * Visual State:
 * +--------------------------------------------------+
 * | i remains at index 2                           |
 * | j moves back to index 2                        |
 * | currGas updated to 7                           |
 * +--------------------------------------------------+
 *
 * -------------------------------------------------
 * Step 3.4: Completion
 * -------------------------------------------------
 *   * j equals i (both at index 2), meaning the circuit is complete.
 *   * Therefore, the valid starting index is 2.
 */

// Approach 2 (Optimized Greedy):
// We first check if the total gas is at least equal to the total cost.
// If not, return -1. Otherwise, we use a running total to determine the starting station.
// Whenever the running total (currentFuelBalance) becomes negative, we reset it and choose the next station as the new candidate.
// Time Complexity: O(n) because we traverse the array only once.
// Space Complexity: O(1) as we use only a constant amount of extra variables.
class Solution {
public:
    int startStation(vector<int>& gas, vector<int>& cost) {
        int n = gas.size();

        // Calculate total gas available and total cost required for the circuit.
        int totalGasAvailable = accumulate(gas.begin(), gas.end(), 0);
        int totalCostRequired = accumulate(cost.begin(), cost.end(), 0);

        // If overall available gas is less than the cost, the journey is impossible.
        if (totalGasAvailable < totalCostRequired) {
            return -1;
        }

        int startingStationIndex = 0;    // Candidate index for starting the journey.
        int currentFuelBalance   = 0;    // Current fuel balance during the journey.

        for (int i = 0; i < n; i++) {
            // Update the current fuel balance by adding the net fuel at station i.
            currentFuelBalance += gas[i] - cost[i];

            // If the balance becomes negative, station i cannot be part of a successful route.
            if (currentFuelBalance < 0) {
                startingStationIndex = i + 1;   // Choose the next station as the new candidate.
                currentFuelBalance   = 0;       // Reset the fuel balance.
            }
        }
        return startingStationIndex;
    }
};

/*
 * Dry Run Visualization:
 *
 * Input:
 *   gas  = [4,  5,  7,  4]
 *   cost = [6,  6,  3,  5]
 *
 * *---------------------------------------------------------------*
 * * Step 1: Compute Totals                                        *
 * *---------------------------------------------------------------*
 * *   totalGasAvailable = 4 + 5 + 7 + 4 = 20                      *
 * *   totalCostRequired = 6 + 6 + 3 + 5 = 20                      *
 * *   Since 20 >= 20, proceed with the simulation.                *
 * *---------------------------------------------------------------*
 *
 * *---------------------------------------------------------------*
 * * Step 2: Initialize Variables                                  *
 * *---------------------------------------------------------------*
 * *   startingStationIndex = 0                                    *
 * *   currentFuelBalance   = 0                                    *
 * *---------------------------------------------------------------*
 *
 * *---------------------------------------------------------------*
 * * Step 3: Iterate Over Each Station                             *
 * *---------------------------------------------------------------*
 *
 * * Iteration 1: i = 0                                            *
 * *---------------------------------------------------------------*
 * * [ Index:   0    1    2    3 ]                                 *
 * * [  gas:   [4,   5,   7,   4] ]                                *
 * * [ cost:   [6,   6,   3,   5] ]                                *
 * *            ^                                                  *
 * *            |                                                  *
 * *          i = 0                                                *
 * *---------------------------------------------------------------*
 * * Calculation:                                                  *
 * *   currentFuelBalance += gas[0] - cost[0]                      *
 * *                     = 0 + (4 - 6) = -2                        *
 * * Since currentFuelBalance (-2) < 0, reset the candidate:       *
 * *   startingStationIndex = 0 + 1 = 1                            *
 * *   currentFuelBalance   = 0                                    *
 * *---------------------------------------------------------------*
 *
 * * Iteration 2: i = 1                                            *
 * *---------------------------------------------------------------*
 * * [ Index:   0    1    2    3 ]                                 *
 * * [  gas:   [4,   5,   7,   4] ]                                *
 * * [ cost:   [6,   6,   3,   5] ]                                *
 * *                 ^                                             *
 * *                 |                                             *
 * *               i = 1                                           *
 * *---------------------------------------------------------------*
 * * Calculation:                                                  *
 * *   currentFuelBalance += gas[1] - cost[1]                      *
 * *                     = 0 + (5 - 6) = -1                        *
 * * Since currentFuelBalance (-1) < 0, reset the candidate:       *
 * *   startingStationIndex = 1 + 1 = 2                            *
 * *   currentFuelBalance   = 0                                    *
 * *---------------------------------------------------------------*
 *
 * * Iteration 3: i = 2                                            *
 * *---------------------------------------------------------------*
 * * [ Index:   0    1    2    3 ]                                 *
 * * [  gas:   [4,   5,   7,   4] ]                                *
 * * [ cost:   [6,   6,   3,   5] ]                                *
 * *                      ^                                        *
 * *                      |                                        *
 * *                    i = 2                                      *
 * *---------------------------------------------------------------*
 * * Calculation:                                                  *
 * *   currentFuelBalance += gas[2] - cost[2]                      *
 * *                     = 0 + (7 - 3) = 4                         *
 * * Since currentFuelBalance (4) >= 0, no reset needed.           *
 * *   startingStationIndex remains 2                              *
 * *---------------------------------------------------------------*
 *
 * * Iteration 4: i = 3                                            *
 * *---------------------------------------------------------------*
 * * [ Index:   0    1    2    3 ]                                 *
 * * [  gas:   [4,   5,   7,   4] ]                                *
 * * [ cost:   [6,   6,   3,   5] ]                                *
 * *                           ^                                   *
 * *                           |                                   *
 * *                         i = 3                                 *
 * *---------------------------------------------------------------*
 * * Calculation:                                                  *
 * *   currentFuelBalance += gas[3] - cost[3]                      *
 * *                     = 4 + (4 - 5) = 3                         *
 * * currentFuelBalance remains positive (3), no reset.            *
 * *   startingStationIndex remains 2                              *
 * *---------------------------------------------------------------*
 *
 * *---------------------------------------------------------------*
 * * Step 4: End of Iteration                                      *
 * *---------------------------------------------------------------*
 * * Final Candidate: startingStationIndex = 2                     *
 * * Return: 2                                                     *
 * *---------------------------------------------------------------*
 */

/************************************************************ JAVA ************************************************/

// Approach 1 (Brute force TLE: 1110 /1111): For each station, if gas[i] >= cost[i], simulate the journey.
// Time Complexity: O(n^2) in the worst-case scenario because for each station, the simulation may traverse nearly all stations.
// Space Complexity: O(1) as we only use a constant amount of extra variables.
class Solution {
    public int startStation(int[] gas, int[] cost) {
        int n = gas.length;

        for (int i = 0; i < n; i++) { // Try each station as a potential starting point.
            if (gas[i] < cost[i]) {   // If station i doesn't have enough gas to leave, skip.
                continue;
            }

            int j       = (i + 1) % n;               // j points to the next station in a circular fashion.
            int currGas = gas[i] - cost[i] + gas[j]; // After leaving i and arriving at j.

            while (j != i) {                         // Continue until we complete a full circle.
                if (currGas < cost[j]) {             // If current gas is insufficient to leave station j, break.
                    break;
                }
                int costForMovingFromThisj = cost[j];                // Cost to leave station j.
                j       = (j + 1) % n;                               // Move to the next station.
                currGas = currGas - costForMovingFromThisj + gas[j]; // Update current gas.
            }

            if (j == i) {   // If we successfully returned to the starting station, return i.
                return i;
            }
        }
        return -1;   // No valid starting station found.
    }
}

/*
 * Dry Run Visualization:
 *
 * Input:
 *   gas  = [4,  5,  7,  4]
 *   cost = [6,  6,   3,  5]
 *
 * -------------------------------------------------
 * Step 1: Try i = 0
 * -------------------------------------------------
 * [ Index:   0    1    2    3 ]
 * [ Gas:    [4,   5,   7,   4] ]
 * [ Cost:   [6,   6,   3,   5] ]
 *   *        i -> 0
 *   * Check: gas[0] (4) < cost[0] (6)
 *   * Decision: Skip station 0.
 *
 * -------------------------------------------------
 * Step 2: Try i = 1
 * -------------------------------------------------
 * [ Index:   0    1    2    3 ]
 * [ Gas:    [4,   5,   7,   4] ]
 * [ Cost:   [6,   6,   3,   5] ]
 *                 i -> 1
 *   * Check: gas[1] (5) < cost[1] (6)
 *   * Decision: Skip station 1.
 *
 * -------------------------------------------------
 * Step 3: Try i = 2 (Potential Start)
 * -------------------------------------------------
 * [ Index:   0    1    2    3 ]
 * [ Gas:    [4,   5,   7,   4] ]
 * [ Cost:   [6,   6,   3,   5] ]
 *                      i -> 2
 *
 * At i = 2:
 *   * Available gas = gas[2] = 7
 *   * Cost to leave station 2 = cost[2] = 3
 *   * After leaving i: Remaining gas = 7 - 3 = 4
 *   * Set pointer: j = (2 + 1) % 4 = 3
 *   * At station j = 3: Add gas[3] = 4
 *   * Updated currGas = 4 + 4 = 8
 *
 * Visual State:
 * +--------------------------------------------------+
 * | Stations:      0    1    2    3                  |
 * | Gas:          [4,   5,   7,   4]                 |
 * | Cost:         [6,   6,   3,   5]                 |
 * | Starting index i = 2                             |
 * | j is at index 3                                  |
 * | currGas = 8                                      |
 * +--------------------------------------------------+
 *
 * -------------------------------------------------
 * Step 3.1: At j = 3
 * -------------------------------------------------
 * [ Index:   0    1    2    3 ]
 * [ Gas:    [4,   5,   7,   4] ]
 * [ Cost:   [6,   6,   3,   5] ]
 *                      i    j -> 3
 *   * At station 3: currGas = 8, cost[3] = 5
 *   * Check: 8 >= 5 → OK to leave.
 *   * Subtract cost: 8 - 5 = 3
 *   * Move j: j = (3 + 1) % 4 = 0
 *   * At new j = 0: Add gas[0] = 4
 *   * Updated currGas = 3 + 4 = 7
 *
 * Visual State:
 * +--------------------------------------------------+
 * | i remains at index 2                           |
 * | j moves to index 0                             |
 * | currGas updated to 7                           |
 * +--------------------------------------------------+
 *
 * -------------------------------------------------
 * Step 3.2: At j = 0
 * -------------------------------------------------
 * [ Index:   0    1    2    3 ]
 * [ Gas:    [4,   5,   7,   4] ]
 * [ Cost:   [6,   6,   3,   5] ]
 *            j -> 0    i
 *   * At station 0: currGas = 7, cost[0] = 6
 *   * Check: 7 >= 6 → OK to leave.
 *   * Subtract cost: 7 - 6 = 1
 *   * Move j: j = (0 + 1) % 4 = 1
 *   * At new j = 1: Add gas[1] = 5
 *   * Updated currGas = 1 + 5 = 6
 *
 * Visual State:
 * +--------------------------------------------------+
 * | i remains at index 2                           |
 * | j moves to index 1                             |
 * | currGas updated to 6                           |
 * +--------------------------------------------------+
 *
 * -------------------------------------------------
 * Step 3.3: At j = 1
 * -------------------------------------------------
 * [ Index:   0    1    2    3 ]
 * [ Gas:    [4,   5,   7,   4] ]
 * [ Cost:   [6,   6,   3,   5] ]
 *                 j -> 1
 *   * At station 1: currGas = 6, cost[1] = 6
 *   * Check: 6 >= 6 → Exactly enough to leave.
 *   * Subtract cost: 6 - 6 = 0
 *   * Move j: j = (1 + 1) % 4 = 2
 *   * At new j = 2: Add gas[2] = 7
 *   * Updated currGas = 0 + 7 = 7
 *
 * Visual State:
 * +--------------------------------------------------+
 * | i remains at index 2                           |
 * | j moves back to index 2                        |
 * | currGas updated to 7                           |
 * +--------------------------------------------------+
 *
 * -------------------------------------------------
 * Step 3.4: Completion
 * -------------------------------------------------
 *   * j equals i (both at index 2), meaning the circuit is complete.
 *   * Therefore, the valid starting index is 2.
 */

// Approach 2 (Optimized Greedy):
// We first check if the total gas is at least equal to the total cost.
// If not, return -1. Otherwise, we use a running total to determine the starting station.
// Whenever the running total (currentFuelBalance) becomes negative, we reset it and choose the next station as the new candidate.
// Time Complexity: O(n) because we traverse the array only once.
// Space Complexity: O(1) as we use only a constant amount of extra variables.
class Solution {
    public int startStation(int[] gas, int[] cost) {
        int n = gas.length;

        // Calculate total gas available and total cost required for the circuit.
        int totalGasAvailable = 0;

        for (int g : gas) {
            totalGasAvailable += g;
        }
        int totalCostRequired = 0;
        for (int c : cost) {
            totalCostRequired += c;
        }

        // If overall available gas is less than the cost, the journey is impossible.
        if (totalGasAvailable < totalCostRequired) {
            return -1;
        }

        int startingStationIndex = 0;    // Candidate index for starting the journey.
        int currentFuelBalance   = 0;    // Current fuel balance during the journey.

        for (int i = 0; i < n; i++) {
            // Update the current fuel balance by adding the net fuel at station i.
            currentFuelBalance += gas[i] - cost[i];

            // If the balance becomes negative, station i cannot be part of a successful route.
            if (currentFuelBalance < 0) {
                startingStationIndex = i + 1;   // Choose the next station as the new candidate.
                currentFuelBalance   = 0;       // Reset the fuel balance.
            }
        }
        return startingStationIndex;
    }
}

/*
 * Dry Run Visualization:
 *
 * Input:
 *   gas  = [4,  5,  7,  4]
 *   cost = [6,  6,   3,  5]
 *
 * *---------------------------------------------------------------*
 * * Step 1: Compute Totals                                        *
 * *---------------------------------------------------------------*
 * *   totalGasAvailable = 4 + 5 + 7 + 4 = 20                      *
 * *   totalCostRequired = 6 + 6 + 3 + 5 = 20                      *
 * *   Since 20 >= 20, proceed with the simulation.                *
 * *---------------------------------------------------------------*
 *
 * *---------------------------------------------------------------*
 * * Step 2: Initialize Variables                                  *
 * *---------------------------------------------------------------*
 * *   startingStationIndex = 0                                    *
 * *   currentFuelBalance   = 0                                    *
 * *---------------------------------------------------------------*
 *
 * *---------------------------------------------------------------*
 * * Step 3: Iterate Over Each Station                             *
 * *---------------------------------------------------------------*
 *
 * * Iteration 1: i = 0                                            *
 * *---------------------------------------------------------------*
 * * [ Index:   0    1    2    3 ]                                 *
 * * [  gas:   [4,   5,   7,   4] ]                                *
 * * [ cost:   [6,   6,   3,   5] ]                                *
 * *            ^                                                  *
 * *            |                                                  *
 * *          i = 0                                                *
 * *---------------------------------------------------------------*
 * * Calculation:                                                  *
 * *   currentFuelBalance += gas[0] - cost[0]                      *
 * *                     = 0 + (4 - 6) = -2                        *
 * * Since currentFuelBalance (-2) < 0, reset the candidate:       *
 * *   startingStationIndex = 0 + 1 = 1                            *
 * *   currentFuelBalance   = 0                                    *
 * *---------------------------------------------------------------*
 *
 * * Iteration 2: i = 1                                            *
 * *---------------------------------------------------------------*
 * * [ Index:   0    1    2    3 ]                                 *
 * * [  gas:   [4,   5,   7,   4] ]                                *
 * * [ cost:   [6,   6,   3,   5] ]                                *
 * *                 ^                                             *
 * *                 |                                             *
 * *               i = 1                                           *
 * *---------------------------------------------------------------*
 * * Calculation:                                                  *
 * *   currentFuelBalance += gas[1] - cost[1]                      *
 * *                     = 0 + (5 - 6) = -1                        *
 * * Since currentFuelBalance (-1) < 0, reset the candidate:       *
 * *   startingStationIndex = 1 + 1 = 2                            *
 * *   currentFuelBalance   = 0                                    *
 * *---------------------------------------------------------------*
 *
 * * Iteration 3: i = 2                                            *
 * *---------------------------------------------------------------*
 * * [ Index:   0    1    2    3 ]                                 *
 * * [  gas:   [4,   5,   7,   4] ]                                *
 * * [ cost:   [6,   6,   3,   5] ]                                *
 * *                      ^                                        *
 * *                      |                                        *
 * *                    i = 2                                      *
 * *---------------------------------------------------------------*
 * * Calculation:                                                  *
 * *   currentFuelBalance += gas[2] - cost[2]                      *
 * *                     = 0 + (7 - 3) = 4                         *
 * * Since currentFuelBalance (4) >= 0, no reset needed.           *
 * *   startingStationIndex remains 2                              *
 * *---------------------------------------------------------------*
 *
 * * Iteration 4: i = 3                                            *
 * *---------------------------------------------------------------*
 * * [ Index:   0    1    2    3 ]                                 *
 * * [  gas:   [4,   5,   7,   4] ]                                *
 * * [ cost:   [6,   6,   3,   5] ]                                *
 * *                           ^                                   *
 * *                           |                                   *
 * *                         i = 3                                 *
 * *---------------------------------------------------------------*
 * * Calculation:                                                  *
 * *   currentFuelBalance += gas[3] - cost[3]                      *
 * *                     = 4 + (4 - 5) = 3                         *
 * * currentFuelBalance remains positive (3), no reset.            *
 * *   startingStationIndex remains 2                              *
 * *---------------------------------------------------------------*
 *
 * *---------------------------------------------------------------*
 * * Step 4: End of Iteration                                      *
 * *---------------------------------------------------------------*
 * * Final Candidate: startingStationIndex = 2                     *
 * * Return: 2                                                     *
 * *---------------------------------------------------------------*
 */
