#pragma once

#include "Graph.h"
#include "assertions.h"

std::ostream & _print_visit(
    std::ostream & o,
    const std::list<size_t> visit_order
) {
    o << "  Actual visit order: ";

    for (const size_t& v: visit_order) {
        o << v << " ";
    }

    return o;
}

std::ostream & _assert_traversal(
    std::ostream & o,
    const std::list<size_t>& visit_order,
    const size_t min_visit,
    const bool repeated_visits
) {

    if (visit_order.size() < min_visit) {
        return o << "Not enough vertices were marked as visited!" << std::endl
                 << "  Min required visits: " << min_visit << std::endl 
                 << "        Actual visits: " << visit_order.size();
    }

    if (repeated_visits) {
        o << "Visited the same vertex more than once!" << std::endl;
        return _print_visit(o, visit_order);
    }

    return o;
}

std::ostream & _assert_cycle(
    std::ostream & o,
    const Graph& g,
    const bool cycle,
    const bool returned
) {

    if (cycle != returned) {
        o << "Incorrect function return" << std::endl;
        o << "  Expected: " << (cycle ? "true" : "false") << std::endl
          << "    Actual: " << (returned ? "true" : "false") << std::endl << std::endl;

        if (cycle) {
            o << "There is supposed to be a cycle!" << std::endl;
        } else {
            o << "There is not a cycle!" << std::endl;
        }

        o << "This is the graph:" << std::endl;

        for (size_t i = 0; i < g.num_vertices(); i++) {
            o << "\t";
            const std::list<size_t> a = g.adj_list(i);
            auto itr = a.begin();

            o << i << ": ";

            if (itr != a.end()) {
                o << *(itr++);
            }

            while (itr != a.end()) {
                o << "->" << *(itr++);
            }

            o << std::endl;
        }
    }

    return o;
}

#define ASSERT_TRAVERSAL(visit_order, min_visit, repeated_visits) \
    MK_ASSERT(_assert_traversal, visit_order, min_visit, repeated_visits)

#define ASSERT_CYCLE(graph, cycle, returned) \
    MK_ASSERT(_assert_cycle, graph, cycle, returned)
