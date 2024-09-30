#include <stdio.h>
void main() {
int a;
scanf("%d", &a);
for(int s=0,n=2;n<a;n++)
	if(a%n==0) {
		printf("%d ",n);
		break;
}
}
