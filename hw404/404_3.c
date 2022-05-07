#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

enum {FALSE, TRUE};

typedef struct{
   int top;
   char* parenStack;
} Stack;

void inputParentheses(int* plengthOfContent, Stack* stack);
void printPalenStack(Stack* stack);
char peek(Stack* stack);
void push(Stack* stack, char parenChar, int parenCounter, int* priorityChecker);
int isEmpty(Stack* stack);
char pop(Stack* stack);
char peek(Stack* stack);
int priorityCheck(int* priorityChecker, int parenPriority, Stack* stack);
int parenOperatorChecker(char paren);

int main(){
   // struct initialize
   Stack* stack = malloc(sizeof(Stack));
   stack->parenStack = malloc(sizeof(char) * 5);
   stack->top = 0;
   int lengthOfContent = 0;

   inputParentheses(&lengthOfContent, stack);
   printPalenStack(stack);
}





int priorityCheck(int* priorityChecker, int parenPriority, Stack* stack ){
   puts("priority check run");
   if(stack->top == 0) *priorityChecker = 3;

   if(*priorityChecker >= parenPriority){
      *priorityChecker = parenPriority;
      return TRUE;
   }else if(*priorityChecker < parenPriority){
      puts("priority miss");
      return FALSE;
   }
}

void push(Stack* stack, char parenChar, int parenCounter, int* priorityChecker){
   // priority check among [{(
   int parenPriority = 0;
   // If stack.push >= 5, realloc the size of stack.parenStack
   if(parenCounter % 5 == 0) stack->parenStack = realloc(stack->parenStack, sizeof(stack->parenStack) + 5);
   
   // parenthesis priority

   switch(parenChar){
      case '(':
            if(!priorityCheck(priorityChecker, 1, stack)){
               puts("priority check failed");
               exit(-1);
            }
         break;
      case '{':
            if(!priorityCheck(priorityChecker, 2, stack)){
               puts("priority check failed");
               exit(-1);
            }
         break;
      case '[':
            if(!priorityCheck(priorityChecker, 3, stack)){
               puts("priority check failed");
               exit(-1);
            }
         break;
      default:
         break;
   }

   // closing parenthesis match
   switch(parenChar){
      case ')':
         if(peek(stack) != '('){
            printf("Push error: invalid parenthesis to '%c' of '%c'\n", peek(stack), parenChar);
            exit(-1);
         }else pop(stack);
         break;
      case '}':
         if(peek(stack) != '{'){
            printf("Push error: invalid parenthesis to '%c' of '%c'\n", peek(stack), parenChar);
            exit(-1);
         }else pop(stack);
         break;
      case ']':
         if(peek(stack) != '['){
            printf("Push error: invalid parenthesis to '%c' of '%c'\n", peek(stack), parenChar);
            exit(-1);
         }else pop(stack);
         break;
      default:
         stack->parenStack[stack->top] = parenChar;
         stack->top++;   
   }
}

char peek(Stack* stack){
   if(isEmpty(stack) == TRUE) puts("Peek error: stack is empty");
   else{
      return stack->parenStack[stack->top - 1];
   }
}

char pop(Stack* stack){
   char returningChar;
   if(isEmpty(stack) == TRUE){
      puts("Pop error: stack is empty");
      exit(-1);
   }
   else{
      returningChar = stack->parenStack[stack->top];
      stack->top--;
      printPalenStack(stack);
      return returningChar;
   }
}

 int isEmpty(Stack* stack){
    if(stack->top == 0) return TRUE;
    else return FALSE;
 }

void inputParentheses(int* plengthOfContent, Stack* stack){
   int parenCounter = 0;
   char buffer[20];
   char paren;
   int priorityChecker = 3;

   printf("Enter parens, input 's' to stop \n");
   while(TRUE){
      scanf("%s", &buffer);
      if(buffer[0] == 's'){
         return;
      }
      sscanf(buffer, "%c", &paren);
      if(isdigit(paren)) continue;
      else if(parenOperatorChecker(paren)) continue;
      parenCounter++;
      plengthOfContent++;
      push(stack, paren, parenCounter, &priorityChecker);
   }
}

void printPalenStack(Stack* stack){
   for(int i = 0; i < stack->top; i++){
      printf("parenStack[%d] : %c\n", i, stack->parenStack[i]);
   }
   printf("Stack top is : %d\n", stack->top);
}

int parenOperatorChecker(char paren){
   if(paren == '+' || paren == '-' || paren == '+' || paren == '/') return TRUE;
   return FALSE;
}