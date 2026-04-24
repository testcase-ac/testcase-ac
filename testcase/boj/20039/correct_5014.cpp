#include <bits/stdc++.h>
using namespace std;
struct segtree {
	vector<int> seg;
	int n;
	segtree(int n): n(n) {
		seg.resize(2*n, -1);
	}
	int query(int l, int r) {
		l += n, r += n;
		int res = -1;
		while(l < r) {
			if(l&1) res = max(res, seg[l++]);
			if(r&1) res = max(res, seg[--r]);
			l /= 2, r /= 2;
		}
		return res;
	}

	void update(int t, int v) {
		t += n;
		if(v <= seg[t]) return;
		seg[t] = v;
		while(t /= 2) {
			seg[t] = max(seg[t*2], seg[t*2+1]);
		}
	}
};
int32_t main() {
	cin.tie(0)->sync_with_stdio(0);
	int N;
	cin >> N;
	vector<int> A(N), V;
	for(int i=0; i<N; i++) {
		cin >> A[i];
	}
	V = A;
	sort(V.begin(), V.end());
	for(int &a: A)
		a = lower_bound(V.begin(), V.end(), a) - V.begin();

	int mn = INT_MAX, mx = -1;
	segtree u2(N), u3(N), d2(N), d3(N);
	for(int i=0; i<N; i++) {
		int u2v = d3.query(0, A[i]);
		if(mn < A[i])
			u2v = max(u2v, 1);
		int d2v = u3.query(A[i], N);
		if(mx > A[i])
			d2v = max(d2v, 1);
		int u3v = max(u2.query(0, A[i]), u3.query(0, A[i]));
		int d3v = max(d2.query(A[i], N), d3.query(A[i], N));
		u2.update(A[i], u2v+1);
		u3.update(A[i], u3v+1);
		d2.update(A[i], d2v+1);
		d3.update(A[i], d3v+1);
		mn = min(mn, A[i]);
		mx = max(mx, A[i]);
	}
	int ans = max({u3.query(0, N), d3.query(0, N)});
	cout << (ans <= 2 ? 0 : ans);
}
