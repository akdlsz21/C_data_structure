#include <stdio.h>
#include <stdlib.h>

#define MAX_VERTICIES 10
#define QUEUE_SIZE 15

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

typedef struct _graph{
   int n;
   int adj_mat[MAX_VERTICIES][MAX_VERTICIES];
}Graph;

int visited[MAX_VERTICIES];


void insertEdge(Graph* graph, int start, int end);
void printMatrix(Graph* graph);
void matrixRecursiveDfs(Graph* graph, int v);
void push(Stack* stack, int val);
int pop(Stack*);
int peek(Stack*);
void matrixIterativeDfs(Graph* graph);
void enqueue(Queue* queue, int value);
int dequeue(Queue* queue);
int isEmpty(Queue* queue);
int isFull(Queue* queue);


int main(){
   Graph* graph = malloc(sizeof(Graph));
   graph->n = 10;

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
   printf("\n");

   matrixRecursiveDfs(graph, 0);
   printf("\n");

   for(int i = 0; i < MAX_VERTICIES; i++)
      visited[i] = 0;


   matrixIterativeDfs(graph);

   for(int i = 0; i < MAX_VERTICIES; i++)
      visited[i] = 0;

   matrixBfs(graph);

}

void matrixBfs(Graph* graph){
   Queue* que = malloc(sizeof(Queue));
   que->front = 0;
   que->rear = 0;
   que->queueSize = 10;
   que->data = malloc(sizeof(int) * 15);

   enqueue(que, 0);

   while(!isEmpty(que)){
      int curr = dequeue(que);

      if(visited[curr] == 0){
         visited[curr] = 1;
         printf("Vertex:%d -> ", curr);

         for(int i = 0; i < MAX_VERTICIES; i++)
            if(graph->adj_mat[curr][i] == 1 && !visited[i]) 
               enqueue(que, i);
      }
   }
   printf("\n");
}


void matrixIterativeDfs(Graph* graph){

   Stack* stack = malloc(sizeof(Stack));
   stack->length = 0;
   stack->stack = malloc(sizeof(int) * 10);
   push(stack, 0);

   while(stack->length > 0){
      int curr = pop(stack);

      if(visited[curr] == 0){
         visited[curr] = 1;
         printf("vertex:%d -> ", curr );

         for(int i = 0; i < MAX_VERTICIES; i++)
            if(graph->adj_mat[curr][i] == 1 && !visited[i]) {
               push(stack, i);
            }
      }
   }
   printf("\n");
}


int peek(Stack* stack){
   return stack->stack[stack->length];
}

void insertEdge(Graph* graph, int start, int end){
   if(start > graph->n || end > graph->n){
      fprintf(stderr, "Pizza pops" );
   }

   graph->adj_mat[start][end] = 1;
   graph->adj_mat[end][start] = 1;
}

void printMatrix(Graph* graph){
   for(int i = 0; i < graph->n; i++){
      for(int j = 0; j < graph->n; j++){
         printf("%2d", graph->adj_mat[i][j]);
      }
      printf("\n");
   }
}

void matrixRecursiveDfs(Graph* graph, int v){
   visited[v] = 1;
   printf("Vertex:%d -> ", v);
   for(int i = 0; i < graph->n; i++){
      if(graph->adj_mat[v][i] && !visited[i]){
         matrixRecursiveDfs(graph, i);
      }
   }
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



// Matrix DFS 
// Vertex:0 -> Vertex:1 -> Vertex:2 -> Vertex:4 -> Vertex:5 -> Vertex:6 -> Vertex:8 -> Vertex:9 -> Vertex:7 -> Vertex:3 -> 