#include <stdio.h>
#include <stdlib.h>

enum {false, true};

typedef struct node {
   char val;
   struct node* next;
}Node;

typedef struct head{
   struct node* listStart;
} Head;

void inputOps(Head* head);
void fillNodes(Node* node, char val);

int main(){
   // initialize Head
   Head* head = malloc(sizeof(Head));
   Node* node = malloc(sizeof(Node));
   head->listStart = node;

   // input operators and operands
   inputOps(head);

}

void inputOps(Head* head){
   char buffer[5];
   char val;
   int i = 1;

   printf("Enter each node of ops: \n");
   while(true){
      printf("\nEnter #%d node's value  ", i);
      scanf("%c", &buffer);
      if(buffer[0] == 's') break;
      val = buffer[0];
      fillNodes(head->listStart, val);
      i++;
   }
}

void fillNodes(Node* node, char val){
   // Find the endd of the list.
   while(node->next != NULL){
      node = node->next;
   }
   node->val = val;
}