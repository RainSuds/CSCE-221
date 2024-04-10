#include "executable.h"
#include <unordered_set>
#include "Vector_logic.h"

TEST(iterates) {
    Typegen t;

    size_t cities_sz = 25;
    string* airports = new string[cities_sz]{"ABI","AMA","AUS","BPT","BRO","CLL","CRP","DAL","DFW","DRT","ELP","HRL","IAH","HOU","GRK","LRD","GGG","LBB","MAF","SJT","SAT","TYR","ACT","SPS"};

    for (size_t i = 0; i < 20; i++) {

        
        // Create Monitor to observe program behavior
        Monitor m;

        size_t size = t.range<size_t>(0, 50);

        // Generate an array

        Flight* arr = new Flight[size];
        fill_array_Flight_and_get_flow(arr,size,airports,cities_sz);

        // Insert value after every node in the list
        
        findAirportNetFlow(Pointer<Flight>(arr),size,airports[t.range<size_t>(0,cities_sz)]);

        // Check if the list was iterated through
        ASSERT_LE_(size, m.iterations(),
            "Make sure you are iterating through the entire array!"
        );


        // cleanup
        delete[] arr;
        
    }

    delete[] airports;

}
