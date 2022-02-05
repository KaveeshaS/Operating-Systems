#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <sys/shm.h>

int main() {
    
    const char *memName = "Calculated_Data";
    const int SIZE = 4096;
    void *ptr;
    int shm_fd;

    shm_fd = shm_open(memName, O_RDONLY, 0666);
    if(shm_fd == -1) {
        exit(-1);
    }
    
    ptr = mmap(0, SIZE, PROT_READ, MAP_SHARED,  shm_fd, 0);
    if(ptr == MAP_FAILED) {
        exit(-1);
    }
    
    printf("Temperatures in Fahrenheit: \n");
    printf("%s\n", (char*)ptr);
    
    if(shm_unlink(memName) == -1) {
        exit(-1);
    }
    
    return 0;
}