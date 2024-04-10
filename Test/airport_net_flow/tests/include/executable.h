#pragma once

// COMMON HEADER FOR ISOLATED EXECUTABLE
// E.G. TESTS ISOLATED TO THEIR OWN TRANSLATION
// UNIT TO RELAX LINKAGE REQUIREMENTS

// Include utilities from utest
#include "utest.h"
// Track memory allocations
#include "memhook.h"
// Deterministic type generator
#include "typegen.h"
// Include source file
#include "starter_code.h"
// Include custom pointer wrapper class
#include "Pointer.h"
// Include custom assertions
#include "assertions.h"

#define TEST(name) UTEST(AIRPORT_NET_FLOW, name)

// Setup main file
UTEST_MAIN()
