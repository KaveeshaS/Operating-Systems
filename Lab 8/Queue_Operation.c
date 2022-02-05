#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include "Queue.h"

node* search(Queue_Info* q, int x){
    node* now = q -> first;
    
    while(now != NULL){
        if(now -> data == x){
            return now;
        } else {
            now = now -> next;
        }
    } 
    
    return NULL;
}

void enqueue(Queue_Info* q, node* n){
    if(q -> first == NULL){
        q -> first = n;
        q -> Queue = n;
        q -> last = n;
    } else {
        q -> last -> next = n;
        n -> next = NULL;
        q -> last = n;
    }
}

node* dequeue(Queue_Info* q){
    if(q -> first == NULL){
        return NULL;
    } else {
        node* tempNode = q -> first;
        q -> first = q -> Queue = tempNode -> next;
        return tempNode;
    }
}
