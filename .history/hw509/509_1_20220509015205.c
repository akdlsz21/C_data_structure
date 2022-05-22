#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define QUEUE_SIZE 15


typedef struct _node{
   int val;
   struct _node* left;
   struct _node* right;
}Node;

typedef struct _array{
   int* array;
   int length;
}Array;

typedef struct queue{
   struct _node* data[QUEUE_SIZE];
   int front;
   int rear;
   int queueSize;
   int length;
}Queue;


int randomInt(int start, int end, int, int);
// void generateChildrenOfRoot(Node* root);
void appendRecursively(Node* root, int nodeVals[], Array* arr, int* j);
void appendIteratively(Node* root, int nodeVals[], Array* arr, int nodeN);
void DFS(Node* node, int resultOfDfs[], int*);
void helper(Node*);
void push(Array*, int);
int getRandomNodeVals(int start, int end);
void levelOrderTraverse(Node* root, Queue* que);
void enqueue(Queue* queue, Node* value);
Node* dequeue(Queue* queue);
int isEmpty(Queue* queue);
int isFull(Queue* queue);





int main(){
   srand(time(NULL));
   // nodeVal array;
   // int nodeN = randomInt(4,4);
   int nodeN = getRandomNodeVals(10, 20);
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
   /*


   */


   int resultOfDfs[200];
   int k = 0;
   DFS(recurRoot, resultOfDfs, &k);
   printf("\n\nRecursive Node tree\n");
   for(int i = 0; i < k; i++){
      printf("%d - ", resultOfDfs[i]);
   }
   printf("\n");


   int whilelooptree[200];
   k = 0;
   DFS(iterRoot, whilelooptree, &k);
   printf("\n\nIterative Node tree\n");
   for(int i = 0; i < k; i++){
      printf("%d - ", whilelooptree[i]);
   }
   printf("\n\n");


   Queue* que = malloc(sizeof(Queue));
   que->front = 0;
   que->rear = 0;
   que->length = 0;
   que->queueSize = QUEUE_SIZE;

   levelOrderTraverse(recurRoot, que);
   levelOrderTraverse(iterRoot, que);

}

void levelOrderTraverse(Node* root, Queue* que){
   enqueue(que, root);
   
   while(que->front != que->rear){
      printf("[");
      int queLength = que->length;
      while(queLength >= 1){
         Node* node = dequeue(que);
         if(node->left) enqueue(que, node->left);
         if(node->right) enqueue(que, node->right);
         printf(" %d ", node->val);
         queLength--;
      }      
      printf("]\n");
   }
   printf("\n");
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
            if(root->left == NULL) break;
            else root = root->left;
            
         }else if(direction == 2){
            if(root->right == NULL) break;
            else root = root->right;
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

void enqueue(Queue* queue, Node* value){
   if(!isFull(queue)){
      queue->rear = (queue->rear + 1) % QUEUE_SIZE;
      queue->data[queue->rear] = value;
      queue->length++;
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
      queue->length--;
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