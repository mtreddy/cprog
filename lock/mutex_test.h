#include <linux/futex.h>
#include <stdio.h>
#include <stdint.h>
#include <limits.h>

#define _GNU_SOURCE
#include <unistd.h>
#include <sys/syscall.h>
#include <sys/time.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <fcntl.h>
#include <sys/mman.h>

#ifndef _MUTEX_TEST_H__
#define _MUTEX_TEST_H__
void *map;
struct futex *test;
void *test_init(void);
void lock_init(void *map);
int test_unlock(void *map) ;
int test_lock(void *map) ;
void *shm_init(void);
#endif
