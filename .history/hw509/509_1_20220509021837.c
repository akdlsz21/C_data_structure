#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define QUEUE_SIZE 15


typedef struct _node{
   int val;
   struct _node* left;
   struct _node* right;
}Node;


typedef struct queue{
   struct _node* data[QUEUE_SIZE];
   int front;
   int rear;
   int queueSize;
   int length;
}Queue;


int randomInt(int start, int end, int, int);
void appendRecursively(Node* root, int nodeVals[], int* j);
void appendIteratively(Node* root, int nodeVals[], int nodeN);
void DFS(Node* node, int resultOfDfs[], int*);
void helper(Node*);
int getRandomNodeVals(int start, int end);
void levelOrderTraverse(Node* root, Queue* que);
void enqueue(Queue* queue, Node* value);
Node* dequeue(Queue* queue);
int isEmpty(Queue* queue);
int isFull(Queue* queue);





int main(){
   srand(time(NULL));
   int nodeN = getRandomNodeVals(10, 19);
   int nodeVals[nodeN];
   for(int i = 0; i < nodeN; i++) nodeVals[i] = getRandomNodeVals(20, 100);
   

   Node* recurRoot = malloc(sizeof(Node));
   recurRoot->val = 500;

   int j = 0;
   for(int i = 0; i < nodeN; i++){
      appendRecursively(recurRoot, nodeVals, &j);
   }

   Node* iterRoot = malloc(sizeof(Node));
   iterRoot->val = 500;

   int l = 0;
   appendIteratively(iterRoot, nodeVals, nodeN);

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
   int level = 0;
   int nodeCount = 0;
   
   while(que->front != que->rear){
      int levelNodesCount = 0;
      printf("[");
      int queLength = que->length;

      while(queLength >= 1){
         Node* node = dequeue(que);
         nodeCount++;
         levelNodesCount++;
         printf(" %d ", node->val);

         if(node->left) enqueue(que, node->left);
         if(node->right) enqueue(que, node->right);
         queLength--;
      }      

      printf("] - %d\n", levelNodesCount);
      level++;
   }
   printf("Level: %d\nNodes: %d\n", level, nodeCount);
   
}


void appendIteratively(Node* root, int nodeVals[], int nodeN){
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



void appendRecursively(Node* root, int nodeVals[], int* j){
   
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
      
      else appendRecursively(root->left, nodeVals, j);
   }else if(direction == 2){
      if(root->right == NULL){
         Node* newNode = malloc(sizeof(Node));
         newNode->val = val;
         *j = *j + 1;
         root->right = newNode;
      }
      
      else appendRecursively(root->right, nodeVals, j);
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


/*
0 - 84 - 0 - 51 - 0 - 50 - 0 - 63 - 0 - 63 - 0 - 58 - 0 - 100 - 0 - 68 - 0
 - 59 - 0 - 38 - 0 - 39 - 0 - 25 - 0 - 55 - 0 - 54 - 0 - 500 - 0 - 95 - 0 - 
 94 - 0 - 27 - 0 - 0 - 46 - 0 - 87 - 0 -

             500 
            /     \
         59         46 
      /    \         /\  
  84        25     27  87 
    \       /\     / 
    58     39 54  95   
    / \   /  /     \
  50  68 38  55     94 
  /\   /
51 63 100 
    \
     63 


[ 500 ] - 1
[ 59  46 ] - 2
[ 84  25  27  87 ] - 4
[ 58  39  54  95 ] - 4
[ 50  68  38  55  94 ] - 5
[ 51  63  100 ] - 3
[ 63 ] - 1
Level: 6
Nodes: 20
*/
