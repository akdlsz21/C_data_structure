#include <stdio.h>
#include <stdlib.h>

struct node{
   int val;
   struct node* next;
}Node;

struct adjList{
   struct node* head;
}AdjList;

struct graph{
   int numberOfVerticies;
   struct adjList* arr;
}Graph;


int main(){
   Graph* graph = malloc(sizeof(Graph));
   graph->numberOfVerticies = 10;
   
}