/*
 * Implement Trie
 *
 * Difficulty: Medium Accuracy: 65.68% Submissions: 69K+ Points: 4 Average Time: 30m
 *
 * Implement Trie class and complete insert(), search() and isPrefix() function for the following queries :
 *
 * Type 1 : (1, word), calls insert(word) function and insert word in the Trie
 * Type 2 : (2, word), calls search(word) function and check whether word exists in Trie or not.
 * Type 3 : (3, word), calls isPrefix(word) function and check whether word exists as a prefix of any string in Trie or not.
 *
 * Examples :
 *
 * Input: query[][] = [[1, "abcd"], [1, "abc"], [1, "bcd"], [2, "bc"], [3, "bc"], [2, "abc"]]
 * Output: [false, true, true]
 * Explanation: string "bc" does not exist in the trie, "bc" exists as prefix of the word "bcd" in the trie, and "abc" also exists in the trie.
 *
 * Input: query[][] = [[1, "gfg"], [1, "geeks"], [3, "fg"], [3, "geek"], [2, "for"]]
 * Output: [false, true, false]
 * Explanation: The string "for" is not present in the trie, "fg" is not a valid prefix, while "geek" is a valid prefix of the word "geeks" in the trie.
 *
 * Constraints:
 * 1 ≤ query.size() ≤ 10^4
 * 1 ≤ word.size() ≤ 10^3
 */

/************************************************************ C++ ************************************************/

// Approach: Use a 26-way trie (prefix tree) where each node has up-to-26 children pointers and an “end-of-word” flag; insert by walking/creating nodes, search by walking and checking end flag, prefix check by walking only.
// Time Complexity: insert/search/isPrefix each take O(L) time per operation, where L = length of the word.
// Space Complexity: O(N * L) in the worst case, for storing N words of average length L (each character may allocate a new node).
class Trie {
public:

    struct trieNode {
        bool      isEndOfWord;        // true if node marks end of a word
        trieNode* children[26];       // pointers to child nodes for 'a' to 'z'
    };

    // Utility to allocate a new trie node
    trieNode* getNode() {
        trieNode* newNode = new trieNode();

        newNode->isEndOfWord = false;
        for (int i = 0; i < 26; i++) {
            newNode->children[i] = nullptr;
        }
        return newNode;
    }
    trieNode* root;      // root of trie

    // Constructor: initialize root node
    Trie() {
        root = getNode();
    }
    // Insert a word into the trie
    void insert(string& word) {
        trieNode* crawler = root;                   // start at root

        for (char ch : word) {                      // for each character
            int idx = ch - 'a';                     // map 'a'..'z' to 0..25
            if (crawler->children[idx] == nullptr) {
                crawler->children[idx] = getNode(); // create node if missing
            }
            crawler = crawler->children[idx];       // move to child
        }
        crawler->isEndOfWord = true;                // mark end of word
    }
    // Search for a full word in the trie
    bool search(string& word) {
        trieNode* crawler = root;                 // start at root

        for (char ch : word) {                    // traverse each character
            int idx = ch - 'a';
            if (crawler->children[idx] == nullptr) {
                return false;                     // missing node → word not present
            }
            crawler = crawler->children[idx];
        }
        return crawler != nullptr && crawler->isEndOfWord;      // true if end-of-word flag set
    }
    // Check if any word in trie starts with given prefix
    bool isPrefix(string& word) {
        trieNode* crawler = root;                 // start at root

        for (char ch : word) {                    // traverse prefix
            int idx = ch - 'a';
            if (crawler->children[idx] == nullptr) {
                return false;                     // missing node → no such prefix
            }
            crawler = crawler->children[idx];
        }
        return true;                              // all chars found → valid prefix
    }
};

