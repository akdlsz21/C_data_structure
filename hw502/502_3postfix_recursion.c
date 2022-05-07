#include <stdio.h>
#include <stdlib.h>

typedef struct _node{
   int val;
   struct _node* left;
   struct _node* right;
}Node;



Node n7 = {5, NULL, NULL};
Node n6 = {4, NULL, NULL};
Node n5 = {'+', &n6, &n7};
Node n4 = {3, NULL, NULL};
Node n3 = {9, NULL, NULL};
Node n2 = {'*', &n4, &n5};
Node n1 = {'/', &n2, &n3};
Node *exp = &n1;

char arr[10];
int i = -1;


int evaluate(Node* root){
   if(root == NULL) return 0;
   if(root->left == NULL && root->right == NULL) return root->val;
   else{
      int op1 = evaluate(root->left);
      int op2 = evaluate(root->right);
      printf("%d %c %d을 계산합니다.\n", op1, root->val, op2);
      switch(root->val){
         case '+':
            return op1 + op2;
         case '-':
            return op1 - op2; 
         case '*':
            return op1 * op2;
         case '/':
            return op1 / op2;
      }
   }

   return 0;
}


void main(){
   printf("수식의 값은 %d입니다. \n", evaluate(exp));
}

