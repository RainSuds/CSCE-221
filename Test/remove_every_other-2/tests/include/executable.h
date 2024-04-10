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
// Include linked list nodes
#include "ListNode.h"
// Include custom assertions
#include "assertions.h"
// Include list assertions
#include "list_assertions.h"
// Include test logic helpers
#include "list_logic.h"

#define TEST(name) UTEST(EVERY_OTHER, name)

// Setup main file
UTEST_MAIN()
