/*
 * LRU Cache
 *
 * Design a data structure that works like a LRU Cache. Here cap denotes the capacity of the cache and Q denotes the number of queries. Query can be of two types:
 *
 * PUT x y: sets the value of the key x with value y
 * GET x: gets the key of x if present else returns -1.
 * The LRUCache class has two methods get() and put() which are defined as follows.
 *
 * get(key): returns the value of the key if it already exists in the cache otherwise returns -1.
 * put(key, value): if the key is already present, update its value. If not present, add the key-value pair to the cache. If the cache reaches its capacity it should remove the least recently used item before inserting the new item.
 * In the constructor of the class the capacity of the cache should be initialized.
 *
 * Examples:
 *
 * Input: cap = 2, Q = 2, Queries = [["PUT", 1, 2], ["GET", 1]]
 * Output: [2]
 * Explanation: Cache Size = 2
 * ["PUT", 1, 2] will insert the key-value pair (1, 2) in the cache,
 * ["GET", 1] will print the value corresponding to Key 1, ie 2.
 *
 * Input: cap = 2, Q = 8, Queries = [["PUT", 1, 2], ["PUT", 2, 3], ["PUT", 1, 5], ["PUT", 4, 5], ["PUT", 6, 7], ["GET", 4], ["PUT", 1, 2], ["GET", 3]]
 * Output: [5, -1]
 * Explanation: Cache Size = 2
 * ["PUT", 1, 2] will insert the pair (1,2) in the cache.
 * ["PUT", 2, 3] will insert the pair (2,3) in the cache: 1->2, 2->3(the most recently used one is kept at the rightmost position)
 * ["PUT", 1, 5] will replace the value of 1 from 2 to 5 : 2 -> 3, 1 -> 5
 * ["PUT", 4, 5] : 1 -> 5, 4 -> 5 (Cache size is 2, hence we delete the least recently used key-value pair)
 * ["PUT", 6, 7] : 4 -> 5, 6 -> 7
 * ["GET", 4] : Prints 5 (The cache now looks like 6 -> 7, 4->5)
 * ["PUT", 1, 2] : 4 -> 5, 1 -> 2  (Cache size is 2, hence we delete the least recently used key-value pair)
 * ["GET", 3] : No key value pair having key = 3. Hence, -1 is printed.
 *
 * Constraints:
 * 1 <= cap <= 10^3
 * 1 <= Q <= 10^5
 * 1 <= x, y <= 10^4
 */

/************************************************************ C++ ************************************************/

// Approach 1: Linear search in vector, move recently used item to end
// Time Complexity: O(n) for both get and put operations
// Space Complexity: O(capacity) to store key-value pairs
class LRUCache {
private:
   // Vector to store key-value pairs in the cache
   vector<pair<int, int> > cache;

   // Maximum capacity of the cache
   int n;

public:
   // Constructor to initialize cache with specified capacity
   LRUCache(int cap) {
      n = cap;
   }

   // Retrieve value for a given key
   int get(int key) {
      // Iterate through cache to find the key
      for (int i = 0; i < cache.size(); i++) {
         // If key is found
         if (cache[i].first == key) {
            // Store the value
            int val = cache[i].second;

            // Create a temporary copy of the current pair
            pair<int, int> temp = cache[i];

            // Remove the current entry
            cache.erase(cache.begin() + i);

            // Move the entry to the end (most recently used)
            cache.push_back(temp);

            // Return the value
            return val;
         }
      }
      // Return -1 if key not found
      return -1;
   }

   // Store or update a key-value pair
   void put(int key, int value) {
      // Check if key already exists
      for (int i = 0; i < cache.size(); i++) {
         if (cache[i].first == key) {
            // Remove existing entry
            cache.erase(cache.begin() + i);

            // Add updated entry at the end
            cache.push_back({ key, value });
            return;
         }
      }

      // If cache is full, remove the least recently used item (first item)
      if (cache.size() == n) {
         cache.erase(cache.begin());
         cache.push_back({ key, value });
      }
      // If cache is not full, simply add the new item
      else {
         cache.push_back({ key, value });
      }
   }
};

// Approach 2: Doubly Linked List + Hashmap for O(1) operations
// Time Complexity: O(1) for both get and put operations
// Space Complexity: O(capacity) to store key-value mappings
class LRUCache {
private:
   // Doubly Linked List to maintain order of recently used items
   list<int> dll;

   // Map to store key to (iterator, value) mapping
   map<int, pair<list<int>::iterator, int> > mp;

   // Remaining capacity of cache
   int n;

public:
   // Constructor to initialize cache capacity
   LRUCache(int cap) {
      n = cap;
   }

