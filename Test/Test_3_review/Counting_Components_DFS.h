#include <iostream>
#include <vector>
using namespace std;

/*
Counting the number of connected components using DFS.
    > one component for each separate tree.
*/

class Graph {
    int V; // Number of vertices
    vector<int> *adj; // Pointer to an array containing adjacency lists

public:
    Graph(int V) {
        this->V = V;
        adj = new vector<int>[V];
    }

    void addEdge(int v, int w) {
        adj[v].push_back(w); // Add w to v’s list.
        adj[w].push_back(v); // Since the graph is undirected
    }

    // DFS utility function
    void DFSUtil(int v, vector<bool> &visited) {
        visited[v] = true; // Mark the current node as visited

        // Recur for all vertices adjacent to this vertex
        for(int i : adj[v]) {
            if(!visited[i])
                DFSUtil(i, visited);
        }
    }

    // Function to count the number of connected components
    int countConnectedComponents() {
        vector<bool> visited(V, false);
        int count = 0;

        for(int v = 0; v < V; v++) {
            if(!visited[v]) {
                DFSUtil(v, visited);
                count++;
            }
        }

        return count;
    }
};

int main() {
    // Create a graph given in the above diagram
    Graph g(5); // 5 vertices numbered from 0 to 4
    g.addEdge(0, 1);
    g.addEdge(1, 2);
    g.addEdge(3, 4);

    cout << "Number of connected components: " << g.countConnectedComponents();

    return 0;
}

/*
    Expected Output:
    "Number of connected components: 2"
    Actual Output:
    "Number of connected components: 2"
*/