#include "mutex_test.h"
#define PROT_SEM 0x8
#if 0
#include "mutex/mutex.h"
struct futex
{
    int count;
}
struct crit {
    mutex test;
    int val;
};
struct crit crit;
int test_lock(void) 
{
    int ret = 0;
    ret = mutex_lock(&crit.test);
    if(ret < 0) {
        printf("Failed to get lock\n");
        return  ret;
    }

    crit.val += 1;
    printf("Got the lock val %d\n", crit.val);
    return ret;
}
int test_unlock(void)
{
    int ret = 0;
    ret = mutex_unlock(&crit.test);
    if(ret < 0) {
        printf("Failed to get unlock\n");
        return  ret;
    }
    printf("Unlocked\n");

}
#else
#include "usersem.h"
static init_done = 0;
#undef FILE_BASED
#define    FILE_BASED 1
void * shm_init(void);
void lock_init(void *map)
{
    if(init_done)
        return;
    printf("Initializing..!!\n");
#ifdef FILE_BASED
    test = test_init();
#else
    test = shm_init();
#endif
    futex_init(test);
    init_done  = 1;
}
void * test_init(void)
{
     void *map;
     int fd;
     fd = open("./tt", O_RDWR);
      if (fd < 0) {
          printf("opening file failed \n");
          exit(1);
      }
      map = mmap(NULL, 4096, PROT_READ|PROT_WRITE|PROT_SEM, MAP_SHARED, fd, 0);
      if (map == MAP_FAILED) {
          printf("mmap failed \n");
          exit(1);
      }

      if((futex_region(map, 4096)) != 0) {
          printf("futex region failed\n");
          exit(1);
      }
      return (map);

}
void * shm_init(void)
{
     void *tmap;
     int fd;
     int r;
    fd = shm_open("global-mutex", O_CREAT | O_RDWR, 0666);
      if (fd < 0) {
          printf("opening file failed \n");
          exit(1);
      }
      r = ftruncate(fd, 4096);
      if(r!=0) {
          printf("Ftruncate error");
          exit(1);
      }
      tmap = mmap(0, 4096, PROT_READ|PROT_WRITE, MAP_SHARED, fd, 0);
      if (map == MAP_FAILED) {
          printf("mmap failed \n");
          exit(1);
      }

      return (tmap);

}
int test_lock(void *map) 
{
    int ret = 0;
    if(test == NULL)
        test = map;
    printf("1  count = %i\n", test->count);
    ret = futex_down(test);
    if(ret < 0) {
        printf("Failed to get lock %d \n", ret);
        exit(1);
    }
    //*(volatile int *) (map + 4) = 0x73727170;

    printf("2 count = %i\n", test->count);
    printf("Got the lock  ret %d futex 0x%llx pid %d\n",  ret, test, getpid());
    return ret;
}
int test_unlock(void *map)
{
    int ret = 0;
    if(test == NULL)
        test = map;
    printf("1 count = %i\n", test->count);
    ret = futex_up(test);
    if(ret < 0) {
        printf("Failed to get unlock ret %d \n", ret);
        exit(ret);
    }
    printf("2 count = %i\n", test->count);
    printf("Unlocked %d ret\n", ret);

}
futex_wait
#endif
