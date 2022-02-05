#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct bitField{
    unsigned int adr: 3;
    unsigned int prsnt: 1;
} bitField;

bitField PageTable[16] = {{2,1}, {1,1}, {6,1}, {0,1},
                          {4,1}, {3,1}, {0,0}, {0,0},
                          {0,0}, {5,1}, {0,0}, {7,1},
                          {0,0}, {0,0}, {0,0}, {0,0}};
                          
int convert(unsigned int adr);

int main(){
    
    unsigned int vAdr;
    
    printf("Enter a Virtual address: ");
    scanf("%i", &vAdr);
    
    printf("The %d virtual address maps to the %d physical address\n", vAdr, convert(vAdr));
    
    return 0;
}

int convert(unsigned int adr){
    unsigned int offset = adr & 0x00000FFF;
    unsigned int index = (adr & 0x0000F000) >> 12;
    bitField x = PageTable[index];
    int newAdr = (x.adr << 12) + offset;
    
    return newAdr;
}