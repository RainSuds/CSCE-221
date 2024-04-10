#pragma once

#include "Monitor.h"
#include "typegen.h"
#include <vector>


class ListNode {
    private:
        // Notice, these are private and therefore can't be accessed outside the class
        int __val;
        ListNode* __next;

    public:
        // Constructor
        ListNode(int v = 0, ListNode* n = nullptr): __val(v), __next(n) {}

        // Get the integer value from a node
        int val() {
            return __val;
        }

        // Get the pointer to the next node in the list
        // Note: This returns a reference to the next pointer so it can be updated
        //    Ex) node->next() = nullptr; 
        ListNode*& next() {
            Monitor::update_next();
            return __next;
        }
};



////////////////////////////////////////////////////////////////////////////////
// THESE ARE USED FOR THE TEST CASES AND ARE NOT MEANT TO BE USED BY STUDENTS //
////////////////////////////////////////////////////////////////////////////////

// Utility function for creating randomized linked lists
ListNode* buildLinkedList(size_t size, Typegen& t, std::vector<int>* q = nullptr) {
    if (size == 0) {
        return nullptr;
    } else {
        int value = t.range<int>(0, 1000);

        if (q != nullptr) {
            q->push_back(value);
        }

        ListNode* head = new ListNode(value, buildLinkedList(size - 1, t, q));

        return head;
    }
}

// Utility funciton for clearing a list (cleanup)
void clearList(ListNode* head) {
    ListNode* toDelete = head;

    while (head != nullptr) {
        head = head->next();
        delete toDelete;
        toDelete = head;
    }
}
