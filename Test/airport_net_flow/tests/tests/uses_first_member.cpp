#include "executable.h"
#include "Vector_logic.h"

TEST(uses_first_member) {
    Typegen t;

    size_t cities_sz = 25;
    string* airports = new string[cities_sz]{"ABI","AMA","AUS","BPT","BRO","CLL","CRP","DAL","DFW","DRT","ELP","HRL","IAH","HOU","GRK","LRD","GGG","LBB","MAF","SJT","SAT","TYR","ACT","SPS"};

    for (int i = 0; i < 20; i++) {
        // Create Monitor to observe program behavior
        Monitor m;

        size_t arr_size = t.range<size_t>(1, 50);

        // Create new array

        Flight* arr = new Flight[arr_size+1];

        // Populate the array

        fill_array_Flight_and_get_flow(arr,arr_size,airports,cities_sz);

        // Call the function to test their accesses

        string target_city = airports[t.range<size_t>(0,cities_sz-1)];

        arr[arr_size] = Flight(100,target_city,airports[t.range<size_t>(0,cities_sz-1)]);

        findAirportNetFlow(Pointer<Flight>(arr),arr_size+1,target_city);

        // Check if the first (useful) data member was accessed
        ASSERT_EQ_(true, m.first(),
            "You didn't access the flights passenger count!"
        );

        ASSERT_EQ_(false, m.brackets(),
            "You shouldn't be using brackets!"
        );

        delete[] arr;
    }

    delete[] airports;
}
