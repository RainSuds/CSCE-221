#include <iostream>
#include <vector>
#include <list>
using namespace std;

/*
Whether a graph has a cycle or not, using the topological approach.
Directed Acyclic Graph only
*/

class Graph {
    int V; // Number of vertices
    list<int> *adj; // Adjacency list

public:
    Graph(int V) {
        this->V = V;
        adj = new list<int>[V];
    }

    void addEdge(int v, int w) {
        adj[v].push_back(w); // Add w to v’s list.
    }

    bool isCyclicUtil(int v, vector<bool> &visited, vector<bool> &recStack) {
        if(!visited[v]) {
            visited[v] = true;
            recStack[v] = true;

            // Recur for all the vertices adjacent to this vertex
            for(auto i = adj[v].begin(); i != adj[v].end(); ++i) {
                if (!visited[*i] && isCyclicUtil(*i, visited, recStack))
                    return true;
                else if (recStack[*i])
                    return true;
            }
        }
        recStack[v] = false; // remove the vertex from recursion stack
        return false;
    }

    bool isCyclic() {
        vector<bool> visited(V, false);
        vector<bool> recStack(V, false);

        for(int i = 0; i < V; i++)
            if (isCyclicUtil(i, visited, recStack))
                return true;

        return false;
    }
};

int main() {
    Graph g(4);
    g.addEdge(0, 1);
    g.addEdge(0, 2);
    g.addEdge(1, 2);
    g.addEdge(2, 0);
    g.addEdge(2, 3);
    g.addEdge(3, 3);

    if(g.isCyclic())
        cout << "Graph contains a cycle";
    else
        cout << "Graph doesn't contain a cycle";

    return 0;
}

/*
    Expected Output:
    "Graph contains a cycle"
    Actual Output:
    "Graph contains a cycle"
*/