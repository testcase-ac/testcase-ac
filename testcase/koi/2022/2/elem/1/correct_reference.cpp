/*
 * KOI 2022 Model Solution
 *
 * Gyojun Youn
 * youngyojun@gmail.com
 *
 */

#include <stdio.h>

int main() {
	int N;
	scanf("%d", &N);

	int K = 0;
	for(int i = 0; i < N; i++) {
		int x;
		scanf("%d", &x);
		if(K + 1 == x)
			K++;
	}

	printf("%d\n", N - K);
	return 0;
}