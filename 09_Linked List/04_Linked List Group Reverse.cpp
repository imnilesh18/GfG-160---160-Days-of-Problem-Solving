/*
 * Linked List Group Reverse
 *
 * Given the head a linked list, the task is to reverse every k node in the linked list. If the number of nodes is not a multiple of k then the left-out nodes in the end, should be considered as a group and must be reversed.
 *
 * Examples:
 *
 * Input: head = 1 -> 2 -> 2 -> 4 -> 5 -> 6 -> 7 -> 8, k = 4
 * Output: 4 -> 2 -> 2 -> 1 -> 8 -> 7 -> 6 -> 5
 * Explanation: The first 4 elements 1, 2, 2, 4 are reversed first and then the next 4 elements 5, 6, 7, 8. Hence, the resultant linked list is 4 -> 2 -> 2 -> 1 -> 8 -> 7 -> 6 -> 5.
 *
 * Input: head = 1 -> 2 -> 3 -> 4 -> 5, k = 3
 * Output: 3 -> 2 -> 1 -> 5 -> 4
 * Explanation: The first 3 elements 1, 2, 3 are reversed first and then left out elements 4, 5 are reversed. Hence, the resultant linked list is 3 -> 2 -> 1 -> 5 -> 4.
 *
 * Constraints:
 * 1 <= size of linked list <= 10^5
 * 1 <= data of nodes <= 10^6
 * 1 <= k <= size of linked list
 */

/************************************************************ C++ ************************************************/

// Approach: Use recursion to reverse groups of k nodes at a time. For each group, reverse k nodes using three pointers (prev, curr, next),
// then recursively process the remaining list.
// Time Complexity: O(n) where n is the number of nodes in the linked list, as we visit each node exactly once
// Space Complexity: O(n/k) due to the recursive call stack, where n is the number of nodes and k is the group size
class Solution {
public:
   Node*reverseKGroup(Node* head, int k) {
      // Base case: if list is empty, return null
      if (!head) {
         return nullptr;
      }

      // Initialize pointers for reversing the list:
      // prev: points to the previous node in reversal
      // curr: points to the current node being processed
      // nextNode: stores the next node before breaking links
      Node* prev     = nullptr;
      Node* curr     = head;
      Node* nextNode = nullptr;

      // Counter to ensure we reverse exactly k nodes
      int count = 0;

      // Step 1: Reverse k nodes in the current group
      while (curr != nullptr && count < k) {
         // Store next node before we change current node's next pointer
         nextNode = curr->next;

         // Reverse the link: make current node point to previous node
         curr->next = prev;

         // Move prev and curr one step forward for next iteration
         prev = curr;
         curr = nextNode;

         // Keep track of how many nodes we've reversed
         count++;
      }

      // Step 2: After reversing current group:
      // 'head' is now the last node of reversed group
      // 'prev' is the new first node of reversed group
      // 'nextNode/curr' is the start of next group

      // Step 3: Recursively reverse next group of k nodes
      if (nextNode) {
         // The original 'head' is now at the end of its group,
         // so its next should point to the head of next reversed group
         head->next = reverseKGroup(nextNode, k);
      }

      // Step 4: Return the new head of the reversed group
      return prev;
   }
};

/************************************************************ JAVA ************************************************/

// Approach: Use recursion to reverse groups of k nodes at a time. For each group, reverse k nodes using three pointers (prev, curr, next),
// then recursively process the remaining list.
// Time Complexity: O(n) where n is the number of nodes in the linked list, as we visit each node exactly once
// Space Complexity: O(n/k) due to the recursive call stack, where n is the number of nodes and k is the group size
class Solution {
   public static Node reverseKGroup(Node head, int k) {
      // Base case: if list is empty, return null
      if (head == null) {
         return null;
      }

      // Initialize pointers for reversing the list:
      // prev: points to the previous node in reversal
      // curr: points to the current node being processed
      // nextNode: stores the next node before breaking links
      Node prev     = null;
      Node curr     = head;
      Node nextNode = null;

      // Counter to ensure we reverse exactly k nodes
      int count = 0;

      // Step 1: Reverse k nodes in the current group
      while (curr != null && count < k) {
         // Store next node before we change current node's next pointer
         nextNode = curr.next;

         // Reverse the link: make current node point to previous node
         curr.next = prev;

         // Move prev and curr one step forward for next iteration
         prev = curr;
         curr = nextNode;

         // Keep track of how many nodes we've reversed
         count++;
      }

      // Step 2: After reversing current group:
      // 'head' is now the last node of reversed group
      // 'prev' is the new first node of reversed group
      // 'nextNode/curr' is the start of next group

      // Step 3: Recursively reverse next group of k nodes
      if (nextNode != null) {
         // The original 'head' is now at the end of its group,
         // so its next should point to the head of next reversed group
         head.next = reverseKGroup(nextNode, k);
      }

      // Step 4: Return the new head of the reversed group
      return prev;
   }
}
