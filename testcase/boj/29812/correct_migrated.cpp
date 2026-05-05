#include <stdio.h>
#include <stdlib.h>
#define _CRT_SECURE_NO_WARNINGS
// 제 코드가 아니며, 제가 해당 문제를 클리어한 후 실행 속도가 가장 빠른 코드 위주로 퍼와 추가하고 있습니다.
int Min(int a, int b, int c) {
	int x = (a < b) ? a : b;
	return (x < c) ? x : c;
}

int main() {
	int N, D, M;
	int numH = 0, numY = 0, numU = 0, energy = 0, count = 1;
	char S[200010] = { 0 };

	scanf("%d %s %d %d", &N, S, &D, &M);

	for (int i = 0; i < N; i++) {
		if (S[i] == 'H' || S[i] == 'Y' || S[i] == 'U') {
			if (S[i] == 'H') {
				numH++;
			}
			if (S[i] == 'Y') {
				numY++;
			}
			if (S[i] == 'U') {
				numU++;
			}
			count = 1;
			continue;
		}

		if (S[i + 1] == 'H' || S[i + 1] == 'Y' || S[i + 1] == 'U' || i == N - 1) {
			if (D * count > M + D) {
				energy += M + D;
			}
			else {
				energy += D * count;
			}
		}
		else {
			count++;
		}
	}

	if (energy == 0) {
		printf("Nalmeok\n");
	}
	else {
		printf("%d\n", energy);
	}
	
	if (Min(numH, numY, numU) == 0) {
		printf("I love HanYang University");
	}
	else {
		printf("%d", Min(numH, numY, numU));
	}
}
