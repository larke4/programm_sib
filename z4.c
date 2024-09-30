#include <stdio.h>

int main () {
	int a;
	scanf("%d", &a);
	int n;
	int k;
	int s = 0;
	for (n=a; n != 0; n = n / 10){
		k = n % 10;
		if (k > s){
			s = k;
		}
	}
	printf("%d \n", s);
}
