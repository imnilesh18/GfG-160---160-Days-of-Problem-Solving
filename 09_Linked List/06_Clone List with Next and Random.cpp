/*
Clone List with Next and Random

You are given a special linked list with n nodes where each node has two pointers a next pointer that points to the next node of the singly linked list, and a random pointer that points to the random node of the linked list.
Construct a copy of this linked list. The copy should consist of the same number of new nodes, where each new node has the value corresponding to its original node. Both the next and random pointer of the new nodes should point to new nodes in the copied list, such that it also represent the same list state. None of the pointers in the new list should point to nodes in the original list.
Return the head of the copied linked list.
NOTE : Original linked list should remain unchanged.

Examples:
Input: head = [[1, 3], [3, 3], [5, NULL], [9, 3]] 
Output: head = [[1, 3], [3, 3], [5, NULL], [9, 3]] 
Explanation: 
Node 1 points to Node 2 as its NEXT and Node 3 as its RANDOM.
Node 2 points to Node 3 as its NEXT and Node 3 as its RANDOM.
Node 3 points to Node 4 as its NEXT and NULL as its RANDOM.
Node 4 points to NULL as its NEXT and Node 3 as its RANDOM.

Input: head = [[1, 3], [2, 1], [3, 5], [4, 3], [5, 2]]
Output: head = [[1, 3], [2, 1], [3, 5], [4, 3], [5, 2]]
Explanation: 
Node 1 points to Node 2 as its NEXT and Node 3 as its RANDOM.
Node 2 points to Node 3 as its NEXT and Node 1 as its RANDOM.
Node 3 points to Node 4 as its NEXT and Node 5 as its RANDOM.
Node 4 points to Node 5 as its NEXT and Node 3 as its RANDOM.
Node 5 points to NULL as its NEXT and Node 2 as its RANDOM.

Input: head = [[7, NULL], [7, NULL]]
Output: head = [[7, NULL], [7, NULL]]
Explanation: 
Node 1 points to Node 2 as its NEXT and NULL as its RANDOM.
Node 2 points to NULL as its NEXT and NULL as its RANDOM.

Constraints:
1 <= n <= 100
0 <= node->data <= 1000
*/

/************************************************************ C++ ************************************************/

// Approach: Three-pass algorithm interweaving nodes, linking random pointers, and then separating cloned list.
// Time Complexity: O(n), traversing the list three times with constant operations.
// Space Complexity: O(1), modifying list in-place without using extra space beyond cloned nodes.
class Solution {
  public:
        Node* cloneLinkedList(Node* head) {
        // Handle empty list case
        if (head == NULL) {
            return NULL;
        }
        
        // Step 1: Create new nodes and interweave them with original list
        // This step creates a clone of each node and places it next to the original node
        Node* curr = head;
        while (curr != NULL) {
            // Create a new node with the same data as the current node
            Node* newNode = new Node(curr->data);
            
            // Link the new node between current node and its original next node
            newNode->next = curr->next;
            curr->next = newNode;
            
            // Move to the next original node
            curr = newNode->next;
        }
        
        // Step 2: Assign random pointers for cloned nodes
        // We use the fact that cloned nodes are right next to original nodes
        curr = head;
        while (curr != NULL) {
            // If original node has a random pointer, set cloned node's random pointer
            if (curr->random != NULL)
                curr->next->random = curr->random->next;
            
            // Move to next pair of original and cloned nodes
            curr = curr->next->next;
        }
        
        // Step 3: Separate the original and cloned lists
        curr = head;
        // First cloned node becomes the head of the new list
        Node* clonedHead = head->next;
        Node* clone = clonedHead;
        
        // Restore both original and cloned lists to their original structure
        while (clone->next != NULL) {
            // Reconnect original list's next pointers
            curr->next = curr->next->next;
            
            // Reconnect cloned list's next pointers
            clone->next = clone->next->next;
            
            // Move pointers forward
            curr = curr->next;
            clone = clone->next;
        }
        
        // Set the last nodes' next pointers to NULL
        curr->next = NULL;
        clone->next = NULL;
        
        // Return the head of the cloned list
        return clonedHead;
    }
};

/************************************************************ JAVA ************************************************/

// Approach: Three-pass algorithm interweaving nodes, linking random pointers, and then separating cloned list.
// Time Complexity: O(n), traversing the list three times with constant operations.
// Space Complexity: O(1), modifying list in-place without using extra space beyond cloned nodes.
class Solution {
    public Node cloneLinkedList(Node head) {
         if (head == null) {
            return null;
        }

        // Step 1: Create new nodes and insert them next to the original nodes
        Node curr = head;
        while (curr != null) {
            Node newNode = new Node(curr.data); // Create a new node with the same data
            newNode.next = curr.next; // Link new node to the next of current node
            curr.next = newNode; // Insert the new node next to the current node
            curr = newNode.next; // Move to the next original node
        }

        // Step 2: Set the random pointers of the new nodes
        curr = head;
        while (curr != null) {
            if (curr.random != null) {
                curr.next.random = curr.random.next; // Point the random of new node to the clone of the random node
            }
            curr = curr.next.next; // Move to the next original node
        }

        // Step 3: Separate the new nodes from the original nodes
        curr = head;
        Node clonedHead = head.next; // Save the head of the cloned list
        Node clone = clonedHead;
        while (clone.next != null) {
            curr.next = curr.next.next; // Restore the next pointer of the original list
            clone.next = clone.next.next; // Restore the next pointer of the cloned list
            curr = curr.next; // Move to the next original node
            clone = clone.next; // Move to the next cloned node
        }
        curr.next = null; // Terminate the original list
        clone.next = null; // Terminate the cloned list

        return clonedHead; 
    }
}