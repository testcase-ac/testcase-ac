#include <cstdio>
// 제 코드가 아니며, 저가 해당 문제를 클리어한 후 실행 속도가 가장 빠른 코드 위주로 퍼와 추가하고 있습니다.
#define MAX_N		50

int nos[MAX_N];

int main() {
	int N, S, i, j, mx;

	scanf("%d", &N);
	for (i = 0; i < N; ++i) scanf("%d", nos + i);
	scanf("%d", &S);
	while (S && N) {
		mx = 0;
		for (j = 1; j <= S && j < N; ++j) {
			if (nos[j] > nos[mx]) mx = j;
		}
		printf("%d ", nos[mx]);
		for (i = mx + 1; i < N; ++i) nos[i - 1] = nos[i];
		S -= mx;
		--N;
	}
	for (i = 0; i < N; ++i) printf("%d ", nos[i]);

	return 0;
}
