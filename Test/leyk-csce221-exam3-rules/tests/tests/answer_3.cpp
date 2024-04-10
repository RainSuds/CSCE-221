#include "executable.h"

TEST(answer_3) {
    {
        // First graph
        Graph g1 = {
            {1, 2}, // 0: 1->2
            {3},    // 1: 3
            {1, 3}, // 2: 1->3
            {},     // 3: empty
            {5},    // 4: 5
            {3, 4}  // 5: 3->4
        };

        bool ret = isValidDatabase(g1);
        ASSERT_CYCLE(g1, false, ret);
    }

    {
        // Second graph
        Graph g2 = {
            {},     // 0: empty
            {2, 5}, // 1: 2->5
            {6},    // 2: 6
            {0, 4}, // 3: 0->4
            {0},    // 4: 0
            {2},    // 5: 2
            {}      // 6: empty
        };

        bool ret = isValidDatabase(g2);
        ASSERT_CYCLE(g2, true, ret);
    }
}
