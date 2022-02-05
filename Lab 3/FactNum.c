#include <stdio.h>

int main(){
   
   int fac = 1;
   int x;
   
   printf("Enter a Number: ");
   scanf("%d", &x);
   
   for(int i = 0; i < x; i++){
      fac = fac * i;
   }
      
   printf("The Factorial is %d\n", fac);
   return 0;
  
}