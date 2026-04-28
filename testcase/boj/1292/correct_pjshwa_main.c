#include <stdio.h>

int main(void){
	int a, b;

	int easy_peasy[1000];

	scanf("%d %d", &a, &b);

	int fill_number = 1;
	int counts = 0;

	for(int i = 0; i < b; i++){
		easy_peasy[i] = fill_number;
		counts++;
		if(fill_number == counts){
			fill_number++;
			counts = 0;
		}
	}

	int sum = 0;

	for(int i = a - 1; i < b; i++){
		sum += easy_peasy[i];
	}

	printf("%d", sum);
}