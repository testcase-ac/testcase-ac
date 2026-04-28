#include <bits/stdc++.h>
#define fastio cin.tie(0)->sync_with_stdio(0)
using namespace std;

constexpr int M = 15;
int cache[M - 1][(1 << M) | 1][2];

int Calc(int n, int pos, bool flag) {
	const int sz = 1 << n;
	if (n == 1) return pos & 1 ? 1 + !flag : 0;
	if (pos == 0 || pos == sz) return 0;
	if (n <= M) {
		int& ret = cache[n - 2][pos][flag];
		if (ret != -1) return ret;
		if (flag) { // x1 == x2 == pos
			if (pos == sz / 2) return ret = 1;
			if (pos > sz / 2) pos = sz - pos;
			return ret = Calc(n - 1, pos, 1) + Calc(n - 1, sz / 2 - pos, 0);
		}
		else { // y1 == y2 == pos
			if (pos == sz / 2) return ret = 2;
			if (pos < sz / 2) return ret = 2 * Calc(n - 1, pos, 0);
			return ret = 2 * Calc(n - 1, pos - sz / 2, 1);
		}
	}
	else {
		if (flag) {
			if (pos == sz / 2) return 1;
			if (pos > sz / 2) pos = sz - pos;
			return Calc(n - 1, pos, 1) + Calc(n - 1, sz / 2 - pos, 0);
		}
		else {
			if (pos == sz / 2) return 2;
			if (pos < sz / 2) return 2 * Calc(n - 1, pos, 0);
			return 2 * Calc(n - 1, pos - sz / 2, 1);
		}
	}
}

int F(int n, int x1, int y1, int x2, int y2, int d = 0) {
	const int sz = 1 << n;

	// rotate cw, ccw
	if (d == 1) return F(n, y1, sz - x1, y2, sz - x2);
	if (d == 2) return F(n, sz - y1, x1, sz - y2, x2);

	// normalization
	if (x1 == x2 && y1 > y2) swap(y1, y2);
	if (y1 == y2 && x1 > x2) swap(x1, x2);
	if (x1 == x2 && y1 == y2) return 0;
	if (x1 == x2 && x1 > sz / 2) return F(n, sz - x1, y1, sz - x2, y2);
	if (x1 == 0 && x2 == 0 || x1 == sz && x2 == sz || y1 == 0 && y2 == 0 || y1 == sz && y2 == sz) return 0;

	// base case
	if (n == 1) {
		if (x1 == x2) {
			if (x1 == 1 && y1 == 0 && y2 >= 1) return 1;
			return 0;
		}
		else {
			if (y1 == 1) return x1 == 0 && x2 == 2 ? 2 : x1 == 0 || x2 == 2 ? 1 : 0;
			return 0;
		}
	}
	if (x1 == 0 && x2 == sz) return Calc(n, y1, 0);
	if (y1 == 0 && y2 == sz) return Calc(n, x1, 1);

	// divide and conquer
	if (x1 == x2) {
		if (x1 == sz / 2) return y1 < sz / 2 && y2 >= sz / 2;
		else {
			if (x1 < sz / 2) {
				if (y2 <= sz / 2) return F(n - 1, x1, y1, x2, y2);
				if (y1 >= sz / 2) return F(n - 1, x1, y1 - sz / 2, x2, y2 - sz / 2, 1);
				return F(n - 1, x1, y1, x2, sz / 2) + F(n - 1, x1, 0, x2, y2 - sz / 2, 1);
			}
			else {
				if (y2 <= sz / 2) return F(n - 1, x1 - sz / 2, y1, x2 - sz / 2, y2);
				if (y1 >= sz / 2) return F(n - 1, x1 - sz / 2, y1 - sz / 2, x2 - sz / 2, y2 - sz / 2, 2);
				return F(n - 1, x1 - sz / 2, y1, x2 - sz / 2, sz / 2) + F(n - 1, x1 - sz / 2, 0, x2 - sz / 2, y2 - sz / 2, 2);
			}
		}
	}
	else {
		if (y1 == sz / 2) return (int)(x1 == 0) + (int)(x2 == sz);
		else {
			if (y1 < sz / 2) {
				if (x2 <= sz / 2) return F(n - 1, x1, y1, x2, y2);
				if (x1 >= sz / 2) return F(n - 1, x1 - sz / 2, y1, x2 - sz / 2, y2);
				return F(n - 1, x1, y1, sz / 2, y2) + F(n - 1, 0, y1, x2 - sz / 2, y2);
			}
			else {
				if (x2 <= sz / 2) return F(n - 1, x1, y1 - sz / 2, x2, y2 - sz / 2, 1);
				if (x1 >= sz / 2) return F(n - 1, x1 - sz / 2, y1 - sz / 2, x2 - sz / 2, y2 - sz / 2, 2);
				return F(n - 1, x1, y1 - sz / 2, sz / 2, y2 - sz / 2, 1) + F(n - 1, 0, y1 - sz / 2, x2 - sz / 2, y2 - sz / 2, 2);
			}
		}
	}
}

int main() {
	fastio;
	memset(cache, -1, sizeof cache);
	for (int n, x1, x2, y; cin >> n && n;) {
		cin >> x1 >> x2 >> y;
		cout << F(n, x1, y, x2, y) << '\n';
	}
}
