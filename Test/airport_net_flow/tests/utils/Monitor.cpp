#include "Monitor.h"

#include <stdexcept>

#ifndef MAX_MONITORS
#define MAX_MONITORS 64
#endif

static Monitor* _live_monitors[MAX_MONITORS];
static size_t   n_monitors = 0;

// Helper for adding a monitor to list of active monitors
static void push_monitor(Monitor* m) {
    if (n_monitors >= MAX_MONITORS) {
        throw std::logic_error("Too many monitors");
    }

    _live_monitors[n_monitors++] = m;
}

// Helper for removing a monitor from list of active monitors
static void pop_monitor(Monitor* m) {
    if (_live_monitors[n_monitors - 1] == m) {
        _live_monitors[n_monitors--] = nullptr;
        return;
    }

    throw std::invalid_argument("Monitor allocated invalidly");
}

// Helpers for updating all live monitors
void Monitor::update_first() {
    for (size_t i = 0; i < n_monitors; i++) {
        _live_monitors[i]->first_access = true;
    }
}

void Monitor::update_second() {
    for (size_t i = 0; i < n_monitors; i++) {
        _live_monitors[i]->second_access = true;
    }
}

void Monitor::update_iterate() {
    for (size_t i = 0; i < n_monitors; i++) {
        ++(_live_monitors[i]->num_iterate);
    }
}

void Monitor::update_brackets() {
    for (size_t i = 0; i < n_monitors; i++) {
        _live_monitors[i]->used_brackets = true;
    }
}

Monitor::Monitor()
    : first_access(false)
    , second_access(false)
    , num_iterate(0)
    , used_brackets(false) 
{
    push_monitor(this);
}

Monitor::~Monitor() {
    pop_monitor(this);
}

bool Monitor::first() {
    return first_access;
}

bool Monitor::second() {
    return second_access;
}

size_t Monitor::iterations() {
    return num_iterate;
}

bool Monitor::brackets() {
    return used_brackets;
}
