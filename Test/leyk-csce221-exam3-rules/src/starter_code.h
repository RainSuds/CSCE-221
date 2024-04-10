#pragma once

#include <iostream>
#include <queue> // For BFS
#include "Graph.h"

// Can be used if you want to use DFS
bool DFS_helper(const Graph& g, size_t vertex, VisitedSet& s) {
    /* TODO (for DFS only) */

    s.visit(vertex);

    for (auto v : g.adj_list(vertex)) { 
        if (!s.has_visited(v)) {
            DFS_helper(g, v, s);
        }
        if (s.has_visited(v) && !s.has_processed(v)) return false; // cycle
    }
    s.process(vertex);

    return true;
}
/*
    Write a function that takes in an unweighted directed graph representing a database and determines whether or not any
    circular dependencies (cycles) exist in the entire database.

    The Graph type is composed of a vector of lists. You may assume that Graph has the following
    functions:

    !!! DO NOT UNCOMMENT THIS CODE BELOW, IT IS ALREADY DEFINED ELSEWHERE AND THIS IS FOR EXPLAINING ONLY !!!
    class Graph {

        // Access the adjacency list for a given vertex (i.e. graph.adj_list(vertex) = {1->2})
        // NOTE: You can traverse this with some iterator, i.e. for (auto v : graph.adj_list(vertex)) or for
        // 
        std::list<size_t> adj_list(size_t vertex);

        // Get the number of vertices
        size_t num_vertices();

    };

    Traversal of the structures:
        Graph (std::vector<std::list<size_t>>):
            - Contain vertices 0 through num_vertices() - 1
            - This then means you can traverse from [0, g.num_vertices()) to access all vertices in the graph.
            - You could also use Graph::iterator and dereference the iterator to get the underlying vertex value.

        Adjacency lists (std::list<size_t>)):
        - Once accessed with graph.adj_list(vertex), you can iterate through a vertex's neighbors.
            - Iterate through them with a range-based for loop, i.e. for (auto neighbor : g.adj_list(vertex))
            - Or with iterators; i.e.) for (auto nei = g.adj_list(vertex).begin(); neighbor != g.adj_list(vertex).end(); ++it)

    There is also a VisitedSet for tracking visited vertices. You may assume that VisitedSet has the
    following functions:

    !!! DO NOT UNCOMMENT THIS CODE BELOW, IT IS ALREADY DEFINED ELSEWHERE AND THIS IS FOR EXPLAINING ONLY !!!
    class VisitedSet {

        // Mark a vertex as visited
        void visit(size_t vertex);

        // Mark a vertex as processed
        void process(size_t vertex);

        // Check if a vertex has been visited (processed is visited)
        bool has_visited(size_t vertex);

        // Check if a vertex has been processed
        bool has_processed(size_t vertex);

        // Clear the set
        void clear();
        
    };
    
    The set and graphs also have iterators, so you can use begin() and end()
    or range-based for loops to iterate through them. If you want to use the types,
    they are Graph::const_iterator, Graph::iterator and VisitedSet::iterator.

    NOTE: For more info, you can look at tests/include/Graph.h for the actual definitions
*/

/**
 * @brief Determine if the graph is a valid database.
 * 
 * This function takes in a graph, and returns true if the graph is a valid database (it contains no circular dependencies).
 * 
 * @param g The unweighted directed graph.
 * @return true If the graph contains no circular dependencies, false otherwise.
 * 
**/

bool isValidDatabase(const Graph& g) {
    // Set for tracking visited vertices
    VisitedSet s(g.num_vertices());

    // Uncomment if you want to use BFS
    // std::queue<int> q;

    // TODO: Implement Using BFS or DFS below
    for (size_t i = 0; i < g.num_vertices(); ++i) {
        if (!s.has_visited(i)) {
            if (!DFS_helper(g, i, s)) return false; // DFS_helper = false == cycle
        }
    }
    return true;
}