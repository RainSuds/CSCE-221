#include "hash_functions.h"

size_t polynomial_rolling_hash::operator() (std::string const & str) const {
    /* TODO */
    size_t hash = 0;
    long long p = 1;
    long long b = 19, m = 3298534883309ul;
    for (char ch : str) {
        hash += ch * p;
        p = (p * b) % m;
    }
    return hash;
}

size_t fnv1a_hash::operator() (std::string const & str) const {
    /* TODO */
    size_t hash = 0xCBF29CE484222325;
    long long p = 0x00000100000001B3;
    for (char ch : str) {
        hash = hash ^ ch;
        hash = hash * p;
    }

    return hash;
}
