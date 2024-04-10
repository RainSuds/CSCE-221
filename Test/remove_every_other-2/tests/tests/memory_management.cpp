#include "executable.h"

TEST(memory_management) {
    Typegen t;

    for (size_t i = 0; i < 20; i++) {
        size_t size = t.range<size_t>(0, 30);
        size_t rem = 2;
        size_t expected_removes = size / rem;
        // Generate a linked list
        ListNode* reference_head = buildLinkedList(size, t);

        {
            Memhook mh;

            // Get a list with every other node removed
            reference_head = removeEveryOther(reference_head);

            // Disable memhook so it does not pick up the debug stream allocations
            mh.disable();

            // check to make sure the number of nodes deleted is correct
            // should be size / 2
            
            ASSERT_EQ_(expected_removes,mh.n_frees(),
                "Did not delete the expected number of nodes"
            );

            // Check if the correct number of nodes were created
            ASSERT_EQ_(0ULL, mh.n_allocs(),
                "New nodes should not be created"
            );
        }

        // Cleanup
        {
            Memhook mh;

            clearList(reference_head);

            mh.disable();

            ASSERT_EQ_(size - expected_removes, mh.n_frees(),
                "The list is not linked properly. There should be \"size/2\" or \"size/2 + 1\" connected nodes. Make sure you are returning the head of the correct list"
            );
        }
    }
}
