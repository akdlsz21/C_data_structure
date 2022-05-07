#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct{
   float coef;
   int expon;
} polynomial; 


int findUniqueExpo(int expoArr[], int termLength);
int findPolyArrLength(int expoArr[], int termLength, int, int, int* Ce, int*);
int polyInput(float coefArr[], int expoArr[], int* Ae);
void poly_add2(int As, int Ae, int Bs, int Be, int Cs, int Ce, polynomial polyArr[]);
char compare(int a, int b);
void attach(float coef, int expon, polynomial polyArr[], int* idx);
void attachPolyToArray(float coefArr[], int expoArr[], polynomial polyArr[], int termLength);
void poly_multiply(int As, int Ae, int Bs, int Be, int Ds, int Ps, int Rs, polynomial polyArr[]);
void developPoly(polynomial polyArr[], int As, int Bs, int Be, int Cs);

void printTermsArray(polynomial polyArr[], int termLength){
   printf("Print Array\n");
   for(int i = 0; i < termLength; i++){
      printf("[%d].coef: %f .expon: %d\n", i, polyArr[i].coef, polyArr[i].expon);
   }
}


// 
int main() {
   int As = 0, Ae, Bs, Be, Cs, Ce;
   int Rs, Ps, Ds, total; 
   int termLength;
   float coefArr[20] = {};
   int expoArr[20] = {};

   termLength = polyInput(coefArr, expoArr, &Ae);
   Bs = Ae + 1;
   Be = termLength - 1;
   Cs = Be + 1;
   int polyArrLength = findPolyArrLength(expoArr, termLength, Bs, Be, &Ce, &Ds);
   Ps = Ds;
   Rs = Ds * 2;
   total = Ds;
   Ds = Ce + 1;
   Rs += Ds;
   Ps += Ds;
   total += Rs;
   
   polynomial* polyArr = malloc(sizeof(polynomial) * polyArrLength);

   attachPolyToArray(coefArr, expoArr, polyArr, termLength);
   poly_add2(As, Ae, Bs, Be, Cs, Ce, polyArr);

   poly_multiply(As, Ae,  Bs, Be, Ds, Ps, Rs, polyArr);
   printTermsArray(polyArr, total);


}

int cmpfunc (const void * a, const void * b) {
   return ( *(int*)a - *(int*)b );
}

int findUniqueExpo(int expoArr[], int termLength){
   int copiedExpoArr[20];
   memcpy(copiedExpoArr, expoArr, 80);
   qsort(copiedExpoArr,termLength, 4, cmpfunc);

   int uniqueCounter = 0;

   for(int i = 0; i < termLength - 1; i++){
      printf("termLength: %d", termLength);
      if(copiedExpoArr[i] == copiedExpoArr[i + 1]){
         uniqueCounter++;
      }

   }

   return termLength - uniqueCounter;
}

int findPolyArrLength(int expoArr[], int termLength, int Bs, int Be, int* Ce, int* length){
   termLength += findUniqueExpo(expoArr, termLength);
   *Ce = termLength -1;
   int jeongae[20];
   int jeongaeCounter = 0;
   for(int i = 0; i < Bs; i++){
      for(int j = Bs; j <= Be; j++){
         jeongae[jeongaeCounter] = expoArr[i] * expoArr[j];
         jeongaeCounter++;
      }
   }

   *length = findUniqueExpo(jeongae, jeongaeCounter);
   termLength += *length * 3;

   return termLength;

}


int polyInput(float coefArr[], int expoArr[], int* Ae){
   int termIdx = 0;
   char buffer[20];
   float coef;
   int expo;

   while(1){
      scanf("%s", &buffer); 
      if(buffer[0] == '/') {
         puts("Ended first input");
         break;
      }
      sscanf(buffer, "%f", &coef);
      scanf("%d", &expo);
      coefArr[termIdx] = coef;
      expoArr[termIdx] = expo;
      termIdx++;
   }
   *Ae = termIdx - 1;

   while(1){
      scanf("%s", &buffer); 
      if(buffer[0] == '/') {
         puts("Ended second input");
         break;
      }
      sscanf(buffer, "%f", &coef);
      scanf("%d", &expo);
      coefArr[termIdx] = coef;
      expoArr[termIdx] = expo;    
      termIdx++;
   }
   printf("Inside coefArr[0]: %f\n", coefArr[0]);

   return termIdx;
}


void poly_add2(int As, int Ae, int Bs, int Be, int Cs, int Ce, polynomial polyArr[]){
   float tempcoef;
   while(As <= Ae && Bs <= Be)
      switch(compare(polyArr[As].expon, polyArr[Bs].expon)){
         case '>':  // A의 차수 > B의 차수
            attach(polyArr[As].coef, polyArr[As].expon, polyArr, &Cs);
            As++; break;
         case '=':
            tempcoef = polyArr[As].coef + polyArr[Bs].coef;
            if(tempcoef)
               attach(tempcoef, polyArr[As].expon, polyArr, &Cs);
            As++; Bs++; break;
         case '<': // A의 차수 < B의 차수
            attach(polyArr[Bs].coef, polyArr[Bs].expon, polyArr, &Cs);
            Bs++; break;
      }

   // A의 나머지 항들을 이동함
   for(; As <= Ae; As++){
      attach(polyArr[As].coef, polyArr[As].expon, polyArr, &Cs);
   }
   // B의 나머지 항들을 이동함
   for(; Bs <= Be; Bs++){
      attach(polyArr[Bs].coef, polyArr[Bs].expon, polyArr, &Cs);

   }
}

char compare(int a, int b){
   if (a > b) return '>';
   else if(a == b) return '=';
   else return '<';
}



void attach(float coef, int expon, polynomial polyArr[], int* idx){
   polyArr[*idx].coef = coef;
   polyArr[*idx].expon = expon;
   
   *idx += 1;
}


void attachPolyToArray(float coefArr[], int expoArr[], polynomial polyArr[], int termLength){
   for(int i = 0; i < termLength; i++){
      int tai = i;
      printf("polyArr: %f\n", coefArr[i]);
      attach(coefArr[i], expoArr[i], polyArr, &tai);
   }

}

void poly_multiply(int As, int Ae, int Bs, int Be, int Ds, int Ps, int Rs, polynomial polyArr[]){
   int length = Ps - Ds - 1;
   for(int i = As; i <= Ae; i++){
      developPoly(polyArr, i, Bs, Be, Ds);
      poly_add2(Ds, Ds + length, Ps, Ps + length, Rs, Rs + length, polyArr);
      memcpy(&polyArr[Ps], &polyArr[Rs], sizeof(polynomial) * (length+1));
   }
   
}

void developPoly(polynomial polyArr[], int As, int Bs, int Be, int Cs){

   for(int i = Bs; i <= Be; i++){
      attach(polyArr[i].coef*polyArr[As].coef, polyArr[i].expon+polyArr[As].expon,polyArr,&Cs);
   }
}