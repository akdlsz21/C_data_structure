#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

typedef struct _node{
   char val;
   struct _node* left;
   struct _node* right;
}Node;

#define QUEUE_SIZE 15

typedef struct queue{
   struct _node* data[QUEUE_SIZE];
   int front;
   int rear;
   int queueSize;
}Queue;

typedef struct _stack {
   int* stack;
   int length;
}Stack;


// Node n7 = {'5', NULL, NULL};
// Node n6 = {'4', NULL, NULL};
// Node n5 = {'+', NULL, NULL};
// Node n4 = {'3', NULL, NULL};
// Node n3 = {'*', &n6, &n7};
// Node n2 = {'9', &n4, &n5};
// Node n1 = {'/', &n2, &n3};
// Node *root = &n1;

// 2*4*(5+5)/2
// Prefix : *2*4/+552

Node n9 = {'2', NULL, NULL};
Node n8 = {'5', NULL, NULL};
Node n7 = {'5', NULL, NULL};
Node n6 = {'+', NULL, NULL};
Node n5 = {'/', NULL, NULL};
Node n4 = {'4', &n8, &n9};
Node n3 = {'*', &n6, &n7};
Node n2 = {'2', &n4, &n5};
Node n1 = {'*', &n2, &n3};
Node *root = &n1;



void traverse(Node* root, Queue* queue, char expression[], int* expLen);
void enqueue(Queue* queue, Node* value);
Node* dequeue(Queue* queue);
int isEmpty(Queue* queue);
int isFull(Queue* queue);
void push(Stack* stack, int val);
int pop(Stack*);
void evaluate(Node* root,  char* expression, int* expLen);
int evalPrefix(Stack*, char*, int);


void main(){
   Queue* queue = malloc(sizeof(Queue));
   queue->front = 0;
   queue->rear = 0;
   queue->queueSize = QUEUE_SIZE;

   char expression[15];
   int expLen = -1;

   traverse(root, queue, expression, &expLen);

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


void traverse(Node* root, Queue* queue, char expression[], int* expLen){
   enqueue(queue, root);

   while(queue->front != queue->rear){
      Node* node = dequeue(queue);
      if(node->val == "ERROR") {
         // node-> from dequeue means that deque is excessive.
         printf("\ndequeueing returns zeroNode.\n");
         exit(-1);
      }
      *expLen = *expLen + 1;
      expression[*expLen] = node->val;
      
      if(node->left) enqueue(queue, node->left);
      if(node->right) enqueue(queue, node->right);
   }
}



void enqueue(Queue* queue, Node* value){
   if(!isFull(queue)){
      queue->rear = (queue->rear + 1) % QUEUE_SIZE;
      queue->data[queue->rear] = value;
   }else{
      printf("Enqueue Failed: queue is Full\n");
   }
}

Node* dequeue(Queue* queue){
   Node* returnVal;
   if(!isEmpty(queue)){
      queue->front = (queue->front + 1) % QUEUE_SIZE;

      returnVal = queue->data[queue->front];
      Node* zeroNode = malloc(sizeof(Node));
      zeroNode->val = "ERROR";
      zeroNode->left = NULL;
      zeroNode->right = NULL;
      queue->data[queue->front] = zeroNode;
      return returnVal;
   }else{
      printf("Dequeue Failed: queue is Empty\n");
   }
}

int isEmpty(Queue* queue){
   return queue->front == queue->rear;
}

int isFull(Queue* queue){
   return ((queue->rear + 1) % QUEUE_SIZE == queue->front);
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


int evalPrefix(Stack* stack, char* expression, int expLen){

   
   while(expLen >= 0){
      char value = expression[expLen];
      expLen--;

      if(isdigit(value))
         push(stack, value - '0');
      else{

         int op1 = pop(stack);
         int op2 = pop(stack);

         switch(value){
            case '+':
               push(stack, op1 + op2);
               break;
            case '-':
               push(stack, op1 - op2);
               break;
            case '/':
               // swap back op1 and op2;
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
