/*
 * Merge two sorted linked lists
 *
 * Given the head of two sorted linked lists consisting of nodes respectively. The task is to merge both lists and return the head of the sorted merged list.
 *
 * Examples:
 *
 * Input: head1 = 5 -> 10 -> 15 -> 40, head2 = 2 -> 3 -> 20
 * Output: 2 -> 3 -> 5 -> 10 -> 15 -> 20 -> 40
 *
 * Input: head1 = 1 -> 1, head2 = 2 -> 4
 * Output: 1 -> 1 -> 2 -> 4
 *
 * Constraints:
 * 1 <= no. of nodes<= 10^3
 * 0 <= node->data <= 10^5
 */

/************************************************************ C++ ************************************************/

// Approach: Create dummy node and merge lists by comparing each node, linking smaller nodes first and appending remaining nodes at the end.
// TC: O(N + M) where N and M are lengths of the input linked lists since we traverse each node exactly once.
// SC: O(1) since we only use a few pointers and don't create any extra nodes except one dummy node.
class Solution {
public:
   Node* sortedMerge(Node* head1, Node* head2) {
      // Create a dummy node to serve as the head of the merged list
      Node* dummyNode = new Node(-1);
      Node* temp      = dummyNode;

      // Traverse both lists simultaneously
      while (head1 != NULL && head2 != NULL) {
         // Compare elements of both lists and link the smaller node
         if (head1->data <= head2->data) {
            temp->next = head1;
            head1      = head1->next;
         } else {
            temp->next = head2;
            head2      = head2->next;
         }
         temp = temp->next;
      }

      // If any list still has remaining elements, append them
      if (head1 != NULL) {
         temp->next = head1;
      } else {
         temp->next = head2;
      }

      // Return the merged list starting from the next of dummy node
      return dummyNode->next;
   }
};

/************************************************************ JAVA ************************************************/

// Approach: Create dummy node and merge lists by comparing each node, linking smaller nodes first and appending remaining nodes at the end.
// TC: O(N + M) where N and M are lengths of the input linked lists since we traverse each node exactly once.
// SC: O(1) since we only use a few pointers and don't create any extra nodes except one dummy node.
class Solution {
   Node sortedMerge(Node head1, Node head2) {
      // Create a dummy node to serve as the head of merged list
      Node dummyNode = new Node(0);
      Node temp      = dummyNode;

      // Traverse both lists simultaneously
      while (head1 != null && head2 != null) {
         // Compare elements of both lists and link the smaller node
         if (head1.data <= head2.data) {
            temp.next = head1;
            head1     = head1.next;
         } else {
            temp.next = head2;
            head2     = head2.next;
         }
         temp = temp.next;
      }

      // If any list still has remaining elements, append them
      if (head1 != null) {
         temp.next = head1;
      } else {
         temp.next = head2;
      }

      // Return the merged list starting from the next of dummy node
      return dummyNode.next;
   }
}
