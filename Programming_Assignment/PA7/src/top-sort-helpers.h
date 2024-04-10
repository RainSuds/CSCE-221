#pragma once

#include <unordered_map>

#include "weighted-graph.hpp"
#include "graph-types.h"

template <typename T>
void computeIndegrees(const WeightedGraph<T>& graph, std::unordered_map<value_type<T>, int>& indegrees) {
    // TODO store the indegree for each vertex in the graph in the indegrees map

   if (graph.empty()) throw std::out_of_range("Graph is empty");

   for (const auto& vertex : graph) {
        indegrees[vertex.first] = 0;
   }
   for (const auto& vertex : graph) {
        for (const auto& edge : vertex.second) {
            indegrees[edge.first]++;
        }
   }
}
