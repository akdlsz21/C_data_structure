#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct _node{
   int val;
   struct _node* left;
   struct _node* right;
}Node;

int randomInt(int start, int end);
void generateChildrenOfRoot(Node* root);

int main(){
   srand(time(NULL));
   // Making the tree;

   
   // init the root;
   Node* rootNode = malloc(sizeof(Node));
   rootNode->val = randomInt(1, 100);

   // make children of rootNode(10 ~ 20)
   for(int i = 0; i < 10; i++){
      
   }


}

int randomInt(int start, int end){
   return (rand() % (end - start + 1)) + start ;
}

void generateChildrenOfRoot(Node* root){
   int n = randomInt(10, 20);
}