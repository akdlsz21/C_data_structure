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
int* DFS(Node* node, int resultOfDfs[]);



int main(){
   srand(time(NULL));
   // Making the tree;

   
   // init the root;
   Node* rootNode = malloc(sizeof(Node));
   // rootNode->val = randomInt(1, 100);
   rootNode->val = 50;

   // make children of rootNode(10 ~ 20)
   int nodeN = randomInt(10, 20);
   for(int i = 0; i < nodeN; i++){
      appendChild(rootNode);
   }
   
   int resultOfDfs[21];
   DFS(rootNode, resultOfDfs);
   for(int i = 0; i < nodeN; i++){
      printf("%d - ", resultOfDfs[i]);
   }


}

int* DFS(Node* node, int resultOfDfs[]){
   
   int i = 0;

   void helper(Node* node){

      if(node == NULL) return;

      if(node->left) helper(node->left);
      resultOfDfs[i] = node->val;
      i++;
      if(node->right) helper(node->right);


   }
   helper(node);

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
   }else if(leftOrRight ==2){
      if(root->right == NULL){
         Node* newNode = malloc(sizeof(Node));
         newNode->val = randomInt(1, 100);
         root->right = newNode;
      }
      
      else appendChild(root->right);
   }

   else{
      printf("\nSomething wrong with randomInt func,=> %d\n  ", leftOrRight);
   }

}

int randomInt(int start, int end){
   return (rand() % (end - start + 1)) + start ;
}

void generateChildrenOfRoot(Node* root){
   int n = randomInt(10, 20);
}