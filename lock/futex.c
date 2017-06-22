#include "futex.h"

struct test_shared {
    int loops;
    futex_t futex;
};

