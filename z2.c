#include <stdio.h>

void main(){
	int n = 2;
	int flag = 0;
	int a;
	scanf("%d", &a);
	while (a%n == 0){
		if (n == a){
			flag = 1;
			break;
		}
	n++;
	}
	printf("%d \n", n);
}
