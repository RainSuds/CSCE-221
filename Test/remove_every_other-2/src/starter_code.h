#pragma once

#include <iostream>
#include <utility>
#include "ListNode.h"

/*
    Write a function that takes in the head of a singly-linked list and removes every other element of the list,
    returning a pointer to the new head node. The first element removed should be the second element if it
    exists (i.e. remove odd "indices").

    No new lists or nodes should be created. The original list should be altered.
    Make sure that nodes are not lost (i.e. you cannot just rewire pointers, you must also deallocate the removed nodes)

    EXAMPLES:
        1) The input 1 -> 2 -> 3 -> 4 -> 5 -> 6 or 1 -> 2 -> 3 -> 4 -> 5
        should generate this output 1 -> 3 -> 5

        2) The input 1 -> 2 -> 3 or 1 -> 2 -> 3 -> 4
        should generate this output 1 -> 3

        3) The input 1 -> 2 or 1
        should generate this output 1

        4) An empty input {} should generate an empty output {}
    
    THIS FUNCTION SHOULD BE IMPLEMENTED ITERATIVELY!!!
    
    For the definition of ListNode, assume the following interface:

    struct ListNode {
        private:
            int __val;
            ListNode* __next;

        public:
            ListNode(int v = 0, ListNode* n = nullptr): __val(v), __next(n) {}

            int val() { return __val; }
            ListNode*& next() { return __next; }
    };

    NOTE: The data members are private, so you MUST use the public getter functions
    to access and manipulate the data in the nodes. Also, the return type for next()
    is a reference, meaning that the returned value is an alias for the __next data
    member.

    ex)
        ListNode* node;
        node->next() = ...

    This will work for changing the value of the __next data member, and can also be
    used for simply retrieving the value of __next.
*/

ListNode* removeEveryOther(ListNode* head) {
    bool erase = false;
    if (!head || !head->next()) {
        return head;
    }

    ListNode* current = head;
    ListNode* prev = nullptr;

    while (current != nullptr) {
        if (erase) {
            ListNode* temp = current;
            prev->next() = current->next();
            delete temp;
            prev = current;
            current = current->next();
            erase = false;
        }
        else {
            prev = current;
            current = current->next();
            erase = true;
        }
    }

    return head;
}
