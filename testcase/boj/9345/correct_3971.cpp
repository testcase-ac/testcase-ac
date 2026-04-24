#include <bits/stdc++.h>
using namespace std;
const int MX = 1e5+2;
typedef long long ll;
typedef pair<int, int> pii;
struct segtree {
	vector<pii> seg;
	int n;
	segtree(int _n) {
		n = _n;
		seg.resize(2*n);
		for(int i=n; i<2*n; i++) {
			seg[i] = {i-n, i-n};
		}
		for(int i=n-1; i; i--)
			seg[i] = u(seg[2*i], seg[2*i+1]);
	}
	pii u(pii& prl, pii& prr) {
		return {min(prl.first, prr.first), max(prl.second, prr.second)};
	}
	void update(int i, int j) {
		i += n, j += n;
		swap(seg[i], seg[j]);
		while(1) {
			i /= 2, j /= 2;
			if(i == j) break;
			seg[i] = u(seg[2*i], seg[2*i+1]);
			seg[j] = u(seg[2*j], seg[2*j+1]);
		}
	}
	pii query(int l, int r) {
		pii res = {1e9, -1e9};
		l += n, r += n+1;
		while(l < r) {
			if(l&1) {
				res = u(res, seg[l++]);
				l++;
			}
			if(r&1) {
				res = u(res, seg[--r]);
			}
			l /= 2, r /= 2;
		}
		return res;
	}
};
void solve() {
	int n, k;
	cin >> n >> k;
	segtree st(n);
	for(int i=0; i<k; i++) {
		int q, a, b;
		cin >> q >> a >> b;
		if(q) {
			pii r = st.query(a, b);
			cout << ((r.first == a && r.second == b) ? "YES\n" : "NO\n");
		} else {
			st.update(a, b);
		}
	}
}
int main() {
	ios::sync_with_stdio(0);cin.tie(0);
	int t;
	cin >> t;
	while(t--) {
		solve();
	}
}
