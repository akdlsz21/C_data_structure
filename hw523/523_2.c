#include <stdio.h>
#include <stdlib.h>

#define NUM_OF_VERTECIES 10
#define QUEUE_SIZE 15


typedef struct node{
   int val;
   struct node* next;
}Node;

typedef struct graph{
   int numOfVertecies;
   struct node* adjList[NUM_OF_VERTECIES];
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



int visited[NUM_OF_VERTECIES];




void addEdge(Graph*, int, int);
void printGraph(Graph* graph);
void recursiveDFS(Graph* graph, int vertex);
void enqueue(Queue* queue, int value);
int dequeue(Queue* queue);
int isEmpty(Queue* queue);
int isFull(Queue* queue);
void bfs(Graph* graph, int startVertex);
void iterativeDFS(Graph* graph, int startVertex);
void push(Stack* stack, int val);
int pop(Stack*);
void resetVisited();



int main(){
   Graph* graph = malloc(sizeof(Graph));
   for(int i = 0; i < NUM_OF_VERTECIES; i++) graph->adjList[i] = NULL;
   graph->numOfVertecies = NUM_OF_VERTECIES;

   addEdge(graph, 0, 1);
   addEdge(graph, 0, 2);
   addEdge(graph, 1, 3);
   addEdge(graph, 1, 2);
   addEdge(graph, 2, 4);
   addEdge(graph, 4, 1);
   addEdge(graph, 5, 4);
   addEdge(graph, 6, 5);
   addEdge(graph, 7, 1);
   addEdge(graph, 8, 4);
   addEdge(graph, 8, 5);
   addEdge(graph, 9, 4);
   addEdge(graph, 9, 7);

   printGraph(graph);

   resetVisited();

   puts("recursiveDFS");
   recursiveDFS(graph, 0);

   resetVisited();

   bfs(graph, 0);

   resetVisited();

   iterativeDFS(graph, 0);
   // IterativeDFS does not has the true meaning of DFS.
   // in the console, the next traversal of 7 should be 1.
   // but instead goes back to 8.
   // visited is the reason. Can't know why.

}

void resetVisited(){
   for(int i = 0; i < NUM_OF_VERTECIES; i++)
      visited[i] = 0;
}


void iterativeDFS(Graph* graph, int startVertex){
   printf("\nIterative DFS: \n");
   Stack* stack = malloc(sizeof(Stack));
   stack->stack = malloc(sizeof(int) * 15);

   visited[startVertex] = 1;

   push(stack, startVertex);

   while (stack->length > 0) {

      int currentVertex = pop(stack);

      printf("%d -> ", currentVertex);
      Node* temp = graph->adjList[currentVertex];

      while (temp != NULL) {
         int adjVertex = temp->val;

         if (visited[adjVertex] == 0) {
            visited[adjVertex] = 1;
            push(stack, adjVertex);
         }
         temp = temp->next;
      }
   }
   printf("\n");

}



void bfs(Graph* graph, int startVertex) {
   printf("\nbfs: \n");
  Queue* que = malloc(sizeof(Queue));
  que->data = malloc(sizeof(int) * 20);
  que->front = 0;
  que->rear = 0;
  que->queueSize = 10;

  visited[startVertex] = 1;

  enqueue(que, startVertex);

  while (!isEmpty(que)) {

    int currentVertex = dequeue(que);
   printf("%d -> ", currentVertex);
    Node* temp = graph->adjList[currentVertex];

    while (temp != NULL) {
      int adjVertex = temp->val;

      if (visited[adjVertex] == 0) {
        visited[adjVertex] = 1;
        enqueue(que, adjVertex);
      }
      temp = temp->next;
    }
  }
}




void recursiveDFS(Graph* graph, int vertex){
    Node* curr = graph->adjList[vertex];

    printf("%d -> ",vertex);

    visited[vertex] = 1;
    
    while(curr != NULL)
    {
       vertex = curr->val;

       if(!visited[vertex])
            recursiveDFS(graph, vertex);
        curr = curr->next;
    }

}

void printGraph(Graph* graph){
   for(int i = 0; i < graph->numOfVertecies; i++){
      Node* curr = graph->adjList[i];
      printf("graph->adjList[%d] : ", i);
      while(curr != NULL){
         printf("-> %d ", curr->val);
         curr = curr->next;
      }
      printf("\n");
   }
}

void addEdge(Graph* graph, int src, int dest){
    // Add an edge from src to dest.  A new node is
    // added to the adjacency list of src.  The node
    // is added at the beginning
   Node* check = NULL;
   Node* newNode = malloc(sizeof(Node));
   newNode->val = dest;
   newNode->next = NULL;
   if (graph->adjList[src] == NULL) {
       newNode->next = graph->adjList[src];
       graph->adjList[src] = newNode;
   }
   else {
        check = graph->adjList[src];
       while (check->next != NULL) {
           check = check->next;
       }
       // graph->adjList[src] = newNode;
       check->next = newNode;
   }
    // Since graph is undirected, add an edge from
   // dest to src also
   Node* newNode2 = malloc(sizeof(Node));
   newNode2->val = src;
   newNode2->next = NULL;

   if (graph->adjList[dest] == NULL) {
       newNode2->next = graph->adjList[dest];
       graph->adjList[dest] = newNode2;
   }
   else {
       check = graph->adjList[dest];
       while (check->next != NULL) {
           check = check->next;
       }
       check->next = newNode2;
   }
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


int peek(Stack* stack){
   return stack->stack[stack->length];
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
