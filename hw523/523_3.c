#include <stdio.h>
#include <stdlib.h>

#define NUM_OF_VERTECIES 10

// Problem of this approach, is that the src and dest
// is stored as an array index, which makes the
// adjList array unefficient.
// the src and dest are two digit numbers, 
// so the list which contains the head of each node
// should be a linked list. 

typedef struct node{
   int val;
   struct node* next;
}Node;

typedef struct graph{
   int numOfVertecies;
   struct node* adjList[NUM_OF_VERTECIES];
}Graph;


int visited[NUM_OF_VERTECIES];


void addEdge(Graph*, int, int);
void printGraph(Graph* graph);
void recursiveDFS(Graph* graph, int vertex);
void graphInit(Graph* graph);
void resetVisited();

int main(){
   Graph* islandNo1 = malloc(sizeof(Graph));
   Graph* islandNo2 = malloc(sizeof(Graph));

   graphInit(islandNo1);
   graphInit(islandNo2);

   addEdge(islandNo1, 3, 4);
   addEdge(islandNo1, 4, 7);
   addEdge(islandNo1, 7, 5);
   addEdge(islandNo1, 5, 6);

   addEdge(islandNo2, 1, 2);
   addEdge(islandNo2, 2, 8);
   addEdge(islandNo2, 8, 0);
   addEdge(islandNo2, 0, 9);
   addEdge(islandNo2, 9, 1);

   recursiveDFS(islandNo1, 4);
   printf("\n");
   resetVisited();
   recursiveDFS(islandNo2, 2);
   printf("\n");

   resetVisited();

}



void recursiveDFS(Graph* graph, int vertex){
    Node* curr = graph->adjList[vertex];

    printf("%d -> ",vertex);

    visited[vertex]=1;
    
    while(curr != NULL)
    {
       vertex = curr->val;

       if(!visited[vertex])
            recursiveDFS(graph, vertex);
        curr = curr->next;
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
(asdf)


void resetVisited(){
   for(int i = 0; i < NUM_OF_VERTECIES; i++)
      visited[i] = 0;
}

void graphInit(Graph* graph){
   for(int i = 0; i < NUM_OF_VERTECIES; i++) graph->adjList[i] = NULL;
   graph->numOfVertecies = NUM_OF_VERTECIES;
}