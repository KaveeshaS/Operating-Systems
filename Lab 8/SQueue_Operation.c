#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include "SQueue.h"

node* search(SQueue* q, int x){
    node* now = q -> Queue;
    
    while(now != NULL){
        if(now -> data == x){
            return now;
        } else {
            now = now -> next;
        }
    } 
    
    return NULL;
}

void enqueue(SQueue* q, node* n){
    if(q -> Queue == NULL){
        q -> Queue = n;
        q -> count++;
    } else if(n -> data > q -> Queue -> data){
        n -> next = q -> Queue;
        q -> Queue = n;
    } else {
        
        node* now = q -> Queue;
        
        while((now -> data < n -> data) & (now -> next != NULL)){
            now = now -> next;
        }
        
        n -> next = now -> next;
        now -> next = n;
        q -> count++;
    }
}

node* dequeue(SQueue* q){
    if(q -> Queue == NULL){
        return NULL;
    } else {
        node* tempNode = q -> Queue;
        q -> Queue = tempNode -> next;
        q -> count--;
        return tempNode;
    }
}