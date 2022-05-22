#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct _node{
   int val;
   struct _node* left;
   struct _node* right;
}Node;

typedef struct _array{
   int* array;
   int length;
}Array;

int randomInt(int start, int end, int, int);
// void generateChildrenOfRoot(Node* root);
void appendRecursively(Node* root, int nodeVals[], Array* arr, int* j);
void appendIteratively(Node* root, int nodeVals[], Array* arr, int nodeN);
void DFS(Node* node, int resultOfDfs[], int*);
void helper(Node*);
void push(Array*, int);
int getRandomNodeVals(int start, int end);






int main(){
   srand(time(NULL));
   // nodeVal array;
   // int nodeN = randomInt(4,4);
   int nodeN = 10;
   int nodeVals[nodeN];
   for(int i = 0; i < nodeN; i++) nodeVals[i] = getRandomNodeVals(20, 100);
   
   Array* arr = malloc(sizeof(Array));
   arr->array = malloc(sizeof(int) * 5);
   arr->length = 0;
   

   Node* recurRoot = malloc(sizeof(Node));
   recurRoot->val = 500;

   int j = 0;
   for(int i = 0; i < nodeN; i++){
      appendRecursively(recurRoot, nodeVals, arr, &j);
   }

   Node* iterRoot = malloc(sizeof(Node));
   iterRoot->val = 500;

   int l = 0;
   appendIteratively(iterRoot, nodeVals, arr, nodeN);
   


   int resultOfDfs[200];
   int k = 0;
   DFS(recurRoot, resultOfDfs, &k);
   printf("\n\nRecursive Node tree(pre)\n==========================================================\n");
   for(int i = 0; i < k; i++){
      printf("%d - ", resultOfDfs[i]);
   }
   printf("\n==========================================================\n");


   int whilelooptree[200];
   k = 0;
   DFS(iterRoot, whilelooptree, &k);
   printf("\n\nIterative Node tree(pre)\n==========================================================\n");
   for(int i = 0; i < k; i++){
      printf("%d - ", whilelooptree[i]);
   }
   printf("\n==========================================================\n");



}

void appendIteratively(Node* root, int nodeVals[], Array* arr, int nodeN){
   Node* rootPointer = root;

   int i = 0; 
   int direction;
   int val;
   while(i < nodeN){
      root = rootPointer;
      val = nodeVals[i];

      while(root->left != NULL || root->right != NULL){
         direction = randomInt(1, 2, root->val, val);
         if(direction == 1){
            if(root->left == NULL){
               Node* newNode = malloc(sizeof(Node));
               newNode->val = val;
               root->left = newNode;
            }
         }else if(direction == 2){
            if(root->right == NULL){
               Node* newNode = malloc(sizeof(Node));
               newNode->val = val;
               root->right = newNode;
            }
         }
      }

      Node* newNode = malloc(sizeof(Node));
      newNode->val = val;

      direction = randomInt(1, 2, root->val, val);

      if(direction == 1){
         root->left = newNode;
      }else if(direction == 2){
         root->right = newNode;
      }
      i++;
   }
}



void appendRecursively(Node* root, int nodeVals[], Array* arr, int* j){
   
   int val = nodeVals[*j];
   int direction = randomInt(1, 2, root->val, val);
   // push(arr, direction);

   if(root == NULL){
      printf("\n something went wrong, \n");
   }
   if(direction == 1){
      if(root->left == NULL){
         Node* newNode = malloc(sizeof(Node));
         newNode->val = val;
         *j = *j + 1;
         root->left = newNode;
      }
      
      else appendRecursively(root->left, nodeVals, arr, j);
   }else if(direction == 2){
      if(root->right == NULL){
         Node* newNode = malloc(sizeof(Node));
         newNode->val = val;
         *j = *j + 1;
         root->right = newNode;
      }
      
      else appendRecursively(root->right, nodeVals, arr, j);
   }

}

void DFS(Node* node, int resultOfDfs[], int* k){
   
   int i = 0;

   void helper(Node* node){

      if(node == NULL) return;

      if(node->left) helper(node->left);
      else {
         resultOfDfs[*k] = 0;
         *k = *k + 1;
      }
      resultOfDfs[*k] = node->val;
      *k = *k + 1;


      if(node->right) helper(node->right);
      else {
         resultOfDfs[*k] = 0;
         *k = *k + 1;
      }


   }
   helper(node);

}


int randomInt(int start, int end, int nodeVal, int val){
   srand(nodeVal + val);
   return (rand() % (end - start + 1)) + start ;
}

int getRandomNodeVals(int start, int end){
   return (rand() % (end - start + 1)) + start;
}

// void generateChildrenOfRoot(Node* root){
//    int n = randomInt(10, 20,);
// }

void push( Array* arr, int val){
   if(arr->length % 5 == 0){
      arr->array = realloc(arr->array, sizeof(int) * (arr->length + 5));
   }
   
   arr->array[arr->length] = val;
   arr->length++;
}