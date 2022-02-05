#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include <pthread.h>
#include <semaphore.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <sys/types.h>
#include "Queue.h"

void *Process_Nodes(void *arg);
void *Add_To_Processing_Queue(void *arg);
void *Send_To_SMemory(void *arg);

// Declare Queue
Queue_Info *Processing_Queue;
Queue_Info *Sending_Queue;

// Declare Mutex
pthread_mutex_t Lock_Input; 
pthread_mutex_t Lock_PList; 
pthread_mutex_t Lock_SList; 

// Declare Semaphores
sem_t Input_Ready;
sem_t Input_Taken;
sem_t Empty_PSlots;
sem_t Filled_PSlots;
sem_t Empty_SSlots;
sem_t Filled_SSlots;

// Delcare Gloabl Variables
int input;
int end_time = 0;

int main() {
    
    int res;
    
    // Declare Thread
    pthread_t add_processing_queue;
    pthread_t process_nodes;
    pthread_t send_to_SMem;
    
    Processing_Queue = (Queue_Info *) malloc(sizeof(Queue_Info));
    Sending_Queue = (Queue_Info *) malloc(sizeof(Queue_Info));
    
    // Creat Mutex
    res = pthread_mutex_init(&Lock_Input, NULL); 
    if (res != 0) { 
        perror("Mutex Init Failed");
        exit(EXIT_FAILURE); 
    }  
    
    res = pthread_mutex_init(&Lock_PList, NULL); 
    if (res != 0) { 
        perror("Mutex Init Failed");
        exit(EXIT_FAILURE); 
    } 
    
    res = pthread_mutex_init(&Lock_SList, NULL); 
    if (res != 0) { 
        perror("Mutex Init Failed");
        exit(EXIT_FAILURE); 
    }  
    
    // Create Semaphores
    res = sem_init(&Input_Ready, 0,  0); 
    if (res != 0) { 
        perror("Semaphore Init Failed");
        exit(EXIT_FAILURE); 
    } 
    
    res = sem_init(&Input_Taken, 0, 1); 
    if (res != 0) { 
        perror("Semaphore Init Failed");
        exit(EXIT_FAILURE); 
    }
    
    res = sem_init(&Empty_PSlots, 0, 5); 
    if (res != 0) { 
        perror("Semaphore Init Failed");
        exit(EXIT_FAILURE); 
    } 
    
    res = sem_init(&Filled_PSlots, 0, 0); 
    if (res != 0) { 
        perror("Semaphore Init Failed");
        exit(EXIT_FAILURE); 
    }
    
    res = sem_init(&Empty_SSlots, 0, 5); 
    if (res != 0) { 
        perror("Semaphore Init Failed");
        exit(EXIT_FAILURE); 
    }
    
    res = sem_init(&Filled_SSlots, 0, 0); 
    if (res != 0) { 
        perror("Semaphore Init Failed");
        exit(EXIT_FAILURE); 
    }
    
    // Create Threads
    res = pthread_create(&add_processing_queue, NULL, Add_To_Processing_Queue, NULL);
    if (res != 0) {
        perror("Thread Create Failed");
        exit(EXIT_FAILURE);
    }
     
    res = pthread_create(&process_nodes, NULL, Process_Nodes, NULL);
    if (res != 0) {
        perror("Thread Create Failed");
        exit(EXIT_FAILURE);
    }
     
    res = pthread_create(&send_to_SMem, NULL, Send_To_SMemory, NULL);
    if (res != 0) {
        perror("Thread Create Failed");
        exit(EXIT_FAILURE);
    }
    
    // Prompt User
    
    while(1) {
        
        sem_wait(&Input_Taken);
        
        printf("Temperature in Celcius: ");
        pthread_mutex_lock(&Lock_Input);
        scanf("%i", &input);
        
        if(input == -1){
            exit(0);
        } else {
            sem_post(&Input_Ready);
        }
        
        pthread_mutex_unlock(&Lock_Input);
    }
    
    // Join Thread 
    res = pthread_join(add_processing_queue, NULL);
    if (res != 0) {
        perror("Thread Join Failed");
        exit(EXIT_FAILURE);
    }
    
    res = pthread_join(process_nodes, NULL);
    if (res != 0) {
        perror("Thread Join Failed");
        exit(EXIT_FAILURE);
    }
    
    res = pthread_join(send_to_SMem, NULL);
    if (res != 0) {
        perror("Thread Join Failed");
        exit(EXIT_FAILURE);
    }
    
    // Kill Semaphores
    sem_destroy(&Input_Ready); 
    sem_destroy(&Input_Taken); 
    sem_destroy(&Empty_PSlots); 
    sem_destroy(&Filled_PSlots);
    sem_destroy(&Empty_SSlots); 
    sem_destroy(&Filled_SSlots);
    
    
    // Kill Mutexs
    pthread_mutex_destroy(&Lock_Input);
    pthread_mutex_destroy(&Lock_PList);
    pthread_mutex_destroy(&Lock_SList);
    
    return 0;
}

