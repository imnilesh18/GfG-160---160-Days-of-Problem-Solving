/*
 *
 * Alien Dictionary
 *
 * Difficulty: Hard Accuracy: 47.81 % Submissions : 158K + Points : 8
 *
 * A new alien language uses the English alphabet, but the order of letters is unknown.You are given a list of words[] from the alien language’s dictionary, where the words are claimed to be sorted lexicographically according to the language’s rules.
 *
 * Your task is to determine the correct order of letters in this alien language based on the given words.If the order is valid, return a string containing the unique letters in lexicographically increasing order as per the new language 's rules. If there are multiple valid orders, return any one of them.
 *
 * However, if the given arrangement of words is inconsistent with any possible letter ordering, return an empty string ("").
 *
 * A string a is lexicographically smaller than a string b if, at the first position where they differ, the character in a appears earlier in the alien language than the corresponding character in b. If all characters in the shorter word match the beginning of the longer word, the shorter word is considered smaller.
 *
 * Note: Your implementation will be tested using a driver code. It will print true if your returned order correctly follows the alien language’s lexicographic rules; otherwise, it will print false.
 *
 * Examples:
 *
 * Input: words[] = ["baa", "abcd", "abca", "cab", "cad"]
 * Output: true
 * Explanation: A possible corrct order of letters in the alien dictionary is "bdac".
 * The pair "baa" and "abcd" suggests 'b ' appears before 'a ' in the alien dictionary.
 * The pair "abcd" and "abca" suggests 'd ' appears before 'a ' in the alien dictionary.
 * The pair "abca" and "cab" suggests 'a ' appears before 'c ' in the alien dictionary.
 * The pair "cab" and "cad" suggests 'b ' appears before 'd ' in the alien dictionary.
 * So, 'b ' → 'd' → 'a' → 'c ' is a valid ordering.
 *
 * Input: words[] = ["caa", "aaa", "aab"]
 * Output: true
 * Explanation: A possible corrct order of letters in the alien dictionary is "cab".
 * The pair "caa" and "aaa" suggests 'c ' appears before 'a '.
 * The pair "aaa" and "aab" suggests 'a ' appear before 'b ' in the alien dictionary.
 * So, 'c ' → 'a' → 'b ' is a valid ordering.
 *
 * Input: words[] = ["ab", "cd", "ef", "ad"]
 * Output: ""
 * Explanation: No valid ordering of letters is possible.
 * The pair "ab" and "ef" suggests "a" appears before "e".
 * The pair "ef" and "ad" suggests "e" appears before "a", which contradicts the ordering rules.
 *
 * Constraints:
 * 1 ≤ words.length ≤ 500
 * 1 ≤ words[i].length ≤ 100
 * words[i] consists only of lowercase English letters.
 */

/************************************************************ C++ ************************************************/

// Approach: Use topological sort (Kahn's algorithm) on a directed graph constructed from adjacent word comparisons to determine character order.
// Time Complexity: O(N * L + V + E) where N is number of words, L is maximum word length, V is unique letters, and E is relationships between letters.
// Space Complexity: O(V + E) for storing the graph and indegree map.
class Solution {
public:
    string findOrder(vector<string>& words) {
        unordered_map<char, unordered_set<char>> graph;        // Graph: char -> set of chars that follow
        unordered_map<char, int> indegree;                      // Count of incoming edges for each char

        // Initialize all unique letters with 0 indegree
        for (const string& word : words) {
            for (char c : word) {
                indegree[c] = 0;
            }
        }

        // Build graph by comparing adjacent words
        for (int i = 0; i < words.size() - 1; i++) {
            string word1           = words[i];
            string word2           = words[i + 1];
            int    len             = min(word1.size(), word2.size());
            bool   foundDifference = false;
            for (int j = 0; j < len; j++) {
                if (word1[j] != word2[j]) {
                    if (graph[word1[j]].find(word2[j]) == graph[word1[j]].end()) {
                        graph[word1[j]].insert(word2[j]);
                        indegree[word2[j]]++;
                    }
                    foundDifference = true;
                    break;
                }
            }
            // Check for invalid case: word1 is longer than word2 but word2 is a prefix of word1
            if (!foundDifference && word1.size() > word2.size()) {
                return "";
            }
        }

        // Topological sort using Kahn's algorithm
        queue<char> q;
        // Push characters with 0 indegree
        for (auto& entry : indegree) {
            if (entry.second == 0) {
                q.push(entry.first);
            }
        }

        string order;
        while (!q.empty()) {
            char curr = q.front();
            q.pop();
            order.push_back(curr);
            // Decrement the indegree for neighbors of current char
            if (graph.find(curr) != graph.end()) {
                for (char neighbor : graph[curr]) {
                    indegree[neighbor]--;
                    if (indegree[neighbor] == 0) {
                        q.push(neighbor);
                    }
                }
            }
        }

        // Check if topological ordering is possible (i.e., no cycle exists)
        if (order.size() != indegree.size()) {
            return "";
        }
        return order;
    }
};

