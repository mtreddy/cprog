#include "mutex_test.h"
int main(void)
{
    int i = 5;
    lock_init(map);
    while(i--) {
        test_lock(map);
        sleep(5);
        test_unlock(map);
    }
}
