There are a couple things that should be discussed, but the most important thing is make commands.

Commands for running locally:
 make -C tests run-all           - Run all tests (stops when a test fails)
 make -C tests run-all -k        - Run all tests (runs all tests, even if some fail)
 make -C tests run/<test_name>   - Run a specific test_name
    * Replace <test_name> with the name of the test case in the tests/tests folder
      without the .cpp


For simplicity and your convenience, assume the following definition for Graph:

    class Graph {

        // Access the adjacency list for a given vertex
        std::list<size_t> adj_list(size_t vertex);

        // Get the number of vertices
        size_t num_vertices();
    
    };

For simplicity and your convenience, assume the following definition for VisitedSet:

    class VisitedSet {

        // Mark a vertex as visited
        void visit(size_t vertex);

        // Mark a vertex as processed
        void process(size_t vertex);

        // Check if a vertex has been visited (terminated is visited)
        bool has_visited(size_t vertex);

        // Check if a vertex has been processed
        bool has_processed(size_t vertex);

        // Clear the set
        void clear();

    };

The actual files have different definitions, but this is once again for giving partial credit for
correct program behavior. As such, certain features have been put into place so that you can use
Graph and VisitedSet as if they had the above definitions (Looking into the actual files will likely 
be more confusing then just using the above definition).