/*
 * Dry Run
 *
 * Example:
 * words = ["baa", "abcd", "abca", "cab", "cad"]
 *
 * 1. Unique characters identified: b, a, c, d; indegree map initialized: {b:0, a:0, c:0, d:0}
 * 2. Compare "baa" and "abcd": first difference at index 0: 'b' != 'a', add edge b -> a, indegree of a becomes 1.
 * 3. Compare "abcd" and "abca": first difference at index 3: 'd' != 'a', add edge d -> a, indegree of a becomes 2.
 * 4. Compare "abca" and "cab": first difference at index 0: 'a' != 'c', add edge a -> c, indegree of c becomes 1.
 * 5. Compare "cab" and "cad": first difference at index 2: 'b' != 'd', add edge b -> d, indegree of d becomes 1.
 * 6. Graph now: {b: {'a', 'd'}, d: {'a'}, a: {'c'}}, indegree: {b:0, a:2, c:1, d:1}
 * 7. Kahn's algorithm: Initialize queue with 'b'. Process 'b': order = "b"; update: 'a' indegree becomes 1, 'd' indegree becomes 0.
 * 8. Enqueue 'd'. Process 'd': order = "bd"; update: 'a' indegree becomes 0.
 * 9. Enqueue 'a'. Process 'a': order = "bda"; update: 'c' indegree becomes 0.
 * 10. Enqueue 'c'. Process 'c': order = "bdac".
 * 11. Final order "bdac" of length 4 equals number of unique characters. Hence, valid ordering.
 */

/************************************************************ JAVA ************************************************/

// Approach: Use topological sort (Kahn's algorithm) on a directed graph built by comparing adjacent words to deduce character order.
// Time Complexity: O(N * L + V + E) where N is number of words, L is max word length, V is number of unique characters, and E is number of edges.
// Space Complexity: O(V + E) for storing the graph and indegree mappings.
class Solution {
    public String findOrder(String[] words) {
        // Map for storing the graph: each character to a set of characters that follow it.
        Map<Character, Set<Character>> graph = new HashMap<>();
        // Map for storing the indegree (number of incoming edges) for each character.
        Map<Character, Integer> indegree = new HashMap<>();

        // Initialize indegree for every unique character in the words array.
        for (String word : words) {
            for (char c : word.toCharArray()) {
                indegree.put(c, 0);
            }
        }

        // Build the graph by comparing adjacent words.
        for (int i = 0; i < words.length - 1; i++) {
            String word1 = words[i];
            String word2 = words[i + 1];
            // Compare the words character by character.
            int     len             = Math.min(word1.length(), word2.length());
            boolean foundDifference = false;
            for (int j = 0; j < len; j++) {
                char parent = word1.charAt(j);
                char child  = word2.charAt(j);
                if (parent != child) {
                    // If an edge from parent to child doesn't exist, add it.
                    Set<Character> set = graph.getOrDefault(parent, new HashSet<>());
                    if (!set.contains(child)) {
                        set.add(child);
                        graph.put(parent, set);
                        // Increase indegree for the child.
                        indegree.put(child, indegree.get(child) + 1);
                    }
                    foundDifference = true;
                    break;
                }
            }
            // Check for invalid input where word1 is longer than word2 but word2 is a prefix of word1.
            if (!foundDifference && word1.length() > word2.length()) {
                return "";
            }
        }

        // Perform topological sort using Kahn's algorithm.
        Queue<Character> queue = new LinkedList<>();
        // Add all characters with 0 indegree to the queue.
        for (Map.Entry<Character, Integer> entry : indegree.entrySet()) {
            if (entry.getValue() == 0) {
                queue.add(entry.getKey());
            }
        }

        StringBuilder order = new StringBuilder();
        while (!queue.isEmpty()) {
            char curr = queue.poll();
            order.append(curr);
            // If the current character has outgoing edges, reduce the indegree of the neighbors.
            if (graph.containsKey(curr)) {
                for (char neighbor : graph.get(curr)) {
                    indegree.put(neighbor, indegree.get(neighbor) - 1);
                    if (indegree.get(neighbor) == 0) {
                        queue.add(neighbor);
                    }
                }
            }
        }

        // If the resulting order's length isn't equal to the number of unique characters, there's a cycle.
        if (order.length() != indegree.size()) {
            return "";
        }
        return order.toString();
    }
}

/*
 * Dry Run
 *
 * Example:
 * words = ["baa", "abcd", "abca", "cab", "cad"]
 *
 * 1. Initialize indegree for unique characters: {b:0, a:0, c:0, d:0}
 * 2. Compare "baa" and "abcd":
 *    - At index 0: 'b' != 'a'; add edge b -> a, indegree of a becomes 1.
 * 3. Compare "abcd" and "abca":
 *    - At index 3: 'd' != 'a'; add edge d -> a, indegree of a becomes 2.
 * 4. Compare "abca" and "cab":
 *    - At index 0: 'a' != 'c'; add edge a -> c, indegree of c becomes 1.
 * 5. Compare "cab" and "cad":
 *    - At index 2: 'b' != 'd'; add edge b -> d, indegree of d becomes 1.
 * 6. Graph: {b: [a, d], d: [a], a: [c]}; indegree: {b:0, a:2, c:1, d:1}
 * 7. Topological sort:
 *    - Start with 'b' (indegree 0); process neighbors: a becomes 1, d becomes 0.
 *    - Next, process 'd'; process neighbor: a becomes 0.
 *    - Process 'a'; process neighbor: c becomes 0.
 *    - Process 'c'. Order formed: "bdac".
 * 8. Since the order length (4) equals number of unique characters, return "bdac".
 */
