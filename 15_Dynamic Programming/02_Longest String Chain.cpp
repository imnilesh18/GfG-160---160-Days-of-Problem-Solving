/*
 * Longest String Chain
 *
 * You are given an array of words where each word consists of lowercase English letters.
 * wordA is a predecessor of wordB if and only if we can insert exactly one letter anywhere in wordA without changing the order of the other characters to make it equal to wordB. For example, "abc" is a predecessor of "abac", while "cba" is not a predecessor of "bcad".
 *
 * A word chain is a sequence of words [word1, word2, ..., wordk] with k >= 1, where word1 is a predecessor of word2, word2 is a predecessor of word3, and so on. A single word is trivially a word chain with k = 1.
 *
 * Return the length of the longest possible word chain with words chosen from the given list of words in any order.
 *
 * Examples:
 *
 * Input: words[] = ["ba", "b", "a", "bca", "bda", "bdca"]
 * Output: 4
 * Explanation: One of the longest word chains is ["a", "ba", "bda", "bdca"].
 *
 * Input: words[] = ["abcd", "dbqca"]
 * Output: 1
 * Explanation: The trivial word chain ["abcd"] is one of the longest word chains.
 *
 * Constraint:
 * 1 <= words.length <= 10^4
 * 1 <= words[i].length <= 10
 * words[i] only consists of lowercase English letters.
 */

/************************************************************ C++ ************************************************/

// Approach: Sort words by length and use a hash map to store the longest chain ending at each word.
// Time Complexity: O(n * k^2), where n is the number of words and k is the maximum word length (substring operations take O(k)).
// Space Complexity: O(n * k), for storing words in the hash map.
class Solution {
public:
    int longestStringChain(vector<string>& words) {
        sort(words.begin(), words.end(), [](const string& a, const string& b) {
            return a.size() < b.size();
        });
        unordered_map<string, int> dp;
        int ans = 0;
        for (const string& word : words) {
            int best = 0;
            for (int i = 0; i < word.size(); i++) {
                // Remove one character at position i to form the predecessor
                string pred = word.substr(0, i) + word.substr(i + 1);
                best = max(best, dp.count(pred) ? dp[pred] : 0);
            }
            dp[word] = best + 1;
            ans      = max(ans, dp[word]);
        }
        return ans;
    }
};

/*
 * Dry Run:
 * Input words: ["a", "ba", "bda", "bdca"]
 *
 * Sorted words: ["a", "ba", "bda", "bdca"]
 * Iteration:
 * 1. word = "a":
 * - Remove index 0: "" (not in dp), best = 0
 * - dp["a"] = 0 + 1 = 1, ans = 1
 * 2. word = "ba":
 * - Remove index 0: "a" (dp["a"] = 1), best = 1
 * - Remove index 1: "b" (not in dp), best remains 1
 * - dp["ba"] = 1 + 1 = 2, ans = 2
 * 3. word = "bda":
 * - Remove index 0: "da" (not in dp), best = 0
 * - Remove index 1: "ba" (dp["ba"] = 2), best = 2
 * - Remove index 2: "bd" (not in dp), best remains 2
 * - dp["bda"] = 2 + 1 = 3, ans = 3
 * 4. word = "bdca":
 * - Remove index 0: "dca" (not in dp), best = 0
 * - Remove index 1: "bca" (not in dp), best remains 0
 * - Remove index 2: "bda" (dp["bda"] = 3), best = 3
 * - Remove index 3: "bdc" (not in dp), best remains 3
 * - dp["bdca"] = 3 + 1 = 4, ans = 4
 * Final Answer: 4
 */

/************************************************************ JAVA ************************************************/

// Approach: Sort words by length and use a HashMap to store the longest chain ending at each word.
// Time Complexity: O(n * k^2), where n is the number of words and k is the maximum word length (substring operations take O(k)).
// Space Complexity: O(n * k), for storing words in the HashMap.
class Solution {
    public int longestStringChain(String words[]) {
        Arrays.sort(words, (a, b)->a.length() - b.length());
        HashMap<String, Integer> dp = new HashMap<>();
        int ans = 0;
        for (String word : words) {
            int best = 0;
            for (int i = 0; i < word.length(); i++) {
                // Remove one character at position i to form the predecessor
                String pred = word.substring(0, i) + word.substring(i + 1);
                best = Math.max(best, dp.getOrDefault(pred, 0));
            }
            dp.put(word, best + 1);
            ans = Math.max(ans, dp.get(word));
        }
        return ans;
    }
}

/*
 * Dry Run:
 * Input words: ["a", "ba", "bda", "bdca"]
 *
 * Sorted words: ["a", "ba", "bda", "bdca"]
 * Iteration:
 * 1. word = "a":
 * - Remove index 0: "" (not in dp), best = 0
 * - dp.put("a", 0 + 1) => dp["a"] = 1, ans = 1
 * 2. word = "ba":
 * - Remove index 0: "a" (dp["a"] = 1), best = 1
 * - Remove index 1: "b" (not in dp), best remains 1
 * - dp.put("ba", 1 + 1) => dp["ba"] = 2, ans = 2
 * 3. word = "bda":
 * - Remove index 0: "da" (not in dp), best = 0
 * - Remove index 1: "ba" (dp["ba"] = 2), best = 2
 * - Remove index 2: "bd" (not in dp), best remains 2
 * - dp.put("bda", 2 + 1) => dp["bda"] = 3, ans = 3
 * 4. word = "bdca":
 * - Remove index 0: "dca" (not in dp), best = 0
 * - Remove index 1: "bca" (not in dp), best remains 0
 * - Remove index 2: "bda" (dp["bda"] = 3), best = 3
 * - Remove index 3: "bdc" (not in dp), best remains 3
 * - dp.put("bdca", 3 + 1) => dp["bdca"] = 4, ans = 4
 * Final Answer: 4
 */
