#include <stdlib.h>
#include <stdio.h>
#include <time.h>

typedef struct node{
   int value;
   struct node* next;
}Node;

typedef struct queue{
   struct node* front;
   struct node* rear;
}Queue;

void randomEnqueueAndDequeue(Queue* queue, int oneOrTwo[], int oneToHundred[]);
void enqueue(Queue* queue, int value);
int dequeue(Queue* queue);
void printQueue(Queue* queue);
void printOperators(int[], int[]);



int main(){
   int oneOrTwo[20];
   int oneToHundred[20];
   Queue* queue = malloc(sizeof(Queue));
   queue->front = NULL;
   queue->rear = NULL;

   srand(time(NULL));

   randomEnqueueAndDequeue(queue, oneOrTwo, oneToHundred);
   printQueue(queue);
   printOperators(oneOrTwo, oneToHundred);


}

void printOperators(int oneOrTwo[], int oneToHundred[]){

   for(int i = 0; i < 20; i++){
      printf("%d |", oneToHundred[i]);
   }
   printf("\n");
   for(int i = 0; i < 20; i++){
      if(oneOrTwo[i] == 1){
         printf("Eq |");
      }else{
         printf("Dq |");
      }
   }
   printf("\n");

}

void randomEnqueueAndDequeue(Queue* queue, int oneOrTwo[], int oneToHundred[]){
   for(int i = 0; i < 20; i++){
      oneOrTwo[i] = rand() % 2 + 1;
      oneToHundred[i] = rand() % 100 + 1;
   }

   for(int i = 0; i < 20; i++){
      if(oneOrTwo[i] == 1){
         enqueue(queue, oneToHundred[i]);
      }else{
         dequeue(queue);
      }
   }

}

void enqueue(Queue* queue, int value){
   Node* newNode = malloc(sizeof(Node));
   newNode->value = value;
   if(queue->front == NULL){
      queue->front = newNode;
   }else{
      queue->rear->next = newNode;
   }

   queue->rear = newNode;
   queue->rear->next = queue->front;
}

int dequeue(Queue* queue){
   int returnValue;

   if(queue->front == NULL){
      printf("Queue is currently empty\n");
      return -1;
   }

   // Last Node where front and rear is the same address
   if(queue->front == queue->rear){
      returnValue = queue->front->value;
      free(queue->front);
      queue->front = NULL;
      queue->rear = NULL;
   }else{
      // case of there are more nodes to be dequeued,
      Node* tempNode = queue->front;
      returnValue = tempNode->value;
      queue->front = queue->front->next;
      queue->rear->next = queue->front;
      free(tempNode);
   }

   return returnValue;
}

void printQueue(Queue* queue){
   if(queue->front == NULL){
      printf("\nThere is Nothing to print\n\n");
      return;
   }
   Node* tempNode = queue->front;
   printf("\n------------------------------\n");
   
   // react to rear. rear has a pointer pointing to front
   while(tempNode->next != queue->front){
      printf("%d | ", tempNode->value);
      tempNode = tempNode->next;
   }

   // tempNode is currently rear, and did not print the value.
   printf("%d", tempNode->value);
   printf("\n------------------------------\n");

}



// 71 |62 |3  |15 |15 |1  |48 |15 |5  |88 |22 |10 |81 |28 |7  |16 |57 |99 |49 |81 |
// Dq |Eq |Eq |Dq |Eq |Dq |Dq |Eq |Dq |Eq |Eq |Eq |Eq |Dq |Eq |Dq |Eq |Eq |Eq |Eq |
//   10 81 7 57 99 49 81
// Queue is currently empty

// ------------------------------
// 10 | 81 | 7 | 57 | 99 | 49 | 81
// ------------------------------