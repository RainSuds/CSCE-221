#include "executable.h"
#include <vector>
#include "Vector_logic.h"
using namespace std;

TEST(answer) {
    Typegen t;

    size_t cities_sz = 25;
    string* airports = new string[cities_sz]{"ABI","AMA","AUS","BPT","BRO","CLL","CRP","DAL","DFW","DRT","ELP","HRL","IAH","HOU","GRK","LRD","GGG","LBB","MAF","SJT","SAT","TYR","ACT","SPS"};

    for (size_t test_iter = 0; test_iter < 20; test_iter++) {

        size_t arr_size = t.range<size_t>(1,100);

        string target_Airport = airports[t.range<size_t>(0,cities_sz-1)];
        
        Flight* arr = new Flight[arr_size];
        int flow = fill_array_Flight_and_get_flow(arr,arr_size,airports,cities_sz,target_Airport);

        int student_flow = findAirportNetFlow(Pointer<Flight>(arr),arr_size,target_Airport);

        ASSERT_EQ(flow,student_flow);

        delete[] arr;
    }

    // cleanup
    delete[] airports;
}
