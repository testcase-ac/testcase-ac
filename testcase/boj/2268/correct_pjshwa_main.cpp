#include <iostream>
#include <vector>
using namespace std;
#define ll long long

void swap(int& a, int& b) {
  int temp = a;
  a = b;
  b = temp;
}

struct Seg {
	int flag;  // array size
	vector<ll> t;

	void build(int N) {
		for (flag = 1; flag < N; flag <<= 1);
		t.resize(2 * flag);

		for (int i = flag; i < flag + N; i++) t[i] = 0;
		for (int i = flag - 1; i >= 1; i--) t[i] = t[i << 1] + t[i << 1 | 1];
	}
	void modify(int p, int value) {  // set value at position p
		for (t[p += flag - 1] = value; p > 1; p >>= 1) t[p >> 1] = t[p] + t[p ^ 1];
	}
	ll query(int L, int R) {
		return query(L, R, 1, 1, flag);
	}
	ll query(int L, int R, int n, int nL, int nR) {  // sum on interval [L, R]
		if (R < nL || nR < L) return 0;
		if (L <= nL && nR <= R) return t[n];

		int mid = (nL + nR) / 2;
		return query(L, R, n << 1, nL, mid) + query(L, R, n << 1 | 1, mid + 1, nR);
	}
}seg;

int main() {
	cin.tie(NULL); cout.tie(NULL);
	ios_base::sync_with_stdio(false);

	int N, M, i, j, k; cin >> N >> M;
	seg.build(N);

	while (M--) {
		cin >> i >> j >> k;
		if (i == 0) {
			if (j > k) swap(j, k);
			cout << seg.query(j, k) << '\n';
		}
		else {
			seg.modify(j, k);
		}
	}

	return 0;
}
