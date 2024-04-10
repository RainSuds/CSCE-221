#pragma once
#include <cstddef>
#include <stdexcept>

class Monitor {
    private:
        bool first_access;
        bool second_access;
        size_t num_iterate;
        bool used_brackets;

        static void update_first();
        static void update_second();
        static void update_iterate();
        static void update_brackets();

    public:
        Monitor();
        ~Monitor();

        bool first();
        bool second() ;
        size_t iterations();
        bool brackets();

        friend struct Flight;

        template <typename T>
        friend class Pointer;
};
