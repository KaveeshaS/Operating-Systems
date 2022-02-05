#ifndef SQUEUE
#define SQUEUE

typedef struct node{
    int data;
    struct node* next;
}node;

typedef struct Queue_Info{
    int count;
    struct node* Queue;
}SQueue;

node* search(SQueue* q, int x);
void enqueue(SQueue* q, node* n);
node* dequeue(SQueue* q);

#endif