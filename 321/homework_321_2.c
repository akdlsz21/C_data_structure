#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct {
   int row;
   int col;
   int** value;
} matrix;

void fillMatrix(matrix* newMatrix);
void printMatrix(matrix* printMatrix);
matrix* addTwoMatrices(matrix* firstMatrix, matrix* secondMatrix);
matrix* allocateMatrix(int row, int col);
matrix* multiplyTwoMatrices(matrix* firstMatrix, matrix* secondMatrix);


void main(){
    srand(time(0));
    int row = (rand() % 10) + 1;
    int col = (rand() % 10) + 1;
    matrix* firstMatrix = allocateMatrix(row, col);
    matrix* secondMatrix = allocateMatrix(row, col);
    fillMatrix(firstMatrix);
    fillMatrix(secondMatrix);
   puts("=========ADDITION=========");

    printMatrix(firstMatrix);
    puts("");
    printMatrix(secondMatrix);

    printMatrix(addTwoMatrices(firstMatrix, secondMatrix));

   puts("=========Multiply=========");

   //  int firstRow = (rand() % 4) + 2;
   //  int firstCol = (rand() % 4) + 2;
   //  int secondRow = firstCol;
   //  int secondCol = (rand() % 4) + 2;
    int firstRow = 2;
    int firstCol = 3;
    int secondRow = firstCol;
    int secondCol = 2;
    matrix* firstMatrixMult = allocateMatrix(firstRow, firstCol);
    matrix* secondMatrixMult = allocateMatrix(secondRow, secondCol);
    fillMatrix(firstMatrixMult);
    fillMatrix(secondMatrixMult);
    
    printMatrix(firstMatrixMult);
    puts("");
    printMatrix(secondMatrixMult);

    printMatrix(multiplyTwoMatrices(firstMatrixMult, secondMatrixMult));
}

void fillMatrix(matrix* newMatrix){    
    for(int i = 0; i < newMatrix->row; i++){
       for(int j = 0; j < newMatrix->col; j++){
          newMatrix->value[i][j] = (rand() % 100);
       }
    }   
}

void printMatrix(matrix* printMatrix){
   printf("---------------------\n");
   for(int i = 0; i < printMatrix->row; i++){
      for(int j = 0; j < printMatrix->col; j++){
         printf("%d ", printMatrix->value[i][j]);
      }
      puts("");
   }
   printf("---------------------\n");
}

matrix* allocateMatrix(int row, int col){
   matrix* returnMatrix = malloc(sizeof(matrix));
   returnMatrix->col = col;
   returnMatrix->row = row;
   returnMatrix->value = malloc(sizeof(int*) * (returnMatrix->row));
    for(int i = 0; i < returnMatrix->row; i++){
        returnMatrix->value[i] = malloc(sizeof(int) * (returnMatrix->col));
    }
    return returnMatrix;
}


matrix* addTwoMatrices(matrix* firstMatrix, matrix* secondMatrix){
   matrix* returnMatrix = allocateMatrix(firstMatrix->row, firstMatrix->col);

   for(int i = 0; i < firstMatrix->row; i++){
      for(int j = 0; j < firstMatrix->col; j++){
         returnMatrix->value[i][j] = firstMatrix->value[i][j] + secondMatrix->value[i][j];
      }
      
   }
   puts("---------return matrix =========");
   return returnMatrix;
}

int handleMultiplyTwoMatrices(matrix* first, matrix* second, int i, int j){
    int sum = 0;
   for(int k = 0; k < first->col; k++){
       sum += first->value[i][k] * second->value[k][j];
   }
   return sum;
}

matrix* multiplyTwoMatrices(matrix* firstMatrix, matrix* secondMatrix){
   matrix* returnMatrix = allocateMatrix(firstMatrix->row, secondMatrix->col);
   
   for(int i = 0; i < returnMatrix->row; i++){
      for(int j = 0; j < returnMatrix->col; j++){
         returnMatrix->value[i][j] = handleMultiplyTwoMatrices(firstMatrix, secondMatrix, i, j);
      }
   }
   return returnMatrix;
}