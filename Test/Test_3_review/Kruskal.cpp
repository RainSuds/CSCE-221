#include "Graph.h"
#include <algorithm>
#include <iostream>
#include <vector>

// A structure to represent a weighted edge in the graph
struct Edge {
    int src, dest, weight;
};

// A structure to represent a connected, undirected and weighted graph
class GraphKruskal {
    int V, E;
    std::vector<Edge> edges;

public:
    GraphKruskal(int V, int E) : V(V), E(E) {}

    void addEdge(int src, int dest, int weight) {
        edges.push_back({src, dest, weight});
    }

    // Function to implement Kruskal's algorithm
    void KruskalMST();
};

// A class to represent a subset for union-find
class Subset {
public:
    int parent;
    int rank;
};

// A utility function to find set of an element i (uses path compression)
int find(Subset subsets[], int i) {
    if (subsets[i].parent != i)
        subsets[i].parent = find(subsets, subsets[i].parent);

    return subsets[i].parent;
}

// A function that does union of two sets of x and y (uses union by rank)
void Union(Subset subsets[], int x, int y) {
    int xroot = find(subsets, x);
    int yroot = find(subsets, y);

    if (subsets[xroot].rank < subsets[yroot].rank)
        subsets[xroot].parent = yroot;
    else if (subsets[xroot].rank > subsets[yroot].rank)
        subsets[yroot].parent = xroot;
    else {
        subsets[yroot].parent = xroot;
        subsets[xroot].rank++;
    }
}

// Compare two edges according to their weights.
bool myComp(const Edge& a, const Edge& b) {
    return a.weight < b.weight;
}

// The main function to construct MST using Kruskal's algorithm
void GraphKruskal::KruskalMST() {
    std::vector<Edge> result(V); // This will store the resultant MST
    int e = 0;  // An index variable, used for result[]
    int i = 0;  // An index variable, used for sorted edges

    // Step 1: Sort all the edges in non-decreasing order of their weight
    std::sort(edges.begin(), edges.end(), myComp);

    // Allocate memory for creating V subsets
    Subset *subsets = new Subset[V];

    // Create V subsets with single elements
    for (int v = 0; v < V; ++v) {
        subsets[v].parent = v;
        subsets[v].rank = 0;
    }

    while (e < V - 1 && i < E) {
        // Step 2: Pick the smallest edge. Increment the index for next iteration
        Edge next_edge = edges[i++];

        int x = find(subsets, next_edge.src);
        int y = find(subsets, next_edge.dest);

        // If including this edge doesn't cause a cycle, include it in the result and increment the index of result for next edge
        if (x != y) {
            result[e++] = next_edge;
            Union(subsets, x, y);
        }
    }

    // Print the contents of result[] to display the built MST
    std::cout << "Following are the edges in the constructed MST\n";
    for (i = 0; i < e; ++i)
        std::cout << result[i].src << " -- " << result[i].dest << " == " << result[i].weight << std::endl;

    delete[] subsets;
}

// Define the Graph class with methods getV(), getAdj() as well as the necessary constructors


/*
Basic Implementation:
Time Complexity: O(ElogE) or O(Elog V)
O(ElogV) since E can be at most V^2 and log ⁡V^2 is 2log V.
The dominating factor in this complexity is the sorting of the edges, which takes O(ElogE) time. 
The disjoint-set data structure operations (union and find) take O(logV) time per operation.

Optimized with Path Compression and Union by Rank:
Time Complexity: O(ElogV).
Using a disjoint-set data structure with path compression and union by rank, 
the time complexity of union and find operations can be reduced, 
making the overall complexity depend more heavily on the sorting step.
*/