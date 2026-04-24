#include <bits/stdc++.h>
using namespace std;
struct segtree {
	vector<int> t, lazy;
	int n;
	segtree(int _n) {
		n = _n;
		t.resize(2*n);
		lazy.resize(2*n);
	}
	void apply(int i, int v) {
		if(i < n) lazy[i] ^= v;
		else t[i] ^= v;
	}
	void build(int p) {
		while(p /= 2)
			t[p] = t[p*2]^t[p*2+1];
	}
	void push(int p) {
		for(int i=32-__builtin_clz(n); i; i--) {
			int k = p >> i;
			if(lazy[k] != 0) {
				apply(2*k, lazy[k]);
				apply(2*k+1, lazy[k]);
				lazy[k] = 0;
			}
		}
	}
	void update(int l, int r, int v) {
		l += n, r += n;
		int l0 = l, r0 = r;
		while(l < r) {
			if(l&1) apply(l++, v);
			if(r&1) apply(--r, v);
			l /= 2, r /= 2;
		}
		build(l0);
		build(r0-1);
	}
	int query(int l, int r) {
		l += n, r += n;
		push(l);
		push(r-1);
		int ret = 0;
		while(l < r) {
			if(l&1) ret ^= t[l++];
			if(r&1) ret ^= t[--r];
			l /= 2, r /= 2;
		}
		return ret;
	}
};
int main() {
	ios::sync_with_stdio(0);cin.tie(0);
	int n;
	cin >> n;
	segtree tree(n);
	for(int i=0; i<n; i++) {
		int t;
		cin >> t;
		tree.update(i, i+1, t);
	}
	int q;
	cin >> q;
	while(q--) {
		int t;
		cin >> t;
		if(t == 1) {
			int a, b, c;
			cin >> a >> b >> c;
			tree.update(a, b+1, c);
		} else {
			int a, b;
			cin >> a >> b;
			cout << tree.query(a, b+1) << '\n';
		}
	}
}
