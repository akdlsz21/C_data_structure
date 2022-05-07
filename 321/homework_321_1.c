#include <stdio.h>
#include <stdlib.h>

#define MAX_TERMS 101
typedef struct{
   float coef;
   int expon;
} polynomial;
polynomial terms[MAX_TERMS] = {};

int tempArrIdx = 0;

// 두개의 정수를 비교
char compare(int a, int b){
   if (a > b) return '>';
   else if(a == b) return '=';
   else return '<';
}

// 새로운 항을 다항식에 추가한ㄷ.
void attach(float coef, int expon){
   if( tempArrIdx > MAX_TERMS) {
      fprintf(stderr, "항의 개수가 너무 많음\n");
      exit(1);
   }
   terms[tempArrIdx].coef = coef;
   terms[tempArrIdx].expon = expon;
   tempArrIdx++;
}

// takes input of polynominals
void poly_input(int start, int* end){
   int i = -1;
   char buffer[20];
   float coef;
   int expo;
   while(1){ 
      scanf("%s", &buffer); 
      if(buffer[0] == '/') {
         *end = start + i;
         return;
      }
      sscanf(buffer, "%f", &coef);  
      scanf("%d", &expo);       
      attach(coef, expo);
      i++;
   }
};

// C = A + B
void poly_add2(int As, int Ae, int Bs, int Be, int *Cs, int *Ce){
   float tempcoef;
   *Cs = tempArrIdx;
   printf("As: %d\nBs: %d\n Ae: %d\n Be: %d\n",As, Bs, Ae, Be);
   while(As <= Ae && Bs <= Be)
      switch(compare(terms[As].expon, terms[Bs].expon)){
         case '>':  // A의 차수 > B의 차수
            attach(terms[As].coef, terms[As].expon);
            As++; break;
         case '=':
            tempcoef = terms[As].coef + terms[Bs].coef;
            if(tempcoef)
               attach(tempcoef, terms[As].expon);
            As++; Bs++; break;
         case '<': // A의 차수 < B의 차수
            attach(terms[Bs].coef, terms[Bs].expon);
            Bs++; break;
      }

   // A의 나머지 항들을 이동함
   for(; As <= Ae; As++)
      attach(terms[As].coef, terms[As].expon);
   // B의 나머지 항들을 이동함
   for(; Bs <= Be; Bs++)
      attach(terms[Bs].coef, terms[Bs].expon);
   
   *Ce = tempArrIdx -1;
}

void print_poly(int s, int e){
   for(int i = s; i < e; i++)
      printf("%3.1fx^%d + ", terms[i].coef, terms[i].expon);
   printf("%3.1fx^%d\n", terms[e].coef, terms[e].expon);
}

void setNewTerms(float aCoef, int aExpon, float bCoef, int bExpon){
   attach(aCoef * bCoef, aExpon + bExpon);
}

void poly_multiply(int As, int Ae, int Bs, int Be, int *Cs, int *Ce){ 
   for(int i = As; i <= Ae; i++){
      for(int j = Bs; j <= Be; j++){
         // setNewTerms(terms[i].coef, terms[i].expon, terms[j].coef, terms[j].expon);
         attach(terms[i].coef * terms[j].coef, terms[i].expon + terms[j].expon);
      }
   }
   int length = Be - Bs; // 4
   //더하는 부분 (A * B) / A의 길이
   int startIdx = Be + 1; //6
   poly_add2(startIdx, startIdx + length, startIdx + length + 1, startIdx + (2*length) + 1, Cs, Ce);
   for(int i = 0; i < (Ae - 1); i++){
      startIdx = startIdx + (2*length) + 2;
      poly_add2(startIdx, startIdx + length, *Cs, *Ce, Cs, Ce);
   }
}


// terms array: {t, t, t, t,     t, t, t, m, m, m,m,m,m,m,m,m,m,m,m m+, + +,   }
//                 4               3            12           12(result)
//
int main(void){
   int As = 0, Ae, Bs = 0, Be, Cs, Ce;
   poly_input(As, &Ae);
   Bs = Ae + 1;
   poly_input(Bs, &Be);
   poly_add2(As, Ae, Bs, Be, &Cs, &Ce);
   print_poly(As, Ae);
   print_poly(Bs, Be);
   puts("--------------------------------------");
   print_poly(Cs, Ce);
   puts("");
   tempArrIdx = Be + 1;
   poly_multiply(As, Ae, Bs, Be, &Cs, &Ce);
   print_poly(Cs, Ce);

   return 0;
}