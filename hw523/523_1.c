#include <stdio.h>
#include <stdlib.h>

#define MAX_VERTICIES 10

typedef struct _graph{
   int n;
   int adj_mat[MAX_VERTICIES][MAX_VERTICIES];
}Graph;

typedef struct _stack {
   int* stack;
   int length;
}Stack;


int visited[MAX_VERTICIES];


void insertEdge(Graph* graph, int start, int end);
void printMatrix(Graph* graph);
void matrixRecursiveDfs(Graph* graph, int v);
void push(Stack* stack, int val);
int pop(Stack*);
void matrixIterativeDfs(Graph* graph);
int peek(Stack*);

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


}

void matrixIterativeDfs(Graph* graph){

   Stack* stack = malloc(sizeof(Stack));
   stack->length = 0;
   stack->stack = malloc(sizeof(int) * 10);
   push(stack, 0);
   visited[0] = 1;
   while(stack->length != 0){

      int curr = pop(stack);
      visited[curr] = 1;
      printf("vertex:%d -> ", curr );

      for(int i = 0; i < MAX_VERTICIES; i++){
         if(graph->adj_mat[curr][i] == 1 && !visited[i]){
            if(visited[i]) continue;
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
   for(int w = 0; w < graph->n; w++){
      if(graph->adj_mat[v][w] && !visited[w]){
         matrixRecursiveDfs(graph, w);
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




// Matrix DFS 
// Vertex:0 -> Vertex:1 -> Vertex:2 -> Vertex:4 -> Vertex:5 -> Vertex:6 -> Vertex:8 -> Vertex:9 -> Vertex:7 -> Vertex:3 -> 