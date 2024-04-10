#include "executable.h"
#include <unordered_set>

TEST(iterates) {
    Typegen t;

    for (size_t i = 0; i < 20; i++) {
        size_t size = t.range<size_t>(0, 30);

        // Generate a linked list
        ListNode* reference_head = buildLinkedList(size, t);

        // Create Monitor to observe program behavior
        Monitor m;

        // Get a list with every other element removed
        removeEveryOther(reference_head);

        // Check if the list was iterated through
        ASSERT_LE_(size, m.iterations(),
            "Make sure you are iterating through the linked list!"
        );

        // No cleanup to allow points even if the lists are improperly setup
    }

}
