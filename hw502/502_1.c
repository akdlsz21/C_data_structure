#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct _node{
   int val;
   struct _node* next;
}Node;

typedef struct list{
   struct _node* head;
   int length;
}List;


void add(List**, int);
void push(List**, int);
List* mergeSort(List* list);
List* merge(List*, List*);
List* split(List* list);
void printList(List* list);
void attachTwoLists(List**, List**);
void printListHead(Node* head, int);
void mergeSortT(List**);
void sortEvenList(Node**);
void frontBackSplit(Node* source, Node** frontRef, Node** backRef);
Node* SortedMerge(Node* a, Node* b);


void main(){
   List* evenList = malloc(sizeof(List));
   List* oddList = malloc(sizeof(List));
   evenList->length = 0;
   oddList->length = 0;

   srand(time(NULL));

   for(int i = 0; i < 20; i++){
      int num = rand() % 50 + 1;
      if(num % 2 == 0)add(&evenList, num);
      else add(&oddList, num);
   }


   printList(evenList);
   printList(oddList);

   attachTwoLists(&evenList, &oddList);
   printList(evenList);

   Node* evenListHead = evenList->head;
   sortEvenList(&evenListHead);

   evenList->head = evenListHead;
   printList(evenList);

}

void sortEvenList(Node** headRef){
   Node* head = *headRef;
   Node* a;
   Node* b;

   if(head == NULL || head->next == NULL) return;

   frontBackSplit(head, &a, &b);
   sortEvenList(&a);
   sortEvenList(&b);

   *headRef = SortedMerge(a, b);
}

Node* SortedMerge(Node* a, Node* b){

   Node* result = NULL;

   if(a == NULL) return b;
   else if(b == NULL) return a;

   if(a->val <= b->val){
      result = a;
      result->next = SortedMerge(a->next, b);
   }else{
      result = b;
      result->next = SortedMerge(a, b->next);
   }

   return result;

}

void frontBackSplit(Node* source, Node** frontRef, Node** backRef){

   Node* slow;
   Node* fast;
   slow = source;
   fast = source->next;


   while(fast != NULL){
      fast = fast->next;
      if(fast != NULL){
         slow = slow->next;
         fast = fast->next;
      }


   }
      *frontRef = source;
      *backRef = slow->next;
      slow->next = NULL;

}

void attachTwoLists(List** evenList, List** oddList){
   Node* evenListHead = (*evenList)->head;
   Node* prev = NULL;
   Node* head = (*evenList)->head;
   while(head != NULL){
      prev = head;
      head = head->next;
   }
   prev->next = (*oddList)->head;
   
   printf("merge two lists");
   (*evenList)->head = evenListHead;
   (*evenList)->head = evenListHead;
   (*evenList)->length += (*oddList)->length;
   printListHead(evenListHead, (*evenList)->length);

}


void printListHead(Node* node, int l){
   printf("\n");
   for(int i = 0; i < l;i++){
      printf("%d -> ", node->val);
      node = node->next;
   }
   printf("\n");

}



void add(List** list, int num){
   (*list)->length++;
   push(list, num);
}

void push(List** list, int num){
   if((*list)->head == NULL){
      Node* newNode = malloc(sizeof(Node));
      newNode->val = num;
      (*list)->head = newNode;
   }else{
      Node* newNode = malloc(sizeof(Node));
      newNode->val = num;


      Node* listHead = (*list)->head;
      while(listHead->next){
         listHead = listHead->next;
      }
      listHead->next = newNode;

   }


   *list = mergeSort(*list);
   }

List* mergeSort(List* list){
   if(list->length == 1) return list;

   List* secondHalf = split(list);
   list = mergeSort(list);
   secondHalf = mergeSort(secondHalf);
   return merge(list, secondHalf);
}


List* split(List* list){
   int count = 0;

   Node* head = list->head;
   Node* prev = NULL;
   for(; count < list->length/2; count++){
      prev = head;
      head = head->next;

   } 
   List* newList = malloc(sizeof(List));
   newList->head = head;
   newList->length = list->length - count;
   prev->next = NULL;


   list->length = count;
   return newList;
}

List* merge(List* list1, List* list2){
   List* newList = malloc(sizeof(List));
   newList->length = list1->length + list2->length;
   newList->head = NULL;

   Node* newListHead = newList->head;
   Node* newListHeadPtr = newListHead;

   Node* list1Head = list1->head;
   Node* list2Head = list2->head;

   while(list1Head && list2Head){
      if(list1Head->val < list2Head->val){
         if(!newListHead){
            newListHead = list2Head;
            newListHeadPtr = newListHead;
         }else{
            newListHead->next = list2Head;
            newListHead = newListHead->next;
         }
         list2Head = list2Head->next;
      }else if(list1Head->val >= list2Head->val){
         if(!newListHead){
            newListHead = list1Head;
            newListHeadPtr = newListHead;
         }else{
            newListHead->next = list1Head;
            newListHead = newListHead->next;
         }
         list1Head = list1Head->next;
      }
   }
   if(!list1Head){
      newListHead->next = list2Head;
   }
   if(!list2Head){
      newListHead->next = list1Head;
   }
   newList->head = newListHeadPtr;

   return newList;

}

void printList(List* list){
   Node* listHead = list->head;
   printf("\n");
   for(int i = 0; i < list->length;i++){
      printf("%d -> ", listHead->val);
      listHead = listHead->next;
   }
   printf("\n");

}