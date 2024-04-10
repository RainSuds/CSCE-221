#include "Graph.h"
#include <iostream>
#include <queue>

void BFS(const Graph& g, int startVertex) {
    int numVertices = g.getV();
    std::vector<bool> visited(numVertices, false);
    std::queue<int> queue;

    // Start BFS from the starting vertex
    visited[startVertex] = true;
    queue.push(startVertex);

    while (!queue.empty()) {
        int currentVertex = queue.front();
        queue.pop();
        std::cout << currentVertex << " ";

        // Iterate over all the adjacent vertices
        for (int adjVertex : g.getAdj(currentVertex)) {
            if (!visited[adjVertex]) {
                visited[adjVertex] = true;
                queue.push(adjVertex);
            }
        }
    }
    std::cout << std::endl;
}

int main() {
    // Create a graph using Graph class
    Graph g(4); // Graph with 4 vertices
    g.addEdge(0, 1);
    g.addEdge(0, 2);
    g.addEdge(1, 2);
    g.addEdge(2, 0);
    g.addEdge(2, 3);
    g.addEdge(3, 3);

    std::cout << "Breadth First Traversal (starting from vertex 0): \n";
    BFS(g, 0);

    return 0;
}

/*


void printBFS(const Graph g, size_t start = 0) {

    VisitedSet s(g.num_vertices());

    std::queue<size_t> q;
    q.push(start);

    while (!q.empty()) {
        size_t v = q.front();
        q.pop();

        if (s.has_visited(v)) {
            continue;
        }

        s.visit(v);

        // prompt (ex: print)
        std::cout << vertex << " ";

        std::list<size_t> adj = g.adj_list(v);

        // loop
        for (std::list<size_t>::iterator u : adj) {

            // tree edges
            if (!s.has_visited(u)) {
                q.push(u);
            }
        }
        s.process(u);
    }
}


*/