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

void Monitor::visit(size_t vertex) {
    for (size_t i = 0; i < n_monitors; i++) {
        (_live_monitors[i]->_visit_order).push_back(vertex);
    }
}

void Monitor::repeat_visit(size_t vertex) {
    for (size_t i = 0; i < n_monitors; i++) {
        (_live_monitors[i]->_repeated_visits) = true;
    }
}

Monitor::Monitor(): _visit_order(), _repeated_visits(false) {
    push_monitor(this);
}

Monitor::~Monitor() {
    pop_monitor(this);
}

std::list<size_t> Monitor::visit_order() {
    return _visit_order;
}

bool Monitor::repeated_visits() {
    return _repeated_visits;
}