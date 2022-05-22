#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct _node{
   int val;
   struct _node* left;
   struct _node* right;
}Node;




int randomInt(int start, int end);
void fillArr(int[]);


int main(){
   srand(time(NULL));
   int iterTreeValArray[20];
   int recurTreeValArray[20];

   fillArr(iterTreeValArray);
   fillArr(recurTreeValArray);
   

}

void fillArr(int valArr[]){
   for(int i = 0; i < 20; i++){
      valArr[i] = randomInt(1, 30);
   }
}

int randomInt(int start, int end){
   return (rand() % (end - start + 1)) + start;
}
