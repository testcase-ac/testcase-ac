#include <bits/stdc++.h>
using namespace std;

#define ll long long
struct ST {
	vector<ll> tree;
	int n;
	ST(){}
	ST(int _n) {n = _n; tree.resize(2*n);}
	void read() {
		for(int i=n; i<2*n; i++)
			cin >> tree[i];
		build();
	}
	void build() {
		for(int i=n-1; i>0; i--)
			tree[i] = tree[i*2] + tree[i*2+1];
	}
	ll query(int l, int r) {  // range is [l,r)
		ll res = 0;
		l += n, r += n;
		while(l < r) {
			if(l&1) res += tree[l++];
			if(r&1) res += tree[--r];
			l >>= 1, r >>= 1;
		}
		return res;
	}
	void update(int i, ll val) {
		i += n;
		tree[i] = val;
		while(i>>=1)
			tree[i] = tree[2*i] + tree[2*i+1];
	}
};

int main() {
	ios::sync_with_stdio(0);cin.tie(0);
	int n, m, k;
	cin >> n >> m >> k;
	ST tree(n);
	tree.read();
	for(int i=0; i<m+k; i++) {
		ll a, b, c;
		cin >> a >> b >> c;
		if(a == 1)
			tree.update(b-1,c);
		else
			cout << tree.query(b-1,c) << '\n';
	}
}