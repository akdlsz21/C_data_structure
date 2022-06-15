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

typedef struct node{
   int val;
   struct node* next;

}Node;

typedef struct g{
   int n;
   struct node* list[MAX_VERTICIES];
}Graph;

int visited[MAX_VERTICIES];



void push(Stack* stack, int val);
int pop(Stack*);
int peek(Stack*);
void enqueue(Queue* queue, int value);
int dequeue(Queue* queue);
int isEmpty(Queue* queue);
int isFull(Queue* queue);

void resetVisited();
void addEdge(Graph* graph, int src, int des);
void printGraph(Graph* graph);
void recursiveDFS(Graph* graph, int vertex);
void iterativeDFS(Graph* graph, int startVertex);
void bfs(Graph* graph, int start);

int main(){
   Graph* graph = malloc(sizeof(Graph));
   graph->n = 10;

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

   iterativeDFS(graph, 0);
   resetVisited();
   printf("\n");

   bfs(graph, 0);
}

void bfs(Graph* graph, int start){
   printf("\nbfs: \n");
  Queue* que = malloc(sizeof(Queue));
  que->data = malloc(sizeof(int) * 20);
  que->front = 0;
  que->rear = 0;
  que->queueSize = 10;

   visited[start] = 1;

   enqueue(que, start);

   while(!isEmpty(que)){
      int curr = dequeue(que);
      printf("%d -> ", curr);

      Node* temp = graph->list[curr];
      while(temp != NULL){
         if(!visited[temp->val]){
            visited[temp->val] = 1;
            enqueue(que, temp->val);
         }

         temp = temp->next;
      }
   }
}


void iterativeDFS(Graph* graph, int val){
   printf("\nIterative DFS\n");
   Stack* stack = malloc(sizeof(Stack));
   stack->stack = malloc(sizeof(int) * 15);
   stack->length = 0;

   visited[val] = 1;

   push(stack, val);

   while(stack->length > 0){
      int curr = pop(stack);

      printf("%d -> ", curr);
      Node* temp = graph->list[curr];

      while(temp != NULL){
         int adjVertex = temp->val;

         if(visited[adjVertex] == 0){
            visited[adjVertex] = 1;
            push(stack, adjVertex);
         }

         temp = temp->next;
      }
   }
   while(stack->length > 0){
      int curr = pop(stack);

      if(!visited[curr]){
         visited[curr] = 1;
         printf("%d -> ", curr);
         
         Node* temp = graph->list[curr];

         while(temp != NULL){
            if(visited[temp->val] == 0){
               visited[temp->val] = 1;
               push(stack, temp->val);
            }
            temp = temp->next;
         }
         
      }
   }
}

void recursiveDFS(Graph* graph, int vertex){
   Node* curr = graph->list[vertex];

   printf("%d -> ", vertex);

   visited[vertex] = 1;

   while(curr != NULL){
      vertex = curr->val;
      if(visited[vertex] == 0){
         recursiveDFS(graph, vertex);

      }
      curr = curr->next;
   }
}

void printGraph(Graph* graph){
   for(int i = 0; i < graph->n; i++){
      Node* curr = graph->list[i];
      printf("graph->list[%d] : ", i);
      while(curr != NULL){
         printf("-> %d ", curr->val);
         curr = curr->next;
      }
      printf("\n");
   }
}


void addEdge(Graph* graph, int src, int des){
   Node* traverseTemp = NULL;

   Node* newNode = malloc(sizeof(Node));
   newNode->val = des;

   if(graph->list[src] == NULL){
      newNode->next = graph->list[src];
      graph->list[src] = newNode;
   }else{
      traverseTemp = graph->list[src];
      while(traverseTemp->next != NULL) traverseTemp = traverseTemp->next;
      traverseTemp->next = newNode;

   }

   Node* newNode2 = malloc(sizeof(Node));
   newNode2->val = src;

   if(graph->list[des] == NULL){
      newNode2->next = graph->list[des];
      graph->list[des] = newNode2;
   }else{
      traverseTemp = graph->list[des];
      while(traverseTemp->next != NULL)
         traverseTemp = traverseTemp->next;
      traverseTemp->next = newNode2;
   }



}

void resetVisited(){
   for(int i = 0; i < MAX_VERTICIES; i++)
      visited[i] = 0;
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


