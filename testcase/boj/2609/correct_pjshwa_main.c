#include <stdio.h>

int main(void){
	int original_number[2];

	scanf("%d %d", &original_number[0], &original_number[1]);

	int a = original_number[0];
	int b = original_number[1];
	int temp;

	while(a != b){
		if(a > b){
			temp = a - b;
			a = b;
			b = temp;
		}
		else{
			temp = b - a;
			b = a;
			a = temp;
		}
	}

	printf("%d\n%d", a, original_number[0] * original_number [1] / a);

	return 0;
}