/*
 * Dry Run
 *
 * Suppose we run the following queries:
 *   insert("abcd")
 *   insert("abc")
 *   insert("bcd")
 *   search("bc")    → false (no path b→c→ for a full word)
 *   isPrefix("bc")  → true  (b→c exists as start of "bcd")
 *   search("abc")   → true  (a→b→c marked end-of-word at node 'c')
 *
 * Step-by-step:
 * 1) insert("abcd"):
 *    root → 'a'(new) → 'b'(new) → 'c'(new) → 'd'(new, mark end)
 * 2) insert("abc"):
 *    root → 'a'(exists) → 'b'(exists) → 'c'(exists, mark end)
 * 3) insert("bcd"):
 *    root → 'b'(new) → 'c'(new) → 'd'(new, mark end)
 * 4) search("bc"):
 *    root → 'b' exists → 'c' exists → reached node, but isEndOfWord==false → return false
 * 5) isPrefix("bc"):
 *    root → 'b' exists → 'c' exists → prefix exists → return true
 * 6) search("abc"):
 *    root → 'a' exists → 'b' exists → 'c' exists with isEndOfWord==true → return true
 */

/************************************************************ JAVA ************************************************/

// Approach: Use a 26-way trie (prefix tree) where each node has up to 26 children and a flag marking end-of-word; insert by creating/traversing nodes, search by traversing and checking the end flag, prefix check by traversing only.
// Time Complexity: insert/search/isPrefix each take O(L) time per operation, where L = length of the word.
// Space Complexity: O(N * L) in the worst case for storing N words of average length L (each new character may allocate a new node).
class Trie {
    // Node structure for the trie
    static class TrieNode {
        TrieNode[] children;    // child links for 'a' to 'z'
        boolean isEndOfWord;    // true if this node completes a word

        TrieNode() {
            children    = new TrieNode[26];
            isEndOfWord = false;
        }
    }

    private TrieNode root;  // root of the trie

    // Constructor initializes the trie with an empty root node
    Trie() {
        root = new TrieNode();
    }
    // Insert a word into the trie
    public void insert(String word) {
        TrieNode crawler = root;                // start at the root

        for (int i = 0; i < word.length(); i++) {
            int index = word.charAt(i) - 'a';             // map 'a'..'z' to 0..25
            if (crawler.children[index] == null) {
                crawler.children[index] = new TrieNode(); // create node if missing
            }
            crawler = crawler.children[index];            // move to the child
        }
        crawler.isEndOfWord = true;                       // mark end of word
    }
    // Search for a full word in the trie
    public boolean search(String word) {
        TrieNode crawler = root;                // start at the root

        for (int i = 0; i < word.length(); i++) {
            int index = word.charAt(i) - 'a';
            if (crawler.children[index] == null) {
                return false;                          // missing node → word not present
            }
            crawler = crawler.children[index];         // move to child
        }
        return crawler != null && crawler.isEndOfWord; // true only if end-of-word flag is set
    }
    // Check if any word in the trie starts with the given prefix
    public boolean isPrefix(String prefix) {
        TrieNode crawler = root;                // start at the root

        for (int i = 0; i < prefix.length(); i++) {
            int index = prefix.charAt(i) - 'a';
            if (crawler.children[index] == null) {
                return false;                   // missing node → no such prefix
            }
            crawler = crawler.children[index];  // move to child
        }
        return true;                            // all prefix characters found
    }
}

/*
 * Dry Run
 *
 * Queries:
 *   insert("abcd")
 *   insert("abc")
 *   insert("bcd")
 *   search("bc")    → false (node exists but not marked end)
 *   isPrefix("bc")  → true  (prefix exists)
 *   search("abc")   → true  (node marked end)
 *
 * Steps:
 * 1) insert("abcd"):
 *    root → 'a'(new) → 'b'(new) → 'c'(new) → 'd'(new, mark end)
 * 2) insert("abc"):
 *    root → 'a'(exists) → 'b'(exists) → 'c'(exists, mark end)
 * 3) insert("bcd"):
 *    root → 'b'(new) → 'c'(new) → 'd'(new, mark end)
 * 4) search("bc"):
 *    root → 'b' exists → 'c' exists → reached node, isEndOfWord==false → return false
 * 5) isPrefix("bc"):
 *    root → 'b' exists → 'c' exists → return true
 * 6) search("abc"):
 *    root → 'a' exists → 'b' exists → 'c' exists, isEndOfWord==true → return true
 */
