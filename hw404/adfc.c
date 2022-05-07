#include <stdlib.h>
#include <stdio.h>

int main(){
   int var = 0;

   for(int i = 1;  ;i++){
      var += i;
      if(var > 10000){
         break;
      }
   }

   printf("%d", var);
}