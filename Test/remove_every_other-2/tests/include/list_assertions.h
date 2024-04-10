#pragma once

#include "ListNode.h"
#include "assertions.h"
#include "utest.h"

enum colours { RESET, GREEN, RED, YELLOW };

// Make sure not to use color printing if not supported
const int use_colours = isatty(STDOUT_FILENO);
const char *colours[] = {"\033[0m", "\033[32m", "\033[31m", "\033[33m"};

std::ostream & _print_list(
    std::ostream & o,
    ListNode* head,
    std::vector<int> expected,
    size_t wrong_idx
) {
    o << "  Expected List: ";

    size_t curr_idx = 0;

    while (!expected.empty()) {
        if (curr_idx == wrong_idx && use_colours) {
            o << colours[RED];
        }

        if (expected.front() < 10) {
            o << " ";
        }
        if (expected.front() < 100) {
            o << " ";
        }
            
        o << expected.front();

        if (use_colours) {
            o << colours[RESET];
        }

        o << " ";

        curr_idx++;
        expected.erase(expected.begin());
    }

    o << std::endl;

    curr_idx = 0;

    o << "    Actual List: ";

    while (head != nullptr) {
        if (curr_idx == wrong_idx && use_colours) {
            o << colours[RED];
        }

        if (head->val() < 10) {
            o << " ";
        }
        if (head->val() < 100) {
            o << " ";
        }
            
        o << head->val();

        if (use_colours) {
            o << colours[RESET];
        }

        o << " ";

        curr_idx++;
        head = head->next();
    }

    return o << std::endl;
}

std::ostream & _assert_correct_list(
    std::ostream & o,
    ListNode* head,
    std::vector<int> expected
) {
    ListNode* original_head = head;
    std::vector<int> original_vector = expected;

    size_t count = 0;

    while (head != nullptr && !expected.empty()) {
        if (head->val() != expected.front()) {
            o << "Value Mismatch" << std::endl 
              << "  Expected: " << expected.front() << std::endl 
              << "    Actual: " << head->val() << std::endl << std::endl;
            return _print_list(o, original_head, original_vector, count);
        }

        head = head->next();
        expected.erase(expected.begin());
        ++count;
    }

    if (head != nullptr) {
        o << "Returned list has too many nodes" << std::endl
          << "  Expected Size: " << original_vector.size() << std::endl
          << "    Actual Size: " << count << std::endl << std::endl;
        return _print_list(o, original_head, original_vector, count);
    }

    if (!expected.empty()) {
        o << "Returned list has too few nodes" << std::endl
          << "  Expected Size: " << original_vector.size() << std::endl
          << "    Actual Size: " << count << std::endl << std::endl;
        return _print_list(o, original_head, original_vector, count);
    }

    return o;
}

#define ASSERT_CORRECT_LIST(list_head, expected_vector) \
    MK_ASSERT(_assert_correct_list, list_head, expected_vector)
