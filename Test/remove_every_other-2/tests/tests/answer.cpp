#include "executable.h"
#include <vector>

TEST(answer) {
    Typegen t;

    for (size_t i = 0; i < 20; i++) {
        // Use a vector for getting the list data discreetly
        std::vector<int> v;

        size_t size = t.range<size_t>(0, 30);

        // Generate a linked list
        ListNode* reference_head = buildLinkedList(size, t, &v);
        removeEveryOther_Vector(v);
        
        // Get a list with every other element removed
        ListNode* removed_head = removeEveryOther(reference_head);

        // Verify the list has every other element
        ASSERT_CORRECT_LIST(removed_head, v);

        // Cleanup
        clearList(removed_head);
    }
}
