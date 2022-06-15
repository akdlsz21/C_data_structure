#include <stdio.h>
#include <stdlib.h>

#define MAX_NUMS 10
#define QUEUE_SIZE 15


typedef struct g{
   int matrix[MAX_NUMS][MAX_NUMS];
   int n;
}Graph;

typedef struct queue{
   int* data;
   int front;
   int rear;
   int queueSize;
}Queue;


typedef struct _stack {
   int* stack;
   int length;
}Stack;

int visited[MAX_NUMS];


void insertEdge(Graph* g, int src, int des);
void printMatrix(Graph* g);
void matrixRecursiveDfs(Graph* g, int val);
void push(Stack* stack, int val);
int pop(Stack*);
int peek(Stack*);
void enqueue(Queue* queue, int value);
int dequeue(Queue* queue);
int isEmpty(Queue* queue);
int isFull(Queue* queue);
void matrixDfsStack(Graph* g, int v);
void resetVisited();
void matrixBfs(Graph* graph, int val);


int main(){
   Graph* graph = malloc(sizeof(Graph));
   graph->n = MAX_NUMS;

   insertEdge(graph, 0, 1);
   insertEdge(graph, 0, 2);
   insertEdge(graph, 1, 3);
   insertEdge(graph, 1, 2);
   insertEdge(graph, 2, 4);
   insertEdge(graph, 4, 1);
   insertEdge(graph, 5, 4);
   insertEdge(graph, 6, 5);
   insertEdge(graph, 7, 1);
   insertEdge(graph, 8, 4);
   insertEdge(graph, 8, 5);
   insertEdge(graph, 9, 4);
   insertEdge(graph, 9, 7);


   printMatrix(graph);
   matrixRecursiveDfs(graph, 0);
   printf("\n");
   resetVisited();
   matrixDfsStack(graph, 0);
   resetVisited();
   matrixBfs(graph, 0);

}

void matrixBfs(Graph* graph, int val){
   Queue* que = malloc(sizeof(Queue));
   que->front = 0;
   que->rear = 0;
   que->queueSize = 10;
   que->data = malloc(sizeof(int) * 15);

   enqueue(que, val);

   while(!isEmpty(que)){
      int curr = dequeue(que);

      if(!visited[curr]){
         visited[curr] = 1;
         printf("V:%d -> ", curr);

         for(int i = 0; i < MAX_NUMS; i++){
            if(graph->matrix[curr][i] && !visited[i]){
               enqueue(que, i);
            }
         }
         
      }
   }

   printf("\n");
}



void matrixDfsStack(Graph* graph, int val){
   Stack* stack = malloc(sizeof(Stack));
   stack->length = 0; 
   stack->stack = malloc(sizeof(int) * 10);
   push(stack, val);

   while(stack->length > 0){
      int curr = pop(stack);

      if(visited[curr] == 0){
         visited[curr] = 1;
         printf("V:%d -> ", curr );

         for(int i = 0; i < MAX_NUMS; i++){
            if(graph->matrix[curr][i] == 1 && visited[i] == 0){
               push(stack, i);
            }
         }
      }
   }

      printf("\n");

}




void resetVisited(){
   for(int i = 0; i < MAX_NUMS; i++){
      visited[i] = 0;
   }
}

void matrixRecursiveDfs(Graph* graph, int val){
   visited[val] = 1;
   printf("V:%d -> ", val);

   for(int i = 0; i < MAX_NUMS; i++){
      if(graph->matrix[val][i] == 1 && visited[i] == 0)
         matrixRecursiveDfs(graph, i);
   }
}


void printMatrix(Graph* g){
   for(int i = 0; i < MAX_NUMS; i++){
      for(int j = 0; j < MAX_NUMS; j++){
         printf("%2d", g->matrix[i][j]);
      }
      printf("\n");
   }

   printf("\n\n");
}

void insertEdge(Graph* g, int src, int des){
   g->matrix[src][des] = 1;
   g->matrix[des][src] = 1;
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


void enqueue(Queue* queue, int value){
   if(!isFull(queue)){
      queue->rear = (queue->rear + 1) % QUEUE_SIZE;
      queue->data[queue->rear] = value;
   }else{
      printf("Enqueue Failed: queue is Full\n");
   }
}

int dequeue(Queue* queue){
   int returnVal;
   if(!isEmpty(queue)){
      queue->front = (queue->front + 1) % QUEUE_SIZE;

      returnVal = queue->data[queue->front];
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