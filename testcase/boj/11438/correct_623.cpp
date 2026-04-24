#include <bits/stdc++.h>
#define MOD 1000000007
#define ll long long
#define sz(x) ((int)(x).size())
#define rep(i,n) for(int i=0; i<(n); i++)
#define deb(v) cout << #v << ':' << v << '\n';

using namespace std;

struct SegmentMin {
	vector<int> tree;
	int n;
	SegmentMin(vector<int> &v) {
		tree.resize(2*sz(v));
		n = sz(v);
		for(int i=0; i<n; i++)
			tree[i+n] = v[i];
		for(int i=n-1;i>=1;i--) {
			tree[i] = min(tree[2*i], tree[2*i+1]);		
		}
	}
	int query(int l, int r) { // [l,r]
		l += n, r += n;
		if(l > r) swap(l, r);
		r++;
		int ret = MOD;
		while(l < r) {
			if(l&1) ret = min(ret, tree[l++]);
			if(r&1) ret = min(ret, tree[--r]);
			l /= 2, r /= 2;
		}
		return ret;
	}
};

#define MAXN 100000
vector<vector<int>> adj(MAXN+1);
vector<int> flattree;
int new2old[MAXN+1], old2pos[MAXN+1];
bool seen[MAXN+1];
int rn = 1;

void dfs(int i) {
	new2old[rn] = i;
	//printf("%d is assigned %d in segtree, at position %d\n", i, rn, sz(flattree));
	old2pos[i] = sz(flattree);
	flattree.push_back(rn);
	int thisnum = rn;
	rn++;
	seen[i] = true;
	for(int a: adj[i]) {
		if(!seen[a]) {
			dfs(a);
			flattree.push_back(thisnum);
		}
	}
}

int main() {
	ios::sync_with_stdio(false);cin.tie(NULL);
	int n, m;
	cin >> n;
	rep(i,n-1) {
		int a, b;
		cin >> a >> b;
		adj[a].push_back(b);
		adj[b].push_back(a);
	}
	dfs(1);
	cin >> m;
	SegmentMin tree(flattree);
	while(m--) {
		int a, b;
		cin >> a >> b;
		int mn = tree.query(old2pos[a], old2pos[b]);
		cout << new2old[mn] << '\n';
	}
}