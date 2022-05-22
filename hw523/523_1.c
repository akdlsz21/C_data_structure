#include <stdio.h>
#include <stdlib.h>

#define MAX_VERTICIES 10

typedef struct _graph{
   int n;
   int adj_mat[MAX_VERTICIES][MAX_VERTICIES];
}Graph;

int visited[MAX_VERTICIES];


void insertEdge(Graph* graph, int start, int end);
void printMatrix(Graph* graph);
void matrixRecursiveDfs(Graph* graph, int v);


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
   int w;
   visited[v] = 1;
   printf("Vertex:%d -> ", v);
   for(w = 0; w < graph->n; w++){
      if(graph->adj_mat[v][w] && !visited[w]){
         matrixRecursiveDfs(graph, w);
      }
   }
}




// Matrix DFS 
// Vertex:0 -> Vertex:1 -> Vertex:2 -> Vertex:4 -> Vertex:5 -> Vertex:6 -> Vertex:8 -> Vertex:9 -> Vertex:7 -> Vertex:3 -> 