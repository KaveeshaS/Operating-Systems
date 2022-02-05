#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>

int a1, a2;

int b1 = 0, b2 = 0, b3 = 0, b4 = 0;

void sigHandler(int sig_num) {

    if (a1 > 0 && a2 > 0) {
        while(1){
            if(b1 == 100) {
                printf("\n%d : DONE\n", getpid());
                fflush(stdout);
                break;
            } else { 
                printf("\n%d : %d\n", getpid(), b1++);
                fflush(stdout);
            }
        }
    } else if (a1 == 0 && a2 > 0) {
        while(1) {
            if(b2 == 100) {
                printf("\n%d : DONE\n", getpid());
                fflush(stdout);
                break;
            } else {
                printf("\n%d : %d\n", getpid(), b2++);
                fflush(stdout);
            }
        }
    } else if (a1 > 0 && a2 == 0) {
        while(1) {
            if(b3 == 100) {
                printf("\n%d : DONE\n", getpid());
                fflush(stdout);
                break;
            } else {
                printf("\n%d : %d\n", getpid(), b3++);
                fflush(stdout);
            }
        }
    } else {
        while(1) {
            if(b4 == 100) {
                printf("\n%d : DONE\n", getpid());
                fflush(stdout);
                break;
            } else {
                printf("\n%d : %d\n", getpid(), b4++);
                fflush(stdout);
            }
        }
    }
    exit(sig_num); 
}

int main() {

    a1 = fork();
    a2 = fork();

    signal(SIGINT, sigHandler);

    while(1);

    return 0;
}