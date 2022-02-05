#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(){
    
    int raceid;
    
    int pid1 = fork();
    int pid2 = fork();

    int input;
    
    printf("Enter numbers for processes to race for >>>>")
    
    if(pid1 == 0 && pid2 == 0){
        raceid = 1;
    } else if(pid1 == 0 && pid2 > 0){
        raceid = 2;
    } else if(pid1 > 0 && pid2 == 0){
        raceid = 3;
    } else if(pid1 > 0 && pid2 > 0){
        raceid = 4;
    }
    
    printf("I am a process with pid %d and I am process number %d in the race.\n", getpid(), raceid);
    
    scanf("%d", &input);
    
    if(input == 1){
        printf("I am a process with pid %d and I am process number %d in the race and I am in %dst place\n", getpid(), raceid, input);
    } else if(input == 2){
        printf("I am a process with pid %d and I am process number %d in the race and I am in %dnd place\n", getpid(), raceid, input);
    } else if(input == 3){
        printf("I am a process with pid %d and I am process number %d in the race and I am in %drd place\n", getpid(), raceid, input);
    } else {
        printf("I am a process with pid %d and I am process number %d in the race and I am in %dth place\n", getpid(), raceid, input);
    }
    wait(NULL);
    wait(NULL);
    
    // scanf("%d", &input);
    // printf("I am a process with pid %d and I am process number %d in the race and I am in %dnd place\n", getpid(), raceid, input);
    
    // scanf("%d", &input);
    // printf("I am a process with pid %d and I am process number %d in the race and I am in %drd place\n", getpid(), raceid, input);
    
    // scanf("%d", &input);
    // printf("I am a process with pid %d and I am process number %d in the race and I am in %dth place\n", getpid(), raceid, input);
    
    return 0;
    
}