#include <stdio.h>

#if 0
#define rdmsr(msr,val1,val2) \
         __asm__ __volatile__("rdmsr" \
                               : "=a" (val1), "=d" (val2) \
                               : "c" (msr))
#endif
#define DECLARE_ARGS(val, low, high)    unsigned low, high
#define EAX_EDX_VAL(val, low, high) ((low) | ((u64)(high) << 32))
#define EAX_EDX_ARGS(val, low, high)    "a" (low), "d" (high)
#define EAX_EDX_RET(val, low, high) "=a" (low), "=d" (high)

static inline unsigned long long native_read_msr(unsigned int msr)
{
    DECLARE_ARGS(val, low, high);

    asm volatile("rdmsr" : EAX_EDX_RET(val, low, high) : "c" (msr));
    return EAX_EDX_VAL(val, low, high);
}

static inline unsigned long long native_read_msr_safe(unsigned int msr,
                              int *err)
{
    DECLARE_ARGS(val, low, high);

    asm volatile("2: rdmsr ; xor %[err],%[err]\n"
             "1:\n\t"
             ".section .fixup,\"ax\"\n\t"
             "3:  mov %[fault],%[err] ; jmp 1b\n\t"
             ".previous\n\t"
             _ASM_EXTABLE(2b, 3b)
             : [err] "=r" (*err), EAX_EDX_RET(val, low, high)
             : "c" (msr), [fault] "i" (-EFAULT));
    return EAX_EDX_VAL(val, low, high);
}

#define rdmsr(msr, val1, val2)                  \
do {                                \
    u64 __val = native_read_msr((msr));         \
    (val1) = (u32)__val;                    \
    (val2) = (u32)(__val >> 32);                \
} while (0)


int main(void)
{
unsigned int low, high;
    rdmsr(0x19c, low, high);
    printf("CPUT temperature low  %d high %d\n", low, high);
}
