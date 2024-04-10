#include "executable.h"

TEST(answer_1) {
    {
        // First graph
        Graph g1 = {
            {1, 2}, // 0: 1->2
            {3, 4}, // 1: 3->4
            {3},    // 2: 3
            {},     // 3: empty
            {3}     // 4: 3
        };

        bool ret = isValidDatabase(g1);
        ASSERT_CYCLE(g1, true, ret);
    }

    {
        // Second graph
        Graph g2 = {
            {1, 4}, // 0: 1->4
            {2},    // 1: 2
            {3, 4}, // 2: 3->4
            {1},    // 3: 1
            {5},    // 4: 5
            {3}     // 5: 3
        };

        bool ret = isValidDatabase(g2);
        ASSERT_CYCLE(g2, false, ret);
    }
}
