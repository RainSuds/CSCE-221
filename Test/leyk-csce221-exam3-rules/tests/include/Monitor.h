#pragma once

#include <list>

class Monitor {
    private:
        std::list<std::size_t> _visit_order;
        bool _repeated_visits;

        static void visit(std::size_t vertex);
        static void repeat_visit(std::size_t vertex);

    public:
        Monitor();
        ~Monitor();

        std::list<std::size_t> visit_order();
        bool repeated_visits();

        friend class VisitedSet;
};
