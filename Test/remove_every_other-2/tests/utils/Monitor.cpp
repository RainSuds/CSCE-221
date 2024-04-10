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

void Monitor::update_next() {
    for (size_t i = 0; i < n_monitors; i++) {
        ++(_live_monitors[i]->_num_next);
    }
}

Monitor::Monitor(): _num_next(0) {
    push_monitor(this);
}

Monitor::~Monitor() {
    pop_monitor(this);
}

size_t Monitor::iterations() {
    return _num_next;
}