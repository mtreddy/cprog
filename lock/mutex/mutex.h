#include <errno.h>
#ifndef _MUTEX_H__
#define _MUTEX_H__
/* Compile Barrier */
#define barrier() asm volatile("": : :"memory")

/* Compare Exchange */
#define cmpxchg(P, O, N) __sync_val_compare_and_swap((P), (O), (N))

/* Atomic add, returning the new value after the addition */
#define atomic_add(P, V) __sync_add_and_fetch((P), (V))

/* Atomic set and clear a bit, given by position */
#define atomic_set_bit(P, V) __sync_or_and_fetch((P), 1<<(V))
#define atomic_clear_bit(P, V) __sync_and_and_fetch((P), ~(1<<(V)))

static inline void rep_nop(void)
{
        asm volatile("rep; nop" ::: "memory");
}
static inline void cpu_relax(void)
{
        rep_nop();
}
static inline unsigned xchg_8(void *ptr, unsigned char x)
{
    __asm__ __volatile__("xchgb %0,%1"
                :"=r" ((unsigned char) x)
                :"m" (*(volatile unsigned char *)ptr), "0" (x)
                :"memory");

    return x;
}
static inline void *xchg_32(void *ptr, unsigned int *x)
{
    __asm__ __volatile__("xchgq %0,%1"
                :"=r" ((unsigned int *) x)
                :"m" (*(volatile void **)ptr), "0" (x)
                :"memory");

    return x;
}
static inline void *xchg_64(void **ptr, void *x)
{
    __asm__ __volatile__("xchgq %0,%1"
                :"=r" ((void *) x)
                :"m" (*(volatile void **)ptr), "0" (x)
                :"memory");

    return x;
}
int sys_futex(void *addr1, int op, int val1, struct timespec *timeout, void *addr2, int val3)
{
        return syscall(SYS_futex, addr1, op, val1, timeout, addr2, val3);
}

typedef int mutex;

#define MUTEX_INITIALIZER {0}

int mutex_init(mutex *m, const void *a)
{
    (void)a;
    *m = 0;
    return 0;
}
int mutex_destroy(mutex *m)
{
    (void)m;
    return 0;
}

int mutex_lock(mutex *m)
{
    int i, c;
    
    /* Spin and try to take lock */
    for (i = 0; i < 100; i++)
    {
        c = cmpxchg(m, 0, 1);
        if (!c) return 0;
        
        cpu_relax();
    }

    /* The lock is now contended */
    if (c == 1) c = xchg_32(m, 2);

    while (c)
    {
        /* Wait in the kernel */
        sys_futex(m, FUTEX_WAIT_PRIVATE, 2, NULL, NULL, 0);
        c = xchg_32(m, 2);
    }
    
    return 0;
}

int mutex_unlock(mutex *m)
{
    int i;
    
    /* Unlock, and if not contended then exit. */
    if (*m == 2)
    {
        *m = 0;
    }
    else if (xchg_32(m, 0) == 1) return 0;

    /* Spin and hope someone takes the lock */
    for (i = 0; i < 200; i++)
    {
        if (*m)
        {
            /* Need to set to state 2 because there may be waiters */
            if (cmpxchg(m, 1, 2)) return 0;
        }
        cpu_relax();
    }
    
    /* We need to wake someone up */
    sys_futex(m, FUTEX_WAKE_PRIVATE, 1, NULL, NULL, 0);
    
    return 0;
}

int mutex_trylock(mutex *m)
{
    /* Try to take the lock, if is currently unlocked */
    unsigned c = cmpxchg(m, 0, 1);
    if (!c) return 0;
    return EBUSY;
}
#endif
