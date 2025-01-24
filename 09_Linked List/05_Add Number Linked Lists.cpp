/*
Add Number Linked Lists

Given the head of two singly linked lists num1 and num2 representing two non-negative integers. The task is to return the head of the linked list representing the sum of these two numbers.

For example, num1 represented by the linked list : 1 -> 9 -> 0, similarly num2 represented by the linked list: 2 -> 5. Sum of these two numbers is represented by 2 -> 1 -> 5.

Note: There can be leading zeros in the input lists, but there should not be any leading zeros in the output list.

Examples:

Input: num1 = 4 - > 5, num2 = 3 -> 4 -> 5
Output:  3 -> 9 -> 0
Explanation: Given numbers are 45 and 345. There sum is 390.

Input: num1 = 0 -> 0 -> 6 -> 3, num2 = 0 -> 7 
Output: 7 -> 0  
Explanation: Given numbers are 63 and 7. There sum is 70.
Constraints:
1 <= size of both linked lists <= 10^6
0 <= elements of both linked lists <= 9
*/

/************************************************************ C++ ************************************************/

// Approach: Pad shorter list with zeros, use recursion to reach rightmost nodes first, add digits from right to left while maintaining carry.
// TC: O(max(N1, N2)) where N1 and N2 are lengths of input lists as we traverse both lists once plus constant extra operations.
// SC: O(max(N1, N2)) due to recursion stack space plus potential padding space for the shorter list.
class Solution {
public:
    Node* addTwoLists(Node* first, Node* second) {
        // Get lengths of both lists
        int len1 = getLength(first);
        int len2 = getLength(second);
        
        // Pad shorter list with zeros
        if(len1 < len2) {
            first = padZeros(first, len2 - len1);
        } else if(len2 < len1) {
            second = padZeros(second, len1 - len2);
        }
        
        // Add lists recursively from right
        int carry = 0;
        Node* result = addListsRecursive(first, second, carry);
        
        // If carry remains, create new node
        if(carry > 0) {
            Node* newNode = new Node(carry);
            newNode->next = result;
            result = newNode;
        }
        
        // Remove leading zeros
        while(result != nullptr && result->next != nullptr && result->data == 0) {
            Node* temp = result;
            result = result->next;
            delete temp;
        }
        
        return result;
    }

private:
    int getLength(Node* head) {
        int len = 0;
        while(head != nullptr) {
            len++;
            head = head->next;
        }
        return len;
    }
    
    Node* padZeros(Node* head, int count) {
        while(count--) {
            Node* newNode = new Node(0);
            newNode->next = head;
            head = newNode;
        }
        return head;
    }
    
    Node* addListsRecursive(Node* first, Node* second, int& carry) {
        // Base case
        if(first == nullptr) return nullptr;
        
        // Recursively go to the rightmost digit
        Node* result = addListsRecursive(first->next, second->next, carry);
        
        // Add current digits and carry
        int sum = first->data + second->data + carry;
        carry = sum / 10;
        
        // Create new node with current sum
        Node* newNode = new Node(sum % 10);
        newNode->next = result;
        
        return newNode;
    }
};

/************************************************************ JAVA ************************************************/

// Approach: Pad shorter list with zeros, use recursion to reach rightmost nodes first, add digits from right to left while maintaining carry.
// TC: O(max(N1, N2)) where N1 and N2 are lengths of input lists as we traverse both lists once plus constant extra operations.
// SC: O(max(N1, N2)) due to recursion stack space plus potential padding space for the shorter list.
class Solution {
    static Node addTwoLists(Node num1, Node num2) {
        // Get lengths of both lists
        int len1 = getLength(num1);
        int len2 = getLength(num2);
        
        // Pad shorter list with zeros
        if(len1 < len2) {
            num1 = padZeros(num1, len2 - len1);
        } else if(len2 < len1) {
            num2 = padZeros(num2, len1 - len2);
        }
        
        IntWrapper carry = new IntWrapper(0);
        Node result = addListsRecursive(num1, num2, carry);
        
        // If carry remains, create new node
        if(carry.value > 0) {
            Node newNode = new Node(carry.value);
            newNode.next = result;
            result = newNode;
        }
        
        // Remove leading zeros
        while(result != null && result.next != null && result.data == 0) {
            result = result.next;
        }
        
        return result;
    }
    
    static private int getLength(Node head) {
        int len = 0;
        while(head != null) {
            len++;
            head = head.next;
        }
        return len;
    }
    
    static private Node padZeros(Node head, int count) {
        while(count-- > 0) {
            Node newNode = new Node(0);
            newNode.next = head;
            head = newNode;
        }
        return head;
    }
    
    static private Node addListsRecursive(Node first, Node second, IntWrapper carry) {
        // Base case
        if(first == null) return null;
        
        // Recursively go to the rightmost digit
        Node result = addListsRecursive(first.next, second.next, carry);
        
        // Add current digits and carry
        int sum = first.data + second.data + carry.value;
        carry.value = sum / 10;
        
        // Create new node with current sum
        Node newNode = new Node(sum % 10);
        newNode.next = result;
        
        return newNode;
    }
    
    // Helper class to handle carry as reference
    static private class IntWrapper {
        int value;
        IntWrapper(int value) {
            this.value = value;
        }
    }
}