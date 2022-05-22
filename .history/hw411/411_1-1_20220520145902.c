#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>

enum{false, true};


typedef struct stack{
   int top;
   char* operatorStack;
}Stack;

typedef struct postfix{
   int j;
   char* string;
} Postfix;

void infixToPrefix(Stack* stack, char* string, Postfix*);
int isValidParenthesesPriority(char operator, int priority, Stack* stack, int* parenPriority);
int isOperator(Stack* stack, char operator, int* parenPriority);
void push(Stack* stack, char operator);
int isOperatorValidParentheses(Stack* stack, char operator, int* parenPriority);
int isValidOperator(Stack* stack, char operator, int* parenPriority);
int isEmpty(Stack* stack);
int checkPrecedence(char operator);
char peek(Stack* stack);
int isOperatorParentheses(char operator);
int isOperatorClosingParentheses(char operator);
void popUntilMatchingParenetheses(Stack* stack, char operator, Postfix*);
char pop(Stack* stack);

int main(){
   Stack* stack = malloc(sizeof(Stack));
   Postfix* postfix = malloc(sizeof(Postfix));

   stack->top = 0;
   postfix->j = 0;

   // below fails
   // char inputString[] = "[3*{6+1/(2+3)+[4-2]}]";

   // below succeeds
   char inputString[] = "[3*{6+1/(2+3)}]";
   infixToPrefix(stack, inputString, postfix);

   puts("Infix to Postfix Done!");
   printf("Current postfix: %s\n", postfix->string);


}

void infixToPrefix(Stack* stack, char string[], Postfix* postfix){
   int stringLength = strlen(string);
   stack->operatorStack = malloc(sizeof(char) * stringLength);
   int parenPriority = 3;
   char operator;

   postfix->string = malloc(sizeof(char) * strlen(stack->operatorStack));

   int j = 0;


   for(int i = 0; i < stringLength; i++){
      operator = string[i];
      if(isOperatorParentheses(operator)){
         if(isOperatorValidParentheses(stack, string[i], &parenPriority)){ 
            push(stack, operator);
         }
         if(isOperatorClosingParentheses(operator)){
            popUntilMatchingParenetheses(stack, operator, postfix);
         }
      }else if(isOperator(stack, string[i], parenPriority)){
         if(isValidOperator(stack, string[i], parenPriority)) push(stack, operator);
         else puts("operator precedence failed");
      }else if(isdigit(operator)){
         // postfix string push.
         postfix->string[postfix->j] = operator;
         postfix->j++;
      }
      printf("stack: %s\n", stack->operatorStack);
   }

}

void popUntilMatchingParenetheses(Stack* stack, char closingParenthesis, Postfix* postfix){
   char returnPoped;

   while(true){
      if(closingParenthesis == ')'){
         returnPoped = pop(stack);
         if(returnPoped == '('){
            break;
         }
         else if(returnPoped == '/' || returnPoped == '*' || returnPoped == '-' || returnPoped == '+'){
         postfix->string[postfix->j] = returnPoped;
         postfix->j++;

         }

      }else if(closingParenthesis == '}'){
         returnPoped = pop(stack);
         if(returnPoped == '{'){
            break;
         }
         else if(returnPoped == '/' || returnPoped == '*' || returnPoped == '-' || returnPoped == '+'){
         postfix->string[postfix->j] = returnPoped;
         postfix->j++;

         }


      }else if(closingParenthesis == ']'){
         returnPoped = pop(stack);

         if(returnPoped == '['){
            break;
         }
         else if(returnPoped == '/' || returnPoped == '*' || returnPoped == '-' || returnPoped == '+'){
         postfix->string[postfix->j] = returnPoped;
         postfix->j++;
         }
      }
   }
}

int isOperatorClosingParentheses(char operator){
   if(operator == ')' || operator == ']' || operator == '}') return true;
   else return false;
}

int checkPrecedence(char operator){
   switch(operator){
      case '+': case '-':
          return 4;
          break;
      case '*': case '/':
          return 5;
          break;
      case '[':
          return 3;
          break;
      case '{':
          return 2;
          break;
      case '(':
          return 1;
          break;
   }
   return false;
}

char peek(Stack* stack){
   if(stack->top != 0) return stack->operatorStack[stack->top - 1];
   else{
      puts("peek failed, program shutdown");
      exit(-1);
   }
}

int isValidOperator(Stack* stack, char operator, int* parenPriority){
   // if(operator == ')' || operator == ']' || operator == '}') return false;
   if(checkPrecedence(operator) >= checkPrecedence(peek(stack))) return true;
   return false;
}

int isEmpty(Stack* stack){
   if(stack->top == 0) return true;
   return false;
}

int isOperator(Stack* stack, char operator, int* parenPriority){
   // check if operator is valid operator precedence
   switch(operator){
      case '+': case '-': return 1;
      case '*': case '/': return 2;
   }
   return false;
}

int isOperatorParentheses(char operator){
   if(operator == '(' || operator == ')' || operator == '[' || operator == '{' || operator == ']' || operator == '}' )
      return true;
   else return false;

}

int isOperatorValidParentheses(Stack* stack, char operator, int* parenPriority){
   // priortiy check
   switch (operator){
   case '[':
      if(isValidParenthesesPriority(operator, 3, stack, parenPriority)) {
         return true;
      }
      else{
         puts("Priority check failed");
         exit(-1);
      }
      break;
   case '{':
      if(isValidParenthesesPriority(operator, 2, stack, parenPriority)) {
         return true;
      }
      else{
         puts("Priority check failed");
         exit(-1);
      }
      break;
   case '(':
      if(isValidParenthesesPriority(operator, 1, stack, parenPriority)) {
         return true;
      }
      else{
         puts("Priority check failed");
         exit(-1);
      }
      break;
   
   default:
      break;
   }

}

void push(Stack* stack, char operator){
   stack->operatorStack[stack->top] = operator;
   stack->top++;
}

char pop(Stack* stack){
   stack->top--;
   char returnPop = stack->operatorStack[stack->top];
   return returnPop;
}

int isValidParenthesesPriority(char operator, int priority, Stack* stack, int* parenPriority){
   if(stack->top == 0) *parenPriority = 3;


   if(*parenPriority >= priority){
      *parenPriority = priority;
      return true;
   }else if(*parenPriority < priority){
      puts("priority miss");
      return false;
   }
}
