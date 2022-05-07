#include <stdlib.h>
#include <stdio.h>
#include <time.h>

int MAX_SIZE = 20;

typedef struct queue{
   int data[10];
   int front;
   int rear;
}Queue;

void randomEnqueueAndDequeue(Queue* queue, int oneOrTwo[], int oneToHundred[]);
void enqueue(Queue* queue, int value);
int dequeue(Queue* queue);
int isEmpty(Queue* queue);
int isFull(Queue* queue);
void printQueueAndOperations(Queue* queue, int oneOrTwo[], int oneToHundred[]);


int main(){
   Queue* queue = malloc(sizeof(Queue));
   queue->front = 0;
   queue->rear = 0;
   int oneOrTwo[MAX_SIZE];
   int oneToHundred[MAX_SIZE];

   srand(time(NULL));

   randomEnqueueAndDequeue(queue, oneOrTwo, oneToHundred);

   printQueueAndOperations(queue, oneOrTwo, oneToHundred);

}

void randomEnqueueAndDequeue(Queue* queue, int oneOrTwo[], int oneToHundred[]){
   for(int i = 0; i < MAX_SIZE; i++){
      // random integers
      oneOrTwo[i] = rand() % 2 + 1;
      oneToHundred[i] = rand() % 100 + 1;
      
      if(oneOrTwo[i] == 1 || oneOrTwo[i] == 3) enqueue(queue, oneToHundred[i]);
      else dequeue(queue);
   }
}

void printQueueAndOperations(Queue* queue, int oneOrTwo[], int oneToHundred[]){
   printf("\nOperations: ");
   for(int i = 0; i < MAX_SIZE; i++){
      if(oneOrTwo[i] == 1 || oneOrTwo[i] == 3) printf("Enq, ");
      else if(oneOrTwo[i] == 2) printf("Deq, ");
   }

   printf("\n    Values: ");
   for(int i = 0; i < MAX_SIZE; i++){
      if(oneToHundred[i] < 10){
         printf("%d  | ", oneToHundred[i]);
      }else{
         printf("%d | ", oneToHundred[i]);
      }
   }

   puts("\n\n----------Print Queue----------");
   for(int j = queue->front; (j % 10) != (queue->rear) % 10 + 1; j++){
      printf("%d | ", queue->data[j]);
   }
   puts("\n----------Print Queue----------\n\n");

}

void enqueue(Queue* queue, int value){
   if(!isFull(queue)){
      queue->rear = (queue->rear + 1) % 10;
      queue->data[queue->rear] = value;
   }else{
      printf("Enqueue Failed: queue is Full\n");
   }
}

int dequeue(Queue* queue){
   int returnVal;
   if(!isEmpty(queue)){
      queue->front = (queue->front + 1) % 10;

      returnVal = queue->data[queue->front];
      queue->data[queue->front] = -1;
      return returnVal;
   }else{
      printf("Dequeue Failed: queue is Empty\n");
   }
}

int isEmpty(Queue* queue){
   return queue->front == queue->rear;
}

int isFull(Queue* queue){
   return ((queue->rear + 1) % 10 == queue->front);
}


/*

Dequeue Failed: queue is Empty
Dequeue Failed: queue is Empty
Dequeue Failed: queue is Empty
Dequeue Failed: queue is Empty
Dequeue Failed: queue is Empty

Operations: Deq, Deq, Deq, Enq, Enq, Deq, Enq, Deq, Deq, Enq, Deq, Deq, Deq, Enq, Enq, Enq, Enq, Deq, Enq, Enq, 
    Values: 65 | 18 | 40 | 22 | 69 | 57 | 76 | 74 | 72 | 39 | 88 | 23 | 73 | 47 | 95 | 71 | 68 | 94 | 82 | 6  | 

----------Print Queue----------
-1 | 95 | 71 | 68 | 82 | 6 |
----------Print Queue----------

*/