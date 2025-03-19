#include <stdio.h>

int main(){
	int g = 1;
	int a, i, n;
	printf("Введите высоту прямоугольника:");
	scanf("%d", &a);
	for (i = 0; i != a; i++){
		for (n = 0; n != a; n++){
			printf("%d ", g);
			g++;
		}
		printf("\n");
	}
	printf("\n");
}
