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
void appendNodeIter(Node* root, int insertVal);
Node* createNode(int insertVal);
void inorderTraverse(Node* root);
Node* deleteNode(Node* root, int deleteVal);
Node* minValueNode(Node* root);

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
      recurTreeRoot = appendNodeRecur(recurTreeRoot, recurValArr[i]);
   }
   puts("111");
   inorderTraverse(recurTreeRoot);
   printf("\n");
   puts("222");

   for(int j = 1; j < 20; j++){
      appendNodeIter(iterTreeRoot, recurValArr[j]);
   }
   puts("333");
   inorderTraverse(iterTreeRoot);
   printf("\n");
   puts("444");


   

}

Node* deleteNode(Node* root, int val){
   if (root == NULL) return root;

   if(val < root->val)
      root->left = deleteNode(root->left, val);
   else if( val > root->val)
      root->right = deleteNode(root->right, val);
   else{
      if(root->left == NULL){
         Node* temp = root->right;
         free(root);
         return temp;
      }
      else if(root->right == NULL){
         Node* temp = root->left;
         free(root);
         return temp;
      }
      
      Node* temp = minValueNode(root->right);

      root->val = temp->val;
      root->right = deleteNode(root->right, temp->val);
   }
   return root;
      
}

Node* minValueNode(Node* root){
   Node* current = root;
   while(current->left != NULL){
      current = current->left;
   }
   return current;
}

void inorderTraverse(Node* root){
   if(root == NULL) return;

   if(root->left) inorderTraverse(root->left);
   printf("%d - ", root->val);
   if(root->right) inorderTraverse(root->right);

}

void appendNodeIter(Node* root, int insertVal){


   Node* prev = NULL;
   
   while(root != NULL){

      if(root->val > insertVal){
         prev = root;
         root = root->left;
      }else if(root->val <= insertVal){
         prev = root;
         root = root->right;
      }

   }
   if(prev->val == insertVal) return;

   if(prev->val > insertVal){
      Node* newNode = malloc(sizeof(Node));
      newNode->val = insertVal;
      prev->left = newNode;
   }
   else if(prev->val < insertVal){
      Node* newNode = malloc(sizeof(Node));
      newNode->val = insertVal;
      prev->right = newNode;
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
   int valSetLength = 0;

   int i = 0;
   while(valSetLength <= 20){
      int val = randomInt(1, 30);

      if(valSetLength == 0){
         valArr[valSetLength] = val;
         valSetLength++;
      }else{
         for(int j = 0; j < valSetLength; j++){
            if(valArr[j] == val) break;
            if(j + 1 == valSetLength){
               valArr[valSetLength] = val;
               valSetLength++;
            }
         }

      }

   }
}

int randomInt(int start, int end){
   return (rand() % (end - start + 1)) + start;
}
