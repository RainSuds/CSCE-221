// Graph.h
#ifndef GRAPH_H
#define GRAPH_H

#include <vector>
#include <list>

class Graph {
    int V; // Number of vertices
    bool isDirected; // Flag to check if the graph is directed
    std::vector<std::list<int>> adj; // Adjacency list representation

public:
    // Constructor, initializes the graph with V vertices and optional directed flag
    Graph(int V, bool isDirected = false) : V(V), isDirected(isDirected), adj(V) {}

    // Function to add an edge from vertex v to vertex w
    void addEdge(int v, int w) {
        adj[v].push_back(w);
        if (!isDirected) {
            adj[w].push_back(v); // If the graph is undirected, add an edge back
        }
    }

    // Getter for the number of vertices
    int getV() const { return V; }

    // Getter for the adjacency list of a vertex
    const std::list<int>& getAdj(int v) const { return adj[v]; }

    // Function to check if the graph is directed
    bool isGraphDirected() const { return isDirected; }
};

#endif // GRAPH_H
