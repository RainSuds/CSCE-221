#include <iostream>
#include <utility>
#include <string>
#include "Pointer.h"
#include "Flight.h"

// If you see red squiggles in the includes, don't worry
// As long as you can run in the terminal/Gradescope, everything is fine

using namespace std;

/*
    Assume the following struct definition for File (DO NOT UNCOMMENT):

    struct Flight {
        private:
            size_t num_passengers;
            string origin;
            string destination;
        
        public:
            size_t getNumPassengers() {
                return num_passengers;
            }
            string getOrigin() {
                return origin;
            }
            string getDestination() {
                return destination;
            }
    };

    Pointer wrapper class is for testing reasons only
    Can be used like any normal pointer, i.e. Pointer<Flight> is (almost) the same as Flight*

    Given an array of flights representing the flights coming into and out of a given target airport, 
    calculate and return the netflow for the flights for the given target airport.

    What is the netflow?
    The netflow is: total passengers coming into the target airport - total passengers coming out of the target airport
    You can determine if a flight is coming in or out of the airport by checking the origin and destination.
    If the flight's destination is the target airport, then it will be incoming.
    If the flight's origin is the target airport, then it will be outgoing.
    
    You may assume that
    the flight is always valid and that the array will always exist.

    You cannot use [] for accessing the elements of the array.
    You are given a pointer to an array of Flights, and the size of the array
*/

int findAirportNetFlow(Pointer<Flight> flights, size_t numFlights, string targetAirport) {
    /* TODO: WRITE YOUR CODE HERE */

    int num_arriving = 0;
    int num_departing = 0;
    int net_flow = 0;

    for (size_t i = 0; i < numFlights; i++) {
        Flight curr = *(flights + i);
        if (curr.getDestination() == targetAirport) {
            num_arriving += curr.getNumPassengers();
        }
        else if (curr.getOrigin() == targetAirport) {
            num_departing += curr.getNumPassengers();
        }
    }
    net_flow = num_arriving - num_departing;

    return net_flow;
}
