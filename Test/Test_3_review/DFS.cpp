#include "Graph.h"
#include <iostream>
#include <vector>

void DFSUtil(const Graph& g, int v, std::vector<bool>& visited) {
    // Mark the current node as visited and print it
    visited[v] = true;
    std::cout << v << " ";

    // Recur for all the vertices adjacent to this vertex
    for (int i : g.getAdj(v)) {
        if (!visited[i]) {
            DFSUtil(g, i, visited);
        }
    }
}

void DFS(const Graph& g, int startVertex) {
    std::vector<bool> visited(g.getV(), false);

    // Call the recursive helper function to print DFS traversal
    DFSUtil(g, startVertex, visited);
}

bool findCycleUtil(const Graph& g, int v, std::vector<bool>& visited, int parent) {
    visited[v] = true;

    for (int adj : g.getAdj(v)) {
        if (!visited[adj]) {
            if (findCycleUtil(g, adj, visited, v))
                return true;
        } 
        else if (adj != parent) {
            // If an adjacent vertex is visited and is not the parent of the current vertex, then there is a cycle.
            return true;
        }
    }
    return false;
}

bool find_cycle(const Graph& g) {
    std::vector<bool> visited(g.getV(), false);

    for (int i = 0; i < g.getV(); i++) {
        if (!visited[i]) {
            if (findCycleUtil(g, i, visited, -1)) return true;
        }
    }
    return false;
}


/*
void DFS_helper(const Graph& g, size_t vertex, VisitedSet& s) {
        s.visit(vertex);

        // prompt (ex: print)
        std::cout << vertex << " ";

        std::list<size_t> adj = g.adj_list(vertex);

        // loop
        for (std::list<size_t>::iterator v : adj) {

            // tree edges
            if (!s.has_visited(*v)) {
                DFS_helper(g, *v, s);
            }
            // back egdes
            else if (!s.has_processed(*v)) { // 1->2->3 but 3->1 would be a back edge, if 3, 2, 1 all terminated, 1 is processed
                std::cout << "back edge" << endl;
            }
            // forward/cross edges
            else {
                std::cout << "forward/cross edge" << endl;
            }
        }

        s.process(vertex);

    }

void printDFS(const Graph& g, size_t start = 0, VisitedSet& s) {

    VisitedSet s(g.num_vertices());

    DFS_helper(g, start, s) // run dfs recursively

    for (size_t i = 0; i < g.num_vertices();i ++i) {
        if (!has_visited(i)) {
            DFS_helper(g, vertex, s);
        }
    }
}


// Efficiency of DFS:
// O(|V |2) if graph is represented using adjacency matrix
// O(|V | + |E|) if graph is represented using adjacency list

*/