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

void printRR();
void insertFirst(int PID, int t);
struct node* delete(int PID);
int nodeLength();
void sort();
void reverse(struct node** ref);
void *RRThread(void *x);

struct node *head = NULL;
struct node *current = NULL;

int quantum;

int main() {
    
    pthread_t roundRobinT;
    
    int PID, t;
    int res;
    
    printf("Round Robin simulation program");
    printf("Enter a quantum value to be used: ");
    scanf("%i", &quantum);
    
    while(1) {
        printf("Enter an ID and a value for a node to add to the list, Enter -1 to stop: ");
        scanf("%i" "%i", &PID, &t);
        
        if(PID == -1 && t == -1) {
            break;
        } else {
            insertFirst(PID, t);
        }
    }

    res = pthread_create(&roundRobinT, NULL, RRThread, NULL);
    
    if (res != 0) {
        exit(EXIT_FAILURE);
    }
    
    res = pthread_join(roundRobinT, NULL);
    if (res != 0) {
        exit(EXIT_FAILURE);
    }
    
    printf("RoundRobin:: All jobs completed\n");
    exit(0);
}

void printRR() {
   
   struct node *ptr = head;

   while(ptr != NULL) {
      printf("Node ID %d with value %d \n",ptr->PID,ptr->t);
      ptr = ptr->next;
   }
}

void insertFirst(int PID, int t) {
  
    struct node *link = (struct node*) malloc(sizeof(struct node));
	
    link -> PID = PID;
    link -> t = t;

    link -> next = head;

    head = link;
}

struct node* delete(int PID) {

    struct node* now = head;
    struct node* old = NULL;
	
 
    if(head == NULL) {
        return NULL;
    }

    while(now -> PID != PID) {
    
        if(now -> next == NULL) {
            return NULL;
        } else {
            old = now;
            now = now -> next;
      }
    }
   
    if(now == head) {
        head = head -> next;
    } else {
        old -> next = now -> next;
   }    
	
   return now;
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

void *RRThread(void *x){
    
    printf("RoundRobin will start on the following list:\n");
    printf("Linked list contain the following values:\n");
    
    reverse(&head);
    printRR();
    
    while(head != NULL){
        struct node *ptr = head;
        
        while(ptr != NULL) {
            printf("Current node %i :time value before %i, after quantum %i\n", ptr->PID,ptr->t,ptr->t - quantum);
            ptr->t = ptr->t - quantum;
            ptr = ptr->next;
        }
        
        ptr = head;
        while(ptr != NULL) {
           
            if(ptr->t <= 0) {
                
                printf("###########################################\n");
                printf("Job with ID %i and time %i will be removed\n",ptr->PID,ptr->t);
                
                delete(ptr->PID);
                
                printf("###########################################\n");
            }
            ptr = ptr->next;
        }
        printf("Iteration completed, RoundRobin Will Start from begining of the list\n");
    }
    
}