/*
 * Official Solution (C++17)
 * Gyojun Youn
 */

#include <cstdio>

int T, N, M, K, D;

int main() {
	scanf("%d", &T);
	while(T--) {
		scanf("%d%d%d%d", &N, &M, &K, &D);
		D = 2*D/N/M/((M-1)*K + (N-1)*M);
		printf("%d\n", D ? N*M*D*((M-1)*K+(N-1)*M)/2 : -1);
	}
	return 0;
}
