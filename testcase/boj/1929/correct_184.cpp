#include <math.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
// 체
int main() {
	int N, M;
	scanf("%d %d", &N, &M);
	char *isNotPrime = (char *)malloc(M+1);
	memset(isNotPrime, 0, sizeof(char) * (M+1));
	isNotPrime[0] = 1;
	isNotPrime[1] = 1;
	int p=2;
	while(p * p <= M) {
		for(int i=p*2; i<=M; i+=p)
			isNotPrime[i] = 1;
		p++;
		while(isNotPrime[p])
			p++;
	}
	for(int i=N; i<=M; i++) {
		if(!isNotPrime[i])
			printf("%d\n", i);
	}
}
