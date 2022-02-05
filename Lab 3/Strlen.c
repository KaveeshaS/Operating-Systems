#include <stdio.h>

int main() {
   
   char str[50];
   int i = 0;
  
   printf("Enter a string: ");
   scanf("%s", str);
  
   while(str[i] != '\0') {
      i++;
   }
   
   printf("Length of the string: %d\n", i);
  
  return 0;
  
}