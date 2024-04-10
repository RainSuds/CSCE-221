#include "executable.h"

TEST(answer_2) {
    {
        // First graph
        Graph g1 = {
            {1, 6}, // 0: 1->6
            {2, 6}, // 1: 2->6
            {3, 6}, // 2: 3->6
            {4, 6}, // 3: 4->6
            {5, 6}, // 4: 5->6
            {6},    // 5: 6
            {}      // 6: empty
        };

        bool ret = isValidDatabase(g1);
        ASSERT_CYCLE(g1, true, ret);
    }

    {
        // Second graph
        Graph g2 = {
            {1},       // 0: 1
            {2, 3, 6}, // 1: 2->3->6
            {3},       // 2: 3
            {4, 5},    // 3: 4->5
            {0, 2},    // 4: 0->2
            {},        // 5: empty
            {4}        // 6: 4

        };

        bool ret = isValidDatabase(g2);
        ASSERT_CYCLE(g2, false, ret);
    }

    {
        // Third graph
        Graph g3 = {
            {1, 2, 4, 5}, // 0: 1->2->4->5
            {},           // 1: empty
            {1},          // 2: 1
            {0, 2},       // 3: 0->2
            {2, 5},       // 4: 2->5
            {1, 3}        // 5: 1->3
        };

        bool ret = isValidDatabase(g3);
        ASSERT_CYCLE(g3, false, ret);
    }
}

