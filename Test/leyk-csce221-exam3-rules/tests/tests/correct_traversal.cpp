#include "executable.h"

TEST(correct_traversal) {
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

        Monitor m;
        isValidDatabase(g1);
        ASSERT_TRAVERSAL(m.visit_order(), 7, m.repeated_visits());
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

        Monitor m;
        isValidDatabase(g2);
        ASSERT_TRAVERSAL(m.visit_order(), 3, m.repeated_visits());
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

        Monitor m;
        isValidDatabase(g3);
        ASSERT_TRAVERSAL(m.visit_order(), 3, m.repeated_visits());
    }

    {
        // Fourth graph
        Graph g4 = {
            {},     // 0: empty
            {2, 5}, // 1: 2->5
            {6},    // 2: 6
            {0, 4}, // 3: 0->4
            {0},    // 4: 0
            {2},    // 5: 2
            {}      // 6: empty
        };

        Monitor m;
        isValidDatabase(g4);
        ASSERT_TRAVERSAL(m.visit_order(), 7, m.repeated_visits());
    }

    {
        // Fifth graph
        Graph g5 = {
            {1, 2}, // 0: 1->2
            {3},    // 1: 3
            {1, 3}, // 2: 1->3
            {},     // 3: empty
            {5},    // 4: 5
            {3, 4}  // 5: 3->4
        };

        Monitor m;
        isValidDatabase(g5);
        ASSERT_TRAVERSAL(m.visit_order(), 2, m.repeated_visits());
    }

    {
        // Sixth graph
        Graph g6 = {
            {1, 2}, // 0: 1->2
            {3, 4}, // 1: 3->4
            {3},    // 2: 3
            {},     // 3: empty
            {3}     // 4: 3
        };

        Monitor m;
        isValidDatabase(g6);
        ASSERT_TRAVERSAL(m.visit_order(), 5, m.repeated_visits());
    }
}
