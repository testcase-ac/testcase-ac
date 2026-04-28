#include <cstdio>

int main(){
	int n;
	scanf("%d", &n);

	for(int i = 0; i < n - 1; i++){
		for(int j = 0; j < n - i - 2; j++){
			printf(" ");
		}
		for(int j = 0; j < i + 1; j++){
			printf(" *");
		}
		printf("\n");
	}
	printf("*");
	for(int i = 0; i < n - 1; i++){
		printf(" *");
	}
}