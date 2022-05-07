#include <stdio.h>
#include <stdlib.h>
#include <time.h>


typedef struct nodeArray{
   struct list** array;
   struct list** transArr;
}NodeArray;

typedef struct list{
   int val;
   struct list* next;
}Node;




void printNodes(NodeArray* nodeArray, int, int);
void fillNodes(NodeArray*, int, int);
void transposeNodes(NodeArray* nodeArray, int row, int col);
void setNodePointerToTransArr(NodeArray* nodeArray, int row, int col);
void printTransNodes(NodeArray* nodeArray, int row, int col);


int main(){
   srand(time(NULL));
   NodeArray* nodeArray = malloc(sizeof(NodeArray));
   int row = 3;
   int col = 4;
   nodeArray->array = malloc(sizeof(Node) * row);
   nodeArray->transArr = malloc(sizeof(Node) * col);
   

   for(int i = 0; i < row; i++){
      fillNodes(nodeArray, i, col);
   }
   printNodes(nodeArray, row, col);
   setNodePointerToTransArr(nodeArray, row, col);
   transposeNodes(nodeArray, row, col);
   printTransNodes(nodeArray, row, col);

}

void printTransNodes(NodeArray* nodeArray, int row, int col){
   printf("\n==========================\n");
   for(int i = 0; i < col; i++){
      Node* head = nodeArray->transArr[i];
      printf("[%d]:", i);
      
      for(int j = 0; j < row; j++){
         printf("( %d ) -> ", head->val);
         head = head->next;
      }
      printf("\n");
   }

}

void setNodePointerToTransArr(NodeArray* nodeArray, int row, int col){
   Node* head = nodeArray->array[0];
   // for(int i = 0; i < col; i++){
   //    nodeArray->transArr[i] = head;
   //    if(i == col - 1) break;
   //    head = head->next;
   // }
   nodeArray->transArr[0] = head;
   head = head->next;
   nodeArray->transArr[1] = head;
   head = head->next;
   nodeArray->transArr[2] = head;
   head = head->next;
   nodeArray->transArr[3] = head;
}

void transposeNodes(NodeArray* nodeArray, int row, int col){
   for(int i = 0; i < row; i++){
      Node* head = nodeArray->array[i];
      for(int j = 0; j < col; j++){
         Node* nextHead = nodeArray->array[i+1];
         if(i + 1 == row){
            Node* prev = head;
            if(head->next == NULL) head->next = NULL;
            prev->next = NULL; 
         }else{
            head->next = nextHead;
            head = head->next;
            nextHead = nextHead->next;
         }

      }
      
   }
}

void printNodes(NodeArray* nodeArray, int row, int col){
   for(int i = 0; i < row; i++){
      Node* head = nodeArray->array[i];
      printf("[%d]:", i);

      for(int j = 0; j < col; j++){
         printf("( %d ) -> ", head->val);
         head = head->next;
      }
      printf("\n");
   }

}

void fillNodes(NodeArray* nodeArray, int i, int col){
   nodeArray->array[i] = malloc(sizeof(Node));
   Node* head = nodeArray->array[i];
   head->val = rand() % 10 + 1;
   col--;
   while(col != 0){
      head->next = malloc(sizeof(Node));
      head = head->next;
      head->val = rand() % 10 + 1;
      col--;
   }
}