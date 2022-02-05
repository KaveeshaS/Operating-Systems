#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

int a[5];

void *mThread(){
    printf("Enter 5 Numbers: ");
    for(int i = 0; i < 5; i++){
        scanf("%d", &a[i]);
    }
}

void *sortThread() {
    for(int i = 0; i < 5; i++){
        for(int j = 0; j < 5; j++){
            if(a[i] < a[j]){
                int t = a[i];
                a[i] = a[j];
                a[j] = t;
            }
        }
    }
    
    for(int k = 0; k < 4; k++){
        printf("%d, ", a[k]);
    }
    
    printf("%d", a[4]);
}

int main(){
    
    int input;
    
    int res;
    
    pthread_t IDmainT;
    pthread_t IDsortT;
    
    do{
        
        res = pthread_create(&IDmainT, NULL, mThread, NULL);
        if(res != 0){
            perror("Thread creation failed"); 
            exit(EXIT_FAILURE); 
        }
        
        res = pthread_join(IDmainT, NULL); 
        if (res != 0) {    
            perror("Thread join failed");      
            exit(EXIT_FAILURE);   
        }
        
        res = pthread_create(&IDsortT, NULL, sortThread, NULL);
        if(res != 0){
            perror("Thread creation failed"); 
            exit(EXIT_FAILURE); 
        }
        
        res = pthread_join(IDsortT, NULL); 
        if (res != 0) {    
            perror("Thread join failed");      
            exit(EXIT_FAILURE);   
        }
        
        printf("\nWould you like to continue? Enter (0) Yes, Enter (1) No : ");
        scanf("%d", &input);
        
        // if(input == 1){
        //     return 0;
        // }
    } while(input == 0);
    
    return 0;
    
}