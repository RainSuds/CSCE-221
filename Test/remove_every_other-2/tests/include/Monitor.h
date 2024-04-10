#pragma once

#include <cstddef>
#include <stdexcept>

class Monitor {
    private:
        size_t _num_next;

        static void update_next();

    public:
        Monitor();
        ~Monitor();

        size_t iterations();

        friend class ListNode;
};
