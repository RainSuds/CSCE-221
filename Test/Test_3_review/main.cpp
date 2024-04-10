#include "Graph.h"
#include <iostream>

// Forward declarations
void BFS(const Graph& g, int startVertex);
void DFS(const Graph& g, int startVertex);
bool find_cycle(const Graph& g);

int main() {
    Graph g(4);
    g.addEdge(0, 1);
    g.addEdge(0, 2);
    g.addEdge(1, 2);
    g.addEdge(2, 3);

    std::cout << "Breadth First Traversal (starting from vertex 0): \n";
    BFS(g, 0);

    std::cout << "\nDepth First Traversal (starting from vertex 0): \n";
    DFS(g, 0);

    std::cout << "\nChecking for cycle in the graph: \n";
    if (find_cycle(g)) {
        std::cout << "Cycle detected in the graph.\n";
    } else {
        std::cout << "No cycle detected in the graph.\n";
    }

    return 0;
}
