#include <stdio.h>
#include <stdlib.h>
#include <string.h>

enum {false, true};

typedef struct book{
   char title[20];
   char author[20];
   int price;
   char date[8];
} Book;

typedef struct stack{
   Book* stack[5];
   int top;
}Stack;

typedef struct book_info{
   char title[20];
   char author[20];
   int price;
   char date[8];
}Book_Info;

void input(Stack*, Stack*, Stack*, Stack*);
void classifyBook(Stack*, Stack*, Stack*, Stack*, Book_Info*);
void push(Stack*, Book*);
void printStack(Stack*);
void generateBookDataAndPush(Stack*, Stack*, Stack*, Stack*);
void storeBook(Stack* stack, Book* newBook);
void merge(Stack* stack, int l, int m, int r);
void mergeSort(Stack* stack, int left, int right);

int main(){
Stack* IS_Stack = malloc(sizeof(Stack));
Stack* CS_Stack = malloc(sizeof(Stack));
Stack* MS_Stack = malloc(sizeof(Stack));
Stack* EEE_Stack = malloc(sizeof(Stack));

// IS_Stack->stack = malloc(sizeof(Book) * 5);
// CS_Stack->stack = malloc(sizeof(Book) * 5);
// MS_Stack->stack = malloc(sizeof(Book) * 5);
// EEE_Stack->stack = malloc(sizeof(Book) * 5);

IS_Stack->top = 0;
CS_Stack->top = 0;
MS_Stack->top = 0;
EEE_Stack->top = 0;

// input(IS_Stack, CS_Stack, MS_Stack, EEE_Stack);
generateBookDataAndPush(IS_Stack, CS_Stack, MS_Stack, EEE_Stack);
printStack(IS_Stack);
printStack(CS_Stack);
printStack(MS_Stack);
printStack(EEE_Stack);

}

void input(Stack* IS_Stack,Stack* CS_Stack,Stack* MS_Stack,Stack* EEE_Stack){
   char buffer[5];

   printf("--- Enter Book Info      ---\n");
   printf("--- Discontinue with '/' ---\n");
   while(true){
      Book_Info* bookInfo = malloc(sizeof(Book_Info));
      printf("Enter Title: ");
      scanf("%s", &bookInfo->title);
      if(bookInfo->title[0] == '/') break;

      printf("Enter Author: ");
      scanf("%s", &bookInfo->author);
      if(bookInfo->author[0] == '/') break;

      printf("Enter Price: ");
      scanf("%d", &bookInfo->price);

      printf("Enter Date of Release(ex:2020/01): ");
      scanf("%s", &bookInfo->date);
      if(bookInfo->date[0] == '/') break;

      classifyBook(IS_Stack, CS_Stack, MS_Stack, EEE_Stack, bookInfo );

      free(bookInfo);
   }
}

void classifyBook(Stack* IS_Stack,Stack* CS_Stack,Stack* MS_Stack,Stack* EEE_Stack, Book_Info* bookInfo ){
   // Create new book, and assign the bookInfo values to the new book
   Book* newBook = malloc(sizeof(Book));
   strcpy(newBook->title, bookInfo->title);
   strcpy(newBook->author, bookInfo->author);
   strcpy(newBook->date, bookInfo->date);
   newBook->price = bookInfo->price;


   // printf("bookTitle is: %s\n", newBook->title);
   if(strstr(newBook->title, "IS")) storeBook(IS_Stack, newBook);
   else if(strstr(newBook->title, "CS")) storeBook(CS_Stack, newBook);
   else if(strstr(newBook->title, "MS")) storeBook(MS_Stack, newBook);
   else if(strstr(newBook->title, "EEE")) storeBook(EEE_Stack, newBook);
}

void storeBook(Stack* stack, Book* newBook){
   push(stack, newBook);
   mergeSort(stack, 0, stack->top-1);
}

void merge(Stack* stack, int left, int mid, int right){

   int n1 = left - mid + 1;
   int n2 = right - mid;

   Book* L[n1], *M[n2];

   for(int i = 0; i < n1; i++)
      L[i] = stack->stack[left + i];
   for(int j = 0; j < n2; j++)
      M[j] = stack->stack[mid + 1 + j];

   int i, j, k;
   i = 0;
   j = 0;
   k = left;

   while(i < n1 && j < n2){
      if(M[j]->price <= L[i]->price){
         stack->stack[k] = L[i];
         i++;
      }else{
         stack->stack[k] = M[j];
         j++;
      }
      k++;
   }

   while(i < n1){
      stack->stack[k] = L[i];
      i++;
      k++;
   }

   while(j < n2){
      stack->stack[k] = M[j];
      j++;
      k++;
   }
}