void *Add_To_Processing_Queue(void *arg){
    
    Qnode *node;
    node = (Qnode *) malloc(sizeof(Qnode));
    
    while(1){
        
        sem_wait(&Input_Ready);
        sem_wait(&Empty_PSlots);
        
        pthread_mutex_lock(&Lock_Input);
        node -> data = input;
        pthread_mutex_unlock(&Lock_Input);
        
        pthread_mutex_lock(&Lock_PList);
        Enqueue(Processing_Queue, node);
        pthread_mutex_unlock(&Lock_PList);
    
        sem_post(&Input_Taken);
        sem_post(&Filled_PSlots);
        
        if(end_time == -1) {
            break;
        }
    }
    end_time = -1;
}

void *Process_Nodes(void *arg) {
    
    // Declare Temperature variables
    int fahren;
    int cel;
    
    // Declare Nodes
    Qnode *node;
    node = (Qnode *) malloc(sizeof(Qnode));
    
    Qnode * newNode;
    newNode = (Qnode *) malloc(sizeof(Qnode));
    
    while(1){
        
        sem_wait(&Filled_PSlots);
        
        pthread_mutex_lock(&Lock_PList);
        node = Dequeue(Processing_Queue);
        pthread_mutex_unlock(&Lock_PList);
    
        sem_post(&Empty_PSlots);
        
        // Temperature Convertions
        cel = node -> data;
        fahren = ((cel/5) * 9) + 32;
        newNode -> data = fahren;
        
        sem_wait(&Empty_SSlots);
        
        pthread_mutex_lock(&Lock_SList);
        Enqueue(Sending_Queue, newNode);
        pthread_mutex_unlock(&Lock_SList);
    
        sem_post(&Filled_SSlots);
        
        if(end_time == -1) {
            break;
        }
    }
}

void *Send_To_SMemory(void *arg){
    
    int fahren;
    int x;
    
    const int SIZE = 4096;
    const char *memName = "Calculated_Data";
    int shm_fd;
    void *ptr;
    
    Qnode * node;
    node = (Qnode *) malloc(sizeof(Qnode));
    
    shm_fd = shm_open(memName, O_CREAT | O_RDWR, 0666);
    ftruncate(shm_fd, SIZE);
    
    ptr = mmap(0, SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd, 0);
    
    while(1) {
        sem_wait(&Filled_SSlots);
        pthread_mutex_lock(&Lock_SList);
        node = Dequeue(Sending_Queue);
        
        fahren = node -> data;
        
        x = sprintf(ptr, "%i\n", fahren);
        ptr = ptr + x;
    
        pthread_mutex_unlock(&Lock_SList);
        sem_post(&Empty_SSlots);
    
        if(end_time == -1) {
            break;
        }
    }
}