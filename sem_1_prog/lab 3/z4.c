#include <stdio.h>

int main() {
    int n,a,k,s;
    scanf("%d",&a);
    for (n=a, s=0; n!=0; n=n/10) { 
        k=n%10; 
        if (k>s) 
        s=k;
    }
    printf("%d\n%d\n", s,k);
}
//выводит первую цифру числа и наибольшую цифру в числе
