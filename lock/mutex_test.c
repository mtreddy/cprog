#include "mutex_test.h"

int main(void)
{
    int i = 10;
    lock_init(map);
    while(i--) {
        test_lock(map);
        sleep(3);
        test_unlock(map);
    }
}
