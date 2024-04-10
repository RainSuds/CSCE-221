#ifndef FLIGHT_H
#define FLIGHT_H

#include <string>
#include "./Monitor.h"
using namespace std;

struct Flight {
    private:
        size_t num_passengers;
        string origin;
        string destination;
    
    public:
        Flight(): num_passengers(0), origin(""),destination(""){}
        explicit Flight(size_t passenger, string orig, string dest): num_passengers(passenger), origin(orig),destination(dest){}
        
        size_t getNumPassengers() {
            Monitor::update_first();
            return num_passengers;
        }
        
        string getOrigin() {
            Monitor::update_second();
            return origin;
        }
        
        string getDestination() {
            Monitor::update_second();
            return destination;
        }
};

#endif