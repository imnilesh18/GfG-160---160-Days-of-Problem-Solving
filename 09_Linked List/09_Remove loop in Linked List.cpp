/*
 * Remove loop in Linked List
 *
 * Given the head of a linked list that may contain a loop.  A loop means that the last node of the linked list is connected back to a node in the same list. The task is to remove the loop from the linked list (if it exists).
 *
 * Custom Input format:
 *
 * A head of a singly linked list and a pos (1-based index) which denotes the position of the node to which the last node points to. If pos = 0, it means the last node points to null, indicating there is no loop.
 *
 * The generated output will be true if there is no loop in list and other nodes in the list remain unchanged, otherwise, false.
 *
 * Examples:
 *
 * Input: head = 1 -> 3 -> 4, pos = 2
 * Output: true
 * Explanation: The linked list looks like
 * A loop is present in the list, and it is removed.
 *
 * Input: head = 1 -> 8 -> 3 -> 4, pos = 0
 * Output: true
 * Explanation:
 * The Linked list does not contains any loop.
 *
 * Input: head = 1 -> 2 -> 3 -> 4, pos = 1
 * Output: true
 * Explanation: The linked list looks like
 * A loop is present in the list, and it is removed.
 *
 * Constraints:
 * 1 ≤ size of linked list ≤ 10^5
 */

/************************************************************ C++ ************************************************/

// Approach: Floyd's Cycle Detection with two-pointer technique
// Time Complexity: O(n)
// Space Complexity: O(1)
class Solution {
public:
   // Function to remove a loop in the linked list.
   void removeLoop(Node* head) {
      // Handle edge case of empty or single node list
      if (!head || !head->next) {
         return;
      }

      // Floyd's Cycle Detection Algorithm: Use slow and fast pointers
      Node* slow = head;
      Node* fast = head;

      // Detect loop by moving pointers at different speeds
      while (fast != nullptr && fast->next != nullptr) {
         slow = slow->next;           // Move slow pointer one step
         fast = fast->next->next;     // Move fast pointer two steps

         // Loop found when slow and fast meet
         if (slow == fast) {
            slow = head;     // Reset slow to head

            // Special case: Loop starts at head
            if (slow == fast) {
               // Find last node of the loop
               while (fast->next != slow) {
                  fast = fast->next;
               }
            } else {
               // Find start of the loop
               while (fast->next != slow->next) {
                  slow = slow->next;
                  fast = fast->next;
               }
            }

            // Break the loop by setting last node's next to nullptr
            fast->next = nullptr;
            break;
         }
      }
   }
};

/************************************************************ JAVA ************************************************/

// Approach: Floyd's Cycle Detection with two-pointer technique
// Time Complexity: O(n)
// Space Complexity: O(1)
class Solution {
   // Function to remove a loop in the linked list.
   public static void removeLoop(Node head) {
      // Handle edge case of empty or single node list
      if (head == null || head.next == null) {
         return;
      }

      Node slow = head;
      Node fast = head;

      // Detect loop
      while (fast != null && fast.next != null) {
         slow = slow.next;
         fast = fast.next.next;

         // Loop found when slow and fast meet
         if (slow == fast) {
            slow = head;

            // Special case: Loop starts at head
            if (slow == fast) {
               // Find last node of the loop
               while (fast.next != slow) {
                  fast = fast.next;
               }
            } else {
               // Find start of the loop
               while (fast.next != slow.next) {
                  slow = slow.next;
                  fast = fast.next;
               }
            }

            // Break the loop by setting last node's next to null
            fast.next = null;
            break;
         }
      }
   }
}
