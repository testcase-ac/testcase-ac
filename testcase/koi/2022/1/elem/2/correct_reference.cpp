/*
 * Official Solution (C++17)
 * Gyojun Youn
 * youngyojun [at] gmail [dot] com
 */
#include <iostream>
using namespace std;

const int MAXN = 2505;

int A[MAXN], D[MAXN];

int N;

int main() {
	cin >> N;
	for(int i = N; i; i--) cin >> A[i];

	for(int i = 2; i <= N; i++) {
		int r = D[i-1];
		for(int j = i-1, x = A[i]; j; j--) {
			x = A[j] - x;
			if(x < 0) break;
			if(!x && r <= D[j-1]) r = D[j-1] + 1;
		}
		D[i] = r;
	}

	cout << N - D[N] << '\n';
	return 0;
}