void mergeSort(Stack* stack, int left, int right){
   // Base case
   if(left < right) {

      int mid = left + (right - left) / 2;

      mergeSort(stack, left, mid);
      mergeSort(stack, mid+1, right);

      merge(stack, left, mid, right);
   
   }
}

void generateBookDataAndPush(Stack* IS_Stack,Stack* CS_Stack,Stack* MS_Stack,Stack* EEE_Stack){
   Book_Info* book1 = malloc(sizeof(Book_Info));
   Book_Info* book2 = malloc(sizeof(Book_Info));
   Book_Info* book3 = malloc(sizeof(Book_Info));
   Book_Info* book4 = malloc(sizeof(Book_Info));
   Book_Info* book5 = malloc(sizeof(Book_Info));
   Book_Info* book6 = malloc(sizeof(Book_Info));
   Book_Info* book7 = malloc(sizeof(Book_Info));
   Book_Info* book8 = malloc(sizeof(Book_Info));
   Book_Info* book9 = malloc(sizeof(Book_Info));
   Book_Info* book10 = malloc(sizeof(Book_Info));




   strcpy(book2->title,"AAAAIS");
   strcpy(book2->author,"YOU");
   book2->price = 1000;
   strcpy(book2->date,"1200/01");

   strcpy(book3->title,"ZZCS_is_one");
   strcpy(book3->author,"KIM");
   book3->price = 2000;
   strcpy(book3->date,"1300/01");

   strcpy(book4->title,"CEEE");
   strcpy(book4->author,"KIM");
   book4->price = 3000;
   strcpy(book4->date,"1400/01");

   strcpy(book5->title,"MS_is_two");
   strcpy(book5->author,"JOE");
   book5->price = 4000;
   strcpy(book5->date,"1500/01");

   strcpy(book6->title,"DEEE");
   strcpy(book6->author,"BATTLE_ANGEL");
   book6->price = 5000;
   strcpy(book6->date,"1600/01");

   strcpy(book7->title,"GIBBERISH_is_one");
   strcpy(book7->author,"BATTLE_ANGEL");
   book7->price = 6000;
   strcpy(book7->date,"1700/01");

   strcpy(book8->title,"AEEE");
   strcpy(book8->author,"TOM");
   book8->price = 7000;
   strcpy(book8->date,"1800/01");

   strcpy(book9->title,"IS THAT A BIRDAA");
   strcpy(book9->author,"ALITA");
   book9->price = 8000;
   strcpy(book9->date,"1900/01");

   strcpy(book10->title,"OR IS THAT A PLANEBB");
   strcpy(book10->author,"SPIDERMAN");
   book10->price = 9000;
   strcpy(book10->date,"2000/01");
   
   strcpy(book1->title,"ABIS");
   strcpy(book1->author,"J.J Martin");
   book1->price = 10000;
   strcpy(book1->date,"1000/01");
   
   classifyBook(IS_Stack, CS_Stack, MS_Stack, EEE_Stack, book4);
   classifyBook(IS_Stack, CS_Stack, MS_Stack, EEE_Stack, book6);
   classifyBook(IS_Stack, CS_Stack, MS_Stack, EEE_Stack, book9);
   classifyBook(IS_Stack, CS_Stack, MS_Stack, EEE_Stack, book3);
   classifyBook(IS_Stack, CS_Stack, MS_Stack, EEE_Stack, book10);
   classifyBook(IS_Stack, CS_Stack, MS_Stack, EEE_Stack, book1);
   classifyBook(IS_Stack, CS_Stack, MS_Stack, EEE_Stack, book7);
   classifyBook(IS_Stack, CS_Stack, MS_Stack, EEE_Stack, book2);
   classifyBook(IS_Stack, CS_Stack, MS_Stack, EEE_Stack, book5);
   classifyBook(IS_Stack, CS_Stack, MS_Stack, EEE_Stack, book8);
}

void push(Stack* stack, Book* newBook){
   stack->stack[stack->top] = newBook;
   stack->top++;
}

void printStack(Stack* stack){
   printf("\n");
   for(int i = 0; i < stack->top; i++){
      printf("------------- Book -------------\n");
      printf("|  Title : %s  \n", stack->stack[i]->title);
      printf("|  Author : %s  \n", stack->stack[i]->author);
      printf("|  Price : %d  \n", stack->stack[i]->price);
      printf("--------------------------------\n");
   }
   printf("\n");
      printf("\t||\n\t||\n");

}