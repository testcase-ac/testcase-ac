/*
 * C++ Official Solution
 *
 * Gyojun Youn
 * youn.gyojun [at] gmail [dot] com
 */

#include <cstdio>
using namespace std;
typedef long long ll;

const int MAXN = 300'005;
const int MAXQ = 500'005;

ll A[MAXN];
int B[MAXQ];

ll L;
int N, Q, K;

void push(ll x) {
	if (Q < x) {
		x = Q;
	}

	if (x) {
		B[x]++;
		K++;
	}
}

int main() {
	scanf("%lld%d%d", &L, &N, &Q);

	for (int t = N; Q && t;) {
		puts("0");
		Q--;
		t--;
	}

	for (int i = 1; i <= N; i++) {
		scanf("%lld", A+i);
	}

	push(A[1]);
	push(L - A[N]);

	for (int i = 1; i < N; i++) {
		ll d = A[i+1] - A[i];
		push(d / 2);
		push((d-1) / 2);
	}

	for (int h = 1; Q; h++) {
		for (int t = K; Q && t;) {
			printf("%d\n", h);
			Q--;
			t--;
		}

		K -= B[h];
	}

	return 0;
}
