#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <pthread.h>

struct node {
    int PID;
    int t;
    struct node *next;
};

void printFCFS();
void printSJF();
void insertFirst(int PID, int t);
int nodeLength();
void sort();
void reverse(struct node** ref);
void *FCFSThread(void *x);
void *SJFThread(void *x);

struct node *head = NULL;
struct node *now = NULL;

int main(){
    
    pthread_t tFCFS;
    pthread_t tSJF;
    
    int PID, t;
    int res;
    
    while(1) {
        printf("Enter an ID and a value for a node to add to the list, Enter -1 to stop: ");
        scanf("%i" "%i", &PID, &t);
        if(PID == -1 && t == -1){
            break;
        } else {
            insertFirst(PID, t);
        }
    }
    
    res = pthread_create(&tFCFS, NULL, FCFSThread, NULL);
    if (res != 0) {
        exit(EXIT_FAILURE);
    }

    res = pthread_create(&tSJF, NULL, SJFThread, NULL);
    if (res != 0) {
        exit(EXIT_FAILURE);
    }
    
    res = pthread_join(tFCFS, NULL);
    if (res != 0) {
        perror("Thread join failed");
        exit(EXIT_FAILURE);
    }
    
    res = pthread_join(tSJF, NULL);
    if (res != 0) {
        perror("Thread join failed");
        exit(EXIT_FAILURE);
    }
    
}

void printFCFS() {
    
    struct node *ptr = head;

    while(ptr != NULL) {
       printf("Node ID %d with value %d \n", ptr -> PID, ptr -> t);
       ptr = ptr -> next;
    }
   
}

void printSJF() {
   
    struct node *ptr = head;
    while(ptr != NULL) {
        printf("Shortest job to run next is with ID: %d and time %d \n", ptr -> PID, ptr -> t);
        ptr = ptr -> next;
    }
   
}

void insertFirst(int PID, int t) {
  
    struct node *link = (struct node*) malloc(sizeof(struct node));
	
    link -> PID = PID;
    link -> t = t;

    link -> next = head;

    head = link;
}

int nodeLength() {
    
    int len = 0;
    struct node *now;
	
    for(now = head; now != NULL; now = now -> next) {
        len++;
    }
   
    return len;
}

void sort() {

    int i, j, k, tempPID, temp;
    struct node *now;
    struct node *next;
   
   
    int size = nodeLength();
    k = size ;
	
    for (i = 0 ; i < size - 1 ; i++, k-- ) {
        
        now = head;
        next = head->next;
		
        for (j = 1 ; j < k ; j++ ) {   

            if (now->t > next->t) {
                
                temp = now -> t;
                now -> t = next -> t;
                next -> t = temp;
                
                tempPID = now -> PID;
                now -> PID = next -> PID;
                next -> PID = tempPID;
            }
			
            now = now -> next;
            next = next -> next;
        }
    }   
}

void reverse(struct node** ref) {
   
    struct node* prev   = NULL;
    struct node* now = *ref;
    struct node* next;
	
    while (now != NULL) {
        next  = now->next;
        now->next = prev;   
        prev = now;
        now = next;
    }
	
    *ref = prev;
}

void *FCFSThread(void *x){
    printf("FCFS Job order:\n");
    printf("FCFS Jobs will be executed in the order they arrived:\n");
    reverse(&head);
    printFCFS();
    printf("FCFS DONE\n");
}

void *SJFThread(void *x){
    sleep(1);
    printf("SJF Jobs Order:\n");
    sort();
    printSJF();
    printf("SJF Done\n");
}