#include <stdio.h>

int main() {
    int a,n;
    int s=0;
    scanf("%d", &a);
    for (n=2; n<a; n++){
         if (a%n==0) {
         s=1;
         break; 
      }
      
    }
    printf("%d\n", n);
}
//программа выводит ближайшее к 2 число на которое введенное делится без остатка
