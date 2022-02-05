#include <stdio.h>
#include <signal.h>
#include <stdlib.h>

unsigned int count = 0;

void sigHandler(int num) {

    printf("\nYou Stopped at: %d\n" , abs(count));
    printf("You were off by %d\n" , abs(1000000000 - count));
    exit(num);

}

int main() {

    printf("\nTry to hit 1 Billion!\n");
    signal(SIGINT, sigHandler);

    while(1) {
        count++;
    }
    
    return 0;
}

