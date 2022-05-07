#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct {
   int row;
   int col;
   int** value;
} matrix;

typedef struct{
   int row;
   int col;
   int value;
} sparseNode;

void fillMatrix(matrix* newMatrix);
void printMatrix(matrix* printMatrix);
matrix* allocateMatrix(int row, int col);
sparseNode* sparsify(matrix* matrix);
void fillTotal(int total[], sparseNode sparseArray[]);
void fillIndex(int total[], int index[], int size);
sparseNode* transpose(sparseNode* array, int index[]);
matrix* unsparsify(sparseNode array[]);

void main(){
   srand(time(0));
   int row = 3;
   int col = 4;
   matrix* firstMatrix = allocateMatrix(row, col);
   fillMatrix(firstMatrix);
   printMatrix(firstMatrix);
   puts("=========TRANSPOSE=========");
   sparseNode* sparseArray = sparsify(firstMatrix);
   

   int* total = malloc(sizeof(int) * sparseArray[0].col);
   int* index = malloc(sizeof(int) * (sparseArray[0].col+1));

   fillTotal(total, sparseArray);
   fillIndex(total, index, sparseArray[0].col + 1);
   sparseNode* transposedSparse = transpose(sparseArray, index);

   matrix * transposed = unsparsify(transposedSparse);
   printMatrix(transposed);
}

matrix* unsparsify(sparseNode array[]){
   int arrayIdx = 1;
   matrix* ret = malloc(sizeof(matrix));
   ret->col = array[0].col;
   ret->row = array[0].row;
   ret->value = malloc(sizeof(int*) * array[0].row);
   for(int i = 0; i < array[0].row; i++){//0123
      ret->value[i] = malloc(sizeof(int) * array[0].col);
      for(int j = 0; j < array[0].col; j++){//012
         if(j == array[arrayIdx].col && i == array[arrayIdx].row){
            ret->value[i][j] = array[arrayIdx].value;
            arrayIdx++;
         }
      }
   }
   return ret;
}

sparseNode* transpose(sparseNode* array, int index[]){
   sparseNode* ret = malloc(sizeof(sparseNode) * (array[0].value+1));
   ret[0].value = array[0].value;
   ret[0].col = array[0].row;
   ret[0].row = array[0].col;
   for(int i = 1; i < array[0].value + 1; i++){
      int retIdx = index[array[i].col];
      index[array[i].col]++;

      ret[retIdx].value = array[i].value;
      ret[retIdx].col = array[i].row;
      ret[retIdx].row = array[i].col;
   }
   return ret;
}


void fillTotal(int total[], sparseNode sparseArray[]){
   for(int i = 1; i < sparseArray[0].value; i++){
      total[sparseArray[i].col] += 1;
   }
}

void fillIndex(int total[], int index[], int size){
   index[0] = 1;
   for(int i = 1; i < size; i++)
      index[i] = index[i-1] + total[i-1];
}




sparseNode* sparsify(matrix* matrix){
   int nonZeroes = 0;

   for(int i = 0; i < matrix->row; i++){
      for(int j = 0; j < matrix->col; j++){
         if(matrix->value[i][j] != 0){
            nonZeroes++;
         }
      }
   }

   sparseNode* sparseArray = malloc(sizeof(sparseNode) * (nonZeroes + 1));
   sparseArray[0].row = matrix->row;
   sparseArray[0].col = matrix->col;
   sparseArray[0].value = nonZeroes;

   int sparseNodeArrayC = 1;

   for(int i = 0; i < matrix->row; i++){
      for(int j = 0; j < matrix->col; j++){
         if(matrix->value[i][j]){
            sparseArray[sparseNodeArrayC].row = i;
            sparseArray[sparseNodeArrayC].col = j;
            sparseArray[sparseNodeArrayC].value = matrix->value[i][j];
            sparseNodeArrayC++;
         }
      }
   }

   return sparseArray;
}  

void fillMatrix(matrix* newMatrix){    
   for(int i = 0; i < newMatrix->row; i++){
      for(int j = 0; j < newMatrix->col; j++){
         newMatrix->value[i][j] = (rand() % 10) * (rand() % 2);
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


