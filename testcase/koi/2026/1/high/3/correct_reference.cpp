/*
* Jump
* Main Correct Solution (C++)
*/

#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;
typedef long long ll;

#define MAXN 300'010

namespace fenwick {
	int tree[MAXN];
	int N;
	void upd(int i, int x) { i++; while (i <= N) { tree[i] += x, i += i & -i; } }
	int get(int i) { i++; int ans = 0; while (i) { ans += tree[i], i -= i & -i; } return ans; }
	int get(int l, int r) {
		if (l == 0) return get(r);
		return get(r) - get(l - 1);
	}
	void init(int _N) {
		N = _N;
		for (int i = 1; i <= N; i++) tree[i] = 0;
	}
}

namespace rmq {
	int tree[MAXN << 2];
	void init(int s, int e, int loc = 1) {
		tree[loc] = 1e9;
		if (s == e) return;
		int m = s + e >> 1;
		init(s, m, loc * 2);
		init(m + 1, e, loc * 2 + 1);
	}
	void upd(int s, int e, int i, int x, int loc = 1) {
		if (e < i || i < s) return;
		tree[loc] = min(tree[loc], x);
		if (s == e) return;
		int m = s + e >> 1;
		upd(s, m, i, x, loc * 2);
		upd(m + 1, e, i, x, loc * 2 + 1);
	}
	int query(int s, int e, int l, int r, int loc = 1) {
		if (e < l || r < s) return 1e9;
		if (l <= s && e <= r) return tree[loc];
		int m = s + e >> 1;
		return min(query(s, m, l, r, loc * 2), query(m + 1, e, l, r, loc * 2 + 1));
	}
}

int X[MAXN];

int left_cnt[MAXN];
int right_cnt[MAXN];
int ans[MAXN];
int xcnt[MAXN];

signed main() {
	ios::sync_with_stdio(false), cin.tie(0);
	int N, D;
	cin >> N >> D;
	vector<int> xlist;
	for (int i = 1; i <= N; i++) {
		cin >> X[i];
		xlist.push_back(X[i]);
	}
	sort(xlist.begin(), xlist.end());
	xlist.erase(unique(xlist.begin(), xlist.end()), xlist.end());
	int xs = xlist.size();

	// X[i] = X[j]
	for (int i = N; i >= 1; i--) {
		int ind = lower_bound(xlist.begin(), xlist.end(), X[i]) - xlist.begin();
		xcnt[ind]++;
		ans[i] += xcnt[ind];
	}

	// X[i] < X[j]
	rmq::init(0, xs - 1);
	fenwick::init(N);
	for (int i = N; i >= 1; i--) {
		int l, r;
		l = upper_bound(xlist.begin(), xlist.end(), X[i]) - xlist.begin();
		r = upper_bound(xlist.begin(), xlist.end(), X[i] + D) - xlist.begin() - 1;
		int ind = 0;
		if (l <= r) {
			ind = rmq::query(0, xs - 1, l, r);
			if (ind > N) ind = 0;
		}
		int xi;
		xi = lower_bound(xlist.begin(), xlist.end(), X[i]) - xlist.begin();
		if (ind) {
			int xj;
			xj = lower_bound(xlist.begin(), xlist.end(), X[ind]) - xlist.begin();
			right_cnt[i] = fenwick::get(xi + 1, xj) + right_cnt[ind];
		}
		rmq::upd(0, xs - 1, xi, i);
		fenwick::upd(xi, 1);
	}

	// X[i] > X[j]
	rmq::init(0, xs - 1);
	fenwick::init(N);
	for (int i = N; i >= 1; i--) {
		int l, r;
		l = lower_bound(xlist.begin(), xlist.end(), X[i] - D) - xlist.begin();
		r = lower_bound(xlist.begin(), xlist.end(), X[i]) - xlist.begin() - 1;
		int ind = 0;
		if (l <= r) {
			ind = rmq::query(0, xs - 1, l, r);
			if (ind > N) ind = 0;
		}
		int xi;
		xi = lower_bound(xlist.begin(), xlist.end(), X[i]) - xlist.begin();
		if (ind) {
			int xj;
			xj = lower_bound(xlist.begin(), xlist.end(), X[ind]) - xlist.begin();
			left_cnt[i] = fenwick::get(xj, xi - 1) + left_cnt[ind];
		}
		rmq::upd(0, xs - 1, xi, i);
		fenwick::upd(xi, 1);
	}
	for (int i = 1; i <= N; i++) {
		ans[i] += left_cnt[i] + right_cnt[i];
		cout << ans[i] << ' ';
	}
}
