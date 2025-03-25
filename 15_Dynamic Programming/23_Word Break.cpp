/*
 * Word Break
 *
 * Difficulty: Medium Accuracy: 40.86% Submissions: 133K+ Points: 4
 *
 * You are given a string s and a list dictionary[] of words. Your task is to determine whether the string s can be formed by concatenating one or more words from the dictionary[].
 *
 * Note: From dictionary[], any word can be taken any number of times and in any order.
 *
 * Examples :
 *
 * Input: s = "ilike", dictionary[] = ["i", "like", "gfg"]
 * Output: true
 * Explanation: s can be breakdown as "i like".
 *
 * Input: s = "ilikegfg", dictionary = ["i", "like", "man", "india", "gfg"]
 * Output: true
 * Explanation: s can be breakdown as "i like gfg".
 *
 * Input: s = "ilikemangoes", dictionary = ["i", "like", "man", "india", "gfg"]
 * Output: false
 * Explanation: s cannot be formed using dictionary[] words.
 *
 * Constraints:
 * 1 ≤ s.size() ≤ 3000
 * 1 ≤ dictionary.size() ≤ 1000
 * 1 ≤ dictionary[i].size() ≤ 100
 */

/************************************************************ C++ ************************************************/

// Approach: Use recursion with memoization (DP) to check if the string can be segmented into dictionary words by trying every possible prefix and using a lookup set for fast word verification.
// Time Complexity: O(n * maxLen) - For each index (n total), we try up to maxLen substrings.
// Space Complexity: O(n) - For the memoization array and recursion call stack.
class Solution {
public:
    int n;
    unordered_set<string> st;      // Set to store dictionary words for quick lookup.
    int t[3001];                   // Fixed-size memoization array to store results for each index.
    int maxLen;                    // Maximum length of any word in the dictionary to limit unnecessary substring checks.

    // Recursive function to solve the problem starting from index 'idx'.
    bool solve(int idx, string& s) {
        // Base case: if we've reached the end of the string, the segmentation is successful.
        if (idx == n) {
            return true;
        }

        // Return the stored result if it exists to avoid recomputation.
        if (t[idx] != -1) {
            return t[idx];
        }

        // Check if the remaining substring is a word in the dictionary.
        if (st.find(s.substr(idx)) != st.end()) {
            return t[idx] = true;
        }

        // Limit substring length to the maximum word length in the dictionary.
        int limit = min(maxLen, n - idx);
        for (int l = 1; l <= limit; l++) {
            // Extract substring starting from idx with length l.
            string temp = s.substr(idx, l);
            // If the substring is in the dictionary and the remaining string can be segmented, return true.
            if (st.find(temp) != st.end() && solve(idx + l, s)) {
                return t[idx] = true;
            }
        }

        // If no valid segmentation is found, store and return false.
        return t[idx] = false;
    }
    
    // Main function that initializes variables and starts the recursion.
    int wordBreak(string& s, vector<string>& dictionary) {
        n = s.size();
        memset(t, -1, sizeof(t));      // Initialize memoization array with -1 (unset).
        maxLen = 0;
        // Insert all words into the set and find the maximum word length.
        for (string& word : dictionary) {
            st.insert(word);
            maxLen = max(maxLen, (int)word.size());
        }

        // Start the recursion from index 0.
        return solve(0, s);
    }
};

/*
 * Dry Run:
 * Input: s = "ilike", dictionary = ["i", "like", "gfg"]
 *
 * Step 1: wordBreak is called.
 *  - n = 5, t[] initialized to -1, maxLen = 4 (from "like")
 *  - st = {"i", "like", "gfg"}
 *
 * Step 2: solve(0, s) is called.
 *  - idx = 0, s.substr(0) = "ilike" is not in st.
 *  - limit = min(4, 5-0) = 4.
 *  - l = 1: temp = "i", which is in st.
 *        -> Call solve(1, s).
 *
 * Step 3: solve(1, s) is called.
 *  - idx = 1, s.substr(1) = "like" is in st.
 *  - Return true from solve(1, s) and memoize t[1] = true.
 *
 * Step 4: Back in solve(0, s), since solve(1, s) returned true, memoize t[0] = true and return true.
 *
 * Final Result: The string "ilike" can be segmented as "i like".
 */

/************************************************************ JAVA ************************************************/

// Approach: Use recursion with memoization (DP) to check if the string can be segmented into dictionary words by trying every possible prefix and using a lookup set for fast word verification.
// Time Complexity: O(n * maxLen) - For each index (n total), we try up to maxLen substrings.
// Space Complexity: O(n) - For the memoization array and recursion call stack.
class Solution {
    private int n;
    private int[] t;         // Memoization array: -1 = not computed, 0 = false, 1 = true
    private int maxLen;
    private Set<String> set; // Set to store dictionary words for quick lookup

    // Recursive function to determine if s.substring(idx) can be segmented
    private boolean solve(int idx, String s) {
        if (idx == n) {
            return true;           // Base case: reached end of string
        }
        if (t[idx] != -1) {
            return t[idx] == 1;               // Return memoized result if available
        }
        // If the entire substring from idx is in the dictionary, we can return true
        if (set.contains(s.substring(idx))) {
            t[idx] = 1;
            return true;
        }

        // Limit the substring length to the maximum word length in the dictionary
        int limit = Math.min(maxLen, n - idx);
        for (int l = 1; l <= limit; l++) {
            String temp = s.substring(idx, idx + l);
            if (set.contains(temp) && solve(idx + l, s)) {
                t[idx] = 1;
                return true;
            }
        }

        t[idx] = 0; // Mark this index as not breakable
        return false;
    }

    public int wordBreak(String s, String[] dictionary) {
        n = s.length();
        t = new int[n + 1];
        Arrays.fill(t, -1);
        maxLen = 0;
        set    = new HashSet<>();

        // Insert dictionary words into the set and update maximum word length
        for (String word : dictionary) {
            set.add(word);
            maxLen = Math.max(maxLen, word.length());
        }

        return solve(0, s) ? 1 : 0;
    }
}

/*
 * Dry Run:
 * Input: s = "ilike", dictionary = ["i", "like", "gfg"]
 *
 * Step 1: wordBreak is called.
 *  - n = 5, t[] initialized to -1, maxLen = 4 (from "like")
 *  - set = {"i", "like", "gfg"}
 *
 * Step 2: solve(0, s) is called.
 *  - idx = 0, s.substring(0) = "ilike" is not in set.
 *  - limit = min(4, 5-0) = 4.
 *  - l = 1: temp = "i", which is in set.
 *        -> Call solve(1, s).
 *
 * Step 3: solve(1, s) is called.
 *  - idx = 1, s.substring(1) = "like" is in set.
 *  - Return true from solve(1, s) and memoize t[1] = 1.
 *
 * Step 4: Back in solve(0, s), since solve(1, s) returned true, memoize t[0] = 1 and return true.
 *
 * Final Result: The string "ilike" can be segmented as "i like".
 */
