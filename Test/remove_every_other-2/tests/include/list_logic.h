#pragma once

#include <vector>
#include <stack>
#include <utility>

void removeEveryOther_Vector(std::vector<int>& input_data) {
    std::vector<int> ret;
    for(size_t i = 0; i < input_data.size(); i += 2){
        ret.push_back(input_data[i]);
    }
    input_data = std::move(ret);
}