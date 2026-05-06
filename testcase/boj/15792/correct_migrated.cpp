#include <cstdio>
int main(){
	int a,b;
	scanf("%d %d",&a,&b);
	printf("%d.",a/b);
	for(int i=0;i<1000;i++){
		a=a%b*10;
		printf("%d",a/b);
	}
}
