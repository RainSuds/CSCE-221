#include "Graph.h"
#include <iostream>
#include <vector>
#include <queue>
#include <climits>

// A utility function to find the vertex with minimum distance value, from the set of vertices not yet included in the shortest path tree
int minDistance(const std::vector<int>& dist, const std::vector<bool>& sptSet, int V) {
    int min = INT_MAX, min_index;

    for (int v = 0; v < V; v++)
        if (!sptSet[v] && dist[v] <= min)
            min = dist[v], min_index = v;

    return min_index;
}

// Function that implements Dijkstra's single source shortest path algorithm for a graph represented using adjacency matrix representation
void dijkstra(const Graph& graph, int src) {
    int V = graph.getV(); // Get the number of vertices in graph
    std::vector<int> dist(V); // dist values used to pick minimum weight edge in cut

    // sptSet[i] will be true if vertex i is included in shortest path tree or shortest distance from src to i is finalized
    std::vector<bool> sptSet(V, false);

    // Initialize all distances as INFINITE and stpSet[] as false
    for (int i = 0; i < V; i++)
        dist[i] = INT_MAX;

    // Distance of source vertex from itself is always 0
    dist[src] = 0;

    // Find shortest path for all vertices
    for (int count = 0; count < V - 1; count++) {
        // Pick the minimum distance vertex from the set of vertices not yet processed. u is always equal to src in the first iteration.
        int u = minDistance(dist, sptSet, V);

        // Mark the picked vertex as processed
        sptSet[u] = true;

        // Update dist value of the adjacent vertices of the picked vertex.
        for (int v = 0; v < V; v++)

            // Update dist[v] only if is not in sptSet, there is an edge from u to v, and total weight of path from src to v through u is smaller than current value of dist[v]
            if (!sptSet[v] && graph.isEdge(u, v) && dist[u] != INT_MAX && dist[u] + graph.edgeWeight(u, v) < dist[v])
                dist[v] = dist[u] + graph.edgeWeight(u, v);
    }

    // Print the constructed distance array
    std::cout << "Vertex \t Distance from Source\n";
    for (int i = 0; i < V; i++)
        std::cout << i << " \t\t" << dist[i] << std::endl;
}

// Define the Graph class with weighted edges, isEdge(), and edgeWeight() functions as needed.


/*
Basic Implementation (without priority queue):
Time Complexity: (V^2)
O(V^2), where V is the number of vertices.
This is the complexity when the graph is implemented using adjacency matrices and the algorithm simply scans all vertices to find the vertex with the minimum distance at each step.

Implementation with Binary Heap (Min-Heap):
Time Complexity: ((V+E)log V)
O((V+E)log V), where E is the number of edges.
In this implementation, a min-heap is used to efficiently find the next vertex to process. The heap operations (insert and extract-min) take O(logV) time.
*/