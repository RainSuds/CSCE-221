// Singly and doubly linked list data structures.
// (a) Write C++ functions for linked lists: insert a new node, delete a node, copy and move con-
// structor, copy and move assignment operator, destructor, search for a given item, get the
// number of items in a list.
// (b) Provide running times using big-O notation for the operations listed in (a).

#include <iostream>

class Node {
    public:
        int val;
        Node* next;

        Node(int data) : val(data), next(nullptr){}
};

class SinglyLinkedList {
    private:
        Node* head;
        Node* tail;

    public:
        SinglyLinkedList() : head(nullptr), tail(nullptr) {}; 
        SinglyLinkedList(const SinglyLinkedList& other) : head(nullptr), tail(nullptr) {
            Node* current = other.head;
            while (current != nullptr) {
                insert(current, current->val);
                current = current->next;
            }
        }
        SinglyLinkedList(SinglyLinkedList&& other) noexcept : head(nullptr), tail(nullptr) {
            head = other.head;
            tail = other.tail;
            other.head = nullptr;
            other.tail = nullptr;
        }
        ~SinglyLinkedList() {
            clear();
        }
        SinglyLinkedList& operator=(SinglyLinkedList&& other) noexcept {
            if (this != &other) {
                clear();
                head = other.head;
                tail = other.tail;
                other.head = nullptr;
                other.tail = nullptr;
            }
            return *this;
        }

        Node* insert(Node* pos, int val) {
            Node* newNode = new Node(val);

            if (pos == nullptr) {
                head = pos;
                tail = pos;
            }
            else if (pos == head) {
                newNode->next = head;
                head = newNode;
            }
            else if (pos == tail) {
                tail->next = newNode;
                tail = newNode;
            }
            else {
                newNode->next = pos->next;
                pos->next = newNode;
            }
            return newNode;
        }
        void erase(Node* nodeToDelete) {

            if (nodeToDelete == nullptr) {
                return;
            }

            if (nodeToDelete == head) {
                head = head->next;
                if (head == nullptr) {
                    tail = nullptr;
                }
                delete nodeToDelete;
                return;
            }
            Node* current = head;
            while (current != nullptr && current->next != nodeToDelete) {
                current = current->next;
            }
            if (current == nullptr) {
                return;
            }
            else if (nodeToDelete == tail) {
                tail = current;
            }
            current->next = nodeToDelete->next;
            delete nodeToDelete;
        }
        Node* search(int num) {
            Node* current = head;

            while (current != nullptr) {
                if (current->val == num) {
                    return current;
                }
                current = current->next;
            }
            return nullptr;
        }
        int size() {
            Node* current = head;
            int total = 0;

            while (current != nullptr) {
                total++;
                current = current->next;
            }
            return total;
        }


        void clear() {
            Node* current = head;
            while (current != nullptr) {
                Node* temp = current;
                current = current->next;
                delete temp;
            }
            head = nullptr;
            tail = nullptr;
        }
        bool empty() {
            if (head == tail) {
                return true;
            }
            return false;
        }
};