#include <malloc.h>
#include <stdio.h>
#include <string.h>
struct qsfp_isr {
    unsigned int pr_isr;
    unsigned int exp_mask;
};
struct qsfp_dt {
    int max_qsfp;
    struct qsfp_isr *isr;
};
struct qsfp_isr isr1[3] = { {0x280, 0xFFFF0000},{0x284, 0xFFFF}, {0x0, 0x0}};
struct qsfp_dt qsfp = {
    12, isr1
};

