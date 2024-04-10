#pragma once

#include <vector>
#include <utility>
#include <string>
#include "executable.h"

int fill_array_Flight_and_get_flow(Flight* arr, size_t sz, string* cities, size_t cities_sz,string target_airport=""){
    Typegen t;
    int ret = 0;
    for(size_t i = 0; i < sz; i++){
        size_t num_passengers = t.range<size_t>(1,500);
        size_t origin_index = t.range<size_t>(0,cities_sz);
        size_t dest_index = t.range<size_t>(0,cities_sz);
        while(dest_index == origin_index){
            dest_index = t.range<size_t>(0,cities_sz);
        }
        Flight f(num_passengers,cities[origin_index],cities[dest_index]);
        arr[i]=f;
        if(cities[dest_index] == target_airport)
            ret += num_passengers;    
        if(cities[origin_index] == target_airport)
            ret -= num_passengers;
    }
    return ret;
}

template<typename T>
vector<T>& array_to_vector(T* arr,size_t sz){
    vector<T> ret;
    for(size_t i = 0; i < sz; i++){
        ret.push_back(arr[i]);
    }
    return Pointer<T>(arr);
}