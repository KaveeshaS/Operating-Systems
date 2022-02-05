#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include "Stack.h"

node* pop(Stack* s){
    if(s -> Top == NULL){
        return NULL;
    } else {
        
        node* tempNode = s -> Top;
        s -> Top = tempNode -> next;
        s -> count--;
        
        return tempnode;
    }
}

void Push(Stack* s, node* n){
    node* tempNode = s -> Top;
    s -> Top = n;
    n -> next = tempNode;
    s -> count++;
}