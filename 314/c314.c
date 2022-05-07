#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define TRUE 1
#define FALSE 0


typedef struct book {
   char title[20];
   char author[20];
   int price;
   int year;
   int month;
} Book;

typedef enum _groups {Before2000, After2000} groups;

typedef struct node {
   Book* value;
   struct node* next;
} Node;

// Prototypes
void createBook(Book* book, char* title, char* author, int year, int month, int price);
void printBook(Book* book);
groups classify_book(Book* book);
void storeBook(Node* headOfBefore2000, Node* headOfAfter2000, Book* book);
void printList(Node* list); 
void find_next(Node** head);


int main(){
   srand(0);
   Book bookArray[10];
   char tempTitle[20];
   char tempAuthor[20];

   // Create book array
   for (int i = 0; i < 10; i++){
      sprintf(tempTitle, "Circle_%d", i);
      sprintf(tempAuthor, "Clone_%d", i);
      createBook(&bookArray[i], tempTitle, tempAuthor, (1980 + rand() % 43), (1 + rand() % 12), i * 1000);
   }

   // Create empty nodes for group Before2000 and After2000
   Node* headOfBefore2000 = malloc(sizeof(Node));
   headOfBefore2000->value = NULL;
   headOfBefore2000->next = NULL;
   Node* headOfAfter2000 = malloc(sizeof(Node));
   headOfAfter2000->value = NULL;
   headOfAfter2000->next = NULL;

   for(int i = 0; i < 10; i++){
      storeBook(headOfBefore2000, headOfAfter2000, &bookArray[i]);
   }

   mergeLists(headOfAfter2000, headOfBefore2000);

   for (size_t i = 0; i < 10; i++)
   {
      printf("%s\n", headOfAfter2000->value->title);
      find_next(&headOfAfter2000);
   }

   return 0;
}


// Function to create a book
void createBook(Book* book, char* title, char* author, int year, int month, int price){
   strcpy(book->title, title);
   strcpy(book->author, author);
   book->year = year;
   book->month = month;
   book->price = price;
   return;
}

void printBook(Book* book){
   char date[8];
   sprintf(date,"%d/%d", book->year,book->month);
   printf("{title : %s, author : %s, date : %s, price : %d}\n", book->title, book->author, date, book->price);
}

groups classify_book(Book* book){
   if(book->year < 2000) return Before2000;
   return After2000;
}

int compareYearOfNodes(Book* newBook, Book* existingBook){
   if(newBook->year > existingBook->year) return FALSE;
   else if(newBook->year < existingBook->year) return TRUE;

   if(newBook->month > existingBook->month) return FALSE;
   return TRUE;
}

void addToList(Node* node, Book* newBook){
   // Finding correct position of newBook
   while(node->next != NULL && compareYearOfNodes(newBook, node->value)){
      node = node->next;
   }

   Node* newNode = malloc(sizeof(Node));
   if(node->next == NULL){ // end of Group
      node->value = newBook;
      newNode->next = NULL;
      newNode->value = NULL;
      node->next = newNode;
   }else{ // Not end of group
      //
      newNode->value = node->value;
      newNode->next = node->next;
      node->next = newNode;
      node->value = newBook;
   }
}

void storeBook(Node* headOfBefore2000, Node* headOfAfter2000, Book* book){
   if(classify_book(book) == Before2000){
      addToList(headOfBefore2000, book);
   }else{
      addToList(headOfAfter2000, book);
   }
}

void printList(Node* list){
   while(list->next){
      printf("%s ",list->value->title);
      printf("%d %d\n",list->value->year, list->value->month);
      list = list->next;
   }
}

void mergeLists(Node* headOfAfter2000, Node* headOfBefore2000){
   if(headOfAfter2000->next == NULL){// Checking whether headOfAfter list is empty
      headOfAfter2000->value = headOfBefore2000->value;
      headOfAfter2000->next = headOfBefore2000->next;

      return ;
   }
   while(headOfAfter2000->next->next != NULL){
      headOfAfter2000 = headOfAfter2000->next;
   }
   // free memory of empty node of group after
   free(headOfAfter2000->next);

   // linking two groups
   headOfAfter2000->next = headOfBefore2000;
}

// remove head node from list
void find_next(Node** head){
   Node* temp = (*head)->next;
   free(*head);
   *head = temp;
}