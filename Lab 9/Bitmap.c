#include <stdio.h>
#include <stdlib.h>

int Mallocate(int Mem_Size);
void Free(int Address, int Size);
void Print_Binary(unsigned int Value);

double Pow(double x, double y);

unsigned int Mem[2];

int main(){

    Mem[0] = 0xFFFFFFFF;
    
    int a = Mallocate(8);
    printf("The address is: %d\n", a);
    
    Print_Binary(Mem[0]);
    Print_Binary(Mem[1]);
    Free(4, 3);
    
    Print_Binary(Mem[0]);
    Print_Binary(Mem[1]);
    Free(32, 4);
    
    Print_Binary(Mem[0]);
    Print_Binary(Mem[1]);
}

int Mallocate(int Mem_Size){
   
    unsigned int mask = (unsigned int)(Pow(2.0, (double)Mem_Size))-1;
    
    mask = mask << 32 - Mem_Size;
    int ad = 0;
    for(int i = 0; i < sizeof(Mem) / sizeof(Mem[0]); i++){
        
        for(int j = 0; j < (32 - Mem_Size) +1; j++){
           
            unsigned int check = Mem[i] & mask;
            
            if(check == 0){
                Mem[i] = Mem[i] + mask;
                return ad;
            }
            
            mask = mask >> 1;
            ad++;
        }
        
        mask = (unsigned int)(Pow(2.0, (double)Mem_Size))-1;
        
        mask = mask << 32 - Mem_Size;
        ad += Mem_Size;
        
    } 
    
    return -1;
}

void Free(int Address, int Size){
    
    if(Address < 32){
        
        unsigned int mask = (unsigned int)(Pow(2.0, (double)Size))-1;
        
        mask = mask << (32 - Size - Address );
        Mem[0] = Mem[0] - mask;
        
    } else {
        
        unsigned int mask = (unsigned int)(Pow(2.0, (double)Size))-1;
        
        mask = mask << ( 32 - Size - (Address-32) );
        Mem[1] = Mem[1] - mask;
    }
    
}

void Print_Binary(unsigned int Value){
    
    int i;
    unsigned int Mask = 1;
    
    Mask = Mask << 31;
    
    for(i=0; i<32; i++){
        
        if((Mask & Value) == 0){
            printf("0");
        }else{
            printf("1");
        }
        Mask = Mask >> 1;
    }
    printf("\n");
}

double Pow(double x, double y){
    
    double num = 1;
    
    for(int i = 0; i <= y; i++){
        num *= x;
    }
    
    return num;
}