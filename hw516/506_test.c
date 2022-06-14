#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct node{
   int val;
   struct node* left;
   struct node* right;
} Node;


void iterAppend(Node* node, int val);
void recurAppend(Node* node, int val);
void inorderTraverse(Node* root);
Node* createNode(int val);
Node* deleteNode(Node* root, int val);
Node* findMinNode(Node* root);

int main(){
   srand(time(NULL));
   int* numsArr = malloc(sizeof(int) * 20);

   for(int i = 0; i < 20; i++){
      numsArr[i] = rand() % 100;
   }

   Node* iterRoot = malloc(sizeof(Node));
   Node* recurRoot = malloc(sizeof(Node));

   iterRoot->val = numsArr[0];
   recurRoot->val = numsArr[0];

   for(int i = 1; i < 20; i++){
      iterAppend(iterRoot, numsArr[i]);
   }

   for(int i = 1; i < 20; i++){
      recurAppend(recurRoot, numsArr[i]);
   }


   inorderTraverse(iterRoot);
   puts("");
   inorderTraverse(recurRoot);
   puts("");
}



Node* deleteNode(Node* root, int val){
   if(root->val < val){
      root->right = deleteNode(root->right, val);
   }else if(root->val > val){
      root->left = deleteNode(root->left, val);
   }else{
      if(root->left == NULL){
         Node* temp = root->right;
         free(root);
         return temp;
      }else if(root->right == NULL){
         Node* temp = root->left;
         free(root);
         return temp;
      }

      Node* temp = findMinNode(root->right);

      root->val = temp->val;
      root->right = deleteNode(root->right, temp->val);
   }

   return root;
}

Node* findMinNode(Node* root){
   while(root != NULL){
      root = root->left;
   }

   return root;
}


void recurAppend(Node* node, int val){
   if(node->val < val){
      if(node->right){
         recurAppend(node->right, val);
      }else{
         Node* newNode = createNode(val);
         node->right = newNode;
      }
   }else if(node->val > val){
      if(node->left){
         recurAppend(node->left, val);
      }else{
         Node* newNode = createNode(val);
         node->left = newNode;
      }
   }


}

Node* createNode(int val){
   Node* newNode = malloc(sizeof(Node));
   newNode->val = val;
   newNode->left = NULL;
   newNode->right = NULL;

   return newNode;
}

void inorderTraverse(Node* root){
   if(root == NULL) return;

   if(root->left) inorderTraverse(root->left);
   printf("%d ", root->val);
   if(root->right) inorderTraverse(root->right);

}


void iterAppend(Node* node, int val){

   Node* prev = NULL;

   while(node != NULL){
      if(node->val == val) return;
      if(node->val < val){
         prev = node;
         node = node->right;
      }else if( node->val > val){
         prev = node;
         node = node->left;
      }
      
      
   }

   if(prev->val == val) return;

   node = malloc(sizeof(Node));
   node->val = val;
   node->left = NULL;
   node->right = NULL;
   if(prev->val < val) prev->right = node;
   if(prev->val > val) prev->left = node;

   return;
}