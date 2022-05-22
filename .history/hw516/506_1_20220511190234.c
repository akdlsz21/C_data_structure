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
Node* appendNodeRecur(Node* root, int insertVal);
Node* createNode(int insertVal);

int main(){
   srand(time(NULL));
   int iterValArr[20];
   int recurValArr[20];

   fillArr(iterValArr);
   fillArr(recurValArr);

   Node* iterTreeRoot = malloc(sizeof(Node));
   Node* recurTreeRoot = malloc(sizeof(Node));

   iterTreeRoot->val = iterValArr[0];
   recurTreeRoot->val = recurValArr[0];

   for(int i = 1; i < 20; i++){
      iterTreeRoot = appendNodeRecur(recurTreeRoot, recurValArr[i]);
   }

   

}

Node* appendNodeRecur(Node* root, int insertVal){
   if(root == NULL){
      return createNode(insertVal);
   }
   else if(root->val < insertVal){
      root->right = appendNodeRecur(root->right, insertVal);
   }else if(root->val > insertVal){
      root->left = appendNodeRecur(root->left, insertVal);
   }

   return root;
}

Node* createNode(int insertVal){
   Node* pizza = malloc(sizeof(Node));
   pizza->val = insertVal;
   return pizza;
}

void fillArr(int valArr[]){
   for(int i = 0; i < 20; i++){
      valArr[i] = randomInt(1, 30);
   }
}

int randomInt(int start, int end){
   return (rand() % (end - start + 1)) + start;
}
