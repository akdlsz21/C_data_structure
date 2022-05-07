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
void appendRecursively(Node* root, int nodeVals[], int directionArr[], int* j);
void DFS(Node* node, int resultOfDfs[]);
void helper(Node*);






int main(){
   srand(time(NULL));
   // nodeVal array;
   int nodeN = randomInt(10, 20);
   int nodeVals[nodeN];
   int directionArr[nodeN];
   
   for(int i = 0; i < nodeN; i++){
      nodeVals[i] = randomInt(1, 100);

   }

   // init the root;
   Node* rootNode = malloc(sizeof(Node));
   // rootNode->val = randomInt(1, 100);
   rootNode->val = 500;

   // make children of rootNode(10 ~ 20)
   int j = 0;
   for(int i = 0; i < nodeN; i++){
      appendRecursively(rootNode, nodeVals, directionArr, &j);
   }
   

   int resultOfDfs[21];
   DFS(rootNode, resultOfDfs);
   printf("\n\nRecursive Node tree(pre)\n==========================================================\n");
   for(int i = 0; i < nodeN; i++){
      printf("%d - ", resultOfDfs[i]);
   }
   printf("\n==========================================================\n");




}

void DFS(Node* node, int resultOfDfs[]){
   
   int i = 0;

   void helper(Node* node){

      if(node == NULL) {
         resultOfDfs[i] = 0;
         i++;
         return;
      }

      if(node->left) helper(node->left);
      resultOfDfs[i] = node->val;
      i++;
      if(node->right) helper(node->right);


   }
   helper(node);

}



void appendRecursively(Node* root, int nodeVals[], int directionArr[], int* j){
   
   int direction = randomInt(1, 2);

   if(direction == 1){
      if(root->left == NULL){
         Node* newNode = malloc(sizeof(Node));
         newNode->val = nodeVals[*j];
         directionArr[*j] = direction;
         *j = *j + 1;
         root->left = newNode;
      }
      
      else appendRecursively(root->left, nodeVals, directionArr, j);
   }else if(direction == 2){
      if(root->right == NULL){
         Node* newNode = malloc(sizeof(Node));
         newNode->val = nodeVals[*j];
         directionArr[*j] = direction;
         *j = *j + 1;
         root->right = newNode;
      }
      
      else appendRecursively(root->right, nodeVals, directionArr, j);
   }

}

int randomInt(int start, int end){
   return (rand() % (end - start + 1)) + start ;
}

void generateChildrenOfRoot(Node* root){
   int n = randomInt(10, 20);
}