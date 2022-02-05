#include <stdio.h>
#include <sys/types.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>

int main() {
    
    char prog[50];
    int end = 1;
    
    while(end){
        
        printf("Enter Command: ");
        scanf("%s", prog);
        
        int pid = fork();
        
        if (!strcmp("End", prog)){
            end = 0; 
        } else if (pid == 0) {
            if(!strcmp("FN", prog)) {
                execve("./FN", NULL, NULL);
            } else if(!strcmp("SL", prog)) {
                execve("./SL", NULL, NULL);
            } else {
                printf("Invalid Input\n");
            }
        } else if (pid > 0) {
            wait(NULL);
        }
    }
    
    return 0;
}
