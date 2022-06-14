#include <stdio.h>
#include <stdlib.h>

// make a program which implements krugal algorithm with nodes which are strings of characters
// and edges which are integers

#define max_edges 10

typedef struct _node {
   char* name;
   int* neighbors[max_edges];
}Node;

typedef struct _graph{
   int adj_matrix[max_edges][max_edges];
}Graph;

void insert_edges(Graph *g, char* cities, int src, int des, int weight);
void init_graph(Graph *g);
void print_matrix(Graph *g);

int main(){
   char* cities[10] = {"seoul", "incheon", "suwon", "chuncheon", "donghae", "dongsong", "cheongju", "chunju", "pusan", "jejo" };
   Graph* graph = malloc(sizeof(Graph));
   init_graph(graph);

   insert_edges(graph, cities, 0, 1, 3);
   insert_edges(graph, cities, 1, 2, 4);
   insert_edges(graph, cities, 0, 3, 5);
   insert_edges(graph, cities, 3, 4, 7);
   insert_edges(graph, cities, 4, 5, 10);
   insert_edges(graph, cities, 3, 6, 11);
   insert_edges(graph, cities, 6, 7, 10);
   insert_edges(graph, cities, 6, 8, 8);
   insert_edges(graph, cities, 7, 8, 9);
   insert_edges(graph, cities, 7, 9, 21);

   print_matrix(graph);
}

void insert_edges(Graph *g, char* cities, int src, int des, int weight){
   g->adj_matrix[src][des] = weight;
   g->adj_matrix[des][src] = weight;
}

void init_graph(Graph *g){
   int i, j;
   for(i = 0; i < max_edges; i++){
      for(j = 0; j < max_edges; j++){
         g->adj_matrix[i][j] = 0;
      }
   }
}

void print_matrix(Graph* g){
   int i, j;
   for(i = 0; i < max_edges; i++){
      for(j = 0; j < max_edges; j++){
         printf("%d ", g->adj_matrix[i][j]);
      }
      printf("\n");
   }
}