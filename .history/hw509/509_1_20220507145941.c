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
void appendChild(Node* root);

int main(){
   srand(time(NULL));
   // Making the tree;

   
   // init the root;
   Node* rootNode = malloc(sizeof(Node));
   rootNode->val = randomInt(1, 100);

   // make children of rootNode(10 ~ 20)
   for(int i = 0; i < randomInt(10, 20); i++){
      appendChild(rootNode);
   }


}
void appendChild(Node* root){
   
   int leftOrRight = randomInt(1, 2);
   
   if(leftOrRight == 1){
      if(root->left == NULL){
         Node* newNode = malloc(sizeof(Node));
         newNode->val = randomInt(1, 100);
         root->left = newNode;
      }
      
      else appendChild(root->left);
   }else{
      if(root->right == NULL){
         Node* newNode = malloc(sizeof(Node));
         newNode->val = randomInt(1, 100);
         root->right = newNode;
      }
      
      else appendChild(root->right);
   }

}

int randomInt(int start, int end){
   return (rand() % (end - start + 1)) + start ;
}

void generateChildrenOfRoot(Node* root){
   int n = randomInt(10, 20);
}