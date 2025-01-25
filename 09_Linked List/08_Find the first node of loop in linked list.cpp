/*
 * Find the first node of loop in linked list
 *
 * Given a head of the singly linked list. If a loop is present in the list then return the first node of the loop else return NULL.
 * Custom Input format:
 * A head of a singly linked list and a pos (1-based index) which denotes the position of the node to which the last node points to. If pos = 0, it means the last node points to null, indicating there is no loop.
 *
 * Examples:
 *
 * Input:
 * Output: 3
 * Explanation: We can see that there exists a loop in the given linked list and the first node of the loop is 3.
 *
 * Input:
 * Output: -1
 * Explanation: No loop exists in the above linked list.So the output is -1.
 *
 * Constraints:
 * 1 <= no. of nodes <= 10^6
 * 1 <= node->data <= 10^6
 */

/************************************************************ C++ ************************************************/

// Approach: Floyd's Cycle Detection Algorithm (Tortoise and Hare)
// Time Complexity: O(n), where n is the number of nodes in the linked list
// Space Complexity: O(1), using only two pointers regardless of list size
class Solution {
public:
   Node* findFirstNode(Node* head) {
      // Floyd's Cycle-Finding Algorithm (Tortoise and Hare)
      // Use two pointers: slow (moves 1 step) and fast (moves 2 steps)
      Node* slow = head;
      Node* fast = head;

      // Detect if a loop exists
      while (fast != nullptr && fast->next != nullptr) {
         slow = slow->next;           // Move slow pointer 1 step
         fast = fast->next->next;     // Move fast pointer 2 steps

         // If slow and fast meet, a loop exists
         if (slow == fast) {
            // Reset slow to head, keep fast at meeting point
            slow = head;

            // Move both pointers at same speed until they meet
            // Meeting point is the start of the loop
            while (slow != fast) {
               slow = slow->next;
               fast = fast->next;
            }
            return slow;      // First node of the loop
         }
      }

      // No loop found
      return nullptr;
   }
};

/************************************************************ JAVA ************************************************/

// Approach: Floyd's Cycle Detection Algorithm (Tortoise and Hare)
// Time Complexity: O(n), where n is the number of nodes in the linked list
// Space Complexity: O(1), using only two pointers regardless of list size
class Solution {
   public static Node findFirstNode(Node head) {
      // If list is empty or has only one node
      if (head == null || head.next == null) {
         return null;
      }

      // Floyd's Cycle Detection Algorithm
      Node slow = head;
      Node fast = head;

      // Detect loop
      while (fast != null && fast.next != null) {
         slow = slow.next;
         fast = fast.next.next;

         // If loop exists
         if (slow == fast) {
            // Reset slow to head
            slow = head;

            // Move both pointers at same speed
            while (slow != fast) {
               slow = slow.next;
               fast = fast.next;
            }

            // First node of the loop
            return slow;
         }
      }

      // No loop found
      return null;
   }
}
