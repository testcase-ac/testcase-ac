#include <bits/stdc++.h>
using namespace std;
#define int long long
const int MX = 1e5+2;
vector<int> adj[MX];
struct segtree { // assignment update, max query
	int n;
	vector<int> t;
	segtree(){}
	segtree(int _n) {
		n = _n;
		t.resize(2*n);
	}
	void build() {
		for(int i=n-1; i; i--)
			t[i] = max(t[2*i], t[2*i+1]);
	}
	void update(int i, int v) {
		i += n;
		t[i] = v;
		while(i /= 2)
			t[i] = max(t[2*i], t[2*i+1]); 
	}
	int query(int l, int r) {
		l += n, r += n;
		if(l > r) swap(l, r);
		int ret = INT_MIN;
		while(l < r) {
			if(l&1) ret = max(ret, t[l++]);
			if(r&1) ret = max(ret, t[--r]);
			l /= 2, r /= 2;
		}
		return ret;
	}
};
// HLD implementation adapted for this solution.
// Reference: https://codeforces.com/blog/entry/53170
struct HLD {
	int n, t, root;
	vector<int> sz, in, inv, par, nxt;
	segtree seg;
	HLD(int _n, int _root) {
		n = _n+1;
		t = 0;
		root = _root;
		sz = in = inv = par = nxt = vector<int>(n);
		seg = segtree(n);
		nxt[root] = root;
		dfs_sz(root, -1);
		dfs_hld(root);
	}
	void dfs_sz(int v, int p) {
		par[v] = p;
		sz[v] = 1;
		auto it = find(adj[v].begin(), adj[v].end(), p);
		if(it != adj[v].end())
			adj[v].erase(it);
		for(int &a: adj[v]) {
			dfs_sz(a, v);
			sz[v] += sz[a];
			if(sz[a] > sz[adj[v][0]]) {
				swap(a, adj[v][0]);
			}
		}
	}
	void dfs_hld(int v) {
		in[v] = t++;
		inv[in[v]] = v;
		for(int a: adj[v]) {
			nxt[a] = (a == adj[v][0] ? nxt[v] : a);
			// printf("nxt %d = %d\n", a, nxt[a]);
			dfs_hld(a);
		}
	}
	void update(int i) {
		i = in[i]; // not nxt
		int v = seg.query(i, i+1);
		seg.update(i, v^1);
	}
	int query(int i) {
		int ans = -1;
		while(i > 0) {
			if(seg.query(in[nxt[i]], in[i]+1)) {
				int l = in[nxt[i]], r = in[i];
				while(l < r) {
					int m = (l+r)/2;
					if(seg.query(in[nxt[i]], m+1)) { // search area wrong
						r = m;
					} else {
						l = m+1;
					}
				}
				ans = inv[l];
			}
			i = par[nxt[i]];
		}
		return ans;
	}
};

int32_t main() {
	ios::sync_with_stdio(0);cin.tie(0);
	int n;
	cin >> n;
	for(int i=0; i<n-1; i++) {
		int u, v;
		cin >> u >> v;
		adj[u].push_back(v);
		adj[v].push_back(u);
	}
	HLD hld(n, 1);
	int q;
	cin >> q;
	while(q--) {
		int type, i;
		cin >> type >> i;
		if(type == 1) {
			hld.update(i);
		} else {
			cout << hld.query(i) << '\n';
		}
	}
}
