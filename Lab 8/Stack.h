#ifndef STACK
#define STACK

typedef struct node{
    int data;
    struct node* next;
}node;

typedef struct Stack_Info{
    int count;
    node* Top;
}Stack;

node* pop(Stack* s);
void Push(Stack* s, node* n);

#endif