/*
 * Reverse a linked list
 *
 * Given the head of a linked list, the task is to reverse this list and return the reversed head.
 *
 * Examples:
 *
 * Input: head: 1 -> 2 -> 3 -> 4 -> NULL
 * Output: head: 4 -> 3 -> 2 -> 1 -> NULL
 * Explanation:
 *
 * Input: head: 2 -> 7 -> 10 -> 9 -> 8 -> NULL
 * Output: head: 8 -> 9 -> 10 -> 7 -> 2 -> NULL
 * Explanation:
 *
 * Input: head: 10 -> NULL
 * Output: 10 -> NULL
 * Explanation:
 *
 * Constraints:
 * 1 <= number of nodes, data of nodes <= 10^5
 */

/************************************************************ C++ ************************************************/

// Approach: Use recursion - recursively reach end of list, then rewire links backwards
// Time Complexity: O(n) where n is number of nodes as we traverse the list once
// Space Complexity: O(n) due to recursive call stack storing n function calls
class Solution {
public:
   Node* reverseList(struct Node* head) {
      if (head == nullptr || head->next == nullptr) {
         return head;     // Base case: return if list empty or has single node
      }

      Node* last = reverseList(head->next); // Recursively reach last node

      head->next->next = head;              // Point next node's next back to current node
      head->next       = nullptr;           // Set current node's next to null

      return last;                          // Return last node which becomes new head
   }
};

/************************************************************ JAVA ************************************************/

// Approach: Recursively reverse list by reaching end, then rewire links backwards one by one
// Time Complexity: O(n) since we traverse the full list once, where n is number of nodes
// Space Complexity: O(n) due to recursive call stack storing n recursive calls
class Solution {
   public Node reverseList(Node head) {
      // Base case: if list is empty or has single node, already "reversed"
      if (head == null || head.next == null) {
         return head;
      }

      // Recursively reverse rest of list and get new head node
      Node last = reverseList(head.next);

      // Current node's next node should point back to current node
      head.next.next = head;

      // Current node should point to null since it's now last node
      head.next = null;

      // Return new head of reversed list
      return last;
   }
}
