#include <stdio.h>
 #include <string.h>
 #include <stdlib.h>
 #include <unistd.h>             
 #include <sys/file.h>           
 #include <sys/mman.h>          
 #include <sys/wait.h>

 void errorAndExit(const char *msg)
 {
     perror(msg);
     exit(EXIT_FAILURE);
 }

 int main(int argc, char *argv[])
 {
      /* shm_open recommends using a leading '/' in
      the region name for portability, but Linux
      doesn't require it. */

      const char *memname = "/myMkfifo.txt";

      // Use one page for this example

      const size_t region_size = sysconf(_SC_PAGE_SIZE);

     /* Create the shared memory region.
      Notice the args are identical to open(2).*/

     int fd = shm_open(memname, O_CREAT | O_TRUNC | O_RDWR, 0666);
     if (fd == -1)
         errorAndExit("shm_open");

    /* Allocate some memory in the region. We use ftruncate, but
     write(2) would work just as well. */

     int r = ftruncate(fd, region_size);
     if (r != 0)
         errorAndExit("ftruncate");

    // Map the region into memory.

     void *ptr =
         mmap(0, region_size, PROT_READ | PROT_WRITE, MAP_SHARED, fd,
              0);
     if (ptr == MAP_FAILED)
         errorAndExit("mmap");

     // Don't need the fd after the mmmap call.

     close(fd);
     pid_t pid = fork();

     if (pid == 0)   // son
     {
         // Child process inherits the shared memory mapping.

         u_long *d = (u_long *) ptr;
         *d = 200;
         printf("I'm the child process and I wrote: %#lx\n", *(u_long *) d);
         exit(0);
     }


     else    
     {   /* child
          Synchronize with the child process. */

         int status;
         waitpid(pid, &status, 0);

         // Parent process sees the same memory.

         printf("I'm the father process , and my child wrote: %#lx\n", *(u_long *) ptr);

     }

     // errorAndExit with the memory, umap it.

     r = munmap(ptr, region_size);
     if (r != 0)
         errorAndExit("munmap");

     // Remove the shared memory region.

     r = shm_unlink(memname);
     if (r != 0)
         errorAndExit("shm_unlink");

    return 0;
}
