/*
 * Print Anagrams Together
 *
 * Given an array of strings, return all groups of strings that are anagrams. The groups must be created in order of their appearance in the original array. Look at the sample case for clarification.
 *
 * Note: The final output will be in lexicographic order.
 *
 * Examples:
 *
 * Input: arr[] = ["act", "god", "cat", "dog", "tac"]
 * Output: [["act", "cat", "tac"], ["god", "dog"]]
 * Explanation: There are 2 groups of anagrams "god", "dog" make group 1. "act", "cat", "tac" make group 2.
 *
 * Input: arr[] = ["no", "on", "is"]
 * Output: [["is"], ["no", "on"]]
 * Explanation: There are 2 groups of anagrams "is" makes group 1. "no", "on" make group 2.
 *
 * Input: arr[] = ["listen", "silent", "enlist", "abc", "cab", "bac", "rat", "tar", "art"]
 * Output: [["abc", "cab", "bac"], ["listen", "silent", "enlist"], ["rat", "tar", "art"]]
 * Explanation:
 * Group 1: "abc", "bac", and "cab" are anagrams.
 * Group 2: "listen", "silent", and "enlist" are anagrams.
 * Group 3: "rat", "tar", and "art" are anagrams.
 *
 * Constraints:
 * 1<= arr.size() <=100
 * 1<= arr[i].size() <=10
 */

/************************************************************ C++ ************************************************/

// Approach: Store sorted version of each string as key in map and original strings as values to group anagrams.
// Time Complexity: O(n * k * log k) where n is array size and k is max string length, due to sorting
// Space Complexity: O(n * k) for storing strings in map
class Solution {
public:
   vector<vector<string> > anagrams(vector<string>& arr){
      // Map to store sorted string as key and list of anagrams as value
      unordered_map<string, vector<string> > mp;

      // Iterate through each string in input array
      for (auto it: arr) {
         string key = it;
         // Sort characters to get canonical form for anagram comparison
         sort(key.begin(), key.end());
         // Add original string to vector mapped to sorted key
         mp[key].push_back(it);
      }

      vector<vector<string> > result;

      // Convert map values to result vector
      for (auto it: mp) {
         result.push_back(it.second);
      }

      return result;
   }
};

/************************************************************ JAVA ************************************************/

// Approach: Sort individual strings and use as keys in HashMap to group anagrams together in ArrayLists
// TC: O(n * k * logk) - n strings of length k, sorting each string takes k*logk time
// SC: O(n * k) - storing n strings of max length k in HashMap
class Solution {
   public ArrayList<ArrayList<String> > anagrams(String[] arr){
      // HashMap to store sorted string as key and list of anagrams as value
      Map<String, ArrayList<String> > map = new HashMap<>();

      // Iterate through input array
      for (String str : arr) {
         // Convert string to char array and sort to get canonical form
         char[] chars = str.toCharArray();
         Arrays.sort(chars);
         String key = new String(chars);

         // Create new ArrayList if key not present
         if (!map.containsKey(key)) {
            map.put(key, new ArrayList<>());
         }
         // Add original string to list of anagrams
         map.get(key).add(str);
      }

      // Convert map values to ArrayList and return
      return new ArrayList<>(map.values());
   }
}
