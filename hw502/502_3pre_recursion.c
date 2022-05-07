#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

typedef struct _node{
   char val;
   struct _node* left;
   struct _node* right;

}Node;


Node n7 = {'5', NULL, NULL};
Node n6 = {'4', NULL, NULL};
Node n5 = {'3', NULL, NULL};
Node n4 = {'*', NULL, NULL};
Node n3 = {'+', &n6, &n7};
Node n2 = {'9', &n4, &n5};
Node n1 = {'/', &n2, &n3};
Node *root = &n1;

typedef struct _stack {
   int* stack;
   int length;
}Stack;



void evaluate(Node* root,  char* expression, int* expLen);
int evalPrefix(Stack*, char*, int);
void push(Stack* stack, int val);
int pop(Stack*);

void main(){


   char expression[10];
   int expLen = -1;

   evaluate(root, expression, &expLen);

   for(int i = 0; i <= expLen; i++){
      printf("%c", expression[i]);
   }
   printf("\n");

   Stack* stack = malloc(sizeof(Stack));
   stack->stack = malloc(sizeof(int) * expLen);
   stack->length = -1;

   int result = evalPrefix(stack, expression, expLen);

   printf("%d\n", result);



}

int evalPrefix(Stack* stack, char* expression, int expLen){

   
   while(expLen >= 0){
      char value = expression[expLen];
      expLen--;

      if(isdigit(value))
         push(stack, value - '0');
      else{

         int op2 = pop(stack);
         int op1 = pop(stack);

         switch(value){
            case '+':
               push(stack, op1 + op2);
               break;
            case '-':
               push(stack, op1 - op2);
               break;
            case '/':
               push(stack, op1 / op2);
               break;
            case '*':
               push(stack, op1 * op2);
               break;
         }
      }
   }

   return pop(stack);
}

void evaluate(Node* root, char* expression, int* expLen){
   if(!root) return;

   *expLen = *expLen + 1;
   expression[*expLen] = root->val;
   if(root->left) evaluate(root->left, expression, expLen);
   if(root->right) evaluate(root->right, expression, expLen);
}

void push(Stack* stack, int val){
   stack->length++;
   stack->stack[stack->length] = val;
}

int pop(Stack* stack){
   int ret = stack->stack[stack->length];
   stack->length--;
   return ret;
}

