#include <stdio.h>

int main(void){

	int testcasenum;

	scanf("%d", &testcasenum);

	int n;

	int one_two_three[11] = {0};
	one_two_three[0] = 1;
	one_two_three[1] = 2;
	one_two_three[2] = 4;

	for(int i = 3; i < 11; i++){
		for(int j = 0; j < 3; j++){
			one_two_three[i] += one_two_three[i-j-1];
		}
	}

	for(int i = 0; i < testcasenum; i++){
		scanf("%d", &n);
		printf("%d\n", one_two_three[n-1]);
	}
    
    return 0;
}