   // Move a key to the front (most recently used)
   void makeRecentlyUsed(int key) {
      // Remove existing position of key
      dll.erase(mp[key].first);

      // Add key to front of list
      dll.push_front(key);

      // Update iterator in map
      mp[key].first = dll.begin();
   }

   // Retrieve value for a given key
   int get(int key) {
      // If key not in cache
      if (mp.find(key) == mp.end()) {
         return -1;
      }

      // Update key's position to most recently used
      makeRecentlyUsed(key);

      // Return value
      return mp[key].second;
   }

   // Store or update key-value pair
   void put(int key, int value) {
      // If key already exists
      if (mp.find(key) != mp.end()) {
         // Update value
         mp[key].second = value;

         // Move to most recently used
         makeRecentlyUsed(key);
      } else {
         // Add new key to front of list
         dll.push_front(key);

         // Map key to its iterator and value
         mp[key] = { dll.begin(), value };

         // Decrease remaining capacity
         n--;
      }

      // If cache exceeds capacity
      if (n < 0) {
         // Get least recently used key
         int key_to_be_deleted = dll.back();

         // Remove from map
         mp.erase(key_to_be_deleted);

         // Remove from list
         dll.pop_back();

         // Restore capacity
         n++;
      }
   }
};

/************************************************************ JAVA ************************************************/

// Approach 1: Linear search in ArrayList, move recently used item to end
// Time Complexity: O(n) for both get and put operations
// Space Complexity: O(capacity) to store key-value pairs
class LRUCache {
   // List to store key-value pairs in the cache
   private List<Pair> cache;

   // Maximum number of items the cache can hold
   private int capacity;

   // Constructor to initialize cache with specified capacity
   public LRUCache(int cap) {
      // Set the maximum capacity
      this.capacity = cap;

      // Initialize an empty ArrayList to store cache entries
      this.cache = new ArrayList<>();
   }

   // Retrieve value for a given key
   public int get(int key) {
      // Iterate through cache to find the key
      for (int i = 0; i < cache.size(); i++) {
         // Check if current entry matches the key
         if (cache.get(i).key == key) {
            // Store the found pair
            Pair temp = cache.get(i);

            // Remove the current entry
            cache.remove(i);

            // Move the entry to the end (most recently used)
            cache.add(temp);

            // Return the value associated with the key
            return temp.value;
         }
      }

      // Return -1 if key not found in cache
      return -1;
   }

   // Store or update a key-value pair
   public void put(int key, int value) {
      // Check if key already exists in cache
      for (int i = 0; i < cache.size(); i++) {
         if (cache.get(i).key == key) {
            // Remove existing entry
            cache.remove(i);

            // Add updated entry at the end
            cache.add(new Pair(key, value));
            return;
         }
      }

      // If cache is at full capacity
      if (cache.size() == capacity) {
         // Remove the least recently used item (first item)
         cache.remove(0);
      }

      // Add new key-value pair to the end of the cache
      cache.add(new Pair(key, value));
   }

   // Inner class to represent a key-value pair
   private class Pair {
      // Key of the cache entry
      int key;

      // Value associated with the key
      int value;

      // Constructor to create a new pair
      Pair(int key, int value) {
         this.key   = key;
         this.value = value;
      }
   }
}

// Approach 2: Doubly Linked List + Hashmap for O(1) operations
// Time Complexity: O(1) for both get and put operations
// Space Complexity: O(capacity) to store key-value mappings
class LRUCache {
   // Doubly Linked List to maintain order of recently used items
   private LinkedList<Integer> dll;

   // Map to store key to (index, value) mapping
   private Map<Integer, Node> map;

   // Remaining capacity of cache
   private int capacity;

   // Constructor to initialize cache capacity
   public LRUCache(int cap) {
      capacity = cap;
      dll      = new LinkedList<>();
      map      = new HashMap<>();
   }

   // Node class to store key-value pair with order
   private class Node {
      int value;

      Node(int value) {
         this.value = value;
      }
   }

   // Move a key to the front (most recently used)
   private void makeRecentlyUsed(int key) {
      dll.remove(Integer.valueOf(key));
      dll.addFirst(key);
   }

   // Retrieve value for a given key
   public int get(int key) {
      if (!map.containsKey(key)) {
         return -1;
      }

      makeRecentlyUsed(key);
      return map.get(key).value;
   }

   // Store or update key-value pair
   public void put(int key, int value) {
      if (map.containsKey(key)) {
         map.get(key).value = value;
         makeRecentlyUsed(key);
      } else {
         if (map.size() >= capacity) {
            int lru = dll.removeLast();
            map.remove(lru);
         }

         dll.addFirst(key);
         map.put(key, new Node(value));
      }
   }
}
