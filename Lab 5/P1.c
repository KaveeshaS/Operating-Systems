#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <sys/types.h>

int main() {
    
    const int SIZE = 4096;
    const char *name = "OS";
    void *ptr;
    char input[100];
    int shm_fd;
    
    shm_fd = shm_open(name, O_CREAT | O_RDWR, 0666);
    
    ftruncate(shm_fd, SIZE);
     
    ptr = mmap(0, SIZE, PROT_WRITE, MAP_SHARED, shm_fd, 0);
    
    if (ptr == MAP_FAILED){
        printf("Map Failed\n");
        return -1;
    }
    
    while(1) {
        
        printf("Enter line to be added to the shared memory space: ");
        scanf("%s", input);
        
        if(!strcmp(input, "End") || !strcmp(input, "end"){
            strcat(input, " \n");
            sprintf(ptr, "%s", input);
            ptr += strlen(input);
            return 0;
        } else {
            strcat(input, " \n");
            sprintf(ptr, "%s", input);
            ptr += strlen(input);
        }
        
    }
    
    return 0;
    
}