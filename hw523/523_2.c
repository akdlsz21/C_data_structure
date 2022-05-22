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



int visited[NUM_OF_VERTECIES];




void addEdge(Graph*, int, int);
void printGraph(Graph* graph);
void adListDfs(Graph* graph, int vertex);
void enqueue(Queue* queue, int value);
int dequeue(Queue* queue);
int isEmpty(Queue* queue);
int isFull(Queue* queue);
void bfs(Graph* graph, int startVertex);



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

   for(int i = 0; i < NUM_OF_VERTECIES; i++){
      visited[i] = 0;
   }

   adListDfs(graph, 0);
   for(int i = 0; i < NUM_OF_VERTECIES; i++){
      visited[i] = 0;
   }
   bfs(graph, 0);

}

void bfs(Graph* graph, int startVertex) {
   printf("\nbfs: \n");
  Queue* que = malloc(sizeof(Queue));
  que->data = malloc(sizeof(int) * 10);
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




void adListDfs(Graph* graph, int vertex){
    Node* curr = graph->adjList[vertex];

    printf("%d -> ",vertex);

    visited[vertex]=1;
    
    while(curr != NULL)
    {
       vertex = curr->val;

       if(!visited[vertex])
            adListDfs(graph, vertex);
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
