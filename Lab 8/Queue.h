#ifndef QUEUE
#define QUEUE

typedef struct node{
    int data;
    struct node* next;
}node;

typedef struct Queue_Info{
    struct node* first;
    struct node* last;
    struct node* Queue;
}Queue_Info;

node* search(Queue_Info* q, int x);
void enqueue(Queue_Info* q, node* n);
node* dequeue(Queue_Info* q);

#endif