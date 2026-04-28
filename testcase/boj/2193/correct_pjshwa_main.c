#include <stdio.h>

int main(void){

	int n;

	scanf("%d", &n);

	long long int pinary[(n+1)/2][2];

	if(n % 2){ // if odd
		pinary[0][0] = 0LL;
		pinary[0][1] = 1LL;
	}
	else{
		pinary[0][0] = 1LL;
		pinary[0][1] = 0LL;
	}

	for(int i = 1; i < (n+1)/2; i++){
		pinary[i][0] = pinary[i-1][0] * 2LL + pinary[i-1][1];
		pinary[i][1] = pinary[i-1][0] + pinary[i-1][1];
	}

    printf("%lld", pinary[(n-1)/2][0] + pinary[(n-1)/2][1]);
    
    return 0;
}