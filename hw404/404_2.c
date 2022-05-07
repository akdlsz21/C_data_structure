#include <stdio.h>
#include <stdlib.h>
#include <string.h>

enum {FALSE, TRUE};

typedef struct node {
   char name[5];
   char major[5];
   struct node* next;
   int length;
} Node;


void inputNodes(Node*, Node*);
void seperationOfLists(Node*, Node*, char[]);
void attachNodeToIS(Node*, int, char[]);
void attachNodeToNonIS(Node*, int, char[]);
void printLists(Node*, Node*);
Node* split(Node*);
Node* merge(Node*, Node*);
Node* mergeSort(Node* list);


int main(){
   // Initialize Node and Node
   Node* headOfNonIS = malloc(sizeof(Node));
   headOfNonIS->length = 0;
   Node* headOfIS = malloc(sizeof(Node));
   headOfIS->length = 0;

   // inputNodes(headOfNonIS, headOfIS);
   seperationOfLists(headOfNonIS, headOfIS, "IS/cjh");
   seperationOfLists(headOfNonIS, headOfIS, "CIS/khg");
   seperationOfLists(headOfNonIS, headOfIS, "BIS/dmj");
   seperationOfLists(headOfNonIS, headOfIS, "IS/pok");

   seperationOfLists(headOfNonIS, headOfIS, "AS/abc");
   seperationOfLists(headOfNonIS, headOfIS, "IL/lko");
   seperationOfLists(headOfNonIS, headOfIS, "BS/zxc");
   seperationOfLists(headOfNonIS, headOfIS, "KF/jos");


   printLists(headOfIS, headOfNonIS);

   headOfIS = mergeSort(headOfIS);
   headOfNonIS = mergeSort(headOfNonIS);

   printLists(headOfIS, headOfNonIS);

   Node* mergedList = merge(headOfIS, headOfNonIS);

   printLists(headOfIS, mergedList);


}

Node* split(Node* list){
   int counter = 0;
   Node* grabber = list;
   Node* newList = malloc(sizeof(Node));

   
   while (counter < (list->length)/2){
      grabber = grabber->next;
      counter++;
   }
   newList->length = list->length - counter;
   list->length = counter;

   newList->next = grabber->next;
   grabber->next = NULL;

   return newList;
   
}

Node* addFromList(Node* nextToEnter, Node** list){
   nextToEnter->next = *list;
   (*list) = (*list)->next;
   nextToEnter->next->next = NULL;
   nextToEnter = nextToEnter->next;

   return nextToEnter;
}

Node* merge(Node* list1, Node* list2){
   Node* newList = malloc(sizeof(Node));
   newList->length = list1->length + list2->length;
   Node* nextToEnter = newList;
   list1 = list1->next;
   list2 = list2->next;

   while(list1 && list2){
      if(strcmp(list1->major, list2->major) == 0){
         if(strcmp(list1->name, list2->name) == 0){
            nextToEnter = addFromList(nextToEnter, &list1);
            nextToEnter = addFromList(nextToEnter, &list2);
         }else if(strcmp(list1->name, list2->name) > 0){
            nextToEnter = addFromList(nextToEnter, &list2);
         }else{
            nextToEnter = addFromList(nextToEnter, &list1);
         }
      }else if(strcmp(list1->major, list2->major) > 0){
            nextToEnter = addFromList(nextToEnter, &list2);
      }else{
            nextToEnter = addFromList(nextToEnter, &list1);
      }
   }

   if(list1 != NULL) nextToEnter->next = list1;
   if(list2 != NULL) nextToEnter->next = list2;

   return newList;
}

Node* mergeSort(Node* list){
   if(list->length == 1) return list;
   
   Node* secondHalf = split(list);
   list = mergeSort(list);
   secondHalf = mergeSort(secondHalf);
   return merge(list, secondHalf);
}

void inputNodes(Node* headOfNonIS, Node* headOfIS){
   char buffer[15];

   while(TRUE){
      printf("Enter student Info: seperate with '/', stop with '1'\n");
      scanf("%s", buffer);
      if(buffer[0] == '1') return;

      seperationOfLists(headOfNonIS, headOfIS, buffer);
   }
}

void seperationOfLists(Node* headOfNonIS, Node* headOfIS, char buffer[]){
   char* s;
   int idxOfMajor = 0;
   s = strstr(buffer, "IS");

   if(s != NULL){
      attachNodeToIS(headOfIS, idxOfMajor, buffer);
      headOfIS->length++;
   }else{
      attachNodeToNonIS(headOfNonIS, idxOfMajor, buffer);
      headOfNonIS->length++;
   }
   
}

void attachNodeToIS(Node* headOfIs, int idxOfMajor, char buffer[]){
   Node* temp =  malloc(sizeof(Node));
   char tempMajor[5];
   char tempName[5];

   while(headOfIs->next != NULL){
      headOfIs = headOfIs->next;
   }
   
   for(int i = idxOfMajor; i < 5; i++){
      if(buffer[i] == '/'){
         for(int j = 0; j < 5; j++ ){
            tempName[j] = buffer[i + j + 1];
         }

         break;
      }
      tempMajor[i] = buffer[i];
   }

   strcpy(temp->major, tempMajor);
   strcpy(temp->name, tempName);
   headOfIs->next = temp;
}

void attachNodeToNonIS(Node* headOfNonIS, int idxOfMajor, char buffer[]){
   Node* temp =  malloc(sizeof(Node));
   char tempMajor[5];
   char tempName[5];

   while(headOfNonIS->next != NULL){
      headOfNonIS = headOfNonIS->next;
   }
   
   for(int i = idxOfMajor; i < 5; i++){
      if(buffer[i] == '/'){
         for(int j = 0; j < 5; j++ ){
            tempName[j] = buffer[i + j + 1];
         }

         break;
      }
      tempMajor[i] = buffer[i];
   }

   strcpy(temp->major, tempMajor);
   strcpy(temp->name, tempName);

   headOfNonIS->next = temp;
}

void printLists(Node* headOfIS, Node* headOfNonIS){
   Node* curr = headOfIS->next;
      printf("\n\n\n=========print IS=========\n");
   while(curr != NULL){
      printf("Major: ");
      for(int i = 0; i < 5; i++){
         printf("%c", curr->major[i]);
      }
      printf("\nName: ");
      for(int i = 0; i < 5; i++){
         printf("%c", curr->name[i]);
      }
      printf("\n------\n");
      curr = curr->next;
   }

   curr = headOfNonIS->next;
   printf("\n=========print non IS=========\n");
   while(curr != NULL){
      printf("Major: ");
      for(int i = 0; i < 5; i++){
         printf("%c", curr->major[i]);
      }
      printf("\nName: ");
      for(int i = 0; i < 5; i++){
         printf("%c", curr->name[i]);
      }
      printf("\n------\n");
      curr = curr->next;
   }

}