/*
 * Rotate a Linked List
 *
 * Given the head of a singly linked list, your task is to left rotate the linked list k times.
 *
 * Examples:
 *
 * Input: head = 10 -> 20 -> 30 -> 40 -> 50, k = 4
 * Output: 50 -> 10 -> 20 -> 30 -> 40
 * Explanation:
 * Rotate 1: 20 -> 30 -> 40 -> 50 -> 10
 * Rotate 2: 30 -> 40 -> 50 -> 10 -> 20
 * Rotate 3: 40 -> 50 -> 10 -> 20 -> 30
 * Rotate 4: 50 -> 10 -> 20 -> 30 -> 40
 *
 * Input: head = 10 -> 20 -> 30 -> 40 , k = 6
 * Output: 30 -> 40 -> 10 -> 20
 *
 * Constraints:
 * 1 <= number of nodes <= 10^5
 * 0 <= k <= 10^9
 * 0 <= data of node <= 10^9
 */

/************************************************************ C++ ************************************************/

// Approach: Find length, make list circular, find kth node, break link and update head
// TC: O(N) where N is the number of nodes in linked list
// SC: O(1) as we are using only pointer variables
class Solution {
public:
   Node* findNthNode(Node* temp, int k) {
      int cnt = 1;

      while (temp != nullptr) {
         if (cnt == k) {
            return temp;
         }
         cnt++;
         temp = temp->next;
      }
      return temp;
   }

   Node* rotate(Node* head, int k) {
      // Handle base cases - empty list or no rotation needed
      if (head == nullptr || k == 0) {
         return head;
      }

      // Calculate length and find tail node
      Node* tail = head;
      int   len  = 1;
      while (tail->next != nullptr) {
         tail = tail->next;
         len++;
      }

      // If k is multiple of length, list remains same
      if (k % len == 0) {
         return head;
      }

      // Normalize k to handle cases where k > length
      k = k % len;

      // Make list circular by connecting tail to head
      tail->next = head;

      // Find new last node (kth node from start)
      Node* newLastNode = findNthNode(head, k);

      // Update head to next of new last node
      head = newLastNode->next;
      // Break circular link
      newLastNode->next = nullptr;

      return head;
   }
};

/************************************************************ JAVA ************************************************/

// Approach: Find length, make list circular, find kth node, break link and update head
// TC: O(N) where N is the number of nodes in linked list
// SC: O(1) as we are using only pointer variables
class Solution {
   private Node findNthNode(Node temp, int k) {
      int cnt = 1;

      while (temp != null) {
         if (cnt == k) {
            return temp;
         }
         cnt++;
         temp = temp.next;
      }
      return temp;
   }

   public Node rotate(Node head, int k) {
      // Handle base cases - empty list or no rotation needed
      if (head == null || k == 0) {
         return head;
      }

      // Calculate length and find tail node
      Node tail = head;
      int  len  = 1;
      while (tail.next != null) {
         tail = tail.next;
         len++;
      }

      // If k is multiple of length, list remains same
      if (k % len == 0) {
         return head;
      }

      // Normalize k to handle cases where k > length
      k = k % len;

      // Make list circular by connecting tail to head
      tail.next = head;

      // Find new last node (kth node from start)
      Node newLastNode = findNthNode(head, k);

      // Update head to next of new last node
      head = newLastNode.next;
      // Break circular link
      newLastNode.next = null;

      return head;
   }
}
