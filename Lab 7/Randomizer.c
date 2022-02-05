#include <stdio.h>
#include <string.h>
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

int timer = 0;
int pts = 0;
int cnt = 1;

void tAlarm(int sig) {
    printf("\n >>Time passed: %d minutes, Time remianing %d Minutes.<<\n", cnt, (timer-cnt));
    
    fflush(stdout);
}

void endExam(int sig) {
    printf("\nTimes up, Thank you for taking the test.\n");
    printf("Total points earned = %i", pts);
    kill(getppid(), SIGINT);
    exit(0);
}
    
int main() {
    
    (void) signal(SIGALRM, tAlarm);
    
    char Q[900];
    char A[900];
    char corr[900];
    int cntPnt = 0;
    int n;

    int fd[2];
    pipe(fd);
 
    FILE *quesFile = fopen("Questions_Exam.txt", "r");
    FILE *ansFile = fopen("Answers_Exam.txt", "r");

    fscanf(quesFile, "%d", &timer);
    fscanf(quesFile, "%c", &n);
 
    pid_t pid0;
    pid0 = fork();

    if(pid0 == 0) {
       
        while(cnt <= timer) {
            sleep(1);
            kill(getpid(), SIGALRM);
            cnt++;
        }
 
        fclose(quesFile);
        fclose(ansFile);
        
        kill(getppid(), SIGINT);
        
        exit(0);
        
    } else if(pid0 != 0) {
        signal(SIGINT, endExam);
        printf("The total exam time is %i Minutes", timer);
 
        while (!feof(quesFile) || !feof(ansFile)) {

            fscanf(quesFile, "%[^\n]", &Q);
            printf("\n%s", Q);
 
            printf(" : ");
            scanf("%s", A);
            
            fscanf(ansFile, "%s %d", &corr, &cntPnt);

            if(strcmp(A, corr) == 0) {
                printf("corr Answer %s for %i points\n", corr, cntPnt);
                pts += cntPnt;
            } else {
                printf(" Wrong Answer. The correct answer is: %s", corr);
            }
            
            fscanf(quesFile, "%c", &n);

            close(fd[0]);

            write(fd[1], &pts, sizeof(int)+1);
            close(fd[1]);
        }
        
        printf("Total points earned =  %i \n", pts);
        
        kill(0, SIGINT);
    }
 
    exit(0);
}