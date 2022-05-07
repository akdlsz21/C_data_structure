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
void appendChild(Node* root, int nodeVals[], int directionArr[]);
int* DFS(Node* node, int resultOfDfs[]);






int main(){
   srand(time(NULL));
   // nodeVal array;
   int nodeN = randomInt(10, 20);
   int nodeVals[nodeN];
   int directionArr[nodeN];
   
   for(int i = 0; i < nodeN; i++){
      nodeVals[i] = randomInt(1, 100);
      directionArr[i] = randomInt(1, 2);

   }


   
   // init the root;
   Node* rootNode = malloc(sizeof(Node));
   // rootNode->val = randomInt(1, 100);
   rootNode->val = 500;

   // make children of rootNode(10 ~ 20)
   for(int i = 0; i < nodeN; i++){
      appendChild(rootNode, nodeVals, directionArr);
   }
   
   int resultOfDfs[21];
   DFS(rootNode, resultOfDfs);
   printf("\n\nRecursive Node tree(pre)\n==========================================================\n");
   for(int i = 0; i < nodeN; i++){
      printf("%d - ", resultOfDfs[i]);
   }
   printf("\n==========================================================\n");


}

int* DFS(Node* node, int resultOfDfs[]){
   
   int i = 0;

   void helper(Node* node){

      if(node == NULL) return;

      resultOfDfs[i] = node->val;
      i++;
      if(node->left) helper(node->left);
      if(node->right) helper(node->right);


   }
   helper(node);

}



void appendChild(Node* root, int nodeVals[], int directionArr[]){
   
   int i = 0;

   if(directionArr[i]){
      if(root->left == NULL){
         Node* newNode = malloc(sizeof(Node));
         newNode->val = nodeVals[i];
         i++;
         root->left = newNode;
      }
      
      else appendChild(root->left, nodeVals, directionArr);
   }else if(directionArr[i] ==2){
      if(root->right == NULL){
         Node* newNode = malloc(sizeof(Node));
         newNode->val = nodeVals[i];
         i++;
         root->right = newNode;
      }
      
      else appendChild(root->right, nodeVals, directionArr);
   }

}

int randomInt(int start, int end){
   return (rand() % (end - start + 1)) + start ;
}

void generateChildrenOfRoot(Node* root){
   int n = randomInt(10, 20);
}