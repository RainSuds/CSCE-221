#include "Graph.h"
#include <iostream>
#include <vector>
#include <climits>
#include <queue>

/*
The algorithm starts with an empty spanning tree. The idea is to maintain two sets of vertices. 
The first set contains the vertices already included in the MST, and the other set contains the vertices not yet included. 
At every step, it considers all the edges that connect the two sets and picks the minimum weight edge from these edges. 
After picking the edge, it moves the other endpoint of the edge to the set containing MST. 
*/

typedef std::pair<int, int> iPair;

void primMST(const Graph& g) {
    int V = g.getV();
    std::priority_queue<iPair, std::vector<iPair>, std::greater<iPair>> pq;

    int src = 0; // Taking vertex 0 as source

    std::vector<int> key(V, INT_MAX);
    std::vector<int> parent(V, -1);
    std::vector<bool> inMST(V, false);

    pq.push(std::make_pair(0, src));
    key[src] = 0;

    while (!pq.empty()) {
        int u = pq.top().second;
        pq.pop();

        inMST[u] = true;

        for (auto& x : g.getAdj(u)) {
            int v = x.first;
            int weight = x.second;

            if (inMST[v] == false && weight < key[v]) {
                key[v] = weight;
                pq.push(std::make_pair(key[v], v));
                parent[v] = u;
            }
        }
    }

    // Print edges of MST
    for (int i = 1; i < V; ++i)
        std::cout << parent[i] << " - " << i << std::endl;
}

// Define the Graph class with methods getV(), getAdj() as well as the necessary constructors

/*
Basic Implementation (without priority queue):
Time Complexity: (V^2)
O(V^2).
Similar to Dijkstra's, the basic implementation uses an adjacency matrix and scans all vertices to find the vertex with the minimum key value.

Implementation with Binary Heap (Min-Heap):
Time Complexity: ((V+E)log V)
O((V+E)logV).
Using a min-heap to keep track of the vertices not yet included in the MST allows more efficient finding and updating of the minimum weight edges.
*/